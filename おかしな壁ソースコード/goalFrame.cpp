/*=============================================================================

 バックグラウンド[ bg.cpp ]

=============================================================================*/
/*=============================================================================
 インクルードヘッダ
=============================================================================*/
#include "manager.h"
#include "renderer.h"
#include "texture.h"

#include "goalFrame.h"

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
LPDIRECT3DVERTEXBUFFER9 CGoalFrame::m_pVtxBuffFrame;
LPDIRECT3DVERTEXBUFFER9 CGoalFrame::m_pVtxBuffIcon;
D3DXVECTOR3 CGoalFrame::m_Pos;

/*-----------------------------------------------------------------------------
 初期化処理関数
-----------------------------------------------------------------------------*/
HRESULT CGoalFrame::Init(D3DXVECTOR3 pos)
{
	// 引数の代入
	m_pVtxBuffFrame = NULL;
	m_pVtxBuffIcon  = NULL;
	m_Pos = D3DXVECTOR3(pos.x - 1.0f, pos.y, 0.1f);

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,					// 作成したい頂点バッファのサイズ(構造体)*頂点数
		D3DUSAGE_WRITEONLY,						// 書き込みのみ実行（最速だが書き込み後ほったらかし）
		FVF_VERTEX_3D,							// 頂点フォーマットの設定（０でも大丈夫）
		D3DPOOL_MANAGED,						// メモリ管理をどうするか ⇒ お任せ
		&m_pVtxBuffFrame,							// 頂点バッファの管理のインターフェースポインタ
		NULL)))									// 使わない
	{
		MessageBox(NULL, "3D頂点バッファの\n生成に失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}// if.fin

	 // 仮想アドレス宣言
	VERTEX_3D *pVtx;

	// 頂点バッファをロックして仮想アドレスの取得
	m_pVtxBuffFrame->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定(必ず３Ｄ空間の原点(0,0)に設定される)
	pVtx[0].pos = D3DXVECTOR3(0.0f, 4.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(4.0f, 4.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(4.0f, 0.0f, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(4, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(4, 1);

	// 頂点バッファのアンロック
	m_pVtxBuffFrame->Unlock();

	/*=============================================================================*/

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,					// 作成したい頂点バッファのサイズ(構造体)*頂点数
		D3DUSAGE_WRITEONLY,						// 書き込みのみ実行（最速だが書き込み後ほったらかし）
		FVF_VERTEX_3D,							// 頂点フォーマットの設定（０でも大丈夫）
		D3DPOOL_MANAGED,						// メモリ管理をどうするか ⇒ お任せ
		&m_pVtxBuffIcon,							// 頂点バッファの管理のインターフェースポインタ
		NULL)))									// 使わない
	{
		MessageBox(NULL, "3D頂点バッファの\n生成に失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}// if.fin

	// 頂点バッファをロックして仮想アドレスの取得
	m_pVtxBuffIcon->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定(必ず３Ｄ空間の原点(0,0)に設定される)
	pVtx[0].pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(2.0f, 1.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(2.0f, 0.0f, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);

	// 頂点バッファのアンロック
	m_pVtxBuffIcon->Unlock();

	// 正常終了
	return S_OK;

}

/*-----------------------------------------------------------------------------
 終了処理関数
-----------------------------------------------------------------------------*/
void CGoalFrame::Uninit(void)
{
	// 頂点バッファインターフェースの解放
	SAFE_RELEASE(m_pVtxBuffFrame);
	SAFE_RELEASE(m_pVtxBuffIcon);

}

/*-----------------------------------------------------------------------------
 更新処理関数
-----------------------------------------------------------------------------*/
void CGoalFrame::Update(void)
{

}

/*-----------------------------------------------------------------------------
 描画処理関数
-----------------------------------------------------------------------------*/
void CGoalFrame::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// ワールドマトリクス
	D3DXMATRIXA16 mtxWorld;

	// 単位行列に初期化(動かさないようにする)
	D3DXMatrixIdentity(&mtxWorld);

	// 平行移動処理
	D3DXMatrixTranslation(&mtxWorld, m_Pos.x + 0.05f, m_Pos.y, m_Pos.z);

	// ワールド座標変換を行う
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点をストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuffFrame, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャ設定
	pDevice->SetTexture(0, CTexture::GetAdr(GOAL_FRAME));

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	/*=============================================================================*/

	// 単位行列に初期化(動かさないようにする)
	D3DXMatrixIdentity(&mtxWorld);

	// 平行移動処理
	D3DXMatrixTranslation(&mtxWorld, m_Pos.x + 1.0f, m_Pos.y + 3.0f, m_Pos.z);

	// ワールド座標変換を行う
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点をストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuffIcon, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャ設定
	pDevice->SetTexture(0, CTexture::GetAdr(EXIT_ICON));

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

