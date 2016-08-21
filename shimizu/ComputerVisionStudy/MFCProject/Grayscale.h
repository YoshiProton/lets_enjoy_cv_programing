#pragma once
#include "ImageProcessor.h"
class CGrayscale :
	public CImageProcessor
{
public:
	CGrayscale();
	~CGrayscale();

	void ProcessByFullOpenCV(CString);
	void ProcessByPartOpenCV(CString);
	void ProcessByFullScratch(LPCOLORREF, BITMAPINFO*);
};

