#ifndef FILTER_H
#define FILTER_H

#include <opencv2\opencv.hpp>

#define HORIZONTAL 0
#define LONGITUDIAL 1

// averageFilter.cpp
cv::Mat averageFilter(const cv::Mat img, const int size);
float multSumMat(const cv::Mat kernel, const cv::Mat trg);
int getRestricted(const int in, const int min, const int max);
int convolute(const int x, const int y, const cv::Mat img, const cv::Mat kernel);

// diffFilter.cpp
cv::Mat diffFileter(const cv::Mat img, const int direction);
cv::Mat prewitt(const cv::Mat img, const int direction);
cv::Mat sobel(const cv::Mat img, const int direction);
cv::Mat difFilterCore(const cv::Mat img, const cv::Mat kernel);
cv::Mat laplacianFilter(const cv::Mat img);


cv::Mat unsharpmask(const cv::Mat img, const int k);
cv::Mat medianFilter(const cv::Mat img, const int ksize);
int getMedianVal(const int x, const int y, const cv::Mat img, const int ksize);

cv::Mat bilateralFilter(const cv::Mat img, const int ksize, const float sigma_xy, const float sigma_color);
float bilateralCore(const cv::Mat reg, const float sigma_xy, const float sigma_color);
cv::Vec3f bilateralCoreColor(cv::Mat reg, const float sigma_xy, const float sigma_color);
int colordist2(const cv::Vec3b color1, const cv::Vec3b color2);


cv::Mat nonlocalmean(const cv::Mat img);

//



#endif