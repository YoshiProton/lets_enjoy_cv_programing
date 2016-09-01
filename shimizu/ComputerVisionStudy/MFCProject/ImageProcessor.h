#pragma once

#include <string> 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")

#include "Utility.h"

class CImageProcessor
{
public:
	CImageProcessor();
	~CImageProcessor();

protected:
	void ShowPictureDlg(cv::Mat);
	void ShowPictureDlg(LPCOLORREF, BITMAPINFO*);
	void GetNewFilePath(LPSTR, LPSTR, LPSTR);
	std::string GetMultiBytePath(CString);
	COLORREF GetPixelValue(BYTE, BYTE, BYTE);
};

