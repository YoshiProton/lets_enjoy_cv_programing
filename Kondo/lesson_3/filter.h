#ifndef FILTER_H
#define FILTER_H

#include <opencv2\opencv.hpp>

#define HORIZONTAL 0
#define LONGITUDIAL 1

// averageFilter.cpp
cv::Mat averageFilter(cv::Mat img, int size);
float multSumMat(cv::Mat kernel, cv::Mat trg);

// diffFilter.cpp
cv::Mat diffFileter(cv::Mat img, int direction);
cv::Mat prewitt(cv::Mat img, int direction);
cv::Mat sobel(cv::Mat img, int direction);
cv::Mat difFilterCore(cv::Mat img, cv::Mat kernel);
cv::Mat laplacianFilter(cv::Mat img);


cv::Mat unsharpmask(cv::Mat img, int k);
cv::Mat medianFilter(cv::Mat img, int ksize);
int getMedianVal(cv::Mat reg, int center);

cv::Mat bilateralFilter(cv::Mat img, int sigma_x, int sigma_color);
cv::Mat nonlocalmean(cv::Mat img);

//



#endif