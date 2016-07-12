
// MFCOpenCVDlg.h : ヘッダー ファイル
//

#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// CMFCOpenCVDlg ダイアログ
class CMFCOpenCVDlg : public CDialogEx
{
// コンストラクション
public:
	CMFCOpenCVDlg(CWnd* pParent = NULL);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCOPENCV_DIALOG };
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
	void iplTobmp(const IplImage* srcIplImage, BITMAPINFO& bmpInfo, unsigned long* bmpData);
	void DrawPicToHDC(cv::Mat cvImg, UINT ID, bool bOnPaint);
public:
	afx_msg void OnMenuExit();
	afx_msg void OnMenuOpen();
	afx_msg void OnMenuAbout();
};
