
// MFCOpenCVDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MFCOpenCV.h"
#include "MFCOpenCVDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
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


// CMFCOpenCVDlg �_�C�A���O



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


// CMFCOpenCVDlg ���b�Z�[�W �n���h���[

BOOL CMFCOpenCVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

	// IDM_ABOUTBOX �́A�V�X�e�� �R�}���h�͈͓̔��ɂȂ���΂Ȃ�܂���B
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

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// TODO: �������������ɒǉ����܂��B

	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
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

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CMFCOpenCVDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

		cv::Mat image1 = cv::imread("lena.jpg");
		DrawPicToHDC(image1, IDC_STATIC, TRUE);
		cv::namedWindow("���摜", cv::WINDOW_AUTOSIZE);
		cv::imshow("���摜", image1);
		cv::waitKey(0);
		cv::destroyAllWindows();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CMFCOpenCVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//IplImage ����BMP(DIB)�֕ϊ�����D
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
