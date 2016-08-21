#pragma once
#include "ImageProcessor.h"
class CResize :
	public CImageProcessor
{
public:
	CResize();
	~CResize();

	enum Algorithm { NearestNeighbor = 0, Bilinear = 1, Bicubic = 2 };

	void ProcessByFullOpenCV(CString);
	void ProcessByPartOpenCV(CString);
	void ProcessByFullScratch(LPCOLORREF, BITMAPINFO*);

private:
	void ResizeByNearestNeighbor(int, int, int, int, double, cv::Mat*, cv::Mat*);//Nearest neighbor（OpenCV用）
	void ResizeByNearestNeighbor(UINT, UINT, UINT, UINT, double, LPCOLORREF, LPCOLORREF);//Nearest neighbor（Win32用）

	void ResizeByBilinear(int, int, int, int, double, cv::Mat*, cv::Mat*);//Bilinear（OpenCV用）
	void ResizeByBilinear(UINT, UINT, UINT, UINT, double, LPCOLORREF, LPCOLORREF);//Bilinear（Win32用）

	void ResizeByBicubic(int, int, int, int, double, cv::Mat*, cv::Mat*);//Bicubic（OpenCV用）
	void ResizeByBicubic(UINT, UINT, UINT, UINT, double, LPCOLORREF, LPCOLORREF);//Bicubic（Win32用）

	double GetBicubicWeight(double);
};

