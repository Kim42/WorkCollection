/*=============================================================================

 �o�b�N�O���E���h[ bg.cpp ]

=============================================================================*/
/*=============================================================================
�C���N���[�h�w�b�_
=============================================================================*/
#include "manager.h"
#include "renderer.h"
#include "texture.h"

#include "bg.h"

/*=============================================================================
 ���_�t�H�[�}�b�g��`
=============================================================================*/
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL | D3DFVF_TEX1)

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

/*=============================================================================
 �ÓI�����o�̓��I�m�ۓ��I�m��
=============================================================================*/
LPDIRECT3DVERTEXBUFFER9 CBg::m_pVtxBuff;
D3DXVECTOR3 CBg::m_Pos;
D3DXVECTOR3 CBg::m_Size;
int CBg::m_nTexType;

/*-----------------------------------------------------------------------------
 �����������֐�
-----------------------------------------------------------------------------*/
HRESULT CBg::Init(int nTexType)
{
	// �����̑��
	m_Pos = D3DXVECTOR3(-5.0f, -5.0f, 1.0f);
	m_Size = D3DXVECTOR3(80.0f, 30.0f, 0.0f);
	m_nTexType = nTexType;

	m_pVtxBuff = NULL;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,					// �쐬���������_�o�b�t�@�̃T�C�Y(�\����)*���_��
		D3DUSAGE_WRITEONLY,						// �������݂̂ݎ��s�i�ő������������݌�ق����炩���j
		FVF_VERTEX_3D,							// ���_�t�H�[�}�b�g�̐ݒ�i�O�ł����v�j
		D3DPOOL_MANAGED,						// �������Ǘ����ǂ����邩 �� ���C��
		&m_pVtxBuff,							// ���_�o�b�t�@�̊Ǘ��̃C���^�[�t�F�[�X�|�C���^
		NULL)))									// �g��Ȃ�
	{
		MessageBox(NULL, "3D���_�o�b�t�@��\n�����Ɏ��s���܂���", "�G���[", MB_OK);
		return E_FAIL;
	}// if.fin

	// ���z�A�h���X�錾
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���ĉ��z�A�h���X�̎擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�(�K���R�c��Ԃ̌��_(0,0)�ɐݒ肳���)
	pVtx[0].pos = D3DXVECTOR3(0.0f, m_Size.y, m_Size.z);
	pVtx[1].pos = D3DXVECTOR3(m_Size.x, m_Size.y, m_Size.z);
	pVtx[2].pos = D3DXVECTOR3(0.0f, m_Size.y - m_Size.y, m_Size.z);
	pVtx[3].pos = D3DXVECTOR3(m_Size.x, m_Size.y - m_Size.y, m_Size.z);

	// �@���̐ݒ�(�Q�c�Q�[���d�l�Ȃ̂Ŏ�O����)
	pVtx[0].nor =
	pVtx[1].nor =
	pVtx[2].nor =
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// ���_�J���\�̐ݒ�
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(3, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(3, 1);

	 // ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
	
	// ����I��
	return S_OK;

}

/*-----------------------------------------------------------------------------
 �I�������֐�
-----------------------------------------------------------------------------*/
void CBg::Uninit(void)
{
	// ���_�o�b�t�@�C���^�[�t�F�[�X�̉��
	SAFE_RELEASE(m_pVtxBuff);
}

/*-----------------------------------------------------------------------------
 �X�V�����֐�
-----------------------------------------------------------------------------*/
void CBg::Update(void)
{
	static float i = 0.0f;

	i += 0.001f;

	// ���z�A�h���X�錾
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���ĉ��z�A�h���X�̎擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0 + i, 0);
	pVtx[1].tex = D3DXVECTOR2(3 + i, 0);
	pVtx[2].tex = D3DXVECTOR2(0 + i, 1);
	pVtx[3].tex = D3DXVECTOR2(3 + i, 1);

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

}

/*-----------------------------------------------------------------------------
 �`�揈���֐�
-----------------------------------------------------------------------------*/
void CBg::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// ���[���h�}�g���N�X
	D3DXMATRIXA16 mtxWorld;

	// �P�ʍs��ɏ�����(�������Ȃ��悤�ɂ���)
	D3DXMatrixIdentity(&mtxWorld);

	// ���s�ړ�����
	D3DXMatrixTranslation(&mtxWorld, m_Pos.x, m_Pos.y, m_Pos.z);

	// ���[���h���W�ϊ����s��
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_���X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���ݒ�
	pDevice->SetTexture(0, CTexture::GetAdr(m_nTexType));

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

