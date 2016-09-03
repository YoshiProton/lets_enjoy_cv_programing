#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/opencv_lib.hpp>
#include <stdio.h>

#define myPI 3.14159265359f

class IPcommon
{
public:
	IPcommon();
	~IPcommon();

	// clampˆ—
	static float clamp(float x, float min, float max);
	// clampˆ—(cv::Vec3f)
	static cv::Vec3f clamp(cv::Vec3f x, float min, float max);

	// mirrorˆ—
	static int mirror(int x, int min, int max);

	// Combination
	static int combination(int x, int y);
};

