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

	//���摜�ǂݍ���
	cv::Mat image1 = cv::imread(path);

	cv::Mat resizeImg;
	//�摜�����T�C�Y����
	cv::resize(image1, resizeImg, cv::Size(), ratio, ratio, selectedAlgorithm);
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

	int dscWidth = width * ratio;
	int dscHeight = height * ratio;

	cv::Mat image2 = cv::Mat(cv::Size(dscWidth, dscHeight), CV_8UC3);

	for (int y = 0; y < dscHeight; y++)
	{
		for (int x = 0; x < dscWidth; x++)
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

	cv::namedWindow("���T�C�Y�摜(RGB����)", cv::WINDOW_AUTOSIZE);
	cv::imshow("���T�C�Y�摜(RGB����)", image2);

	cv::waitKey(0);
	cv::destroyAllWindows();
}


///<summary>
///	OpenCV��S���g�킸�Ƀt���X�N���b�`
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

	//�����Ək���͕�Ԃ̕K�v���Ȃ�����Nearest neighbor�ŏ���
	if (ratio <= 1.0)
	{
		ResizeByNearestNeighbor(width, height, dscWidth, dscHeight, ratio, srcPixelData, dscPixelData);
	}
	//�g��͊e�A���S���Y���ŏ���
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
			int srcPos = x + y * width;//��_

			int srcPosH = (x + 1) + y * width;//�E���̃s�N�Z���̈ʒu
			int srcPosV = x + (y + 1) * width;//�^���̃s�N�Z���̈ʒu

			//RGB���������i�������K�v�Ȃ̂�int�Ōv�Z���čŌ��BYTE�ɃL���X�g����j
			int red = (int)GetRValue(srcPixelData[srcPos]);
			int green = (int)GetGValue(srcPixelData[srcPos]);
			int blue = (int)GetBValue(srcPixelData[srcPos]);

			//��_�ƉE���̃s�N�Z���Ƃ̍���RGB��
			int diffRH = (int)GetRValue(srcPixelData[srcPosH]) - red;
			int diffHG = (int)GetGValue(srcPixelData[srcPosH]) - green;
			int diffHB = (int)GetBValue(srcPixelData[srcPosH]) - blue;

			//��_�Ɛ^���̃s�N�Z���Ƃ̍���RGB��
			int diffRV = (int)GetRValue(srcPixelData[srcPosV]) - red;
			int diffVG = (int)GetGValue(srcPixelData[srcPosV]) - green;
			int diffVB = (int)GetBValue(srcPixelData[srcPosV]) - blue;

			//��_(0)����ׂ̃s�N�Z��(1)�܂�1/ratio�X�e�b�v�ŕω�������
			for (double r = 0; isless(r, 1.0); r += (1 / ratio))//�����̔�r��C99�Œǉ����ꂽ���������_����r�}�N�����g�p
			{
				//�c�����̕��
				int dscPosV = (int)(x * ratio) + (int)((y + r) * ratio) * dscWidth;
				dscPixelData[dscPosV] = RGB(
					(BYTE)(red + diffRV * r), 
					(BYTE)(green + diffVG * r), 
					(BYTE)(blue + diffVB * r));

				//�������̕��
				int dscPosH = (int)((x + r) * ratio) + (int)(y * ratio) * dscWidth;
				dscPixelData[dscPosH] = RGB(
					(BYTE)(red + diffRH * r),
					(BYTE)(green + diffHG * r),
					(BYTE)(blue + diffHB * r));

				//��Ԃ����c�̃s�N�Z�������Ɉ�O�̃u���b�N�̉���������
				if (x != 0)
				{
					//��O�̃u���b�N�̈ʒu
					int prevPosV = (int)((x - 1) * ratio) + (int)((y + r) * ratio) * dscWidth;

					//�������K�v�Ȃ̂�int�Ōv�Z���čŌ��BYTE�ɃL���X�g����
					int prevR = (int)GetRValue(dscPixelData[prevPosV]);
					int prevG = (int)GetGValue(dscPixelData[prevPosV]);
					int prevB = (int)GetBValue(dscPixelData[prevPosV]);

					int diffR = (int)GetRValue(dscPixelData[dscPosV]) - prevR;
					int diffG = (int)GetGValue(dscPixelData[dscPosV]) - prevG;
					int diffB = (int)GetBValue(dscPixelData[dscPosV]) - prevB;

					//��_(0)����ׂ̃s�N�Z��(1)�܂�1/ratio�X�e�b�v�ŕω�������i�������̕�ԁj
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