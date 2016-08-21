#pragma once
#include "ImageProcessor.h"

class CHueFilter :
	public CImageProcessor
{
public:
	CHueFilter();
	~CHueFilter();

	void ProcessByOpenCV(CString);
	void ProcessByScratch(LPCOLORREF, BITMAPINFO*);
};

