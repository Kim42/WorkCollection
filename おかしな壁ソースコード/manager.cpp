/*=============================================================================

 �Ǘ�����[ manager.cpp ]

=============================================================================*/
/*=============================================================================
�C���N���[�h�w�b�_
=============================================================================*/
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "sound.h"
#include "scene.h"

#include "mode.h"
#include "fade.h"

/*=============================================================================
 �����o�ϐ��̓��I�錾
=============================================================================*/
CInputKeyboard  *CManager :: m_pInputKeyboard  = NULL;
CInputGamePad  *CManager :: m_pInputGamePad  = NULL;
CMode* CManager::m_pMode = NULL;
CSound* CManager::m_Sound = NULL;
CFade* CManager::m_pFade = NULL;

int CManager::m_nNowStage = 0;

/*-----------------------------------------------------------------------------
 �����������֐�
-----------------------------------------------------------------------------*/
HRESULT CManager :: Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �����_���[�̐���
	CRenderer :: Init(hInstance, hWnd, bWindow);

	// �e�N�X�`���f�[�^�̓ǂݍ���
	CTexture::Load();

	// �T�E���h�f�[�^�̓ǂݍ���
	m_Sound = new CSound;
	m_Sound->Init(hWnd);

	// �C���v�b�g�F�L�[�{�[�h�̐���
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	// �C���v�b�g�F�Q�[���p�b�h�̐���
	m_pInputGamePad = new CInputGamePad;
	m_pInputGamePad->Init(hInstance, hWnd);

	// �Q�[���p�b�h���ڑ��̏ꍇ
	//if (!m_pInputGamePad->GetGamePad()) return E_FAIL;

	// �t�F�[�h�̐���
	m_pFade = CFade::Create(TEX_FADE, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));

	// �t�F�[�h�Z�b�g
	m_pFade->SetFade(CFade::FADE_IN);

	// �Z�b�g���[�h�F�^�C�g��
	SetMode(new CModeTitle);

	// ����I��
	return S_OK;
	
}

/*-----------------------------------------------------------------------------
 �I�������֐�
-----------------------------------------------------------------------------*/
void CManager :: Uninit(void)
{
	// �t�F�[�h�̔j��
	SAFE_DELETE_Ex(m_pFade);

	// ���[�h�̔j��
	if( m_pMode != NULL )
	{
		m_pMode->Uninit();
		delete m_pMode;
	}//if.fin

	// �V�[���I�u�W�F�N�g�̓�������E�j��
	CScene::ReleaseAll();

	// �T�E���h�f�[�^�̉��
	m_Sound->Uninit();

	// �e�N�X�`���f�[�^�̉��
	CTexture::Release();

	// �����_���j��
	CRenderer :: Uninit();

	// �C���v�b�g�����̔j��
	SAFE_DELETE_Ex(m_pInputKeyboard);
	SAFE_DELETE_Ex(m_pInputGamePad);

}

/*-----------------------------------------------------------------------------
 �X�V����
-----------------------------------------------------------------------------*/
void CManager :: Update(void)
{
	// �C���v�b�g�F�Q�[���p�b�h�X�V
	m_pInputKeyboard->Update();
	m_pInputGamePad->Update();

	// ���[�h�X�V
	m_pMode->Update();

	// �t�F�[�h�X�V
	m_pFade->Update();

	// �V�[���I�u�W�F�N�g�̍X�V
	CScene::UpdateAll();

}

/*-----------------------------------------------------------------------------
 �`��Ǘ�����
-----------------------------------------------------------------------------*/
void CManager :: Draw(void)
{
	// �����_�����O�J�n
	if(SUCCEEDED(CRenderer :: DrawBigen()))
	{
		// ���[�h�`��
		m_pMode->Draw();

		// �V�[���I�u�W�F�N�g�̕`��
		CScene::DrawAll();

		// �t�F�[�h�`��
		m_pFade->Draw();

	}//if.fin

	// �����_�����O�I��
	CRenderer :: DrawEnd();

}


/*******************************************************************************
���[�h�̂�������ꂷ��֐�
*******************************************************************************/
void CManager::SetMode( CMode *pMode )
{
	if( m_pMode != NULL )
	{
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = NULL;
	}

	m_pMode = pMode;

	if( m_pMode != NULL )
	{
		m_pMode->Init();
	}
}

/*******************************************************************************
���[�h�̂�������ꂷ��֐�(���̓�)
*******************************************************************************/
void CManager::SetMode( CMode *pMode , int StageID)
{
	if( m_pMode != NULL )
	{
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = NULL;
	}

	m_pMode = pMode;

	if( m_pMode != NULL )
	{
		m_pMode->Init(StageID);
	}
}

