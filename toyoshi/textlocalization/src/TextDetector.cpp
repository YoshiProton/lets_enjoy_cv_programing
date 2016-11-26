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
  
  cvtColor(image, grayImage, CV_BGR2GRAY);

  for(int i = 0; i < 256; i++){
    std::cout << i << std::endl;
    Mat dst;
    threshold(grayImage,
	      dst, i,
	      max_BINARY_value, threshold_type);


    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    
    Canny(dst, canny_output, thresh, thresh*2, 3);

    findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    
    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
      {
	Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
	drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
      }

    imshow("binaly image", dst);
    imshow("canny output", canny_output);
    imshow("grey image", drawing);
    imshow("image", image);
    waitKey(0);
  }

  return Mat();
}
