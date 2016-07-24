#include "stdafx.h"

#include <opencv2/opencv.hpp>
#include <opencv2/opencv_lib.hpp>

using namespace cv;

int main()
{
	Mat image = cv::imread("../../image/lena.jpg");

	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			cv::Vec3b vec = image.at<cv::Vec3b>(y, x);
			int B = vec(0);
			int G = vec(1);
			int R = vec(2);
			
			int M = (int)((R * 2.0f + G * 4.0f + B * 1.0f) / 7.0f);
			vec = Vec3b(M, M, M);

			image.at<cv::Vec3b>(y, x) = vec;
		}
	}

	cv::imshow("", image);
	cv::imwrite("lena_m.jpg", image);

	waitKey(0);

    return 0;
}
