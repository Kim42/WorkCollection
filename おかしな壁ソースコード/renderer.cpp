/*=============================================================================

 レンダー処理[ renderer.cpp ]

=============================================================================*/
/*=============================================================================
 インクルードヘッダ
=============================================================================*/
#include "manager.h"
#include "renderer.h"

/*=============================================================================
 静的メンバ変数の動的メモリ確保
=============================================================================*/
LPDIRECT3D9       CRenderer :: m_pD3D       = NULL;
LPDIRECT3DDEVICE9 CRenderer :: m_pD3DDevice = NULL;
LPD3DXFONT        CRenderer :: m_pFont      = NULL;

/*-----------------------------------------------------------------------------
 初期化処理関数
-----------------------------------------------------------------------------*/
HRESULT CRenderer :: Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// 変数宣言
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE        d3ddm;

	// Direct3Dオブジェクトの作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	// 返し
	if (m_pD3D == NULL)
	{
		MessageBox(NULL, "デバイスの読み込み失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}//if.fin

	 // 現在のディスプレイモードを取得
	if (FAILED(m_pD3D -> GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		MessageBox(NULL, "失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}//if.fin

	 // デバイスのプレゼントパラメーターの設定（デバイスを作るための設定をするための設定）
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// 値を０で初期化してくれる 同じ効果⇒ （= {0};）
	d3dpp.BackBufferWidth            = SCREEN_WIDTH;					// スクリーンの幅のバックバッファ
	d3dpp.BackBufferHeight           = SCREEN_HEIGHT;					// スクリーンの高さのバックバッファ
	d3dpp.BackBufferFormat           = d3ddm.Format;					// カラーモードの指定
	d3dpp.BackBufferCount            = 1;								
	d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD;			
	d3dpp.EnableAutoDepthStencil     = TRUE;							// エラー対策
	d3dpp.AutoDepthStencilFormat     = D3DFMT_D16;						// エラー対策
	d3dpp.Windowed                   = bWindow;							// スクリーン状態
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		

	// Direct3Dデバイスの作成（ハードウェアで行う）
	if (FAILED(
		m_pD3D -> CreateDevice(
			D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, 
			D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
	{
		// 描画はハードウェア、頂点処理はソフトウェアで行う
		if (FAILED(
			m_pD3D -> CreateDevice(
				D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, 
				D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
		{
			// 全てをソフトウェアで行う
			if (FAILED(
				m_pD3D -> CreateDevice(
					D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, 
					D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
			{
				MessageBox(NULL, "もう無理です！ＰＣ買い替えてください！", "エラー", MB_OK);
				return E_FAIL;
			}//if.fin

		}//if.fin

	}//if.fin

	// アルファブレンドの設定
	m_pD3DDevice -> SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	// 半透明処理を行う
	m_pD3DDevice -> SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	// 標準透過
	m_pD3DDevice -> SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Ｚ比較を行なう
	m_pD3DDevice -> SetRenderState(D3DRS_ZENABLE, TRUE);

	// テクスチャステージステート設定：カラー
	m_pD3DDevice -> SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3DDevice -> SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	m_pD3DDevice -> SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	// テクスチャステージステート設定：アルファ
	m_pD3DDevice -> SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice -> SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	m_pD3DDevice -> SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	// サンプラーステートの設定（テクスチャ縮小時）
	m_pD3DDevice -> SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	// サンプラーステートの設定（テクスチャ拡大時）
	m_pD3DDevice -> SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	// アグレッシブモードの設定
	m_pD3DDevice -> SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);

	// フォント設定
	D3DXCreateFont(m_pD3DDevice, 20, 0, 0, 0, 0, 0, 0, 0, 0, "tahoma", &m_pFont);

	// 正常終了
	return S_OK;

}

/*-----------------------------------------------------------------------------
 終了処理関数
-----------------------------------------------------------------------------*/
void CRenderer :: Uninit(void)
{
	// Direct3Dデバイスの解放
	SAFE_RELEASE(m_pD3DDevice);

	// Direct3Dインターフェースの解放
	SAFE_RELEASE(m_pD3D);

	// Direct3Dフォントの解放
	SAFE_RELEASE(m_pFont);

}

/*-----------------------------------------------------------------------------
 更新処理関数
-----------------------------------------------------------------------------*/
void CRenderer :: Update(void)
{
	
}

/*-----------------------------------------------------------------------------
 描画開始処理関数
-----------------------------------------------------------------------------*/
HRESULT CRenderer :: DrawBigen(void)
{
	// ビューポートと深度バッファのクリアとステンシルバッファの削除
	if (FAILED(m_pD3DDevice -> Clear(0, NULL, 		// クリアする領域は全面
		D3DCLEAR_TARGET |							// バックバッファを指定
		D3DCLEAR_ZBUFFER, 							// 深度バッファ（Zバッファ）を指定
		D3DCOLOR_RGBA(0, 0, 0, 255), 				// クリアする色
		1.0f, 										// クリアする深度バッファ（Zバッファ）の値
		0)))										// クリアするステンシルバッファの値 
	{
		return E_FAIL;
	}//if.fin
	
	// 描画開始設定
	if(FAILED(m_pD3DDevice -> BeginScene())) return E_FAIL;

	// 正常終了
	return S_OK;

}

/*-----------------------------------------------------------------------------
 描画終了処理関数
-----------------------------------------------------------------------------*/
void CRenderer :: DrawEnd(void)
{
	// ディスプレイへの描画処理
	m_pD3DDevice -> EndScene();

	 // 描画結果の転送
	m_pD3DDevice -> Present(NULL, NULL, NULL, NULL);

}

