
// MFCOpenCV.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMFCOpenCVApp:
// このクラスの実装については、MFCOpenCV.cpp を参照してください。
//

class CMFCOpenCVApp : public CWinApp
{
public:
	CMFCOpenCVApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CMFCOpenCVApp theApp;