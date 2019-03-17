// MFCApplicationDLL.cpp : DLL の初期化ルーチンを定義します。
//

#include "stdafx.h"
#include "MFCApplicationDLL.h"
#include "SDGDLLEX.H"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SDGDLL_VER	(0x100)				// DLLバージョンの宣言

MC_SDGHEAD(
	_T("通信応答テストプログラム"),
	_T("データを受信したら要求コードをチェックして\r\n")
	_T("OK、ERRを返送します。\r\n")
);

//
//TODO: この DLL が MFC DLL に対して動的にリンクされる場合、
//		MFC 内で呼び出されるこの DLL からエクスポートされたどの関数も
//		関数の最初に追加される AFX_MANAGE_STATE マクロを
//		持たなければなりません。
//
//		例:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 通常関数の本体はこの位置にあります
//		}
//
//		このマクロが各関数に含まれていること、MFC 内の
//		どの呼び出しより優先することは非常に重要です。
//		it は、次の範囲内で最初のステートメントとして表示されるべきです
//		らないことを意味します、コンストラクターが MFC
//		DLL 内への呼び出しを行う可能性があるので、オブ
//		ジェクト変数の宣言よりも前でなければなりません。
//
//		詳細については MFC テクニカル ノート 33 および
//		58 を参照してください。
//

// CMFCApplicationDLLApp

BEGIN_MESSAGE_MAP(CMFCApplicationDLLApp, CWinApp)
END_MESSAGE_MAP()


// CMFCApplicationDLLApp の構築

CMFCApplicationDLLApp::CMFCApplicationDLLApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}


// 唯一の CMFCApplicationDLLApp オブジェクト

CMFCApplicationDLLApp theApp;


// CMFCApplicationDLLApp の初期化

BOOL CMFCApplicationDLLApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

// 電文比較用変数の宣言
unsigned char bytecode[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
							 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10 };

//------------------------------------------------
//	SDGコールバック関数
//------------------------------------------------
DWORD WINAPI CallBackSDG(ULONG dest, ULONG src) {
	MC_MODULEUSE;                           // 変数宣言
//----------------------------------------------
//  定型マクロ処理
//----------------------------------------------
	MC_EV_DEFAULT;                          // 基本パラメータセット
	MC_EV_GETCOMMENT;                       // DLLのコメント情報を取得する
	MC_EV_GETVER;                           // ver.を取得する
	MC_EV_CONFIGRESULT(SDGDLL_CONFIGUSE);   // コンフィグの有無を取得する
	//----------------------------------------------
	//  データ受信
	//----------------------------------------------
	if (srcData->command & SDGDLL_ONRECEIVE) {
		int nCmd = FALSE;            // はじめはエラー返送をセット

		// 電文チェックを行う
		nCmd = CMFCApplicationDLLApp::recvDataChk(destData, srcData);

		destData->command = SDGDLL_REQSEND;     // データ送信要求を行う
		destData->wparam = 0;                   // 受信したポートのみ返送する
		destData->lpbuffer = srcData->lpbuffer; // 受信データエリアを
												// 送信データエリアに流用
		// ここで、受信データエリアは通信の設定で決めた
		//「内部プログラム受信バッファサイズ」が適用されていますので、
		// そのサイズまでは上書きが可能になります。
		// サイズがそれを超過する可能性がある通信仕様では、
		// 内部で確保する必要があります。
		// 確保した場合は開放のタイミングを作成することをお忘れなく

		//TODO: 電文の構造体を作成してvoidポインタでキャストして使用する。


		// 送信された電文の下位1バイトを記録しておく

		destData->myLparam = ++srcData->myLparam;
		destData->myWparam = srcData->command;

		//lstrcpy((char *)destData->myWparam, (char *)destData->lpbuffer);

		//memcpy((void *)destData->myLparam ,&srcData->lpbuffer, 1);
		//memcpy((void *)destData->myWparam, &srcData->lpbuffer, 2);

		if (nCmd > FALSE) {
			CMFCApplicationDLLApp::sendMakeData(nCmd, destData, srcData);
			//destData->buffsize = 2;             // 送信データは2Byte
			//lstrcpy((char *)destData->lpbuffer, _T("OK"));
		}
		else {
			destData->buffsize = 3;             // 送信データは3Byte
			lstrcpy((char *)destData->lpbuffer, _T("ERR"));
		}
		return SDGDLL_RESULTOK;
	}
	return SDGDLL_RESULTOK;
}

int CMFCApplicationDLLApp::recvDataChk(SDGDLLSTRUCT* destData, SDGDLLSTRUCT* srcData)
{
	int nCmd = FALSE;
	if (srcData->buffsize == 8) {       // 受信データは規定のサイズ？
		//if (memcmp(srcData->lpbuffer, _T("A0000000"), 8) == 0 ||
		//	memcmp(srcData->lpbuffer, _T("A0000001"), 8) == 0 ||
		//	memcmp(srcData->lpbuffer, bytecode, 8) == 0) {
		nCmd = TRUE;             // OKの返送を行う
		//}
	}

	unsigned char* cBuf = (unsigned char *)srcData->lpbuffer;

	// ログ出力する
	destData->logbuffer = srcData->logbuffer;
	destData->logtype = 1;	//1:情報、2:注意、3:警告

	// コマンド格納位置
	char cmd = cBuf[0];

	// コマンドを比較する
	switch (cmd)
	{
	case order:
		lstrcpy((char *)destData->logbuffer, _T("依頼電文を受信"));
		nCmd = order;
		break;
	case result:
		lstrcpy((char *)destData->logbuffer, _T("結果電文を受信"));
		nCmd = result;
		break;
	default:
		break;
	}
	return nCmd;
}

void CMFCApplicationDLLApp::sendMakeData(int nCmd, SDGDLLSTRUCT* destData, SDGDLLSTRUCT* srcData)
{
	CString buf;
	// コマンドを比較する
	switch (nCmd)
	{
	case order:
		// TODO:文字列を別ファイルから取得するようにする
		buf = "OKKKKKKKKK";
		destData->buffsize = buf.GetLength();
		lstrcpy((char *)destData->lpbuffer, buf);
		break;
	case result:
		// TODO:文字列を別ファイルから取得するようにする
		buf = "OKKKKKKKKオマーン代表戦K";
		destData->buffsize = buf.GetLength();
		lstrcpy((char *)destData->lpbuffer, buf);
		break;
	default:
		break;
	}


}