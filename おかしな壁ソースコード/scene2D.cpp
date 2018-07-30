/*=============================================================================

 ２Ｄポリゴン描画処理[ scene2D.cpp ]

=============================================================================*/
/*=============================================================================
 インクルードヘッダ
=============================================================================*/
#include "scene2D.h"

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
 コンストラクタ
-----------------------------------------------------------------------------*/
CScene2D :: CScene2D()
{
	m_Pos  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	m_nTexType = -1;

	m_pVtxBuff = NULL;

}

/*-----------------------------------------------------------------------------
 デスクトラクタ
-----------------------------------------------------------------------------*/
CScene2D :: ~CScene2D()
{
	m_Pos  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nTexType = -1;

	m_pVtxBuff = NULL;

}

/*-----------------------------------------------------------------------------
 初期化処理関数
-----------------------------------------------------------------------------*/
HRESULT CScene2D :: Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// 頂点バッファの生成
	if(FAILED(pDevice -> CreateVertexBuffer(
		sizeof(VERTEX_2D) * NUM_VERTEX,		// 作成したい頂点バッファのサイズ
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
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

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
void CScene2D :: Uninit(void)
{
	// バーテックスバッファの解放
	SAFE_RELEASE(m_pVtxBuff);

	// オブジェクトの破棄( 自身 )
	CScene::Release();

}

/*-----------------------------------------------------------------------------
 更新処理関数
-----------------------------------------------------------------------------*/
void CScene2D :: Update(void)
{
	// 頂点情報を設定
	VERTEX_2D *pVtx = NULL;

	// 頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x, m_Pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Pos.x + m_Size.x, m_Pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x, m_Pos.y + m_Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Pos.x + m_Size.x, m_Pos.y + m_Size.y, 0.0f);

	// ＵＶ値の設定
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();

}

/*-----------------------------------------------------------------------------
 描画処理関数
-----------------------------------------------------------------------------*/
void CScene2D :: Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice -> SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice -> SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice -> SetTexture(0, CTexture::GetAdr(m_nTexType));

	// ポリゴンの描画
	pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_PRIMITIVE);

}

