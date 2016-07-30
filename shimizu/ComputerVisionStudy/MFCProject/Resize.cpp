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

	int dstWidth = width * ratio;
	int dstHeight = height * ratio;

	cv::Mat image2 = cv::Mat(cv::Size(dstWidth, dstHeight), CV_8UC3);

	for (int y = 0; y < dstHeight; y++)
	{
		for (int x = 0; x < dstWidth; x++)
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

	UINT dstWidth = width * ratio;
	UINT dstHeight = height * ratio;

	BITMAPINFO bmpInf;
	bmpInf.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInf.bmiHeader.biWidth = dstWidth;
	bmpInf.bmiHeader.biHeight = -(INT)dstHeight;
	bmpInf.bmiHeader.biPlanes = bmpInfo->bmiHeader.biPlanes;
	bmpInf.bmiHeader.biBitCount = bmpInfo->bmiHeader.biBitCount;
	bmpInf.bmiHeader.biCompression = bmpInfo->bmiHeader.biCompression;

	LPCOLORREF dstPixelData = new COLORREF[dstWidth * dstHeight];

	//原寸と縮小は補間の必要がないためNearest neighborで処理
	if (ratio <= 1.0)
	{
		ResizeByNearestNeighbor(width, height, dstWidth, dstHeight, ratio, srcPixelData, dstPixelData);
	}
	//拡大は各アルゴリズムで処理
	else
	{
		//Nearest neighbor
		if (algorithm == Algorithm::NearestNeighbor)
		{
			ResizeByNearestNeighbor(width, height, dstWidth, dstHeight, ratio, srcPixelData, dstPixelData);
		}
		//Bilinear
		else if (algorithm == Algorithm::Bilinear)
		{
			ResizeByBilinear(width, height, dstWidth, dstHeight, ratio, srcPixelData, dstPixelData);
		}
		//Bicubic
		else if (algorithm == Algorithm::Bicubic)
		{
			ResizeByBicubic(width, height, dstWidth, dstHeight, ratio, srcPixelData, dstPixelData);
		}
	}

	ShowPictureDlg(dstPixelData, &bmpInf);

	delete[] dstPixelData;
}


///<summary>
///	Nearest neighbor
///</summary>
void CResize::ResizeByNearestNeighbor(UINT width, UINT height, UINT dstWidth, UINT dstHeight, double ratio, LPCOLORREF srcPixelData, LPCOLORREF dstPixelData)
{
	for (int x = 0; x < dstWidth; x++)
	{
		for (int y = 0; y < dstHeight; y++)
		{
			int dstPos = x + y * dstWidth;
			int srcPos = (int)(x / ratio) + (int)(y / ratio) * width;

			dstPixelData[dstPos] = srcPixelData[srcPos];
		}
	}
}


///<summary>
///	Bilinear
///</summary>
void CResize::ResizeByBilinear(UINT width, UINT height, UINT dstWidth, UINT dstHeight, double ratio, LPCOLORREF srcPixelData, LPCOLORREF dstPixelData)
{
	for (int x = 1; x < width - 1; x++)
	{
		for (int y = 0; y < height - 1; y++)
		{
			//基準点
			int srcPos = x + y * width;
			//右横のピクセルの位置
			int srcPosH = (x + 1) + y * width;
			//真下のピクセルの位置
			int srcPosV = x + (y + 1) * width;

			//RGB分解処理（符号が必要なのでintで計算して最後にBYTEにキャストする）
			int srcR = (int)GetRValue(srcPixelData[srcPos]);
			int srcG = (int)GetGValue(srcPixelData[srcPos]);
			int srcB = (int)GetBValue(srcPixelData[srcPos]);

			//基準点と右横のピクセルとの差をRGBで求める
			int diffRH = (int)GetRValue(srcPixelData[srcPosH]) - srcR;
			int diffGH = (int)GetGValue(srcPixelData[srcPosH]) - srcG;
			int diffBH = (int)GetBValue(srcPixelData[srcPosH]) - srcB;

			//基準点と真下のピクセルとの差をRGBで求める
			int diffRV = (int)GetRValue(srcPixelData[srcPosV]) - srcR;
			int diffGV = (int)GetGValue(srcPixelData[srcPosV]) - srcG;
			int diffBV = (int)GetBValue(srcPixelData[srcPosV]) - srcB;

			//拡大後のピクセルの位置の原画像での位置を求めてスキャン
			for (int n = 0; n < ratio; n++)
			{
				double linear = n / ratio;

				//縦方向の補間
				int dstPosV = (int)(x * ratio) + (int)(y * ratio + n) * dstWidth;
				dstPixelData[dstPosV] = RGB((BYTE)(srcR + diffRV * linear), (BYTE)(srcG + diffGV * linear), (BYTE)(srcB + diffBV * linear));

				//横方向の補間
				int dstPosH = (int)(x * ratio + n) + (int)(y * ratio) * dstWidth;
				dstPixelData[dstPosH] = RGB((BYTE)(srcR + diffRH * linear), (BYTE)(srcG + diffGH * linear), (BYTE)(srcB + diffBH * linear));

				//補間した縦のピクセルを元に一つ前のブロックの横方向を補間

				//縦方向のピクセルの一つ前のブロックの位置
				int prevPosV = (int)((x - 1) * ratio) + (int)(y * ratio + n) * dstWidth;

				//RGB分解処理（符号が必要なのでintで計算して最後にBYTEにキャストする）
				int prevR = (int)GetRValue(dstPixelData[prevPosV]);
				int prevG = (int)GetGValue(dstPixelData[prevPosV]);
				int prevB = (int)GetBValue(dstPixelData[prevPosV]);

				//基準点と右横のピクセルとの差をRGBで求める
				int diffR = (int)GetRValue(dstPixelData[dstPosV]) - prevR;
				int diffG = (int)GetGValue(dstPixelData[dstPosV]) - prevG;
				int diffB = (int)GetBValue(dstPixelData[dstPosV]) - prevB;

				for (int nx = 1; nx < ratio; nx++)
				{
					linear = nx / ratio;

					int dstPos = (int)((x - 1) * ratio + nx) + (int)((y * ratio) + n) * dstWidth;
					dstPixelData[dstPos] = RGB((BYTE)(prevR + diffR * linear), (BYTE)(prevG + diffG * linear), (BYTE)(prevB + diffB * linear));
				}
			}
		}
	}
}


///<summary>
///	Bicubic
///</summary>
void CResize::ResizeByBicubic(UINT width, UINT height, UINT dstWidth, UINT dstHeight, double ratio, LPCOLORREF srcPixelData, LPCOLORREF dstPixelData)
{
	double dx[4];
	double dy[4];

	for (int x = 1; x < width - 3; x++)
	{
		for (int y = 1; y < height - 3; y++)
		{
			//拡大後のピクセルの位置の原画像での位置を求めてスキャン
			for (int nx = 0; nx < ratio; nx++)
			{
				for (int ny = 0; ny < ratio; ny++)
				{
					double trgX = x + nx / ratio;
					double trgY = y + ny / ratio;

					dx[0] = 1 + trgX - (x + 1);
					dx[1] = trgX - (x + 1);
					dx[2] = (x + 1) + 1 - trgX;
					dx[3] = (x + 1) + 2 - trgX;

					dy[0] = 1 + trgY - (y + 1);
					dy[1] = trgY - (y + 1);
					dy[2] = (y + 1) + 1 - trgY;
					dy[3] = (y + 1) + 2 - trgY;

					double sumR = 0;
					double sumG = 0;
					double sumB = 0;
					double sumW = 0;

					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 4; j++)
						{
							int pos = (x + i - 1) + (y + j - 1) * width;

							double weight = GetBicubicWeight(dx[i]) * GetBicubicWeight(dy[j]);

							sumR += weight * GetRValue(srcPixelData[pos]);
							sumG += weight * GetGValue(srcPixelData[pos]);
							sumB += weight * GetBValue(srcPixelData[pos]);
							sumW += weight;
						}
					}

					int dstPos = (int)(trgX * ratio) + (int)(trgY * ratio) * dstWidth;
					dstPixelData[dstPos] = RGB((BYTE)(sumR / sumW), (BYTE)(sumG / sumW), (BYTE)(sumB / sumW));
				}
			}
		}
	}
}


///<summary>
///Bicubicのウェイトの計算
///係数aは一般的な-1.0にするとアンダーシュート（オーバーシュート）が出るので-0.2に設定
///</summary>
double CResize::GetBicubicWeight(double d)
{
	double result = 0;
	double a = -0.2;

	if (d <= 1.0)
	{
		result = (a + 2) * abs(d * d * d) - (a + 3) * abs(d * d) + 1;
	}
	else if (d > 1.0 && d <= 2.0)
	{
		result = a * abs(d * d * d) - 5 * a * abs(d * d) + 8 * a * abs(d) - 4 * a;
	}
	else if (d > 2.0)
	{
		result = 0;
	}

	return result;
}

