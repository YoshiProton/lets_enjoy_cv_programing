// PictureDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MFCProject.h"
#include "PictureDlg.h"
#include "afxdialogex.h"


// CPictureDlg ダイアログ

IMPLEMENT_DYNAMIC(CPictureDlg, CDialogEx)

CPictureDlg::CPictureDlg(CImage* img, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PICTUREBOX, pParent)
{
	pImage = img;
}

CPictureDlg::~CPictureDlg()
{
}

void CPictureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPictureDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CPictureDlg メッセージ ハンドラー


BOOL CPictureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: ここに初期化を追加してください
	SetClientSize(this->m_hWnd, pImage->GetWidth(), pImage->GetHeight());

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}


void CPictureDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ここにメッセージ ハンドラー コードを追加します。
					   // 描画メッセージで CDialogEx::OnPaint() を呼び出さないでください。
	pImage->BitBlt(::GetDC(this->m_hWnd), 0, 0);
}

BOOL CPictureDlg::SetClientSize(HWND hWnd, int width, int height)
{
	RECT rw, rc;
	::GetWindowRect(hWnd, &rw);
	::GetClientRect(hWnd, &rc);

	int new_width = (rw.right - rw.left) - (rc.right - rc.left) + width;
	int new_height = (rw.bottom - rw.top) - (rc.bottom - rc.top) + height;

	return ::SetWindowPos(hWnd, NULL, 0, 0, new_width, new_height, SWP_NOMOVE | SWP_NOZORDER);
}
