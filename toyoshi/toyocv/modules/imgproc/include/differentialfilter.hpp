#ifndef __DIFFERENTIALFILTER_HPP__
#define __DIFFERENTIALFILTER_HPP__

#include "filter.hpp"

namespace toyocv{
  class DifferentialFilter: public FilterBase{
  public:
    DifferentialFilter(const int &ddepth,
		       const int &dx, const int &dy,
		       const cv::Size &ksize);
  };
}

#endif
