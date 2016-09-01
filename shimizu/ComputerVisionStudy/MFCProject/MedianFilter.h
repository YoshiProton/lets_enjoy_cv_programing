#pragma once
#include "ImageProcessor.h"

class CMedianFilter :
	public CImageProcessor
{
public:
	CMedianFilter();
	~CMedianFilter();

	void SetKernel(int);

	void ProcessByFullOpenCV(CString);
	void ProcessByPartOpenCV(CString);
	void ProcessByFullScratch(LPCOLORREF, BITMAPINFO*);

private:
	int kernelSize;
};

