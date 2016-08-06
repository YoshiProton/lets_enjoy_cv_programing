#include "../include/NearestNeighborsResizer.hpp"
using namespace cv;

namespace toyocv{
  void NearestNeighborsResizer::resize(Mat src, Mat dst){
    int imageWidth = src.rows;
    int imageHeight = src.cols;
  
    for(int w = 0; w < imageWidth; w++){
      for(int h = 0; h < imageHeight; h++){
	Vec3b p = src.at<Vec3b>(w, h);

	if (w != 0 && h != 0){
	  dst.at<Vec3b>(w * 2 - 1, h * 2 - 1) = p;
	}

	if (w != 0){
	  dst.at<Vec3b>(w * 2 - 1, h * 2) = p;
	}

	if (h != 0){
	  dst.at<Vec3b>(w * 2, h * 2 - 1) = p;
	}

	dst.at<Vec3b>(w * 2, h * 2) = p;
      }
    }
  }
  
  void NearestNeighborsResizerPointer::resize(Mat src, Mat dst){
    int imageWidth = src.rows;
    int imageHeight = src.cols;
  
    for(int w = 0; w < imageWidth; w++){
      cv::Vec3b *srcPointer1 = src.ptr<cv::Vec3b>(w * 2 - 1);
      cv::Vec3b *srcPointer2 = src.ptr<cv::Vec3b>(w * 2);

      for(int h = 0; h < imageHeight; h++){
	Vec3b p = src.at<Vec3b>(w, h);

	if (w != 0 && h != 0){
	  // dst.at<Vec3b>(w * 2 - 1, h * 2 - 1) = p;
	  srcPointer1[h * 2 - 1] = p;
	}

	if (w != 0){
	  // dst.at<Vec3b>(w * 2 - 1, h * 2) = p;
	  srcPointer1[h * 2] = p;
	}

	if (h != 0){
	  // dst.at<Vec3b>(w * 2, h * 2 - 1) = p;
	  srcPointer2[h * 2 - 1] = p;	  
	}

	// dst.at<Vec3b>(w * 2, h * 2) = p;
	srcPointer2[h * 2] = p;
      }
    }
  }
}

