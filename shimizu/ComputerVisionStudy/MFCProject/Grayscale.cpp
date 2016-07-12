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


//OpenCV�����p���ĊȒP����
void CGrayscale::ProcessFullOpenCV()
{

}


//�摜�ǂݍ��ݕۑ��̂�OpenCV���g�p���ăs�N�Z������̓X�N���b�`
void CGrayscale::ProcessHalfOpenCV()
{

}


//OpenCV��S���g�킸�Ƀt���X�N���b�`
void CGrayscale::ProcessFullScratch()
{

}