#include "../include/imgproc.hpp"
#include "../include/Resizer.hpp"
#include "../include/NearestNeighborsResizer.hpp"
#include "../include/BilinearResizer.hpp"
using namespace cv;

namespace toyocv{
  void resize(InputArray _src, OutputArray _dst,
	      ResizeMethod method)
  {
    int stype = _src.type();
    int dcn = 3;
    int depth = CV_MAT_DEPTH(stype);
    
    Mat src, dst;
    src = _src.getMat();

    Size sz = src.size() * 2;

    _dst.create(sz, CV_MAKETYPE(depth, dcn));
    dst = _dst.getMat();

    Resizer *resizer;
    switch(method){
    case NearestNeighbors:
      resizer = new NearestNeighborsResizer();
      break;
    case NearestNeighborsPointer:
      resizer = new NearestNeighborsResizer();
      break;
    case Bilinear:
      resizer = new BilinearResizer();
      break;
    default:
      break;
    }
    resizer->resize(src, dst);
    delete resizer;
  }
}
