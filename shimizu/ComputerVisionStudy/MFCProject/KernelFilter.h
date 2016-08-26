#pragma once
#include "ImageProcessor.h"

class CKernelFilter :
	public CImageProcessor
{
public:
	CKernelFilter();
	~CKernelFilter();

	//enum FilterType { Averaging = 0, Gaussian, Differencial, Prewitt, Sobel, Laplacian, Sharpening };

	void SetKernel(std::vector<std::vector<int>>, int);

	void ProcessByFullOpenCV(CString);
	void ProcessByPartOpenCV(CString);
	void ProcessByFullScratch(LPCOLORREF, BITMAPINFO*);

private:
	std::vector<std::vector<int>> kernel;
	int normalize;
};

