// ProcessDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MFCProject.h"
#include "ProcessDlg.h"
#include "afxdialogex.h"


// CProcessDlg ダイアログ

IMPLEMENT_DYNAMIC(CProcessDlg, CDialogEx)

CProcessDlg::CProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProcessDlg::IDD, pParent)
	, algorithm(0)
{

}

CProcessDlg::~CProcessDlg()
{
}

void CProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_PROCESSTYPE_RADIO1, algorithm);
}


BEGIN_MESSAGE_MAP(CProcessDlg, CDialogEx)
END_MESSAGE_MAP()


// CResizeDlg メッセージ ハンドラー
void CProcessDlg::SetValues(int* algo)
{
	pAlgo = algo;
}


// CProcessDlg メッセージ ハンドラー


void CProcessDlg::OnOK()
{
	UpdateData(TRUE);

	*pAlgo = algorithm;

	CDialogEx::OnOK();
}
