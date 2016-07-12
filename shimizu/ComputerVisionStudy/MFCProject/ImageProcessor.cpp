#include "stdafx.h"
#include "ImageProcessor.h"


CImageProcessor::CImageProcessor()
{
}


CImageProcessor::~CImageProcessor()
{
}

//‰æ‘œˆ—‚Ì•û–@‚ðÝ’è
void CImageProcessor::SetProcessMethod(ProcessMethod param)
{
	this->processMethod = param;
}