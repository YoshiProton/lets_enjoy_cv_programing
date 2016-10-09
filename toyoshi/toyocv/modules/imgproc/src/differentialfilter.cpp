#include "../include/imgproc.hpp"
#include "../include/differentialfilter.hpp"

using namespace cv;

namespace toyocv{
  DifferentialFilter::DifferentialFilter(const int &ddepth,
					 const int &dx, const int &dy,
					 const cv::Size &ksize){
    try{
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
      setKernel(_kernel);
    }catch(...){
      std::cout << "dead in differential filter" << std::endl;
    }

  }
}
