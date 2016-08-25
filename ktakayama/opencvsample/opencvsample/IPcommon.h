#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/opencv_lib.hpp>
#include <stdio.h>

using namespace cv;

#define myPI 3.14159265359f

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

// Combination
inline int my_combination(int x, int y) {

	if (y > x) return 0;
	if (y == 0 || y == x) return 1;

	float n = 1.0f;
	for (int i = 1; i <= y; i++) {
		n *= (float)(x - y + i) / (float)i;
		// printf("%dC%d = %f\n", x, y, n);
	}

	return (int)n;
}
