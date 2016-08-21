#pragma once
#include "ImageProcessor.h"

class COriginal :
	public CImageProcessor
{
public:
	COriginal();
	~COriginal();

	void ProcessByFullOpenCV(CString);
	//void ProcessByPartOpenCV(CString);
	void ProcessByFullScratch(LPCOLORREF, BITMAPINFO*);
};

