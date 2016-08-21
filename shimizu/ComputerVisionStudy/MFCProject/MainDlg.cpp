
// MainDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MFCProject.h"
#include "MainDlg.h"
#include "afxdialogex.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "ImageProcessor.h"
#include "Original.h"
#include "Grayscale.h"
#include "Resize.h"
#include "ColorSpaceDlg.h"
#include "HueFilter.h"
#include "Utility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMainDlg ダイアログ

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCPROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMainDlg::~CMainDlg()
{
	delete[] pixelData;
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENU_EXIT, &CMainDlg::OnMenuExit)
	ON_COMMAND(ID_MENU_OPEN, &CMainDlg::OnMenuOpen)
	ON_COMMAND(ID_MENU_SAVE, &CMainDlg::OnMenuSave)
	ON_COMMAND(ID_MENU_ABOUT, &CMainDlg::OnMenuAbout)
	ON_COMMAND(ID_MENU_ORIGINAL_FULLOCV, &CMainDlg::OnMenuOriginalFullOpenCV)
	ON_COMMAND(ID_MENU_ORIGINAL_SCRATCH, &CMainDlg::OnMenuOriginalScratch)
	ON_COMMAND(ID_MENU_GRAYSCALE_FULLOCV, &CMainDlg::OnMenuGrayscaleFullOpenCV)
	ON_COMMAND(ID_MENU_GRAYSCALE_HALFOCV, &CMainDlg::OnMenuGrayscaleHalfOpenCV)
	ON_COMMAND(ID_MENU_GRAYSCALE_SCRATCH, &CMainDlg::OnMenuGrayscaleScratch)
	ON_COMMAND(ID_MENU_RESIZE_FULLOCV, &CMainDlg::OnMenuResizeFullOpenCV)
	ON_COMMAND(ID_MENU_RESIZE_HALFOCV, &CMainDlg::OnMenuResizeHalfOpenCV)
	ON_COMMAND(ID_MENU_RESIZE_SCRATCH, &CMainDlg::OnMenuResizeScratch)
	ON_COMMAND(ID_MENU_NEW, &CMainDlg::OnMenuNew)
	ON_COMMAND(ID_MENU_FILTER_COLOR, &CMainDlg::OnMenuFilterColor)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMainDlg メッセージ ハンドラー

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	int err = 0;
	UINT statusText[2] = { 0, IDS_ABOUTBOX };

	// ステータスバー初期化
	if (!err) if (!statusBar.Create(this)) err = 1;
	if (!err) if (!statusBar.SetIndicators(statusText, 2)) err = 1;
	if (!err)
	{
		statusBar.SetPaneInfo(0, 0, SBPS_STRETCH, 0);
		statusBar.SetPaneInfo(1, IDS_ABOUTBOX, SBPS_NORMAL, 30);
		if (!statusBar.SetPaneText(0, _T("ステータスバー"))) err = 1;
	}
	if (!err) RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if (!filePath.IsEmpty())
		{
			CPaintDC dc(this);
			this->LoadImage(dc);
			this->ShowImage(dc);
		}

		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMainDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
}

///<summary>
/// 課題2の1,2
/// 左クリックした画素の位置、RGB,HSVの値をステータスバーに表示
///</summary>
void CMainDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (pixelData != NULL)
	{
		UINT width = bmpInfo.bmiHeader.biWidth;
		UINT height = bmpInfo.bmiHeader.biHeight;

		if (width >= point.x &&  height >= point.y)
		{
			COLORREF pixel = pixelData[point.x + (height - point.y) * width];

			BYTE r = CUtility::GetR(pixel);
			BYTE g = CUtility::GetG(pixel);
			BYTE b = CUtility::GetB(pixel);

			int h ,s, v;
			h = s = v = 0;
			CUtility::ConvertRGBtoHSV(r, g, b, &h, &s, &v);

			CString msg;
			msg.Format(_T("座標 [x:%d y:%d] RGB[%d,%d,%d] HSV[%d,%d,%d]"), point.x, point.y, r, g, b, h, s, v);
			statusBar.SetPaneText(0, msg);
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


///<summary>
///ファイルから画像を読み込んでメンバの配列とBITMAPINFOに値を設定
///</summary>
void CMainDlg::LoadImage(HDC hdc)
{
	CImage image;
	image.Load(filePath);

	//CBitmap bitmap;
	//bitmap.Attach(image.Detach());

	int width = image.GetWidth();
	int height = image.GetHeight();

	if (sizeof(pixelData) > 0)
		delete[] pixelData;

	pixelData = new COLORREF[width * height];

	HBITMAP hBitmap = (HBITMAP)image;

	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = width;
	bmpInfo.bmiHeader.biHeight = height;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 32;
	bmpInfo.bmiHeader.biCompression = BI_RGB;

	GetDIBits(hdc, hBitmap, 0, height, pixelData, &bmpInfo, DIB_RGB_COLORS);

	if (image)
	{
		DeleteObject(hBitmap);
		image.Detach();
		image.Destroy();
	}
}


///<summary>
///メンバの配列とBITMAPINFOを使用して画像を表示
///</summary>
void CMainDlg::ShowImage(HDC hdc)
{
	SetDIBitsToDevice(hdc, 0, 0, bmpInfo.bmiHeader.biWidth, bmpInfo.bmiHeader.biHeight, 0, 0, 0, bmpInfo.bmiHeader.biHeight, pixelData, &bmpInfo, DIB_RGB_COLORS);
}


#pragma region 画像処理以外のメニュー選択イベント

///<summary>
///終了メニュー選択
///</summary>
void CMainDlg::OnMenuExit()
{
	OnOK();
	//OnCancel();
}

///<summary>
///ファイルを開くメニュー選択
///</summary>
void CMainDlg::OnMenuOpen()
{
	CString filter("JPEG Files (*.jpg;*.jpeg)|*.jpg; *.jpeg|PNG Files (*.png)|*.png|BMP Files (*.bmp)|*.bmp||");
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, filter);
	if (fileDlg.DoModal() == IDOK)
	{
		filePath = fileDlg.GetPathName();

		Invalidate(TRUE);

		statusBar.SetPaneText(0, _T("ファイルを開きました"));
		UpdateData(FALSE);
	}
}

///<summary>
///ファイルを保存メニュー選択
///</summary>
void CMainDlg::OnMenuSave()
{
	CString filter("JPEG Files (*.jpg;*.jpeg)|*.jpg; *.jpeg|PNG Files (*.png)|*.png|BMP Files (*.bmp)|*.bmp||");
	CFileDialog fileDlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter);
	if (fileDlg.DoModal() == IDOK)
	{
		statusBar.SetPaneText(0, _T("ファイルを保存しました"));
		UpdateData(FALSE);
	}
}

///<summary>
///アバウトメニュ選択
///</summary>
void CMainDlg::OnMenuAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

#pragma endregion


#pragma region 画像処理メニュー選択イベント

#pragma region 元画像をそのまま表示

///<summary>
///OpenCVを活用して簡単実装
///</summary>
void CMainDlg::OnMenuOriginalFullOpenCV()
{
#pragma region
	///*
	//Transformation of OpenCV image to MFC image in MSVC project
	//http://kvy.com.ua/transformation-of-opencv-image-to-mfc-image-in-msvc-project/
	//*/
	//cv::Mat m_matCVImg = cv::imread(filePath);
	//cv::Size size;

	//////1. Define MFC window size :
	////RECT r;
	////pictureCtrl.GetClientRect(&r);
	////size = cv::Size(r.right, r.bottom);

	//size = m_matCVImg.size();

	//////2. The size of m_matCVImg is not always the same as an MFC window’s :
	////cv::Mat matImgTmp;
	////if (m_matCVImg.size() != size)
	////{
	////	matImgTmp = cv::Mat(size, CV_8UC3);
	////	cv::resize(m_matCVImg, matImgTmp, size, 0, 0, cv::INTER_AREA);
	////}
	////else
	////{
	////	matImgTmp = m_matCVImg.clone();
	////}

	////3. Rotate the image :
	//cv::flip(m_matCVImg, m_matCVImg, 0);

	////4. Create an MFC image :
	//CImage* image = new CImage;
	//image->Create(size.width, size.height, 24);

	////5. For image you need a header.Create it by using BITMAPINFO structure
	//BITMAPINFO bitInfo;
	//bitInfo.bmiHeader.biBitCount = 32;
	//bitInfo.bmiHeader.biWidth = size.width;
	//bitInfo.bmiHeader.biHeight = size.height;
	//bitInfo.bmiHeader.biPlanes = 1;
	//bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	//bitInfo.bmiHeader.biCompression = BI_RGB;
	//bitInfo.bmiHeader.biClrImportant =
	//bitInfo.bmiHeader.biClrUsed =
	//bitInfo.bmiHeader.biSizeImage =
	//bitInfo.bmiHeader.biXPelsPerMeter =
	//bitInfo.bmiHeader.biYPelsPerMeter = 0;
	//
	////6. Add header and OpenCV image’s data to image
	//StretchDIBits(
	//	image->GetDC(), 0, 0,
	//	size.width, size.height, 0, 0,
	//	size.width, size.height,
	//	m_matCVImg.data, &bitInfo, DIB_RGB_COLORS, SRCCOPY);

	////7. Display image in MFC window
	//image->BitBlt(::GetDC(pictureCtrl.m_hWnd), 0, 0);

	////8. (Optional)Release image, if you will not use it :
	//if (image)
	//{
	//	image->ReleaseDC();
	//	delete image;
	//	image = NULL;
	//}
#pragma endregion

	COriginal process;
	process.ProcessByFullOpenCV(filePath);
}

///<summary>
///OpenCVを全く使わずにフルスクラッチ
///</summary>
void CMainDlg::OnMenuOriginalScratch()
{
	COriginal process;
	process.ProcessByFullScratch(pixelData, &bmpInfo);
}

#pragma endregion


#pragma region グレイスケール化

///<summary>
///OpenCVを活用して簡単実装
///</summary>
void CMainDlg::OnMenuGrayscaleFullOpenCV()
{
	CGrayscale process;
	process.ProcessByFullOpenCV(filePath);
}

///<summary>
///画像読み込み保存のみOpenCVを使用してピクセル操作はスクラッチ
///</summary>
void CMainDlg::OnMenuGrayscaleHalfOpenCV()
{
	CGrayscale process;
	process.ProcessByPartOpenCV(filePath);
}

///<summary>
///OpenCVを全く使わずにフルスクラッチ
///</summary>
void CMainDlg::OnMenuGrayscaleScratch()
{
	CGrayscale process;
	process.ProcessByFullScratch(pixelData, &bmpInfo);
}

#pragma endregion


#pragma region リサイズ

///<summary>
///OpenCVを活用して簡単実装
///</summary>
void CMainDlg::OnMenuResizeFullOpenCV()
{
	CResize process;
	process.ProcessByFullOpenCV(filePath);
}

///<summary>
///画像読み込み保存のみOpenCVを使用してピクセル操作はスクラッチ
///</summary>
void CMainDlg::OnMenuResizeHalfOpenCV()
{
	CResize process;
	process.ProcessByPartOpenCV(filePath);
}

///<summary>
///OpenCVを全く使わずにフルスクラッチ
///</summary>
void CMainDlg::OnMenuResizeScratch()
{
	CResize process;
	process.ProcessByFullScratch(pixelData, &bmpInfo);
}

#pragma endregion

#pragma endregion


///<summary>
///課題2の3
///</summary>
void CMainDlg::OnMenuNew()
{
	//全部OpenCVでやる方式（RBG<-->HSV変換）
	cv::Mat srcImg(256, 256, CV_8UC3, cv::Scalar(100, 100, 100));
	cv::Mat dstImg(256, 256, CV_8UC3);
	cv::cvtColor(srcImg, dstImg, cv::COLOR_HSV2BGR);
	cv::namedWindow("256*256の大きさで(色相、彩度、明度)=(100, 100, 100)の画像(OpenCV使用)", cv::WINDOW_AUTOSIZE);
	cv::imshow("256*256の大きさで(色相、彩度、明度)=(100, 100, 100)の画像(OpenCV使用)", dstImg);

	//ダイアログでRGB(HSV)を指定した値を元にして表示する方式（作成中）
	int r, g, b;
	int width, height;
	CColorSpaceDlg dlg;
	dlg.SetValues(&width, &height, &r, &g, &b);
	if (dlg.DoModal() == IDOK)
	{
		//スクラッチでRBG<-->HSV変換
		cv::Mat img(cv::Size(width, height), CV_8UC3, cv::Scalar(b, g, r));
		cv::namedWindow("スクラッチでRBG<-->HSV変換", cv::WINDOW_AUTOSIZE);
		cv::imshow("スクラッチでRBG<-->HSV変換", img);
	}
}

///<summary>
///課題2の4
///</summary>
void CMainDlg::OnMenuFilterColor()
{
	CHueFilter process;
	process.ProcessByOpenCV(filePath);
	process.ProcessByScratch(pixelData, &bmpInfo);
}

