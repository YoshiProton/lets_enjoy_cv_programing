#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <toyocv/imgproc.hpp>

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

  Mat grayImage;
  cvtColor(image, grayImage, CV_BGR2GRAY );

  Mat myGrayImage;
  toyocv::cvtColor(image, myGrayImage);

  Mat resizeImage;
  resize(image, resizeImage, Size(), 2.0, 2.0, INTER_NEAREST);
  Mat myResizeImage;
  toyocv::resize(image, myResizeImage);

  imshow("Orig Image", image);
  imshow("Gray Image", grayImage);
  imshow("My Gray Image", myGrayImage);
  imshow("Resized Image", resizeImage);
  imshow("My Resized Image", myResizeImage);
  
  waitKey(0);
  return 0;
}
