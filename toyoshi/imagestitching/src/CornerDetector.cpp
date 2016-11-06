#include "CornerDetector.hpp"

#include <random>
#include <cstdint>
#include <algorithm>
#include <stdexcept>
#include <unordered_set>
#include <functional>
#include <limits>
#include <type_traits>

using namespace std;
using namespace cv;

vector<KeyPoint> CornerDetector::detectCorners(const Mat &src){
  Mat src_gray, dst, dst_norm;
  dst = Mat::zeros( src.size(), CV_32FC1 );

  cvtColor( src, src_gray, CV_BGR2GRAY );

  const int blockSize = 3;
  const int apertureSize = 3;
  // const double k = 0.04;
  const double k = 0.1;
  const int thresh = 150;

  cornerHarris( src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT );

  normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );

  vector<KeyPoint> corners(0);  
  for( int j = 0; j < dst_norm.rows ; j++ ){
    for( int i = 0; i < dst_norm.cols; i++ ){
      if( (int) dst_norm.at<float>(j,i) > thresh ){
	corners.push_back(KeyPoint(Point(i, j), 1.0));

      }
    }
  }
  return corners;
}

