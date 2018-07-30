/*=============================================================================

 レンダー処理ヘッダ[ renderer.h ]

=============================================================================*/
/*-----------------------------------------------------------------------------
 インクルードガード
-----------------------------------------------------------------------------*/
#ifndef _RENDERER_H_
#define _RENDERER_H_

/*-----------------------------------------------------------------------------
 クラス定義
-----------------------------------------------------------------------------*/
class CRenderer
{
	private:

		// Direct3Dインターフェース
		static LPDIRECT3D9 m_pD3D;

		// Direct3Dデバイスへのポインタ
		static LPDIRECT3DDEVICE9 m_pD3DDevice;

	public:

		// コンストラクタ & デスクトラクタ
		CRenderer() {}
		~CRenderer() {}

		// 各処理関数
		static HRESULT Init  (HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
		static void    Uninit(void);
		static void    Update(void);
		static HRESULT DrawBigen(void);
		static void    DrawEnd  (void);

		// デバイス取得
		static LPDIRECT3DDEVICE9 GetDevice(void){ return m_pD3DDevice; }

		// デバッグテキスト
		static LPD3DXFONT m_pFont;

};

/*-----------------------------------------------------------------------------
 インクルードエンド
-----------------------------------------------------------------------------*/
#endif
