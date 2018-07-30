/*=============================================================================

 プレイヤーヘッダ[ player.h ]

=============================================================================*/
/*-----------------------------------------------------------------------------
 インクルードガード
-----------------------------------------------------------------------------*/
#ifndef _PLAYER_H_
#define _PLAYER_H_

/*-----------------------------------------------------------------------------
 インクルードファイル
-----------------------------------------------------------------------------*/
#include "scene3D.h"

/*-----------------------------------------------------------------------------
 プレイヤーメソッド前方宣言
-----------------------------------------------------------------------------*/
class CAction;

/*-----------------------------------------------------------------------------
 クラス定義：シーン３Ｄ継承
-----------------------------------------------------------------------------*/
class CPlayer : public CScene3D
{
	private:

		// 接地判定フラグ
		bool m_bGround;
		bool m_bItem;
		bool m_bGoal;
		bool m_bOver;
		bool bRe;
		bool bCreate;

		int GoalCount;

		// 前回位置
		D3DXVECTOR3 m_OldPos;

		// 移動量
		D3DXVECTOR3 m_Move;

		// 移動処理機能
		CAction *m_Action;

		// 衝突判定による共通挙動処理
		void CollisionBehavior(D3DXVECTOR3 targetPos, D3DXVECTOR3 targetSize);

		// オブジェクトとの衝突判定処理
		void CollisionField(void);
		void CollisionWall(void);
		void CollisionItem(void);

		// テクスチャアニメーション
		void ChangeTexture(void);

		// 切羽詰まっているので許してね処理関数
		void SubResult(void);

	public:

		// コンストラクタ & デスクトラクタ
		CPlayer();
		~CPlayer();

		// 生成関数
		static CPlayer *Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size);

		// 各処理関数
		HRESULT Init  (int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size);
		void    Uninit(void);
		void    Update(void);
		void    Draw  (void);

		// 移動量の取得
		D3DXVECTOR3 GetMove(void) { return m_Move; }

		// 移動量の設置
		void InitializeMove(void) { m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); }

		// 状態の取得
		bool GetGoal(void) { return m_bGoal; }
		bool GetOver(void) { return m_bOver; }

};

/*-----------------------------------------------------------------------------
 インクルードエンド
-----------------------------------------------------------------------------*/
#endif
