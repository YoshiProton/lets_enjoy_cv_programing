#ifndef __TEXT_DETECTOR_HPP__
#define __TEXT_DETECTOR_HPP__

#include <opencv2/opencv.hpp>

class TextDetector{
public:
  cv::Mat detectText(const cv::Mat &image);
};

#endif
