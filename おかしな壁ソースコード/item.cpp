/*=============================================================================

 �A�C�e��[ item.cpp ]

=============================================================================*/
/*=============================================================================
 �C���N���[�h�w�b�_
=============================================================================*/
#include "manager.h"
#include "item.h"
#include "goalFrame.h"

#include "collision.h"
#include "action.h"

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
CItem *CItem::Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nSubType)
{
	// �ϐ��N���X��`
	CItem *pClass;

	// �C���X�^���X�̐����F�^�C�v��
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

	// �Ԋ�
	return pClass;

}

/*-----------------------------------------------------------------------------
 �����������֐�
-----------------------------------------------------------------------------*/
HRESULT CItem::Init(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nSubType)
{
	// �����̑��
	m_Pos      = pos;
	m_Size     = size;
	m_nTexType = nTexType;
	m_SubType  = (SUBTYPE)nSubType;

	// �I�u�W�F�N�g������
	CScene3D::Init();

	// �S�[���͐����
	if (m_SubType == SUB_GOAL)
	{
		// ���z�A�h���X�錾
		VERTEX_3D *pVtx;

		// ���_�o�b�t�@�����b�N���ĉ��z�A�h���X�̎擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		
		pVtx[0].tex = D3DXVECTOR2(0, 0);
		pVtx[1].tex = D3DXVECTOR2(1, 0);
		pVtx[2].tex = D3DXVECTOR2(0, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 1);

		// ���_�o�b�t�@�̃A�����b�N
		m_pVtxBuff->Unlock();

		// �t���[����������
		CGoalFrame::Init(pos);

	}//if.fin

	// ����I��
	return S_OK;

}

/*-----------------------------------------------------------------------------
 �I�������֐�
-----------------------------------------------------------------------------*/
void CItem::Uninit(void)
{
	// �t���[���̏I��
	if (m_SubType == SUB_GOAL) CGoalFrame::Uninit();

	// �I�u�W�F�N�g�̔j��
	CScene3D::Uninit();
}

/*-----------------------------------------------------------------------------
 �`�揈���֐�
-----------------------------------------------------------------------------*/
void CItem::Draw(void)
{
	// �t���[���̕`��
	if (m_SubType == SUB_GOAL) CGoalFrame::Draw();

	// �I�u�W�F�N�g�̕`��
	CScene3D::Draw();

}

/*-----------------------------------------------------------------------------
 �X�V�����֐��F�u���b�N
-----------------------------------------------------------------------------*/
void CBlock::Update(void)
{
	// �ړ��O�̍��W�̕ۊ�
	m_OldPos = m_Pos;

	// �d��(���̂��R�O�{)
	m_Pos.y += CAction::Gravity() * 30.0f;

	// �V�[���I�u�W�F�N�g�����̃��[�v
	for (int nCnt = 0; nCnt < NUM_SCENE; nCnt++)
	{
		// ID�̎擾
		CScene *pScene = CScene::GetScene(nCnt);

		// NULLCHECK
		if (pScene == NULL) continue;

		// THISCHECK
		if (pScene == this) continue;

		// TYPECHECK
		CItem *pItem = (CItem*)pScene;
		if (pItem->GetSubType() == SUB_COLLECT_ITEM || pItem->GetSubType() == SUB_ARROW) continue;

		// �I�u�W�F�N�g�^�C�v�̎���
		if ((pScene->GetObjType() != TYPE_PLAYER) && (pScene->GetObjType() != TYPE_SWITCH))
		{
			// �f�[�^�̎擾
			D3DXVECTOR3 pos = pScene->GetPos(), size = pScene->GetSize();

			// ���ʏՓ˔��苓������
			CollisionObjVertical(pos, size);

			// �Ԃ�l�F�������Ă��邩���Ȃ���
			if ((m_bMove = CollisionObjSide(pos, size)) == false) break;

		}//if.fin

	}//for.fin

}

/*-----------------------------------------------------------------------------
 �c�I�u�W�F�N�g�Փ˔��菈��
-----------------------------------------------------------------------------*/
void CBlock::CollisionObjVertical(D3DXVECTOR3 targetPos, D3DXVECTOR3 targetSize)
{
	if (C2DCollision::UP == C2DCollision::ColRect_Dir(m_Pos, m_Size, targetPos, targetSize))
	{
		// �d�͑��E
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
 ���I�u�W�F�N�g�Փ˔��菈��
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
