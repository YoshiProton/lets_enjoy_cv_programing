#pragma once


// CProcessDlg �_�C�A���O

class CProcessDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProcessDlg)

public:
	CProcessDlg(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CProcessDlg();
	void SetValues(int*);

// �_�C�A���O �f�[�^
	enum { IDD = IDD_PROCESSTYPE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()

private:
	int algorithm;
	int* pAlgo;
	virtual void OnOK();
};
