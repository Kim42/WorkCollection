/*=============================================================================

 フェード描画処理[ fade.cpp ]

=============================================================================*/
/*=============================================================================
インクルードヘッダ
=============================================================================*/
#include "manager.h"
#include "renderer.h"
#include "texture.h"

#include "fade.h"

/*=============================================================================
 マクロ定義
=============================================================================*/
#define FADE_RATE_FULL (0.02f)

/*=============================================================================
 ２Ｄ頂点フォーマット
=============================================================================*/
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

/*=============================================================================
 2D頂点情報構造体
=============================================================================*/
struct VERTEX_2D
{
	D3DXVECTOR3 pos;		// 座標位置
	float       rhw;		// 変換済み座標
	D3DCOLOR    col;		// 色
	D3DXVECTOR2 tex;		// テクスチャ座標
};

/*-----------------------------------------------------------------------------
 生成処理関数
-----------------------------------------------------------------------------*/
CFade *CFade::Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// 変数クラス定義
	CFade *pClass;

	// インスタンスの生成5
	pClass = new CFade;

	// 初期化
	pClass->Init(nTexType, pos, size, color);

	// 返還
	return pClass;

}

/*-----------------------------------------------------------------------------
 初期化処理関数
-----------------------------------------------------------------------------*/
HRESULT CFade::Init(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	m_Pos = pos;
	m_Size = size;
	m_nTexType = nTexType;

	//m_Fade = FADE_NONE;
	m_Color = color;

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// 頂点バッファの生成
	if(FAILED(pDevice -> CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,					// 作成したい頂点バッファのサイズ
		D3DUSAGE_WRITEONLY,						// 書き込みのみ実行（最速だが書き込み後ほったらかし）
		FVF_VERTEX_2D,							// 頂点フォーマットの設定（０でも大丈夫）
		D3DPOOL_MANAGED,						// メモリ管理をどうするか ⇒ お任せ
		&m_pVtxBuff,							// 頂点バーテックスアドレス
		NULL)))
	{
		MessageBox(NULL, "2D頂点バッファの\n生成に失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}//if.fin

	// 頂点情報を設定
	VERTEX_2D *pVtx = NULL;

	// 頂点バッファのロック
	m_pVtxBuff -> Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x,            m_Pos.y,            0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Pos.x + m_Size.x, m_Pos.y,            0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x,            m_Pos.y + m_Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Pos.x + m_Size.x, m_Pos.y + m_Size.y, 0.0f);

	// rhwの設定(必ず1.0f)
	pVtx[0].rhw = 
	pVtx[1].rhw = 
	pVtx[2].rhw = 
	pVtx[3].rhw = 1.0f;

	// 頂点カラ―の設定
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = m_Color;

	// ＵＶ値の設定
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);
	
	// 頂点バッファのアンロック
	m_pVtxBuff -> Unlock();

	// 正常終了
	return S_OK;

}

/*-----------------------------------------------------------------------------
 終了処理関数
-----------------------------------------------------------------------------*/
void CFade::Uninit(void)
{
	// バーテックスバッファの解放
	SAFE_RELEASE(m_pVtxBuff);

}

/*-----------------------------------------------------------------------------
 更新処理関数
-----------------------------------------------------------------------------*/
void CFade::Update(void)
{
	//処理をしないで終了
	if (m_Fade == FADE_NONE) return;
	
	//フェードイン
	if (m_Fade == FADE_IN)
	{
		m_Color.a -= FADE_RATE_FULL;

		//終了判定
		if (m_Color.a <= 0.0f)
		{
			m_Color.a = 0.0f;
			m_Fade = FADE_NONE;
		}//if.fin

	}//if.fin

	//フェードアウト
	if (m_Fade == FADE_OUT)
	{
		m_Color.a += FADE_RATE_FULL;

		//終了判定
		if (m_Color.a >= 1.0f)
		{
			m_Color.a = 1.0f;
			m_Fade = FADE_IN;
		}//if.fin
		
	}//if.fin

	// 頂点情報を設定
	VERTEX_2D *pVtx = NULL;

	// 頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// カラーの反映
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = m_Color;

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();

}

/*-----------------------------------------------------------------------------
 描画処理関数
-----------------------------------------------------------------------------*/
void CFade::Draw(void)
{
	//描画せずに終了
	if (m_Fade == FADE_NONE) return;

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice -> SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice -> SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice -> SetTexture(0, CTexture::GetAdr(m_nTexType));

	// ポリゴンの描画
	pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}


