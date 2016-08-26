#include "stdafx.h"
#include "Original.h"


COriginal::COriginal()
{
}


COriginal::~COriginal()
{
}


///<summary>
///	OpenCV�����p���ĊȒP����
///</summary>
void COriginal::ProcessByFullOpenCV(CString filePath)
{
	std::string path = this->GetMultiBytePath(filePath);
	cv::Mat cvImage = cv::imread(path);
	cv::namedWindow("���摜", cv::WINDOW_AUTOSIZE);
	cv::imshow("���摜", cvImage);
}


///<summary>
///	�摜�ǂݍ��ݕۑ��̂�OpenCV���g�p���ăs�N�Z������̓X�N���b�`
///</summary>
void COriginal::ProcessByPartOpenCV(CString filePath)
{
	//���摜�ǂݍ���
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

	cv::namedWindow("���摜", cv::WINDOW_AUTOSIZE);
	cv::imshow("���摜", dstImage);
}


///<summary>
///	OpenCV��S���g�킸�Ƀt���X�N���b�`
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