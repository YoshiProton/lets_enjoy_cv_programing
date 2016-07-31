#include "../include/imgproc.hpp"
using namespace cv;

namespace toyocv{
  void resize(InputArray _src, OutputArray _dst)
  {
    int stype = _src.type();
    int dcn = 3;
    int depth = CV_MAT_DEPTH(stype);
    
    Mat src, dst;
    src = _src.getMat();

    Size sz = src.size() * 2;

    _dst.create(sz, CV_MAKETYPE(depth, dcn));
    dst = _dst.getMat();
    
    int imageWidth = src.rows;
    int imageHeight = src.cols;
  
    dst = _dst.getMat();

    for(int w = 0; w < imageWidth; w++){
      for(int h = 0; h < imageHeight; h++){
	uchar r = src.at<Vec3b>(w, h).val[0];
	uchar b = src.at<Vec3b>(w, h).val[1];
	uchar g = src.at<Vec3b>(w, h).val[2];

	if (w != 0 && h != 0){
	  dst.at<Vec3b>(w * 2 - 1, h * 2 - 1).val[0] = r;
	  dst.at<Vec3b>(w * 2 - 1, h * 2 - 1).val[1] = b;
	  dst.at<Vec3b>(w * 2 - 1, h * 2 - 1).val[2] = g;
	}

	if (w != 0){
	  dst.at<Vec3b>(w * 2 - 1, h * 2).val[0] = r;
	  dst.at<Vec3b>(w * 2 - 1, h * 2).val[1] = b;
	  dst.at<Vec3b>(w * 2 - 1, h * 2).val[2] = g;
	}

	if (h != 0){
	  dst.at<Vec3b>(w * 2, h * 2 - 1).val[0] = r;
	  dst.at<Vec3b>(w * 2, h * 2 - 1).val[1] = b;
	  dst.at<Vec3b>(w * 2, h * 2 - 1).val[2] = g;
	}

	dst.at<Vec3b>(w * 2, h * 2).val[0] = r;
	dst.at<Vec3b>(w * 2, h * 2).val[1] = b;
	dst.at<Vec3b>(w * 2, h * 2).val[2] = g;
      }
    }
  }
}
