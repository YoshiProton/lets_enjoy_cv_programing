#pragma once
#include "ImageProcessor.h"
class COriginal :
	public CImageProcessor
{
public:
	COriginal();
	~COriginal();

	void Execute(std::string);
};

