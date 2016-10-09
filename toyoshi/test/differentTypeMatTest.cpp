#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat diffTypeMul(const cv::Mat &a, const cv::Mat &b){
  int aDepth = a.depth();
  int bDepth = b.depth();
  
  if(aDepth == bDepth){
      return a.mul(b);
  }

  if(aDepth < bDepth){
    Mat c;
    a.convertTo(c, bDepth);
    return c.mul(b);
  }

  Mat c;
  b.convertTo(c, aDepth);
  return b.mul(c);
}

int main(){
  Mat a = Mat::eye(10, 10, CV_8UC1);
  Mat b = Mat::eye(10, 10, CV_16UC1);

  Mat c;
  a.convertTo(c, CV_16UC1);

  try{
    Mat mul = a.mul(b);
    cout << mul << endl;
  }catch(...){
    cout << "fail in a.mul(b)" << endl;
  }

  try{
    Mat mul = c.mul(b);
    cout << mul << endl;
  }catch(...){
    cout << "fail in c.mul(b)" << endl;
  }

  try{
    Mat mul = diffTypeMul(a, b);
    cout << mul << endl;
  }catch(...){
    cout << "fail in diffTypeMul" << endl;
  }
}
