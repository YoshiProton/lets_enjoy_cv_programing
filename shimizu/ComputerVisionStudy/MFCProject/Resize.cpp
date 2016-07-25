#include "stdafx.h"
#include <math.h>
#include "Resize.h"
#include "ResizeDlg.h"

CResize::CResize()
{
}


CResize::~CResize()
{
}


///<summary>
///	OpenCVを活用して簡単実装
///</summary>
void CResize::ProcessFullOpenCV(CString filePath)
{
	std::string path = this->GetMultiBytePath(filePath);

	double ratio = 1.0;
	int algorithm = 0;
	CResizeDlg dlg;
	dlg.SetValues(&ratio, &algorithm);
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	//元画像読み込み
	cv::Mat image1 = cv::imread(path);

	cv::Mat resizeImg;
	//画像をリサイズする
	cv::resize(image1, resizeImg, cv::Size(), ratio, ratio, algorithm);
	cv::namedWindow("リサイズ画像(resize関数)", cv::WINDOW_AUTOSIZE);
	cv::imshow("リサイズ画像(resize関数)", resizeImg);

	cv::waitKey(0);
	cv::destroyAllWindows();

	char lpDest[MAX_PATH] = {};
	this->GetNewFilePath((LPSTR)path.c_str(), "size1.jpg", lpDest);
	cv::imwrite(lpDest, resizeImg);
}


///<summary>
///	画像読み込み保存のみOpenCVを使用してピクセル操作はスクラッチ
///</summary>
void CResize::ProcessHalfOpenCV(CString filePath)
{
	std::string path = this->GetMultiBytePath(filePath);

	double ratio = 1.0;
	int algorithm = 0;
	CResizeDlg dlg;
	dlg.SetValues(&ratio, &algorithm);
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	//元画像読み込み
	cv::Mat image1 = cv::imread(path);

	//RGB分解
	int x, y;
	uchar r1, g1, b1, r2, g2, b2, color2;
	int width = image1.cols;
	int height = image1.rows;

	int newWidth = width * ratio;
	int newHeight = height * ratio;

	cv::Mat image2 = cv::Mat(cv::Size(newWidth, newHeight), CV_8UC3);

	for (int y = 0; y < newHeight; y++)
	{
		for (int x = 0; x < newWidth; x++)
		{
			int oldX = (int)(x / ratio);
			int oldY = (int)(y / ratio);

			//等倍および縮小は補間の必要がないためNearest neighborのみ
			if (ratio <= 1.0)
			{
				image2.at<cv::Vec3b>(y, x) = image1.at<cv::Vec3b>(oldY, oldX);
			}
			//拡大
			else
			{
				//Nearest neighbor
				if (algorithm == 0)
				{
					image2.at<cv::Vec3b>(y, x) = image1.at<cv::Vec3b>(oldY, oldX);
				}
				//Bilinear
				else if (algorithm == 1)
				{
					//TODO
				}
				//Bicubic
				else if (algorithm == 2)
				{
					//TODO
				}
			}
		}
	}

	cv::namedWindow("リサイズ画像(RGB分解)", cv::WINDOW_AUTOSIZE);
	cv::imshow("リサイズ画像(RGB分解)", image2);

	cv::waitKey(0);
	cv::destroyAllWindows();
}


///<summary>
///	OpenCVを全く使わずにフルスクラッチ
///</summary>
void CResize::ProcessFullScratch(LPCOLORREF lpcrPixelData, BITMAPINFO* bmpInfo)
{
	double ratio = 1.0;
	int algorithm = 0;
	CResizeDlg dlg;
	dlg.SetValues(&ratio, &algorithm);
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	UINT width = bmpInfo->bmiHeader.biWidth;
	UINT height = -1 * bmpInfo->bmiHeader.biHeight;

	UINT newWidth = width * ratio;
	UINT newHeight = height * ratio;

	BITMAPINFO bmpInf;
	bmpInf.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInf.bmiHeader.biWidth = newWidth;
	bmpInf.bmiHeader.biHeight = -(INT)newHeight;
	bmpInf.bmiHeader.biPlanes = bmpInfo->bmiHeader.biPlanes;
	bmpInf.bmiHeader.biBitCount = bmpInfo->bmiHeader.biBitCount;
	bmpInf.bmiHeader.biCompression = bmpInfo->bmiHeader.biCompression;

	LPCOLORREF lpcrPixelData2 = new COLORREF[newWidth * newHeight];

	for (int x = 0; x < newWidth; x++)
	{
		for (int y = 0; y < newHeight; y++)
		{
			int newXY = x + y * newWidth;
			int oldXY = (int)(x / ratio) + (int)(y / ratio) * width;

			//等倍および縮小は補間の必要がないためNearest neighborのみ
			if (ratio <= 1.0)
			{
				lpcrPixelData2[newXY] = lpcrPixelData[oldXY];
			}
			//拡大
			else
			{
				//Nearest neighbor
				if (algorithm == 0)
				{
					lpcrPixelData2[newXY] = lpcrPixelData[oldXY];
				}
				//Bilinear
				else if (algorithm == 1)
				{
					//TODO
				}
				//Bicubic
				else if (algorithm == 2)
				{
					//TODO
				}
			}
		}
	}

	ShowPictureDlg(lpcrPixelData2, &bmpInf);

	delete[] lpcrPixelData2;
}