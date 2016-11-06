#include "../include/imgproc.hpp"
#include "../include/bilateralfilter.hpp"

using namespace cv;

namespace toyocv{
  void bilateral(InputArray _src, OutputArray _dst,
		 const int &ddepth, const int &dx, const int &dy,
		 const Size &ksize, const Point &anchor, const int &borderType){
    BilateralFilter birateralFilter(ddepth, dx, dy, ksize);
    BilateralFilter.apply(_src, _dst, ddepth);
  }
}
