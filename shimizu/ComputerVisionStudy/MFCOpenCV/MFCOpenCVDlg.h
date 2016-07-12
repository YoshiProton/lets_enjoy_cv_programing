
// MFCOpenCVDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// CMFCOpenCVDlg �_�C�A���O
class CMFCOpenCVDlg : public CDialogEx
{
// �R���X�g���N�V����
public:
	CMFCOpenCVDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^�[

// �_�C�A���O �f�[�^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCOPENCV_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g


// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
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
