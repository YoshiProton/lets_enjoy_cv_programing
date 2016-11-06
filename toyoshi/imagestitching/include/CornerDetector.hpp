#ifndef __CORNER_DETECTOR_HPP__
#define __CORNER_DETECTOR_HPP__

#include <vector>
#include <opencv2/opencv.hpp>


class CornerDetector
{
public:
  std::vector<cv::KeyPoint> detectCorners(const cv::Mat &src);
};

#endif

