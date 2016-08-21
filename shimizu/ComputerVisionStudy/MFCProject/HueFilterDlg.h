#pragma once
#include "afxcmn.h"


// CHueFilterDlg �_�C�A���O

class CHueFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHueFilterDlg)

public:
	CHueFilterDlg(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CHueFilterDlg();

// �_�C�A���O �f�[�^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HUEFILTERBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	void SetValues(int*, int*);

private:
	CSliderCtrl hueSliderCtrl;
	int* pRangeStart;
	int* pRangeEnd;
	virtual void OnOK();

public:
	afx_msg void OnBnClickedHueStartButton();
	afx_msg void OnBnClickedHueEndButton();
	afx_msg void OnBnClickedHueResetButton();
};
