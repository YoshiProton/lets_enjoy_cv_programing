#pragma once
#include "afxwin.h"


// CPictureDlg ダイアログ

class CPictureDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPictureDlg)

public:
	CPictureDlg(CImage*, CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CPictureDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PICTUREBOX };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()

	CImage* pImage;
	BOOL SetClientSize(HWND hWnd, int width, int height);

	afx_msg void OnPaint();
};
