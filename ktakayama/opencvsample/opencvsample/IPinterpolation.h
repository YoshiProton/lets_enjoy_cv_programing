#include "IPcommon.h"

#pragma once
class IPinterpolation
{
private:
	static void resize(const cv::Mat image, cv::Mat out, const double scale, const int wsize, double interFunction(double x));

public:
	IPinterpolation();
	~IPinterpolation();

	// �T�C�Y�ύX(Nearest Neighbor)
	static void resizeNN(const cv::Mat image, cv::Mat out, const double scale);
	// �T�C�Y�ύX(Bilinear)
	static void resizeBL(const cv::Mat image, cv::Mat out, const double scale);
	// �T�C�Y�ύX(Bicubic)
	static void resizeBC(const cv::Mat image, cv::Mat out, const double scale);
	// �T�C�Y�ύX(Lanczos4)
	static void resizeLZ(const cv::Mat image, cv::Mat out, const double scale);
};

