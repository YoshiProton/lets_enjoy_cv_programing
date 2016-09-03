#include "filter.h"

cv::Mat difFilterCore(cv::Mat img, cv::Mat kernel)
{
	cv::Mat dstimg = cv::Mat::zeros(img.size(), CV_8UC1); // 何かで初期化しておかないと、下のatを使った代入でエラーがでる。
	int ksize = kernel.cols;

	if (img.channels() == 3)
	{
		// カラー画像へのエッジフィルタはない？
	}

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
				float mulsum = multSumMat(kernel, reg);
				// 積和した値を結果に。(int)で値の切り捨て
				// 差分を計算すると、負数もでるので、絶対値をとる。
				dstimg.at<uchar>(y, x) = (int)abs(mulsum);
			}
		}
	}
	return dstimg;
}


cv::Mat diffFileter(cv::Mat img, int direction)
{
	int size = 3;
	// 微分フィルタのカーネル作成
	cv::Mat kernel;
	switch (direction)
	{
		case HORIZONTAL:
			kernel = (cv::Mat_<float>(size, size) << 0, 0, 0, -0.5, 0, 0.5, 0, 0, 0);
			break;
		case LONGITUDIAL:
			kernel = (cv::Mat_<float>(size, size) << 0, 0.5, 0, 0, 0, 0, 0, -0.5, 0);
			break;
		default:
			kernel = (cv::Mat_<float>(size, size) << 0, 0, 0, 0, 1, 0, 0, 0, 0);
	}
	cv::Mat dstimg = difFilterCore(img, kernel);

	return dstimg;
}



cv::Mat prewitt(cv::Mat img, int direction)
{
	int size = 3;
	// 平均化フィルタのカーネル作成
	cv::Mat kernel;
	switch (direction)
	{
	case HORIZONTAL:
		kernel = (cv::Mat_<float>(size, size) << -1.0, 0, 1.0, -1.0, 0, 1.0, -1.0, 0, 1.0);
		kernel = kernel * 1.0f / 6;
		break;
	case LONGITUDIAL:
		kernel = (cv::Mat_<float>(size, size) << 1.0, 1.0, 1.0, 0, 0, 0, -1.0, -1.0, -1.0);
		kernel = kernel * 1.0f / 6;
		break;
	default:
		kernel = (cv::Mat_<float>(size, size) << 0, 0, 0, 0, 1, 0, 0, 0, 0);
	}
	
	cv::Mat dstimg = difFilterCore(img, kernel);
	return dstimg;
}


cv::Mat sobel(cv::Mat img, int direction)
{
	int size = 3;
	// 平均化フィルタのカーネル作成
	cv::Mat kernel;
	switch (direction)
	{
	case HORIZONTAL:
		kernel = (cv::Mat_<float>(size, size) << -1.0, 0, 1.0, -2.0, 0, 2.0, -1.0, 0, 1.0);
		kernel = kernel * 1.0f / 8;
		break;
	case LONGITUDIAL:
		kernel = (cv::Mat_<float>(size, size) << 1.0, 2.0, 1.0, 0, 0, 0, -1.0, -2.0, -1.0);
		kernel = kernel * 1.0f / 8;
		break;
	default:
		kernel = (cv::Mat_<float>(size, size) << 0, 0, 0, 0, 1, 0, 0, 0, 0);
	}

	cv::Mat dstimg = difFilterCore(img, kernel);
	return dstimg;
}



cv::Mat laplacianFilter(cv::Mat img)
{
	int size = 3;
	// 平均化フィルタのカーネル作成
	cv::Mat kernel = (cv::Mat_<float>(size, size) << 0, 1.0, 0, 1.0, -4.0, 1.0, 0, 1.0, 0);

	cv::Mat dstimg = difFilterCore(img, kernel);
	return dstimg;
}
