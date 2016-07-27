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

	int selectedAlgorithm = 0;
	switch (algorithm)
	{
	case 0:
		selectedAlgorithm = cv::INTER_NEAREST;
		break;
	case 1:
		selectedAlgorithm = cv::INTER_LINEAR;
		break;
	case 2:
		selectedAlgorithm = cv::INTER_CUBIC;
		break;
	}

	//元画像読み込み
	cv::Mat image1 = cv::imread(path);

	cv::Mat resizeImg;
	//画像をリサイズする
	cv::resize(image1, resizeImg, cv::Size(), ratio, ratio, selectedAlgorithm);
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

	int dscWidth = width * ratio;
	int dscHeight = height * ratio;

	cv::Mat image2 = cv::Mat(cv::Size(dscWidth, dscHeight), CV_8UC3);

	for (int y = 0; y < dscHeight; y++)
	{
		for (int x = 0; x < dscWidth; x++)
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
				if (algorithm == Algorithm::NearestNeighbor)
				{
					image2.at<cv::Vec3b>(y, x) = image1.at<cv::Vec3b>(oldY, oldX);
				}
				//Bilinear
				else if (algorithm == Algorithm::Bilinear)
				{
					//TODO
				}
				//Bicubic
				else if (algorithm == Algorithm::Bicubic)
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
void CResize::ProcessFullScratch(LPCOLORREF srcPixelData, BITMAPINFO* bmpInfo)
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

	UINT dscWidth = width * ratio;
	UINT dscHeight = height * ratio;

	BITMAPINFO bmpInf;
	bmpInf.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInf.bmiHeader.biWidth = dscWidth;
	bmpInf.bmiHeader.biHeight = -(INT)dscHeight;
	bmpInf.bmiHeader.biPlanes = bmpInfo->bmiHeader.biPlanes;
	bmpInf.bmiHeader.biBitCount = bmpInfo->bmiHeader.biBitCount;
	bmpInf.bmiHeader.biCompression = bmpInfo->bmiHeader.biCompression;

	LPCOLORREF dscPixelData = new COLORREF[dscWidth * dscHeight];

	//原寸と縮小は補間の必要がないためNearest neighborで処理
	if (ratio <= 1.0)
	{
		ResizeByNearestNeighbor(width, height, dscWidth, dscHeight, ratio, srcPixelData, dscPixelData);
	}
	//拡大は各アルゴリズムで処理
	else
	{
		//Nearest neighbor
		if (algorithm == Algorithm::NearestNeighbor)
		{
			ResizeByNearestNeighbor(width, height, dscWidth, dscHeight, ratio, srcPixelData, dscPixelData);
		}
		//Bilinear
		else if (algorithm == Algorithm::Bilinear)
		{
			ResizeByBilinear(width, height, dscWidth, dscHeight, ratio, srcPixelData, dscPixelData);
		}
		//Bicubic
		else if (algorithm == Algorithm::Bicubic)
		{
			ResizeByBicubic(width, height, dscWidth, dscHeight, ratio, srcPixelData, dscPixelData);
		}
	}

	ShowPictureDlg(dscPixelData, &bmpInf);

	delete[] dscPixelData;
}


///<summary>
///	Nearest neighbor
///</summary>
void CResize::ResizeByNearestNeighbor(UINT width, UINT height, UINT dscWidth, UINT dscHeight, double ratio, LPCOLORREF srcPixelData, LPCOLORREF dscPixelData)
{
	for (int x = 0; x < dscWidth; x++)
	{
		for (int y = 0; y < dscHeight; y++)
		{
			int dscPos = x + y * dscWidth;
			int srcPos = (int)(x / ratio) + (int)(y / ratio) * width;

			dscPixelData[dscPos] = srcPixelData[srcPos];
		}
	}
}


///<summary>
///	Bilinear
///</summary>
void CResize::ResizeByBilinear(UINT width, UINT height, UINT dscWidth, UINT dscHeight, double ratio, LPCOLORREF srcPixelData, LPCOLORREF dscPixelData)
{
	for (int x = 0; x < width - 1; x++)
	{
		for (int y = 0; y < height - 1; y++)
		{
			int srcPos = x + y * width;//基準点

			int srcPosH = (x + 1) + y * width;//右横のピクセルの位置
			int srcPosV = x + (y + 1) * width;//真下のピクセルの位置

			//RGB分解処理（符号が必要なのでintで計算して最後にBYTEにキャストする）
			int red = (int)GetRValue(srcPixelData[srcPos]);
			int green = (int)GetGValue(srcPixelData[srcPos]);
			int blue = (int)GetBValue(srcPixelData[srcPos]);

			//基準点と右横のピクセルとの差をRGBで
			int diffRH = (int)GetRValue(srcPixelData[srcPosH]) - red;
			int diffHG = (int)GetGValue(srcPixelData[srcPosH]) - green;
			int diffHB = (int)GetBValue(srcPixelData[srcPosH]) - blue;

			//基準点と真下のピクセルとの差をRGBで
			int diffRV = (int)GetRValue(srcPixelData[srcPosV]) - red;
			int diffVG = (int)GetGValue(srcPixelData[srcPosV]) - green;
			int diffVB = (int)GetBValue(srcPixelData[srcPosV]) - blue;

			//基準点(0)から隣のピクセル(1)まで1/ratioステップで変化させる
			for (double r = 0; isless(r, 1.0); r += (1 / ratio))//実数の比較にC99で追加された浮動小数点数比較マクロを使用
			{
				//縦方向の補間
				int dscPosV = (int)(x * ratio) + (int)((y + r) * ratio) * dscWidth;
				dscPixelData[dscPosV] = RGB(
					(BYTE)(red + diffRV * r), 
					(BYTE)(green + diffVG * r), 
					(BYTE)(blue + diffVB * r));

				//横方向の補間
				int dscPosH = (int)((x + r) * ratio) + (int)(y * ratio) * dscWidth;
				dscPixelData[dscPosH] = RGB(
					(BYTE)(red + diffRH * r),
					(BYTE)(green + diffHG * r),
					(BYTE)(blue + diffHB * r));

				//補間した縦のピクセルを元に一つ前のブロックの横方向を補間
				if (x != 0)
				{
					//一つ前のブロックの位置
					int prevPosV = (int)((x - 1) * ratio) + (int)((y + r) * ratio) * dscWidth;

					//符号が必要なのでintで計算して最後にBYTEにキャストする
					int prevR = (int)GetRValue(dscPixelData[prevPosV]);
					int prevG = (int)GetGValue(dscPixelData[prevPosV]);
					int prevB = (int)GetBValue(dscPixelData[prevPosV]);

					int diffR = (int)GetRValue(dscPixelData[dscPosV]) - prevR;
					int diffG = (int)GetGValue(dscPixelData[dscPosV]) - prevG;
					int diffB = (int)GetBValue(dscPixelData[dscPosV]) - prevB;

					//基準点(0)から隣のピクセル(1)まで1/ratioステップで変化させる（横方向の補間）
					for (double rh = (1 / ratio); isless(rh, 1.0); rh += (1 / ratio))
					{
						int dscPos = (int)((x - 1 + rh) * ratio) + (int)((y + r) * ratio) * dscWidth;
						dscPixelData[dscPos] = RGB(
							(BYTE)(prevR + diffR * rh),
							(BYTE)(prevG + diffG * rh),
							(BYTE)(prevB + diffB * rh));
					}
				}
			}
		}
	}
}

///<summary>
///	Bicubic
///</summary>
void CResize::ResizeByBicubic(UINT width, UINT height, UINT dscWidth, UINT dscHeight, double ratio, LPCOLORREF srcPixelData, LPCOLORREF dscPixelData)
{
	//TODO
}