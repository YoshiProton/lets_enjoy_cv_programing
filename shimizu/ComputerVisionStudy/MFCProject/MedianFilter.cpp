#include "stdafx.h"
#include "MedianFilter.h"


CMedianFilter::CMedianFilter()
{
}


CMedianFilter::~CMedianFilter()
{
}


///<summary>
///	�J�[�l���̃Z�b�g
///</summary>
void CMedianFilter::SetKernel(int size)
{
	this->kernelSize = size;
}


///<summary>
///	OpenCV�����p���ĊȒP����
///</summary>
void CMedianFilter::ProcessByFullOpenCV(CString filePath)
{
}

///<summary>
///	�摜�ǂݍ��ݕۑ��̂�OpenCV���g�p���ăs�N�Z������̓X�N���b�`
///</summary>
void CMedianFilter::ProcessByPartOpenCV(CString filePath)
{
}

///<summary>
///	OpenCV��S���g�킸�Ƀt���X�N���b�`
///</summary>
void CMedianFilter::ProcessByFullScratch(LPCOLORREF srcPixelData, BITMAPINFO* bmpInfo)
{
	UINT width = bmpInfo->bmiHeader.biWidth;
	UINT height = bmpInfo->bmiHeader.biHeight;

	LPCOLORREF dstPixelData = new COLORREF[width * height];

	int offset = this->kernelSize / 2;
	int size = this->kernelSize;
	int arrySize = size * size;

	int* r = new int[arrySize];
	int* g = new int[arrySize];
	int* b = new int[arrySize];

	for (int x = offset; x < width - offset; x++)
	{
		for (int y = offset; y < height - offset; y++)
		{
			int srcPos = x + y * width;

			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					int pos = (x + j - offset) + (y + i - offset) * width;
					int arryPos = j + i * size;

					r[arryPos] = CUtility::GetR(srcPixelData[pos]);
					g[arryPos] = CUtility::GetG(srcPixelData[pos]);
					b[arryPos] = CUtility::GetB(srcPixelData[pos]);
				}
			}

			std::sort(&r[0], &r[arrySize]);
			std::sort(&g[0], &g[arrySize]);
			std::sort(&b[0], &b[arrySize]);

			int medianR = r[arrySize / 2];
			int medianG = g[arrySize / 2];
			int medianB = b[arrySize / 2];

			dstPixelData[srcPos] = GetPixelValue(medianR, medianG, medianB);
		}
	}

	delete[] r, g, b;

	ShowPictureDlg(dstPixelData, bmpInfo);
	delete[] dstPixelData;
}