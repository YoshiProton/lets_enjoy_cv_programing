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
  
  return 0;
}
