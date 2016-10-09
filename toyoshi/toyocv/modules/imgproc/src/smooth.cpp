#include "../include/imgproc.hpp"
#include "../include/boxfilter.hpp"

using namespace cv;

namespace toyocv{

  void blur(InputArray _src, OutputArray _dst,
	    const Size &ksize, const Point &anchor, const int &borderType){
    BoxFilter boxFilter(ksize);
    boxFilter.apply(_src, _dst, CV_64F);
  }
}
