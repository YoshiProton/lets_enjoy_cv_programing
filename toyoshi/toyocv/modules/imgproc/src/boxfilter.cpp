#include "../include/boxfilter.hpp"

using namespace cv;

namespace toyocv{
  BoxFilter::BoxFilter(const cv::Size &ksize){
    Mat kernel = Mat::ones(ksize, CV_8UC1);
    setKernel(kernel);
  }
}
