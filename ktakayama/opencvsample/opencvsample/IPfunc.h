#include <opencv2/opencv.hpp>
#include <opencv2/opencv_lib.hpp>

using namespace cv;

// clamp処理
inline float my_clamp(float x, float min, float max) {
	if (x < min) x = min;
	if (x > max) x = max;

	return x;
}

// clamp処理(cv::Vec3f)
inline cv::Vec3f my_clamp(cv::Vec3f x, float min, float max) {
	for (int i = 0; i < 3; i++)
	{
		if (x(i) < min) x(i) = min;
		if (x(i) > max) x(i) = max;
	}

	return x;
}

// mirror処理
inline int my_mirror(int x, int min, int max) {
	while (x < min || x >= max) {
		if (x < min) x = min + (min - x - 1);
		if (x >= max) x = max + (max - x - 1);
	}

	return x;
}


// グレースケール化
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

// サイズ変更(Nearest Neighbor)
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

// HSVの値セット
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

// 肌検出
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

// 平均化フィルタ
inline void my_average(const cv::Mat image, cv::Mat out)
{
	int size = 1;
	int mx, my;
	cv::Vec3f c;
	float w;

	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			c = cv::Vec3f(0.0f, 0.0f, 0.0f);

			for (int dy = -size; dy <= size; dy++)
			{
				for (int dx = -size; dx <= size; dx++)
				{
					mx = my_mirror(x + dx, 0, image.cols);
					my = my_mirror(y + dy, 0, image.rows);

					w = 1.0f / 9.0f;

					cv::Vec3b vec = image.at<cv::Vec3b>(my, mx);
					c += (cv::Vec3f)vec * w;
				}
			}

			c = my_clamp(c, 0.0f, 255.0f);
			out.at<cv::Vec3b>(y, x) = (cv::Vec3b)c;
		}
	}

	return;
}
