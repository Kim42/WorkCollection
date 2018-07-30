/*=============================================================================

 �e�L�X�g�e�N�X�`���\������[ texttexture.cpp ]

=============================================================================*/
/*=============================================================================
 �C���N���[�h�w�b�_
=============================================================================*/
#include "manager.h"
#include "mode.h"
#include "textTexture.h"
#include "fade.h"
#include "sound.h"

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

/*=============================================================================
 �ÓI�����o�̓��I�m��
=============================================================================*/
int CTextTexture::m_nCursor = NEXT_STAGE;

/*-----------------------------------------------------------------------------
 ��������
-----------------------------------------------------------------------------*/
CTextTexture *CTextTexture::Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �g�p�錾
	CTextTexture *pText;

	// �N���X�̐���
	pText = new CTextTexture;

	// ������
	pText->Init(nTexType, pos, size);

	// �N���X�|�C���^��Ԃ�
	return pText;

}

/*-----------------------------------------------------------------------------
����������
-----------------------------------------------------------------------------*/
HRESULT CTextTexture::Init(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_Pos = pos;
	m_Size = size;
	m_nTexType = nTexType;

	// �I�u�W�F�N�g�̏�����
	CScene2D::Init();

	// ����I��
	return S_OK;

}

/*-----------------------------------------------------------------------------
 �I������
-----------------------------------------------------------------------------*/
void CTextTexture::Uninit(void)
{
	// �I�u�W�F�N�g�̔j��
	CScene2D::Uninit();

}

/*-----------------------------------------------------------------------------
 �X�V����
-----------------------------------------------------------------------------*/
void CTextTexture::Update(void)
{
	// �Q�[���p�b�h�g�p�錾
	CInputGamePad *pGamePad = CManager::GetInputGamePad();

	if (m_nTexType == SELECT)
	{
		static int nCus1 = STAGE_SELECT, nCus2 = RETRY;
		int nEmpty1;

		if (CInputGamePad::POV_UP == pGamePad->GetPadPOVRepeat())
		{
			// SE �Đ�
			CManager::GetSound()->Play(CSound::SE_CURSOR);

			nEmpty1   = nCus2;
			nCus2     = nCus1;
			nCus1     = m_nCursor;
			m_nCursor = nEmpty1;

			// SE ��~
			CManager::GetSound()->Stop(CSound::SE_CURSOR);
		}
		
		if (CInputGamePad::POV_DOWN == pGamePad->GetPadPOVTrigger())
		{
			// SE �Đ�
			CManager::GetSound()->Play(CSound::SE_CURSOR);

			nEmpty1   = m_nCursor;
			m_nCursor = nCus1;
			nCus1     = nCus2;
			nCus2     = nEmpty1;

			// SE ��~
			CManager::GetSound()->Stop(CSound::SE_CURSOR);
		}//if.fin

		// ���W�̐ݒ�
		switch (m_nCursor)
		{
			case NEXT_STAGE:

				// ���̃X�e�[�W�֑J��
				// ���X�e�[�W���ŏI�X�e�[�W�̏ꍇ�͍ŏ��̃X�e�[�W��
				if (pGamePad->GetPadButtonTrigger(CInputGamePad::GB_A))
				{
					// �I�u�W�F�N�g�̔j��
					CScene::ReleaseAll();

					CManager::m_nNowStage++;

					if (CManager::m_nNowStage > 6) CManager::m_nNowStage = 1;

					CManager::SetMode(new CModeGame, CManager::m_nNowStage);

					return;
				}//if.fin
					

				m_Pos.y = 300.0f;
				break;

			case STAGE_SELECT:

				// �X�e�[�W�Z���N�g�֑J��
				if (pGamePad->GetPadButtonTrigger(CInputGamePad::GB_A)) 
				{
					// �I�u�W�F�N�g�̔j��
					CScene::ReleaseAll();

					CManager::SetMode(new CModeStageSelect);

					return;
				}//if.fin

				m_Pos.y = 380.0f;
				break;

			case RETRY:

				// �����P�x���̃X�e�[�W���v���C
				if (pGamePad->GetPadButtonTrigger(CInputGamePad::GB_A))
				{
					// �I�u�W�F�N�g�̔j��
					CScene::ReleaseAll();

					CManager::SetMode( new CModeGame , CManager::m_nNowStage);

					return;
				}//if.fin

				m_Pos.y = 460.0f;
				break;
		}//switch.fin

		// �I�u�W�F�N�g�̍X�V
		CScene2D::Update();

	}//if.fin

}

/*-----------------------------------------------------------------------------
 �`�揈��
-----------------------------------------------------------------------------*/
void CTextTexture::Draw(void)
{
	// �I�u�W�F�N�g�̕`��
	CScene2D::Draw();

}

