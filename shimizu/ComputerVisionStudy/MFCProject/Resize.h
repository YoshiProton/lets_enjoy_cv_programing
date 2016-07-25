#pragma once
#include "ImageProcessor.h"
class CResize :
	public CImageProcessor
{
public:
	CResize();
	~CResize();

	void ProcessFullOpenCV(CString);
	void ProcessHalfOpenCV(CString);
	void ProcessFullScratch(LPCOLORREF, BITMAPINFO*);
};

