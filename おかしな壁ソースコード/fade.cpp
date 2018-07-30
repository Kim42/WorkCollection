/*=============================================================================

 �t�F�[�h�`�揈��[ fade.cpp ]

=============================================================================*/
/*=============================================================================
�C���N���[�h�w�b�_
=============================================================================*/
#include "manager.h"
#include "renderer.h"
#include "texture.h"

#include "fade.h"

/*=============================================================================
 �}�N����`
=============================================================================*/
#define FADE_RATE_FULL (0.02f)

/*=============================================================================
 �Q�c���_�t�H�[�}�b�g
=============================================================================*/
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

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
CFade *CFade::Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// �ϐ��N���X��`
	CFade *pClass;

	// �C���X�^���X�̐���5
	pClass = new CFade;

	// ������
	pClass->Init(nTexType, pos, size, color);

	// �Ԋ�
	return pClass;

}

/*-----------------------------------------------------------------------------
 �����������֐�
-----------------------------------------------------------------------------*/
HRESULT CFade::Init(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	m_Pos = pos;
	m_Size = size;
	m_nTexType = nTexType;

	//m_Fade = FADE_NONE;
	m_Color = color;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// ���_�o�b�t�@�̐���
	if(FAILED(pDevice -> CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,					// �쐬���������_�o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,						// �������݂̂ݎ��s�i�ő������������݌�ق����炩���j
		FVF_VERTEX_2D,							// ���_�t�H�[�}�b�g�̐ݒ�i�O�ł����v�j
		D3DPOOL_MANAGED,						// �������Ǘ����ǂ����邩 �� ���C��
		&m_pVtxBuff,							// ���_�o�[�e�b�N�X�A�h���X
		NULL)))
	{
		MessageBox(NULL, "2D���_�o�b�t�@��\n�����Ɏ��s���܂���", "�G���[", MB_OK);
		return E_FAIL;
	}//if.fin

	// ���_����ݒ�
	VERTEX_2D *pVtx = NULL;

	// ���_�o�b�t�@�̃��b�N
	m_pVtxBuff -> Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x,            m_Pos.y,            0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Pos.x + m_Size.x, m_Pos.y,            0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x,            m_Pos.y + m_Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Pos.x + m_Size.x, m_Pos.y + m_Size.y, 0.0f);

	// rhw�̐ݒ�(�K��1.0f)
	pVtx[0].rhw = 
	pVtx[1].rhw = 
	pVtx[2].rhw = 
	pVtx[3].rhw = 1.0f;

	// ���_�J���\�̐ݒ�
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = m_Color;

	// �t�u�l�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);
	
	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff -> Unlock();

	// ����I��
	return S_OK;

}

/*-----------------------------------------------------------------------------
 �I�������֐�
-----------------------------------------------------------------------------*/
void CFade::Uninit(void)
{
	// �o�[�e�b�N�X�o�b�t�@�̉��
	SAFE_RELEASE(m_pVtxBuff);

}

/*-----------------------------------------------------------------------------
 �X�V�����֐�
-----------------------------------------------------------------------------*/
void CFade::Update(void)
{
	//���������Ȃ��ŏI��
	if (m_Fade == FADE_NONE) return;
	
	//�t�F�[�h�C��
	if (m_Fade == FADE_IN)
	{
		m_Color.a -= FADE_RATE_FULL;

		//�I������
		if (m_Color.a <= 0.0f)
		{
			m_Color.a = 0.0f;
			m_Fade = FADE_NONE;
		}//if.fin

	}//if.fin

	//�t�F�[�h�A�E�g
	if (m_Fade == FADE_OUT)
	{
		m_Color.a += FADE_RATE_FULL;

		//�I������
		if (m_Color.a >= 1.0f)
		{
			m_Color.a = 1.0f;
			m_Fade = FADE_IN;
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
void CFade::Draw(void)
{
	//�`�悹���ɏI��
	if (m_Fade == FADE_NONE) return;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice -> SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice -> SetTexture(0, CTexture::GetAdr(m_nTexType));

	// �|���S���̕`��
	pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}


