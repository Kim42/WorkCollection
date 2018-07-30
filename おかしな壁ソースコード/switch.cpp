/*=============================================================================

 �X�C�b�`[ swtch.cpp ]

=============================================================================*/
/*=============================================================================
 �C���N���[�h�w�b�_
=============================================================================*/
#include "manager.h"

#include "collision.h"
#include "switch.h"
#include "field.h"

/*=============================================================================
 �}�N����`
=============================================================================*/
#define TEX_X 0.333f
#define ADJUSTMENT 0.2f			// ���̏Փ˔͈͒���

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
CSwitch::CSwitch()
{
	SetObjType(TYPE_SWITCH);
}

/*-----------------------------------------------------------------------------
�f�X�g���N�^
-----------------------------------------------------------------------------*/
CSwitch::~CSwitch()
{

}

/*-----------------------------------------------------------------------------
�����֐�
-----------------------------------------------------------------------------*/
CSwitch *CSwitch::Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nFieldID)
{
	// �ϐ��N���X��`
	CSwitch *pClass;

	// �C���X�^���X�̐���
	pClass = new CSwitch;

	// ������
	pClass->Init(nTexType, pos, size, nFieldID);

	// �Ԋ�
	return pClass;

}

/*-----------------------------------------------------------------------------
�����������֐�
-----------------------------------------------------------------------------*/
HRESULT CSwitch::Init(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nFieldID)
{
	// �����̑��
	m_Pos      = pos;
	m_Size     = size;
	m_nTexType = nTexType;
	m_nFieldID = nFieldID;
	m_fTexX    = 0.0f;
	m_nTimer   = 0;
	m_bSwitch  = false;

	// �I�u�W�F�N�g������
	CScene3D::Init();

	// ���z�A�h���X�錾
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���ĉ��z�A�h���X�̎擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �t�u�l�̐ݒ�
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

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	// ����I��
	return S_OK;

}

/*-----------------------------------------------------------------------------
�I�������֐�
-----------------------------------------------------------------------------*/
void CSwitch::Uninit(void)
{
	// �I�u�W�F�N�g�I��
	CScene3D::Uninit();

}

/*-----------------------------------------------------------------------------
�X�V�����֐�
-----------------------------------------------------------------------------*/
void CSwitch::Update(void)
{
	// �A�C�e���Փ˔���
	CollisionObj();

	// �X�C�b�`�������ꂽ��
	if (m_bSwitch == true && m_nTimer < 10)
	{
		// ID�̎擾
		CScene *pScene = CScene::GetScene(m_nFieldID);

		// �e�N�X�`���A�j���[�V����
		Animtion();

		// ���� // �ǂ����ɂ������
		if (m_nTimer >= 10) pScene->SetPos(D3DXVECTOR3(-100.0f, -100.0f, 0.0f));

	}//if.fin

	// �I�u�W�F�N�g�X�V
	CScene3D::Update();

}

/*-----------------------------------------------------------------------------
�`�揈���֐�
-----------------------------------------------------------------------------*/
void CSwitch::Draw(void)
{
	// �I�u�W�F�N�g�`��
	CScene3D::Draw();

}

/*-----------------------------------------------------------------------------
 �Փ˔��菈���֐�
-----------------------------------------------------------------------------*/
void CSwitch::CollisionObj(void)
{
	// �v���C���[���G�ꂽ���ƁA�A�C�e���u���b�N���G�ꂽ���ŕ�����I�I�I

	D3DXVECTOR3 pos, size;

	// �V�[���I�u�W�F�N�g�����̃��[�v
	for (int nCnt = 0; nCnt < NUM_SCENE; nCnt++)
	{
		// ID�̎擾
		CScene *pScene = CScene::GetScene(nCnt);

		// NULLCHECK
		if (pScene == NULL) continue;

		// �f�[�^�̎擾
		pos = pScene->GetPos(), size = pScene->GetSize();

		// �Ή�����t�B�[���h�I�u�W�F�N�g���폜����
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
 �e�N�X�`���A�j���[�V���������֐�
-----------------------------------------------------------------------------*/
void CSwitch::Animtion(void)
{
	m_nTimer++;

	if (m_nTimer == 8) m_fTexX += TEX_X;
	if (m_nTimer == 10) m_fTexX += TEX_X;

	// ���z�A�h���X�錾
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���ĉ��z�A�h���X�̎擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �t�u�l�̐ݒ�
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

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

}

