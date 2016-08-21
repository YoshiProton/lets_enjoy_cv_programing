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
///保存先のファイルパスを生成（OpenCV用としてマルチバイトキャラ専用）
///</summary>
void CImageProcessor::GetNewFilePath(LPSTR lpSrc, LPSTR lpFile, LPSTR lpDest)
{
	LPCSTR lpFileName = PathFindFileNameA(lpSrc);
	wsprintfA(lpDest, "%s.%s", lpFileName, lpFile);
}


///<summary>
///CString(ワイドキャラ)型のファイルパスをstd::string型に変換（OpenCV用）
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
	image->Create(bmpInfo->bmiHeader.biWidth, bmpInfo->bmiHeader.biHeight, bmpInfo->bmiHeader.biBitCount);

	StretchDIBits(
		image->GetDC(), //HDC
		0, 0, bmpInfo->bmiHeader.biWidth, bmpInfo->bmiHeader.biHeight, //コピー先サイズ
		0, 0, bmpInfo->bmiHeader.biWidth, bmpInfo->bmiHeader.biHeight, //コピー元サイズ
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
///</summary>
void CImageProcessor::ShowPictureDlg(cv::Mat cvImg)
{
	cv::Size size = cvImg.size();

	// 上下反転
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
		0, 0, bmpInfo.bmiHeader.biWidth, bmpInfo.bmiHeader.biHeight,//コピー先サイズ
		0, 0, bmpInfo.bmiHeader.biWidth, bmpInfo.bmiHeader.biHeight,//コピー元サイズ
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

