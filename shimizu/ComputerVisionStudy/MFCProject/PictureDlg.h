#pragma once
#include "afxwin.h"


// CPictureDlg �_�C�A���O

class CPictureDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPictureDlg)

public:
	CPictureDlg(CImage*, CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CPictureDlg();

// �_�C�A���O �f�[�^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PICTUREBOX };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()

	CImage* pImage;
	BOOL SetClientSize(HWND hWnd, int width, int height);

	afx_msg void OnPaint();
};
