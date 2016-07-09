#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main( int argc, char** argv )
{
  if( argc != 2)
    {
      cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
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

  Mat resizeImage;
  resize(image, resizeImage, Size(), 2.0, 2.0, INTER_NEAREST);

  imshow("Orig Image", image);
  imshow("Gray Image", grayImage);
  imshow("Resized Image", resizeImage);

  waitKey(0);
  return 0;
}
