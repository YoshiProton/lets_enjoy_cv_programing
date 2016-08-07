#include "../include/Resizer.hpp"
using namespace cv;

namespace toyocv{
  class BilinearResizer : public Resizer{
    void resize(Mat src, Mat dst);
  };
}
