/*=============================================================================

 バックグラウンド[ bg.cpp ]

=============================================================================*/
/*=============================================================================
インクルードヘッダ
=============================================================================*/
#include "manager.h"
#include "renderer.h"
#include "texture.h"

#include "bg.h"

/*=============================================================================
 頂点フォーマット定義
=============================================================================*/
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL | D3DFVF_TEX1)

/*=============================================================================
 ３Ｄ頂点情報構造体
=============================================================================*/
struct VERTEX_3D
{
	D3DXVECTOR3 pos;		// 座標位置
	D3DXVECTOR3 nor;		// 法線
	D3DCOLOR    col;		// 色
	D3DXVECTOR2 tex;		// テクスチャ座標
};

/*=============================================================================
 静的メンバの動的確保動的確保
=============================================================================*/
LPDIRECT3DVERTEXBUFFER9 CBg::m_pVtxBuff;
D3DXVECTOR3 CBg::m_Pos;
D3DXVECTOR3 CBg::m_Size;
int CBg::m_nTexType;

/*-----------------------------------------------------------------------------
 初期化処理関数
-----------------------------------------------------------------------------*/
HRESULT CBg::Init(int nTexType)
{
	// 引数の代入
	m_Pos = D3DXVECTOR3(-5.0f, -5.0f, 1.0f);
	m_Size = D3DXVECTOR3(80.0f, 30.0f, 0.0f);
	m_nTexType = nTexType;

	m_pVtxBuff = NULL;

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,					// 作成したい頂点バッファのサイズ(構造体)*頂点数
		D3DUSAGE_WRITEONLY,						// 書き込みのみ実行（最速だが書き込み後ほったらかし）
		FVF_VERTEX_3D,							// 頂点フォーマットの設定（０でも大丈夫）
		D3DPOOL_MANAGED,						// メモリ管理をどうするか ⇒ お任せ
		&m_pVtxBuff,							// 頂点バッファの管理のインターフェースポインタ
		NULL)))									// 使わない
	{
		MessageBox(NULL, "3D頂点バッファの\n生成に失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}// if.fin

	// 仮想アドレス宣言
	VERTEX_3D *pVtx;

	// 頂点バッファをロックして仮想アドレスの取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定(必ず３Ｄ空間の原点(0,0)に設定される)
	pVtx[0].pos = D3DXVECTOR3(0.0f, m_Size.y, m_Size.z);
	pVtx[1].pos = D3DXVECTOR3(m_Size.x, m_Size.y, m_Size.z);
	pVtx[2].pos = D3DXVECTOR3(0.0f, m_Size.y - m_Size.y, m_Size.z);
	pVtx[3].pos = D3DXVECTOR3(m_Size.x, m_Size.y - m_Size.y, m_Size.z);

	// 法線の設定(２Ｄゲーム仕様なので手前向き)
	pVtx[0].nor =
	pVtx[1].nor =
	pVtx[2].nor =
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// 頂点カラ―の設定
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(3, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(3, 1);

	 // 頂点バッファのアンロック
	m_pVtxBuff->Unlock();
	
	// 正常終了
	return S_OK;

}

/*-----------------------------------------------------------------------------
 終了処理関数
-----------------------------------------------------------------------------*/
void CBg::Uninit(void)
{
	// 頂点バッファインターフェースの解放
	SAFE_RELEASE(m_pVtxBuff);
}

/*-----------------------------------------------------------------------------
 更新処理関数
-----------------------------------------------------------------------------*/
void CBg::Update(void)
{
	static float i = 0.0f;

	i += 0.001f;

	// 仮想アドレス宣言
	VERTEX_3D *pVtx;

	// 頂点バッファをロックして仮想アドレスの取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0 + i, 0);
	pVtx[1].tex = D3DXVECTOR2(3 + i, 0);
	pVtx[2].tex = D3DXVECTOR2(0 + i, 1);
	pVtx[3].tex = D3DXVECTOR2(3 + i, 1);

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();

}

/*-----------------------------------------------------------------------------
 描画処理関数
-----------------------------------------------------------------------------*/
void CBg::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// ワールドマトリクス
	D3DXMATRIXA16 mtxWorld;

	// 単位行列に初期化(動かさないようにする)
	D3DXMatrixIdentity(&mtxWorld);

	// 平行移動処理
	D3DXMatrixTranslation(&mtxWorld, m_Pos.x, m_Pos.y, m_Pos.z);

	// ワールド座標変換を行う
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点をストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャ設定
	pDevice->SetTexture(0, CTexture::GetAdr(m_nTexType));

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

