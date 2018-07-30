/*=============================================================================

 �i���o�[�`�揈��[ number.cpp ]

=============================================================================*/
/*=============================================================================
 �C���N���[�h�w�b�_
=============================================================================*/
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "number.h"

/*=============================================================================
 �}�N����`
=============================================================================*/
#define NUM_VERTEX  (4)		// ���_��
#define NUM_POLYGON (2)		// �v���~�e�B�u��
#define TEX_U       (0.1f)

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

//=============================================================================
// ��������
//=============================================================================
CNumber *CNumber :: Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumber)
{
	// �g�p�錾
	CNumber *pNumber;

	// �i���o�[�̐���
	pNumber = new CNumber;

	// ������
	pNumber -> Init(nTexType, pos, size, nNumber );

	// �N���X�|�C���^��Ԃ�
	return pNumber;

}

/*-----------------------------------------------------------------------------
 ����������
-----------------------------------------------------------------------------*/
HRESULT CNumber :: Init( int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumber )
{
	// �l�̑��
	m_Pos = pos;
	m_Size = size;
	m_nTexType = nTexType;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer:: GetDevice();

	// ���_�o�b�t�@�̐���
	if( FAILED ( pDevice -> CreateVertexBuffer(
		sizeof(VERTEX_2D) * NUM_VERTEX ,		// �쐬���钸�_�o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,						// �������݂̂ݎ��s
		FVF_VERTEX_2D,							// ���_�t�H�[�}�b�g�̐ݒ�
		D3DPOOL_MANAGED,						// �������Ǘ� �� ���C��
		&m_pVtxBuff,							// ���_�o�[�e�b�N�X�A�h���X
		NULL ) ) )
	{
		MessageBox(NULL, "���_�o�b�t�@�̐����Ɏ��s���܂���", "�G���[", MB_OK);
		return E_FAIL;
	}//if.fin

	// ���_����ݒ�
	VERTEX_2D *pVtx = NULL;

	// ���_�o�b�t�@�̃��b�N
	m_pVtxBuff -> Lock( 0, 0, ( void** )&pVtx, 0 );

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3( m_Pos.x         , m_Pos.y         , 0.0f );
	pVtx[1].pos = D3DXVECTOR3( m_Pos.x + size.x, m_Pos.y         , 0.0f );
	pVtx[2].pos = D3DXVECTOR3( m_Pos.x         , m_Pos.y + size.y, 0.0f );
	pVtx[3].pos = D3DXVECTOR3( m_Pos.x + size.x, m_Pos.y + size.y, 0.0f );

	// rhw�̐ݒ�(�K��1.0f)
	pVtx[0].rhw = 
	pVtx[1].rhw = 
	pVtx[2].rhw = 
	pVtx[3].rhw = 1.0f;

	// ���_�J���\�̐ݒ�(0�`255�̐����l)
	pVtx[0].col = 
	pVtx[1].col = 
	pVtx[2].col = 
	pVtx[3].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );

	// �t�u�l�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2( 0.1f * nNumber,         0 );
	pVtx[1].tex = D3DXVECTOR2( 0.1f * nNumber + TEX_U, 0 );
	pVtx[2].tex = D3DXVECTOR2( 0.1f * nNumber,         1 );
	pVtx[3].tex = D3DXVECTOR2( 0.1f * nNumber + TEX_U, 1 );

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff -> Unlock();

	// ����I��
	return S_OK;

}

/*-----------------------------------------------------------------------------
 �I���Ǘ�����
-----------------------------------------------------------------------------*/
void CNumber :: Uninit( void )
{
	// ���_�o�b�t�@�̔j��
	SAFE_RELEASE(m_pVtxBuff);

	// ���g�̔j��
	delete this;

}

/*-----------------------------------------------------------------------------
 �`��Ǘ�����
-----------------------------------------------------------------------------*/
void CNumber :: Draw( void )
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice -> SetStreamSource( 0, m_pVtxBuff, 0, sizeof(VERTEX_2D) );

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_2D );

	// �e�N�X�`���̐ݒ�
	pDevice -> SetTexture( 0, CTexture::GetAdr(m_nTexType));

	// �|���S���̕`��
	pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON );

}

/*-----------------------------------------------------------------------------
 �����̒l�ݒu
-----------------------------------------------------------------------------*/
void CNumber :: SetNumber( int nNumber )
{
	// ���_����ݒ�
	VERTEX_2D *pVtx = NULL;

	// ���_�o�b�t�@�̃��b�N
	m_pVtxBuff -> Lock( 0, 0, ( void** )&pVtx, 0 );

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2( 0.1f * nNumber,         0 );
	pVtx[1].tex = D3DXVECTOR2( 0.1f * nNumber + TEX_U, 0 );
	pVtx[2].tex = D3DXVECTOR2( 0.1f * nNumber,         1 );
	pVtx[3].tex = D3DXVECTOR2( 0.1f * nNumber + TEX_U, 1 );

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff -> Unlock();

}

