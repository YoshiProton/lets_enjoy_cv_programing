
// MainDlg.cpp : �����t�@�C��
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


// CMainDlg �_�C�A���O

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


// CMainDlg ���b�Z�[�W �n���h���[

BOOL CMainDlg::OnInitDialog()
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

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CMainDlg::OnPaint()
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
		if (!filePath.IsEmpty())
		{
			CPaintDC dc(this);
			this->LoadImage(dc);
			this->ShowImage(dc);
		}

		CDialogEx::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


///<summary>
///�t�@�C������摜��ǂݍ���Ń����o�̔z���BITMAPINFO�ɒl��ݒ�
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
///�����o�̔z���BITMAPINFO���g�p���ĉ摜��\��
///</summary>
void CMainDlg::ShowImage(HDC hdc)
{
	SetDIBitsToDevice(hdc, 0, 0, WIDTH, HEIGHT, 0, 0, 0, HEIGHT, pixelData, &bmpInfo, DIB_RGB_COLORS);
}


#pragma region �摜�����ȊO�̃��j���[�I���C�x���g

///<summary>
///�I�����j���[�I��
///</summary>
void CMainDlg::OnMenuExit()
{
	OnOK();
	//OnCancel();
}

///<summary>
///�t�@�C�����J�����j���[�I��
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
///�t�@�C����ۑ����j���[�I��
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
///�A�o�E�g���j���I��
///</summary>
void CMainDlg::OnMenuAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

#pragma endregion


#pragma region �摜�������j���[�I���C�x���g

#pragma region ���摜�����̂܂ܕ\��

///<summary>
///OpenCV�����p���ĊȒP����
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

	//////2. The size of m_matCVImg is not always the same as an MFC window�fs :
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
	////6. Add header and OpenCV image�fs data to image
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
///OpenCV��S���g�킸�Ƀt���X�N���b�`
///</summary>
void CMainDlg::OnMenuOriginalScratch()
{
	COriginal process;
	process.ProcessFullScratch(pixelData, &bmpInfo);
}

#pragma endregion


#pragma region �O���C�X�P�[����

///<summary>
///OpenCV�����p���ĊȒP����
///</summary>
void CMainDlg::OnMenuGrayscaleFullOpenCV()
{
	CGrayscale process;
	process.ProcessFullOpenCV(filePath);
}

///<summary>
///�摜�ǂݍ��ݕۑ��̂�OpenCV���g�p���ăs�N�Z������̓X�N���b�`
///</summary>
void CMainDlg::OnMenuGrayscaleHalfOpenCV()
{
	CGrayscale process;
	process.ProcessHalfOpenCV(filePath);
}

///<summary>
///OpenCV��S���g�킸�Ƀt���X�N���b�`
///</summary>
void CMainDlg::OnMenuGrayscaleScratch()
{
	CGrayscale process;
	process.ProcessFullScratch(pixelData, &bmpInfo);
}

#pragma endregion


#pragma region ���T�C�Y

///<summary>
///OpenCV�����p���ĊȒP����
///</summary>
void CMainDlg::OnMenuResizeFullOpenCV()
{
	CResize process;
	process.ProcessFullOpenCV(filePath);
}

///<summary>
///�摜�ǂݍ��ݕۑ��̂�OpenCV���g�p���ăs�N�Z������̓X�N���b�`
///</summary>
void CMainDlg::OnMenuResizeHalfOpenCV()
{
	CResize process;
	process.ProcessHalfOpenCV(filePath);
}

///<summary>
///OpenCV��S���g�킸�Ƀt���X�N���b�`
///</summary>
void CMainDlg::OnMenuResizeScratch()
{
	CResize process;
	process.ProcessFullScratch(pixelData, &bmpInfo);
}

#pragma endregion

#pragma endregion
