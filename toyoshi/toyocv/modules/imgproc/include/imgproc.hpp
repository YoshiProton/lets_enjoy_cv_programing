#include <opencv2/opencv.hpp>

#ifndef __IMGPROC__
#define __IMGPROC__

namespace toyocv{
  enum ResizeMethod{
    NearestNeighbors,
    NearestNeighborsPointer,
    Bilinear
  };
  
  void cvtColor(cv::InputArray src, cv::OutputArray dst);
  void resize(cv::InputArray src, cv::OutputArray dst, ResizeMethod method = NearestNeighbors);
  void blur(cv::InputArray src, cv::OutputArray dst,
	    const cv::Size &ksize, const cv::Point &anchor = cv::Point(-1,-1),
	    const int &borderType = cv::BORDER_DEFAULT);
}
#endif
