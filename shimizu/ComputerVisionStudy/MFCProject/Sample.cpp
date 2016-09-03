#include "stdafx.h"
#include "Sample.h"
#include "ColorSpaceDlg.h"

#define _USE_MATH_DEFINES
#include <math.h>

CSample::CSample()
{
}


CSample::~CSample()
{
}



///<summary>
///	
///</summary>
void CSample::CreateColorSpaceImage(CString filePath)
{
	////全部OpenCVでやる方式（RBG<-->HSV変換）
	//cv::Mat srcImg(256, 256, CV_8UC3, cv::Scalar(100, 100, 100));
	//cv::Mat dstImg(256, 256, CV_8UC3);
	//cv::cvtColor(srcImg, dstImg, cv::COLOR_HSV2BGR);
	//cv::namedWindow("256*256の大きさで(色相、彩度、明度)=(100, 100, 100)の画像(OpenCV使用)", cv::WINDOW_AUTOSIZE);
	//cv::imshow("256*256の大きさで(色相、彩度、明度)=(100, 100, 100)の画像(OpenCV使用)", dstImg);

	//ダイアログでRGB(HSV)を指定した値を元にして表示する方式（作成中）
	int r, g, b;
	int width, height;
	CColorSpaceDlg dlg;
	dlg.SetValues(&width, &height, &r, &g, &b);
	if (dlg.DoModal() == IDOK)
	{
		//スクラッチでRBG<-->HSV変換
		cv::Mat img(cv::Size(width, height), CV_8UC3, cv::Scalar(b, g, r));
		cv::namedWindow("スクラッチでRBG<-->HSV変換", cv::WINDOW_AUTOSIZE);
		cv::imshow("スクラッチでRBG<-->HSV変換", img);
	}
}

///<summary>
///	
///</summary>
void CSample::CreateFrequencyImage(CString filePath)
{
	//元画像読み込み
	std::string path = this->GetMultiBytePath(filePath);
	cv::Mat img(256, 256, CV_8UC3, cv::Scalar(255, 255, 255));

	for (int x = 0; x < img.cols; x++)
	{
		for (int y = 0; y < img.rows; y++)
		{
			double rad = x * 6 * M_PI / 180.0;
			int val = 127 + 127 * sin(rad);

			cv::Vec3b color = img.at<cv::Vec3b>(y, x);
			int r = val;
			int g = val;
			int b = val;

			img.at<cv::Vec3b>(y, x) = cv::Vec3b(b, g, r);
		}
	}

	//表示
	cv::namedWindow("サンプル画像", cv::WINDOW_AUTOSIZE);
	cv::imshow("サンプル画像", img);

	//ファイルに保存
	cv::imwrite(path, img);
}


void CSample::CreateGaussianNoiseImage(CString srcPath, CString dstsPath)
{
	//元画像読み込み
	cv::Mat src = cv::imread(this->GetMultiBytePath(srcPath), 1);
	cv::Mat snoise;

	//標準偏差15
	double noise_sigma = 15.0;
	AddNoise(src, snoise, noise_sigma, 0.0);

	//表示
	cv::namedWindow("ガウシアンノイズ付加画像", cv::WINDOW_AUTOSIZE);
	cv::imshow("ガウシアンノイズ付加画像", snoise);

	//ファイルに保存
	cv::imwrite(this->GetMultiBytePath(dstsPath), snoise);
}

void CSample::AddNoiseSoltPepperMono(cv::Mat& src, cv::Mat& dest, double per)
{
	cv::RNG rng; 

	for (int j = 0; j<src.rows; j++)
	{
		uchar* s = src.ptr(j);
		uchar* d = dest.ptr(j);
		for (int i = 0; i<src.cols; i++)
		{
			double a1 = rng.uniform((double)0, (double)1);

			if (a1>per)
				d[i] = s[i];
			else
			{
				double a2 = rng.uniform((double)0, (double)1);
				if (a2>0.5)d[i] = 0;
				else d[i] = 255;
			}
		}
	}
} 

void CSample::AddNoiseMono(cv::Mat& src, cv::Mat& dest, double sigma)
{
	cv::Mat s;
	src.convertTo(s, CV_16S);
	cv::Mat n(s.size(), CV_16S);
	randn(n, 0, sigma);
	cv::Mat temp = s + n;
	temp.convertTo(dest, CV_8U);
}

void CSample::AddNoise(cv::Mat& src, cv::Mat& dest, double sigma, double sprate)
{
	if (src.channels() == 1)
	{
		AddNoiseMono(src, dest, sigma);
		if (sprate != 0)AddNoiseSoltPepperMono(dest, dest, sprate);
		return;
	}
	else
	{
		cv::vector<cv::Mat> s;
		cv::vector<cv::Mat> d(src.channels());
		split(src, s);
		for (int i = 0; i<src.channels(); i++)
		{
			AddNoiseMono(s[i], d[i], sigma);

			if (sprate != 0)
				AddNoiseSoltPepperMono(d[i], d[i], sprate);
		}
		cv::merge(d, dest);
	}
}

