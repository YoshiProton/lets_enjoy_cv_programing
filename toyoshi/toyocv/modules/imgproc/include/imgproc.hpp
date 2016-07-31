#include <opencv2/opencv.hpp>

#ifndef __IMGPROC__
#define __IMGPROC__

namespace toyocv{
  void cvtColor(cv::InputArray src, cv::OutputArray dst);
  void resize(cv::InputArray src, cv::OutputArray dst);
}
#endif
