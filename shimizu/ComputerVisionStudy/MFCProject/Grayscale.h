#pragma once
#include "ImageProcessor.h"
class CGrayscale :
	public CImageProcessor
{
public:
	CGrayscale();
	~CGrayscale();

	void Execute(std::string);

private:
	void ProcessFullOpenCV();
	void ProcessHalfOpenCV();
	void ProcessFullScratch();
};

