/*=============================================================================

 入力処理 [input.h]
 Author : KIM NAKAMURA

=============================================================================*/
/*-----------------------------------------------------------------------------
 インクルードガード
-----------------------------------------------------------------------------*/
#ifndef _INPUT_H_
#define _INPUT_H_

/*-----------------------------------------------------------------------------
 インクルードファイル
-----------------------------------------------------------------------------*/
#define  DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <XInput.h>

/*-----------------------------------------------------------------------------
 マクロ定義
-----------------------------------------------------------------------------*/
#define NUM_KEY_MAX        (256)	// キー最大数

//ゲームパッド
#define BUTTON_MAX         (32)		// ゲームパッド使用ボタン最大数
#define MAX_BUF_PAD        (1000)	// ゲームパッドのバッファの最大値
#define XYZ                (4)		// アナログスティック（0・1 = 左／2・3 = 右）
#define MIN_AXIS_PAD       (0)		// ゲームパッドの軸の最小値
#define MAX_AXIS_PAD       (65535)	// ゲームパッドの軸の最大値

/*-----------------------------------------------------------------------------
 インプットクラス
-----------------------------------------------------------------------------*/
class CInput
{
	public:

		CInput();
		virtual ~CInput();

		virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
		virtual void    Uninit(void);
		virtual HRESULT Update(void) = 0;		// ---> 純粋仮想関数化

	protected:

		HWND m_hWnd;							// ウィンドウハンドル

		static LPDIRECTINPUT8 m_pDInput;		// DirectInputオブジェクト
		LPDIRECTINPUTDEVICE8 m_pDIDevice;		// Deviceオブジェクト(入力に必要)

};

/*-----------------------------------------------------------------------------
 インプットクラス：キーボード
-----------------------------------------------------------------------------*/
class CInputKeyboard : public CInput
{
	private:

		BYTE m_aKeyState         [NUM_KEY_MAX];			// キーボードの状態を受け取るワーク
		BYTE m_aKeyStateTrigger  [NUM_KEY_MAX];			// トリガーワーク
		BYTE m_aKeyStateRelease  [NUM_KEY_MAX];			// リリースワーク
		BYTE m_aKeyStateRepeat   [NUM_KEY_MAX];			// リピートワーク
		int  m_aKeyStateRepeatCnt[NUM_KEY_MAX];			// リピートカウンタ

	public:

		CInputKeyboard();
		~CInputKeyboard();

		// 各処理関数
		HRESULT Init(HINSTANCE hInst, HWND hWnd);
		void    Uninit(void);
		HRESULT Update(void) override;

		// キーボードデータ取得(プレス)
		BOOL GetKeyPress(int nKey)
		{
			return (m_aKeyState[nKey] & 0x80) ? TRUE : FALSE;
		}//end

		// キーボードデータ取得(トリガー)
		BOOL GetKeyTrigger(int nKey)
		{
			return (m_aKeyStateTrigger[nKey] & 0x80) ? TRUE : FALSE;
		}//end

		// キーボードデータ取得(リリース)
		BOOL GetKeyRelease(int nKey)
		{
			return (m_aKeyStateRelease[nKey] & 0x80) ? TRUE : FALSE;
		}//end

		// キーボードデータ取得(リピート)
		BOOL GetKeyRepeat(int nKey)
		{
			return (m_aKeyStateRepeat[nKey] & 0x80) ? TRUE : FALSE;
		}//end

		// キーボードデータ削除(トリガー)
		void FlushKeyTrigger(int nKey)
		{
			m_aKeyStateTrigger[nKey] = 0;
		}//end

};

/*-----------------------------------------------------------------------------
 インプットクラス：マウス
-----------------------------------------------------------------------------*/
class CInputMouse : public CInput
{
	private:

		DIMOUSESTATE2 m_mouseState;
		DIMOUSESTATE2 m_mouseStateTrigger;
		POINT         m_MousePosScreen;			// スクリーンでのポジション
		POINT         m_MousePosClient;			// クライアント領域でのポジション
		D3DXVECTOR3   m_MousePosWrold;			// ワールド座標変換時のポジション

	public:

		CInputMouse() {}
		~CInputMouse() {}

		// 各処理関数
		HRESULT Init(HINSTANCE hInst, HWND hWnd);
		void    Uninit(void);
		HRESULT Update(void) override;

		// 左ボタン：プレス
		BOOL GetLeftPress(void)
		{
			return (m_mouseState.rgbButtons[0] & 0x80) ? TRUE : FALSE;
		}//end

		// 左ボタン：トリガー
		BOOL GetLeftTrigger(void)
		{
			return (m_mouseStateTrigger.rgbButtons[0] & 0x80) ? TRUE : FALSE;
		}//end

		// 右ボタン：プレス
		BOOL GetRightPress(void)
		{
			return (m_mouseState.rgbButtons[1] & 0x80) ? TRUE : FALSE;
		}//end

		// 右ボタン：トリガー
		BOOL GetRightTrigger(void)
		{
			return (m_mouseStateTrigger.rgbButtons[1] & 0x80) ? TRUE : FALSE;
		}//end

		// 中央ボタン：プレス
		BOOL GetCenterPress(void)
		{
			return (m_mouseState.rgbButtons[2] & 0x80) ? TRUE : FALSE;
		}//end

		// 中央ボタン：トリガー
		BOOL GetCenterTrigger(void)
		{
			return (m_mouseStateTrigger.rgbButtons[2] & 0x80) ? TRUE : FALSE;
		}//end

		// 前フレームの座標位置を取得
		LONG GetAxisX(void) { return m_mouseState.lX; }
		LONG GetAxisY(void) { return m_mouseState.lY; }
		LONG GetAxisZ(void) { return m_mouseState.lZ; }

		// 座標位置取得
		const POINT& GetPosScreen(void) { return m_MousePosScreen; }
		const POINT& GetPosClient(void) { return m_MousePosClient; }
		D3DXVECTOR3 GetPosWorld(void);

};

/*-----------------------------------------------------------------------------
 インプットクラス：ゲームパッド
-----------------------------------------------------------------------------*/
class CInputGamePad : public CInput
{
	private:

		static LPDIRECTINPUTDEVICE8 m_pDevGamePad;	//ゲームパッドデバイス
		static DIDEVCAPS m_DevCaps;					//ゲームパッドの状態情報

		BYTE m_aPadButton         [BUTTON_MAX];		//ゲームパッドの入力情報ワーク
		BYTE m_aPadButtonTrigger  [BUTTON_MAX];		//ゲームパッドのトリガー情報ワーク
		BYTE m_aPadButtonRelease  [BUTTON_MAX];		//ゲームパッドのリリース情報ワーク
		BYTE m_aPadButtonRepeat   [BUTTON_MAX];		//ゲームパッドのリピート情報ワーク
		BYTE m_aPadButtonRepeatCnt[BUTTON_MAX];		//ゲームパッドのリピートカウンタ

		int m_aPadAnalogStick[XYZ];					// アナログスティックの情報ワーク
		int m_nPadPOV;								// ゲームパッド十字キーの情報ワーク
		int m_nPadPOVTrigger;						// ゲームパッド十字キーのトリガー情報ワーク
		int m_nPadPOVRepeat;						// ゲームパッド十字キーのリピート情報ワーク

		//列挙されたデバイスごとに呼び出されるコールバック関数
		static BOOL CALLBACK EnumPadCallback(const DIDEVICEINSTANCE* pdidInstance, LPVOID pContext);
		static BOOL CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);

	public:

		CInputGamePad()
		{
			m_pDevGamePad = NULL;
			m_nPadPOV     = POV_NOTUSE;
		}//end

		~CInputGamePad() {}

		// ゲームパッド列挙型
		typedef enum
		{
#if 0
			GB_Y = 0,			// Ｙボタン
			GB_B,				// Ｂボタン
			GB_A,				// Ａボタン
			GB_X,				// Ｘボタン
			GB_L1,				// Ｌ１ボタン
			GB_R1,				// Ｒ１ボタン
			GB_L2,				// Ｌ２ボタン
			GB_R2,				// Ｒ２ボタン
			GB_BACK,			// バックボタン
			GB_STRAT,			// スタートボタン
			GB_L3,				// Ｌ３ボタン
			GB_R3,				// Ｒ３ボタン
#else
			GB_A = 0,			// Ａボタン
			GB_B,				// Ｂボタン
			GB_X,				// Ｘボタン
			GB_Y,				// Ｙボタン
			GB_L1,				// Ｌ１ボタン
			GB_R1,				// Ｒ１ボタン
			GB_BACK,			// バックボタン
			GB_STRAT,			// スタートボタン
			GB_L3,				// Ｌ３ボタン
			GB_R3,				// Ｒ３ボタン
#endif
			GBA_MAX,			// これ以上のボタンはありません

			GS_X = 0,			// Ｘ軸方向アナログスティック(左
			GS_Y,				// Ｙ軸方向アナログスティック(左
			GS_ZX,				// Ｚ軸横方向アナログスティック(右
			GS_ZY,				// Ｚ軸縦方向アナログスティック(右

			GSL,				// 左スティックを使用する
			GSR,				// 右スティックを使用する

			POV_NOTUSE = -1,	// 十字キーの未使用
			POV_UP = 0,			// 十字キーの上ボタン
			POV_UPRIGHT,		// 十字キーの右上ボタン
			POV_RIGHT,			// 十字キーの右ボタン
			POV_DOWNRIGHT,		// 十字キーの右下ボタン
			POV_DOWN,			// 十字キーの下ボタン
			POV_DOWNLEFT,		// 十字キーの左下ボタン
			POV_LEFT,			// 十字キーの左ボタン
			POV_UPLEFT,			// 十字キーの左ボタン

		}GAMEPAD;

		// 各処理関数
		HRESULT Init(HINSTANCE hInstance, HWND hWnd);
		void Uninit(void);
		HRESULT Update(void) override;

		/* 採用している取得状態
			プレス　：押している間、真となる
			トリガー：押したときに真となる
			リピート：押している間、一定のリズムで真となる
			リリース：離したときに真となる
		*/

		// ゲームパッド：ボタン
		BOOL GetPadButton       (int nPad) { return (m_aPadButton       [nPad] & 0x80) ? true : false; }
		BOOL GetPadButtonTrigger(int nPad) { return (m_aPadButtonTrigger[nPad] & 0x80) ? true : false; }
		BOOL GetPadButtonRepeat (int nPad) { return (m_aPadButtonRepeat [nPad] & 0x80) ? true : false; }
		BOOL GetPadButtonRelease(int nPad) { return (m_aPadButtonRelease[nPad] & 0x80) ? true : false; }

		// ゲームパッド：ＰＯＶ（十字キー）
		int GetPadPOVPress(void);
		int GetPadPOVTrigger(void);
		int GetPadPOVRepeat(void);

		// アナログスティックの状態の取得
		D3DXVECTOR3 GetPadAnalogStick(int nPadType);

		// ゲームパッド接続状況の取得
		LPDIRECTINPUTDEVICE8 GetGamePad(void) { return m_pDevGamePad; }

};

/*-----------------------------------------------------------------------------
 インクルードエンド
-----------------------------------------------------------------------------*/
#endif

