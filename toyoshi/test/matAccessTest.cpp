#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
  Size ksize(3, 3);
  int depth = CV_64F;
  
  Mat _kernel = Mat::zeros(ksize, CV_MAKETYPE(depth, 1));
  Point center(ksize.width / 2, ksize.height / 2);

  std::cout << _kernel << std::endl;

  _kernel.data[0 * _kernel.step + 1 * _kernel.elemSize()] =  1;

  double *src = _kernel.ptr<double>(2);
  src[1] = -1;

  std::cout << _kernel << std::endl;
  
}
