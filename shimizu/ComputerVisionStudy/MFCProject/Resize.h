#pragma once
#include "ImageProcessor.h"
class CResize :
	public CImageProcessor
{
public:
	CResize();
	~CResize();

	enum Algorithm { NearestNeighbor = 0, Bilinear = 1, Bicubic = 2 };

	void ProcessFullOpenCV(CString);
	void ProcessHalfOpenCV(CString);
	void ProcessFullScratch(LPCOLORREF, BITMAPINFO*);

private:
	void ResizeByNearestNeighbor(UINT, UINT, UINT, UINT, double, LPCOLORREF, LPCOLORREF);
	void ResizeByBilinear(UINT, UINT, UINT, UINT, double, LPCOLORREF, LPCOLORREF);
	void ResizeByBicubic(UINT, UINT, UINT, UINT, double, LPCOLORREF, LPCOLORREF);
};

