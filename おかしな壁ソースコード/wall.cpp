/*=============================================================================

�E�H�[��[ wall.cpp ]

=============================================================================*/
/*=============================================================================
�C���N���[�h�w�b�_
=============================================================================*/
#include "manager.h"

#include "wall.h"
#include "player.h"
#include "item.h"

/*=============================================================================
�}�N����`
=============================================================================*/
#define COMP_OBJ		(2)
#define SKILL_OFFSET	(2.0f)

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
�����֐�
-----------------------------------------------------------------------------*/
CWall *CWall::Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nSkill)
{
	// �ϐ��N���X��`
	CWall *pClass;

	// �C���X�^���X�̐����F�X�L����
	switch (nSkill)
	{
	case SKILL_SWAP:

		pClass = new CSwap;
		pClass->Init(nTexType, pos, size, nSkill);
		break;

	case SKILL_COPY:

		pClass = new CCopy;
		pClass->Init(nTexType, pos, size, nSkill);
		break;

	case SKILL_SYNC:

		pClass = new CSync;
		pClass->Init(nTexType, pos, size, nSkill);
		break;

	}//switch.fin

	 // �Ԋ�
	return pClass;

}

/*-----------------------------------------------------------------------------
�����������֐�
-----------------------------------------------------------------------------*/
HRESULT CWall::Init(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nSkill)
{
	// �����̑��
	m_Pos = pos;
	m_Size = size;
	m_nTexType = nTexType;
	m_SkillType = (SKILL)nSkill;

	// �I�u�W�F�N�g������
	CScene3D::Init();

	if (m_Size.y >= 1.0f)
	{
		// ���z�A�h���X�錾
		VERTEX_3D *pVtx;

		// ���_�o�b�t�@�����b�N���ĉ��z�A�h���X�̎擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		if(m_Size.x / m_Size.y > 1)
		{
			pVtx[0].tex = D3DXVECTOR2(1, 0);
			pVtx[1].tex = D3DXVECTOR2(1, m_Size.x);
			pVtx[2].tex = D3DXVECTOR2(0, 0);
			pVtx[3].tex = D3DXVECTOR2(0, m_Size.x);
		}
		else
		{
			pVtx[0].tex = D3DXVECTOR2(0, 0);
			pVtx[1].tex = D3DXVECTOR2(1, 0);
			pVtx[2].tex = D3DXVECTOR2(0, m_Size.y);
			pVtx[3].tex = D3DXVECTOR2(1, m_Size.y);
		}
			
		// ���_�o�b�t�@�̃A�����b�N
		m_pVtxBuff->Unlock();

	}//if.fin

	// ����I��
	return S_OK;

}

/*-----------------------------------------------------------------------------
�I�������֐�
-----------------------------------------------------------------------------*/
void CWall::Uninit(void)
{
	CScene3D::Uninit();
}

/*-----------------------------------------------------------------------------
�X�V�����֐�
-----------------------------------------------------------------------------*/
void CWall::Update(void)
{
	CScene3D::Update();
}

/*-----------------------------------------------------------------------------
�`�揈���֐�
-----------------------------------------------------------------------------*/
void CWall::Draw(void)
{
	CScene3D::Draw();
}

//=============================================================================
// ����ւ�����
//=============================================================================
bool CSwap::Swap(void)
{
	CScene3D* SwapObj[COMP_OBJ] = {};
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Size;
	bool Updown = (m_Size.x / m_Size.y) > 1 ? true : false;

	for (int CntScene = 0; CntScene < NUM_SCENE; CntScene++)
	{
		CScene* Scene = CScene::GetScene(CntScene);

		if (Scene != NULL)
		{
			OBJTYPE ObjType;
			ObjType = Scene->GetObjType();

			if (ObjType == TYPE_ITEM)
			{
				CItem* Block;
				Block = dynamic_cast <CItem*> (Scene);

				if (Block->GetSubType() == SUB_BLOCK)
				{
					Pos = Block->GetPos();
					Size = Block->GetSize();

					if (Updown)
					{
						if ((Pos.x >= m_Pos.x) && (Pos.x + Size.x <= (m_Pos.x + m_Size.x)) && (Pos.y + Size.y >= m_Pos.y - SKILL_OFFSET) && ((Pos.y + Size.y) <= (m_Pos.y + m_Size.y)))
						{
							if (SwapObj[0] != NULL)
							{
								if (SwapObj[0]->GetPos().y <= Pos.y)
								{
									SwapObj[0] = Block;
								}
							}
							else
							{
								SwapObj[0] = Block;
							}
						}

						if ((Pos.x >= m_Pos.x) && (Pos.x + Size.x <= (m_Pos.x + m_Size.x)) && (Pos.y <= m_Pos.y + m_Size.y + SKILL_OFFSET) && ((Pos.y + Size.y) >= (m_Pos.y + m_Size.y)))
						{
							if (SwapObj[1] != NULL)
							{
								if (SwapObj[1]->GetPos().y >= Pos.y)
								{
									SwapObj[1] = Block;
								}
							}
							else
							{
								SwapObj[1] = Block;
							}
						}
					}
					else
					{
						if ((Pos.x <= m_Pos.x) && (Pos.x >= (m_Pos.x - SKILL_OFFSET)) && (Pos.y >= m_Pos.y - 0.1f) && (Pos.y <= (m_Pos.y + m_Size.y)))
						{
							if (SwapObj[0] != NULL)
							{
								if (SwapObj[0]->GetPos().x <= Pos.x)
								{
									SwapObj[0] = Block;
								}
							}
							else
							{
								SwapObj[0] = Block;
							}
						}

						if ((Pos.x >= m_Pos.x) && (Pos.x <= (m_Pos.x + m_Size.x + SKILL_OFFSET)) && (Pos.y >= m_Pos.y - 0.1f) && (Pos.y <= (m_Pos.y + m_Size.y)))
						{
							if (SwapObj[1] != NULL)
							{
								if (SwapObj[1]->GetPos().x >= Pos.x)
								{
									SwapObj[1] = Block;
								}
							}
							else
							{
								SwapObj[1] = Block;
							}
						}
					}
				}
			}
			else if (ObjType == TYPE_PLAYER)
			{
				CPlayer* Player;
				Player = dynamic_cast <CPlayer*> (Scene);

				Pos = Player->GetPos();
				Size = D3DXVECTOR3(Player->GetSize().x, Player->GetSize().y, 0.0f);

				if (Updown)
				{
					if ((Pos.x >= m_Pos.x) && (Pos.x + Size.x <= (m_Pos.x + m_Size.x)) && (Pos.y + Size.y >= m_Pos.y - SKILL_OFFSET) && ((Pos.y + Size.y) <= (m_Pos.y + m_Size.y)))
					{
						if (SwapObj[0] != NULL)
						{
							if (SwapObj[0]->GetPos().x <= Pos.x)
							{
								SwapObj[0] = Player;
							}
						}
						else
						{
							SwapObj[0] = Player;
						}
					}

					if ((Pos.x >= m_Pos.x) && (Pos.x + Size.x <= (m_Pos.x + m_Size.x)) && (Pos.y <= m_Pos.y + m_Size.y + SKILL_OFFSET) && ((Pos.y + Size.y) >= (m_Pos.y + m_Size.y)))
					{
						if (SwapObj[1] != NULL)
						{
							if (SwapObj[1]->GetPos().x >= Pos.x)
							{
								SwapObj[1] = Player;
							}
						}
						else
						{
							SwapObj[1] = Player;
						}
					}
				}
				else
				{
					if ((Pos.x <= (m_Pos.x - m_Size.x * 0.5f)) && (Pos.x >= (m_Pos.x - SKILL_OFFSET)) && (m_Pos.y - 0.1f <= Pos.y) && ((m_Pos.y + m_Size.y) >= Pos.y))
					{
						if (SwapObj[0] != NULL)
						{
							if (SwapObj[0]->GetPos().x <= Pos.x)
							{
								SwapObj[0] = Player;
							}
						}
						else
						{
							SwapObj[0] = Player;
						}
					}

					if ((Pos.x >= (m_Pos.x + m_Size.x * 0.5f)) && (Pos.x <= (m_Pos.x + SKILL_OFFSET)) && (m_Pos.y - 0.1f <= Pos.y) && ((m_Pos.y + m_Size.y) >= Pos.y))
					{
						if (SwapObj[1] != NULL)
						{
							if (SwapObj[1]->GetPos().x >= Pos.x)
							{
								SwapObj[1] = Player;
							}
						}
						else
						{
							SwapObj[1] = Player;
						}
					}
				}
			}
		}
	}

	if ((SwapObj[0] != NULL) && (SwapObj[1] != NULL))
	{
		Pos = SwapObj[0]->GetPos();
		SwapObj[0]->SetPos(SwapObj[1]->GetPos());
		SwapObj[1]->SetPos(Pos);

		return true;

	}

	return false;
}

//=============================================================================
// �R�s�[����
//=============================================================================
bool CCopy::Copy(void)
{
	CItem* CopyBlock[COMP_OBJ] = {};
	D3DXVECTOR3 Pos;

	for (int CntScene = 0; CntScene < NUM_SCENE; CntScene++)
	{
		CScene* Scene = CScene::GetScene(CntScene);

		if (Scene != NULL)
		{
			OBJTYPE ObjType;
			ObjType = Scene->GetObjType();

			if (ObjType == TYPE_ITEM)
			{
				CItem* Block;
				Block = dynamic_cast <CItem*> (Scene);

				if (Block->GetSubType() == SUB_BLOCK)
				{
					Pos = Block->GetPos();

					if (Pos.x <= (m_Pos.x - m_Size.x * 0.5f) && Pos.x >= (m_Pos.x - m_Size.y * 0.5f) && ((m_Pos.y - m_Size.y * 0.5f) <= Pos.y) && ((m_Pos.y + m_Size.y * 0.5f) >= Pos.y))
					{
						if (CopyBlock[0] != NULL)
						{
							if (CopyBlock[0]->GetPos().x <= Pos.x)
							{
								CopyBlock[0] = Block;
							}
						}
						else
						{
							CopyBlock[0] = Block;
						}
					}

					if (Pos.x >= (m_Pos.x + m_Size.x * 0.5f) && Pos.x <= (m_Pos.x + m_Size.y * 0.5f) && ((m_Pos.y - m_Size.y * 0.5f) <= Pos.y) && ((m_Pos.y + m_Size.y * 0.5f) >= Pos.y))
					{
						if (CopyBlock[1] != NULL)
						{
							if (CopyBlock[1]->GetPos().x >= Pos.x)
							{
								CopyBlock[1] = Block;
							}
						}
						else
						{
							CopyBlock[1] = Block;
						}
					}
				}
			}
		}
	}

	if ((CopyBlock[0] != NULL) && (CopyBlock[1] != NULL))
	{
		for (int CntScene = 0; CntScene < NUM_SCENE; CntScene++)
		{
			CScene* Scene = CScene::GetScene(CntScene);

			if (Scene != NULL)
			{
				OBJTYPE ObjType;
				ObjType = Scene->GetObjType();

				if (ObjType == TYPE_PLAYER)
				{
					CPlayer* Player;
					Player = dynamic_cast <CPlayer*> (Scene);
					D3DXVECTOR3 pos = Player->GetPos();

					if (pos.x < m_Pos.x)
					{
						//CopyBlock[1]->SetType(CopyBlock[0]->GetType());
					}
					else
					{
						//CopyBlock[0]->SetType(CopyBlock[1]->GetType());
					}
				}
			}
		}

		return true;
	}

	return false;
}

//=============================================================================
// ��������
//=============================================================================
bool CSync::Sync(void)
{
	CItem* Block = NULL;
	CPlayer* Player = NULL;
	D3DXVECTOR3 Pos;
	bool PlayerLeft = false;

	for (int CntScene = 0; CntScene < NUM_SCENE; CntScene++)
	{
		CScene* Scene = CScene::GetScene(CntScene);

		if (Scene != NULL)
		{
			OBJTYPE ObjType;
			ObjType = Scene->GetObjType();

			if (ObjType == TYPE_PLAYER)
			{
				CPlayer* Work;
				Work = dynamic_cast <CPlayer*> (Scene);

				Pos = Work->GetPos();

				if ((Pos.x <= m_Pos.x) && (Pos.x >= m_Pos.x - SKILL_OFFSET) && ((m_Pos.y - m_Size.y * 0.5f) <= Pos.y) && ((m_Pos.y + m_Size.y * 0.5f) >= Pos.y))
				{
					Player = Work;
					PlayerLeft = true;
					break;
				}
				else if ((Pos.x >= (m_Pos.x + m_Size.x)) && (Pos.x <= m_Pos.x + m_Size.x + SKILL_OFFSET) && ((m_Pos.y - m_Size.y * 0.5f) <= Pos.y) && ((m_Pos.y + m_Size.y * 0.5f) >= Pos.y))
				{
					Player = Work;
					break;
				}
				else
				{
					Player = NULL;
				}
			}
		}
	}
	for (int CntScene = 0; CntScene < NUM_SCENE; CntScene++)
	{
		CScene* Scene = CScene::GetScene(CntScene);

		if (Scene != NULL)
		{
			OBJTYPE ObjType;
			ObjType = Scene->GetObjType();

			if (ObjType == TYPE_ITEM)
			{
				CItem* Work;
				Work = dynamic_cast <CItem*> (Scene);

				if (Work->GetSubType() == SUB_BLOCK)
				{
					Pos = Work->GetPos();

					if (PlayerLeft)
					{
						if (Pos.x >= (m_Pos.x + m_Size.x * 0.5f) && ((m_Pos.y - 0.1f) <= Pos.y) && ((m_Pos.y + m_Size.y) >= Pos.y))
						{
							if (Block != NULL)
							{
								if (Block->GetPos().x >= Pos.x)
								{
									Block = Work;
								}
							}
							else
							{
								Block = Work;
							}
						}
					}
					else
					{
						if ((Pos.x <= m_Pos.x) && ((m_Pos.y - m_Size.y * 0.5f) <= Pos.y) && ((m_Pos.y + m_Size.y * 0.5f) >= Pos.y))
						{
							if (Block != NULL)
							{
								if (Block->GetPos().x <= Pos.x)
								{
									Block = Work;
								}
							}
							else
							{
								Block = Work;
							}
						}
					}
				}
			}
		}
	}

	if ((Block != NULL) && (Player != NULL))
	{
		Block->SetPos(D3DXVECTOR3(Block->GetPos().x, Player->GetPos().y, Block->GetPos().z));

		return true;
	}
	else
	{
		m_SyncFrag = false;
	}

	return false;

}

//=============================================================================
// �X�V����(Sync)
//=============================================================================
void CSync::Update(void)
{
	if (m_SyncFrag) Sync();

	CScene3D::Update();
}

//=============================================================================
// �X�L������(Sync)
//=============================================================================
bool CSync::Skill(void)
{
	m_SyncFrag ^= true;

	return m_SyncFrag;
}

