// ColorSpaceDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MFCProject.h"
#include "ColorSpaceDlg.h"
#include "afxdialogex.h"
#include "Utility.h"

// CColorSpaceDlg ダイアログ

IMPLEMENT_DYNAMIC(CColorSpaceDlg, CDialogEx)

CColorSpaceDlg::CColorSpaceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COLORSPACEBOX, pParent)
	, width(256)
	, height(256)
	, sliderRValue(_T("R : 128"))
	, sliderGValue(_T("G : 128"))
	, sliderBValue(_T("B : 128"))
	, sliderHValue(_T("H : 0"))
	, sliderSValue(_T("S : 255"))
	, sliderVValue(_T("V : 255"))
{

}

CColorSpaceDlg::~CColorSpaceDlg()
{
}

void CColorSpaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_WIDTH, width);
	DDV_MinMaxUInt(pDX, width, 0, 1920);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, height);
	DDV_MinMaxUInt(pDX, height, 0, 1920);
	DDX_Control(pDX, IDC_EDIT_WIDTH, widthEdit);
	DDX_Control(pDX, IDC_EDIT_HEIGHT, heightEdit);
	DDX_Control(pDX, IDC_SLIDER_R, sliderRCtrl);
	DDX_Control(pDX, IDC_SLIDER_G, sliderGCtrl);
	DDX_Control(pDX, IDC_SLIDER_B, sliderBCtrl);
	DDX_Control(pDX, IDC_SLIDER_H, sliderHCtrl);
	DDX_Control(pDX, IDC_SLIDER_S, sliderSCtrl);
	DDX_Control(pDX, IDC_SLIDER_V, sliderVCtrl);
	DDX_Text(pDX, IDC_STATIC_R, sliderRValue);
	DDX_Text(pDX, IDC_STATIC_G, sliderGValue);
	DDX_Text(pDX, IDC_STATIC_B, sliderBValue);
	DDX_Text(pDX, IDC_STATIC_H, sliderHValue);
	DDX_Text(pDX, IDC_STATIC_S, sliderSValue);
	DDX_Text(pDX, IDC_STATIC_V, sliderVValue);
}


BEGIN_MESSAGE_MAP(CColorSpaceDlg, CDialogEx)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CColorSpaceDlg メッセージ ハンドラー


BOOL CColorSpaceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: ここに初期化を追加してください
	sliderRCtrl.SetRange(0, 255);
	sliderRCtrl.SetPageSize(16);
	sliderRCtrl.SetPos(127);

	sliderGCtrl.SetRange(0, 255);
	sliderGCtrl.SetPageSize(16);
	sliderGCtrl.SetPos(127);

	sliderBCtrl.SetRange(0, 255);
	sliderBCtrl.SetPageSize(16);
	sliderBCtrl.SetPos(127);

	sliderHCtrl.SetRange(0, 180);
	sliderHCtrl.SetPageSize(20);
	sliderHCtrl.SetPos(0);

	sliderSCtrl.SetRange(0, 255);
	sliderSCtrl.SetPageSize(16);
	sliderSCtrl.SetPos(0);

	sliderVCtrl.SetRange(0, 255);
	sliderVCtrl.SetPageSize(16);
	sliderVCtrl.SetPos(127);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CColorSpaceDlg::SetValues(int* w, int* h, int* pR, int* pG, int* pB)
{
	pWidth = w;
	pHeight = h;

	pRed = pR;
	pGreen = pG;
	pBlue = pB;
}

void CColorSpaceDlg::OnOK()
{
	UpdateData(TRUE);

	*pWidth = width;
	*pHeight = height;
	*pRed = sliderRCtrl.GetPos();
	*pGreen = sliderGCtrl.GetPos();
	*pBlue = sliderBCtrl.GetPos();

	CDialogEx::OnOK();
}

void CColorSpaceDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CSliderCtrl* pSb = (CSliderCtrl*)pScrollBar;

	//RGBのいずれかのスライダーが変更された場合
	if (pSb == &sliderRCtrl || pSb == &sliderGCtrl || pSb == &sliderBCtrl)
	{
		int r = sliderRCtrl.GetPos();
		int g = sliderGCtrl.GetPos();
		int b = sliderBCtrl.GetPos();

		sliderRValue.Format(L"R : %d", r);
		sliderGValue.Format(L"G : %d", g);
		sliderBValue.Format(L"B : %d", b);

		int h, s, v;
		CUtility::ConvertRGBtoHSV(r, g, b, &h, &s, &v);

		//RGBが変更されるとHSVも変わるので計算してラベル（値）に反映
		sliderHCtrl.SetPos(h);
		sliderHValue.Format(L"H : %d", h);
		sliderSCtrl.SetPos(s);
		sliderSValue.Format(L"S : %d", s);
		sliderVCtrl.SetPos(v);
		sliderVValue.Format(L"V : %d", v);
	}
	//HSVのいずれかのスライダーが変更された場合
	else if (pSb == &sliderHCtrl || pSb == &sliderSCtrl || pSb == &sliderVCtrl)
	{
		int h = sliderHCtrl.GetPos();
		int s = sliderSCtrl.GetPos();
		int v = sliderVCtrl.GetPos();

		sliderHValue.Format(L"H : %d", h);
		sliderSValue.Format(L"S : %d", s);
		sliderVValue.Format(L"V : %d", v);

		int r, g, b;
		CUtility::ConvertHSVtoRGB(h, s, v, &r, &g, &b);

		//HSVが変更されるとRGBも変わるので計算してラベル（値）に反映
		sliderRCtrl.SetPos(r);
		sliderRValue.Format(L"R : %d", r);
		sliderGCtrl.SetPos(g);
		sliderGValue.Format(L"G : %d", g);
		sliderBCtrl.SetPos(b);
		sliderBValue.Format(L"B : %d", b);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);

	UpdateData(FALSE);
}
