
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
	ON_COMMAND(ID_MENU_ORIGINAL, &CMainDlg::OnMenuOriginal)
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
	filePath = "lena.jpg";

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
		CDialogEx::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#pragma region �摜�����ȊO�̃��j���[�I���C�x���g
void CMainDlg::OnMenuExit()
{
	OnOK();
	//OnCancel();
}

//�t�@�C�����J�����j���[�I��
void CMainDlg::OnMenuOpen()
{
	CBitmap bmp;
	CImage image;
	image.Load(_T("lena.jpg"));
	bmp.Attach(image.Detach());
	CStatic* pictbox = (CStatic*)GetDlgItem(IDC_STATIC_PICTURE);
	pictbox->SetBitmap(bmp);

	//�z��ɕϊ�
	//http://killswitch5375.hatenablog.com/entry/20100601/p1
	//HBITMAP hBitmap = (HBITMAP)image;
	//GetBitmapBits(hBitmap, size, buff);
	//HDC hdc = image.GetDC();
	//image.ReleaseDC();
	image.Destroy();
}

//�t�@�C����ۑ����j���[�I��
void CMainDlg::OnMenuSave()
{

}

//�A�o�E�g���j���I��
void CMainDlg::OnMenuAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}
#pragma endregion

#pragma region �摜�������j���[�I���C�x���g

#pragma region ���摜�����̂܂ܕ\��
void CMainDlg::OnMenuOriginal()
{
	COriginal process;
	process.Execute(filePath);
}
#pragma endregion

#pragma region �O���C�X�P�[����
//OpenCV�����p���ĊȒP����
void CMainDlg::OnMenuGrayscaleFullOpenCV()
{
	CGrayscale process;
	process.SetProcessMethod(ProcessMethod::FullOpenCV);
	process.Execute(filePath);
}

//�摜�ǂݍ��ݕۑ��̂�OpenCV���g�p���ăs�N�Z������̓X�N���b�`
void CMainDlg::OnMenuGrayscaleHalfOpenCV()
{
	CGrayscale process;
	process.SetProcessMethod(ProcessMethod::HalfOpenCV);
	process.Execute(filePath);
}

//OpenCV��S���g�킸�Ƀt���X�N���b�`
void CMainDlg::OnMenuGrayscaleScratch()
{
	CGrayscale process;
	process.SetProcessMethod(ProcessMethod::FullScratch);
	process.Execute(filePath);
}
#pragma endregion

#pragma region ���T�C�Y
//OpenCV�����p���ĊȒP����
void CMainDlg::OnMenuResizeFullOpenCV()
{
	CResize process;
	process.SetProcessMethod(ProcessMethod::FullOpenCV);
	process.Execute(filePath);
}

//�摜�ǂݍ��ݕۑ��̂�OpenCV���g�p���ăs�N�Z������̓X�N���b�`
void CMainDlg::OnMenuResizeHalfOpenCV()
{
	CResize process;
	process.SetProcessMethod(ProcessMethod::HalfOpenCV);
	process.Execute(filePath);
}

//OpenCV��S���g�킸�Ƀt���X�N���b�`
void CMainDlg::OnMenuResizeScratch()
{
	CResize process;
	process.SetProcessMethod(ProcessMethod::FullScratch);
	process.Execute(filePath);
}
#pragma endregion

#pragma endregion
