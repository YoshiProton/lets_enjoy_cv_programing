#include "stdafx.h"
#include "Original.h"


COriginal::COriginal()
{
}


COriginal::~COriginal()
{
}


///<summary>
///	OpenCV�����p���ĊȒP����
///</summary>
void COriginal::ProcessByFullOpenCV(CString filePath)
{
	std::string path = this->GetMultiBytePath(filePath);
	cv::Mat cvImage = cv::imread(path);
	cv::namedWindow("���摜", cv::WINDOW_AUTOSIZE);
	cv::imshow("���摜", cvImage);

	//�t�@�C���ۑ�
	char lpDest[MAX_PATH] = {};
	this->GetNewFilePath((LPSTR)path.c_str(), "original.ocv.jpg", lpDest);
	cv::imwrite(lpDest, cvImage);
}

//
////�摜�ǂݍ��ݕۑ��̂�OpenCV���g�p���ĕ\����MFC��PictureCotrol��
//void COriginal::ProcessByPartOpenCV(std::string filePath)
//{
//	cv::Mat cvImage = cv::imread(filePath);
//	this->ShowPictureDlg(cvImage);
//
//	char lpDest[MAX_PATH] = {};
//	this->GetNewFilePath((LPSTR)path.c_str(), "original2.jpg", lpDest);
//	cv::imwrite(lpDest, cvImage);
//}


///<summary>
///	OpenCV��S���g�킸�Ƀt���X�N���b�`
///</summary>
void COriginal::ProcessByFullScratch(LPCOLORREF pixelData, BITMAPINFO* bmpInfo)
{
	ShowPictureDlg(pixelData, bmpInfo);
}