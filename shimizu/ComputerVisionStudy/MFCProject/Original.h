#pragma once
#include "ImageProcessor.h"

class COriginal :
	public CImageProcessor
{
public:
	COriginal();
	~COriginal();

	void ProcessFullOpenCV(CString);
	//void ProcessHalfOpenCV(CString);
	void ProcessFullScratch(LPCOLORREF, BITMAPINFO*);
};

