#pragma once
#include "afxcmn.h"


// CResizeDlg ダイアログ

class CResizeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CResizeDlg)

public:
	CResizeDlg(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CResizeDlg();
	void SetValues(double*, int*);

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESIZEBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

private:
	CSliderCtrl sliderCtrl;
	double* pRatio;
	int sliderValue;
	int algorithm;
	int* pAlgo;
	virtual void OnOK();
};
