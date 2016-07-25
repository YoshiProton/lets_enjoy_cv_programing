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
void CGrayscale::ProcessFullOpenCV(CString filePath)
{
	std::string path = this->GetMultiBytePath(filePath);

	//���摜�ǂݍ���
	cv::Mat image1 = cv::imread(path);

	//cvtColor�֐��ŕϊ�
	cv::Mat image3;
	cvtColor(image1, image3, CV_RGB2GRAY);
	cv::namedWindow("�O���C�X�P�[���摜(cvtColor�֐��g�p)", cv::WINDOW_AUTOSIZE);
	cv::imshow("�O���C�X�P�[���摜(cvtColor�֐��g�p)", image3);

	//�ǂݍ��ݎ��I�v�V�����w��
	cv::Mat image4 = cv::imread(path, cv::IMREAD_GRAYSCALE);
	cv::namedWindow("�O���C�X�P�[���摜(�ǂݍ��ݎ��ɕϊ�)", cv::WINDOW_AUTOSIZE);
	cv::imshow("�O���C�X�P�[���摜(�ǂݍ��ݎ��ɕϊ�)", image4);

	cv::waitKey(0);
	cv::destroyAllWindows();

	char lpDest[MAX_PATH] = {};
	this->GetNewFilePath((LPSTR)path.c_str(), "grayscale1.jpg", lpDest);
	cv::imwrite(lpDest, image3);
}


///<summary>
///	�摜�ǂݍ��ݕۑ��̂�OpenCV���g�p���ăs�N�Z������̓X�N���b�`
///</summary>
void CGrayscale::ProcessHalfOpenCV(CString filePath)
{
	std::string path = this->GetMultiBytePath(filePath);

	//���摜�ǂݍ���
	cv::Mat image1 = cv::imread(path);

	//�s�N�Z������ŃO���C�X�P�[����
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

	cv::namedWindow("�O���C�X�P�[���摜(�s�N�Z������)", cv::WINDOW_AUTOSIZE);
	cv::imshow("�O���C�X�P�[���摜(�s�N�Z������)", image2);

	cv::waitKey(0);
	cv::destroyAllWindows();
}


///<summary>
///	OpenCV��S���g�킸�Ƀt���X�N���b�`
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