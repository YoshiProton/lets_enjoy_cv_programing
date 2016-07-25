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
///	OpenCV�����p���ĊȒP����
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

	//���摜�ǂݍ���
	cv::Mat image1 = cv::imread(path);

	cv::Mat resizeImg;
	//�摜�����T�C�Y����
	cv::resize(image1, resizeImg, cv::Size(), ratio, ratio, algorithm);
	cv::namedWindow("���T�C�Y�摜(resize�֐�)", cv::WINDOW_AUTOSIZE);
	cv::imshow("���T�C�Y�摜(resize�֐�)", resizeImg);

	cv::waitKey(0);
	cv::destroyAllWindows();

	char lpDest[MAX_PATH] = {};
	this->GetNewFilePath((LPSTR)path.c_str(), "size1.jpg", lpDest);
	cv::imwrite(lpDest, resizeImg);
}


///<summary>
///	�摜�ǂݍ��ݕۑ��̂�OpenCV���g�p���ăs�N�Z������̓X�N���b�`
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

	//���摜�ǂݍ���
	cv::Mat image1 = cv::imread(path);

	//RGB����
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

			//���{����яk���͕�Ԃ̕K�v���Ȃ�����Nearest neighbor�̂�
			if (ratio <= 1.0)
			{
				image2.at<cv::Vec3b>(y, x) = image1.at<cv::Vec3b>(oldY, oldX);
			}
			//�g��
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

	cv::namedWindow("���T�C�Y�摜(RGB����)", cv::WINDOW_AUTOSIZE);
	cv::imshow("���T�C�Y�摜(RGB����)", image2);

	cv::waitKey(0);
	cv::destroyAllWindows();
}


///<summary>
///	OpenCV��S���g�킸�Ƀt���X�N���b�`
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

			//���{����яk���͕�Ԃ̕K�v���Ȃ�����Nearest neighbor�̂�
			if (ratio <= 1.0)
			{
				lpcrPixelData2[newXY] = lpcrPixelData[oldXY];
			}
			//�g��
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