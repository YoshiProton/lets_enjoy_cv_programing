#include "stdafx.h"
#include "ImageProcessor.h"
#include "PictureDlg.h"

CImageProcessor::CImageProcessor()
{
}


CImageProcessor::~CImageProcessor()
{
}


///<summary>
///�ۑ���̃t�@�C���p�X�𐶐��iOpenCV�p�Ƃ��ă}���`�o�C�g�L������p�j
///</summary>
void CImageProcessor::GetNewFilePath(LPSTR lpSrc, LPSTR lpFile, LPSTR lpDest)
{
	LPCSTR lpFileName = PathFindFileNameA(lpSrc);
	wsprintfA(lpDest, "%s.%s", lpFileName, lpFile);
}


///<summary>
///CString(���C�h�L����)�^�̃t�@�C���p�X��std::string�^�ɕϊ��iOpenCV�p�j
///</summary>
std::string CImageProcessor::GetMultiBytePath(CString filePath)
{
	//���C�h��������}���`�o�C�g������ɕϊ�
	CHAR mstr[MAX_PATH] = {};
	::WideCharToMultiByte(CP_ACP, 0, filePath, wcslen(filePath), mstr, sizeof(mstr) - 1, 0, 0);
	return (std::string)mstr;
}


///<summary>
///	LPCOLORREF�̉摜�f�[�^�z���MFC��CImage�^�I�u�W�F�N�g�ɕϊ����ă_�C�A���O�\��
///</summary>
void CImageProcessor::ShowPictureDlg(LPCOLORREF pixelData, BITMAPINFO* bmpInfo)
{
	CImage* image = new CImage;
	image->Create(bmpInfo->bmiHeader.biWidth, bmpInfo->bmiHeader.biHeight, bmpInfo->bmiHeader.biBitCount);

	StretchDIBits(
		image->GetDC(), //HDC
		0, 0, bmpInfo->bmiHeader.biWidth, bmpInfo->bmiHeader.biHeight, //�R�s�[��T�C�Y
		0, 0, bmpInfo->bmiHeader.biWidth, bmpInfo->bmiHeader.biHeight, //�R�s�[���T�C�Y
		pixelData, bmpInfo, DIB_RGB_COLORS, SRCCOPY);

	CPictureDlg dlg(image);
	dlg.DoModal();

	if (image)
	{
		image->ReleaseDC();
		delete image;
		image = NULL;
	}
}


///<summary>
///	OpenCV��image�f�[�^�ł���Mat�^�f�[�^��MFC��CImage�^�I�u�W�F�N�g�ɕϊ����ă_�C�A���O�\���i�쐬���j
///</summary>
void CImageProcessor::ShowPictureDlg(cv::Mat cvImg)
{
	cv::Size size = cvImg.size();

	// �㉺���]
	cv::flip(cvImg, cvImg, 0);

	BITMAPINFO bmpInfo;
	bmpInfo.bmiHeader.biBitCount = cvImg.channels() * 8;
	bmpInfo.bmiHeader.biWidth = size.width;
	bmpInfo.bmiHeader.biHeight = size.height;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biCompression = BI_RGB;
	bmpInfo.bmiHeader.biClrImportant =
		bmpInfo.bmiHeader.biClrUsed =
		bmpInfo.bmiHeader.biSizeImage =
		bmpInfo.bmiHeader.biXPelsPerMeter =
		bmpInfo.bmiHeader.biYPelsPerMeter = 0;

	CImage* image = new CImage;
	image->Create(bmpInfo.bmiHeader.biWidth, bmpInfo.bmiHeader.biHeight, bmpInfo.bmiHeader.biBitCount);
	//HDC hdc = image->GetDC();

	StretchDIBits(
		image->GetDC(), //HDC
		0, 0, bmpInfo.bmiHeader.biWidth, bmpInfo.bmiHeader.biHeight,//�R�s�[��T�C�Y
		0, 0, bmpInfo.bmiHeader.biWidth, bmpInfo.bmiHeader.biHeight,//�R�s�[���T�C�Y
		cvImg.data, &bmpInfo, DIB_RGB_COLORS, SRCCOPY);

	//http://chichimotsu.hateblo.jp/entry/20121130/1354265478
	//HBITMAP hbmp = CreateCompatibleBitmap(hdc, bmpInfo.bmiHeader.biWidth, bmpInfo.bmiHeader.biHeight);
	//SetDIBits(hdc, hbmp, 0, bmpInfo.bmiHeader.biHeight, cvImg.data, &bmpInfo, DIB_RGB_COLORS);
	//HDC hdc2 = CreateCompatibleDC(hdc);
	//SelectObject(hdc2, hbmp);
	//BitBlt(hdc, 0, 0, bmpInfo.bmiHeader.biWidth, bmpInfo.bmiHeader.biHeight, hdc2, 0, 0, SRCCOPY);
	//DeleteDC(hdc2);
	//DeleteObject(hbmp);

	CPictureDlg dlg(image);
	dlg.DoModal();

	if (image)
	{
		image->ReleaseDC();
		delete image;
		image = NULL;
	}
}

