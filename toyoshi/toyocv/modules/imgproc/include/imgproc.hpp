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
  void differential(cv::InputArray _src, cv::OutputArray _dst,
		    const int &ddepth, const int &dx, const int &dy,
		    const cv::Size &ksize, const cv::Point &anchor = cv::Point(-1,-1),
		    const int &borderType = cv::BORDER_DEFAULT);
  void sobel(cv::InputArray _src, cv::OutputArray _dst,
	     const int &ddepth, const int &dx, const int &dy,
	     const cv::Size &ksize, const cv::Point &anchor = cv::Point(-1,-1),
	     const int &borderType = cv::BORDER_DEFAULT);
  void laplacian(cv::InputArray _src, cv::OutputArray _dst,
		 const int &ddepth,
		 const cv::Size &ksize, const double &sigma,
		 const cv::Point &anchor  = cv::Point(-1,-1),
		 const int &borderType = cv::BORDER_DEFAULT);
  void bilateral(cv::InputArray _src, cv::OutputArray _dst,
		 const int &ddepth, const int &dx, const int &dy,
		 const cv::Size &ksize, const cv::Point &anchor, const int &borderType);
}
#endif
