#ifndef __BOXFILTER_HPP__
#define __BOXFILTER_HPP__

#include "filter.hpp"

namespace toyocv{
  class BoxFilter: public FilterBase{
  public:
    BoxFilter(const cv::Size &ksize);
  };
}

#endif
