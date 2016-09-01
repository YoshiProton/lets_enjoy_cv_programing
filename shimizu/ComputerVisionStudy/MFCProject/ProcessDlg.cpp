// ProcessDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MFCProject.h"
#include "ProcessDlg.h"
#include "afxdialogex.h"


// CProcessDlg �_�C�A���O

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


// CResizeDlg ���b�Z�[�W �n���h���[
void CProcessDlg::SetValues(int* algo)
{
	pAlgo = algo;
}


// CProcessDlg ���b�Z�[�W �n���h���[


void CProcessDlg::OnOK()
{
	UpdateData(TRUE);

	*pAlgo = algorithm;

	CDialogEx::OnOK();
}
