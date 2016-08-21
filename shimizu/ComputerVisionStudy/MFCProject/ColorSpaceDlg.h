#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxcmn.h"


// CColorSpaceDlg ダイアログ

class CColorSpaceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CColorSpaceDlg)

public:
	CColorSpaceDlg(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CColorSpaceDlg();
	virtual BOOL OnInitDialog();
	void SetValues(int*, int*, int*, int*, int*);

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLORSPACEBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()

private:
	UINT width;
	UINT height;

	int* pWidth;
	int* pHeight;
	int* pRed;
	int* pGreen;
	int* pBlue;

	virtual void OnOK();

public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

private:
	CEdit widthEdit;
	CEdit heightEdit;
	CString sliderRValue;
	CString sliderGValue;
	CString sliderBValue;
	CString sliderHValue;
	CString sliderSValue;
	CString sliderVValue;
	CSliderCtrl sliderRCtrl;
	CSliderCtrl sliderGCtrl;
	CSliderCtrl sliderBCtrl;
	CSliderCtrl sliderHCtrl;
	CSliderCtrl sliderSCtrl;
	CSliderCtrl sliderVCtrl;
};
