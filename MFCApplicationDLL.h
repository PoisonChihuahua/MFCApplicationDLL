// MFCApplicationDLL.h : MFCApplicationDLL DLL のメイン ヘッダー ファイル
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル
#include "SDGDLLEX.H"

enum cmdList {
	order = 'A',
	result = 'R'
};

// CMFCApplicationDLLApp
// このクラスの実装に関しては MFCApplicationDLL.cpp をご覧ください
//

class CMFCApplicationDLLApp : public CWinApp
{
public:
	CMFCApplicationDLLApp();

// オーバーライド
public:
	virtual BOOL InitInstance();
	static int recvDataChk(SDGDLLSTRUCT* destData, SDGDLLSTRUCT* srcData);
	static void sendMakeData(int nCmd, SDGDLLSTRUCT* destData, SDGDLLSTRUCT* srcData);

	DECLARE_MESSAGE_MAP()
};
