/*=============================================================================

 フェードヘッダ[ fade.h ]

=============================================================================*/
/*-----------------------------------------------------------------------------
 インクルードガード
-----------------------------------------------------------------------------*/
#ifndef _FADE_H_
#define _FADE_H_

/*-----------------------------------------------------------------------------
 クラス定義
-----------------------------------------------------------------------------*/
class CFade
{
	public:

		// フェード状態の列挙型
		enum FADE
		{
			FADE_NONE = 0,		// なし
			FADE_IN,			// フェードイン
			FADE_OUT,			// フェードアウト
			FADE_MAX			// 最大
		};

	private:

		// フェードの状態
		FADE m_Fade;

		// 頂点バッファインターフェース
		LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;

		// ポジション
		D3DXVECTOR3 m_Pos;

		// サイズ
		D3DXVECTOR3 m_Size;

		// テクスチャ
		int m_nTexType;

		// カラー状態
		D3DXCOLOR m_Color;

	public:

		CFade() { m_pVtxBuff = NULL; }
		~CFade() {}

		// 生成処理
		static CFade *Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);

		// 各処理関数
		HRESULT Init(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);
		void    Uninit(void);
		void    Update(void);
		void    Draw(void);

		// セット
		void SetFade(FADE fade) { m_Fade = fade; }

		// ゲットカラー
		float GetColor(void) { return m_Color.a; }

};

/*-----------------------------------------------------------------------------
 インクルードエンド
-----------------------------------------------------------------------------*/
#endif