#include "IPcommon.h"

// フィルタ処理
inline void my_filter(const cv::Mat image, cv::Mat out, cv::Mat filter)
{
	int size = (filter.cols - 1) / 2;
	int mx, my;
	cv::Vec3f c;

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

					cv::Vec3b vec = image.at<cv::Vec3b>(my, mx);
					c += (cv::Vec3f)vec * filter.at<float>(dy + size, dx + size);
				}
			}

			c = my_clamp(c, 0.0f, 255.0f);
			out.at<cv::Vec3b>(y, x) = (cv::Vec3b)c;
		}
	}

	return;
}

// 平均化フィルタ
inline void my_average(const cv::Mat image, cv::Mat out, const int size)
{
	int wsize = size * 2 + 1;
	cv::Mat filter(wsize, wsize, CV_32F);

	filter = 1.0f / (float)(wsize * wsize);

	my_filter(image, out, filter);

	return;
}

inline void my_average(const cv::Mat image, cv::Mat out)
{
	my_average(image, out, 1);
	return;
}

// ガウシアンフィルタ(未実装)
inline void my_gaussian(const cv::Mat image, cv::Mat out, const int size)
{
	int wsize = size * 2 + 1;
	cv::Mat filter(wsize, wsize, CV_32F);

	for (int y = 0; y < wsize; y++)
	{
		for (int x = 0; x < wsize; x++)
		{
			filter.at<float>(y, x) = 1.0f / (float)(size * 2 * wsize);
		}
	}

	my_filter(image, out, filter);

	return;
}

inline void my_gaussian(const cv::Mat image, cv::Mat out)
{
	my_gaussian(image, out, 1);
	return;
}

// プリューウィットフィルタ(横)
inline void my_prewitt_x(const cv::Mat image, cv::Mat out)
{
	cv::Mat filter = (cv::Mat_<float>(3, 3) << 
		-1.0f, 0.0f, 1.0f, 
		-1.0f, 0.0f, 1.0f, 
		-1.0f, 0.0f, 1.0f);

	my_filter(image, out, filter);

	return;
}

// プリューウィットフィルタ(縦)
inline void my_prewitt_y(const cv::Mat image, cv::Mat out)
{
	cv::Mat filter = (cv::Mat_<float>(3, 3) <<
		-1.0f, -1.0f, -1.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f);

	my_filter(image, out, filter);

	return;
}

// ソーベルフィルタ(横)
inline void my_sobel_x(const cv::Mat image, cv::Mat out)
{
	cv::Mat filter = (cv::Mat_<float>(3, 3) <<
		-1.0f, 0.0f, 1.0f,
		-2.0f, 0.0f, 2.0f,
		-1.0f, 0.0f, 1.0f);

	my_filter(image, out, filter);

	return;
}

// ソーベルフィルタ(縦)
inline void my_sobel_y(const cv::Mat image, cv::Mat out)
{
	cv::Mat filter = (cv::Mat_<float>(3, 3) <<
		-1.0f, -2.0f, -1.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 2.0f, 1.0f);

	my_filter(image, out, filter);

	return;
}
