#include "stdafx.h"
#include "Grayscale.h"


CGrayscale::CGrayscale()
{
}


CGrayscale::~CGrayscale()
{
}


///<summary>
///	OpenCV�����p���ĊȒP����
///</summary>
void CGrayscale::ProcessByFullOpenCV(CString filePath)
{
	std::string path = this->GetMultiBytePath(filePath);

	//���摜�ǂݍ���
	cv::Mat srcImage = cv::imread(path);

	//cvtColor�֐��ŕϊ�
	cv::Mat dstImage1;
	cvtColor(srcImage, dstImage1, CV_RGB2GRAY);
	cv::namedWindow("�O���C�X�P�[���摜(cvtColor�֐��g�p)", cv::WINDOW_AUTOSIZE);
	cv::imshow("�O���C�X�P�[���摜(cvtColor�֐��g�p)", dstImage1);

	//�ǂݍ��ݎ��I�v�V�����w��
	cv::Mat dstImage2 = cv::imread(path, cv::IMREAD_GRAYSCALE);
	cv::namedWindow("�O���C�X�P�[���摜(�ǂݍ��ݎ��ɕϊ�)", cv::WINDOW_AUTOSIZE);
	cv::imshow("�O���C�X�P�[���摜(�ǂݍ��ݎ��ɕϊ�)", dstImage2);

	//�t�@�C���ɕۑ�
	char lpDest[MAX_PATH] = {};
	this->GetNewFilePath((LPSTR)path.c_str(), "grayscale.ocv1.jpg", lpDest);
	cv::imwrite(lpDest, dstImage1);
	//�t�@�C���ɕۑ�
	this->GetNewFilePath((LPSTR)path.c_str(), "grayscale.ocv2.jpg", lpDest);
	cv::imwrite(lpDest, dstImage2);
}


///<summary>
///	�摜�ǂݍ��ݕۑ��̂�OpenCV���g�p���ăs�N�Z������̓X�N���b�`
///</summary>
void CGrayscale::ProcessByPartOpenCV(CString filePath)
{
	std::string path = this->GetMultiBytePath(filePath);

	//���摜�ǂݍ���
	cv::Mat srcImage = cv::imread(path);

	//�s�N�Z������ŃO���C�X�P�[����
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

	cv::namedWindow("�O���C�X�P�[���摜(�s�N�Z������)", cv::WINDOW_AUTOSIZE);
	cv::imshow("�O���C�X�P�[���摜(�s�N�Z������)", dstImage);

	//ShowPictureDlg(dstImage);

	//�t�@�C���ɕۑ�
	char lpDest[MAX_PATH] = {};
	this->GetNewFilePath((LPSTR)path.c_str(), "grayscale.hocv.jpg", lpDest);
	cv::imwrite(lpDest, dstImage);
}


///<summary>
///	OpenCV��S���g�킸�Ƀt���X�N���b�`
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