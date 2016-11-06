#ifndef __BIRATERALFILTER_HPP__
#define __BIRATERALFILTER_HPP__

#include "filter.hpp"

namespace toyocv{
  class BilateralFilter: public FilterBase{
  public:
    BilateralFilter(const int &ddepth,
		    const int &dx, const int &dy,
		    const cv::Size &ksize);
  };
}

#endif
