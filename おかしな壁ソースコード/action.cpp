/*=============================================================================

�A�N�V����[ action.cpp ]

=============================================================================*/
/*=============================================================================
�C���N���[�h�w�b�_
=============================================================================*/
#include "action.h"
#include "wall.h"
#include "sound.h"

/*=============================================================================
�}�N����`
=============================================================================*/
#define JUMP_COUNT   (8)
#define SKILL_OFFSET (2.0f)

/*-----------------------------------------------------------------------------
���ړ�����
-----------------------------------------------------------------------------*/
float CAction::Move(float moveX, float fSpeed, bool *bGround, bool *bItem)
{
	// �Q�[���p�b�h�g�p�錾
	CInputGamePad *pGamePad = CManager::GetInputGamePad();

	// ���ړ�����
	if (((int)pGamePad->GetPadAnalogStick(CInputGamePad::GSL).x <= MIN_AXIS_PAD + 10000) || 
		(CInputGamePad::POV_LEFT == pGamePad->GetPadPOVPress()) )
	{
		m_Dir = DIR_LEFT;			// ������
		moveX -= M_S(fSpeed);		// �}�C�i�X����
	}//if.fin

	if (((int)pGamePad->GetPadAnalogStick(CInputGamePad::GSL).x >= MAX_AXIS_PAD - 10000) || 
		(CInputGamePad::POV_RIGHT == pGamePad->GetPadPOVPress()))
	{
		m_Dir = DIR_RIGHT;			// �E����
		moveX += M_S(fSpeed);		// �v���X����
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

	// �u���b�N���������̐�������
	if (true == *bItem)
	{
		if (((int)pGamePad->GetPadAnalogStick(CInputGamePad::GSL).x <= MIN_AXIS_PAD + 10000) || 
		(CInputGamePad::POV_LEFT == pGamePad->GetPadPOVPress()))
		{
			m_Dir = DIR_LEFT;					// ������
			moveX += M_S(fSpeed * 0.75f);		// �}�C�i�X����
		}//if.fin

		if (((int)pGamePad->GetPadAnalogStick(CInputGamePad::GSL).x >= MAX_AXIS_PAD - 10000) || 
		(CInputGamePad::POV_RIGHT == pGamePad->GetPadPOVPress()))
		{
			m_Dir = DIR_RIGHT;					// �E����
			moveX -= M_S(fSpeed * 0.75f);		// �v���X����
		}//if.fin

	}//if.fin

	 // �W�����v���̐�������
	if (false == *bGround)
	{
		if (((int)pGamePad->GetPadAnalogStick(CInputGamePad::GSL).x <= MIN_AXIS_PAD + 10000) || 
		(CInputGamePad::POV_LEFT == pGamePad->GetPadPOVPress()))
		{
			m_Dir = DIR_LEFT;					// ������
			moveX += M_S(fSpeed * 0.25f);		// �}�C�i�X����
		}//if.fin

		if (((int)pGamePad->GetPadAnalogStick(CInputGamePad::GSL).x >= MAX_AXIS_PAD - 10000) || 
		(CInputGamePad::POV_RIGHT == pGamePad->GetPadPOVPress()))
		{
			m_Dir = DIR_RIGHT;					// �E����
			moveX -= M_S(fSpeed * 0.25f);		// �v���X����
		}//if.fin

	}//if.fin

	 // �ړ��ʂ�Ԋ�
	return moveX;

}

/*-----------------------------------------------------------------------------
�W�����v����
-----------------------------------------------------------------------------*/
float CAction::Jump(float moveY, float fJumpingFouce, bool *bGround)
{
	// �Q�[���p�b�h�g�p�錾
	CInputGamePad *pGamePad = CManager::GetInputGamePad();

	// �������L���W�����v
	static int m_nJumpCnt = JUMP_COUNT;
	static bool bJump = false;

	// �W�����v����
	if ((true == *bGround) && (pGamePad->GetPadButtonTrigger(CInputGamePad::GB_A)))
	{
		m_Dir = DIR_UP;

		// �ړI���� �� fJumpingFouce�܂ł̏����x
		moveY += -GRAVITY * fJumpingFouce;

		// �Ăяo�����̃t���O����
		*bGround = false;

		// �W�����v�t���O
		bJump = true;

	}//if.fin

	// �{�^���������Ă���ԁF�^
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

	// �ړ��ʂ�Ԋ�
	return moveY;

}

/*-----------------------------------------------------------------------------
�X�L������
-----------------------------------------------------------------------------*/
void CAction::Skill(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	// �Q�[���p�b�h�g�p�錾
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

