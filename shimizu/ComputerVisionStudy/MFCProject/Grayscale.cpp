#include "stdafx.h"
#include "Grayscale.h"


CGrayscale::CGrayscale()
{
}


CGrayscale::~CGrayscale()
{
}


void CGrayscale::Execute(std::string path)
{
	this->filePath = path;

	switch (this->processMethod)
	{
	case ProcessMethod::FullOpenCV:
		this->ProcessFullOpenCV();
		break;

	case ProcessMethod::HalfOpenCV:
		this->ProcessHalfOpenCV();
		break;

	case ProcessMethod::FullScratch:
		this->ProcessFullScratch();
		break;
	}
}


//OpenCVを活用して簡単実装
void CGrayscale::ProcessFullOpenCV()
{

}


//画像読み込み保存のみOpenCVを使用してピクセル操作はスクラッチ
void CGrayscale::ProcessHalfOpenCV()
{

}


//OpenCVを全く使わずにフルスクラッチ
void CGrayscale::ProcessFullScratch()
{

}