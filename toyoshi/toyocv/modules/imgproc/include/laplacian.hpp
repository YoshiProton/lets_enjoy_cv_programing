#ifndef __LAPLACIANFILTER_HPP__
#define __LAPLACIANFILTER_HPP__

#include "filter.hpp"

namespace toyocv{
  class LaplacianFilter: public FilterBase{
  public:
    LaplacianFilter(const int &ddepth,
		    const int &dx, const int &dy,
		    const cv::Size &ksize);
  };
}

#endif
