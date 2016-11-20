#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <toyocv/imgproc.hpp>
#include <chrono>

#include <TextDetector.hpp>

using namespace std;
using namespace cv;


int main( int argc, char** argv )
{
  Mat image;
  image = imread(argv[1], CV_LOAD_IMAGE_COLOR);

  if(!image.data){
    cout <<  "Could not open or find the image" << std::endl ;
    return -1;
  }

  TextDetector textDetector;

  Mat result = textDetector.detectText(image);

  // show result
  cv::imshow("image", image);
  cv::waitKey(0);

  return 0;
}
