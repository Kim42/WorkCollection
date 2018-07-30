/*=============================================================================

 メイン処理[ main.cpp ]

=============================================================================*/
/*=============================================================================
 インクルードヘッダ
=============================================================================*/
#include "manager.h"

/*=============================================================================
 マクロ定義
=============================================================================*/
#define CLASS_NAME  "SWEET WALL"
#define WINDOW_NAME "SWEET WALL"

/*=============================================================================
 プロトタイプ宣言
=============================================================================*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*-----------------------------------------------------------------------------
 メイン関数
-----------------------------------------------------------------------------*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 警告遮断
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 拡張宣告構造体
	WNDCLASSEX wcex;

	wcex.cbSize        = sizeof(WNDCLASSEX);				// WNDCLASSEXのメモリサイズの指定
	wcex.style         = CS_CLASSDC;						// 表示するウィンドウのスタイルの設定
	wcex.lpfnWndProc   = WndProc;							// ウィンドウプロシージャのアドレス(関数名)を取得
	wcex.cbClsExtra    = 0;									// 通常は使用しないので"0"を指定
	wcex.cbWndExtra    = 0;									// 通常は使用しないので"0"を指定
	wcex.hInstance     = hInstance;							// WinMainのパラメータのインスタンスハンドル
	wcex.hIcon         = NULL;								// 使用するアイコンを指定(Windowsが持っているアイコン)
	wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);		// マウスカーソウルの指定
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);		// ウィンドウのクライアント領域の背景色を設定
	wcex.lpszMenuName  = NULL;								// windowにつけるメニューを設定
	wcex.lpszClassName = CLASS_NAME;						// ウィンドウクラスの名前
	wcex.hIconSm       = NULL;								// 小さいアイコンが設定された場合の情報を記述

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ハンドル定義
	HWND hWnd;
	MSG msg;

	// ウィンドウスタイルの設定
	DWORD WindowStyle = WS_OVERLAPPEDWINDOW &~ (WS_MAXIMIZEBOX | WS_THICKFRAME);

	// ウィンドウ枠・スクリーンサイズの指定変更
	RECT cr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	AdjustWindowRect(&cr, WindowStyle, FALSE);

	int ww = cr.right - cr.left;
	int wh = cr.bottom - cr.top;

	// デスクトップの中心にウィンドウの表示
	RECT dr;
	GetWindowRect(GetDesktopWindow(), &dr);

	int dw = dr.right - dr.left;
	int dh = dr.bottom - dr.top;
	int wx = ww > dw ? 0 : (dw - ww) / 2;
	int wy = wh > dh ? 0 : (dh - wh) / 2;

	// ウィンドウの形状作成
	hWnd = CreateWindowEx(0,		// 拡張ウィンドウスタイル
		CLASS_NAME,					// ウィンドウクラスの名前
		WINDOW_NAME,				// ウィンドウの名前
		WindowStyle,				// ウィンドウスタイル 
		wx,							// ウィンドウの表示場所Ｘ
		wy,							// ウィンドウの表示場所Ｙ
		ww,							// ウィンドウのフレーム＋スクリーンの幅
		wh,							// ウィンドウのフレーム＋スクリーンの高さ
		NULL,						// 親ウィンドウのハンドル
		NULL,						// メニューハンドルまたは子ウィンドウＩＤ
		hInstance,					// インスタンスハンドル
		NULL);						// ウィンドウ作成データ

	ShowWindow(hWnd, nCmdShow);		// 指定されたウィンドウの表示：ウィンメイン
	UpdateWindow(hWnd);				// ウィンドウの状態を直ちに反映：ウィンメイン

	// 初期化処理
	if(FAILED(CManager :: Init(hInstance, hWnd, true)))
	{
		// メッセージの表示
		MessageBox(NULL, "ゲームパッドが未接続か\n純粋なエラーのため初期化に失敗しました\nウィンドウを閉じます", "エラー", NULL);
		return E_FAIL;
	}
	else
	{
		// メッセージループ
		for(;;)
		{
			if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
			{
				// Windowsの処理
				if(msg.message == WM_QUIT)
				{
					break;
				}
				else
				{
					// 呼び出し側のスレッドのメッセージの翻訳と送信
					TranslateMessage(&msg);

					// ウィンドウプロシ―ジャへメッセージの送信
					DispatchMessage(&msg);
				}//if.fin
			}
			else
			{
				// 更新処理
				CManager :: Update();

				// 描画処理
				CManager :: Draw();

			}//if.fin

		}//for.fin

	}//if.fin

	// 終了処理
	CManager :: Uninit();

	// ウィンドウクラスの解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 値を返す
	return (int)msg.wParam;
}

/*-----------------------------------------------------------------------------
 ウィンドウプロシージャ
  (CALLBACK : Win32API関数を呼び出しの規約)
  hWnd   : ウィンドウのハンドル
  uMsg   : メッセージの識別子
  wParam : メッセージの最初のパラメータ
  lParam : メッセージの２番目のパラメータ
-----------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// 変数宣言
	UINT nID;

	// 二度手間の仕組み
	switch(uMsg)
	{
		case WM_DESTROY:

			PostQuitMessage(0);
			break;

		case WM_KEYDOWN:

			switch(wParam)		// wParamに入力したキーのアドレスが入いる
			{
				case VK_ESCAPE:

					nID = MessageBox(NULL, "終了しますか？", "終了メッセージ", MB_YESNO | MB_DEFBUTTON1);

					// 終了処理
					if(nID == IDYES) DestroyWindow(hWnd);
					break;

			}//switch
			break;

		default:

			break;

	}//switch.fin

	// 既定の返り値
	return DefWindowProc(hWnd, uMsg, wParam, lParam);

}
