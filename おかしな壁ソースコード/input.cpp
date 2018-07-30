/*-----------------------------------------------------------------------------

 入力処理 [input.cpp]
 Author : KIM NAKAMURA

-----------------------------------------------------------------------------*/
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "camera.h"

/*-----------------------------------------------------------------------------
 マクロ定義
-----------------------------------------------------------------------------*/
#define COUNT_WAIT_REPEAT   (20)	// リピート待ち時間
#define LIMIT_COUNT_REPEAT  (24)	// リピートカウントリミッター(20もよい)

// 列挙状態（続ける／やめる）
#define DIDENUM_CONTINUE   (0)
#define DIDENU_STOP        (1)

/*-----------------------------------------------------------------------------
 静的変数メンバの動的確保
-----------------------------------------------------------------------------*/
LPDIRECTINPUT8 CInput::m_pDInput = NULL;	// DirectInputオブジェクト
LPDIRECTINPUTDEVICE8 CInputGamePad::m_pDevGamePad = NULL;
DIDEVCAPS CInputGamePad::m_DevCaps;

/*-----------------------------------------------------------------------------
 CInputコンストラスタ
-----------------------------------------------------------------------------*/
CInput::CInput()
{
	m_pDIDevice = NULL;
}

/*-----------------------------------------------------------------------------
 CInputデストラスタ
 -----------------------------------------------------------------------------*/
CInput::~CInput()
{
}

/*-----------------------------------------------------------------------------
 入力処理の初期化処理
 -----------------------------------------------------------------------------*/
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInputオブジェクトの作成、DirectInputインターフェースの作成
	// キーボード、パッド、マウス共通なので一つでOK、ここの継ぎ足しで動く
	if (m_pDInput == NULL)
	{
		if (FAILED(DirectInput8Create(
		hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDInput, NULL)))
		{
			MessageBox(hWnd, "DirectXInputオブジェクトが作成できませんでした。",
				"Direct Input Error", MB_OK | MB_DEFBUTTON1);
			return E_FAIL;
		}//if.fin

	}//if.fin

	// ウィンドウハンドルの取得
	m_hWnd = hWnd;

	// 返還
	return S_OK;
}

/*-----------------------------------------------------------------------------
 入力処理の終了処理
-----------------------------------------------------------------------------*/
void CInput::Uninit(void)
{
	// デバイスオブジェクトの解放
	if(m_pDIDevice)
	{
		m_pDIDevice->Unacquire();

		m_pDIDevice->Release();
		m_pDIDevice = NULL;
	}//if.fin

	// DirectInputオブジェクトの解放
	if(m_pDInput)
	{
		m_pDInput->Release();
		m_pDInput = NULL;
	}//if.fin

}

/*-----------------------------------------------------------------------------
 CInputKeyboardコンストラスタ
-----------------------------------------------------------------------------*/
CInputKeyboard::CInputKeyboard()
{
	// 各ワークのクリア
	ZeroMemory(m_aKeyState, sizeof m_aKeyState);
	ZeroMemory(m_aKeyStateTrigger, sizeof m_aKeyStateTrigger);
	ZeroMemory(m_aKeyStateRelease, sizeof m_aKeyStateRelease);
	ZeroMemory(m_aKeyStateRepeat, sizeof m_aKeyStateRepeat);
	ZeroMemory(m_aKeyStateRepeatCnt, sizeof m_aKeyStateRepeatCnt);

}

/*-----------------------------------------------------------------------------
 CInputKeyboardデストラスタ
 -----------------------------------------------------------------------------*/
CInputKeyboard::~CInputKeyboard()
{
}

/*-----------------------------------------------------------------------------
 キーボードの初期化処理
 -----------------------------------------------------------------------------*/
HRESULT CInputKeyboard::Init(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// 入力処理の初期化
	CInput::Init(hInst, hWnd);

	// デバイスオブジェクトを作成
	hr = m_pDInput->CreateDevice(GUID_SysKeyboard, &m_pDIDevice, NULL);
	if(FAILED(hr) || m_pDIDevice == NULL)
	{
		MessageBox(hWnd, "キーボードがねぇ！", "警告！", MB_ICONWARNING);
		return hr;
	}//if.fin

	// データフォーマットを設定
	hr = m_pDIDevice->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}//if.fin

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = m_pDIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}//if.fin

	// m_pDIDeviceアクセス権を獲得(入力制御開始)
	m_pDIDevice->Acquire();

	// 返還
	return hr;

}

/*-----------------------------------------------------------------------------
 キーボード入力処理の開放
 -----------------------------------------------------------------------------*/
void CInputKeyboard::Uninit(void)
{
	// 入力処理の開放
	CInput::Uninit();

}

/*-----------------------------------------------------------------------------
 キーボードの更新処理
-----------------------------------------------------------------------------*/
HRESULT CInputKeyboard::Update(void)
{
	HRESULT hr;
	BYTE aKeyState[NUM_KEY_MAX];

	if(!m_pDIDevice)
	{
		return E_FAIL;
	}//if.fin

	// デバイスからデータを取得
	hr = m_pDIDevice->GetDeviceState(sizeof(aKeyState), aKeyState);
	if(SUCCEEDED(hr))
	{
		for(int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];
			m_aKeyStateRepeat[nCntKey] = m_aKeyStateTrigger[nCntKey];

			if(aKeyState[nCntKey])
			{
				m_aKeyStateRepeatCnt[nCntKey]++;
				if(m_aKeyStateRepeatCnt[nCntKey] >= COUNT_WAIT_REPEAT)
				{
					m_aKeyStateRepeat[nCntKey] = aKeyState[nCntKey];
				}//if.fin
			}
			else
			{
				m_aKeyStateRepeatCnt[nCntKey] = 0;
				m_aKeyStateRepeat[nCntKey] = 0;
			}//if.fin

			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}//for.fin
	}
	else
	{
		m_pDIDevice->Acquire();
	}//if.fin

	// 返還
	return hr;

}

/*-----------------------------------------------------------------------------
 マウスの初期化処理
-----------------------------------------------------------------------------*/
HRESULT CInputMouse::Init(HINSTANCE hInst, HWND hWnd)
{
	// 変数宣言
	HRESULT hr;

	// 入力処理の初期化
	CInput::Init(hInst, hWnd);

	// デバイスオブジェクトを作成
	hr = m_pDInput->CreateDevice(GUID_SysMouse, &m_pDIDevice, NULL);

	if (FAILED(hr) || m_pDIDevice == NULL)
	{
		MessageBox(hWnd, "マウスがねぇ！", "警告！", MB_ICONWARNING);
		return hr;
	}//if.fin

	 // データフォーマットを設定
	hr = m_pDIDevice->SetDataFormat(&c_dfDIMouse2);

	if (FAILED(hr))
	{
		MessageBox(hWnd, "マウスのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}//if.fin

	 // 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = m_pDIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	if (FAILED(hr))
	{
		MessageBox(hWnd, "マウスの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}//if.fin

	 // デバイスの設定
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(dipdw);
	dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = DIPROPAXISMODE_REL;

	hr = m_pDIDevice->SetProperty(DIPROP_AXISMODE, &dipdw.diph);

	// マウスのm_pDIDeviceアクセス権を獲得(入力制御開始)
	m_pDIDevice->Acquire();

	// 返還
	return hr;

}

/*-----------------------------------------------------------------------------
 マウス入力処理の開放
-----------------------------------------------------------------------------*/
void CInputMouse::Uninit(void)
{
	// 入力処理の開放
	CInput::Uninit();
}

/*-----------------------------------------------------------------------------
 マウスの更新処理
-----------------------------------------------------------------------------*/
HRESULT CInputMouse::Update(void)
{
	// 変数宣言
	HRESULT hr;

	// 構造体使用宣言
	DIMOUSESTATE2 mouseState;

	// NULLCHECK
	if (!m_pDIDevice) return S_FALSE;

	// デバイスからデータの取得
	hr = m_pDIDevice->GetDeviceState(sizeof(mouseState), &mouseState);

	if (SUCCEEDED(hr))
	{
		// X
		m_mouseStateTrigger.lX = ((m_mouseState.lX ^ mouseState.lX) & mouseState.lX);

		// Y
		m_mouseStateTrigger.lY = ((m_mouseState.lY ^ mouseState.lY) & mouseState.lY);

		// Z
		m_mouseStateTrigger.lZ = ((m_mouseState.lZ ^ mouseState.lZ) & mouseState.lZ);

		// キー８つ分のループ
		for (int nCntKey = 0; nCntKey < 8; nCntKey++)
		{
			m_mouseStateTrigger.rgbButtons[nCntKey]
				= ((m_mouseState.rgbButtons[nCntKey] ^ mouseState.rgbButtons[nCntKey]) & mouseState.rgbButtons[nCntKey]);
		}//for.fin

		// ステートの確保
		m_mouseState = mouseState;

		// クライアント座標の取得
		ScreenToClient(m_hWnd, &m_MousePosScreen);

		// 用途別のために移し替える
		m_MousePosClient = m_MousePosScreen;

		// スクリーン座標を取得
		GetCursorPos(&m_MousePosScreen);
	}
	else
	{
		// マウスのm_pDIDeviceアクセス権を獲得(入力制御開始)
		m_pDIDevice->Acquire();
	}//if.fin

	// 返還
	return hr;

}

/*-----------------------------------------------------------------------------
 マウス：ワールド座標変換処理
-----------------------------------------------------------------------------*/
D3DXVECTOR3 CInputMouse::GetPosWorld(void)
{
	// 各行列の逆行列を算出
	D3DXMATRIX InvView, InvPrj, InvPort, ViewPort;

	// ビューマトリクスの逆行列返還
	D3DXMatrixInverse(&InvView, NULL, CCamera::GetViewMtx());

	// プロジェクションマトリクスの逆行列返還
	D3DXMatrixInverse(&InvPrj, NULL, CCamera::GetProjectionMtx());

	// ビューポートマトリクスの正規化
	D3DXMatrixIdentity(&ViewPort);

	ViewPort._11 = SCREEN_WIDTH / 2.0f; ViewPort._22 = -SCREEN_HEIGHT / 2.0f;
	ViewPort._41 = SCREEN_WIDTH / 2.0f; ViewPort._42 =  SCREEN_HEIGHT / 2.0f;

	// ビューポートマトリクスの逆行列返還
	D3DXMatrixInverse(&InvPort, NULL, &ViewPort);

	// 逆変換
	D3DXMATRIX tmp = InvPort * InvPrj * InvView;
	D3DXVec3TransformCoord
	(&m_MousePosWrold, &D3DXVECTOR3((float)m_MousePosClient.x, (float)m_MousePosClient.y, 1.0f), &tmp);

	// 結果の返還
	return m_MousePosWrold;

}

/*-----------------------------------------------------------------------------
 ゲームパッドの初期化処理
-----------------------------------------------------------------------------*/
HRESULT CInputGamePad::Init(HINSTANCE hInst, HWND hWnd)
{
	// 入力処理の初期化
	CInput::Init(hInst, hWnd);

	// ゲームパッドデバイスの作成
	if (FAILED(m_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL,		// 列挙するデバイスの種類
		EnumPadCallback,										// 列挙コールバック関数のアドレス
		NULL,													// 列挙コールバック関数が呼ばれる度実行
		DIEDFL_ATTACHEDONLY)))									// 列挙の葉にを指定するフラグ値
	{
		MessageBox(hWnd, "ゲームパッドが列挙に失敗しました。", "Direct Input Error", MB_ICONWARNING);
		return E_FAIL;
	}//if.fin

	// ゲームパッド接続確認
	if (!m_pDevGamePad) return S_OK;

	// ゲームパッドのデータフォーマット
	if (FAILED(m_pDevGamePad->SetDataFormat(&c_dfDIJoystick2)))
	{
		MessageBox(hWnd, "ゲームパッドのデータフォーマットを設定できませんでした。", "Direct Input Error", MB_ICONWARNING);
		return E_FAIL;
	}//if.fin

	 // 大事!フォアグラウンドorバックグラウンド,非排他or排他、詳しくは教科書へ
	 // 協調モードを設定（フォアグラウンド＆非排他モード）

	 //ゲームパッド
	if (FAILED(m_pDevGamePad->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		MessageBox(hWnd, "ゲームパッドの協調モードを設定できませんでした。", "Direct Input Error", MB_ICONWARNING);
		return E_FAIL;
	}//if.fin

	//軸の範囲設定
	if (FAILED(m_pDevGamePad->EnumObjects(EnumAxesCallback, NULL, DIDFT_AXIS)))
	{
		MessageBox(hWnd, "ゲームパッドの軸モードが設定せきませんでした。", "Direct Input Error", MB_ICONWARNING);
	}//if.fin

	// 正常終了
	return S_OK;

}

/*-----------------------------------------------------------------------------
 ゲームパッドの入力処理の開放
-----------------------------------------------------------------------------*/
void CInputGamePad::Uninit(void)
{
	// 入力デバイスインターフェースの解放
	SAFE_RELEASE(m_pDevGamePad);

	// 入力処理の開放
	CInput::Uninit();
}

/*-----------------------------------------------------------------------------
 ゲームパッドの更新処理
-----------------------------------------------------------------------------*/
HRESULT CInputGamePad::Update(void)
{
	// ゲームパッドの接続がない場合
	if (!m_pDevGamePad) return E_FAIL;

	// 変数宣言
	HRESULT hr;
	DIJOYSTATE2 dijs;

	// メモリを解放
	ZeroMemory(&dijs, sizeof(dijs));

	// データのポーリング // 起動準備完了
	hr = m_pDevGamePad->Poll();

	// 失敗なら再び動作開始を行う
	if (FAILED(hr))
	{
		hr = m_pDevGamePad->Acquire();

		while (hr == DIERR_INPUTLOST)
		{
			hr = m_pDevGamePad->Acquire();
		}//while.fin

	}//if.fin

	// ゲームパッド入力によるデータを直接取得
	if (SUCCEEDED(m_pDevGamePad->GetDeviceState(sizeof(dijs), &dijs)))
	{
		// アナログスティックデータ代入
		m_aPadAnalogStick[0] = dijs.lX;				// 左スティック：Ｘ軸担当
		m_aPadAnalogStick[1] = dijs.lY;				// 左スティック：Ｙ軸担当
		m_aPadAnalogStick[2] = dijs.lZ;				// 右スティック：Ｚ軸横担当
		m_aPadAnalogStick[3] = dijs.lRz;			// 右スティック：Ｚ軸縦担当

		// ＰＯＶ(十字キー)データ代入
		m_nPadPOV = dijs.rgdwPOV[0];

		// ボタンデータ取得に成功
		for (int nCnPad = 0; nCnPad < BUTTON_MAX; nCnPad++)
		{
			// ゲームパッド・ボタン：キートリガー・リリース情報の取得

			//トリガー
			m_aPadButtonTrigger[nCnPad] = 
				(m_aPadButton[nCnPad] ^ dijs.rgbButtons[nCnPad]) & dijs.rgbButtons[nCnPad];

			//リリース
			m_aPadButtonRelease[nCnPad] = 
				(m_aPadButton[nCnPad] ^ dijs.rgbButtons[nCnPad]) & m_aPadButton[nCnPad];

			// キーリピート
			if (dijs.rgbButtons[nCnPad] & 0x80)
			{
				if (m_aPadButtonRepeatCnt[nCnPad] < LIMIT_COUNT_REPEAT)
				{
					m_aPadButtonRepeatCnt[nCnPad]++;

					if (m_aPadButtonRepeatCnt[nCnPad] == 1 || m_aPadButtonRepeatCnt[nCnPad] >= LIMIT_COUNT_REPEAT)
					{
						m_aPadButtonRepeat[nCnPad] = m_aPadButton[nCnPad] | dijs.rgbButtons[nCnPad];
					}
					else//押されているけど待機中
					{
						m_aPadButtonRepeat[nCnPad] = 0;
					}//if.fin

				}//if.fin
			}
			else
			{
				m_aPadButtonRepeat[nCnPad] = 0;
				m_aPadButtonRepeatCnt[nCnPad] = 0;
			}//if.fin

			// キープレス情報を保存
			m_aPadButton[nCnPad] = dijs.rgbButtons[nCnPad];
		}//for.fin
	}
	else
	{
		// 失敗なら再び動作開始を行う
		m_pDevGamePad->Acquire();
	}//if.fin

	// 結果返還
	return hr;

}

/*-----------------------------------------------------------------------------
 ジョイスティックのアナログスティックの状態の取得
-----------------------------------------------------------------------------*/
D3DXVECTOR3 CInputGamePad::GetPadAnalogStick(int nPadType)
{
	// 変数宣言
	D3DXVECTOR3 StickStatus;

	// それぞれの軸の値を代入
	switch (nPadType)
	{
		// ＸＹ軸方向アナログスティック(左
		case GSL:
			StickStatus = D3DXVECTOR3((float)m_aPadAnalogStick[GS_X],
									  (float)m_aPadAnalogStick[GS_Y],
									  (float)m_aPadAnalogStick[GS_Y]);
			break;

		// 軸方向縦横アナログスティック(右
		case GSR:
			StickStatus = D3DXVECTOR3((float)m_aPadAnalogStick[GS_ZX],
									  (float)m_aPadAnalogStick[GS_ZY], 
									  (float)m_aPadAnalogStick[GS_ZY]);
			break;

		// ＹとＺは共通

	}//switch.fin

	// 値を返す
	return StickStatus;

}

/*-----------------------------------------------------------------------------
 ジョイスティックの十字キーのプレス状態の取得
-----------------------------------------------------------------------------*/
int CInputGamePad::GetPadPOVPress(void)
{
	// 十字キーデータ格納変数宣言
	int StickStatus = POV_NOTUSE;

	// 入力によって取得出来る値の割り振り
	if (m_nPadPOV == 0)     StickStatus = POV_UP;			// 十字キーの上ボタン
	if (m_nPadPOV == 4500)  StickStatus = POV_UPRIGHT;		// 十字キーの右上ボタン
	if (m_nPadPOV == 9000)  StickStatus = POV_RIGHT;		// 十字キーの右ボタン
	if (m_nPadPOV == 13500) StickStatus = POV_DOWNRIGHT;	// 十字キーの右下ボタン
	if (m_nPadPOV == 18000) StickStatus = POV_DOWN;			// 十字キーの下ボタン
	if (m_nPadPOV == 22500) StickStatus = POV_DOWNLEFT;		// 十字キーの左下ボタン
	if (m_nPadPOV == 27000) StickStatus = POV_LEFT;			// 十字キーの左ボタン
	if (m_nPadPOV == 31500) StickStatus = POV_UPLEFT;		// 十字キーの左ボタン

	// 値を返す
	return StickStatus;

}

/*-----------------------------------------------------------------------------
 ジョイスティックの十字キーのトリガー状態の取得
-----------------------------------------------------------------------------*/
int CInputGamePad::GetPadPOVTrigger(void)
{
	// 変数宣言
	int StickStatus = POV_NOTUSE;		// 十字キーデータ格納
	static bool bUse = false;			// POV入力の有無判断

	// ＰＯＶの入力がない場合
	if (bUse == false)
	{
		// 入力によって取得出来る値の割り振り
		if (m_nPadPOV == 0)     StickStatus = POV_UP;			// 十字キーの上ボタン
		if (m_nPadPOV == 4500)  StickStatus = POV_UPRIGHT;		// 十字キーの右上ボタン
		if (m_nPadPOV == 9000)  StickStatus = POV_RIGHT;		// 十字キーの右ボタン
		if (m_nPadPOV == 13500) StickStatus = POV_DOWNRIGHT;	// 十字キーの右下ボタン
		if (m_nPadPOV == 18000) StickStatus = POV_DOWN;			// 十字キーの下ボタン
		if (m_nPadPOV == 22500) StickStatus = POV_DOWNLEFT;		// 十字キーの左下ボタン
		if (m_nPadPOV == 27000) StickStatus = POV_LEFT;			// 十字キーの左ボタン
		if (m_nPadPOV == 31500) StickStatus = POV_UPLEFT;		// 十字キーの左ボタン
	}//if.fin

	 // 十字キーの入力があった場合
	if (m_nPadPOV != POV_NOTUSE) bUse = true;	// 入力あり
	else                         bUse = false;	// 入力なし

	// 値を返す
	return StickStatus;

}

/*-----------------------------------------------------------------------------
 ジョイスティックの十字キーのリピート状態の取得
-----------------------------------------------------------------------------*/
int CInputGamePad::GetPadPOVRepeat(void)
{
	// 変数宣言
	int StickStatus = POV_NOTUSE;		// 十字キーデータ格納
	static int  nCntPOV = 0;			// POV入力カウンタ
	static bool bUse = false;			// POV入力の有無判断
	static bool bGo = false;			// POVリピートGoSign

	// ＰＯＶの入力がない場合
	if (bUse == false)
	{
		// 入力によって取得出来る値の割り振り
		if (m_nPadPOV == 0)     StickStatus = POV_UP;			// 十字キーの上ボタン
		if (m_nPadPOV == 4500)  StickStatus = POV_UPRIGHT;		// 十字キーの右上ボタン
		if (m_nPadPOV == 9000)  StickStatus = POV_RIGHT;		// 十字キーの右ボタン
		if (m_nPadPOV == 13500) StickStatus = POV_DOWNRIGHT;	// 十字キーの右下ボタン
		if (m_nPadPOV == 18000) StickStatus = POV_DOWN;			// 十字キーの下ボタン
		if (m_nPadPOV == 22500) StickStatus = POV_DOWNLEFT;		// 十字キーの左下ボタン
		if (m_nPadPOV == 27000) StickStatus = POV_LEFT;			// 十字キーの左ボタン
		if (m_nPadPOV == 31500) StickStatus = POV_UPLEFT;		// 十字キーの左ボタン
	}//if.fin

	// 十字キーの入力があった場合
	if (m_nPadPOV != POV_NOTUSE)
	{
		if (bGo == false)
		{
			bUse = true;		// 入力あり
			++nCntPOV;			// カウントアップ
		}//if.fin

		 // 入力間隔
		if ((nCntPOV == 90) || (nCntPOV == 120) || (nCntPOV == 150))
		{
			bUse = false;		// 入力あり
		}//if.fin

		 // 入力開放
		if (nCntPOV == 180)
		{
			bUse = false;		// 入力あり
			bGo = true;			// GoSign
		}//if.fin
	}
	else
	{
		bUse = false;			// 入力なし
		bGo = false;			// リセット
		nCntPOV = 0;			// カウンタリセット
	}//if.fin

	// 値を返す
	return StickStatus;

}

/*-----------------------------------------------------------------------------
 ゲームパッドを列挙するコールバック関数
-----------------------------------------------------------------------------*/
BOOL CALLBACK CInputGamePad::EnumPadCallback(const DIDEVICEINSTANCE* pDidInstance, LPVOID pContext)
{
	HRESULT hr;

	// 列挙されたゲームパッドへのインターフェースを取得する
	hr = m_pDInput->CreateDevice(pDidInstance->guidInstance, &m_pDevGamePad, NULL);

	//列挙を続ける
	if (FAILED(hr)) return DIDENUM_CONTINUE;

	// ゲームパッドの状態を調べる
	m_DevCaps.dwSize = sizeof(DIDEVCAPS);

	hr = m_pDevGamePad->GetCapabilities(&m_DevCaps);

	if (FAILED(hr))
	{
		// 入力デバイスインターフェースの解放
		SAFE_RELEASE(m_pDevGamePad);

		//列挙を続ける
		return DIDENUM_CONTINUE;
	}//if.fin

	 // 列挙の終了
	return DIDENU_STOP;

	// ２つ以上使用する場合
	// return DIENUM_CONTENUE;

}

/*-----------------------------------------------------------------------------
 ゲームパッドの軸を列挙するコールバック関数
-----------------------------------------------------------------------------*/
BOOL CALLBACK CInputGamePad::EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE pdidoi, LPVOID pvRef)
{
	// DIPROPRANGEの使用宣言
	DIPROPRANGE diprg;
	
	// 使用する分のメモリ領域の開放
	ZeroMemory(&diprg, sizeof(diprg));

	// 入力範囲の設定
	// 返された軸については、最小/最大値をスケーリングするために、列挙された軸のDIPROP_RANGEプロパティを設定
	if (pdidoi->dwType & DIDFT_AXIS)
	{
		diprg.diph.dwSize       = sizeof(DIPROPRANGE);
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		diprg.diph.dwHow        = DIPH_BYID;				// タイプで取得することを指定
		diprg.diph.dwObj        = pdidoi->dwType;			// 列挙された軸を指定します
		diprg.lMin              = MIN_AXIS_PAD;				// 値の最小値
		diprg.lMax              = MAX_AXIS_PAD;				// 値の最大値
		
		//m_pDevGamePad = (LPDIRECTINPUTDEVICE8)pvRef;

		// 最初の1つのみで列挙を終了する
		if (FAILED(m_pDevGamePad->SetProperty(DIPROP_RANGE, &diprg.diph))) return DIDENU_STOP;

	}//if.fin

	// ２つ以上の列挙が必要な場合に続行する
	return DIDENUM_CONTINUE;

}



