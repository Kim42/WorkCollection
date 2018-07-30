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
#include "scene.h"
#include "sound.h"

#include "light.h"
#include "camera.h"
#include "bg.h"
#include "timer.h"
#include "collecter.h"

#include "data.h"

#include "textTexture.h"

#include "player.h"

/*******************************************************************************
* �}�N����`
*******************************************************************************/

/*******************************************************************************
* �ÓI�����o�ϐ�
*******************************************************************************/
CCamera *CModeGame::m_pCamera;
CLight *CModeGame::m_pLight;

bool g_Pause = false;

/*******************************************************************************
�������֐�
*******************************************************************************/
void CModeGame::Init( int StageID )
{
	// �o�b�N�O���E���h������
	CBg::Init(SWEET_BG);

	// �J�����̏�����
	CCamera :: Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -13.0f));

	// �X�e�[�W�I��
	switch(StageID)
	{
	case 0:
		CData::Load(TEXT_NAME_TUTORIAL);
		break;

	case 1:
		CData::Load(TEXT_NAME_TSAGE1);
		break;

	case 2:
		CData::Load(TEXT_NAME_TSAGE2);
		break;

	case 3:
		CData::Load(TEXT_NAME_TSAGE3);
		break;

	case 4:
		CData::Load(TEXT_NAME_TSAGE4);
		break;

	case 5:
		CData::Load(TEXT_NAME_TSAGE5);
		break;

	case 6:
		CData::Load(TEXT_NAME_TSAGE6);
		break;

	default:
		break;
	}//switch.fin

	// �^�C�}�[����
	CTimer::Create(TIME_CLOCK, 100, D3DXVECTOR3(820.0f, 15.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));

	// �R���N�^�[����
	CCollecter::Create(COUNT_ICON, D3DXVECTOR3(10.0f, 5.0f, 0.0f), D3DXVECTOR3(75.0f, 75.0f, 0.0f));

	// BGM �Đ�
	CManager::GetSound()->Play(CSound::GAME_BGM);

	g_Pause = false;

}

/*******************************************************************************
�I���֐�
*******************************************************************************/
void CModeGame::Uninit( void )
{
	// BGM ��~
	CManager::GetSound()->Stop(CSound::GAME_BGM);

	// �J�����j��
	CCamera::Uninit();

	CBg::Uninit();

	// �S�Ă������[�X
	CScene::ReleaseAll();
}


/*******************************************************************************
�X�V�֐�
*******************************************************************************/
void CModeGame::Update( void )
{
	// �Q�[���p�b�h�g�p�錾
	CInputGamePad *pGamePad = CManager::GetInputGamePad();

	CPlayer* Player = NULL;

	// �J�����X�V
	CCamera :: Update();

	// �V�[���I�u�W�F�N�g�����̃��[�v
	for (int nCnt = 0; nCnt < NUM_SCENE; nCnt++)
	{
		// ID�̎擾
		CScene *pScene = CScene::GetScene(nCnt);

		// NULLCHECK
		if (pScene == NULL) continue;

		// �I�u�W�F�N�g�^�C�v�̎���
		if (pScene->GetObjType() == TYPE_TIMER)
		{
			CTimer *pClass = (CTimer*)pScene;

			// �X�g�b�v�E�H�b�`
			pClass->SetState(!g_Pause);
		}//if.fin

		if(pScene->GetObjType() == TYPE_PLAYER)
		{
			Player = (CPlayer*)pScene;
		}

	}//for.fin


	if(Player != NULL)
	{
		if(Player->GetGoal() == false && Player->GetOver() == false)
		{
			if(pGamePad->GetPadButtonTrigger(CInputGamePad::GB_STRAT))
			{
				g_Pause ^= true;

				if(g_Pause)
				{
					CTextTexture::Create(NEXT_STAGE, D3DXVECTOR3(290.0f, 300.0f, 0.0f), D3DXVECTOR3(200.0f, 70.0f, 0.0f));
					CTextTexture::Create(STAGE_SELECT, D3DXVECTOR3(290.0f, 380.0f, 0.0f), D3DXVECTOR3(200.0f, 70.0f, 0.0f));
					CTextTexture::Create(RETRY, D3DXVECTOR3(290.0f, 460.0f, 0.0f), D3DXVECTOR3(200.0f, 70.0f, 0.0f));
					CTextTexture::Create(SELECT, D3DXVECTOR3(240.0f, 300.0f, 0.0f), D3DXVECTOR3(50.0f, 70.0f, 0.0f));
				}
				else
				{
					for (int nCnt = 0; nCnt < NUM_SCENE; nCnt++)
					{
						// ID�̎擾
						CScene *pScene = CScene::GetScene(nCnt);

						// NULLCHECK
						if (pScene == NULL) continue;

						// �I�u�W�F�N�g�^�C�v�̎���
						if (pScene->GetTexType() == NEXT_STAGE || pScene->GetTexType() == STAGE_SELECT || pScene->GetTexType() == RETRY || pScene->GetTexType() == SELECT)
						{
							pScene->Uninit();
						}
					}
				}
			}
		}
	}
}

/*******************************************************************************
�`��֐�
*******************************************************************************/
void CModeGame::Draw( void )
{
	// ���C�g�ݒu
	CLight :: Set();

	// �J�����̐ݒu
	CCamera :: Set();

	// �o�b�N�O���E���h
	CBg::Draw();

}


