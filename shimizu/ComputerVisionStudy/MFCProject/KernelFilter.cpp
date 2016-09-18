#include "stdafx.h"
#include "KernelFilter.h"
#include <algorithm>

CKernelFilter::CKernelFilter()
{
}


CKernelFilter::~CKernelFilter()
{
}


///<summary>
///	カーネルのセット
///</summary>
void CKernelFilter::SetKernel(FilterType filterType, std::vector<std::vector<int>> kernel, int normalize)
{
	this->filterType = filterType;
	this->kernel = kernel;
	this->normalize = normalize;
}


///<summary>
///	OpenCVを活用して簡単実装
///</summary>
void CKernelFilter::ProcessByFullOpenCV(CString filePath)
{
	//元画像読み込み
	cv::Mat srcImage = cv::imread(this->GetMultiBytePath(filePath));
	cv::Mat dstImage;
	cv::cvtColor(srcImage, dstImage, CV_BGR2BGRA);

	cv::namedWindow("フィルタ画像", cv::WINDOW_AUTOSIZE);
	cv::imshow("フィルタ画像", dstImage);
}


///<summary>
///	画像読み込み保存のみOpenCVを使用してピクセル操作はスクラッチ
///</summary>
void CKernelFilter::ProcessByPartOpenCV(CString filePath)
{
	//元画像読み込み
	cv::Mat srcImage = cv::imread(this->GetMultiBytePath(filePath));
	cv::Mat dstImage = cv::Mat(cv::Size(srcImage.cols, srcImage.rows), CV_8UC3);

	size_t offset = this->kernel.size() / 2;
	int r, g, b;
	cv::Vec3b color;

	for (int x = 0; x < srcImage.cols; x++)
	{
		for (int y = 0; y < srcImage.rows; y++)
		{
			r = g = b = 0;

			//畳み込み
			for (int i = 0; i < this->kernel.size(); i++)
			{
				for (int j = 0; j < this->kernel.size(); j++)
				{
					color = srcImage.at<cv::Vec3b>(y + i - offset, x + j - offset);
					r += kernel[i][j] * (int)color[2];
					g += kernel[i][j] * (int)color[1];
					b += kernel[i][j] * (int)color[0];
				}
			}

			dstImage.at<cv::Vec3b>(y, x) = cv::Vec3b(std::abs(b / normalize), std::abs(g / normalize), std::abs(r / normalize));
		}
	}

	cv::namedWindow("フィルタ画像", cv::WINDOW_AUTOSIZE);
	cv::imshow("フィルタ画像", dstImage);
}


///<summary>
///	OpenCVを全く使わずにフルスクラッチ
///</summary>
void CKernelFilter::ProcessByFullScratch(LPCOLORREF srcPixelData, BITMAPINFO* bmpInfo)
{
	UINT width = bmpInfo->bmiHeader.biWidth;
	UINT height = bmpInfo->bmiHeader.biHeight;

	LPCOLORREF dstPixelData = new COLORREF[width * height];

	int offset = this->kernel.size() / 2;
	int sumR, sumG, sumB;

	for (int x = offset; x < width - offset; x++)
	{
		for (int y = offset; y < height - offset; y++)
		{
			int srcPos = x + y * width;

			sumR = sumG = sumB = 0;

			//畳み込み
			for (int i = 0; i < this->kernel.size(); i++)
			{
				for (int j = 0; j < this->kernel.size(); j++)
				{
					int pos = (x + j - offset) + (y + i - offset) * width;
					sumR += kernel[i][j] * CUtility::GetR(srcPixelData[pos]);
					sumG += kernel[i][j] * CUtility::GetG(srcPixelData[pos]);
					sumB += kernel[i][j] * CUtility::GetB(srcPixelData[pos]);
				}
			}

			sumR = std::abs(sumR / normalize);
			sumG = std::abs(sumG / normalize);
			sumB = std::abs(sumB / normalize);

			sumR = std::min(sumR, 255);
			sumG = std::min(sumG, 255);
			sumB = std::min(sumB, 255);

			sumR = std::max(sumR, 0);
			sumG = std::max(sumG, 0);
			sumB = std::max(sumB, 0);

			dstPixelData[srcPos] = GetPixelValue(sumR, sumG, sumB);
		}
	}

	ShowPictureDlg(dstPixelData, bmpInfo);
	delete[] dstPixelData;
}