#include "filter.h"

cv::Mat difFilterCore(const cv::Mat img, const cv::Mat kernel)
{
	cv::Mat dstimg = cv::Mat::zeros(img.size(), CV_8UC1); // 何かで初期化しておかないと、下のatを使った代入でエラーがでる。
	int ksize = kernel.cols;

	if (img.channels() == 3)
	{
		// カラー画像へのエッジフィルタはない？
	}

	if (img.channels() == 1)
	{
		// エッジ処理込み
		for (int y = 0; y < img.rows; y++)
		{
			for (int x = 0; x < img.cols; x++)
			{
				// 積和した値を結果に。(int)で値の切り捨て
				int conv = convolute(x, y, img, kernel);
				dstimg.at<uchar>(y, x) = abs(conv);
			}
		}
	}
	return dstimg;
}


cv::Mat diffFileter(const cv::Mat img, const int direction)
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



cv::Mat prewitt(const cv::Mat img, const int direction)
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


cv::Mat sobel(const cv::Mat img, const int direction)
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



cv::Mat laplacianFilter(const cv::Mat img)
{
	int size = 3;
	// 平均化フィルタのカーネル作成
	cv::Mat kernel = (cv::Mat_<float>(size, size) << 0, 1.0, 0, 1.0, -4.0, 1.0, 0, 1.0, 0);

	cv::Mat dstimg = difFilterCore(img, kernel);
	return dstimg;
}
