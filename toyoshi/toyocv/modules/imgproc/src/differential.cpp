#include "../include/imgproc.hpp"
#include "../include/differentialfilter.hpp"

using namespace cv;

namespace toyocv{
  void differential(InputArray _src, OutputArray _dst,
		    const int &ddepth, const int &dx, const int &dy,
		    const Size &ksize, const Point &anchor, const int &borderType){
    try{
      DifferentialFilter differentialFilter(ddepth, dx, dy, ksize);
      differentialFilter.apply(_src, _dst, ddepth);
    }catch(...){
      std::cout << "dead in differentialFilter constructor" << std::endl;
    }
  }
}
