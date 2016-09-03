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

// ガウシアンフィルタ
inline void my_gaussian(const cv::Mat image, cv::Mat out, const float sigma, const int size)
{
	int wsize = size * 2 + 1;
	cv::Mat filter(wsize, wsize, CV_32F);

	for (int y = 0; y < wsize; y++)
	{
		for (int x = 0; x < wsize; x++)
		{
			filter.at<float>(y, x) =
				exp(- ((x - size) * (x - size) + (y - size) * (y - size)) / (2.0f * sigma * sigma))
				/ (2.0f * myPI * sigma * sigma);
		}
	}

	my_filter(image, out, filter);

	return;
}

inline void my_gaussian(const cv::Mat image, cv::Mat out, const float sigma)
{
	my_gaussian(image, out, sigma, 1);
	return;
}

inline void my_gaussian(const cv::Mat image, cv::Mat out)
{
	my_gaussian(image, out, 1.0f);
	return;
}

// ガウシアンフィルタ(パスカル)
inline void my_gaussian_pascal(const cv::Mat image, cv::Mat out, const int size)
{
	int wsize = size * 2 + 1;
	cv::Mat filter(wsize, wsize, CV_32F);

	for (int y = 0; y < wsize; y++)
	{
		for (int x = 0; x < wsize; x++)
		{
			filter.at<float>(y, x) = (float)my_combination(wsize - 1, x) * (float)my_combination(wsize - 1, y) / (float)pow(2, (wsize - 1) * 2);
		}
	}

	my_filter(image, out, filter);

	return;
}

inline void my_gaussian_pascal(const cv::Mat image, cv::Mat out)
{
	my_gaussian_pascal(image, out, 1);
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

// ラプラシアンフィルタ
inline void my_laplacian(const cv::Mat image, cv::Mat out)
{
	cv::Mat filter = (cv::Mat_<float>(3, 3) <<
		0.0f, 1.0f, 0.0f,
		1.0f, -4.0f, 1.0f,
		0.0f, 1.0f, 0.0f);

	my_filter(image, out, filter);

	return;
}

// 鮮鋭化フィルタ
inline void my_sharpening(const cv::Mat image, cv::Mat out, const float scale)
{
	float k = scale / 9.0f;

	cv::Mat filter = (cv::Mat_<float>(3, 3) <<
		-k, -k, -k,
		-k, 1.0f + k * 8.0f, -k,
		-k, -k, -k);

	my_filter(image, out, filter);

	return;
}

inline void my_sharpening(const cv::Mat image, cv::Mat out)
{
	my_sharpening(image, out, 1.0f);
	return;
}

// メディアンフィルタ
inline void my_median(const cv::Mat image, cv::Mat out, int size)
{
	int wsize = size * 2 + 1;

	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			cv::Vec3b c = cv::Vec3b(0, 0, 0);
			cv::Vec3b window[1000];
			for (int i = 0; i < wsize * wsize; i++)
			{
				window[i] = 0;
			}

			for (int dy = -size; dy <= size; dy++)
			{
				for (int dx = -size; dx <= size; dx++)
				{
					int mx = my_mirror(x + dx, 0, image.cols);
					int my = my_mirror(y + dy, 0, image.rows);

					cv::Vec3b vec = image.at<cv::Vec3b>(my, mx);

					int n = (dx + size) + (dy + size) * wsize;

					for (int i = 0; i < 3; i++)
					{
						for (int j = 0; j < n; j++)
						{
							if (vec(i) > window[j](i))
							{
								for (int k = wsize * wsize - 1; k >= j + 1; k--)
								{
									window[k](i) = window[k - 1](i);
								}
								window[j](i) = vec(i);
								break;
							}
						}
					}

					c = window[wsize * wsize / 2];
				}
			}

			out.at<cv::Vec3b>(y, x) = c;
		}
	}

	return;
}

inline void my_median(const cv::Mat image, cv::Mat out)
{
	my_median(image, out, 1);
	return;
}

// バイラテラルフィルタ
inline void my_bilateral(const cv::Mat image, cv::Mat out, const int size, const float sigma1, const float sigma2)
{
	int mx, my;
	cv::Vec3f c;

	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			c = cv::Vec3f(0.0f, 0.0f, 0.0f);

			cv::Vec3f f = (cv::Vec3f)image.at<cv::Vec3b>(y, x) / 255.0f;

			cv::Vec3f wn = Vec3f(0.0f, 0.0f, 0.0f); // 分子
			cv::Vec3f wd = Vec3f(0.0f, 0.0f, 0.0f); // 分母

			for (int dy = -size; dy <= size; dy++)
			{
				for (int dx = -size; dx <= size; dx++)
				{
					mx = my_mirror(x + dx, 0, image.cols);
					my = my_mirror(y + dy, 0, image.rows);

					cv::Vec3f fd = (cv::Vec3f)image.at<cv::Vec3b>(my, mx) / 255.0f;
					cv::Vec3f w;

					for (int i = 0; i < 3; i++)
					{
						w(i) = exp(- ((float)(dx * dx + dy * dy)) / (2.0f * sigma1 * sigma1))
							* exp(- powf((float)(f(i) - fd(i)), 2.0f) / (2.0f * sigma2 * sigma2));

						wn(i) += w(i) * fd(i);
						wd(i) += w(i);
					}
				}
			}

			for (int i = 0; i < 3; i++)
			{
				c(i) = wn(i) / wd(i);
			}

			c = my_clamp(c, 0.0f, 1.0f) * 255.0f;
			out.at<cv::Vec3b>(y, x) = (cv::Vec3b)c;
		}
	}

	return;
}

inline void my_bilateral(const cv::Mat image, cv::Mat out)
{
	my_bilateral(image, out, 1, 1.0f, 0.05f);

	return;
}

inline void my_bilateral(const cv::Mat image, cv::Mat out, const int size, const float sigma1, const float sigma2, const int loop)
{
	my_bilateral(image, out, size, sigma1, sigma2);
	for (int i = 0; i < loop - 1; i++)
	{
		my_bilateral(out, out, size, sigma1, sigma2);
	}

	return;
}


// ノンローカルミーンフィルタ
inline void my_nonlocalmean(const cv::Mat image, cv::Mat out, const int size1, const int size2, const float sigma)
{
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			cv::Vec3f c = cv::Vec3f(0.0f, 0.0f, 0.0f);
			cv::Vec3f f = (cv::Vec3f)image.at<cv::Vec3b>(y, x) / 255.0f;

			cv::Vec3f wn = Vec3f(0.0f, 0.0f, 0.0f); // 分子
			cv::Vec3f wd = Vec3f(0.0f, 0.0f, 0.0f); // 分母

			for (int dy = -size1; dy <= size1; dy++)
			{
				for (int dx = -size1; dx <= size1; dx++)
				{
					int mx = my_mirror(x + dx, 0, image.cols);
					int my = my_mirror(y + dy, 0, image.rows);

					cv::Vec3f fd = (cv::Vec3f)image.at<cv::Vec3b>(my, mx) / 255.0f;
					cv::Vec3f w;

					cv::Vec3f w_local = cv::Vec3f(0.0f, 0.0f, 0.0f);
					for (int dy2 = -size2; dy2 <= size2; dy2++)
					{
						for (int dx2 = -size2; dx2 <= size2; dx2++)
						{
							int mx2 = my_mirror(x + dx + dx2, 0, image.cols);
							int my2 = my_mirror(y + dy + dy2, 0, image.rows);

							cv::Vec3f fd2 = (cv::Vec3f)image.at<cv::Vec3b>(my2, mx2) / 255.0f;

							for (int i = 0; i < 3; i++)
							{
								w_local(i) += (float)((fd2(i) - fd(i)) * (fd2(i) - fd(i)));
							}
						}
					}

					for (int i = 0; i < 3; i++)
					{
						w(i) = exp(-w_local(i) / (2.0f * sigma * sigma));

						wn(i) += w(i) * fd(i);
						wd(i) += w(i);
					}
				}
			}

			for (int i = 0; i < 3; i++)
			{
				c(i) = wn(i) / wd(i);
			}

			c = my_clamp(c, 0.0f, 1.0f) * 255.0f;
			out.at<cv::Vec3b>(y, x) = (cv::Vec3b)c;
		}
	}

	return;
}

inline void my_nonlocalmean(const cv::Mat image, cv::Mat out)
{
	my_nonlocalmean(image, out, 1, 1, 0.05f);

	return;
}

inline void my_nonlocalmean(const cv::Mat image, cv::Mat out, const int size1, const int size2,  const float sigma, const int loop)
{
	my_nonlocalmean(image, out, size1, size2, sigma);
	for (int i = 0; i < loop - 1; i++)
	{
		my_nonlocalmean(out, out, size1, size2, sigma);
	}

	return;
}

