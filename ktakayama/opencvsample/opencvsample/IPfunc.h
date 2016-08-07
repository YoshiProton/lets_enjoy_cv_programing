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


inline void my_valueSetHSV(cv::Mat out, int H, int S, int V)
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


inline void my_skinDetect(const cv::Mat image, cv::Mat out)
{
	cv::Mat image_hsv;
	cvtColor(image, image_hsv, CV_BGR2HSV);

	for (int y = 0; y < image_hsv.rows; y++)
	{
		for (int x = 0; x < image_hsv.cols; x++)
		{
			cv::Vec3b vec = image_hsv.at<cv::Vec3b>(y, x);
			int H = vec(0);
			int S = vec(1);
			int V = vec(2);

			// printf("(%d, %d, %d)\n", H, S, V);

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
