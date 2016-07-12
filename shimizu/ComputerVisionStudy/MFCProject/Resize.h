#pragma once
#include "ImageProcessor.h"
class CResize :
	public CImageProcessor
{
public:
	CResize();
	~CResize();

	void Execute(std::string);

private:
	void ProcessFullOpenCV();
	void ProcessHalfOpenCV();
	void ProcessFullScratch();
};

