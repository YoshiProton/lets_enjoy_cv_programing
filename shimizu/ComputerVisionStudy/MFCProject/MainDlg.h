
// MainDlg.h : ヘッダー ファイル
//

#pragma once
#include <string> 
#include "afxwin.h"

// CMainDlg ダイアログ
class CMainDlg : public CDialogEx
{
// コンストラクション
public:
	CMainDlg(CWnd* pParent = NULL);	// 標準コンストラクター
	~CMainDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCPROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CImage image;
	CString filePath;
	LPCOLORREF lpcrPixelData;
	BITMAPINFO bmpInfo;
	UINT WIDTH;
	UINT HEIGHT;
	void LoadImage(HDC);
	void ShowImage(HDC);

public:
	afx_msg void OnMenuExit();
	afx_msg void OnMenuOpen();
	afx_msg void OnMenuSave();
	afx_msg void OnMenuAbout();

	afx_msg void OnMenuOriginalFullOpenCV();
	afx_msg void OnMenuOriginalScratch();

	afx_msg void OnMenuGrayscaleFullOpenCV();
	afx_msg void OnMenuGrayscaleHalfOpenCV();
	afx_msg void OnMenuGrayscaleScratch();

	afx_msg void OnMenuResizeFullOpenCV();
	afx_msg void OnMenuResizeHalfOpenCV();
	afx_msg void OnMenuResizeScratch();
};
