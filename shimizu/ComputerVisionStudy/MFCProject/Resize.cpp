#include "stdafx.h"
#include "Resize.h"


CResize::CResize()
{
}


CResize::~CResize()
{
}


void CResize::Execute(std::string path)
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
void CResize::ProcessFullOpenCV()
{

}


//�摜�ǂݍ��ݕۑ��̂�OpenCV���g�p���ăs�N�Z������̓X�N���b�`
void CResize::ProcessHalfOpenCV()
{

}


//OpenCV��S���g�킸�Ƀt���X�N���b�`
void CResize::ProcessFullScratch()
{

}