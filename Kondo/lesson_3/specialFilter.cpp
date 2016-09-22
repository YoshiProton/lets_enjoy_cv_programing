#include "filter.h"


int getMedianVal(const int x, const int y, const cv::Mat img, const int ksize)
{
	int center = ksize * ksize / 2 + 1;
	int margin = ksize / 2;
	std::vector<int> vec;

	// エッジ処理込み
	for (int wy = 0; wy < ksize; wy++)
	{
		for (int wx = 0; wx < ksize; wx++)
		{
			int winx = getRestricted(x + wx - margin, 0, img.cols - 1);
			int winy = getRestricted(y + wy - margin, 0, img.rows - 1);
			vec.push_back(img.at<uchar>(winy, winx));
		}
	}
	std::sort(vec.begin(), vec.end());

	return vec[center];
}

cv::Mat medianFilter(const cv::Mat img, const int ksize)
{
	// エッジの処理はしないので、オリジナル画像をコピー
	cv::Mat dstimg = img.clone();
	int center = ksize*ksize / 2 + 1;

	// 処理の簡略化のため、エッジ周辺の処理をしていないバージョン
	// グレー画像
	if (img.channels() == 1)
	{
		for (int y = 0; y < img.rows; y++)
		{
			for (int x = 0; x < img.cols; x++)
			{
				// (x,y)を中心とする領域の中間地の取得
				dstimg.at<uchar>(y, x) = getMedianVal(x, y, img, ksize);
			}
		}
	}
	else if (img.channels() == 3)
	{
		//（カラーの場合は各BGRに、grayimgへと同じ処理）
		// BGRに対して、grayへの処理を再帰呼び出ししてもよさそうだが、
		// x,yのfor分が余計になりそうなので、コアの処理をBGRのループにした。
		std::vector<cv::Mat> channels;
		std::vector<cv::Mat> channels_dst;
		cv::split(img, channels);
		channels_dst = channels; //ここも、エッジ処理をしていないので、元のコピー

		for (int y = 0; y < img.rows; y++)
		{
			for (int x = 0; x < img.cols; x++)
			{
				// channels毎に平均化処理
				for (int i = 0; i < channels.size(); i++)
				{
					// x,yを中心とした中間値の計算
					channels_dst[i].at<uchar>(y, x) = getMedianVal(x, y, channels[i], ksize);
				}
			}
		}
		cv::merge(channels_dst, dstimg);
	}
	// [TO DO] エッジ周辺の処理も考慮したバージョンを作る

	return dstimg;
}




cv::Mat bilateralFilter(const cv::Mat img, const int ksize, const float sigma_xy, const float sigma_color)
{
	// エッジの処理はしないので、オリジナル画像をコピー
	cv::Mat dstimg = img.clone();

	// 処理の簡略化のため、エッジ周辺の処理をしていないバージョン
	// グレー画像
	if (img.channels() == 1)
	{
		int margin = ksize / 2; // エッジ周辺のマージンを取る。
		cv::Mat reg = cv::Mat::zeros(ksize, ksize, CV_8UC1); // 領域の確保
		for (int y = margin; y < img.rows - margin; y++)
		{
			for (int x = margin; x < img.cols - margin; x++)
			{
				reg = img(cv::Rect(x - margin, y - margin, ksize, ksize)).clone();

				float blval = bilateralCore(reg, sigma_xy, sigma_color);
				dstimg.at<uchar>(y, x) = (int)blval;
			}
		}
	}
	else if (img.channels() == 3)
	{
		// カラー対応
		int margin = ksize / 2; // エッジ周辺のマージンを取る。
		cv::Mat reg = cv::Mat::zeros(ksize, ksize, CV_8UC1); // 領域の確保
		for (int y = margin; y < img.rows - margin; y++)
		{
			for (int x = margin; x < img.cols - margin; x++)
			{
				reg = img(cv::Rect(x - margin, y - margin, ksize, ksize)).clone();

				cv::Vec3b blval = bilateralCoreColor(reg, sigma_xy, sigma_color);
				for (int k = 0; k < 3; k++)
				{
					dstimg.at<cv::Vec3b>(y, x)[k] = blval[k];
				}
			}
		}
	}

	return dstimg;
}



float bilateralCore(cv::Mat reg, float sigma_xy, float sigma_color)
{
	float weight_sum = 0.0;			// 重みの和
	float weightedcolor_sum = 0.0;	// 重みをかけた画素値の和
	float weight_xy = 0.0;			// 空間方向の重み
	float weight_color = 0.0;		// 色空間方向の重み
	float weight_ij = 0.0;			// 空間、色空間の重みの積
	double r2 = 0;					// x^2 + y^2
	int rc2 = 0;					// 色空間での差の２乗
	int cx = reg.cols / 2 + 1;		// 領域の中心(x,y)
	int cy = cx;
	double inv_sigma_xy2 = 1 / (sigma_xy * sigma_xy);			// 空間方向分散の２乗の逆数
	double inv_sigma_color2 = 1 / (sigma_color * sigma_color);	// 色空間方向分散の２乗の逆数
	int color_ij = 0;						//考慮位置の画素値
	int color_cnt = reg.at<uchar>(cy, cx);	// 中心の画素値
	float weightedcolor_ij = 0.0;			// 重みをかけた画素値
	float res_color = 0.0;		// 最終結果画素
	 
	for (int i = 0; i < reg.rows; i++)
	{
		for (int j = 0; j < reg.cols; j++)
		{
			// 空間方向の重みの計算
			r2 = (i - cx)* (i - cx) + (j - cy)*(j - cy);
			weight_xy = exp(-r2 * 0.5 * inv_sigma_xy2);
			// 色空間方向の画素値の差、重みの計算
			color_ij = reg.at<uchar>(i, j);
			rc2 = (color_ij - color_cnt) * (color_ij - color_cnt);
			weight_color = exp(-0.5 * rc2 * inv_sigma_color2);
			// 空間方向、色空間方向の重みの積
			weight_ij = weight_xy * weight_color;			
			weight_sum += weight_ij;
			// 重みのかかった画素値の計算
			weightedcolor_ij = color_ij * weight_ij;
			weightedcolor_sum += weightedcolor_ij;
		}
	}
	res_color = weightedcolor_sum / weight_sum;

	return res_color;
}


cv::Vec3f bilateralCoreColor(cv::Mat reg, float sigma_xy, float sigma_color)
{
	float weight_sum = 0.0;			// 重みの和
	cv::Vec3f weightedcolor_sum = cv::Vec3f(0, 0, 0);	// 重みをかけた画素値の和
	float weight_xy = 0.0;			// 空間方向の重み
	float weight_color = 0.0;		// 色空間方向の重み
	float weight_ij = 0.0;			// 空間、色空間の重みの積
	double r2 = 0;					// x^2 + y^2
	int rc2 = 0;					// 色空間での差の２乗
	int cx = reg.cols / 2 + 1;		// 領域の中心(x,y)
	int cy = cx;
	double inv_sigma_xy2 = 1 / (sigma_xy * sigma_xy);			// 空間方向分散の２乗の逆数
	double inv_sigma_color2 = 1 / (sigma_color * sigma_color);	// 色空間方向分散の２乗の逆数
	cv::Vec3b color_ij = 0;						//考慮位置の画素値
	cv::Vec3b color_cnt = reg.at<cv::Vec3b>(cy, cx);	// 中心の画素値
	cv::Vec3f weightedcolor_ij = cv::Vec3f(0, 0, 0);	// 重みをかけた画素値
	cv::Vec3f res_color = cv::Vec3f(0, 0, 0);		// 最終結果画素

	for (int i = 0; i < reg.rows; i++)
	{
		for (int j = 0; j < reg.cols; j++)
		{
			// 空間方向の重みの計算
			r2 = (i - cx)* (i - cx) + (j - cy)*(j - cy);
			weight_xy = exp(-r2 * 0.5 * inv_sigma_xy2);

			// 色空間方向の画素値の差、重みの計算
			color_ij = reg.at<cv::Vec3b>(i, j);
			rc2 = colordist2(color_cnt, color_ij);
			weight_color = exp(-0.5 * rc2 * inv_sigma_color2);

			// 空間方向、色空間方向の重みの積		 
			weight_ij = weight_xy * weight_color;
			weight_sum += weight_ij;

			// 重みのかかった画素値の計算
			weightedcolor_ij = color_ij * weight_ij;
			for (int k = 0; k < 3; k++)
			{
				weightedcolor_sum[k] += weightedcolor_ij[k];
			}
		}
	}
	res_color = weightedcolor_sum / weight_sum;

	return res_color;

}


// RGB空間での画素値の差の２乗を計算
int colordist2(cv::Vec3b color1, cv::Vec3b color2)
{
	float colordistance = 0.0;
	int dif_sum = 0;
	for (int i = 0; i < color1.channels; i++)
	{
		int difs = color1[i] - color2[i];
		dif_sum += difs*difs;
	}

	return colordistance;
}


cv::Mat nonlocalmean(cv::Mat img)
{
	cv::Mat dstimg;

	return dstimg;
}

