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

	int dstWidth = width * ratio;
	int dstHeight = height * ratio;

	cv::Mat image2 = cv::Mat(cv::Size(dstWidth, dstHeight), CV_8UC3);

	for (int y = 0; y < dstHeight; y++)
	{
		for (int x = 0; x < dstWidth; x++)
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

	//�����Ək���͕�Ԃ̕K�v���Ȃ�����Nearest neighbor�ŏ���
	if (ratio <= 1.0)
	{
		ResizeByNearestNeighbor(width, height, dstWidth, dstHeight, ratio, srcPixelData, dstPixelData);
	}
	//�g��͊e�A���S���Y���ŏ���
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
			//��_
			int srcPos = x + y * width;
			//�E���̃s�N�Z���̈ʒu
			int srcPosH = (x + 1) + y * width;
			//�^���̃s�N�Z���̈ʒu
			int srcPosV = x + (y + 1) * width;

			//RGB���������i�������K�v�Ȃ̂�int�Ōv�Z���čŌ��BYTE�ɃL���X�g����j
			int srcR = (int)GetRValue(srcPixelData[srcPos]);
			int srcG = (int)GetGValue(srcPixelData[srcPos]);
			int srcB = (int)GetBValue(srcPixelData[srcPos]);

			//��_�ƉE���̃s�N�Z���Ƃ̍���RGB�ŋ��߂�
			int diffRH = (int)GetRValue(srcPixelData[srcPosH]) - srcR;
			int diffGH = (int)GetGValue(srcPixelData[srcPosH]) - srcG;
			int diffBH = (int)GetBValue(srcPixelData[srcPosH]) - srcB;

			//��_�Ɛ^���̃s�N�Z���Ƃ̍���RGB�ŋ��߂�
			int diffRV = (int)GetRValue(srcPixelData[srcPosV]) - srcR;
			int diffGV = (int)GetGValue(srcPixelData[srcPosV]) - srcG;
			int diffBV = (int)GetBValue(srcPixelData[srcPosV]) - srcB;

			//�g���̃s�N�Z���̈ʒu�̌��摜�ł̈ʒu�����߂ăX�L����
			for (int n = 0; n < ratio; n++)
			{
				double linear = n / ratio;

				//�c�����̕��
				int dstPosV = (int)(x * ratio) + (int)(y * ratio + n) * dstWidth;
				dstPixelData[dstPosV] = RGB((BYTE)(srcR + diffRV * linear), (BYTE)(srcG + diffGV * linear), (BYTE)(srcB + diffBV * linear));

				//�������̕��
				int dstPosH = (int)(x * ratio + n) + (int)(y * ratio) * dstWidth;
				dstPixelData[dstPosH] = RGB((BYTE)(srcR + diffRH * linear), (BYTE)(srcG + diffGH * linear), (BYTE)(srcB + diffBH * linear));

				//��Ԃ����c�̃s�N�Z�������Ɉ�O�̃u���b�N�̉���������

				//�c�����̃s�N�Z���̈�O�̃u���b�N�̈ʒu
				int prevPosV = (int)((x - 1) * ratio) + (int)(y * ratio + n) * dstWidth;

				//RGB���������i�������K�v�Ȃ̂�int�Ōv�Z���čŌ��BYTE�ɃL���X�g����j
				int prevR = (int)GetRValue(dstPixelData[prevPosV]);
				int prevG = (int)GetGValue(dstPixelData[prevPosV]);
				int prevB = (int)GetBValue(dstPixelData[prevPosV]);

				//��_�ƉE���̃s�N�Z���Ƃ̍���RGB�ŋ��߂�
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
			//�g���̃s�N�Z���̈ʒu�̌��摜�ł̈ʒu�����߂ăX�L����
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
///Bicubic�̃E�F�C�g�̌v�Z
///�W��a�͈�ʓI��-1.0�ɂ���ƃA���_�[�V���[�g�i�I�[�o�[�V���[�g�j���o��̂�-0.2�ɐݒ�
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

