#pragma once
#define _USE_MATH_DEFINES
#include <opencv2/opencv.hpp>
#include <opencv2/opencv_lib.hpp>
#include <stdio.h>
#include <math.h>

class IPcommon
{
public:
	IPcommon();
	~IPcommon();

	// clampˆ—
	static float clamp(float x, float min, float max);
	static double clamp(double x, double min, double max);
	static cv::Vec3f clamp(cv::Vec3f x, float min, float max);
	static cv::Vec3d clamp(cv::Vec3d x, double min, double max);

	// mirrorˆ—
	static int mirror(int x, int min, int max);

	// Combination
	static int combination(int x, int y);
};

