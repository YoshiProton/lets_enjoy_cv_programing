// ResizeDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MFCProject.h"
#include "ResizeDlg.h"
#include "afxdialogex.h"


// CResizeDlg �_�C�A���O

IMPLEMENT_DYNAMIC(CResizeDlg, CDialogEx)

CResizeDlg::CResizeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RESIEBOX, pParent)
	, sliderValue(0)
	, algorithm(0)
{
}

CResizeDlg::~CResizeDlg()
{
}

void CResizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, sliderCtrl);
	DDX_Slider(pDX, IDC_SLIDER1, sliderValue);
	DDV_MinMaxInt(pDX, sliderValue, 0, 4);
	DDX_Radio(pDX, IDC_RADIO_NEARESTNEIGHBOR, algorithm);
}


BEGIN_MESSAGE_MAP(CResizeDlg, CDialogEx)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CResizeDlg ���b�Z�[�W �n���h���[
void CResizeDlg::SetValues(double* ratio, int* algo)
{
	pRatio = ratio;
	pAlgo = algo;
}

BOOL CResizeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	sliderCtrl.SetRange(0, 4);
	sliderCtrl.SetPageSize(1);
	sliderValue = 2;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}


void CResizeDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int pageSize = sliderCtrl.GetPageSize();
	int min;
	int max;

	switch (nSBCode)
	{
		// �܂݂��h���b�O
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		sliderValue = nPos;
		break;
		// �܂ݍ����A�㑤���N���b�N
	case SB_PAGELEFT:
		//case SB_PAGEUP:
		sliderCtrl.GetRange(min, max);
		sliderValue = (sliderValue - pageSize > min) ? sliderValue - pageSize : min;
		break;
		// �܂݉E���A�������N���b�N
	case SB_PAGERIGHT:
		//case SB_PAGEDOWN:
		sliderCtrl.GetRange(min, max);
		sliderValue = (sliderValue + pageSize < max) ? sliderValue + pageSize : max;
		break;
	default:
		break;
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CResizeDlg::OnOK()
{
	UpdateData();

	switch (sliderValue)
	{
	case 0:
		*pRatio = 0.33333;
		break;
	case 1:
		*pRatio = 0.5;
		break;
	case 3:
		*pRatio = 2.0;
		break;
	case 4:
		*pRatio = 3.0;
		break;
	default:
		*pRatio = 1.0;
		break;
	}

	*pAlgo = algorithm;

	//CString msg;
	//msg.Format(_T("�A���S���Y��%d���I������Ă��܂��B�{����%f�ł��B"), *pAlgo + 1, *pRatio);
	//MessageBox(msg);

	CDialogEx::OnOK();
}
