#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <toyocv/imgproc.hpp>
#include <chrono>

using namespace std;
using namespace cv;

int main( int argc, char** argv )
{
  if( argc != 2)
    {
      cout <<" Usage: cv_shokyu ImageToLoadAndDisplay" << endl;
      return -1;
    }

  Mat image;
  image = imread(argv[1], CV_LOAD_IMAGE_COLOR);

  if(! image.data )
    {
      cout <<  "Could not open or find the image" << std::endl ;
      return -1;
    }

  Mat showImage;
  imshow("original", image);

  Mat blurImage;
  Size kernelSize(11, 11);
  blur(image, blurImage, kernelSize);
  imshow("blur", blurImage);

  Mat blurImageOrig;
  toyocv::blur(image, blurImageOrig, kernelSize);
  imshow("blurorig", blurImageOrig);

  imshow("diff", blurImage - blurImageOrig);
  
  waitKey(0);
  destroyAllWindows();

  Mat grayImage;
  cvtColor(image, grayImage, CV_RGB2GRAY);

  Size kernelSize2(3, 3);
  
  Mat differentialx;
  Mat differentialy;
  Mat differentialxy;
  // toyocv::differential(grayImage, differentialx, CV_16UC3, 1, 0, kernelSize2);
  // toyocv::differential(grayImage, differentialy, CV_16UC3, 0, 1, kernelSize2);
  // toyocv::differential(grayImage, differentialxy, CV_16UC3, 1, 1, kernelSize2);  

  toyocv::differential(grayImage, differentialx, CV_8UC1, 1, 0, kernelSize);
  toyocv::differential(grayImage, differentialy, CV_8UC1, 0, 1, kernelSize);
  toyocv::differential(grayImage, differentialxy, CV_8UC1, 1, 1, kernelSize);  
  
  imshow("diffx", differentialx);
  imshow("diffy", differentialy);
  imshow("diffxy", differentialxy);

  waitKey(0);
  
  return 0;
}
