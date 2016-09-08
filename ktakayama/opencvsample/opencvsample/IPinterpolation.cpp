#include "stdafx.h"
#include "IPinterpolation.h"


IPinterpolation::IPinterpolation()
{
}


IPinterpolation::~IPinterpolation()
{
}

double NearestNeighbor(double x) {
	if (x <= 0.5) return 1.0;

	return 0.0;
}

double BiLinear(double x) {
	if (x < 1.0) return 1.0 - x;

	return 0.0;
}

double BiCubic(double x) {
	if (x < 1.0) {
		return 1.5 * x * x * x - 2.5 * x * x + 1.0;
	}
	else if (x < 2.0) {
		return -0.5 * x * x * x + 2.5 * x * x - 4.0 * x + 2.0;
	}

	return 0.0;
}

double Lanczos(double x, double len) {
	if (x == 0.0) {
		return 1.0;
	}
	else if (x < len) {
		return (double)(sin(M_PI * x) / (M_PI * x) * sin(M_PI * x / len) / (M_PI * x / len));
	}

	return 0.0f;
}

double Lanczos3(double x) {
	return Lanczos(x, 3.0);
}

double Lanczos4(double x) {
	return Lanczos(x, 4.0);
}

double BiCubic1(double x) {
	if (x < 1.0) return 2.0 * x * x * x - 3.0 * x * x + 1.0;

	return 0.0;
}

double BiCubic3(double x) {
	if (x < 1.0) {
		return 4.0 / 3.0 * x * x * x - 7.0 / 3.0 * x * x + 1.0;
	}
	else if (x < 2.0) {
		return -7.0 / 12.0 * x * x * x + 3.0 * x * x - 59.0 / 12.0 * x + 5.0 / 2.0;
	}
	else if (x < 3.0) {
		return 1.0 / 12.0 * x * x * x - 2.0 / 3.0 * x * x + 7.0 / 4.0 * x - 3.0 / 2.0;
	}

	return 0.0f;
}

void IPinterpolation::resize(const cv::Mat image, cv::Mat out, const double scale, const int wsize, double interFunction(double x))
{
	for (int y = 0; y < (int)floor(image.rows * scale); y++)
	{
		double y0 = ((double)y + 0.5) / scale - 0.5;
		for (int x = 0; x < (int)floor(image.cols * scale); x++)
		{
			double x0 = ((double)x + 0.5) / scale - 0.5;

			cv::Vec3d c = cv::Vec3d(0.0, 0.0, 0.0);

			for (int dy = 1 - wsize; dy <= wsize; dy++)
			{
				int y0d = (int)(floor(y0) + dy);
				int my = IPcommon::mirror(y0d, 0, image.rows);
				for (int dx = 1 - wsize; dx <= wsize; dx++)
				{
					int x0d = (int)(floor(x0) + dx);
					int mx = IPcommon::mirror(x0d, 0, image.cols);

					cv::Vec3d cd = (cv::Vec3d)image.at<cv::Vec3b>(my, mx);

					c += cd * interFunction(abs(x0 - x0d)) * interFunction(abs(y0 - y0d));

					//if(x == 0 && y == 0)
					//	printf("xy(%d, %d), dxy(%d, %d), xy0(%.3f, %.3f), xy0d(%d, %d), dis(%.3f, %.3f)\n", x, y, dx, dy, x0, y0, x0d, y0d, abs(x0 - x0d), abs(y0 - y0d));
				}
			}

			out.at<cv::Vec3b>(y, x) = (cv::Vec3b)IPcommon::clamp(c, 0.0, 255.0);
		}
	}

	return;
}

// サイズ変更(Nearest Neighbor) OpenCVと多少ずれあり
void IPinterpolation::resizeNN(const cv::Mat image, cv::Mat out, const double scale)
{
	for (int y = 0; y < (int)floor(image.rows * scale); y++)
	{
		double y0 = ((double)y) / scale + 0.5;
		int my = IPcommon::mirror((int)floor(y0), 0, image.rows);
		for (int x = 0; x < (int)floor(image.cols * scale); x++)
		{
			double x0 = ((double)x) / scale + 0.5;
			int mx = IPcommon::mirror((int)floor(x0), 0, image.cols);

			cv::Vec3b vec = image.at<cv::Vec3b>(my, mx);

			out.at<cv::Vec3b>(y, x) = vec;
		}
	}

	// resize(image, out, scale, 1, NearestNeighbor);
	return;
}

// サイズ変更(Bilinear)
void IPinterpolation::resizeBL(const cv::Mat image, cv::Mat out, const double scale)
{
	resize(image, out, scale, 1, BiLinear);
	return;
}

// サイズ変更(Bicubic)
void IPinterpolation::resizeBC(const cv::Mat image, cv::Mat out, const double scale)
{
	resize(image, out, scale, 2, BiCubic);
	return;
}

// サイズ変更(Lanczos)
void IPinterpolation::resizeLZ(const cv::Mat image, cv::Mat out, const double scale)
{
	resize(image, out, scale, 4, Lanczos4);
	return;
}
