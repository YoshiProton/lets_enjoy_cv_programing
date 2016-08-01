#include "../include/Resizer.hpp"
using namespace cv;

namespace toyocv{
  class NearestNeighborsResizer : public Resizer{
    void resize(Mat src, Mat dst);
  };
}
