#include "ImageSticher.hpp"

using namespace std;
using namespace cv;

Mat ImageSticher::descriptFeatures(const Mat &image, vector<KeyPoint> &corners){
  initModule_nonfree(); 
  Ptr<DescriptorExtractor> extractor = cv::DescriptorExtractor::create("SIFT");
  Mat descriptor;
  extractor->compute(image, corners, descriptor);

  return descriptor;
}

vector<DMatch> calcSiftMatch(const Mat *descriptors){
  Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("FlannBased");
  vector<DMatch> dmatch;
  
  matcher->match(descriptors[0], descriptors[1], dmatch);

  return dmatch;
}

Mat createEquationA(vector<cv::DMatch> dmatch, const vector<KeyPoint> *corners){
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

Mat createEquationb(vector<DMatch> dmatch, const vector<KeyPoint> *corners){
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

Mat ImageSticher::solveEquation(const Mat &A, const Mat &b){
  Mat tmp1 = A.t() * A;

  Mat tmp2 = tmp1.inv(cv::DECOMP_SVD);

  Mat h = tmp2 * A.t() * b;

  Mat mat33 = Mat::ones(1, 1, CV_32FC1);
  h.push_back(mat33);

  return h.reshape(1, 3);
}

Mat ImageSticher::selectRows(const Mat &src, const vector<int> &rand_array){
  Mat dst = src.row(rand_array[0]);

  for(uint i = 1; i < rand_array.size(); ++i){
    dst.push_back(src.row(rand_array[i]));
  }

  return dst;
}

template <typename T> vector<T> ImageSticher::selectVector(const vector<T> &src, const vector<int> &index){
  vector<T> dst;
  for(uint i = 0; i < index.size(); ++i){
    dst.push_back(src[index[i]]);
  }
  return dst;
}

Mat ImageSticher::solve(const std::vector<cv::DMatch> &origDmatch,
			const vector<KeyPoint> *corners){
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
