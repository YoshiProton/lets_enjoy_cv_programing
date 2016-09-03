#pragma once
#include "ImageProcessor.h"

class CNonlocalMeansFilter :
	public CImageProcessor
{
public:
	CNonlocalMeansFilter();
	~CNonlocalMeansFilter();

	void SetKernel(int, int);

	void ProcessByFullOpenCV(CString);
	void ProcessByPartOpenCV(CString);
	void ProcessByFullScratch(LPCOLORREF, BITMAPINFO*);

private:
	int templeteWindowSize;
	int searchWindowSize;
};

