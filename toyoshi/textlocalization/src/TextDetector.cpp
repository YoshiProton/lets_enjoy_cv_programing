#include <TextDetector.hpp>

using namespace std;
using namespace cv;

Mat TextDetector::detectText(const Mat &image){
  // calc image channels
  {
    // RGB

    // HSI

    // Delta
  }

  // extract ERs


  // calc connected component

  // labeling

  // vectorlization

  return Mat();
}

Mat TextDetector::mser(const Mat &image){
  Mat grayImage;
  vector<Mat> sweapedImages;
  RNG rng(12345);

  Mat blackMat = Mat::zeros(image.size(), image.type());
  Mat whiteMat = Mat::ones(image.size(), image.type()) * 255;
  
  cvtColor(image, grayImage, CV_BGR2GRAY);

  vector<vector<Point> > contours;

  for(int i = 0; i < 256; i++){
    std::cout << i << std::endl;
    Mat dst;
    Mat dstInv;
    threshold(grayImage,
	      dst, i,
	      max_BINARY_value, 0);
    threshold(grayImage,
	      dstInv, i,
	      max_BINARY_value, 1);

    if(cv::countNonZero(dst) == 0)
      continue;
    if(cv::countNonZero(dstInv) == 0)
      continue;

    Mat canny_output;

    vector<Vec4i> hierarchy;
    vector<vector<Point> > contour;
    
    Canny(dst, canny_output, thresh, thresh*2, 3);

    findContours(canny_output, contour, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    contours.insert(contours.end(), contour.begin(), contour.end());
  }
    
  std::cout << contours.size() << std::endl;


  sort(contours.begin(),
       contours.end(),
       [](const vector<Point>& a, const vector<Point>& b){return (a.size() == b.size()) ? (a.size() < b.size()) : (a.size() < b.size());}
    );
  
  for( int i = 0; i< contours.size(); i++ )
    {
      Mat drawing = Mat::zeros( image.size(), CV_8UC3 );

      vector<Point> cont = contours[i];

      std::cout << i << std::endl;
      std::cout << cont.size() << std::endl;      
      Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
      drawContours( drawing, contours, i, color, 2, 8);

      imshow("grey image", drawing);
      waitKey(0);
    }

  // imshow("binaly image", dst);
  // imshow("canny output", canny_output);

  imshow("image", image);
  waitKey(0);

  return Mat();
}
