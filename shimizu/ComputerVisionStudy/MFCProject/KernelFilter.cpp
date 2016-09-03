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
///	�J�[�l���̃Z�b�g
///</summary>
void CKernelFilter::SetKernel(FilterType filterType, std::vector<std::vector<int>> kernel, int normalize)
{
	this->filterType = filterType;
	this->kernel = kernel;
	this->normalize = normalize;
}


///<summary>
///	OpenCV�����p���ĊȒP����
///</summary>
void CKernelFilter::ProcessByFullOpenCV(CString filePath)
{
	//���摜�ǂݍ���
	cv::Mat srcImage = cv::imread(this->GetMultiBytePath(filePath));
	cv::Mat dstImage;
	cv::cvtColor(srcImage, dstImage, CV_BGR2BGRA);

	cv::namedWindow("�t�B���^�摜", cv::WINDOW_AUTOSIZE);
	cv::imshow("�t�B���^�摜", dstImage);
}


///<summary>
///	�摜�ǂݍ��ݕۑ��̂�OpenCV���g�p���ăs�N�Z������̓X�N���b�`
///</summary>
void CKernelFilter::ProcessByPartOpenCV(CString filePath)
{
	//���摜�ǂݍ���
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

			//��ݍ���
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

	cv::namedWindow("�t�B���^�摜", cv::WINDOW_AUTOSIZE);
	cv::imshow("�t�B���^�摜", dstImage);
}


///<summary>
///	OpenCV��S���g�킸�Ƀt���X�N���b�`
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

			//��ݍ���
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