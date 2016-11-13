#include "ImageStitcher.hpp"

#include <opencv2/nonfree/nonfree.hpp>
#include <toyocv/imgproc.hpp>

#include <random>
#include <cstdint>
#include <algorithm>
#include <stdexcept>
#include <unordered_set>
#include <functional>
#include <limits>
#include <type_traits>

#include "UniqueRandomSampler.hpp"
#include "CornerDetector.hpp"

using namespace std;
using namespace cv;

const uint imageCount = 2;

Mat ImageStitcher::descriptFeatures(const Mat &image, vector<KeyPoint> &corners){
  initModule_nonfree(); 
  Ptr<DescriptorExtractor> extractor = cv::DescriptorExtractor::create("SIFT");
  Mat descriptor;
  extractor->compute(image, corners, descriptor);

  return descriptor;
}

vector<DMatch> ImageStitcher::calcSiftMatch(const Mat *descriptors){
  Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("FlannBased");
  vector<DMatch> dmatch;
  
  matcher->match(descriptors[0], descriptors[1], dmatch);

  return dmatch;
}

Mat ImageStitcher::createEquationA(vector<cv::DMatch> dmatch, const vector<KeyPoint> *corners){
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

Mat ImageStitcher::createEquationb(vector<DMatch> dmatch, const vector<KeyPoint> *corners){
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

Mat ImageStitcher::solveEquation(const Mat &A, const Mat &b){
  Mat tmp1 = A.t() * A;

  Mat tmp2 = tmp1.inv(cv::DECOMP_SVD);

  Mat h = tmp2 * A.t() * b;

  Mat mat33 = Mat::ones(1, 1, CV_32FC1);
  h.push_back(mat33);

  return h.reshape(1, 3);
}

Mat ImageStitcher::selectRows(const Mat &src, const vector<int> &rand_array){
  Mat dst = src.row(rand_array[0]);

  for(uint i = 1; i < rand_array.size(); ++i){
    dst.push_back(src.row(rand_array[i]));
  }

  return dst;
}

template <typename T> vector<T> ImageStitcher::selectVector(const vector<T> &src, const vector<int> &index){
  vector<T> dst;
  for(uint i = 0; i < index.size(); ++i){
    dst.push_back(src[index[i]]);
  }
  return dst;
}

Mat ImageStitcher::solve(const std::vector<cv::DMatch> &origDmatch,
			const vector<KeyPoint> *corners){
  uint matchCount = origDmatch.size();

  UniqueRandomSampler uniqueRandomSampler;
  
  std::vector<int> rand_array = uniqueRandomSampler.make_rand_array_unique(4, 0, matchCount - 1);

  vector<cv::DMatch> dmatch = selectVector<cv::DMatch>(origDmatch, rand_array);

  // create equation
  Mat A = createEquationA(dmatch, corners);
  Mat b = createEquationb(dmatch, corners);

  // solve equation
  Mat h = solveEquation(A, b);

  return h;
}


Mat ImageStitcher::stitch(const Mat* images){
    // Detect corners
  CornerDetector cornerDetector;
  vector<KeyPoint> corners[imageCount];
  for(uint i = 0; i < imageCount; ++i)
    corners[i] = cornerDetector.detectCorners(images[i]);

  // Draw detected corners
  // for(uint i = 0; i < imageCount; ++i)
  //   drawAndShowImage(images[i], corners[i]);

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
  // drawSiftMatch(images, corners, origDmatch);

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
    throw 1;
  }

  // homogeneous transformation
  Mat transformedImage;

  // cv::warpPerspective(images[1], transformedImage, hVec[maxIdx], transformedImage.size());

  cout << hVec[maxIdx] << endl;
  
  warpPerspective(images[0], transformedImage, hVec[maxIdx], cv::Size(images[0].cols+images[1].cols,images[0].rows));
  cv::Mat half(transformedImage, cv::Rect(0, 0, images[1].cols, images[1].rows));
  images[1].copyTo(half);

  return transformedImage;
}
