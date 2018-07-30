/*=============================================================================

 スイッチ[ swtch.cpp ]

=============================================================================*/
/*=============================================================================
 インクルードヘッダ
=============================================================================*/
#include "manager.h"

#include "collision.h"
#include "switch.h"
#include "field.h"

/*=============================================================================
 マクロ定義
=============================================================================*/
#define TEX_X 0.333f
#define ADJUSTMENT 0.2f			// 幅の衝突範囲調整

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

/*-----------------------------------------------------------------------------
コンストラクタ
-----------------------------------------------------------------------------*/
CSwitch::CSwitch()
{
	SetObjType(TYPE_SWITCH);
}

/*-----------------------------------------------------------------------------
デストラクタ
-----------------------------------------------------------------------------*/
CSwitch::~CSwitch()
{

}

/*-----------------------------------------------------------------------------
生成関数
-----------------------------------------------------------------------------*/
CSwitch *CSwitch::Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nFieldID)
{
	// 変数クラス定義
	CSwitch *pClass;

	// インスタンスの生成
	pClass = new CSwitch;

	// 初期化
	pClass->Init(nTexType, pos, size, nFieldID);

	// 返還
	return pClass;

}

/*-----------------------------------------------------------------------------
初期化処理関数
-----------------------------------------------------------------------------*/
HRESULT CSwitch::Init(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nFieldID)
{
	// 引数の代入
	m_Pos      = pos;
	m_Size     = size;
	m_nTexType = nTexType;
	m_nFieldID = nFieldID;
	m_fTexX    = 0.0f;
	m_nTimer   = 0;
	m_bSwitch  = false;

	// オブジェクト初期化
	CScene3D::Init();

	// 仮想アドレス宣言
	VERTEX_3D *pVtx;

	// 頂点バッファをロックして仮想アドレスの取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ＵＶ値の設定
	switch (nTexType - SWITCHANIMETION0)
	{
		case UP:
			pVtx[0].tex = D3DXVECTOR2(0, 0);
			pVtx[1].tex = D3DXVECTOR2(TEX_X, 0);
			pVtx[2].tex = D3DXVECTOR2(0, 1);
			pVtx[3].tex = D3DXVECTOR2(TEX_X, 1);
			break;

		case BOTTOM:
			pVtx[0].tex = D3DXVECTOR2(TEX_X, 1);
			pVtx[1].tex = D3DXVECTOR2(0, 1);
			pVtx[2].tex = D3DXVECTOR2(TEX_X, 0);
			pVtx[3].tex = D3DXVECTOR2(0, 0);
			break;

		case LEFT:
			pVtx[0].tex = D3DXVECTOR2(TEX_X, 0);
			pVtx[1].tex = D3DXVECTOR2(TEX_X, 1);
			pVtx[2].tex = D3DXVECTOR2(0, 0);
			pVtx[3].tex = D3DXVECTOR2(0, 1);
			break;

		case RIGHT:
			pVtx[0].tex = D3DXVECTOR2(0, 1);
			pVtx[1].tex = D3DXVECTOR2(0, 0);
			pVtx[2].tex = D3DXVECTOR2(TEX_X, 1);
			pVtx[3].tex = D3DXVECTOR2(TEX_X, 0);
			break;
	}//switch.fin

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	// 正常終了
	return S_OK;

}

/*-----------------------------------------------------------------------------
終了処理関数
-----------------------------------------------------------------------------*/
void CSwitch::Uninit(void)
{
	// オブジェクト終了
	CScene3D::Uninit();

}

/*-----------------------------------------------------------------------------
更新処理関数
-----------------------------------------------------------------------------*/
void CSwitch::Update(void)
{
	// アイテム衝突判定
	CollisionObj();

	// スイッチがおされたら
	if (m_bSwitch == true && m_nTimer < 10)
	{
		// IDの取得
		CScene *pScene = CScene::GetScene(m_nFieldID);

		// テクスチャアニメーション
		Animtion();

		// 消す // どっかにおいやる
		if (m_nTimer >= 10) pScene->SetPos(D3DXVECTOR3(-100.0f, -100.0f, 0.0f));

	}//if.fin

	// オブジェクト更新
	CScene3D::Update();

}

/*-----------------------------------------------------------------------------
描画処理関数
-----------------------------------------------------------------------------*/
void CSwitch::Draw(void)
{
	// オブジェクト描画
	CScene3D::Draw();

}

/*-----------------------------------------------------------------------------
 衝突判定処理関数
-----------------------------------------------------------------------------*/
void CSwitch::CollisionObj(void)
{
	// プレイヤーが触れた時と、アイテムブロックが触れた時で分ける！！！

	D3DXVECTOR3 pos, size;

	// シーンオブジェクト数分のループ
	for (int nCnt = 0; nCnt < NUM_SCENE; nCnt++)
	{
		// IDの取得
		CScene *pScene = CScene::GetScene(nCnt);

		// NULLCHECK
		if (pScene == NULL) continue;

		// データの取得
		pos = pScene->GetPos(), size = pScene->GetSize();

		// 対応するフィールドオブジェクトを削除する
		switch (C2DCollision::ColRect_Dir(pos, size,
				D3DXVECTOR3(m_Pos.x + (ADJUSTMENT * 0.5f), m_Pos.y, m_Pos.z),
				D3DXVECTOR3(m_Size.x - ADJUSTMENT, m_Size.y, m_Size.z)))
		{
			case C2DCollision::UP:

				if ((m_nTexType - SWITCHANIMETION0) == C2DCollision::UP) m_bSwitch = true;
				break;

			case C2DCollision::BOTTOM:

				if ((m_nTexType - SWITCHANIMETION0) == C2DCollision::BOTTOM) m_bSwitch = true;
				break;

			case C2DCollision::LEFT:

				m_bSwitch = true;
				break;

			case C2DCollision::RIGHT:

				m_bSwitch = true;
				break;

		}//switch.fin

	}//for.fin

}

/*-----------------------------------------------------------------------------
 テクスチャアニメーション処理関数
-----------------------------------------------------------------------------*/
void CSwitch::Animtion(void)
{
	m_nTimer++;

	if (m_nTimer == 8) m_fTexX += TEX_X;
	if (m_nTimer == 10) m_fTexX += TEX_X;

	// 仮想アドレス宣言
	VERTEX_3D *pVtx;

	// 頂点バッファをロックして仮想アドレスの取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ＵＶ値の設定
	switch (m_nTexType - SWITCHANIMETION0)
	{
		case UP:
			pVtx[0].tex = D3DXVECTOR2(m_fTexX, 0);
			pVtx[1].tex = D3DXVECTOR2(m_fTexX + TEX_X, 0);
			pVtx[2].tex = D3DXVECTOR2(m_fTexX, 1);
			pVtx[3].tex = D3DXVECTOR2(m_fTexX + TEX_X, 1);
			break;

		case BOTTOM:
			pVtx[0].tex = D3DXVECTOR2(m_fTexX + TEX_X, 1);
			pVtx[1].tex = D3DXVECTOR2(m_fTexX, 1);
			pVtx[2].tex = D3DXVECTOR2(m_fTexX + TEX_X, 0);
			pVtx[3].tex = D3DXVECTOR2(m_fTexX, 0);
			break;

		case LEFT:
			pVtx[0].tex = D3DXVECTOR2(m_fTexX + TEX_X, 0);
			pVtx[1].tex = D3DXVECTOR2(m_fTexX + TEX_X, 1);
			pVtx[2].tex = D3DXVECTOR2(m_fTexX, 0);
			pVtx[3].tex = D3DXVECTOR2(m_fTexX, 1);
			break;

		case RIGHT:
			pVtx[0].tex = D3DXVECTOR2(m_fTexX, 1);
			pVtx[1].tex = D3DXVECTOR2(m_fTexX, 0);
			pVtx[2].tex = D3DXVECTOR2(m_fTexX + TEX_X, 1);
			pVtx[3].tex = D3DXVECTOR2(m_fTexX + TEX_X, 0);
			break;
	}//switch.fin

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();

}

