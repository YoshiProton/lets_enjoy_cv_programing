// HueFilterDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MFCProject.h"
#include "HueFilterDlg.h"
#include "afxdialogex.h"


// CHueFilterDlg ダイアログ

IMPLEMENT_DYNAMIC(CHueFilterDlg, CDialogEx)

CHueFilterDlg::CHueFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HUEFILTERBOX, pParent)
{
}

CHueFilterDlg::~CHueFilterDlg()
{
}

void CHueFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HUE_FILTER_SLIDER, hueSliderCtrl);
}


BEGIN_MESSAGE_MAP(CHueFilterDlg, CDialogEx)
	ON_BN_CLICKED(IDC_HUE_START_BUTTON, &CHueFilterDlg::OnBnClickedHueStartButton)
	ON_BN_CLICKED(IDC_HUE_END_BUTTON, &CHueFilterDlg::OnBnClickedHueEndButton)
	ON_BN_CLICKED(IDC_HUE_RESET_BUTTON, &CHueFilterDlg::OnBnClickedHueResetButton)
END_MESSAGE_MAP()


// CHueFilterDlg メッセージ ハンドラー


BOOL CHueFilterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: ここに初期化を追加してください
	hueSliderCtrl.SetRange(0, 180, false);
	//*pRangeStart = 0;
	//*pRangeEnd = 180;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}


void CHueFilterDlg::SetValues(int* start, int* end)
{
	*start = 0;
	*end = 0;
	pRangeStart = start;
	pRangeEnd = end;
}

void CHueFilterDlg::OnBnClickedHueStartButton()
{
	*pRangeStart = hueSliderCtrl.GetPos();
	hueSliderCtrl.SetSelection(*pRangeStart, *pRangeStart);
}


void CHueFilterDlg::OnBnClickedHueEndButton()
{
	*pRangeEnd = hueSliderCtrl.GetPos();
	hueSliderCtrl.SetSelection(*pRangeStart, *pRangeEnd);
}


void CHueFilterDlg::OnBnClickedHueResetButton()
{
	*pRangeStart = *pRangeEnd = -1;
	hueSliderCtrl.ClearSel();
}

void CHueFilterDlg::OnOK()
{
	UpdateData(TRUE);

	hueSliderCtrl.GetSelection(*pRangeStart, *pRangeEnd);
	if (*pRangeStart < *pRangeEnd)
	{
		CDialogEx::OnOK();
	}
	else
	{
		AfxMessageBox(L"指定範囲が間違っています");
	}
}
