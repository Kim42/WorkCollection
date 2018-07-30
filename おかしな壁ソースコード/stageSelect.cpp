/*=============================================================================

�X�e�[�W�Z���N�g[ stageSelect.cpp ]

=============================================================================*/
/*=============================================================================
�C���N���[�h�w�b�_
=============================================================================*/
#include "manager.h"
#include "stageSelect.h"
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
CStageSelect *CStageSelect::Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �ϐ��N���X��`
	CStageSelect *pClass;

	// �C���X�^���X�̐���
	pClass = new CStageSelect;

	// ������
	pClass->Init(nTexType, pos, size);

	// �Ԋ�
	return pClass;

}

/*-----------------------------------------------------------------------------
�����������֐�
-----------------------------------------------------------------------------*/
HRESULT CStageSelect::Init(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �����̑��
	m_Pos = pos;
	m_Size = size;
	m_nTexType = nTexType;

	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nCounterState = 0;
	m_fAlpha = 1.0f;
	m_nAlphaPlus = 0;

	// �I�u�W�F�N�g������
	CScene3D::Init();

	// �|�C���^�ϐ�
	VERTEX_3D* pVtx;

	// �o�b�t�@�����b�N�����z�A�h���X���擾����
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);

	// �o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	// ����I��
	return S_OK;

}

/*-----------------------------------------------------------------------------
�X�V�����֐�
-----------------------------------------------------------------------------*/
void CStageSelect::Update(void)
{
	// �҂��҂�
	if (m_nTexType == STAGESELECT000)
	{
		m_color.a = m_fAlpha;

		if (m_nAlphaPlus == 0)
		{
			if ((m_fAlpha = max((m_fAlpha - 0.020f), 0.0f)) <= 0.0f)
			{
				m_nAlphaPlus ^= 1;
			}
		}
		else
		{
			if ((m_fAlpha = min((m_fAlpha + 0.020f), 1.0f)) >= 1.0f)
			{
				m_nAlphaPlus ^= 1;
			}
		}

		// �|�C���^�ϐ�
		VERTEX_3D* pVtx;

		// �o�b�t�@�����b�N�����z�A�h���X���擾����
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].col = D3DXCOLOR(m_color.r, m_color.g, m_color.b, m_color.a);
		pVtx[1].col = D3DXCOLOR(m_color.r, m_color.g, m_color.b, m_color.a);
		pVtx[2].col = D3DXCOLOR(m_color.r, m_color.g, m_color.b, m_color.a);
		pVtx[3].col = D3DXCOLOR(m_color.r, m_color.g, m_color.b, m_color.a);

		// �o�b�t�@���A�����b�N
		m_pVtxBuff->Unlock();

	}//if.fin

}
