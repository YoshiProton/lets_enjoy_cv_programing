#pragma once


// CProcessDlg ダイアログ

class CProcessDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProcessDlg)

public:
	CProcessDlg(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CProcessDlg();
	void SetValues(int*);

// ダイアログ データ
	enum { IDD = IDD_PROCESSTYPE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()

private:
	int algorithm;
	int* pAlgo;
	virtual void OnOK();
};
