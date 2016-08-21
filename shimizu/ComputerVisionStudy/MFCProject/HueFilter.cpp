#include "stdafx.h"
#include "HueFilter.h"
#include "HueFilterDlg.h"
#include "Utility.h"

CHueFilter::CHueFilter()
{
}


CHueFilter::~CHueFilter()
{
}


///<summary>
/// �ۑ�2��4
///	OpenCV�����p���ĊȒP����
///</summary>
void CHueFilter::ProcessByOpenCV(CString filePath)
{
	std::string path = this->GetMultiBytePath(filePath);
	cv::Mat srcImage = cv::imread(path);

	cv::Mat skinImage = cv::Mat(cv::Size(srcImage.cols, srcImage.rows), CV_8UC3);
	//cv::Mat smoothImage;
	cv::Mat hsvImage;

	skinImage = cv::Scalar(0, 0, 0);
	//cv::medianBlur(srcImage, smoothImage, 7);	//�m�C�Y������̂ŕ�����
	cv::cvtColor(srcImage, hsvImage, CV_BGR2HSV);	//HSV�ɕϊ�		
	for (int y = 0; y<srcImage.rows;y++)
	{
		for (int x = 0; x < srcImage.cols; x++)
		{
			int pos = x * 3 + y * hsvImage.step;
			//H��0����15�͈͓̔��Ȃ�f�[�^���R�s�[������ȊO�͉������Ȃ�
			if (hsvImage.data[pos] >= 0 && hsvImage.data[pos] <= 15)
			{
				skinImage.data[pos] = srcImage.data[pos];
				skinImage.data[pos + 1] = srcImage.data[pos + 1];
				skinImage.data[pos + 2] = srcImage.data[pos + 2];
			}
		}
	}

	cv::namedWindow("���F���o�摜", cv::WINDOW_AUTOSIZE);
	cv::imshow("���F���o�摜", skinImage);

	//�t�@�C����ۑ�
	char lpDest[MAX_PATH] = {};
	this->GetNewFilePath((LPSTR)path.c_str(), "skin.ocv.jpg", lpDest);
	cv::imwrite(lpDest, skinImage);
}

///<summary>
///	OpenCV��S���g�킸�Ƀt���X�N���b�`
///</summary>
void CHueFilter::ProcessByScratch(LPCOLORREF srcPixelData, BITMAPINFO* bmpInfo)
{
	int start;
	int end;
	CHueFilterDlg dlg;
	dlg.SetValues(&start, &end);
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	UINT width = bmpInfo->bmiHeader.biWidth;
	UINT height = bmpInfo->bmiHeader.biHeight;

	LPCOLORREF dstPixelData = new COLORREF[width * height];

	for (int i = 0; i < width * height; i++)
	{
		BYTE r = CUtility::GetR(srcPixelData[i]);
		BYTE g = CUtility::GetG(srcPixelData[i]);
		BYTE b = CUtility::GetB(srcPixelData[i]);

		int h, s, v;
		CUtility::ConvertRGBtoHSV(r, g, b, &h, &s, &v);

		if (h >= start && h <= end)
		{
			dstPixelData[i] = srcPixelData[i];
		}
		else
		{
			dstPixelData[i] = RGB(0, 0, 0);
		}
	}

	ShowPictureDlg(dstPixelData, bmpInfo);

	delete[] dstPixelData;
}