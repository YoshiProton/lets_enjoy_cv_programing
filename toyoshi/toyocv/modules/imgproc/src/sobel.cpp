#include "../include/imgproc.hpp"
#include "../include/sobelfilter.hpp"

using namespace cv;

namespace toyocv{
  void sobel(InputArray _src, OutputArray _dst,
	     const int &ddepth, const int &dx, const int &dy,
	     const Size &ksize, const Point &anchor, const int &borderType){
    SobelFilter sobelFilter(ddepth, dx, dy, ksize);
    sobelFilter.apply(_src, _dst, ddepth);
  }
}
