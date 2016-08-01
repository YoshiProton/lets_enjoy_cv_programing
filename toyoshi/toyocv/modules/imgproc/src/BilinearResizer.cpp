#include "../include/BilinearResizer.hpp"
using namespace cv;

namespace toyocv{
  void BilinearResizer::resize(Mat src, Mat dst){
    double scale = 2.0;
      
    int imageWidth = src.rows * scale;
    int imageHeight = src.cols * scale;

    for(int w = 1; w < imageWidth - 1; w++){
      for(int h = 1; h < imageHeight - 1; h++){
	int nearx1 = w / scale;
	int neary2 = h / scale;

	if (nearx1 * 2 == w || neary2 * 2 == h){
	  dst.at<Vec3b>(w, h) = src.at<Vec3b>(nearx1, neary2);
	  continue;
	}

	int nearx2 = nearx1 + 1;
	int neary1 = neary2 + 1;

	Vec3b q12 = src.at<Vec3b>(nearx1, neary2);
	Vec3b q22 = src.at<Vec3b>(nearx2, neary2);
	Vec3b q11 = src.at<Vec3b>(nearx1, neary1);
	Vec3b q21 = src.at<Vec3b>(nearx2, neary1);

	Vec3b fxy1 = (nearx2 * 2 - w) / ((nearx2 - nearx1) * 2.0) * q11
	  + (nearx2 * 2 - w) / ((nearx2 - nearx1) * 2.0) * q21;
	Vec3b fxy2 = (nearx2 * 2 - w) / ((nearx2 - nearx1) * 2.0) * q12
	  + (nearx2 * 2 - w) / ((nearx2 - nearx1) * 2.0) * q22;
	Vec3b fxy = (neary2 * 2 - h) / ((neary2 - neary1) * 2.0) * q12
	  + (neary2 * 2 - h) / ((neary2 - neary1) * 2.0) * q22;

	dst.at<Vec3b>(w, h) = fxy;
      }
    }
  }
}
