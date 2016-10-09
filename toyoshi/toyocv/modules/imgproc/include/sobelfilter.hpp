#ifndef __SOBELFILTER_HPP__
#define __SOBELFILTER_HPP__

#include "filter.hpp"

namespace toyocv{
  class SobelFilter: public FilterBase{
  public:
    SobelFilter(const int &ddepth,
		const int &dx, const int &dy,
		const cv::Size &ksize);
  };
}

#endif
