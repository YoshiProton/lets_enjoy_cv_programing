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
	void ResizeByNearestNeighbor(int, int, int, int, double, cv::Mat*, cv::Mat*);//Nearest neighbor�iOpenCV�p�j
	void ResizeByNearestNeighbor(UINT, UINT, UINT, UINT, double, LPCOLORREF, LPCOLORREF);//Nearest neighbor�iWin32�p�j

	void ResizeByBilinear(int, int, int, int, double, cv::Mat*, cv::Mat*);//Bilinear�iOpenCV�p�j
	void ResizeByBilinear(UINT, UINT, UINT, UINT, double, LPCOLORREF, LPCOLORREF);//Bilinear�iWin32�p�j

	void ResizeByBicubic(int, int, int, int, double, cv::Mat*, cv::Mat*);//Bicubic�iOpenCV�p�j
	void ResizeByBicubic(UINT, UINT, UINT, UINT, double, LPCOLORREF, LPCOLORREF);//Bicubic�iWin32�p�j

	double GetBicubicWeight(double);
};

