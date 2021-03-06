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

  Mat showImage;
  imshow("original", image);

  Mat blurImage;
  Size kernelSize(5, 5);
  blur(image, blurImage, kernelSize);
  imshow("blur", blurImage);

  Mat blurImageOrig;
  toyocv::blur(image, blurImageOrig, kernelSize);

  blurImageOrig.convertTo(blurImageOrig, CV_8UC3);
  
  imshow("blurorig", blurImageOrig);

  imshow("diff", blurImage - blurImageOrig);
  
  waitKey(0);
  destroyAllWindows();

  Mat grayImage;
  cvtColor(image, grayImage, CV_RGB2GRAY);

  Size kernelSize2(3, 3);
  
  Mat differentialx;
  Mat differentialy;
  Mat differentialxy;
  toyocv::differential(image, differentialx, CV_64F, 1, 0, kernelSize2);
  toyocv::differential(image, differentialy, CV_64F, 0, 1, kernelSize2);
  toyocv::differential(image, differentialxy, CV_64F, 1, 1, kernelSize2);  

  imshow("diffx", differentialx * 100);
  imshow("diffy", differentialy * 100);
  imshow("diffxy", differentialxy * 100);

  waitKey(0);
  destroyAllWindows();

  Mat sobelx;
  Mat sobely;
  toyocv::sobel(image, sobelx, CV_64F, 1, 0, kernelSize2);
  toyocv::sobel(image, sobely, CV_64F, 0, 1, kernelSize2);

  imshow("sobelx", sobelx * 100);
  imshow("sobely", sobely * 100);

  waitKey(0);
  destroyAllWindows();

  Size kernelSize3(11, 11);

  Mat laplacian[21];
  for (int i = 1; i < 20; ++i){

    double sigma = i * 0.1;
    
    toyocv::laplacian(image, laplacian[i], CV_64F, kernelSize3, sigma);

    std::stringstream   windowName;
    windowName << "laplacian sigma " << sigma;
    imshow(windowName.str(), laplacian[i] * 100);
  }

  waitKey(0);
  destroyAllWindows();  
  
  return 0;
}
