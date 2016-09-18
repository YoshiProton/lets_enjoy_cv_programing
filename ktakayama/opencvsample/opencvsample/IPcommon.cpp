#include "stdafx.h"
#include "IPcommon.h"


IPcommon::IPcommon()
{
}


IPcommon::~IPcommon()
{
}

// clampèàóù
float IPcommon::clamp(float x, float min, float max) {
	if (x < min) x = min;
	if (x > max) x = max;

	return x;
}

double IPcommon::clamp(double x, double min, double max) {
	if (x < min) x = min;
	if (x > max) x = max;

	return x;
}

// clampèàóù(cv::Vec3f)
cv::Vec3f IPcommon::clamp(cv::Vec3f x, float min, float max) {
	for (int i = 0; i < 3; i++)
	{
		clamp(x(i), min, max);
	}

	return x;
}

cv::Vec3d IPcommon::clamp(cv::Vec3d x, double min, double max) {
	for (int i = 0; i < 3; i++)
	{
		clamp(x(i), min, max);
	}

	return x;
}

// mirrorèàóù
int IPcommon::mirror(int x, int min, int max) {
	while (x < min || x >= max) {
		if (x < min) x = min + (min - x - 1);
		if (x >= max) x = max + (max - x - 1);
	}

	return x;
}

// Combination
int IPcommon::combination(int x, int y) {

	if (y > x) return 0;
	if (y == 0 || y == x) return 1;

	float n = 1.0f;
	for (int i = 1; i <= y; i++) {
		n *= (float)(x - y + i) / (float)i;
		// printf("%dC%d = %f\n", x, y, n);
	}

	return (int)n;
}
