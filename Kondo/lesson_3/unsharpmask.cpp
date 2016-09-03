#include "filter.h"

cv::Mat unsharpmask(cv::Mat img, int k)
{
	int size = 3;
	// 平均化フィルタのカーネル作成
	float arnd = -1.0f / 9 * k;
	float cntr = 1.0f + 8.0 / 9 * k;
	cv::Mat kernel = (cv::Mat_<float>(size, size) << arnd, arnd, arnd, arnd, cntr, arnd, arnd, arnd, arnd);

	cv::Mat dstimg = difFilterCore(img, kernel);
	return dstimg;
}