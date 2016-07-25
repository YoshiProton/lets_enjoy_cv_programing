#pragma once
#include "ImageProcessor.h"
class CGrayscale :
	public CImageProcessor
{
public:
	CGrayscale();
	~CGrayscale();

	void ProcessFullOpenCV(CString);
	void ProcessHalfOpenCV(CString);
	void ProcessFullScratch(LPCOLORREF, BITMAPINFO*);
};

