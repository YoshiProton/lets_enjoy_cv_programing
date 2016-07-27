#include "stdafx.h"
#include "Original.h"


COriginal::COriginal()
{
}


COriginal::~COriginal()
{
}


///<summary>
///	OpenCVを活用して簡単実装
///</summary>
void COriginal::ProcessFullOpenCV(CString filePath)
{
	std::string path = this->GetMultiBytePath(filePath);
	cv::Mat cvImage = cv::imread(path);
	cv::namedWindow("原画像", cv::WINDOW_AUTOSIZE);
	cv::imshow("原画像", cvImage);
	cv::waitKey(0);
	cv::destroyAllWindows();

	char lpDest[MAX_PATH] = {};
	this->GetNewFilePath((LPSTR)path.c_str(), "original1.jpg", lpDest);
	cv::imwrite(lpDest, cvImage);
}

//
////画像読み込み保存のみOpenCVを使用して表示をMFCのPictureCotrolで
//void COriginal::ProcessHalfOpenCV(std::string filePath)
//{
//	cv::Mat cvImage = cv::imread(filePath);
//	this->ShowPictureDlg(cvImage);
//
//	char lpDest[MAX_PATH] = {};
//	this->GetNewFilePath((LPSTR)path.c_str(), "original2.jpg", lpDest);
//	cv::imwrite(lpDest, cvImage);
//}


///<summary>
///	OpenCVを全く使わずにフルスクラッチ
///</summary>
void COriginal::ProcessFullScratch(LPCOLORREF pixelData, BITMAPINFO* bmpInfo)
{
	ShowPictureDlg(pixelData, bmpInfo);
}