#include "stdafx.h"
#include "ImageProcessor.h"


CImageProcessor::CImageProcessor()
{
}


CImageProcessor::~CImageProcessor()
{
}

//画像処理の方法を設定
void CImageProcessor::SetProcessMethod(ProcessMethod param)
{
	this->processMethod = param;
}