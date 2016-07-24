#include "../include/imgproc.hpp"
using namespace cv;

int myCvtColor(const Mat &image, Mat &grayImage)
{
  int imageWidth = image.rows;
  int imageHeight = image.cols;
  int imageType = image.type();
  
  grayImage = Mat::zeros(imageWidth, imageHeight, CV_8UC1);

  for(int w = 0; w < imageWidth; w++){
    for(int h = 0; h < imageHeight; h++){
      uchar r = image.at<Vec3b>(w, h).val[0];
      uchar b = image.at<Vec3b>(w, h).val[1];
      uchar g = image.at<Vec3b>(w, h).val[2];

      double sum = r + b + g;

      grayImage.at<uchar>(w, h) = (uchar)(sum / 3.0);
    }
  }
}
