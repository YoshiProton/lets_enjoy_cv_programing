#include "stdafx.h"
#include "IPfunc.h"


IPfunc::IPfunc()
{
}


IPfunc::~IPfunc()
{
}

// グレースケール化
void IPfunc::grayscale(const cv::Mat image, cv::Mat out)
{
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			cv::Vec3b vec = image.at<cv::Vec3b>(y, x);
			int B = vec(0);
			int G = vec(1);
			int R = vec(2);

			int M = (int)IPcommon::clamp(R * 0.299f + G * 0.587f + B * 0.144f, 0.0f, 255.0f);
			vec = cv::Vec3b(M, M, M);

			out.at<cv::Vec3b>(y, x) = vec;
		}
	}

	return;
}

// HSVの値セット
void IPfunc::valueSetHSV(cv::Mat out, int H, int S, int V)
{
	cv::Mat out_hsv = out;
	cv::Vec3b vec(H, S, V);

	for (int y = 0; y < out.rows; y++)
	{
		for (int x = 0; x < out.cols; x++)
		{
			out_hsv.at<cv::Vec3b>(y, x) = vec;
		}
	}

	cvtColor(out_hsv, out, CV_HSV2BGR);

	return;
}

// 肌検出
void IPfunc::skinDetect(const cv::Mat image, cv::Mat out)
{
	cv::Mat image_hsv;
	cvtColor(image, image_hsv, CV_BGR2HSV);

	for (int y = 0; y < image_hsv.rows; y++)
	{
		for (int x = 0; x < image_hsv.cols; x++)
		{
			cv::Vec3b vec = image_hsv.at<cv::Vec3b>(y, x);
			int H = vec(0);

			cv::Vec3b vec_rgb = image.at<cv::Vec3b>(y, x);

			if (H < 0 || H > 15)
			{
				vec_rgb = cv::Vec3b(0, 0, 0);
			}

			out.at<cv::Vec3b>(y, x) = vec_rgb;
		}
	}

	return;
}
