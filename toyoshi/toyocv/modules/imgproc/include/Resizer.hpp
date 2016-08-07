#include "../include/imgproc.hpp"
using namespace cv;

#ifndef __RESIZER__
#define __RESIZER__

namespace toyocv{
  class Resizer{
  public:
    virtual void resize(Mat src, Mat dst) = 0;
  };
}

#endif
