#ifndef __TEXT_DETECTOR_HPP__
#define __TEXT_DETECTOR_HPP__

#include <opencv2/opencv.hpp>

class TextDetector{
public:
  cv::Mat detectText(const cv::Mat &image);
  cv::Mat mser(const cv::Mat &image);
  
private:
  int threshold_type = 0;
  int const max_value = 255;
  int const max_type = 4;
  int const max_BINARY_value = 255;

  int thresh = 100;
  int max_thresh = 255;
};

#endif
