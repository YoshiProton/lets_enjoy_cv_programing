#include "stdafx.h"
#include "ImageProcessor.h"


CImageProcessor::CImageProcessor()
{
}


CImageProcessor::~CImageProcessor()
{
}

//�摜�����̕��@��ݒ�
void CImageProcessor::SetProcessMethod(ProcessMethod param)
{
	this->processMethod = param;
}