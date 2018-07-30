/*=============================================================================

 プレイヤー[ player.cpp ]

=============================================================================*/
/*=============================================================================
インクルードヘッダ
=============================================================================*/
#include "manager.h"
#include "sound.h"

#include "action.h"
#include "collision.h"
#include "collecter.h"

#include "player.h"
#include "field.h"
#include "wall.h"
#include "item.h"

#include "timer.h"

#include "halfFade.h"
#include "textTexture.h"

/*=============================================================================
 マクロ定義
=============================================================================*/
#define ADJUSTMENT 0.2f			// 幅の衝突範囲調整

bool g_PausePause = false;

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
CPlayer::CPlayer()
{
	SetObjType(TYPE_PLAYER);

	// アクションのインスタンス生成
	m_Action = new CAction();

}

/*-----------------------------------------------------------------------------
 デストラクタ
-----------------------------------------------------------------------------*/
CPlayer::~CPlayer()
{
	// アクション破棄
	delete m_Action;

}

/*-----------------------------------------------------------------------------
 生成関数
-----------------------------------------------------------------------------*/
CPlayer *CPlayer :: Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 変数クラス定義
	CPlayer *pClass;

	// インスタンスの生成
	pClass = new CPlayer;

	// 初期化
	pClass-> Init(nTexType, pos, size);

	// 返還
	return pClass;

}

/*-----------------------------------------------------------------------------
 初期化処理関数
-----------------------------------------------------------------------------*/
HRESULT CPlayer :: Init(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 引数の代入
	m_Pos = pos;
	m_Size = size;
	m_Move  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nTexType = nTexType;

	m_bItem = false;
	m_bGoal = false;
	m_bOver = false;

	bRe = false;
	bCreate = false;

	GoalCount = 0;

	// 接地判定確認
	if (pos.y > 0.0f)
		m_bGround = false;
	else
		m_bGround = true;

	// オブジェクト初期化
	CScene3D :: Init();

	g_PausePause = false;

	// 正常終了
	return S_OK;

}

/*-----------------------------------------------------------------------------
 終了処理関数
-----------------------------------------------------------------------------*/
void CPlayer :: Uninit(void)
{
	// オブジェクト終了
	CScene3D:: Uninit();

}

/*-----------------------------------------------------------------------------
 更新処理関数
-----------------------------------------------------------------------------*/
void CPlayer :: Update(void)
{
	// ゲームパッド使用宣言
	CInputGamePad *pGamePad = CManager::GetInputGamePad();

	if(pGamePad->GetPadButtonTrigger(CInputGamePad::GB_STRAT))
	{
		g_PausePause ^= true;
	}
		if(!g_PausePause)
		{
	// クリアかフェイルした場合
	if (m_bGoal != true && m_bOver != true)
	{
		// 移動前の座標の保管
		m_OldPos = m_Pos;

		// 移動結果を取得
		m_Move.x = m_Action->Move(m_Move.x, 0.9f, &m_bGround, &m_bItem);
		m_Move.y = m_Action->Jump(m_Move.y, 0.09f, &m_bGround);

		// 慣性を与える
		m_Action->Friction(&m_Move.x);

		// ポジションに反映
		m_Pos += m_Move;

		// アイテム衝突判定
		CollisionItem();

		// ウォール衝突判定
		CollisionWall();

		// スキル発動
		m_Action->Skill(m_Pos, m_Size);

		// フィールド衝突判定
		CollisionField();

		// 重力
		m_Move.y += CAction::Gravity();
	}
	else
	{
		if (bRe == true) return;

		SubResult();

		// シーンオブジェクト数分のループ
		for (int nCnt = 0; nCnt < NUM_SCENE; nCnt++)
		{
			// IDの取得
			CScene *pScene = CScene::GetScene(nCnt);

			// NULLCHECK
			if (pScene == NULL) continue;

			// オブジェクトタイプの識別：フィールド
			if (pScene->GetObjType() == TYPE_TIMER)
			{
				// 指定クラスにポインタキャスト
				CTimer *pTimer = (CTimer*)pScene;

				// データの取得
				pTimer->SetState(false);

				break;
			}//if.fin

		}//for.fin

	}//if.fin

	// テクスチャアニメーション
	ChangeTexture();

	// シーンオブジェクト数分のループ
	for (int nCnt = 0; nCnt < NUM_SCENE; nCnt++)
	{
		// IDの取得
		CScene *pScene = CScene::GetScene(nCnt);

		// NULLCHECK
		if (pScene == NULL) continue;

		// オブジェクトタイプの識別：フィールド
		if (pScene->GetObjType() == TYPE_TIMER)
		{
			// 指定クラスにポインタキャスト
			CTimer *pTimer = (CTimer*)pScene;

			// データの取得
			int nTime = pTimer->GetTime();

			if (nTime <= 0) m_bOver = true;

			break;
		}//if.fin

	}//for.fin

	// オブジェクト更新
	CScene3D:: Update();
		}

}

/*-----------------------------------------------------------------------------
 描画処理関数
-----------------------------------------------------------------------------*/
void CPlayer :: Draw(void)
{
	// オブジェクト描画
	CScene3D::Draw();

}

/*-----------------------------------------------------------------------------
 共通衝突判定挙動処理
-----------------------------------------------------------------------------*/
void CPlayer::CollisionBehavior(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	switch (C2DCollision::ColRect_Dir(
			D3DXVECTOR3(m_Pos.x + (ADJUSTMENT * 0.5f), m_Pos.y, m_Pos.z),
			D3DXVECTOR3(m_Size.x - ADJUSTMENT, m_Size.y, m_Size.z), pos, size))
	{
		case C2DCollision::UP:

			// ベクトルが上向きの場合
			if (m_OldPos.y > m_Pos.y)
			{
				// 重力相殺
				m_Move.y = m_Action->NoGravity();
				m_Pos.y = pos.y + size.y;

				// 接地完了
				m_bGround = true;
			}//if.fin
			break;

		case C2DCollision::BOTTOM:

			// ベクトルが下向きの場合
			if (m_OldPos.y < m_Pos.y) m_Move.y = -m_Action->NoGravity();
			break;

		case C2DCollision::LEFT:

			m_Pos.x -= m_Move.x;
			break;

		case C2DCollision::RIGHT:

			m_Pos.x -= m_Move.x;
			break;

	}//switch.fin

}

/*-----------------------------------------------------------------------------
 フィールド衝突判定処理
-----------------------------------------------------------------------------*/
void CPlayer::CollisionField(void)
{
	// シーンオブジェクト数分のループ
	for (int nCnt = 0; nCnt < NUM_SCENE; nCnt++)
	{
		// IDの取得
		CScene *pScene = CScene::GetScene(nCnt);

		// NULLCHECK
		if (pScene == NULL) continue;

		// オブジェクトタイプの識別：フィールド
		if (pScene->GetObjType() == TYPE_FIELD)
		{
			// 指定クラスにポインタキャスト
			CField *pField = (CField*)pScene;

			// データの取得
			D3DXVECTOR3 pos = pField->GetPos(), size = pField->GetSize();

			// 共通衝突判定挙動処理
			CollisionBehavior(pos, size);

		}//if.fin

	}//for.fin

}

/*-----------------------------------------------------------------------------
 ウォール衝突判定処理
-----------------------------------------------------------------------------*/
void CPlayer::CollisionWall(void)
{
	// シーンオブジェクト数分のループ
	for (int nCnt = 0; nCnt < NUM_SCENE; nCnt++)
	{
		// IDの取得
		CScene *pScene = CScene::GetScene(nCnt);

		// NULLCHECK
		if (pScene == NULL) continue;

		// オブジェクトタイプの識別：ウォール
		if (pScene->GetObjType() == TYPE_WALL)
		{
			// 指定クラスにポインタキャスト
			CWall *pWall = (CWall*)pScene;

			// データの取得
			D3DXVECTOR3 pos = pWall->GetPos(), size = pWall->GetSize();

			// 共通衝突判定挙動処理
			CollisionBehavior(pos, size);

		}//if.fin

	}//for.fin

}

/*-----------------------------------------------------------------------------
 アイテム衝突判定処理
-----------------------------------------------------------------------------*/
void CPlayer::CollisionItem(void)
{
	// データの取得用変数
	D3DXVECTOR3 pos, size;

	// シーンオブジェクト数分のループ
	for (int nCnt = 0; nCnt < NUM_SCENE; nCnt++)
	{
		// IDの取得
		CScene *pScene = CScene::GetScene(nCnt);

		// NULLCHECK
		if (pScene == NULL) continue;

		// オブジェクトタイプの識別：アイテム
		if (pScene->GetObjType() == TYPE_ITEM)
		{
			// 指定クラスにポインタキャスト
			CItem *pItem = (CItem*)pScene;

			// サブタイプ別処理
			switch (pItem->GetSubType())
			{
				case SUB_GOAL:
				{
					// 指定クラスにポインタキャスト
					CGoal *pItemSub = (CGoal*)pScene;

					// データの取得
					pos = pItemSub->GetPos(), size = pItemSub->GetSize();

					if (true == C2DCollision::ColRect(m_Pos, m_Size, pos, size))
					{
						// ゴール：ゲームクリアフラグ
						if (m_Action->GetDir() == CAction::DIR_UP)
						{
							m_bGoal = true;
						}//if.fin

					}//if.fin

				}//case.fin
				break;

				case SUB_COLLECT_ITEM:
				{
					// 指定クラスにポインタキャスト
					CCollect *pItemSub = (CCollect*)pScene;

					// データの取得
					pos = pItemSub->GetPos(), size = pItemSub->GetSize();

					if (true == C2DCollision::ColRect(m_Pos, m_Size, pos, size))
					{
						// シーンオブジェクト数分のループ
						for (int nCnt = 0; nCnt < NUM_SCENE; nCnt++)
						{
							// IDの取得
							CScene *pScene = CScene::GetScene(nCnt);

							// NULLCHECK
							if (pScene == NULL) continue;

							// オブジェクトタイプの識別：アイテム
							if (pScene->GetObjType() == TYPE_COLLECTER)
							{
								// 指定クラスにポインタキャスト
								CCollecter *pClass = (CCollecter*)pScene;

								// 加算処理
								pClass->AddCountItem();

								break;
							}//if.fin

						}//for.fin

						// どっかにおいやる
						pItemSub->SetPos(D3DXVECTOR3(-100.0f, 100.0f, 0.0f));

					}//if.fin

				}//case.fin
				break;

				case SUB_NEEDLE:
				{
					// 指定クラスにポインタキャスト
					CNeedle *pItemSub = (CNeedle*)pScene;

					// データの取得
					pos = pItemSub->GetPos(), size = pItemSub->GetSize();

					// ニードルに刺さったらシーン遷移
					if (C2DCollision::UP == C2DCollision::ColRect_Dir(m_Pos, m_Size, pos, size))
					{
						// 重力相殺
						m_Move.y = m_Action->NoGravity();
						m_Pos.y = pos.y + size.y - ADJUSTMENT;

						// ゲームオーバーフラグ
						m_bOver = true;

					}//if.fin

				}//case.fin
				break;

				case SUB_BLOCK:
				{
					// 指定クラスにポインタキャスト
					CBlock *pItemSub = (CBlock*)pScene;

					// データの取得
					pos = pItemSub->GetPos(), size = pItemSub->GetSize();

					// ブロックを動かす
					if (C2DCollision::UP == C2DCollision::ColRect_Dir(
						D3DXVECTOR3(m_Pos.x + (ADJUSTMENT * 0.5f), m_Pos.y, m_Pos.z),
						D3DXVECTOR3(m_Size.x - ADJUSTMENT, m_Size.y, m_Size.z), pos, size))
					{
						// ベクトルが上向きの場合
						if (m_OldPos.y > m_Pos.y)
						{
							// 重力相殺
							m_Move.y = m_Action->NoGravity();
							m_Pos.y = pos.y + size.y;
						}//if.fin

						// 接地完了
						m_bGround = true;
						return;
					}//if.fin

					// 潰されてゲームオーバー
					if (C2DCollision::BOTTOM == C2DCollision::ColRect_Dir(
						D3DXVECTOR3(m_Pos.x + (ADJUSTMENT * 0.5f), m_Pos.y, m_Pos.z),
						D3DXVECTOR3(m_Size.x - ADJUSTMENT, m_Size.y, m_Size.z), pos, size))
					{
						// ベクトルが下向きの場合
						if (m_OldPos.y < m_Pos.y) m_Move.y = -m_Action->NoGravity();
						return;
					}//if.fin

					if (C2DCollision::LEFT == C2DCollision::ColRect_Dir(
						D3DXVECTOR3(m_Pos.x + (ADJUSTMENT * 0.5f), m_Pos.y, m_Pos.z),
						D3DXVECTOR3(m_Size.x - ADJUSTMENT, m_Size.y, m_Size.z), pos, size))
					{
						// ブロック事態がほかのオブジェクトと衝突が無い場合、実行
						if (pItemSub->GetMove() == true)
						{
							m_bItem = true;
							pItemSub->SetPosMove(m_Move.x);
						}//if.fin

						m_Pos.x -= m_Move.x;
						return;

					}//if.fin

					if (C2DCollision::RIGHT == C2DCollision::ColRect_Dir(
						D3DXVECTOR3(m_Pos.x + (ADJUSTMENT * 0.5f), m_Pos.y, m_Pos.z),
						D3DXVECTOR3(m_Size.x - ADJUSTMENT, m_Size.y, m_Size.z), pos, size))
					{
						// ブロック事態がほかのオブジェクトと衝突が無い場合、実行
						if (pItemSub->GetMove() == true)
						{
							m_bItem = true;
							pItemSub->SetPosMove(m_Move.x);
						}//if.fin
					
						m_Pos.x -= m_Move.x;
						return;

					}//if.fin
					
					m_bItem = false;

				}//case.fin
				break;

			}//switch.fin

		}//if.fin

	}//for.fin

}

/*-----------------------------------------------------------------------------
 テクスチャアニメーション処理
-----------------------------------------------------------------------------*/
void CPlayer::ChangeTexture(void)
{
	// 仮想アドレス宣言
	VERTEX_3D *pVtx;

	static int i = 0;

	// 頂点バッファをロックして仮想アドレスの取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_bGoal)
	{
		float scr = (float)(120 - GoalCount) / 120;
		if ((GoalCount % 30) == 0) m_nTexType = GOGOAL1;
		else if ((GoalCount % 15) == 0) m_nTexType = GOGOAL2;

		D3DXVECTOR3 Size = m_Size * scr;

		pVtx[0].pos = D3DXVECTOR3(0.0, Size.y, m_Size.z);
		pVtx[1].pos = D3DXVECTOR3(Size.x, Size.y, m_Size.z);
		pVtx[2].pos = D3DXVECTOR3(0.0, 0.0f, m_Size.z);
		pVtx[3].pos = D3DXVECTOR3(Size.x, 0.0f, m_Size.z);

		GoalCount++;
	}
	else if (m_bItem) 
	{

		

		if (m_Move.x > 0.01f) 
		{
			i++;

			if ((i % 30) == 0) 
			{
				i = 0;

				m_nTexType = 5;
			}
			else if ((i % 15) == 0) 
			{

				m_nTexType = 6;
			}

			// ＵＶ値の設定
			pVtx[0].tex = D3DXVECTOR2(1, 1);
			pVtx[1].tex = D3DXVECTOR2(2, 1);
			pVtx[2].tex = D3DXVECTOR2(1, 2);
			pVtx[3].tex = D3DXVECTOR2(2, 2);

		}
		else if (m_Move.x < -0.01f) 
		{
			i++;

			if ((i % 30) == 0) {
				i = 0;

				m_nTexType = 5;
			}
			else if ((i % 15) == 0) {

				m_nTexType = 6;
			}

			// ＵＶ値の設定
			pVtx[0].tex = D3DXVECTOR2(0, 0);
			pVtx[1].tex = D3DXVECTOR2(1, 0);
			pVtx[2].tex = D3DXVECTOR2(0, 1);
			pVtx[3].tex = D3DXVECTOR2(1, 1);

		}

		

	}
	else if (m_bGround) 
	{
		//CSound::Play(CSound::SE_WALK);

		if (m_Move.x > 0.01f) 
		{
			i++;

			if ((i % 30) == 0) 
			{
				i = 0;

				m_nTexType = 2;
			}
			else if ((i % 15) == 0) 
			{

				m_nTexType = 1;
			}

			// ＵＶ値の設定
			pVtx[0].tex = D3DXVECTOR2(1, 1);
			pVtx[1].tex = D3DXVECTOR2(2, 1);
			pVtx[2].tex = D3DXVECTOR2(1, 2);
			pVtx[3].tex = D3DXVECTOR2(2, 2);

			

		}
		else if (m_Move.x < -0.01f)
		{
			i++;

			if ((i % 30) == 0) 
			{
				i = 0;

				m_nTexType = 2;
			}
			else if ((i % 15) == 0) 
			{

				m_nTexType = 1;
			}

			// ＵＶ値の設定
			pVtx[0].tex = D3DXVECTOR2(0, 0);
			pVtx[1].tex = D3DXVECTOR2(1, 0);
			pVtx[2].tex = D3DXVECTOR2(0, 1);
			pVtx[3].tex = D3DXVECTOR2(1, 1);

		}
		else m_nTexType = 0;

		//CSound::Stop(CSound::SE_WALK);
		
	}
	else 
	{
		// ジャンプ
		m_nTexType = 3;

		if (m_Move.x > 0.01f) 
		{

			// ＵＶ値の設定
			pVtx[0].tex = D3DXVECTOR2(1, 1);
			pVtx[1].tex = D3DXVECTOR2(2, 1);
			pVtx[2].tex = D3DXVECTOR2(1, 2);
			pVtx[3].tex = D3DXVECTOR2(2, 2);
		}
		else if (m_Move.x < -0.01f) 
		{

			// ＵＶ値の設定
			pVtx[0].tex = D3DXVECTOR2(0, 0);
			pVtx[1].tex = D3DXVECTOR2(1, 0);
			pVtx[2].tex = D3DXVECTOR2(0, 1);
			pVtx[3].tex = D3DXVECTOR2(1, 1);
		}
	}

	m_pVtxBuff->Unlock();

}

/*-----------------------------------------------------------------------------
 簡易リザルト処理：今後、こういった処理の仕方はやめましょう
-----------------------------------------------------------------------------*/
void CPlayer::SubResult(void)
{
	// ハーフフェードの生成
	if (!bCreate)
	{
		if(m_bGoal == true)CHalfFade::Create(TEX_FADE, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		if (m_bOver == true)CHalfFade::Create(TEX_FADE, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

		bCreate = true;
	}//if.fin

	// ハーフフェード
	for (int nCnt = 0; nCnt < NUM_SCENE; nCnt++)
	{
		// IDの取得
		CScene *pScene = CScene::GetScene(nCnt);

		// NULLCHECK
		if (pScene == NULL) continue;

		// オブジェクトタイプの識別
		if (pScene->GetObjType() == TYPE_HALFFADE)
		{
			// 指定クラスにポインタキャスト
			CHalfFade *pClass = (CHalfFade*)pScene;

			// フェード実行
			pClass->SetFade(CHalfFade::FADE_OUT);

			if (pClass->GetColor() >= 0.5f)
			{
				// テキストテクスチャ
				if (m_bGoal == true)
				{
					CTextTexture::Create(CLEAR, D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(600.0f, 300.0f, 0.0f));
					CTextTexture::Create(GOOD, D3DXVECTOR3(630.0f, 50.0f, 0.0f), D3DXVECTOR3(300.0f, 500.0f, 0.0f));
				}//if.fin

				if (m_bOver == true)
				{
					CTextTexture::Create(FAILED, D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(600.0f, 300.0f, 0.0f));
					CTextTexture::Create(BAD, D3DXVECTOR3(630.0f, 50.0f, 0.0f), D3DXVECTOR3(300.0f, 500.0f, 0.0f));
				}//if.fin

				CTextTexture::Create(NEXT_STAGE, D3DXVECTOR3(290.0f, 300.0f, 0.0f), D3DXVECTOR3(200.0f, 70.0f, 0.0f));
				CTextTexture::Create(STAGE_SELECT, D3DXVECTOR3(290.0f, 380.0f, 0.0f), D3DXVECTOR3(200.0f, 70.0f, 0.0f));
				CTextTexture::Create(RETRY, D3DXVECTOR3(290.0f, 460.0f, 0.0f), D3DXVECTOR3(200.0f, 70.0f, 0.0f));
				CTextTexture::Create(SELECT, D3DXVECTOR3(240.0f, 300.0f, 0.0f), D3DXVECTOR3(50.0f, 70.0f, 0.0f));

				bRe = true;
			}//if.fin

			break;
		}//if.fin

	}//for.fin

}
