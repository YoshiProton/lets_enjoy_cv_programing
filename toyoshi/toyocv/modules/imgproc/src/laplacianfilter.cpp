#include "../include/imgproc.hpp"
#include "../include/laplacianfilter.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace cv;

namespace toyocv{
  LaplacianFilter::LaplacianFilter(const int &ddepth,
				   const cv::Size &ksize,
				   const double &sigma){
    Mat _kernel = Mat::zeros(ksize, CV_64FC1);
    Point center(ksize.width / 2, ksize.height / 2);

    // create laplacian kernel
    for (int y = 0; y < ksize.width; ++y){
      Vec<double , 1> *ptr = _kernel.ptr<Vec<double, 1> >(y);
      for (int x = 0; x < ksize.height; ++x){
	ptr[x] = CalcLaplacianOperator(x - center.x, y - center.y, sigma);
      }
    }

    setKernel(_kernel);
  }

  double LaplacianFilter::CalcLaplacianOperator(const int &x,
						const int &y,
						const double &sigma){
    double upperLeft = pow(x, 2) + pow(y, 2) - 2 * pow(sigma, 2);
    double lowerLeft = 2 * M_PI * pow(sigma, 6);

    double upperRight = pow(x, 2) + pow(y, 2);

    double lowerRight = 2 * pow(sigma, 2);

    return upperLeft / lowerRight * exp(-1.0 * upperRight / lowerRight);
  }
}

