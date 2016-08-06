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

  {
    // 中心画素値の表示
    Vec3b centerPoint = image.at<Vec3b>(image.rows / 2, image.cols / 2);

    std::cout << "center point rgb: " << centerPoint << std::endl;

    // 色空間の変換
    Mat hsvImage;
    cvtColor(image, hsvImage, CV_RGB2HSV);
    Vec3b centerPointHsv = hsvImage.at<Vec3b>(image.rows / 2, image.cols / 2);
    std::cout << "center point hsv: " << centerPointHsv << std::endl;
  }

  {
    Mat testImage(255, 255, CV_8UC3);
    testImage = Scalar(100, 100, 100);
    Mat rgbImage;
    cvtColor(testImage, rgbImage, CV_HSV2BGR);
    imshow("result2", rgbImage);
  }

  {
    // 色空間の変換
    Mat hsvImage;
    cvtColor(image, hsvImage, CV_BGR2HSV);

    for(int w = 0; w < hsvImage.cols; ++w){
      for(int h = 0; h < hsvImage.rows; ++h){
	Vec3b p = hsvImage.at<Vec3b>(w, h);
	if (p[0] < 15){
	  cout << "hoge" << std::endl;	  
	  p[0] = 120;
	  p[1] = 100;
	  p[2] = 100;
	}
	hsvImage.at<Vec3b>(w, h) = p;
      }
    }
    Mat showImage;
    cvtColor(hsvImage, showImage, CV_HSV2BGR);
    imshow("result3", showImage);
  }

  waitKey(0);
  
  return 0;
}
