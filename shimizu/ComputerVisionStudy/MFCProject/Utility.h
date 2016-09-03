#pragma once

#include <string> 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class CUtility
{
public:
	CUtility();
	~CUtility();

	static void ConvertRGBtoHSV(int, int, int, int*, int*, int*);
	static void ConvertHSVtoRGB(int, int, int, int*, int*, int*);

	static double GetPSNR(cv::Mat&, cv::Mat&);
	static double CalcPSNR(cv::Mat&, cv::Mat&);

	static BYTE GetR(COLORREF);
	static BYTE GetG(COLORREF);
	static BYTE GetB(COLORREF);
};

