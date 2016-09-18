#include "filter.h"


int getMedianVal(cv::Mat reg, int center)
{
	std::vector<int> vec; 
	cv::Mat reshaped = reg.reshape(1, 1); //1channel, 1行にreshape

	for (int i = 0; i < reshaped.cols; i++)
	{
		vec.push_back(reshaped.at<uchar>(0, i));
	}
	std::sort(vec.begin(), vec.end());

	return vec[center];
}

cv::Mat medianFilter(cv::Mat img, int ksize)
{
	// エッジの処理はしないので、オリジナル画像をコピー
	cv::Mat dstimg = img.clone();
	int center = ksize*ksize / 2 + 1;

	// 処理の簡略化のため、エッジ周辺の処理をしていないバージョン
	// グレー画像
	if (img.channels() == 1)
	{
		int margin = ksize / 2; // エッジ周辺のマージンを取る。
		cv::Mat reg;
		for (int y = margin; y < img.rows - margin; y++)
		{
			for (int x = margin; x < img.cols - margin; x++)
			{
				// (size x size)の領域の画像とkernelの要素同士の積を計算
				reg = img(cv::Rect(x - margin, y - margin, ksize, ksize)).clone();
				int med = getMedianVal(reg, center);
				// 積和した値を結果に。(int)で値の切り捨て
				dstimg.at<uchar>(y, x) = med;
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

		int margin = ksize / 2; // 処理しないエッジ周辺のマージン。
		cv::Mat reg;
		for (int y = margin; y < img.rows - margin; y++)
		{
			for (int x = margin; x < img.cols - margin; x++)
			{
				// channels毎に平均化処理
				for (int i = 0; i < channels.size(); i++)
				{
					// (size x size)の領域の画像とkernelの要素同士の積を計算
					reg = channels[i](cv::Rect(x - margin, y - margin, ksize, ksize)).clone();
					int med = getMedianVal(reg, center);
					// 積和した値を結果に。(int)で値の切り捨て
					channels_dst[i].at<uchar>(y, x) = med;
				}
			}
		}
		cv::merge(channels_dst, dstimg);
	}
	// [TO DO] エッジ周辺の処理も考慮したバージョンを作る

	return dstimg;
}




cv::Mat bilateralFilter(cv::Mat img, int ksize, float sigma_xy, float sigma_color)
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
	}


	return dstimg;
}

float bilateralCore(cv::Mat reg, float sigma_xy, float sigma_color)
{
	float weight_sum = 0.0;			// 重みの和
	float weightedcolor_sum = 0.0;	//重みをかけた画素値の和
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



cv::Mat nonlocalmean(cv::Mat img)
{
	cv::Mat dstimg;

	return dstimg;
}

