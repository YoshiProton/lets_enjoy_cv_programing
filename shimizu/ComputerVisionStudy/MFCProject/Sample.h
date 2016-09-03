#pragma once
#include "ImageProcessor.h"

class CSample :
	public CImageProcessor
{
public:
	CSample();
	~CSample();

	void CreateColorSpaceImage(CString);
	void CreateFrequencyImage(CString);
	void CreateGaussianNoiseImage(CString, CString);

	//noise
	void AddNoiseSoltPepperMono(cv::Mat&, cv::Mat&, double);
	void AddNoiseMono(cv::Mat&, cv::Mat&, double);
	void AddNoise(cv::Mat&, cv::Mat&, double, double);
};

