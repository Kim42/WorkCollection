/*=============================================================================

 アイテムヘッダ[ item.h ]

=============================================================================*/
/*-----------------------------------------------------------------------------
 インクルードガード
-----------------------------------------------------------------------------*/
#ifndef _ITEM_H_
#define _ITEM_H_

/*-----------------------------------------------------------------------------
 インクルードファイル
-----------------------------------------------------------------------------*/
#include "scene3D.h"

/*-----------------------------------------------------------------------------
 オブジェクトタイプの列挙型定義
-----------------------------------------------------------------------------*/
enum SUBTYPE
{
	SUB_GOAL = 0,		// ０：ゴール
	SUB_COLLECT_ITEM,	// １：コレクトアイテム
	SUB_BLOCK,			// ２：ブロック
	SUB_NEEDLE,			// ３：ニードル
	SUB_ARROW,			// ４：矢印
};

/*-----------------------------------------------------------------------------
 クラス定義：シーン３Ｄ継承
-----------------------------------------------------------------------------*/
class CItem : public CScene3D
{
	protected:

		// サブタイプ
		SUBTYPE m_SubType;

		// サブタイプのセット
		void SetType(SUBTYPE sub) { m_SubType = sub; }

	public:

		// コンストラクタ & デスクトラクタ
		CItem() { SetObjType(TYPE_ITEM); }
		~CItem() {}

		// 生成関数
		static CItem *Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nSubType);

		// 各処理関数
		HRESULT Init(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nSubType);
		void    Uninit(void);
		virtual void Update(void) = 0;
		void    Draw(void);

		// サブタイプの取得
		SUBTYPE GetSubType(void) { return m_SubType; }

};

/*-----------------------------------------------------------------------------
 ゴールクラス：アイテム継承
-----------------------------------------------------------------------------*/
class CGoal : public CItem
{
	public:

		// コンストラクタ & デスクトラクタ
		CGoal() { SetType(SUB_GOAL); }
		~CGoal() {}

		// 更新処理のオーバーライド
		void Update(void) override {}

};

/*-----------------------------------------------------------------------------
 コレクトアイテム：アイテム継承
-----------------------------------------------------------------------------*/
class CCollect : public CItem
{
	public:

		// コンストラクタ & デスクトラクタ
		CCollect() { SetType(SUB_COLLECT_ITEM); }
		~CCollect() {}

		// 更新処理のオーバーライド
		void Update(void) override {}

};

/*-----------------------------------------------------------------------------
 ブロック：アイテム継承
-----------------------------------------------------------------------------*/
class CBlock : public CItem
{
	private:

		// 移動判定
		bool m_bMove;

		// 前回位置
		D3DXVECTOR3 m_OldPos;

		// 移動量
		float m_fMoveY;

		// オブジェクトとの衝突判定処理(プレイヤー以外)
		void CollisionObjVertical(D3DXVECTOR3 targetPos, D3DXVECTOR3 targetSize);
		bool CollisionObjSide(D3DXVECTOR3 targetPos, D3DXVECTOR3 targetSize);

	public:

		// コンストラクタ & デスクトラクタ
		CBlock() { SetType(SUB_BLOCK); m_bMove = true; m_fMoveY = 0.0f; }
		~CBlock() {}

		// 更新処理のオーバーライド
		void Update(void) override;

		// ポジションの移動
		void SetPosMove(float m_MoveX) { m_Pos.x += m_MoveX; }

		// 状態の取得
		bool GetMove(void) { return m_bMove; }

};

/*-----------------------------------------------------------------------------
 ニードルクラス：アイテム継承
-----------------------------------------------------------------------------*/
class CNeedle : public CItem
{
	public:

		// コンストラクタ & デスクトラクタ
		CNeedle() { SetType(SUB_NEEDLE); }
		~CNeedle() {}

		// 更新処理のオーバーライド
		void Update(void) override {}

};

/*-----------------------------------------------------------------------------
 矢印クラス：アイテム継承
-----------------------------------------------------------------------------*/
class CArrow : public CItem
{
	public:

		// コンストラクタ & デスクトラクタ
		CArrow() { SetType(SUB_ARROW); }
		~CArrow() {}

		// 更新処理のオーバーライド
		void Update(void) override {}

};

/*-----------------------------------------------------------------------------
 インクルードエンド
-----------------------------------------------------------------------------*/
#endif
