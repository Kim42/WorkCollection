/*=============================================================================

 管理処理ヘッダ[ manager.h ]

=============================================================================*/
/*-----------------------------------------------------------------------------
 インクルードガード
-----------------------------------------------------------------------------*/
#ifndef _MANAGER_H_
#define _MANAGER_H_

/*-----------------------------------------------------------------------------
 インクルードファイル
-----------------------------------------------------------------------------*/
#include <Windows.h>
#include <d3dx9.h>

// 入力処理用のヘッダ
#include "input.h"

// Music
#include <XAudio2.h>

// 数学
#define _USE_MATH_DEFINES
#include <math.h>

// 直接ライブラリにリンクできるプラグマコメント（VSのみの裏技）
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

/*-----------------------------------------------------------------------------
 マクロ定義
-----------------------------------------------------------------------------*/
// 参照カウンタのデクリメント
#define SAFE_RELEASE(p) { if(p) { (p) -> Release(); (p) = NULL; } }

// メモリの解放
#define SAFE_DELETE(p)     { if(p != NULL) { delete (p); (p) = NULL; } }
#define SAFE_DELETE_Ex(p)  { if(p != NULL) { (p) -> Uninit(); delete (p); (p) = NULL; } }
#define SAFE_DELETE_MUL(p) { if(p != NULL) { delete[] (p); (p) = NULL; } }

// ウィンドウサイズ
#define SCREEN_WIDTH  (1000)	// 幅
#define SCREEN_HEIGHT (600)		// 高さ

/*-----------------------------------------------------------------------------
 前方宣言
-----------------------------------------------------------------------------*/
class CInputKeyboard;
class CInputGamePad;
class CMode;
class CSound;
class CFade;

/*-----------------------------------------------------------------------------
 クラス定義
-----------------------------------------------------------------------------*/
class CManager
{
	private:

		// インプット：キーボード
		static CInputKeyboard *m_pInputKeyboard;

		// インプット：ゲームパッド
		static CInputGamePad *m_pInputGamePad;

		// モード
		static CMode *m_pMode;

		// サウンド
		static CSound *m_Sound;

		// フェード
		static CFade *m_pFade;

	public:

		// コンストラクタ & デスクトラクタ
		CManager() {}
		virtual ~CManager() {}

		// 各処理関数
		static HRESULT Init  (HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
		static void    Uninit(void);
		static void    Update(void);
		static void    Draw  (void);

		// インプット：キーボード
		static CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }

		// インプット：ゲームパッド
		static CInputGamePad *GetInputGamePad(void) { return m_pInputGamePad; }

		// モード
		static void SetMode( CMode *pMode );
		static void SetMode( CMode *pMode , int StageID);

		static CSound* GetSound(void){ return m_Sound; }

		// フェード
		static CFade *GetFade(void) { return m_pFade; };

		// ステージ番号確保
		static int m_nNowStage;

};

/*-----------------------------------------------------------------------------
 インクルードエンド
-----------------------------------------------------------------------------*/
#endif