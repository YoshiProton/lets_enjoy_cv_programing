
// MainDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MFCProject.h"
#include "MainDlg.h"
#include "afxdialogex.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Utility.h"
#include "ImageProcessor.h"
#include "Sample.h"
#include "ProcessDlg.h"
#include "Original.h"
#include "Grayscale.h"
#include "Resize.h"
#include "HueFilter.h"
#include "KernelFilter.h"
#include "BilateralFilter.h"
#include "NonlocalMeansFilter.h"
#include "MedianFilter.h"
#include "FourierTransform.h"

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
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_MENU_EXIT, &CMainDlg::OnMenuExit)
	ON_COMMAND(ID_MENU_OPEN, &CMainDlg::OnMenuOpen)
	ON_COMMAND(ID_MENU_SAVE, &CMainDlg::OnMenuSave)
	ON_COMMAND(ID_MENU_ABOUT, &CMainDlg::OnMenuAbout)
	ON_COMMAND(ID_MENU_ORIGINAL, &CMainDlg::OnMenuOriginal)
	ON_COMMAND(ID_MENU_GRAYSCALE, &CMainDlg::OnMenuGrayscale)
	ON_COMMAND(ID_MENU_RESIZE, &CMainDlg::OnMenuResize)
	ON_COMMAND(ID_MENU_NEW, &CMainDlg::OnMenuNew)
	ON_COMMAND(ID_MENU_FILTER_COLOR, &CMainDlg::OnMenuColorFilter)
	ON_COMMAND(ID_MENU_AVERAGING_FILTER, &CMainDlg::OnMenuAveragingFilter)
	ON_COMMAND(ID_MENU_GAUSSIAN_FILTER, &CMainDlg::OnMenuGaussianFilter)
	ON_COMMAND(ID_MENU_DIFFERENCIAL_FILTER, &CMainDlg::OnMenuDifferencialFilter)
	ON_COMMAND(ID_MENU_PREWITT_FILTER, &CMainDlg::OnMenuPrewittFilter)
	ON_COMMAND(ID_MENU_SOBEL_FILTER, &CMainDlg::OnMenuSobelFilter)
	ON_COMMAND(ID_MENU_LAPLACIAN_FILTER, &CMainDlg::OnMenuLaplacianFilter)
	ON_COMMAND(ID_MENU_SHARPENING_FILTER, &CMainDlg::OnMenuSharpeningFilter)
	ON_COMMAND(ID_MENU_BILATERAL_FILTER, &CMainDlg::OnMenuBilateralFilter)
	ON_COMMAND(ID_MENU_NONLOCALMEAN_FILTER, &CMainDlg::OnMenuNonLocalMeanFilter)
	ON_COMMAND(ID_MENU_MEDIAL_FILTER, &CMainDlg::OnMenuMedialFilter)
	ON_COMMAND(ID_MENU_FOURIER_TRANSFORM, &CMainDlg::OnMenuFourierTransform)
	ON_COMMAND(ID_MENU_INVERSE_FOURIER_TRANSFORM, &CMainDlg::OnMenuInverseFourierTransform)
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

	int err = 0;
	UINT statusText[2] = { 0, IDS_ABOUTBOX };

	// �X�e�[�^�X�o�[������
	if (!err) if (!statusBar.Create(this)) err = 1;
	if (!err) if (!statusBar.SetIndicators(statusText, 2)) err = 1;
	if (!err)
	{
		statusBar.SetPaneInfo(0, 0, SBPS_STRETCH, 0);
		statusBar.SetPaneInfo(1, IDS_ABOUTBOX, SBPS_NORMAL, 30);
		if (!statusBar.SetPaneText(0, _T("�X�e�[�^�X�o�["))) err = 1;
	}
	if (!err) RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

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

void CMainDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
}

///<summary>
/// �ۑ�2��1,2
/// ���N���b�N������f�̈ʒu�ARGB,HSV�̒l���X�e�[�^�X�o�[�ɕ\��
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
			msg.Format(_T("���W [x:%d y:%d] RGB[%d,%d,%d] HSV[%d,%d,%d]"), point.x, point.y, r, g, b, h, s, v);
			statusBar.SetPaneText(0, msg);
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


///<summary>
///�t�@�C������摜��ǂݍ���Ń����o�̔z���BITMAPINFO�ɒl��ݒ�
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
///�����o�̔z���BITMAPINFO���g�p���ĉ摜��\��
///</summary>
void CMainDlg::ShowImage(HDC hdc)
{
	SetDIBitsToDevice(hdc, 0, 0, bmpInfo.bmiHeader.biWidth, bmpInfo.bmiHeader.biHeight, 0, 0, 0, bmpInfo.bmiHeader.biHeight, pixelData, &bmpInfo, DIB_RGB_COLORS);
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

		statusBar.SetPaneText(0, _T("�t�@�C�����J���܂���"));
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
		statusBar.SetPaneText(0, _T("�t�@�C����ۑ����܂���"));
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

///<summary>
///���摜�����̂܂ܕ\��
///</summary>
void CMainDlg::OnMenuOriginal()
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

	int procMethod = 0;
	CProcessDlg dlg;
	dlg.SetValues(&procMethod);
	if (dlg.DoModal() != IDOK)
		return;

	COriginal process;
	switch (procMethod)
	{
	case 0://OpenCV�����p���ĊȒP����
		process.ProcessByFullOpenCV(filePath);
		break;
	case 1://�摜�ǂݍ��ݕۑ��̂�OpenCV���g�p���ăs�N�Z������̓X�N���b�`
		process.ProcessByPartOpenCV(filePath);
		break;
	case 2://OpenCV��S���g�킸�Ƀt���X�N���b�`
		process.ProcessByFullScratch(pixelData, &bmpInfo);
		break;
	}
}

///<summary>
///�O���C�X�P�[��
///</summary>
void CMainDlg::OnMenuGrayscale()
{
	int procMethod = 0;
	CProcessDlg dlg;
	dlg.SetValues(&procMethod);
	if (dlg.DoModal() != IDOK)
		return;

	CGrayscale process;
	switch (procMethod)
	{
	case 0://OpenCV�����p���ĊȒP����
		process.ProcessByFullOpenCV(filePath);
		break;
	case 1://�摜�ǂݍ��ݕۑ��̂�OpenCV���g�p���ăs�N�Z������̓X�N���b�`
		process.ProcessByPartOpenCV(filePath);
		break;
	case 2://OpenCV��S���g�킸�Ƀt���X�N���b�`
		process.ProcessByFullScratch(pixelData, &bmpInfo);
		break;
	}
}

///<summary>
///���T�C�Y
///</summary>
void CMainDlg::OnMenuResize()
{
	int procMethod = 0;
	CProcessDlg dlg;
	dlg.SetValues(&procMethod);
	if (dlg.DoModal() != IDOK)
		return;

	CResize process;
	switch (procMethod)
	{
	case 0://OpenCV�����p���ĊȒP����
		process.ProcessByFullOpenCV(filePath);
		break;
	case 1://�摜�ǂݍ��ݕۑ��̂�OpenCV���g�p���ăs�N�Z������̓X�N���b�`
		process.ProcessByPartOpenCV(filePath);
		break;
	case 2://OpenCV��S���g�킸�Ƀt���X�N���b�`
		process.ProcessByFullScratch(pixelData, &bmpInfo);
		break;
	}
}

///<summary>
///�ۑ�2��3
///</summary>
void CMainDlg::OnMenuNew()
{
	CSample sample;

	switch (1)
	{
	case 0://�J���[�t�B���^�pHSV
		sample.CreateColorSpaceImage(L"sample.hsv.jpg");
		break;
	case 1://�K�E�V�A���m�C�Y�t��
		sample.CreateGaussianNoiseImage(L"lena.jpg", L"sample.noise.jpg");
		break;
	case 2://�t�[���G�ϊ��p�T�C���g
		sample.CreateFrequencyImage(L"sample.sin.bmp");
		break;
	}
}

///<summary>
///�F��ԃt�B���^
///</summary>
void CMainDlg::OnMenuColorFilter()
{
	int procMethod = 0;
	CProcessDlg dlg;
	dlg.SetValues(&procMethod);
	if (dlg.DoModal() != IDOK)
		return;

	CHueFilter process;
	switch (procMethod)
	{
	case 0://OpenCV�����p���ĊȒP����
		process.ProcessByFullOpenCV(filePath);
		break;
	case 1://�摜�ǂݍ��ݕۑ��̂�OpenCV���g�p���ăs�N�Z������̓X�N���b�`
		//process.ProcessByPartOpenCV(filePath);
		break;
	case 2://OpenCV��S���g�킸�Ƀt���X�N���b�`
		process.ProcessByFullScratch(pixelData, &bmpInfo);
		break;
	}
}

///<summary>
///���ω��t�B���^
///</summary>
void CMainDlg::OnMenuAveragingFilter()
{
	int procMethod = 0;
	CProcessDlg dlg;
	dlg.SetValues(&procMethod);
	if (dlg.DoModal() != IDOK)
		return;

#pragma region ���ω��t�B���^�p�J�[�l��
	const std::vector<std::vector<int>> kernel3
	{
		{ 1, 1, 1 },
		{ 1, 1, 1 },
		{ 1, 1, 1 },
	};
	const std::vector<std::vector<int>> kernel5
	{ 
		{ 1, 1, 1, 1, 1 }, 
		{ 1, 1, 1, 1, 1 }, 
		{ 1, 1, 1, 1, 1 }, 
		{ 1, 1, 1, 1, 1 }, 
		{ 1, 1, 1, 1, 1 },
	};
	const std::vector<std::vector<int>> kernel7
	{
		{ 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1 },
	};
#pragma endregion

	int normalize = 0;
	//���K���p�̕���̒l���Z�o
	normalize = 0;
	for (auto row : kernel5)
		for (auto col : row)
			normalize += col;

	CKernelFilter filter;
	filter.SetKernel(CKernelFilter::FilterType::Averaging, kernel5, normalize);

	switch (procMethod)
	{
	case 0:
		filter.ProcessByFullOpenCV(filePath);
		break;
	case 1:
		filter.ProcessByPartOpenCV(filePath);
		break;
	case 2:
		filter.ProcessByFullScratch(pixelData, &bmpInfo);
		break;
	}
}

///<summary>
///�K�E�V�A���t�B���^
///</summary>
void CMainDlg::OnMenuGaussianFilter()
{
	int procMethod = 0;
	CProcessDlg dlg;
	dlg.SetValues(&procMethod);
	if (dlg.DoModal() != IDOK)
		return;

#pragma region �K�E�V�A���t�B���^�p�J�[�l��
	const std::vector<std::vector<int>> kernel3
	{
		{ 1, 2, 1 },
		{ 2, 4, 2 },
		{ 1, 2, 1 },
	};
	const std::vector<std::vector<int>> kernel5
	{
		{ 1,  4,  6,  4, 1 },
		{ 4, 16, 24, 16, 4 },
		{ 6, 24, 36, 24, 6 },
		{ 4, 16, 24, 16, 4 },
		{ 1,  4,  6,  4, 1 },
	};
	const std::vector<std::vector<int>> kernel7
	{
		{  1,   6,  15,  20,  15,   6,  1 },
		{  6,  36,  90, 120,  90,  36,  6 },
		{ 15,  90, 225, 300, 225,  90, 15 },
		{ 20, 120, 300, 400, 300, 120, 20 },
		{ 15,  90, 225, 300, 225,  90, 15 },
		{  6,  36,  90, 120,  90,  36,  6 },
		{  1,   6,  15,  20,  15,   6,  1 },
	};
#pragma endregion

	int normalize = 0;
	//���K���p�̕���̒l���Z�o
	normalize = 0;
	for (auto row : kernel5)
		for (auto col : row)
			normalize += col;

	CKernelFilter filter;
	filter.SetKernel(CKernelFilter::FilterType::Gaussian, kernel5, normalize);

	switch (procMethod)
	{
	case 0:
		filter.ProcessByFullOpenCV(filePath);
		break;
	case 1:
		filter.ProcessByPartOpenCV(filePath);
		break;
	case 2:
		filter.ProcessByFullScratch(pixelData, &bmpInfo);
		break;
	}
}

///<summary>
///�����t�B���^
///</summary>
void CMainDlg::OnMenuDifferencialFilter()
{
	int procMethod = 0;
	CProcessDlg dlg;
	dlg.SetValues(&procMethod);
	if (dlg.DoModal() != IDOK)
		return;

	//�c�t�B���^�Ɖ��t�B���^�����Z�����J�[�l��
	const std::vector<std::vector<int>> kernel
	{
		{  0,  1,  0 },
		{  1,  0, -1 },
		{  0, -1,  0 },
	};

	CKernelFilter filter;
	filter.SetKernel(CKernelFilter::FilterType::Differencial, kernel, 1);

	switch (procMethod)
	{
	case 0:
		filter.ProcessByFullOpenCV(filePath);
		break;
	case 1:
		filter.ProcessByPartOpenCV(filePath);
		break;
	case 2:
		filter.ProcessByFullScratch(pixelData, &bmpInfo);
		break;
	}
}

///<summary>
///�v�����[�E�B�b�g�t�B���^
///</summary>
void CMainDlg::OnMenuPrewittFilter()
{
	int procMethod = 0;
	CProcessDlg dlg;
	dlg.SetValues(&procMethod);
	if (dlg.DoModal() != IDOK)
		return;

	//�c�t�B���^�Ɖ��t�B���^�����Z�����J�[�l��
	const std::vector<std::vector<int>> kernel
	{
		{  0,  1,  2 },
		{ -1,  0,  1 },
		{ -2, -1,  0 },
	};

	CKernelFilter filter;
	filter.SetKernel(CKernelFilter::FilterType::Prewitt, kernel, 3);

	switch (procMethod)
	{
	case 0:
		filter.ProcessByFullOpenCV(filePath);
		break;
	case 1:
		filter.ProcessByPartOpenCV(filePath);
		break;
	case 2:
		filter.ProcessByFullScratch(pixelData, &bmpInfo);
		break;
	}
}

///<summary>
///�\�[�x���t�B���^
///</summary>
void CMainDlg::OnMenuSobelFilter()
{
	int procMethod = 0;
	CProcessDlg dlg;
	dlg.SetValues(&procMethod);
	if (dlg.DoModal() != IDOK)
		return;

	//�c�t�B���^�Ɖ��t�B���^�����Z�����J�[�l��
	const std::vector<std::vector<int>> kernel
	{
		{  0,  2,  2 },
		{ -2,  0,  2 },
		{ -2, -2,  0 },
	};

	CKernelFilter filter;
	filter.SetKernel(CKernelFilter::FilterType::Sobel, kernel, 4);

	switch (procMethod)
	{
	case 0:
		filter.ProcessByFullOpenCV(filePath);
		break;
	case 1:
		filter.ProcessByPartOpenCV(filePath);
		break;
	case 2:
		filter.ProcessByFullScratch(pixelData, &bmpInfo);
		break;
	}
}

///<summary>
///���v���V�A���t�B���^
///</summary>
void CMainDlg::OnMenuLaplacianFilter()
{
	int procMethod = 0;
	CProcessDlg dlg;
	dlg.SetValues(&procMethod);
	if (dlg.DoModal() != IDOK)
		return;

	const std::vector<std::vector<int>> kernel
	{
		{ 0,  1, 0 },
		{ 1, -4, 1 },
		{ 0,  1, 0 },
	};

	CKernelFilter filter;
	filter.SetKernel(CKernelFilter::FilterType::Laplacian, kernel, 1);

	switch (procMethod)
	{
	case 0:
		filter.ProcessByFullOpenCV(filePath);
		break;
	case 1:
		filter.ProcessByPartOpenCV(filePath);
		break;
	case 2:
		filter.ProcessByFullScratch(pixelData, &bmpInfo);
		break;
	}
}

///<summary>
///�N�s���t�B���^
///</summary>
void CMainDlg::OnMenuSharpeningFilter()
{
	int procMethod = 0;
	CProcessDlg dlg;
	dlg.SetValues(&procMethod);
	if (dlg.DoModal() != IDOK)
		return;

	const std::vector<std::vector<int>> kernel
	{
		{ -1, -1, -1 },
		{ -1,  9, -1 },
		{ -1, -1, -1 },
	};

	CKernelFilter filter;
	filter.SetKernel(CKernelFilter::FilterType::Sharpening, kernel, 1);

	switch (procMethod)
	{
	case 0:
		filter.ProcessByFullOpenCV(filePath);
		break;
	case 1:
		filter.ProcessByPartOpenCV(filePath);
		break;
	case 2:
		filter.ProcessByFullScratch(pixelData, &bmpInfo);
		break;
	}
}

///<summary>
///�o�C���e�����t�B���^
///</summary>
void CMainDlg::OnMenuBilateralFilter()
{
	int procMethod = 0;
	CProcessDlg dlg;
	dlg.SetValues(&procMethod);
	if (dlg.DoModal() != IDOK)
		return;

	CBilateralFilter filter;
	filter.SetKernel(3);

	switch (procMethod)
	{
	case 0:
		filter.ProcessByFullOpenCV(filePath);
		break;
	case 1:
		filter.ProcessByPartOpenCV(filePath);
		break;
	case 2:
		filter.ProcessByFullScratch(pixelData, &bmpInfo);
		break;
	}
}

///<summary>
///�m�����[�J���~�[���t�B���^
///</summary>
void CMainDlg::OnMenuNonLocalMeanFilter()
{
	int procMethod = 0;
	CProcessDlg dlg;
	dlg.SetValues(&procMethod);
	if (dlg.DoModal() != IDOK)
		return;

	CNonlocalMeansFilter filter;
	filter.SetKernel(3, 7);

	switch (procMethod)
	{
	case 0:
		filter.ProcessByFullOpenCV(filePath);
		break;
	case 1:
		filter.ProcessByPartOpenCV(filePath);
		break;
	case 2:
		filter.ProcessByFullScratch(pixelData, &bmpInfo);
		break;
	}
}

///<summary>
///���f�B�A���t�B���^
///</summary>
void CMainDlg::OnMenuMedialFilter()
{
	int procMethod = 0;
	CProcessDlg dlg;
	dlg.SetValues(&procMethod);
	if (dlg.DoModal() != IDOK)
		return;

	CMedianFilter filter;
	filter.SetKernel(3);

	switch (procMethod)
	{
	case 0:
		filter.ProcessByFullOpenCV(filePath);
		break;
	case 1:
		filter.ProcessByPartOpenCV(filePath);
		break;
	case 2:
		filter.ProcessByFullScratch(pixelData, &bmpInfo);
		break;
	}
}


void CMainDlg::OnMenuFourierTransform()
{
	int procMethod = 0;
	CProcessDlg dlg;
	dlg.SetValues(&procMethod);
	if (dlg.DoModal() != IDOK)
		return;

	CFourierTransform process;

	switch (procMethod)
	{
	case 0:
		process.ProcessByFullOpenCV(filePath);
		break;
	case 1:
		process.ProcessByPartOpenCV(filePath);
		break;
	case 2:
		process.ProcessByFullScratch(pixelData, &bmpInfo);
		break;
	}
}


void CMainDlg::OnMenuInverseFourierTransform()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
}

#pragma endregion
