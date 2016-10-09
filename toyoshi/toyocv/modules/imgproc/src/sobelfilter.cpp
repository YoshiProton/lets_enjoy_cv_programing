#include "../include/imgproc.hpp"
#include "../include/sobelfilter.hpp"

using namespace cv;

namespace toyocv{
  SobelFilter::SobelFilter(const int &ddepth,
			   const int &dx, const int &dy,
			   const cv::Size &ksize){
    Mat _kernel = Mat::zeros(ksize, CV_64FC1);
    Point center(ksize.width / 2, ksize.height / 2);

    if(0 < dx){
      double *ptr = _kernel.ptr<double>(center.y);
      for (int i = 0; i < ksize.width / 2; ++i){
	ptr[i] = 1;
      }

      for (int i = ksize.width / 2 + 1; i < ksize.width; ++i){
	ptr[i] = -1;
      }
    }

    if(0 < dy){
      for (int i = 0; i < ksize.height / 2; ++i){
	double *ptr = _kernel.ptr<double>(i);
	ptr[center.x] = 1;
      }

      for (int i = ksize.height / 2 + 1; i < ksize.height; ++i){
	double *ptr = _kernel.ptr<double>(i);
	ptr[center.x] = -1;
      }
    }

    Mat _smoothKernel = Mat::zeros(ksize, CV_64FC1);

    if(0 < dx){
      for (int i = 0; i < ksize.height / 2; ++i){
	double *ptr = _smoothKernel.ptr<double>(i);
	ptr[center.x] = 1;
      }

      for (int i = ksize.height / 2 + 1; i < ksize.height; ++i){
	double *ptr = _smoothKernel.ptr<double>(i);
	ptr[center.x] = 1;
      }
      _smoothKernel.at<double>(center.y, center.x) = 2;
      _kernel = _smoothKernel * _kernel;      
    }

    if(0 < dy){
      double *ptr = _smoothKernel.ptr<double>(center.y);
      for (int i = 0; i < ksize.width / 2; ++i){
	ptr[i] = 1;
      }

      for (int i = ksize.width / 2 + 1; i < ksize.width; ++i){
	ptr[i] = 1;
      }
      _smoothKernel.at<double>(center.y, center.x) = 2;
      _kernel = _kernel * _smoothKernel;
    }
    
    setKernel(_kernel);
  }
}
