/*=============================================================================

 �v���C���[[ player.cpp ]

=============================================================================*/
/*=============================================================================
�C���N���[�h�w�b�_
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
 �}�N����`
=============================================================================*/
#define ADJUSTMENT 0.2f			// ���̏Փ˔͈͒���

bool g_PausePause = false;

/*=============================================================================
 �R�c���_���\����
=============================================================================*/
struct VERTEX_3D
{
	D3DXVECTOR3 pos;		// ���W�ʒu
	D3DXVECTOR3 nor;		// �@��
	D3DCOLOR    col;		// �F
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
};

/*-----------------------------------------------------------------------------
 �R���X�g���N�^
-----------------------------------------------------------------------------*/
CPlayer::CPlayer()
{
	SetObjType(TYPE_PLAYER);

	// �A�N�V�����̃C���X�^���X����
	m_Action = new CAction();

}

/*-----------------------------------------------------------------------------
 �f�X�g���N�^
-----------------------------------------------------------------------------*/
CPlayer::~CPlayer()
{
	// �A�N�V�����j��
	delete m_Action;

}

/*-----------------------------------------------------------------------------
 �����֐�
-----------------------------------------------------------------------------*/
CPlayer *CPlayer :: Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �ϐ��N���X��`
	CPlayer *pClass;

	// �C���X�^���X�̐���
	pClass = new CPlayer;

	// ������
	pClass-> Init(nTexType, pos, size);

	// �Ԋ�
	return pClass;

}

/*-----------------------------------------------------------------------------
 �����������֐�
-----------------------------------------------------------------------------*/
HRESULT CPlayer :: Init(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �����̑��
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

	// �ڒn����m�F
	if (pos.y > 0.0f)
		m_bGround = false;
	else
		m_bGround = true;

	// �I�u�W�F�N�g������
	CScene3D :: Init();

	g_PausePause = false;

	// ����I��
	return S_OK;

}

/*-----------------------------------------------------------------------------
 �I�������֐�
-----------------------------------------------------------------------------*/
void CPlayer :: Uninit(void)
{
	// �I�u�W�F�N�g�I��
	CScene3D:: Uninit();

}

/*-----------------------------------------------------------------------------
 �X�V�����֐�
-----------------------------------------------------------------------------*/
void CPlayer :: Update(void)
{
	// �Q�[���p�b�h�g�p�錾
	CInputGamePad *pGamePad = CManager::GetInputGamePad();

	if(pGamePad->GetPadButtonTrigger(CInputGamePad::GB_STRAT))
	{
		g_PausePause ^= true;
	}
		if(!g_PausePause)
		{
	// �N���A���t�F�C�������ꍇ
	if (m_bGoal != true && m_bOver != true)
	{
		// �ړ��O�̍��W�̕ۊ�
		m_OldPos = m_Pos;

		// �ړ����ʂ��擾
		m_Move.x = m_Action->Move(m_Move.x, 0.9f, &m_bGround, &m_bItem);
		m_Move.y = m_Action->Jump(m_Move.y, 0.09f, &m_bGround);

		// ������^����
		m_Action->Friction(&m_Move.x);

		// �|�W�V�����ɔ��f
		m_Pos += m_Move;

		// �A�C�e���Փ˔���
		CollisionItem();

		// �E�H�[���Փ˔���
		CollisionWall();

		// �X�L������
		m_Action->Skill(m_Pos, m_Size);

		// �t�B�[���h�Փ˔���
		CollisionField();

		// �d��
		m_Move.y += CAction::Gravity();
	}
	else
	{
		if (bRe == true) return;

		SubResult();

		// �V�[���I�u�W�F�N�g�����̃��[�v
		for (int nCnt = 0; nCnt < NUM_SCENE; nCnt++)
		{
			// ID�̎擾
			CScene *pScene = CScene::GetScene(nCnt);

			// NULLCHECK
			if (pScene == NULL) continue;

			// �I�u�W�F�N�g�^�C�v�̎��ʁF�t�B�[���h
			if (pScene->GetObjType() == TYPE_TIMER)
			{
				// �w��N���X�Ƀ|�C���^�L���X�g
				CTimer *pTimer = (CTimer*)pScene;

				// �f�[�^�̎擾
				pTimer->SetState(false);

				break;
			}//if.fin

		}//for.fin

	}//if.fin

	// �e�N�X�`���A�j���[�V����
	ChangeTexture();

	// �V�[���I�u�W�F�N�g�����̃��[�v
	for (int nCnt = 0; nCnt < NUM_SCENE; nCnt++)
	{
		// ID�̎擾
		CScene *pScene = CScene::GetScene(nCnt);

		// NULLCHECK
		if (pScene == NULL) continue;

		// �I�u�W�F�N�g�^�C�v�̎��ʁF�t�B�[���h
		if (pScene->GetObjType() == TYPE_TIMER)
		{
			// �w��N���X�Ƀ|�C���^�L���X�g
			CTimer *pTimer = (CTimer*)pScene;

			// �f�[�^�̎擾
			int nTime = pTimer->GetTime();

			if (nTime <= 0) m_bOver = true;

			break;
		}//if.fin

	}//for.fin

	// �I�u�W�F�N�g�X�V
	CScene3D:: Update();
		}

}

/*-----------------------------------------------------------------------------
 �`�揈���֐�
-----------------------------------------------------------------------------*/
void CPlayer :: Draw(void)
{
	// �I�u�W�F�N�g�`��
	CScene3D::Draw();

}

/*-----------------------------------------------------------------------------
 ���ʏՓ˔��苓������
-----------------------------------------------------------------------------*/
void CPlayer::CollisionBehavior(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	switch (C2DCollision::ColRect_Dir(
			D3DXVECTOR3(m_Pos.x + (ADJUSTMENT * 0.5f), m_Pos.y, m_Pos.z),
			D3DXVECTOR3(m_Size.x - ADJUSTMENT, m_Size.y, m_Size.z), pos, size))
	{
		case C2DCollision::UP:

			// �x�N�g����������̏ꍇ
			if (m_OldPos.y > m_Pos.y)
			{
				// �d�͑��E
				m_Move.y = m_Action->NoGravity();
				m_Pos.y = pos.y + size.y;

				// �ڒn����
				m_bGround = true;
			}//if.fin
			break;

		case C2DCollision::BOTTOM:

			// �x�N�g�����������̏ꍇ
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
 �t�B�[���h�Փ˔��菈��
-----------------------------------------------------------------------------*/
void CPlayer::CollisionField(void)
{
	// �V�[���I�u�W�F�N�g�����̃��[�v
	for (int nCnt = 0; nCnt < NUM_SCENE; nCnt++)
	{
		// ID�̎擾
		CScene *pScene = CScene::GetScene(nCnt);

		// NULLCHECK
		if (pScene == NULL) continue;

		// �I�u�W�F�N�g�^�C�v�̎��ʁF�t�B�[���h
		if (pScene->GetObjType() == TYPE_FIELD)
		{
			// �w��N���X�Ƀ|�C���^�L���X�g
			CField *pField = (CField*)pScene;

			// �f�[�^�̎擾
			D3DXVECTOR3 pos = pField->GetPos(), size = pField->GetSize();

			// ���ʏՓ˔��苓������
			CollisionBehavior(pos, size);

		}//if.fin

	}//for.fin

}

/*-----------------------------------------------------------------------------
 �E�H�[���Փ˔��菈��
-----------------------------------------------------------------------------*/
void CPlayer::CollisionWall(void)
{
	// �V�[���I�u�W�F�N�g�����̃��[�v
	for (int nCnt = 0; nCnt < NUM_SCENE; nCnt++)
	{
		// ID�̎擾
		CScene *pScene = CScene::GetScene(nCnt);

		// NULLCHECK
		if (pScene == NULL) continue;

		// �I�u�W�F�N�g�^�C�v�̎��ʁF�E�H�[��
		if (pScene->GetObjType() == TYPE_WALL)
		{
			// �w��N���X�Ƀ|�C���^�L���X�g
			CWall *pWall = (CWall*)pScene;

			// �f�[�^�̎擾
			D3DXVECTOR3 pos = pWall->GetPos(), size = pWall->GetSize();

			// ���ʏՓ˔��苓������
			CollisionBehavior(pos, size);

		}//if.fin

	}//for.fin

}

/*-----------------------------------------------------------------------------
 �A�C�e���Փ˔��菈��
-----------------------------------------------------------------------------*/
void CPlayer::CollisionItem(void)
{
	// �f�[�^�̎擾�p�ϐ�
	D3DXVECTOR3 pos, size;

	// �V�[���I�u�W�F�N�g�����̃��[�v
	for (int nCnt = 0; nCnt < NUM_SCENE; nCnt++)
	{
		// ID�̎擾
		CScene *pScene = CScene::GetScene(nCnt);

		// NULLCHECK
		if (pScene == NULL) continue;

		// �I�u�W�F�N�g�^�C�v�̎��ʁF�A�C�e��
		if (pScene->GetObjType() == TYPE_ITEM)
		{
			// �w��N���X�Ƀ|�C���^�L���X�g
			CItem *pItem = (CItem*)pScene;

			// �T�u�^�C�v�ʏ���
			switch (pItem->GetSubType())
			{
				case SUB_GOAL:
				{
					// �w��N���X�Ƀ|�C���^�L���X�g
					CGoal *pItemSub = (CGoal*)pScene;

					// �f�[�^�̎擾
					pos = pItemSub->GetPos(), size = pItemSub->GetSize();

					if (true == C2DCollision::ColRect(m_Pos, m_Size, pos, size))
					{
						// �S�[���F�Q�[���N���A�t���O
						if (m_Action->GetDir() == CAction::DIR_UP)
						{
							m_bGoal = true;
						}//if.fin

					}//if.fin

				}//case.fin
				break;

				case SUB_COLLECT_ITEM:
				{
					// �w��N���X�Ƀ|�C���^�L���X�g
					CCollect *pItemSub = (CCollect*)pScene;

					// �f�[�^�̎擾
					pos = pItemSub->GetPos(), size = pItemSub->GetSize();

					if (true == C2DCollision::ColRect(m_Pos, m_Size, pos, size))
					{
						// �V�[���I�u�W�F�N�g�����̃��[�v
						for (int nCnt = 0; nCnt < NUM_SCENE; nCnt++)
						{
							// ID�̎擾
							CScene *pScene = CScene::GetScene(nCnt);

							// NULLCHECK
							if (pScene == NULL) continue;

							// �I�u�W�F�N�g�^�C�v�̎��ʁF�A�C�e��
							if (pScene->GetObjType() == TYPE_COLLECTER)
							{
								// �w��N���X�Ƀ|�C���^�L���X�g
								CCollecter *pClass = (CCollecter*)pScene;

								// ���Z����
								pClass->AddCountItem();

								break;
							}//if.fin

						}//for.fin

						// �ǂ����ɂ������
						pItemSub->SetPos(D3DXVECTOR3(-100.0f, 100.0f, 0.0f));

					}//if.fin

				}//case.fin
				break;

				case SUB_NEEDLE:
				{
					// �w��N���X�Ƀ|�C���^�L���X�g
					CNeedle *pItemSub = (CNeedle*)pScene;

					// �f�[�^�̎擾
					pos = pItemSub->GetPos(), size = pItemSub->GetSize();

					// �j�[�h���Ɏh��������V�[���J��
					if (C2DCollision::UP == C2DCollision::ColRect_Dir(m_Pos, m_Size, pos, size))
					{
						// �d�͑��E
						m_Move.y = m_Action->NoGravity();
						m_Pos.y = pos.y + size.y - ADJUSTMENT;

						// �Q�[���I�[�o�[�t���O
						m_bOver = true;

					}//if.fin

				}//case.fin
				break;

				case SUB_BLOCK:
				{
					// �w��N���X�Ƀ|�C���^�L���X�g
					CBlock *pItemSub = (CBlock*)pScene;

					// �f�[�^�̎擾
					pos = pItemSub->GetPos(), size = pItemSub->GetSize();

					// �u���b�N�𓮂���
					if (C2DCollision::UP == C2DCollision::ColRect_Dir(
						D3DXVECTOR3(m_Pos.x + (ADJUSTMENT * 0.5f), m_Pos.y, m_Pos.z),
						D3DXVECTOR3(m_Size.x - ADJUSTMENT, m_Size.y, m_Size.z), pos, size))
					{
						// �x�N�g����������̏ꍇ
						if (m_OldPos.y > m_Pos.y)
						{
							// �d�͑��E
							m_Move.y = m_Action->NoGravity();
							m_Pos.y = pos.y + size.y;
						}//if.fin

						// �ڒn����
						m_bGround = true;
						return;
					}//if.fin

					// �ׂ���ăQ�[���I�[�o�[
					if (C2DCollision::BOTTOM == C2DCollision::ColRect_Dir(
						D3DXVECTOR3(m_Pos.x + (ADJUSTMENT * 0.5f), m_Pos.y, m_Pos.z),
						D3DXVECTOR3(m_Size.x - ADJUSTMENT, m_Size.y, m_Size.z), pos, size))
					{
						// �x�N�g�����������̏ꍇ
						if (m_OldPos.y < m_Pos.y) m_Move.y = -m_Action->NoGravity();
						return;
					}//if.fin

					if (C2DCollision::LEFT == C2DCollision::ColRect_Dir(
						D3DXVECTOR3(m_Pos.x + (ADJUSTMENT * 0.5f), m_Pos.y, m_Pos.z),
						D3DXVECTOR3(m_Size.x - ADJUSTMENT, m_Size.y, m_Size.z), pos, size))
					{
						// �u���b�N���Ԃ��ق��̃I�u�W�F�N�g�ƏՓ˂������ꍇ�A���s
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
						// �u���b�N���Ԃ��ق��̃I�u�W�F�N�g�ƏՓ˂������ꍇ�A���s
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
 �e�N�X�`���A�j���[�V��������
-----------------------------------------------------------------------------*/
void CPlayer::ChangeTexture(void)
{
	// ���z�A�h���X�錾
	VERTEX_3D *pVtx;

	static int i = 0;

	// ���_�o�b�t�@�����b�N���ĉ��z�A�h���X�̎擾
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

			// �t�u�l�̐ݒ�
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

			// �t�u�l�̐ݒ�
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

			// �t�u�l�̐ݒ�
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

			// �t�u�l�̐ݒ�
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
		// �W�����v
		m_nTexType = 3;

		if (m_Move.x > 0.01f) 
		{

			// �t�u�l�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(1, 1);
			pVtx[1].tex = D3DXVECTOR2(2, 1);
			pVtx[2].tex = D3DXVECTOR2(1, 2);
			pVtx[3].tex = D3DXVECTOR2(2, 2);
		}
		else if (m_Move.x < -0.01f) 
		{

			// �t�u�l�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0, 0);
			pVtx[1].tex = D3DXVECTOR2(1, 0);
			pVtx[2].tex = D3DXVECTOR2(0, 1);
			pVtx[3].tex = D3DXVECTOR2(1, 1);
		}
	}

	m_pVtxBuff->Unlock();

}

/*-----------------------------------------------------------------------------
 �ȈՃ��U���g�����F����A���������������̎d���͂�߂܂��傤
-----------------------------------------------------------------------------*/
void CPlayer::SubResult(void)
{
	// �n�[�t�t�F�[�h�̐���
	if (!bCreate)
	{
		if(m_bGoal == true)CHalfFade::Create(TEX_FADE, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		if (m_bOver == true)CHalfFade::Create(TEX_FADE, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

		bCreate = true;
	}//if.fin

	// �n�[�t�t�F�[�h
	for (int nCnt = 0; nCnt < NUM_SCENE; nCnt++)
	{
		// ID�̎擾
		CScene *pScene = CScene::GetScene(nCnt);

		// NULLCHECK
		if (pScene == NULL) continue;

		// �I�u�W�F�N�g�^�C�v�̎���
		if (pScene->GetObjType() == TYPE_HALFFADE)
		{
			// �w��N���X�Ƀ|�C���^�L���X�g
			CHalfFade *pClass = (CHalfFade*)pScene;

			// �t�F�[�h���s
			pClass->SetFade(CHalfFade::FADE_OUT);

			if (pClass->GetColor() >= 0.5f)
			{
				// �e�L�X�g�e�N�X�`��
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
