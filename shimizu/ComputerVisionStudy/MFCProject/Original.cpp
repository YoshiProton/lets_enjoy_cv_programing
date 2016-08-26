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
void COriginal::ProcessByFullOpenCV(CString filePath)
{
	std::string path = this->GetMultiBytePath(filePath);
	cv::Mat cvImage = cv::imread(path);
	cv::namedWindow("原画像", cv::WINDOW_AUTOSIZE);
	cv::imshow("原画像", cvImage);
}


///<summary>
///	画像読み込み保存のみOpenCVを使用してピクセル操作はスクラッチ
///</summary>
void COriginal::ProcessByPartOpenCV(CString filePath)
{
	//元画像読み込み
	cv::Mat srcImage = cv::imread(this->GetMultiBytePath(filePath));
	cv::Mat dstImage = cv::Mat(cv::Size(srcImage.cols, srcImage.rows), CV_8UC3);

	for (int x = 0; x < srcImage.cols; x++)
	{
		for (int y = 0; y < srcImage.rows; y++)
		{
			cv::Vec3b color = srcImage.at<cv::Vec3b>(y, x);
			int r = (int)color[2];
			int g = (int)color[1];
			int b = (int)color[0];

			dstImage.at<cv::Vec3b>(y, x) = cv::Vec3b(b, g, r);
		}
	}

	cv::namedWindow("原画像", cv::WINDOW_AUTOSIZE);
	cv::imshow("原画像", dstImage);
}


///<summary>
///	OpenCVを全く使わずにフルスクラッチ
///</summary>
void COriginal::ProcessByFullScratch(LPCOLORREF srcPixelData, BITMAPINFO* bmpInfo)
{
	UINT width = bmpInfo->bmiHeader.biWidth;
	UINT height = bmpInfo->bmiHeader.biHeight;

	LPCOLORREF dstPixelData = new COLORREF[width * height];

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int srcPos = x + y * width;
			int r = (int)CUtility::GetR(srcPixelData[srcPos]);
			int g = (int)CUtility::GetG(srcPixelData[srcPos]);
			int b = (int)CUtility::GetB(srcPixelData[srcPos]);

			dstPixelData[srcPos] = GetPixelValue(r, g, b);
		}
	}

	ShowPictureDlg(dstPixelData, bmpInfo);
	delete[] dstPixelData;
}