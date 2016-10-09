#include "../include/imgproc.hpp"
#include "../include/laplacianfilter.hpp"

using namespace cv;

namespace toyocv{
  void laplacian(InputArray _src, OutputArray _dst,
		 const int &ddepth,
		 const Size &ksize, const double &sigma,
		 const Point &anchor, const int &borderType){
    LaplacianFilter laplacianFilter(ddepth, ksize, sigma);
    laplacianFilter.apply(_src, _dst, ddepth);
  }
}
