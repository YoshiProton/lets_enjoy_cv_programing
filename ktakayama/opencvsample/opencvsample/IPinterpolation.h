#include "IPcommon.h"

#pragma once
class IPinterpolation
{
private:
	static void resize(const cv::Mat image, cv::Mat out, const double scale, const int wsize, double interFunction(double x));

public:
	IPinterpolation();
	~IPinterpolation();

	// サイズ変更(Nearest Neighbor)
	static void resizeNN(const cv::Mat image, cv::Mat out, const double scale);
	// サイズ変更(Bilinear)
	static void resizeBL(const cv::Mat image, cv::Mat out, const double scale);
	// サイズ変更(Bicubic)
	static void resizeBC(const cv::Mat image, cv::Mat out, const double scale);
	// サイズ変更(Lanczos4)
	static void resizeLZ(const cv::Mat image, cv::Mat out, const double scale);
};

