#include "stdafx.h"
#include "Grayscale.h"


CGrayscale::CGrayscale()
{
}


CGrayscale::~CGrayscale()
{
}


///<summary>
///	OpenCVを活用して簡単実装
///</summary>
void CGrayscale::ProcessByFullOpenCV(CString filePath)
{
	std::string path = this->GetMultiBytePath(filePath);

	//元画像読み込み
	cv::Mat srcImage = cv::imread(path);

	//cvtColor関数で変換
	cv::Mat dstImage1;
	cvtColor(srcImage, dstImage1, CV_RGB2GRAY);
	cv::namedWindow("グレイスケール画像(cvtColor関数使用)", cv::WINDOW_AUTOSIZE);
	cv::imshow("グレイスケール画像(cvtColor関数使用)", dstImage1);

	//読み込み時オプション指定
	cv::Mat dstImage2 = cv::imread(path, cv::IMREAD_GRAYSCALE);
	cv::namedWindow("グレイスケール画像(読み込み時に変換)", cv::WINDOW_AUTOSIZE);
	cv::imshow("グレイスケール画像(読み込み時に変換)", dstImage2);

	//ファイルに保存
	char lpDest[MAX_PATH] = {};
	this->GetNewFilePath((LPSTR)path.c_str(), "grayscale.ocv1.jpg", lpDest);
	cv::imwrite(lpDest, dstImage1);
	//ファイルに保存
	this->GetNewFilePath((LPSTR)path.c_str(), "grayscale.ocv2.jpg", lpDest);
	cv::imwrite(lpDest, dstImage2);
}


///<summary>
///	画像読み込み保存のみOpenCVを使用してピクセル操作はスクラッチ
///</summary>
void CGrayscale::ProcessByPartOpenCV(CString filePath)
{
	std::string path = this->GetMultiBytePath(filePath);

	//元画像読み込み
	cv::Mat srcImage = cv::imread(path);

	//ピクセル操作でグレイスケール化
	int x, y;
	uchar r1, g1, b1, r2, g2, b2, color2;
	cv::Vec3b color1;
	cv::Mat dstImage = cv::Mat(cv::Size(srcImage.cols, srcImage.rows), CV_8UC1);
	for (y = 0;y < srcImage.rows; y++)
	{
		for (x = 0;x < srcImage.cols; x++)
		{
			color1 = srcImage.at<cv::Vec3b>(y, x);
			r1 = color1[2];
			g1 = color1[1];
			b1 = color1[0];
			color2 = cv::saturate_cast<uchar>(0.299 * r1 + 0.587 * g1 + 0.114 * b1);
			dstImage.at<uchar>(y, x) = color2;
		}
	}

	cv::namedWindow("グレイスケール画像(ピクセル操作)", cv::WINDOW_AUTOSIZE);
	cv::imshow("グレイスケール画像(ピクセル操作)", dstImage);

	//ShowPictureDlg(dstImage);

	//ファイルに保存
	char lpDest[MAX_PATH] = {};
	this->GetNewFilePath((LPSTR)path.c_str(), "grayscale.hocv.jpg", lpDest);
	cv::imwrite(lpDest, dstImage);
}


///<summary>
///	OpenCVを全く使わずにフルスクラッチ
///</summary>
void CGrayscale::ProcessByFullScratch(LPCOLORREF srcPixelData, BITMAPINFO* bmpInfo)
{
	UINT width = bmpInfo->bmiHeader.biWidth;
	UINT height = bmpInfo->bmiHeader.biHeight;

	BYTE red, green, blue, density;
	LPCOLORREF dstPixelData = new COLORREF[width * height];

	for (int i = 0; i < width * height; i++)
	{
		red = CUtility::GetR(srcPixelData[i]);
		green = CUtility::GetG(srcPixelData[i]);
		blue = CUtility::GetB(srcPixelData[i]);

		density = (4 * red + 2 * green + blue) / 7;
		dstPixelData[i] = RGB(density, density, density);
	}

	ShowPictureDlg(dstPixelData, bmpInfo);

	delete[] dstPixelData;
}