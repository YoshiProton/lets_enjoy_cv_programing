#pragma once
#include "ImageProcessor.h"

class CHueFilter :
	public CImageProcessor
{
public:
	CHueFilter();
	~CHueFilter();

	void ProcessByFullOpenCV(CString);
	void ProcessByFullScratch(LPCOLORREF, BITMAPINFO*);
};

