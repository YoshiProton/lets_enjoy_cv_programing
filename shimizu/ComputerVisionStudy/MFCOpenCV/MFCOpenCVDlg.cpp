
// MFCOpenCVDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MFCOpenCV.h"
#include "MFCOpenCVDlg.h"
#include "afxdialogex.h"

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
public:
	afx_msg void OnMenuSave();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_COMMAND(ID_MENU_SAVE, &CAboutDlg::OnMenuSave)
END_MESSAGE_MAP()


// CMFCOpenCVDlg ダイアログ



CMFCOpenCVDlg::CMFCOpenCVDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCOPENCV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCOpenCVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCOpenCVDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENU_EXIT, &CMFCOpenCVDlg::OnMenuExit)
	ON_COMMAND(ID_MENU_OPEN, &CMFCOpenCVDlg::OnMenuOpen)
	ON_COMMAND(ID_MENU_ABOUT, &CMFCOpenCVDlg::OnMenuAbout)
END_MESSAGE_MAP()


// CMFCOpenCVDlg メッセージ ハンドラー

BOOL CMFCOpenCVDlg::OnInitDialog()
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

void CMFCOpenCVDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCOpenCVDlg::OnPaint()
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
		CDialogEx::OnPaint();

		cv::Mat image1 = cv::imread("lena.jpg");
		DrawPicToHDC(image1, IDC_STATIC, TRUE);
		cv::namedWindow("原画像", cv::WINDOW_AUTOSIZE);
		cv::imshow("原画像", image1);
		cv::waitKey(0);
		cv::destroyAllWindows();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CMFCOpenCVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//IplImage からBMP(DIB)へ変換する．
//http://seesaawiki.jp/urakana-tips/d/OpenCV%A4%F2Win32API%A4%C8%C1%C8%A4%DF%B9%E7%A4%EF%A4%BB%A4%C6%BB%C8%A4%A4%A4%BF%A4%A4
//http://fa11enprince.hatenablog.com/entry/2014/04/24/023546
void CMFCOpenCVDlg::iplTobmp(const IplImage* srcIplImage, BITMAPINFO& bmpInfo, unsigned long* bmpData)
{
	int width = srcIplImage->width;
	int height = srcIplImage->height;

	ZeroMemory(&bmpInfo, sizeof(bmpInfo));
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = width;
	bmpInfo.bmiHeader.biHeight = height;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 32;
	bmpInfo.bmiHeader.biCompression = BI_RGB;

	unsigned long pixel;
	unsigned char r, g, b;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			b = srcIplImage->imageData[srcIplImage->widthStep * i + j * 3];
			g = srcIplImage->imageData[srcIplImage->widthStep * i + j * 3 + 1];
			r = srcIplImage->imageData[srcIplImage->widthStep * i + j * 3 + 2];
			pixel = 0x00000000;
			pixel = (r << 16) + (g << 8) + b;
			bmpData[j + (height - i - 1) * width] = pixel;
		}
	}
}


//http://stackoverflow.com/questions/28997560/opencv-2-4-displaying-a-cvmat-in-mfc
void CMFCOpenCVDlg::DrawPicToHDC(cv::Mat cvImg, UINT ID, bool bOnPaint)
{
	// Get the HDC handle information from the ID passed
	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDCDst = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	cv::Size winSize(rect.right, rect.bottom);

	// Resize the source to the size of the destination image if necessary
	cv::Mat cvImgTmp(winSize, CV_8UC3);
	if (cvImg.size() != winSize)
	{
		cv::resize(cvImg, cvImgTmp, winSize);
	}
	else
	{
		cvImgTmp = cvImg;
	}

	// Rotate the image
	cv::flip(cvImgTmp, cvImgTmp, 0);

	// Initialize the BITMAPINFO structure
	BITMAPINFO bitInfo;
	bitInfo.bmiHeader.biBitCount = 24;
	bitInfo.bmiHeader.biWidth = winSize.width;
	bitInfo.bmiHeader.biHeight = winSize.height;
	bitInfo.bmiHeader.biPlanes = 1;
	bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitInfo.bmiHeader.biCompression = BI_RGB;
	bitInfo.bmiHeader.biClrImportant = 0;
	bitInfo.bmiHeader.biClrUsed = 0;
	bitInfo.bmiHeader.biSizeImage = 0;
	bitInfo.bmiHeader.biXPelsPerMeter = 0;
	bitInfo.bmiHeader.biYPelsPerMeter = 0;

	// Add header and OPENCV image's data to the HDC
	StretchDIBits(hDCDst, 0, 0,
		winSize.width, winSize.height, 0, 0,
		winSize.width, winSize.height,
		cvImgTmp.data, &bitInfo, DIB_RGB_COLORS, SRCCOPY);

	ReleaseDC(pDC);
}

void CMFCOpenCVDlg::OnMenuExit()
{
	OnOK();
}


void CMFCOpenCVDlg::OnMenuOpen()
{
}


void CAboutDlg::OnMenuSave()
{
}


void CMFCOpenCVDlg::OnMenuAbout()
{
}
