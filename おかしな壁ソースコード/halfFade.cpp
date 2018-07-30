/*=============================================================================

 �n�[�t�t�F�[�h�`�揈��[ halfFade.cpp ]

=============================================================================*/
/*=============================================================================
�C���N���[�h�w�b�_
=============================================================================*/
#include "manager.h"

#include "halfFade.h"

/*=============================================================================
 �}�N����`
=============================================================================*/
#define FADE_RATE (0.01f)

/*=============================================================================
 2D���_���\����
=============================================================================*/
struct VERTEX_2D
{
	D3DXVECTOR3 pos;		// ���W�ʒu
	float       rhw;		// �ϊ��ςݍ��W
	D3DCOLOR    col;		// �F
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
};

/*-----------------------------------------------------------------------------
 ���������֐�
-----------------------------------------------------------------------------*/
CHalfFade *CHalfFade::Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// �ϐ��N���X��`
	CHalfFade *pClass;

	// �C���X�^���X�̐���5
	pClass = new CHalfFade;

	// ������
	pClass->Init(nTexType, pos, size, color);

	// �Ԋ�
	return pClass;

}

/*-----------------------------------------------------------------------------
 �����������֐�
-----------------------------------------------------------------------------*/
HRESULT CHalfFade::Init(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	m_Pos = pos;
	m_Size = size;
	m_nTexType = nTexType;

	m_Fade = FADE_NONE;
	m_Color = color;

	// �I�u�W�F�N�g�̏�����
	CScene2D::Init();

	// ���_����ݒ�
	VERTEX_2D *pVtx = NULL;

	// ���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �J���[�̔��f
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = m_Color;

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	// ����I��
	return S_OK;

}

/*-----------------------------------------------------------------------------
 �I�������֐�
-----------------------------------------------------------------------------*/
void CHalfFade::Uninit(void)
{
	// �I�u�W�F�N�g�I��
	CScene2D::Uninit();

}

/*-----------------------------------------------------------------------------
 �X�V�����֐�
-----------------------------------------------------------------------------*/
void CHalfFade::Update(void)
{
	//���������Ȃ��ŏI��
	if (m_Fade == FADE_NONE) return;
	
	//�t�F�[�h�C��
	if (m_Fade == FADE_IN)
	{
		m_Color.a -= FADE_RATE;

		//�I������
		if (m_Color.a <= 0.0f)
		{
			m_Color.a = 0.0f;
			//m_Fade = FADE_NONE;
		}//if.fin

	}//if.fin

	//�t�F�[�h�A�E�g
	if (m_Fade == FADE_OUT)
	{
		m_Color.a += FADE_RATE;

		//�I������
		if (m_Color.a >= 0.5f)
		{
			m_Color.a = 0.5f;
			//m_Fade = FADE_IN;
		}//if.fin

	}//if.fin

	// ���_����ݒ�
	VERTEX_2D *pVtx = NULL;

	// ���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �J���[�̔��f
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = m_Color;

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

}

/*-----------------------------------------------------------------------------
 �`�揈���֐�
-----------------------------------------------------------------------------*/
void CHalfFade::Draw(void)
{
	//�`�悹���ɏI��
	if (m_Fade == FADE_NONE) return;

	// �I�u�W�F�N�g�̕`��
	CScene2D::Draw();

}


