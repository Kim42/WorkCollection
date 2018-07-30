/*=============================================================================

アクション[ action.cpp ]

=============================================================================*/
/*=============================================================================
インクルードヘッダ
=============================================================================*/
#include "action.h"
#include "wall.h"
#include "sound.h"

/*=============================================================================
マクロ定義
=============================================================================*/
#define JUMP_COUNT   (8)
#define SKILL_OFFSET (2.0f)

/*-----------------------------------------------------------------------------
横移動処理
-----------------------------------------------------------------------------*/
float CAction::Move(float moveX, float fSpeed, bool *bGround, bool *bItem)
{
	// ゲームパッド使用宣言
	CInputGamePad *pGamePad = CManager::GetInputGamePad();

	// 横移動処理
	if (((int)pGamePad->GetPadAnalogStick(CInputGamePad::GSL).x <= MIN_AXIS_PAD + 10000) || 
		(CInputGamePad::POV_LEFT == pGamePad->GetPadPOVPress()) )
	{
		m_Dir = DIR_LEFT;			// 左向き
		moveX -= M_S(fSpeed);		// マイナス方向
	}//if.fin

	if (((int)pGamePad->GetPadAnalogStick(CInputGamePad::GSL).x >= MAX_AXIS_PAD - 10000) || 
		(CInputGamePad::POV_RIGHT == pGamePad->GetPadPOVPress()))
	{
		m_Dir = DIR_RIGHT;			// 右向き
		moveX += M_S(fSpeed);		// プラス方向
	}//if.fin

	if (((int)pGamePad->GetPadAnalogStick(CInputGamePad::GSL).y <= MIN_AXIS_PAD + 10000) || 
		(CInputGamePad::POV_UP == pGamePad->GetPadPOVPress()))
	{
		m_Dir = DIR_UP;
	}

	if (((int)pGamePad->GetPadAnalogStick(CInputGamePad::GSL).y >= MAX_AXIS_PAD - 10000) || 
		(CInputGamePad::POV_DOWN == pGamePad->GetPadPOVPress()))
	{
		m_Dir = DIR_DOWN;
	}

	// ブロック動かし中の制限処理
	if (true == *bItem)
	{
		if (((int)pGamePad->GetPadAnalogStick(CInputGamePad::GSL).x <= MIN_AXIS_PAD + 10000) || 
		(CInputGamePad::POV_LEFT == pGamePad->GetPadPOVPress()))
		{
			m_Dir = DIR_LEFT;					// 左向き
			moveX += M_S(fSpeed * 0.75f);		// マイナス方向
		}//if.fin

		if (((int)pGamePad->GetPadAnalogStick(CInputGamePad::GSL).x >= MAX_AXIS_PAD - 10000) || 
		(CInputGamePad::POV_RIGHT == pGamePad->GetPadPOVPress()))
		{
			m_Dir = DIR_RIGHT;					// 右向き
			moveX -= M_S(fSpeed * 0.75f);		// プラス方向
		}//if.fin

	}//if.fin

	 // ジャンプ中の制限処理
	if (false == *bGround)
	{
		if (((int)pGamePad->GetPadAnalogStick(CInputGamePad::GSL).x <= MIN_AXIS_PAD + 10000) || 
		(CInputGamePad::POV_LEFT == pGamePad->GetPadPOVPress()))
		{
			m_Dir = DIR_LEFT;					// 左向き
			moveX += M_S(fSpeed * 0.25f);		// マイナス方向
		}//if.fin

		if (((int)pGamePad->GetPadAnalogStick(CInputGamePad::GSL).x >= MAX_AXIS_PAD - 10000) || 
		(CInputGamePad::POV_RIGHT == pGamePad->GetPadPOVPress()))
		{
			m_Dir = DIR_RIGHT;					// 右向き
			moveX -= M_S(fSpeed * 0.25f);		// プラス方向
		}//if.fin

	}//if.fin

	 // 移動量を返還
	return moveX;

}

/*-----------------------------------------------------------------------------
ジャンプ処理
-----------------------------------------------------------------------------*/
float CAction::Jump(float moveY, float fJumpingFouce, bool *bGround)
{
	// ゲームパッド使用宣言
	CInputGamePad *pGamePad = CManager::GetInputGamePad();

	// 長押し有効ジャンプ
	static int m_nJumpCnt = JUMP_COUNT;
	static bool bJump = false;

	// ジャンプ処理
	if ((true == *bGround) && (pGamePad->GetPadButtonTrigger(CInputGamePad::GB_A)))
	{
		m_Dir = DIR_UP;

		// 目的高さ ＝ fJumpingFouceまでの初速度
		moveY += -GRAVITY * fJumpingFouce;

		// 呼び出し側のフラグ操作
		*bGround = false;

		// ジャンプフラグ
		bJump = true;

	}//if.fin

	// ボタンを押している間：真
	if ((bJump == true) && (m_nJumpCnt > 0) && (pGamePad->GetPadButton(CInputGamePad::GB_A)))
	{
		m_nJumpCnt--;
		moveY += -(GRAVITY * fJumpingFouce / 16.0f);
		CManager::GetSound()->Play(CSound::SE_JUMP);
	}
	else
	{
		m_nJumpCnt = JUMP_COUNT;
		bJump = false;
	}//if.fin

	// 移動量を返還
	return moveY;

}

/*-----------------------------------------------------------------------------
スキル発動
-----------------------------------------------------------------------------*/
void CAction::Skill(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	// ゲームパッド使用宣言
	CInputGamePad *pGamePad = CManager::GetInputGamePad();

	if (pGamePad->GetPadButtonTrigger(CInputGamePad::GB_X))
	{
		m_Skill = true;
		CWall* Work = NULL;

		for (int CntScene = 0; CntScene < NUM_SCENE; CntScene++)
		{
			CScene* Scene = CScene::GetScene(CntScene);

			if (Scene != NULL)
			{
				OBJTYPE ObjType;
				ObjType = Scene->GetObjType();

				if (ObjType == TYPE_WALL)
				{
					CWall* Wall;
					Wall = dynamic_cast <CWall*> (Scene);
					D3DXVECTOR3 WPos = Wall->GetPos();
					D3DXVECTOR3 WSize = Wall->GetSize();

					switch (m_Dir)
					{
					case DIR_RIGHT:
						if ((WPos.x > Pos.x) && (WPos.x - SKILL_OFFSET < Pos.x) &&
							(WPos.y - 0.1f <= Pos.y) && ((WPos.y + WSize.y) > Pos.y))
						{
							if (Work != NULL)
							{
								if (WPos.x < Work->GetPos().x)
								{
									Work = Wall;
								}
							}
							else
							{
								Work = Wall;
							}
						}
						break;

					case DIR_LEFT:
						if ((WPos.x < Pos.x) && (WPos.x + WSize.x + SKILL_OFFSET > Pos.x) &&
							(WPos.y - 0.1f <= Pos.y) && ((WPos.y + WSize.y) > Pos.y))
						{
							if (Work != NULL)
							{
								if (WPos.x > Work->GetPos().x)
								{
									Work = Wall;
								}
							}
							else
							{
								Work = Wall;
							}
						}
						break;

					case DIR_UP:
						if (WPos.y > Pos.y && (WPos.y - SKILL_OFFSET < Pos.y))
						{
							if (Work != NULL)
							{
								if (WPos.y < Work->GetPos().y)
								{
									Work = Wall;
								}
							}
							else
							{
								Work = Wall;
							}
						}
						break;

					case DIR_DOWN:
						if (WPos.y < Pos.y && (WPos.y + SKILL_OFFSET > Pos.y))
						{
							if (Work != NULL)
							{
								if (WPos.y > Work->GetPos().y)
								{
									Work = Wall;
								}
							}
							else
							{
								Work = Wall;
							}
						}
						break;

					default:
						break;
					}

					if (Work != NULL && m_Skill)
					{
						Work->Skill();
						m_Skill = false;
					}
				}
			}
		}
	}

}

