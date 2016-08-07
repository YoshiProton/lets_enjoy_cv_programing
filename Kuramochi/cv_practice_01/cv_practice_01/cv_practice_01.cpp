// cv_practice_01.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//
#include "stdafx.h"
#include <iostream>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui.hpp>

using namespace std;

// practice 01: show image
void Show(const cv::Mat& img_, const string& windowName_)
{
	cv::namedWindow(windowName_);
	cv::imshow(windowName_, img_);
}

// practice 02: convert color image to gray scale image using OpenCV method
cv::Mat ConvertToGray(const cv::Mat& colorImg_)
{
	cv::Mat gray;
	cv::cvtColor(colorImg_, gray, cv::COLOR_BGR2GRAY);

	return gray;
}

// practice 03: convert color image to gray scale image not using OpenCV method
cv::Mat MyConvertToGray(const cv::Mat& colorImg_)
{
	const double weightBlue = 0.114;  // from OpenCV 2.2 reference cvtColor
	const double weightGreen = 0.587; // from OpenCV 2.2 reference cvtColor
	const double weightRed = 0.299;   // from OpenCV 2.2 reference cvtColor

	cv::Mat gray = cv::Mat::zeros(cv::Size(colorImg_.cols, colorImg_.rows), CV_8UC1);

	// 本当は forEach を使いたいんだけど...
	// 2 枚の画像に対してどうやって forEach する？
	// zip みたいな機能ってないのだろうか？
	for (int row = 0; row < gray.rows; row++)
	{
		auto *colorPixel = &colorImg_.at<cv::Vec3b>(row, 0);
		unsigned char *grayPixel = &gray.at<unsigned char>(row, 0);
		for (int col = 0; col < gray.cols; col++)
		{
			*grayPixel = weightBlue * (*colorPixel)[0] + weightGreen * (*colorPixel)[1] + weightRed * (*colorPixel)[2];
			colorPixel++;
			grayPixel++;
		}
	}

	return gray;
}


int main()
{
	const string practiceDirectory = "C:\\Users\\Teddy\\Source\\Repos\\lets_enjoy_cv_programing\\_lesson\\20160709";
	const string lenaFilename = "lena.jpg";
	auto lenaImg = cv::imread(practiceDirectory + "\\" + lenaFilename);

	// practice 01: show lena
	Show(lenaImg, "Lena");
	
	// practice 02: convert color to gray using OpenCV method
	const string lenaFilenameGrayCV = "lena_gray_cv.jpg";
	auto lenaGray = ConvertToGray(lenaImg);
	cv::imwrite(practiceDirectory + "\\" + lenaFilenameGrayCV, lenaGray);

	// practice 03: convert color to gray not using OpenCV method
	const string lenaFilenameMyGray = "lena_gray_my.jpg";
	auto lenaMyGray = MyConvertToGray(lenaImg);
	cv::imwrite(practiceDirectory + "\\" + lenaFilenameMyGray, lenaMyGray)+

	cv::waitKey(0);
	cv::destroyAllWindows();
	
    return 0;
}
