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
///保存先のファイルパスを生成
///</summary>
void CImageProcessor::GetNewFilePath(LPSTR lpSrc, LPSTR lpFile, LPSTR lpDest)
{
	LPCSTR lpFileName = PathFindFileNameA(lpSrc);
	wsprintfA(lpDest, "%s.%s", lpFileName, lpFile);
}


///<summary>
///CString(ワイドキャラ)型のファイルパスをstd::string型に変換
///</summary>
std::string CImageProcessor::GetMultiBytePath(CString filePath)
{
	//ワイド文字列をマルチバイト文字列に変換
	CHAR mstr[MAX_PATH] = {};
	::WideCharToMultiByte(CP_ACP, 0, filePath, wcslen(filePath), mstr, sizeof(mstr) - 1, 0, 0);
	return (std::string)mstr;
}


///<summary>
///	LPCOLORREFの画像データ配列をMFCのCImage型オブジェクトに変換してダイアログ表示
///</summary>
void CImageProcessor::ShowPictureDlg(LPCOLORREF pixelData, BITMAPINFO* bmpInfo)
{
	CImage* image = new CImage;
	image->Create(bmpInfo->bmiHeader.biWidth, -1 * bmpInfo->bmiHeader.biHeight, bmpInfo->bmiHeader.biBitCount);

	StretchDIBits(
		image->GetDC(), 0, 0,
		bmpInfo->bmiHeader.biWidth, -1 * bmpInfo->bmiHeader.biHeight, 0, 0,
		bmpInfo->bmiHeader.biWidth, -1 * bmpInfo->bmiHeader.biHeight,
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
///	OpenCVのimageデータであるMat型データをMFCのCImage型オブジェクトに変換してダイアログ表示（作成中）
////http://chichimotsu.hateblo.jp/entry/20121130/1354265478
///</summary>
void CImageProcessor::ShowPictureDlg(cv::Mat m_matCVImg)
{
	cv::Size size = m_matCVImg.size();

	cv::flip(m_matCVImg, m_matCVImg, 0);

	CImage* image = new CImage;
	image->Create(size.width, size.height, 24);

	BITMAPINFO bitInfo;
	bitInfo.bmiHeader.biBitCount = 24;
	bitInfo.bmiHeader.biWidth = size.width;
	bitInfo.bmiHeader.biHeight = size.height;
	bitInfo.bmiHeader.biPlanes = 1;
	bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitInfo.bmiHeader.biCompression = BI_RGB;
	bitInfo.bmiHeader.biClrImportant =
		bitInfo.bmiHeader.biClrUsed =
		bitInfo.bmiHeader.biSizeImage =
		bitInfo.bmiHeader.biXPelsPerMeter =
		bitInfo.bmiHeader.biYPelsPerMeter = 0;

	StretchDIBits(
		image->GetDC(), 0, 0,
		size.width, size.height, 0, 0,
		size.width, size.height,
		m_matCVImg.data, &bitInfo, DIB_RGB_COLORS, SRCCOPY);

	CPictureDlg dlg(image);
	dlg.DoModal();

	if (image)
	{
		image->ReleaseDC();
		delete image;
		image = NULL;
	}
}

