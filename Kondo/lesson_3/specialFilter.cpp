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
		for (int x = margin; x < img.rows - margin; x++)
		{
			for (int y = margin; y < img.cols - margin; y++)
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
		for (int x = margin; x < img.rows - margin; x++)
		{
			for (int y = margin; y < img.cols - margin; y++)
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




cv::Mat bilateralFilter(cv::Mat img, int sigma_x, int sigma_color)
{
	cv::Mat dstimg;

	return dstimg;
}

cv::Mat nonlocalmean(cv::Mat img)
{
	cv::Mat dstimg;

	return dstimg;
}

