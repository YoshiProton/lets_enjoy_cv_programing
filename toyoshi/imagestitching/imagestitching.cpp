#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <toyocv/imgproc.hpp>
#include <chrono>

#include <random>
#include <cstdint>
#include <algorithm>
#include <stdexcept>
#include <unordered_set>
#include <functional>
#include <limits>
#include <type_traits>

#include <limits>

#include "ImageStitcher.hpp"

using namespace std;
using namespace cv;

const uint imageCount = 2;
const uint ransacTrial = 1000;


void drawAndShowImage(const Mat &image, const vector<KeyPoint> &corners){
  Mat tmpImage;
  image.copyTo(tmpImage);
  for(uint i = 0; i < corners.size(); ++i)
    circle(tmpImage, corners[i].pt, 5,  Scalar(0, 255, 0), -1, 8, 0 );    

  imshow("corner detection", tmpImage);
  waitKey(0);
  destroyAllWindows();
}

void drawSiftMatch(const Mat *images,
		   const vector<KeyPoint> *corners,
		   const std::vector<cv::DMatch> &dmatch){
  cv::Mat result;
  cv::drawMatches(images[0], corners[0], images[1], corners[1], dmatch, result);
  cv::imshow("matching", result);
  waitKey(0);
  destroyAllWindows();
}

int main( int argc, char** argv )
{
  if( argc != imageCount + 1)
    {
      cout <<" Usage: cv_shokyu image1 image2" << endl;
      return -1;
    }

  Mat images[imageCount];
  for(uint i = 0; i < imageCount; ++i)
    images[i] = imread(argv[i+1], CV_LOAD_IMAGE_COLOR);

  if(!images[0].data || !images[imageCount].data){
    cout <<  "Could not open or find the image" << std::endl ;
    return -1;
  }

  ImageStitcher imageStitcher;

  Mat transformedImage = imageStitcher.stitch(images);
  
  // show result
  cv::imshow("image", transformedImage);
  cv::waitKey(0);

  return 0;
}
