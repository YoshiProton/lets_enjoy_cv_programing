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

#include "CornerDetector.hpp"

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

Mat descriptFeatures(const Mat &image, vector<KeyPoint> &corners){
  initModule_nonfree(); 
  Ptr<DescriptorExtractor> extractor = cv::DescriptorExtractor::create("SIFT");
  Mat descriptor;
  extractor->compute(image, corners, descriptor);

  return descriptor;
}

std::vector<cv::DMatch> calcSiftMatch(const Mat *descriptors){
  cv::Ptr<DescriptorMatcher> matcher = cv::DescriptorMatcher::create("FlannBased");
  std::vector<cv::DMatch> dmatch;
  
  matcher->match(descriptors[0], descriptors[1], dmatch);

  return dmatch;
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

Mat createEquationA(std::vector<cv::DMatch> dmatch, const vector<KeyPoint> *corners){
  uint matchCount = dmatch.size();
  Mat A = Mat::zeros(Size(8, matchCount * 2), CV_32FC1);
  for (uint i = 0; i < matchCount; ++i){
    
    Point2f p1 = corners[0][dmatch[i].queryIdx].pt;
    Point2f p2 = corners[1][dmatch[i].trainIdx].pt;

    float *equation1 = A.ptr<float>(i * 2);
    float *equation2 = A.ptr<float>(i * 2 + 1);

    equation1[0] = p1.x;
    equation1[1] = p1.y;
    equation1[2] = 1;
    equation1[6] = -1 * p1.x * p2.x;
    equation1[7] = -1 * p2.x * p1.y;

    equation2[3] = p1.x;
    equation2[4] = p1.y;
    equation2[5] = 1;
    equation2[6] = -1 * p1.x * p2.y;
    equation2[7] = -1 * p1.y * p2.y;
  }

  return A;
}

Mat createEquationb(std::vector<cv::DMatch> dmatch, const vector<KeyPoint> *corners){
  uint matchCount = dmatch.size();
  Mat bt = Mat::zeros(Size(matchCount * 2, 1), CV_32FC1);

  float *equation = bt.ptr<float>(0);
  
  for (uint i = 0; i < matchCount; ++i){
    Point2f p2 = corners[1][dmatch[i].trainIdx].pt;

    equation[i * 2] = p2.x;
    equation[i * 2 + 1] = p2.y;
  }

  return bt.t();
}


std::mt19937 create_rand_engine(){
  std::random_device rnd;
  std::vector<std::uint_least32_t> v(10);// 初期化用ベクタ
  std::generate(v.begin(), v.end(), std::ref(rnd));// ベクタの初期化
  std::seed_seq seed(v.begin(), v.end());
  return std::mt19937(seed);// 乱数エンジン
}

std::vector<int> make_rand_array_unique(const int size, int rand_min, int rand_max){
  if(rand_min > rand_max) std::swap(rand_min, rand_max);
  const int max_min_diff = static_cast<int>(rand_max - rand_min + 1);
  if(max_min_diff < size) throw std::runtime_error("引数が異常です");

  std::vector<int> tmp;
  auto engine = create_rand_engine();
  std::uniform_int_distribution<int> distribution(rand_min, rand_max);

  const int make_size = static_cast<int>(size*1.2);

  while(tmp.size() < size){
    while(tmp.size() < make_size) tmp.push_back(distribution(engine));
    std::sort(tmp.begin(), tmp.end());
    auto unique_end = std::unique(tmp.begin(), tmp.end());

    if(size < std::distance(tmp.begin(), unique_end)){
      unique_end = std::next(tmp.begin(), size);
    }
    tmp.erase(unique_end, tmp.end());
  }

  std::shuffle(tmp.begin(), tmp.end(), engine);
  return std::move(tmp);
}

Mat solveEquation(const Mat &A, const Mat &b){
  Mat tmp1 = A.t() * A;

  Mat tmp2 = tmp1.inv(cv::DECOMP_SVD);

  Mat h = tmp2 * A.t() * b;

  Mat mat33 = Mat::ones(1, 1, CV_32FC1);
  h.push_back(mat33);

  return h.reshape(1, 3);
}

Mat selectRows(const Mat &src, const vector<int> &rand_array){
  Mat dst = src.row(rand_array[0]);

  for(uint i = 1; i < rand_array.size(); ++i){
    dst.push_back(src.row(rand_array[i]));
  }

  return dst;
}

template <typename T> vector<T> selectVector(const vector<T> &src, const vector<int> &index){
  vector<T> dst;
  for(uint i = 0; i < index.size(); ++i){
    dst.push_back(src[index[i]]);
  }
  return dst;
}

Mat solve(const std::vector<cv::DMatch> &origDmatch, const vector<KeyPoint> *corners){
  uint matchCount = origDmatch.size();
  std::vector<int> rand_array = make_rand_array_unique(4, 0, matchCount - 1);

  vector<cv::DMatch> dmatch = selectVector<cv::DMatch>(origDmatch, rand_array);

  // create equation
  Mat A = createEquationA(dmatch, corners);
  Mat b = createEquationb(dmatch, corners);

  // solve equation
  Mat h = solveEquation(A, b);

  return h;
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

  // Detect corners
  CornerDetector cornerDetector;
  vector<KeyPoint> corners[imageCount];
  for(uint i = 0; i < imageCount; ++i)
    corners[i] = cornerDetector.detectCorners(images[i]);

  // Draw detected corners
  for(uint i = 0; i < imageCount; ++i)
    drawAndShowImage(images[i], corners[i]);

  // descript sift feature
  Mat descriptors[imageCount];
  for(uint i = 0; i < imageCount; ++i)
    descriptors[i] = descriptFeatures(images[i], corners[i]);

  // calc sift match
  std::vector<cv::DMatch> origDmatch = calcSiftMatch(descriptors);

  // remove weak distance match
  float minDist = std::min_element(origDmatch.begin(), origDmatch.end(),
				   [](DMatch a, DMatch b) {
				     return a.distance > b.distance;
				   })->distance;
  remove_if(origDmatch.begin(), origDmatch.end(),
	    [&](DMatch x) -> bool{
	      return x.distance > minDist * 3;
	    });
  drawSiftMatch(images, corners, origDmatch);

  // test opencv findHomography
  // {
  //   std::vector< Point2f > obj;
  //   std::vector< Point2f > scene;
  //   for(int i = 0; i < origDmatch.size(); ++i){
  //     obj.push_back( corners[0][ origDmatch[i].queryIdx ].pt );
  //     scene.push_back( corners[1][ origDmatch[i].trainIdx ].pt );      
  //   }
  //   Mat H = findHomography( obj, scene, CV_RANSAC );

  //   // Use the Homography Matrix to warp the images
  //   cv::Mat result;
  //   warpPerspective(images[0], result, H, cv::Size(images[0].cols+images[1].cols,images[0].rows));
  //   cv::Mat half(result,cv::Rect(0,0,images[1].cols,images[1].rows));
  //   images[1].copyTo(half);
  //   imshow( "Result", result );
  //   waitKey(0);
  // }
  

  std::vector<Mat> hVec(ransacTrial);
  int maxIdx = -1;
  int maxInliers = 0;
  
  for (uint i = 0; i < ransacTrial; ++i){
    Mat h = solve(origDmatch, corners);

    hVec[i] = h;

    int inliers = 0;

    for(uint j = 0; j < origDmatch.size(); ++j){
      Point2f p1 = corners[0][origDmatch[j].queryIdx].pt;
      Point2f p2 = corners[1][origDmatch[j].trainIdx].pt;

      float reprojectedX = (p1.x * h.at<float>(0, 0) + p1.y * h.at<float>(0, 1) + h.at<float>(0, 2)) / (p1.x * h.at<float>(2, 0) + p1.y * h.at<float>(2, 1) + h.at<float>(2, 2));
      float reprojectedY = (p1.x * h.at<float>(1, 0) + p1.y * h.at<float>(1, 1) + h.at<float>(1, 2)) / (p1.x * h.at<float>(2, 0) + p1.y * h.at<float>(2, 1) + h.at<float>(2, 2));

      Point2f reprojectedPoint = Point2f(reprojectedX, reprojectedY);

      double res = cv::norm(p2 - reprojectedPoint);

      if (res < 10.0){
	inliers++;
      }
    }

    if (maxInliers < inliers){
      maxInliers = inliers;
      maxIdx = i;
    }
  }

  if (maxIdx < 0){
    std::cout << "not found" << std::endl;
    return 0;
  }

  // homogeneous transformation
  Mat transformedImage;

  // cv::warpPerspective(images[1], transformedImage, hVec[maxIdx], transformedImage.size());

  cout << hVec[maxIdx] << endl;
  
  warpPerspective(images[0], transformedImage, hVec[maxIdx], cv::Size(images[0].cols+images[1].cols,images[0].rows));
  cv::Mat half(transformedImage, cv::Rect(0, 0, images[1].cols, images[1].rows));
  images[1].copyTo(half);

  // show result
  cv::imshow("image", transformedImage);
  cv::waitKey(0);

  return 0;
}
