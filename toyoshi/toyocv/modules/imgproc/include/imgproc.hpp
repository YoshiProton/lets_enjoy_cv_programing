#include <opencv2/opencv.hpp>

#ifndef __IMGPROC__
#define __IMGPROC__

namespace toyocv{
  enum ResizeMethod{
    NearestNeighbors,
    Bilinear
  };
  
  void cvtColor(cv::InputArray src, cv::OutputArray dst);
  void resize(cv::InputArray src, cv::OutputArray dst, ResizeMethod method = NearestNeighbors);
}
#endif
