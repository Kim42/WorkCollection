/*=============================================================================

 �����_�[����[ renderer.cpp ]

=============================================================================*/
/*=============================================================================
 �C���N���[�h�w�b�_
=============================================================================*/
#include "manager.h"
#include "renderer.h"

/*=============================================================================
 �ÓI�����o�ϐ��̓��I�������m��
=============================================================================*/
LPDIRECT3D9       CRenderer :: m_pD3D       = NULL;
LPDIRECT3DDEVICE9 CRenderer :: m_pD3DDevice = NULL;
LPD3DXFONT        CRenderer :: m_pFont      = NULL;

/*-----------------------------------------------------------------------------
 �����������֐�
-----------------------------------------------------------------------------*/
HRESULT CRenderer :: Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �ϐ��錾
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE        d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	// �Ԃ�
	if (m_pD3D == NULL)
	{
		MessageBox(NULL, "�f�o�C�X�̓ǂݍ��ݎ��s���܂���", "�G���[", MB_OK);
		return E_FAIL;
	}//if.fin

	 // ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D -> GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		MessageBox(NULL, "���s���܂���", "�G���[", MB_OK);
		return E_FAIL;
	}//if.fin

	 // �f�o�C�X�̃v���[���g�p�����[�^�[�̐ݒ�i�f�o�C�X����邽�߂̐ݒ�����邽�߂̐ݒ�j
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// �l���O�ŏ��������Ă���� �������ʁ� �i= {0};�j
	d3dpp.BackBufferWidth            = SCREEN_WIDTH;					// �X�N���[���̕��̃o�b�N�o�b�t�@
	d3dpp.BackBufferHeight           = SCREEN_HEIGHT;					// �X�N���[���̍����̃o�b�N�o�b�t�@
	d3dpp.BackBufferFormat           = d3ddm.Format;					// �J���[���[�h�̎w��
	d3dpp.BackBufferCount            = 1;								
	d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD;			
	d3dpp.EnableAutoDepthStencil     = TRUE;							// �G���[�΍�
	d3dpp.AutoDepthStencilFormat     = D3DFMT_D16;						// �G���[�΍�
	d3dpp.Windowed                   = bWindow;							// �X�N���[�����
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		

	// Direct3D�f�o�C�X�̍쐬�i�n�[�h�E�F�A�ōs���j
	if (FAILED(
		m_pD3D -> CreateDevice(
			D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, 
			D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
	{
		// �`��̓n�[�h�E�F�A�A���_�����̓\�t�g�E�F�A�ōs��
		if (FAILED(
			m_pD3D -> CreateDevice(
				D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, 
				D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
		{
			// �S�Ă��\�t�g�E�F�A�ōs��
			if (FAILED(
				m_pD3D -> CreateDevice(
					D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, 
					D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
			{
				MessageBox(NULL, "���������ł��I�o�b�����ւ��Ă��������I", "�G���[", MB_OK);
				return E_FAIL;
			}//if.fin

		}//if.fin

	}//if.fin

	// �A���t�@�u�����h�̐ݒ�
	m_pD3DDevice -> SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	// �������������s��
	m_pD3DDevice -> SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	// �W������
	m_pD3DDevice -> SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �y��r���s�Ȃ�
	m_pD3DDevice -> SetRenderState(D3DRS_ZENABLE, TRUE);

	// �e�N�X�`���X�e�[�W�X�e�[�g�ݒ�F�J���[
	m_pD3DDevice -> SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3DDevice -> SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	m_pD3DDevice -> SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	// �e�N�X�`���X�e�[�W�X�e�[�g�ݒ�F�A���t�@
	m_pD3DDevice -> SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice -> SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	m_pD3DDevice -> SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	// �T���v���[�X�e�[�g�̐ݒ�i�e�N�X�`���k�����j
	m_pD3DDevice -> SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	// �T���v���[�X�e�[�g�̐ݒ�i�e�N�X�`���g�厞�j
	m_pD3DDevice -> SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	// �A�O���b�V�u���[�h�̐ݒ�
	m_pD3DDevice -> SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);

	// �t�H���g�ݒ�
	D3DXCreateFont(m_pD3DDevice, 20, 0, 0, 0, 0, 0, 0, 0, 0, "tahoma", &m_pFont);

	// ����I��
	return S_OK;

}

/*-----------------------------------------------------------------------------
 �I�������֐�
-----------------------------------------------------------------------------*/
void CRenderer :: Uninit(void)
{
	// Direct3D�f�o�C�X�̉��
	SAFE_RELEASE(m_pD3DDevice);

	// Direct3D�C���^�[�t�F�[�X�̉��
	SAFE_RELEASE(m_pD3D);

	// Direct3D�t�H���g�̉��
	SAFE_RELEASE(m_pFont);

}

/*-----------------------------------------------------------------------------
 �X�V�����֐�
-----------------------------------------------------------------------------*/
void CRenderer :: Update(void)
{
	
}

/*-----------------------------------------------------------------------------
 �`��J�n�����֐�
-----------------------------------------------------------------------------*/
HRESULT CRenderer :: DrawBigen(void)
{
	// �r���[�|�[�g�Ɛ[�x�o�b�t�@�̃N���A�ƃX�e���V���o�b�t�@�̍폜
	if (FAILED(m_pD3DDevice -> Clear(0, NULL, 		// �N���A����̈�͑S��
		D3DCLEAR_TARGET |							// �o�b�N�o�b�t�@���w��
		D3DCLEAR_ZBUFFER, 							// �[�x�o�b�t�@�iZ�o�b�t�@�j���w��
		D3DCOLOR_RGBA(0, 0, 0, 255), 				// �N���A����F
		1.0f, 										// �N���A����[�x�o�b�t�@�iZ�o�b�t�@�j�̒l
		0)))										// �N���A����X�e���V���o�b�t�@�̒l 
	{
		return E_FAIL;
	}//if.fin
	
	// �`��J�n�ݒ�
	if(FAILED(m_pD3DDevice -> BeginScene())) return E_FAIL;

	// ����I��
	return S_OK;

}

/*-----------------------------------------------------------------------------
 �`��I�������֐�
-----------------------------------------------------------------------------*/
void CRenderer :: DrawEnd(void)
{
	// �f�B�X�v���C�ւ̕`�揈��
	m_pD3DDevice -> EndScene();

	 // �`�挋�ʂ̓]��
	m_pD3DDevice -> Present(NULL, NULL, NULL, NULL);

}

