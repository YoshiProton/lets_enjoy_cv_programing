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
void CResize::ProcessByFullOpenCV(CString filePath)
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
	cv::Mat srcImage = cv::imread(path);

	cv::Mat dstImage;
	//�摜�����T�C�Y����
	cv::resize(srcImage, dstImage, cv::Size(), ratio, ratio, selectedAlgorithm);
	cv::namedWindow("���T�C�Y�摜(resize�֐�)", cv::WINDOW_AUTOSIZE);
	cv::imshow("���T�C�Y�摜(resize�֐�)", dstImage);

	//�t�@�C����ۑ�����
	char lpDest[MAX_PATH] = {};
	this->GetNewFilePath((LPSTR)path.c_str(), "size.ocv.jpg", lpDest);
	cv::imwrite(lpDest, dstImage);
}


///<summary>
///	�摜�ǂݍ��ݕۑ��̂�OpenCV���g�p���ăs�N�Z������̓X�N���b�`
///</summary>
void CResize::ProcessByPartOpenCV(CString filePath)
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
	cv::Mat srcImage = cv::imread(path);

	//RGB����
	int x, y;
	uchar r1, g1, b1, r2, g2, b2, color2;
	int width = srcImage.cols;
	int height = srcImage.rows;

	int dstWidth = width * ratio;
	int dstHeight = height * ratio;

	cv::Mat dstImage = cv::Mat(cv::Size(dstWidth, dstHeight), CV_8UC3);

	//�����Ək���͕�Ԃ̕K�v���Ȃ�����Nearest neighbor�ŏ���
	if (ratio <= 1.0)
	{
		ResizeByNearestNeighbor(width, height, dstWidth, dstHeight, ratio, &srcImage, &dstImage);
	}
	//�g��͊e�A���S���Y���ŏ���
	else
	{
		//Nearest neighbor
		if (algorithm == Algorithm::NearestNeighbor)
		{
			ResizeByNearestNeighbor(width, height, dstWidth, dstHeight, ratio, &srcImage, &dstImage);
		}
		//Bilinear
		else if (algorithm == Algorithm::Bilinear)
		{
			ResizeByBilinear(width, height, dstWidth, dstHeight, ratio, &srcImage, &dstImage);
		}
		//Bicubic
		else if (algorithm == Algorithm::Bicubic)
		{
			ResizeByBicubic(width, height, dstWidth, dstHeight, ratio, &srcImage, &dstImage);
		}
	}

	cv::namedWindow("���T�C�Y�摜(RGB����)", cv::WINDOW_AUTOSIZE);
	cv::imshow("���T�C�Y�摜(RGB����)", dstImage);

	//�t�@�C����ۑ�����
	char lpDest[MAX_PATH] = {};
	this->GetNewFilePath((LPSTR)path.c_str(), "size.hocv.jpg", lpDest);
	cv::imwrite(lpDest, dstImage);
}


///<summary>
///	OpenCV��S���g�킸�Ƀt���X�N���b�`
///</summary>
void CResize::ProcessByFullScratch(LPCOLORREF srcPixelData, BITMAPINFO* bmpInfo)
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
	UINT height = bmpInfo->bmiHeader.biHeight;

	UINT dstWidth = width * ratio;
	UINT dstHeight = height * ratio;

	BITMAPINFO bmpInf;
	bmpInf.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInf.bmiHeader.biWidth = (INT)dstWidth;
	bmpInf.bmiHeader.biHeight = (INT)dstHeight;
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
///	Nearest neighbor�iOpenCV�p�j
///</summary>
void CResize::ResizeByNearestNeighbor(int width, int height, int dstWidth, int dstHeight, double ratio, cv::Mat* pSrcImage, cv::Mat* pDstImage)
{
	for (int x = 0; x < dstWidth; x++)
	{
		for (int y = 0; y < dstHeight; y++)
		{
			int srcX = (int)(x / ratio);
			int srcY = (int)(y / ratio);

			pDstImage->at<cv::Vec3b>(y, x) = pSrcImage->at<cv::Vec3b>(srcY, srcX);
		}
	}
}


///<summary>
///	Nearest neighbor�iWin32�p�j
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
///	Nearest neighbor�iOpenCV�p�j
///</summary>
void CResize::ResizeByBilinear(int width, int height, int dstWidth, int dstHeight, double ratio, cv::Mat* pSrcImage, cv::Mat* pDstImage)
{
	for (int x = 1; x < width - 1; x++)
	{
		for (int y = 0; y < height - 1; y++)
		{
			//��_
			cv::Vec3b color = pSrcImage->at<cv::Vec3b>(y, x);
			//�E���̃s�N�Z���̈ʒu
			cv::Vec3b colorH = pSrcImage->at<cv::Vec3b>(y, x + 1);
			//�^���̃s�N�Z���̈ʒu
			cv::Vec3b colorV = pSrcImage->at<cv::Vec3b>(y + 1, x);

			//RGB���������i�������K�v�Ȃ̂�int�Ōv�Z���čŌ��uchar�ɃL���X�g����j
			int srcR = (int)color[2];
			int srcG = (int)color[1];
			int srcB = (int)color[0];

			//��_�ƉE���̃s�N�Z���Ƃ̍���RGB�ŋ��߂�
			int diffRH = (int)colorH[2] - srcR;
			int diffGH = (int)colorH[1] - srcG;
			int diffBH = (int)colorH[0] - srcB;

			//��_�Ɛ^���̃s�N�Z���Ƃ̍���RGB�ŋ��߂�
			int diffRV = (int)colorV[2] - srcR;
			int diffGV = (int)colorV[1] - srcG;
			int diffBV = (int)colorV[0] - srcB;

			//�g���̃s�N�Z���̈ʒu�̌��摜�ł̈ʒu�����߂ăX�L����
			for (int n = 0; n < ratio; n++)
			{
				double linear = n / ratio;

				//�c�����̕��
				pDstImage->at<cv::Vec3b>((int)(y * ratio + n) + n, (int)(x * ratio)) 
					= cv::Vec3b(
					(uchar)(srcB + diffBV * linear), 
					(uchar)(srcG + diffGV * linear), 
					(uchar)(srcR + diffRV * linear));

				//�������̕��
				pDstImage->at<cv::Vec3b>((int)(y * ratio), (int)(x * ratio + n)) 
					= cv::Vec3b(
					(uchar)(srcB + diffBH * linear),
					(uchar)(srcG + diffGH * linear), 
					(uchar)(srcR + diffRH * linear));

				//��Ԃ����c�̃s�N�Z�������Ɉ�O�̃u���b�N�̉���������

				//�c�����̃s�N�Z���̈�O�̃u���b�N�̈ʒu
				cv::Vec3b prevColorV = pDstImage->at<cv::Vec3b>((int)(y * ratio + n), (int)((x - 1) * ratio));
				//RGB���������i�������K�v�Ȃ̂�int�Ōv�Z���čŌ��uchar�ɃL���X�g����j
				int prevR = (int)prevColorV[2];
				int prevG = (int)prevColorV[1];
				int prevB = (int)prevColorV[0];

				//��_�ƉE���̃s�N�Z���Ƃ̍���RGB�ŋ��߂�
				cv::Vec3b dstColorV = pDstImage->at<cv::Vec3b>((int)(y * ratio + n) + n, (int)(x * ratio));
				int diffR = (int)dstColorV[2] - prevR;
				int diffG = (int)dstColorV[1] - prevG;
				int diffB = (int)dstColorV[0] - prevB;

				for (int nx = 1; nx < ratio; nx++)
				{
					linear = nx / ratio;
					pDstImage->at<cv::Vec3b>((int)((y * ratio) + n) + n, (int)((x - 1) * ratio + nx)) 
						= cv::Vec3b(
						(uchar)(prevB + diffB * linear),
						(uchar)(prevG + diffG * linear),
						(uchar)(prevR + diffR * linear));
				}
			}
		}
	}
}


///<summary>
///	Bilinear�iWin32�p�j
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
			int srcR = (int)CUtility::GetR(srcPixelData[srcPos]);
			int srcG = (int)CUtility::GetG(srcPixelData[srcPos]);
			int srcB = (int)CUtility::GetB(srcPixelData[srcPos]);

			//��_�ƉE���̃s�N�Z���Ƃ̍���RGB�ŋ��߂�
			int diffRH = (int)CUtility::GetR(srcPixelData[srcPosH]) - srcR;
			int diffGH = (int)CUtility::GetG(srcPixelData[srcPosH]) - srcG;
			int diffBH = (int)CUtility::GetB(srcPixelData[srcPosH]) - srcB;

			//��_�Ɛ^���̃s�N�Z���Ƃ̍���RGB�ŋ��߂�
			int diffRV = (int)CUtility::GetR(srcPixelData[srcPosV]) - srcR;
			int diffGV = (int)CUtility::GetG(srcPixelData[srcPosV]) - srcG;
			int diffBV = (int)CUtility::GetB(srcPixelData[srcPosV]) - srcB;

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
				int prevR = (int)CUtility::GetR(dstPixelData[prevPosV]);
				int prevG = (int)CUtility::GetG(dstPixelData[prevPosV]);
				int prevB = (int)CUtility::GetB(dstPixelData[prevPosV]);

				//��_�ƉE���̃s�N�Z���Ƃ̍���RGB�ŋ��߂�
				int diffR = (int)CUtility::GetR(dstPixelData[dstPosV]) - prevR;
				int diffG = (int)CUtility::GetG(dstPixelData[dstPosV]) - prevG;
				int diffB = (int)CUtility::GetB(dstPixelData[dstPosV]) - prevB;

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
///	Bicubic�iOpenCV�p�j
///</summary>
void CResize::ResizeByBicubic(int width, int height, int dstWidth, int dstHeight, double ratio, cv::Mat* pSrcImage, cv::Mat* pDstImage)
{
	double dx[4];
	double dy[4];
	double trgX;
	double trgY;

	for (int x = 1; x < width - 3; x++)
	{
		for (int y = 1; y < height - 3; y++)
		{
			//�g���̃s�N�Z���̈ʒu�̌��摜�ł̈ʒu�����߂ăX�L����
			for (int nx = 0; nx < ratio; nx++)
			{
				trgX = x + nx / ratio;

				dx[0] = 1 + trgX - (x + 1);
				dx[1] = trgX - (x + 1);
				dx[2] = (x + 1) + 1 - trgX;
				dx[3] = (x + 1) + 2 - trgX;

				for (int ny = 0; ny < ratio; ny++)
				{
					trgY = y + ny / ratio;

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
							int posX = (x + i - 1);
							int posY = (y + j - 1);

							double weight = GetBicubicWeight(dx[i]) * GetBicubicWeight(dy[j]);

							cv::Vec3b color = pSrcImage->at<cv::Vec3b>(posY, posX);

							sumR += weight * color[2];
							sumG += weight * color[1];
							sumB += weight * color[0];
							sumW += weight;
						}
					}
					pDstImage->at<cv::Vec3b>((int)(trgY * ratio), (int)(trgX * ratio)) 
						= cv::Vec3b(
						(uchar)(sumB / sumW), 
						(uchar)(sumG / sumW), 
						(uchar)(sumR / sumW));
				}
			}
		}
	}
}


///<summary>
///	Bicubic�iWin32�p�j
///</summary>
void CResize::ResizeByBicubic(UINT width, UINT height, UINT dstWidth, UINT dstHeight, double ratio, LPCOLORREF srcPixelData, LPCOLORREF dstPixelData)
{
	double dx[4];
	double dy[4];
	double trgX;
	double trgY;

	for (int x = 1; x < width - 3; x++)
	{
		for (int y = 1; y < height - 3; y++)
		{
			//�g���̃s�N�Z���̈ʒu�̌��摜�ł̈ʒu�����߂ăX�L����
			for (int nx = 0; nx < ratio; nx++)
			{
				trgX = x + nx / ratio;

				dx[0] = 1 + trgX - (x + 1);
				dx[1] = trgX - (x + 1);
				dx[2] = (x + 1) + 1 - trgX;
				dx[3] = (x + 1) + 2 - trgX;

				for (int ny = 0; ny < ratio; ny++)
				{
					trgY = y + ny / ratio;

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

							sumR += weight * CUtility::GetR(srcPixelData[pos]);
							sumG += weight * CUtility::GetG(srcPixelData[pos]);
							sumB += weight * CUtility::GetB(srcPixelData[pos]);
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

