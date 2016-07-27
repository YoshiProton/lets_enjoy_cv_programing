
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

	// TODO: 初期化をここに追加します。

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


///<summary>
///ファイルから画像を読み込んでメンバの配列とBITMAPINFOに値を設定
///</summary>
void CMainDlg::LoadImage(HDC hdc)
{
	CImage image;
	image.Load(filePath);

	WIDTH = image.GetWidth();
	HEIGHT = image.GetHeight();

	if (sizeof(pixelData) > 0)
		delete[] pixelData;

	pixelData = new COLORREF[WIDTH * HEIGHT];

	HBITMAP hBitmap = (HBITMAP)image;

	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = WIDTH;
	bmpInfo.bmiHeader.biHeight = -(INT)HEIGHT;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 32;
	bmpInfo.bmiHeader.biCompression = BI_RGB;

	GetDIBits(hdc, hBitmap, 0, HEIGHT, pixelData, &bmpInfo, DIB_RGB_COLORS);

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
	SetDIBitsToDevice(hdc, 0, 0, WIDTH, HEIGHT, 0, 0, 0, HEIGHT, pixelData, &bmpInfo, DIB_RGB_COLORS);
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
	//bitInfo.bmiHeader.biBitCount = 24;
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
	process.ProcessFullOpenCV(filePath);
}

///<summary>
///OpenCVを全く使わずにフルスクラッチ
///</summary>
void CMainDlg::OnMenuOriginalScratch()
{
	COriginal process;
	process.ProcessFullScratch(pixelData, &bmpInfo);
}

#pragma endregion


#pragma region グレイスケール化

///<summary>
///OpenCVを活用して簡単実装
///</summary>
void CMainDlg::OnMenuGrayscaleFullOpenCV()
{
	CGrayscale process;
	process.ProcessFullOpenCV(filePath);
}

///<summary>
///画像読み込み保存のみOpenCVを使用してピクセル操作はスクラッチ
///</summary>
void CMainDlg::OnMenuGrayscaleHalfOpenCV()
{
	CGrayscale process;
	process.ProcessHalfOpenCV(filePath);
}

///<summary>
///OpenCVを全く使わずにフルスクラッチ
///</summary>
void CMainDlg::OnMenuGrayscaleScratch()
{
	CGrayscale process;
	process.ProcessFullScratch(pixelData, &bmpInfo);
}

#pragma endregion


#pragma region リサイズ

///<summary>
///OpenCVを活用して簡単実装
///</summary>
void CMainDlg::OnMenuResizeFullOpenCV()
{
	CResize process;
	process.ProcessFullOpenCV(filePath);
}

///<summary>
///画像読み込み保存のみOpenCVを使用してピクセル操作はスクラッチ
///</summary>
void CMainDlg::OnMenuResizeHalfOpenCV()
{
	CResize process;
	process.ProcessHalfOpenCV(filePath);
}

///<summary>
///OpenCVを全く使わずにフルスクラッチ
///</summary>
void CMainDlg::OnMenuResizeScratch()
{
	CResize process;
	process.ProcessFullScratch(pixelData, &bmpInfo);
}

#pragma endregion

#pragma endregion
