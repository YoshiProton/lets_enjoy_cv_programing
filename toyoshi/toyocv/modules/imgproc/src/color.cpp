#include "../include/imgproc.hpp"
using namespace cv;

namespace toyocv{
  void cvtColor(InputArray _src, OutputArray _dst)
  {
    int stype = _src.type();
    int dcn = 1;
    int depth = CV_MAT_DEPTH(stype);
    
    Mat src, dst;
    src = _src.getMat();

    Size sz = src.size();

    _dst.create(sz, CV_MAKETYPE(depth, dcn));
    dst = _dst.getMat();
    
    int imageWidth = src.rows;
    int imageHeight = src.cols;
  
    dst = Mat::zeros(imageWidth, imageHeight, CV_8UC1);

    for(int w = 0; w < imageWidth; w++){
      for(int h = 0; h < imageHeight; h++){
	uchar r = src.at<Vec3b>(w, h).val[0];
	uchar b = src.at<Vec3b>(w, h).val[1];
	uchar g = src.at<Vec3b>(w, h).val[2];

	double sum = r + b + g;

	dst.at<uchar>(w, h) = (uchar)(sum / 3.0);
      }
    }
  }
}
