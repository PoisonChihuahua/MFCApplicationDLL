//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
//┃SDGDLLEX.H                                                                                  ┃
//┠──────────────────────────────────────────────┨
//┃拡張DLL向け、ヘッダファイル                                                                 ┃
//┃ver.	1.00	2004/12/11                                                                  ┃
//┃ver.	1.01	2004/12/12 マクロ追加                                                       ┃
//┃ver.	1.02	2004/12/17 定義追加 タイマーに1Timeタイマー追加                             ┃
//┃ver.	1.06	2005/01/09 定義追加 送信時の送信ポート指定追加                              ┃
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
#pragma once

//関数戻り値
#define	SDGDLL_RESULTOK			(0)					// CallBack関数 OK
#define	SDGDLL_RESULTERROR		(1)					// CallBack関数 NG
#define	SDGDLL_RESULTCANCEL		(2)					// CallBack関数 (Cancel)

#define SDGDLL_CONFIGUSE		(1)					// Config設定あり
#define SDGDLL_CONFIGNOT		(0)					// Config情報なし

#define SDGDLL_LOGINFO			(1)					// LOG INFO
#define SDGDLL_LOGEXCL			(2)					// LOG EXCL
#define SDGDLL_LOGERR			(3)					// LOG ERROR

#define SDGDLL_TIMER1			(0x00000000)		// Timer No.1
#define SDGDLL_TIMER2			(0x00000001)		// Timer No.2
#define SDGDLL_TIMER_1TIME		(0x80000000)		// １回だけ有効のタイマー

//要求パラメータビット(イベント)
#define SDGDLL_ONCONNECT		(0x00000001)		// 接続完了
#define SDGDLL_ONCLOSE			(0x00000002)		// 切断
#define SDGDLL_ONRECEIVE		(0x00000004)		// データ受信
#define SDGDLL_ONSEND 			(0x00000008)		// データ送信要求
#define SDGDLL_ONTIMER 			(0x00000010)		// タイマーイベント

//要求パラメータビット(要求コマンド)
#define SDGDLL_REQSEND			(0x00000100)		// 送信要求
#define SDGDLL_REQCLOSE			(0x00000200)		// 切断要求
#define SDGDLL_REQSTARTTIMER	(0x00000400)		// タイマーイベント(開始)要求
#define SDGDLL_REQSTOPTIMER		(0x00000800)		// タイマーイベント(停止)要求
#define SDGDLL_REQEDITER		(0x00001000)		// エディタデータ取得要求(アンサー有り)
#define SDGDLL_REQSETEDITER		(0x00002000)		// エディタデータ設定要求

//要求パラメータビット(その他イベントなど)
#define SDGDLL_GETCOMMENT		(0x01000000)		// コメント取得要求
#define SDGDLL_GETVER			(0x02000000)		// Ver.取得(戻り値による)
#define SDGDLL_CONFIGRESULT		(0x04000000)		// コンフィグ設定あり？
#define SDGDLL_EDITCONFIG		(0x08000000)		// 設定画面表示
#define SDGDLL_SETCONFIG		(0x10000000)		// 設定セット
#define SDGDLL_RECALL			(0x80000000)		// コマンド実行後再呼び出し指定

//データ送信時指定
#define SDGDLL_SEND_ME			(0)					// 対応したポートで送信
#define SDGDLL_SEND_PORT1		(1)					// ポート１（全て）で送信
#define SDGDLL_SEND_PORT2		(2)					// ポート２（全て）で送信
//---------------------------------------------------------------
//	CallBack 関数 パラメータ
//---------------------------------------------------------------
typedef struct {
	DWORD	command;	// コマンド
	DWORD	wparam;		// パラメータ(1)
	DWORD	lparam;		// パラメータ(2)
	DWORD	myWparam;	// DLL内部で必要とするデータのパラメータ(1)
	DWORD	myLparam;	// DLL内部で必要とするデータのパラメータ(2)

	DWORD	buffsize;	// バッファサイズ
	LPVOID	lpbuffer;	// バッファの先頭アドレス

	DWORD	logsize;	// ログ出力バッファサイズ
	DWORD	logtype;	// ログ出力タイプ 0:None 1:Info 2:Exclamation 3:Error
	LPVOID	logbuffer;	// ログメッセージ
} SDGDLLSTRUCT;



/*
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃                                                  ┃
┃            コールバック関数の定義                ┃
┃                                                  ┃
┃                                                  ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━┛
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃DWORD WINAPI CallBackSDG( ULONG dest, ULONG src ) ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━┛
┃CallBack関数は、SDGDLLSTRUCTを２つの領域先頭アドレスを渡されてコールされる。
┃第一パラメータ(dest)
┃第二パラメータ(src)
┃として扱い、exeからの指示はsrcに格納される。
┃dllでは、destにアンサーを格納する。
┃戻り値は専用の定義で行う。
┃
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃                                                  ┃
┃                 共通機能解説                     ┃
┃                                                  ┃
┃                                                  ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━┛
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃①RECALL                                          ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━┛
┃DLLで処理を行ったあと、その処理内容や、DLLの構成により、
┃エリア解放などのタイミングが欲しい場合がある。
┃その場合、destコマンドにSDGDLL_RECALLを付与することにより実現できる。
┃呼び出すきっかけとなったコマンドフラグと同時に立てることを推奨する。
┃本機能はOK(Online時。何度でも指定可能)と、1 Time(1度だけ可能）の場合のみ指定可能。
┃
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃②My Param                                        ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━┛
┃myWparam	DLL内部で記憶しておきたい数値（アドレス）を保存する。
┃myLparam	DLL内部で記憶しておきたい数値（アドレス）を保存する。
┃DLLはコールバックで起動されるため、呼び出しの前後で関係をもてない。
┃しかし、連続した処理を行うためには処理ごとの記憶エリアが必要となる。
┃そのため、destに本データをセットしておくことにより
┃次のイベント時にsrcに値がコピーされ起動される。
┃これを利用して、処理のシーケンスの作成が可能となる。
┃本機能を指定できるものは
┃My Param OK
┃となっているイベント、コマンドである。
┃
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃③ログ機能                                        ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━┛
┃Online中はDLL内からコメントを画面に出力することが出来る。
┃Log OK 
┃となっているコマンド、イベントが対応。
┃
┃srcの
┃logsize   : ログ出力バッファサイズ (0でないこと)
┃logbuffer	: ログ出力アドレス       (NULLでないこと)
┃上記、()内の条件が満たされた呼び出しの場合、ログ出力可能である。
┃
┃ログ出力の手順
┃1.srcのlogbufferアドレスをdestのlogbufferに値コピー
┃2.logbufferアドレスにsrcのlogsize内(NULLは考慮すること)にログ文言をセット
┃3.destのlogtypeにタイプをセット
┃ 1:情報
┃ 2:注意
┃ 3:警告
┃
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃④Online共通                                      ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━┛
┃Online共通仕様として設定可能なdestのcommandパラメータを示す。
┃
┃SDGDLL_REQSEND
┃SDGDLL_REQCLOSE	(この指定の場合、SDGDLL_RECALLは設定できない。次に発生するイベントはSDGDLL_ONCLOSEである。）
┃SDGDLL_REQSTARTTIMER
┃SDGDLL_REQSTOPTIMER
┃SDGDLL_REQEDITER（SDGDLL_RECALL指定は不要。destで指示後に、srcでSDGDLL_REQEDITERイベントが発生する。）
┃SDGDLL_REQSETEDITER
┃Online時は、これらのコマンドが発行できる。
┃各コマンドは同時設定は行えない。
┃特記のないものはSDGDLL_RECALLを定義できる。
┃詳細は、下に記述する。
┃
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃                                                  ┃
┃                 イベント処理                     ┃
┃                  EXE --> DLL                     ┃
┃                                                  ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━┛
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃                 コメント取得                     ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━┛
┃	SDGDLL_GETCOMMENT
┠─────────────────────────
┃	Scene.		Config
┃	RECALL		No
┃	My Param	No
┃	Log			No
┃	Return		SDGDLL_RESULTOK
┠─────────────────────────
┃	src:
┃		command		(SDGDLL_GETCOMMENT)
┃		wparam		0:タイトル 1:説明
┃	dest:
┃		buffsize	:	NULLを含んだ文字数
┃		lpbuffer	:	文字数先頭アドレス
┠─────────────────────────
┃	DLLの説明文を返す。
┃	ここで使用するバッファは解放ができないので
┃	DLL内部でstatic宣言しておくこと。
┃	(そのため、この文字列はDLLごとに不変となる。)
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃                 タイプ取得                       ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━┛
┃	SDGDLL_GETVER
┠─────────────────────────
┃	Scene. 		Config, Online(before)
┃	RECALL 		No
┃	My Param	No
┃	Log			No
┃	Return		SDGDLL_RESULTOK
┠─────────────────────────
┃	src:
┃		command		(SDGDLL_GETVER)
┃	dest:
┃		wparam		:	タイプ番号
┠─────────────────────────
┃	DLLのタイプを返す。
┃	現状、対応は、0x100のみである。
┃	（将来、拡張処理の追加時に対応タイプとして返す予定）
┃	DLLの選択画面で表示するほか、
┃	Online開始前にも確認のためコールされる。
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃               詳細設定可能か確認                 ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━┛
┃	SDGDLL_CONFIGRESULT
┠─────────────────────────
┃	Scene. 		Config, Online(before)
┃	RECALL 		No
┃	My Param	No
┃	Log			No
┃	Return		SDGDLL_RESULTOK
┠─────────────────────────
┃	src:
┃		command		(SDGDLL_CONFIGRESULT)
┃	dest:
┃		wparam		:	SDGDLL_CONFIGNOT:なし   SDGDLL_CONFIGUSE:有り
┠─────────────────────────
┃	この拡張処理に詳細設定データウィンドウがあるかチェックする。
┃	DLL選択画面で「詳細情報」ボタンが押せるかのチェックと
┃	Online前に設定されたデータをDLLに渡す必要があるかをチェックする。
┃	本処理を有りとした場合、詳細設定ウィンドウ要求処理を
┃	対応する必要がある。
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃                  詳細設定要求                    ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━┛
┃	SDGDLL_EDITCONFIG
┠─────────────────────────
┃	Scene. 		Config
┃	RECALL		1 Time
┃	My Param	No
┃	Log			No
┃	Return		SDGDLL_RESULTOK, SDGDLL_RESULTCANCEL
┠─────────────────────────
┃	src:
┃		command		(SDGDLL_EDITCONFIG)
┃		lpbuffer	:	既に編集された設定データがある場合のみそのデータの先頭アドレスが格納される。
┃		buffsize	:	データバッファのサイズ。設定がない場合は0が格納される。
┃	dest:
┃		command		(SDGDLL_EDITCONFIG | SDGDLL_RECALL)
┃					※内部でバッファ確保して返送した場合は、そのエリア解放のために行う必要がある。
┃					　バッファ確保しなければ0でかまわない
┃		lpbuffer	:	詳細設定で作成したデータをバイト配列として扱う。その先頭アドレス
┃		buffsize	:	詳細設定データバイト数
┠─────────────────────────
┃	DLL選択画面から「詳細情報」ボタン押下でコールされる。
┃	DLL内部で設定ウィンドウを開き、ユーザにデータ登録を提供する。
┃	設定されたデータはexeに渡すことで、通信設定情報と一緒にファイル保存が可能となる。
┃	ここで設定したデータはOnline前に再び、DLLにデータ投入されるので
┃	設定データに従った通信処理が可能となる。
┃	設定データをexeに返却するために一時的にバッファを確保する必要がある。
┃	その場合、解放処理のために1度だけSDGDLL_RECALLによる
┃	再呼び出し指定を可能とする。
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃               設定データの投入                   ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━┛
┃	SDGDLL_SETCONFIG
┠─────────────────────────
┃	Scene. 		Online(before)
┃	RECALL 		No
┃	My Param	OK (destで返されたものからが対象)
┃	Log			OK
┃	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
┠─────────────────────────
┃	src:
┃		command		(SDGDLL_SETCONFIG)
┃		lpbuffer	:	編集された設定データがある場合のみそのデータの先頭アドレスが格納される。
┃		buffsize	:	データバッファのサイズ。設定がない場合は0が格納される。
┃		logsize;	:	(Log機能による)
┃		logtype;	:	(Log機能による)
┃		logbuffer;	:	(Log機能による)
┃	dest:
┃		myWparam	:	(My Param機能による)
┃		myLparam	:	(My Param機能による)
┃		logsize;	:	(Log機能による)
┃		logtype;	:	(Log機能による)
┃		logbuffer;	:	(Log機能による)
┠─────────────────────────
┃	DLLの設定ウィンドウで定義された設定情報をDLLに引き渡す。
┃	本処理以降、Online処理が開始されるため
┃	DLL内部でデータを保存しておくこと。
┃	My Param機能はこの処理のdestから有効となる。
┃	データの解放はSDGDLL_ONCLOSEで行う。（DLL終了のイベント)
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃                  通信処理開始                    ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━┛
┃	SDGDLL_ONCONNECT
┠─────────────────────────
┃	Scene. 		Online
┃	RECALL 		OK
┃	My Param	OK
┃	Log			OK
┃	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
┠─────────────────────────
┃	src:
┃		command		(SDGDLL_ONCONNECT)
┃		myWparam	:	(My Param機能による)
┃		myLparam	:	(My Param機能による)
┃		logsize;	:	(Log機能による)
┃		logtype;	:	(Log機能による)
┃		logbuffer;	:	(Log機能による)
┃	dest:
┃		command		:	(Online共通)
┃		myWparam	:	(My Param機能による)
┃		myLparam	:	(My Param機能による)
┃		logsize;	:	(Log機能による)
┃		logtype;	:	(Log機能による)
┃		logbuffer;	:	(Log機能による)
┠─────────────────────────
┃	ソケット処理開始時にコールされる。
┃	タイマーや、送信処理などのコマンド作業は
┃	本イベントから可能となる。
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃                  データ受信                      ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━┛
┃	SDGDLL_ONRECEIVE
┠─────────────────────────
┃	Scene. 		Online
┃  RECALL 		OK
┃	My Param	OK
┃	Log			OK
┃	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
┠─────────────────────────
┃	src:
┃		command		(SDGDLL_ONRECEIVE)
┃		lpbuffer	:	受信データ先頭アドレス
┃		buffsize	:	受信したバイト数
┃		myWparam	:	(My Param機能による)
┃		myLparam	:	(My Param機能による)
┃		logsize;	:	(Log機能による)
┃		logtype;	:	(Log機能による)
┃		logbuffer;	:	(Log機能による)
┃	dest:
┃		command		:	(Online共通)
┃		myWparam	:	(My Param機能による)
┃		myLparam	:	(My Param機能による)
┃		logsize;	:	(Log機能による)
┃		logtype;	:	(Log機能による)
┃		logbuffer;	:	(Log機能による)
┠─────────────────────────
┃	ソケットでデータを受信した際にデータとともにコールされる。
┃	返信データ等あれば、destのcommandにSDGDLL_REQSENDなどを
┃	付けてその後の処理を行う。
┃	特に処理が無ければdestのcommandは0を返すのみでよい。
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃          送信データエディタデータの通知          ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━┛
┃	SDGDLL_REQEDITER
┠─────────────────────────
┃	Scene. 		Online
┃  RECALL 		OK
┃	My Param	OK
┃	Log			OK
┃	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
┠─────────────────────────
┃	src:
┃		command		(SDGDLL_REQEDITER)
┃		lpbuffer	:	送信データエディタデータ先頭アドレス
┃		buffsize	:	送信データエディタデータバイト数
┃		myWparam	:	(My Param機能による)
┃		myLparam	:	(My Param機能による)
┃		logsize;	:	(Log機能による)
┃		logtype;	:	(Log機能による)
┃		logbuffer;	:	(Log機能による)
┃	dest:
┃		command		:	(Online共通)
┃		myWparam	:	(My Param機能による)
┃		myLparam	:	(My Param機能による)
┃		logsize;	:	(Log機能による)
┃		logtype;	:	(Log機能による)
┃		logbuffer;	:	(Log機能による)
┠─────────────────────────
┃	本処理は、ネットワークイベントで起動されるものではない。
┃	dest指示でSDGDLL_REQEDITER(送信データエディタ内のデータ要求)を行った場合
┃	データ内容を通知するためにコールする。
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃                    タイマー通知                  ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━┛
┃	SDGDLL_ONTIMER
┠─────────────────────────
┃	Scene. 		Online
┃  RECALL 		OK
┃	My Param	OK
┃	Log			OK
┃	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
┠─────────────────────────
┃	src:
┃		command		(SDGDLL_ONTIMER)
┃		wparam		:	タイマーID　（0 or 1)
┃		myWparam	:	(My Param機能による)
┃		myLparam	:	(My Param機能による)
┃		logsize;	:	(Log機能による)
┃		logtype;	:	(Log機能による)
┃		logbuffer;	:	(Log機能による)
┃	dest:
┃		command		:	(Online共通)
┃		myWparam	:	(My Param機能による)
┃		myLparam	:	(My Param機能による)
┃		logsize;	:	(Log機能による)
┃		logtype;	:	(Log機能による)
┃		logbuffer;	:	(Log機能による)
┠─────────────────────────
┃	設定したタイマーが時間になった際にコールされる。
┃	送信データ等あれば、destのcommandにSDGDLL_REQSENDなどを
┃	付けてその後の処理を行ったりする。
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃                 ソケット処理終了                 ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━┛
┃	SDGDLL_ONCLOSE
┠─────────────────────────
┃	Scene. 		Online
┃  RECALL 		OK
┃	My Param	OK
┃	Log			OK
┃	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
┠─────────────────────────
┃	src:
┃		command		(SDGDLL_ONCLOSE)
┃		myWparam	:	(My Param機能による)
┃		myLparam	:	(My Param機能による)
┃		logsize;	:	(Log機能による)
┃		logtype;	:	(Log機能による)
┃		logbuffer;	:	(Log機能による)
┃	dest:
┃		command		:	設定不可
┃		myWparam	:	設定不可
┃		myLparam	:	設定不可
┃		logsize;	:	(Log機能による)
┃		logtype;	:	(Log機能による)
┃		logbuffer;	:	(Log機能による)
┠─────────────────────────
┃	ソケット処理の終了時にコールされる。
┃	処理を通して最後のコールとなるので解放する
┃	データ等があればここで必ず解放を行う。
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃                                                  ┃
┃                  Online時共通                    ┃
┃    Online時に DLL -> EXEに対して行う処理要求     ┃
┃                                                  ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━┛
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃                 データ送信要求                   ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━┛
┃	SDGDLL_REQSEND
┠─────────────────────────
┃	Scene. 		Online
┃  RECALL 		OK
┃	My Param	OK
┃	Log			OK
┃	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
┠─────────────────────────
┃	dest:
┃		command		:	SDGDLL_REQSEND | SDGDLL_RECALL(OPTION)
┃		lpbuffer	:	送信データ先頭アドレス
┃		buffsize	:	送信するバイト数
┃		wparam		:	送信データポート指定
┃						SDGDLL_SEND_ME		(対応したポートで送信)
┃						SDGDLL_SEND_PORT1	(ポート１（全て）で送信)
┃						SDGDLL_SEND_PORT2	(ポート２（全て）で送信)
┃		(その他パラメータは、各イベントのdestに準じる。)
┠─────────────────────────
┃	データの送信要求を行う。
┃	この処理の多くはDLL内部でエリア確保を行うと思うので
┃	その場合はSDGDLL_RECALLを付けて、
┃	再コールして、エリアの解放を行う必要がある。
┃	エリアを確保していなかったり、
┃	SDGDLL_ONCLOSEで解放する場合はこの限りでない。
┃	渡されたデータはすぐさまコピーされ、以後、渡された
┃	データアドレスにアクセスすることはない。
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃                通信処理終了要求                  ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━┛
┃	SDGDLL_REQCLOSE
┠─────────────────────────
┃	Scene. 		Online
┃  RECALL 		No
┃	My Param	OK
┃	Log			OK
┃	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
┠─────────────────────────
┃	dest:
┃		command		:	SDGDLL_REQCLOSE
┃		(その他パラメータは、各イベントのdestに準じる。)
┠─────────────────────────
┃	通信の終了を要求する。
┃	コマンド発行後、SDGDLL_ONCLOSEイベントが発生するので
┃	エリア解放などはそちらで行うことが望ましい。
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃                タイマー開始要求                  ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━┛
┃	SDGDLL_REQSTARTTIMER
┠─────────────────────────
┃	Scene. 		Online
┃  RECALL 		OK
┃	My Param	OK
┃	Log			OK
┃	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
┠─────────────────────────
┃	dest:
┃		command		:	SDGDLL_REQSTARTTIMER | SDGDLL_RECALL(OPTION)
┃		wparam		:	タイマーID ( SDGDLL_TIMER1 or SDGDLL_TIMER2 )
┃                      (SDGDLL_TIMER_1TIME と組み合わせると1回しかイベント発行しない。
┃                       それ以外は連続で周期発行される)
┃		lparam		:	タイマー周期( ミリsec )
┃		(その他パラメータは、各イベントのdestに準じる。)
┠─────────────────────────
┃	タイマー処理を要求する。
┃	設定可能なタイマーは２つまで。
┃  SDGDLL_TIMER_1TIMEと組み合わせると１回のみイベント発行し、
┃  タイマーは自動停止する。
┃	手動タイマー停止は、SDGDLL_REQSTOPTIMER要求で行う。
┃	通信処理終了時は自動停止される。
┃	タイマーイベントの通知はSDGDLL_ONTIMERで行われる。
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃                タイマー停止要求                  ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━┛
┃	SDGDLL_REQSTOPTIMER
┠─────────────────────────
┃	Scene. 		Online
┃  RECALL 		OK
┃	My Param	OK
┃	Log			OK
┃	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
┠─────────────────────────
┃	dest:
┃		command		:	SDGDLL_REQSTOPTIMER | SDGDLL_RECALL(OPTION)
┃		wparam		:	タイマーID ( 0 or 1 )
┃		(その他パラメータは、各イベントのdestに準じる。)
┠─────────────────────────
┃	タイマー処理を停止する。
┃	タイマーが設定されていない場合は何も処理を行わない。
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃            送信データエディタデータ要求          ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━┛
┃	SDGDLL_REQEDITER
┠─────────────────────────
┃	Scene. 		Online
┃  RECALL 		NG(設定しなくともアンサーイベントが発生する。)
┃	My Param	OK
┃	Log			OK
┃	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
┠─────────────────────────
┃	dest:
┃		command		:	SDGDLL_REQEDITER
┃		(その他パラメータは、各イベントのdestに準じる。)
┠─────────────────────────
┃	送信データエディタにセットされている情報を要求する。
┃	アンサーとしてSDGDLL_REQEDITERがイベントで発生する。
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃       送信データエディタにデータセット要求       ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━┛
┃	SDGDLL_REQSETEDITER
┠─────────────────────────
┃	Scene. 		Online
┃  RECALL 		OK
┃	My Param	OK
┃	Log			OK
┃	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
┠─────────────────────────
┃	dest:
┃		command		:	SDGDLL_REQSETEDITER | SDGDLL_RECALL(OPTION)
┃		lpbuffer	:	セットデータ先頭アドレス
┃		buffsize	:	セットするバイト数
┃		(その他パラメータは、各イベントのdestに準じる。)
┠─────────────────────────
┃	送信データエディタに指定したデータをセットする。
┃	エリア解放のためにSDGDLL_RECALLを行う。（必要ならば）
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃                                                  ┃
┃              再コールについて                    ┃
┃                                                  ┃
┃                                                  ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━┛
┃SDGDLL_RECALLをセットした場合、多くは元となった
┃イベント（コマンド）とセットで指定する。
┃それらの情報を元にDLL内部では対応処理を記述する。
┃もちろん、SDGDLL_RECALL単独でのセットも可能である。
┃その場合はMy Param機能を使ってDLL内部の処理状況を把握して行って欲しい。


*/



/*
┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃                                                  ┃
┃              作成支援マクロ                      ┃
┃                                                  ┃
┃                                                  ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/
//####################################################################
//	名称:	グローバル宣言マクロ
//	機能:
//####################################################################
#define MC_SDGHEAD( xxx1,xxx2 )			\
static char sdg_mc1[] = xxx1;			\
static char sdg_mc2[] = xxx2;
//####################################################################
//	名称:	ログの出力サブルーチンマクロ
//	機能:
//####################################################################
#define MC_SDGMODULE																			\
	void SDGLogWrite( SDGDLLSTRUCT* dest, SDGDLLSTRUCT* src, int info, const char* comment )	\
	{																							\
		if( src->logbuffer == NULL )					return;									\
		if( src->logsize <= (DWORD)lstrlen(comment) )	return;									\
		dest->logbuffer = src->logbuffer;														\
		dest->logtype = info;																	\
		lstrcpy( (char*)dest->logbuffer, comment );												\
	}
//####################################################################
//	名称:	マクロ使用時の宣言
//	機能:
//####################################################################
#define MC_MODULEUSE										\
	SDGDLLSTRUCT*	destData	= (SDGDLLSTRUCT*)dest;		\
	SDGDLLSTRUCT*	srcData		= (SDGDLLSTRUCT*)src;
//####################################################################
//	名称:	返信のための基本処理
//	機能:
//####################################################################
#define MC_EV_DEFAULT										\
	destData->command = NULL;								\
	destData->myWparam = srcData->myWparam;					\
	destData->myLparam = srcData->myLparam;
//####################################################################
//	名称:	(Event) コメント返送マクロ
//	機能:
//####################################################################
#define MC_EV_GETCOMMENT									\
	if( srcData->command & SDGDLL_GETCOMMENT ){				\
		if( srcData->wparam == 0 ){							\
			destData->buffsize = lstrlen( sdg_mc1 )+1;		\
			destData->lpbuffer = sdg_mc1;					\
		}													\
		else{												\
			destData->buffsize = lstrlen( sdg_mc2 )+1;		\
			destData->lpbuffer = sdg_mc2;					\
		}													\
		return SDGDLL_RESULTOK;								\
	}
//####################################################################
//	名称:	(Event) バージョン返送マクロ
//	機能:
//####################################################################
#define MC_EV_GETVER										\
	if( srcData->command & SDGDLL_GETVER ){					\
		destData->wparam = SDGDLL_VER;						\
		return SDGDLL_RESULTOK;								\
	}
//####################################################################
//	名称:	(Event) コンフィグ有無マクロ
//	機能:
//####################################################################
#define MC_EV_CONFIGRESULT(xxx)								\
	if( srcData->command & SDGDLL_CONFIGRESULT ){			\
		destData->wparam = xxx;								\
		return SDGDLL_RESULTOK;								\
	}
//####################################################################
//	名称:	(Event) コンフィグ設定後、エリア解放マクロ
//	機能:
//####################################################################
#define MC_EV_CONFIGFREE	{									\
	if( (srcData->command & SDGDLL_RECALL) && (srcData->command & SDGDLL_EDITCONFIG) ){	\
		if( srcData->lpbuffer != NULL ){						\
			GlobalFree( (HGLOBAL)srcData->lpbuffer );			\
		}														\
		return SDGDLL_RESULTOK;									\
	}															\
}
//####################################################################
//	名称:	コンフィグ設定時の領域確保マクロ
//	機能:	(COleSafeArray -> GlobalAlloc)
//####################################################################
#define MC_CONFIGALLOC( xxxx ){	\
	int		mcsize = xxxx.GetOneDimSize();						\
	char	*lpmcbyte;											\
	destData->buffsize = mcsize;								\
	destData->lpbuffer = (LPVOID)GlobalAlloc( GPTR, mcsize );	\
	xxxx.AccessData( (void**)&lpmcbyte );						\
	CopyMemory( destData->lpbuffer, lpmcbyte, mcsize );			\
	xxxx.UnaccessData();										\
}






