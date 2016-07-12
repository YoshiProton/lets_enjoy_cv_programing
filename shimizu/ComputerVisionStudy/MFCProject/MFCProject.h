
// MFCProject.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMFCProjectApp:
// このクラスの実装については、MFCProject.cpp を参照してください。
//

class CMFCProjectApp : public CWinApp
{
public:
	CMFCProjectApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CMFCProjectApp theApp;