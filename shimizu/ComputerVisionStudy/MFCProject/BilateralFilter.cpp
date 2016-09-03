#include "stdafx.h"
#include "BilateralFilter.h"


CBilateralFilter::CBilateralFilter()
{
}


CBilateralFilter::~CBilateralFilter()
{
}


///<summary>
///	カーネルのセット
///</summary>
void CBilateralFilter::SetKernel(int kernelSize)
{
	this->kernelSize = kernelSize;
}


///<summary>
///	OpenCVを活用して簡単実装
///</summary>
void CBilateralFilter::ProcessByFullOpenCV(CString filePath)
{
	//元画像読み込み
	std::string path = this->GetMultiBytePath(filePath);
	cv::Mat src = cv::imread(path, 1);
	cv::Mat dest;

	int color_sigma = 35;
	int space_sigma = 5;
	cv::bilateralFilter(src, dest, this->kernelSize, color_sigma, space_sigma);

	//表示
	cv::namedWindow("バイラテラルフィルタ画像", cv::WINDOW_AUTOSIZE);
	cv::imshow("バイラテラルフィルタ画像", dest);
}

///<summary>
///	画像読み込み保存のみOpenCVを使用してピクセル操作はスクラッチ
///</summary>
void CBilateralFilter::ProcessByPartOpenCV(CString filePath)
{
	AfxMessageBox(L"未実装");
}

///<summary>
///	OpenCVを全く使わずにフルスクラッチ
///</summary>
void CBilateralFilter::ProcessByFullScratch(LPCOLORREF srcPixelData, BITMAPINFO* bmpInfo)
{
	UINT width = bmpInfo->bmiHeader.biWidth;
	UINT height = bmpInfo->bmiHeader.biHeight;

	LPCOLORREF dstPixelData = new COLORREF[width * height];

	int offset = this->kernelSize / 2;
	int size = this->kernelSize;

	double sumR, sumG, sumB;

	double sigma1 = 0.8;
	double weight1 = -2.0 * std::pow(sigma1, 2.0);

	double sigma2 = 0.3;
	double weight2 = -2.0 * std::pow(sigma2, 2.0);

	//double normalR = 0;
	//CString s;

	//for (int i = 0; i < this->kernel.size(); i++)
	//{
	//	for (int j = 0; j < this->kernel.size(); j++)
	//	{
	//		double t1 = std::pow((double)(j - offset), 2.0);
	//		double t2 = std::pow((double)(i - offset), 2.0);
	//		double diffD = std::exp((t1 + t2) / weight1);
	//		normalR += diffD;

	//		s.Format(L"%lf %lf %lf %lf", t1, t2, diffD, normalR);
	//		AfxMessageBox(s);
	//	}
	//}
	//s.Format(L"%lf", normalR);
	//AfxMessageBox(s);

	for (int x = offset; x < width - offset; x++)
	{
		for (int y = offset; y < height - offset; y++)
		{
			int srcPos = x + y * width;

			sumR = sumG = sumB = 0;

			//正規化用の分母の値を算出
			double normalR = 0;
			double normalG = 0;
			double normalB = 0;

			//畳み込み
			for (int i = 0; i < this->kernelSize; i++)
			{
				for (int j = 0; j < this->kernelSize; j++)
				{
					int pos = (x + j - offset) + (y + i - offset) * width;

					int r = CUtility::GetR(srcPixelData[pos]);
					int g = CUtility::GetG(srcPixelData[pos]);
					int b = CUtility::GetB(srcPixelData[pos]);

					double diffR = std::exp(std::pow((double)CUtility::GetR(srcPixelData[srcPos]) - (double)r, 2.0) / weight2);
					double diffG = std::exp(std::pow((double)CUtility::GetG(srcPixelData[srcPos]) - (double)g, 2.0) / weight2);
					double diffB = std::exp(std::pow((double)CUtility::GetB(srcPixelData[srcPos]) - (double)b, 2.0) / weight2);
					
					double diffD = std::exp((std::pow((double)(j - offset), 2.0) + std::pow((double)(i - offset), 2.0)) / weight1);

					double tmpR = diffD * diffR;
					double tmpG = diffD * diffG;
					double tmpB = diffD * diffB;

					sumR += (tmpR * r);
					sumG += (tmpG * g);
					sumB += (tmpB * b);

					normalR += tmpR;
					normalG += tmpG;
					normalB += tmpB;
				}
			}

			int resR = (int)(sumR / normalR);
			int resG = (int)(sumG / normalG);
			int resB = (int)(sumB / normalB);

			resR = std::min(resR, 255);
			resG = std::min(resG, 255);
			resB = std::min(resB, 255);

			resR = std::max(resR, 0);
			resG = std::max(resG, 0);
			resB = std::max(resB, 0);

			dstPixelData[srcPos] = GetPixelValue(resR, resG, resB);
		}
	}

	ShowPictureDlg(dstPixelData, bmpInfo);
	delete[] dstPixelData;
}
