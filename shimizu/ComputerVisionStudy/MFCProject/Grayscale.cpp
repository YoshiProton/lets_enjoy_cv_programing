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
void CGrayscale::ProcessFullOpenCV(CString filePath)
{
	std::string path = this->GetMultiBytePath(filePath);

	//元画像読み込み
	cv::Mat image1 = cv::imread(path);

	//cvtColor関数で変換
	cv::Mat image3;
	cvtColor(image1, image3, CV_RGB2GRAY);
	cv::namedWindow("グレイスケール画像(cvtColor関数使用)", cv::WINDOW_AUTOSIZE);
	cv::imshow("グレイスケール画像(cvtColor関数使用)", image3);

	//読み込み時オプション指定
	cv::Mat image4 = cv::imread(path, cv::IMREAD_GRAYSCALE);
	cv::namedWindow("グレイスケール画像(読み込み時に変換)", cv::WINDOW_AUTOSIZE);
	cv::imshow("グレイスケール画像(読み込み時に変換)", image4);

	cv::waitKey(0);
	cv::destroyAllWindows();

	char lpDest[MAX_PATH] = {};
	this->GetNewFilePath((LPSTR)path.c_str(), "grayscale1.jpg", lpDest);
	cv::imwrite(lpDest, image3);
}


///<summary>
///	画像読み込み保存のみOpenCVを使用してピクセル操作はスクラッチ
///</summary>
void CGrayscale::ProcessHalfOpenCV(CString filePath)
{
	std::string path = this->GetMultiBytePath(filePath);

	//元画像読み込み
	cv::Mat image1 = cv::imread(path);

	//ピクセル操作でグレイスケール化
	int x, y;
	uchar r1, g1, b1, r2, g2, b2, color2;
	cv::Vec3b color1;
	int width = image1.cols;
	int height = image1.rows;
	cv::Mat image2 = cv::Mat(cv::Size(width, height), CV_8UC1);
	for (y = 0;y < height; y++)
	{
		for (x = 0;x < width; x++)
		{
			color1 = image1.at<cv::Vec3b>(y, x);
			r1 = color1[2];
			g1 = color1[1];
			b1 = color1[0];
			color2 = cv::saturate_cast<uchar>(0.299 * r1 + 0.587 * g1 + 0.114 * b1);
			image2.at<uchar>(y, x) = color2;
		}
	}

	cv::namedWindow("グレイスケール画像(ピクセル操作)", cv::WINDOW_AUTOSIZE);
	cv::imshow("グレイスケール画像(ピクセル操作)", image2);

	cv::waitKey(0);
	cv::destroyAllWindows();
}


///<summary>
///	OpenCVを全く使わずにフルスクラッチ
///</summary>
void CGrayscale::ProcessFullScratch(LPCOLORREF lpcrPixelData, BITMAPINFO* bmpInfo)
{
	UINT WIDTH = bmpInfo->bmiHeader.biWidth;
	UINT HEIGHT = -1 * bmpInfo->bmiHeader.biHeight;

	BYTE byRed, byGreen, byBlue, byDensity;
	LPCOLORREF lpcrPixelData2 = new COLORREF[WIDTH * HEIGHT];

	for (int i = 0;i < WIDTH * HEIGHT; i++)
	{
		byRed = GetRValue(lpcrPixelData[i]);
		byGreen = GetGValue(lpcrPixelData[i]);
		byBlue = GetBValue(lpcrPixelData[i]);

		byDensity = (4 * byRed + 2 * byGreen + byBlue) / 7;
		lpcrPixelData2[i] = RGB(byDensity, byDensity, byDensity);
	}

	ShowPictureDlg(lpcrPixelData2, bmpInfo);

	delete[] lpcrPixelData2;
}