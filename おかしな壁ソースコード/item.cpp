/*=============================================================================

 アイテム[ item.cpp ]

=============================================================================*/
/*=============================================================================
 インクルードヘッダ
=============================================================================*/
#include "manager.h"
#include "item.h"
#include "goalFrame.h"

#include "collision.h"
#include "action.h"

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
 生成関数
-----------------------------------------------------------------------------*/
CItem *CItem::Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nSubType)
{
	// 変数クラス定義
	CItem *pClass;

	// インスタンスの生成：タイプ別
	switch (nSubType)
	{
		case SUB_GOAL:

			pClass = new CGoal;
			pClass->Init(nTexType, pos, D3DXVECTOR3(2.0f, 3.0f, size.z), nSubType);
			break;

		case SUB_COLLECT_ITEM:

			pClass = new CCollect;
			pClass->Init(nTexType, pos, D3DXVECTOR3(0.5f, 0.5f, size.z), nSubType);
			break;

		case SUB_BLOCK:

			pClass = new CBlock;
			pClass->Init(nTexType, pos, size, nSubType);
			break;

		case SUB_NEEDLE:

			pClass = new CNeedle;
			pClass->Init(nTexType, pos, D3DXVECTOR3(size.x, 1.0f, size.z), nSubType);
			break;

		case SUB_ARROW:

			pClass = new CArrow;
			pClass->Init(nTexType, pos, D3DXVECTOR3(1.0f, 1.0f, size.z), nSubType);
			break;

	}//switch.fin

	// 返還
	return pClass;

}

/*-----------------------------------------------------------------------------
 初期化処理関数
-----------------------------------------------------------------------------*/
HRESULT CItem::Init(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nSubType)
{
	// 引数の代入
	m_Pos      = pos;
	m_Size     = size;
	m_nTexType = nTexType;
	m_SubType  = (SUBTYPE)nSubType;

	// オブジェクト初期化
	CScene3D::Init();

	// ゴールは正常に
	if (m_SubType == SUB_GOAL)
	{
		// 仮想アドレス宣言
		VERTEX_3D *pVtx;

		// 頂点バッファをロックして仮想アドレスの取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		
		pVtx[0].tex = D3DXVECTOR2(0, 0);
		pVtx[1].tex = D3DXVECTOR2(1, 0);
		pVtx[2].tex = D3DXVECTOR2(0, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 1);

		// 頂点バッファのアンロック
		m_pVtxBuff->Unlock();

		// フレームを初期化
		CGoalFrame::Init(pos);

	}//if.fin

	// 正常終了
	return S_OK;

}

/*-----------------------------------------------------------------------------
 終了処理関数
-----------------------------------------------------------------------------*/
void CItem::Uninit(void)
{
	// フレームの終了
	if (m_SubType == SUB_GOAL) CGoalFrame::Uninit();

	// オブジェクトの破棄
	CScene3D::Uninit();
}

/*-----------------------------------------------------------------------------
 描画処理関数
-----------------------------------------------------------------------------*/
void CItem::Draw(void)
{
	// フレームの描画
	if (m_SubType == SUB_GOAL) CGoalFrame::Draw();

	// オブジェクトの描画
	CScene3D::Draw();

}

/*-----------------------------------------------------------------------------
 更新処理関数：ブロック
-----------------------------------------------------------------------------*/
void CBlock::Update(void)
{
	// 移動前の座標の保管
	m_OldPos = m_Pos;

	// 重力(何故か３０倍)
	m_Pos.y += CAction::Gravity() * 30.0f;

	// シーンオブジェクト数分のループ
	for (int nCnt = 0; nCnt < NUM_SCENE; nCnt++)
	{
		// IDの取得
		CScene *pScene = CScene::GetScene(nCnt);

		// NULLCHECK
		if (pScene == NULL) continue;

		// THISCHECK
		if (pScene == this) continue;

		// TYPECHECK
		CItem *pItem = (CItem*)pScene;
		if (pItem->GetSubType() == SUB_COLLECT_ITEM || pItem->GetSubType() == SUB_ARROW) continue;

		// オブジェクトタイプの識別
		if ((pScene->GetObjType() != TYPE_PLAYER) && (pScene->GetObjType() != TYPE_SWITCH))
		{
			// データの取得
			D3DXVECTOR3 pos = pScene->GetPos(), size = pScene->GetSize();

			// 共通衝突判定挙動処理
			CollisionObjVertical(pos, size);

			// 返り値：当たっているかいないか
			if ((m_bMove = CollisionObjSide(pos, size)) == false) break;

		}//if.fin

	}//for.fin

}

/*-----------------------------------------------------------------------------
 縦オブジェクト衝突判定処理
-----------------------------------------------------------------------------*/
void CBlock::CollisionObjVertical(D3DXVECTOR3 targetPos, D3DXVECTOR3 targetSize)
{
	if (C2DCollision::UP == C2DCollision::ColRect_Dir(m_Pos, m_Size, targetPos, targetSize))
	{
		// 重力相殺
		m_fMoveY = CAction::NoGravity();
		m_Pos.y = targetPos.y + targetSize.y;
		return;
	}//if.fin

	if (C2DCollision::BOTTOM == C2DCollision::ColRect_Dir(m_Pos, m_Size, targetPos, targetSize))
	{
		m_fMoveY = -CAction::NoGravity();
		return;
	}//if.fin

}

/*-----------------------------------------------------------------------------
 横オブジェクト衝突判定処理
-----------------------------------------------------------------------------*/
bool CBlock::CollisionObjSide(D3DXVECTOR3 targetPos, D3DXVECTOR3 targetSize)
{
	if (C2DCollision::LEFT == C2DCollision::ColRect_Dir(m_Pos, m_Size, targetPos, targetSize))
	{
		m_Pos.y = m_OldPos.y;
		m_Pos.x = targetPos.x - m_Size.x;
		return false;
	}//if.fin

	if (C2DCollision::RIGHT == C2DCollision::ColRect_Dir(m_Pos, m_Size, targetPos, targetSize))
	{
		m_Pos.y = m_OldPos.y;
		m_Pos.x = targetPos.x + m_Size.x;
		return false;
	}//if.fin

	return true;

}
