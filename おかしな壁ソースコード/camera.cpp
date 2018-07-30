/*=============================================================================

 �J��������[ camera.cpp ]

=============================================================================*/
/*=============================================================================
 �C���N���[�h�w�b�_
=============================================================================*/
#include "manager.h"
#include "renderer.h"
#include "camera.h"

#include "player.h"
#include "action.h"

/*=============================================================================
 �����o�ϐ��̓��I�錾
=============================================================================*/
D3DXVECTOR3 CCamera :: m_At  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CCamera :: m_Eye = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CCamera :: m_Up  = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

D3DXMATRIX  CCamera :: m_mtxProjection;
D3DXMATRIX  CCamera :: m_mtxView;

float       CCamera ::m_fZoom = 60.0f;

/*-----------------------------------------------------------------------------
 �����������֐�
-----------------------------------------------------------------------------*/
HRESULT CCamera :: Init(D3DXVECTOR3 At, D3DXVECTOR3 Eye)
{
	// �l�̏�����
	m_At = At;
	m_Eye = Eye;

	// ����I��
	return S_OK;

}

/*-----------------------------------------------------------------------------
 �I�������֐�
-----------------------------------------------------------------------------*/
void CCamera :: Uninit(void)
{
	// �g�p���������o�ϐ��̃[��������
	m_At  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Eye = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Up  = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

}

/*-----------------------------------------------------------------------------
 �X�V�����֐�
-----------------------------------------------------------------------------*/
void CCamera :: Update(void)
{
	// �V�[���I�u�W�F�N�g�����̃��[�v
	for (int nCnt = 0; nCnt < NUM_SCENE; nCnt++)
	{
		// ID�̎擾
		CScene *pScene = CScene::GetScene(nCnt);

		// NULLCHECK
		if (pScene == NULL) continue;

		// �I�u�W�F�N�g�^�C�v�̎���
		if (pScene->GetObjType() == TYPE_PLAYER)
		{
			CPlayer *pClass = (CPlayer*)pScene;

			// �J�����|�W�V����
			m_Eye.z = -13.0f;

			 // �v���C���[�|�W�V�����w���P�O�ȏ�A�U�O�ȉ��̏ꍇ
			if ((pClass->GetPos().x > 10.0f) && (pClass->GetPos().x < 60.0f))
			{
				m_At.x = pClass->GetPos().x;
				m_Eye.x = pClass->GetPos().x;
			}
			else if (pClass->GetPos().x < 10.0f)
			{
				m_At.x = 10.0f;
				m_Eye.x = 10.0f;
			}
			else if (pClass->GetPos().x > 60.0f)
			{
				m_At.x = 60.0f;
				m_Eye.x = 60.0f;
			}//if.fin

			// �v���C���[�|�W�V�����x���T�D�T�ȏ�̏ꍇ
			if (pClass->GetPos().y > 5.5f)
			{
				m_At.y = pClass->GetPos().y;
				m_Eye.y = pClass->GetPos().y;
			}
			else
			{
				m_At.y = 5.5f;
				m_Eye.y = 5.5f;
			}//if.fin

		}//if.fin

	}//for.fin

}

/*-----------------------------------------------------------------------------
 �ݒu�����֐�
-----------------------------------------------------------------------------*/
void CCamera :: Set(void)
{
	// ���_�t�H�[�}�b�g�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �}�g���N�X�̐��K��
	D3DXMatrixIdentity(&m_mtxView);
	
	// �r���[�|�[�g�}�g���N�X�̐ݒ�
	D3DXMatrixLookAtLH(&m_mtxView, &m_Eye, &m_At, &m_Up);

	// �r���[�|�[�g�}�g���N�X�̍��W�ϊ����s��
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
	
	// �}�g���N�X�̐��K��
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V����(���e)�}�g���N�X�̐ݒu
	D3DXMatrixPerspectiveFovLH(
		&m_mtxProjection,							// �v���W�F�N�V�����}�g���N�X�A�h���X
		D3DXToRadian(m_fZoom),						// ��p(����p�x)
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,		// �A�X�y�N�g��F�U�O�x
		0.1f,										// NEAR �ߏ�(�K���O���傫��)
		100.0f);									// FAR  ����

	// �v���W�F�N�V�����}�g���N�X�̍��W�ϊ����s��
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

}

