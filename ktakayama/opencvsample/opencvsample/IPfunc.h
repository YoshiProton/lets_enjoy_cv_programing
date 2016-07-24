#include <opencv2/opencv.hpp>
#include <opencv2/opencv_lib.hpp>

using namespace cv;

inline void my_grayscale(const cv::Mat image, cv::Mat out)
{
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			cv::Vec3b vec = image.at<cv::Vec3b>(y, x);
			int B = vec(0);
			int G = vec(1);
			int R = vec(2);

			int M = (int)(R * 0.299f + G * 0.587f + B * 0.144f + 0.5f);
			vec = Vec3b(M, M, M);

			out.at<cv::Vec3b>(y, x) = vec;
		}
	}

	return;
}


inline void my_resizeNN(const cv::Mat image, cv::Mat out, const double scale)
{
	for (int y = 0; y < image.rows * scale; y++)
	{
		for (int x = 0; x < image.cols * scale; x++)
		{
			cv::Vec3b vec = image.at<cv::Vec3b>((int)((double)y / scale), (int)((double)x / scale));

			out.at<cv::Vec3b>(y, x) = vec;
		}
	}

	return;
}
