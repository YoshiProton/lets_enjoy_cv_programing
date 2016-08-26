#pragma once
#include "ImageProcessor.h"

class CBilateralFilter :
	public CImageProcessor
{
public:
	CBilateralFilter();
	~CBilateralFilter();

	void SetKernel(int);

	void ProcessByFullOpenCV(CString);
	void ProcessByPartOpenCV(CString);
	void ProcessByFullScratch(LPCOLORREF, BITMAPINFO*);

private:
	int kernelSize;
};

