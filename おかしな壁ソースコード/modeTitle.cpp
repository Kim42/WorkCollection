/*============================================================================

�|���S���\��[manager.cpp]

Author: Miyu Ishikawa
Date: 2017/04/26

=============================================================================*/

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "manager.h"
#include "mode.h"
#include "title.h"
#include "sound.h"
#include "scene.h"

#include "light.h"
#include "camera.h"
#include "bg.h"

#include "player.h"
#include "field.h"

#include "textTexture.h"

#include "fade.h"

/*******************************************************************************
* �}�N����`
*******************************************************************************/

/*******************************************************************************
* �ÓI�����o�ϐ�
*******************************************************************************/

/*******************************************************************************
�������֐�
*******************************************************************************/
void CModeTitle::Init( void )
{
	CTitle::Create(D3DXVECTOR3(100.0f, 5.0f, 0.0f), D3DXVECTOR3(800, 400, 0.0f));

	// �o�b�N�O���E���h������
	CBg::Init(SWEET_BG2);

	// �J�����̏�����
	CCamera :: Init(D3DXVECTOR3(10.0f, 4.0f, 0.0f), D3DXVECTOR3(10.0f, 4.0f, -13.0f));

	// �v���C���[����
	CPlayer :: Create(WALK2, D3DXVECTOR3(13.0f, -2.0f, 0.0f), D3DXVECTOR3(1.0f, 1.5f, 0.0f));

	// �K�菰
	CField::Create(YUKA, D3DXVECTOR3(-3.0f, -4.0f, 0.0f), D3DXVECTOR3(30.0f, 2.0f, 0.0f));

	// ����
	CTextTexture::Create(START, D3DXVECTOR3(280.0f, 400.0f, 0.0f), D3DXVECTOR3(450.0f, 70.0f, 0.0f));

	// BGM �Đ�
	CManager::GetSound()->Play(CSound::TITLE_BGM);

}

/*******************************************************************************
�I���֐�
*******************************************************************************/
void CModeTitle::Uninit( void )
{
	// BGM ��~
	CManager::GetSound()->Stop(CSound::TITLE_BGM);

	CBg::Uninit();

	// �S�Ă������[�X
	CScene::ReleaseAll();
}


/*******************************************************************************
�X�V�֐�
*******************************************************************************/
void CModeTitle::Update( void )
{
	// �Q�[���p�b�h�g�p�錾
	CInputGamePad *pGamePad = CManager::GetInputGamePad();

	CBg::Update();

	if(pGamePad->GetPadButtonTrigger(CInputGamePad::GB_A))
	{
		// SE
		CManager::GetSound()->Play(CSound::SE_SKILL_SWAP);

		CManager::SetMode(new CModeStageSelect);

		// SE
		CManager::GetSound()->Stop(CSound::SE_SKILL_SWAP);
	}

}

/*******************************************************************************
�`��֐�
*******************************************************************************/
void CModeTitle::Draw( void )
{
	// ���C�g�ݒu
	CLight :: Set();

	// �J�����̐ݒu
	CCamera :: Set();

	CBg::Draw();

}

