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

  Mat grayImage;
  auto start = std::chrono::system_clock::now();
  cvtColor(image, grayImage, CV_BGR2GRAY );
  auto end1 = std::chrono::system_clock::now();
  auto usec = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start).count();
  std::cout << "opencv cvtColor " << usec << " nano sec \n";

  Mat myGrayImage;
  toyocv::cvtColor(image, myGrayImage);
  auto end2 = std::chrono::system_clock::now();
  usec = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - end1).count();
  std::cout << "my cvtColor " << usec << " nano sec \n";

  Mat resizeImage;
  resize(image, resizeImage, Size(), 2.0, 2.0, INTER_NEAREST);
  auto end3 = std::chrono::system_clock::now();
  usec = std::chrono::duration_cast<std::chrono::nanoseconds>(end3 - end2).count();
  std::cout << "opencv resize " << usec << " nano sec \n";

  Mat myResizeImageNearestNeighbors;
  toyocv::resize(image, myResizeImageNearestNeighbors, toyocv::NearestNeighbors);
  auto end4 = std::chrono::system_clock::now();
  usec = std::chrono::duration_cast<std::chrono::nanoseconds>(end4 - end3).count();
  std::cout << "my resize nearest neighbor " << usec << " nano sec \n";
  
  Mat myResizeImage;
  toyocv::resize(image, myResizeImage, toyocv::Bilinear);
  auto end5 = std::chrono::system_clock::now();
  usec = std::chrono::duration_cast<std::chrono::nanoseconds>(end5 - end4).count();
  std::cout << "my resize bilinear interpolation " << usec << " nano sec \n";

  Mat myResizeImage2;
  toyocv::resize(image, myResizeImage2, toyocv::NearestNeighborsPointer);
  auto end6 = std::chrono::system_clock::now();
  usec = std::chrono::duration_cast<std::chrono::nanoseconds>(end6 - end5).count();
  std::cout << "my resize nearest neighbor pointer " << usec << " nano sec \n";
  
  imshow("Orig Image", image);
  imshow("Gray Image", grayImage);
  imshow("My Gray Image", myGrayImage);
  imshow("Resized Image", resizeImage);
  imshow("My Resized Image", myResizeImage);
  
  waitKey(0);
  return 0;
}
