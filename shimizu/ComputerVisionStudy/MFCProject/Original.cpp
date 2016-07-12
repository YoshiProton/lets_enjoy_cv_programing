#include "stdafx.h"
#include "Original.h"


COriginal::COriginal()
{
}


COriginal::~COriginal()
{
}


void COriginal::Execute(std::string filePath)
{
	cv::Mat image1 = cv::imread(filePath);
	cv::namedWindow("Œ´‰æ‘œ", cv::WINDOW_AUTOSIZE);
	cv::imshow("Œ´‰æ‘œ", image1);
	cv::waitKey(0);
	cv::destroyAllWindows();
}