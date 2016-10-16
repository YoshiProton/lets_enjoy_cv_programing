#ifndef __LAPLACIANFILTER_HPP__
#define __LAPLACIANFILTER_HPP__

#include "filter.hpp"

namespace toyocv{
  class LaplacianFilter: public FilterBase{
  public:
    LaplacianFilter(const int &ddepth,
		    const cv::Size &ksize,
		    const double &sigma);

  private:
    double CalcLaplacianOperator(const int &x,
				 const int &y,
				 const double &sigma);
  };    
}

#endif
