#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/opencv_lib.hpp>

using namespace cv;

// clampˆ—
inline float my_clamp(float x, float min, float max) {
	if (x < min) x = min;
	if (x > max) x = max;

	return x;
}

// clampˆ—(cv::Vec3f)
inline cv::Vec3f my_clamp(cv::Vec3f x, float min, float max) {
	for (int i = 0; i < 3; i++)
	{
		if (x(i) < min) x(i) = min;
		if (x(i) > max) x(i) = max;
	}

	return x;
}

// mirrorˆ—
inline int my_mirror(int x, int min, int max) {
	while (x < min || x >= max) {
		if (x < min) x = min + (min - x - 1);
		if (x >= max) x = max + (max - x - 1);
	}

	return x;
}
