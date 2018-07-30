/*=============================================================================

 �V�[�����ʏ���[ scene.cpp ]

=============================================================================*/
/*=============================================================================
 �C���N���[�h�w�b�_
=============================================================================*/
#include "scene.h"

/*=============================================================================
 �����o�ϐ��̓��I�������m��
=============================================================================*/
CScene *CScene :: m_apScene[NUM_SCENE] = {};
int     CScene :: m_nNumScene = 0;

/*-----------------------------------------------------------------------------
 �R���X�g���N�^
-----------------------------------------------------------------------------*/
CScene :: CScene()
{
	// �I�u�W�F�N�g�J�E���^
	for(int nCntScene = 0; nCntScene < NUM_SCENE; nCntScene++)
	{
		// NULLCHECK
		if(m_apScene[nCntScene] == NULL)
		{
			m_apScene[nCntScene] = this;		// ���g�̓o�^����
			m_nID = nCntScene;					// ���ʔԍ��̐ݒ�
			m_nNumScene++;						// �J�E���g�A�b�v

			break;

		}//if.fin

	}//for.fin

}

/*-----------------------------------------------------------------------------
 �X�V��������
-----------------------------------------------------------------------------*/
void CScene :: UpdateAll(void)
{
	// �C���X�^���X�����ꂽ�I�u�W�F�N�g�̍X�V
	for(int nCntScene = 0; nCntScene < NUM_SCENE; nCntScene++)
	{
		// NULLCHECK
		if(m_apScene[nCntScene] != NULL)
		{
			m_apScene[nCntScene] -> Update();
		}//if.fin

	}//for.fin

}

/*-----------------------------------------------------------------------------
 �`�擝������
-----------------------------------------------------------------------------*/
void CScene :: DrawAll(void)
{
	// �C���X�^���X�����ꂽ�I�u�W�F�N�g�̕`��
	for(int nCntScene = 0; nCntScene < NUM_SCENE; nCntScene++)
	{
		// NULLCHECK
		if(m_apScene[nCntScene] != NULL)
		{
			m_apScene[nCntScene] -> Draw();
		}//if.fin

	}//for.fin

}

/*-----------------------------------------------------------------------------
 �����������
-----------------------------------------------------------------------------*/
void CScene :: ReleaseAll(void)
{
	// �C���X�^���X�����ꂽ�I�u�W�F�N�g�̏I��
	for(int nCntScene = 0; nCntScene < NUM_SCENE; nCntScene++)
	{
		// NULLCHECK
		if(m_apScene[nCntScene] != NULL)
		{
			m_apScene[nCntScene] -> Uninit();

			// �������J��
			delete m_apScene[nCntScene];
			m_apScene[nCntScene] = NULL;

		}//if.fin

	}//for.fin

}

/*-----------------------------------------------------------------------------
 �������
-----------------------------------------------------------------------------*/
void CScene :: Release(void)
{
	// NLLCHECK
	if(m_apScene[m_nID] != NULL)
	{
		// ���ʔԍ��̑ޔ�
		int nID = m_nID;

		// �ԍ��̓��f�[�^�̔j��
		delete m_apScene[nID];
		m_apScene[nID] = NULL;

		// �J�E���g�_�E��
		m_nNumScene--;

	}//if.fin

}



