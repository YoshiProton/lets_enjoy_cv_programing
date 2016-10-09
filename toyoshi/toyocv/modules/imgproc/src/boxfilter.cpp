#include "../include/boxfilter.hpp"

using namespace cv;

namespace toyocv{
  BoxFilter::BoxFilter(const cv::Size &ksize){
    Mat _kernel = Mat::ones(ksize, CV_64FC1);

    setKernel(_kernel);
  }
}
