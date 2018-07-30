/*=============================================================================

 �^�C�}�[����[ timer.cpp ]

=============================================================================*/
/*=============================================================================
�C���N���[�h�w�b�_
=============================================================================*/
#include "manager.h"
#include "timer.h"
#include "number.h"

/*=============================================================================
 �}�N����`
=============================================================================*/
#define FRAME 60

/*-----------------------------------------------------------------------------
 �R���X�g���N�^
-----------------------------------------------------------------------------*/
CTimer::CTimer()
{
	SetObjType(TYPE_TIMER);

	m_bTimer = true;
	m_nTimer = 0;
	m_nFrameTimer = 0;

}

/*-----------------------------------------------------------------------------
 �f�X�N�g���N�^
-----------------------------------------------------------------------------*/
CTimer :: ~CTimer()
{

}

/*-----------------------------------------------------------------------------
 ��������
-----------------------------------------------------------------------------*/
CTimer *CTimer::Create(int nTexType, int nTimeMax, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �g�p�錾
	CTimer *pScore;

	// �X�R�A�̐���
	pScore = new CTimer;

	// ������
	pScore->Init(nTexType, nTimeMax, pos, size);

	// �N���X�|�C���^��Ԃ�
	return pScore;

}

/*-----------------------------------------------------------------------------
 ����������
-----------------------------------------------------------------------------*/
HRESULT CTimer::Init(int nTexType, int nTimeMax, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_Pos      = pos;
	m_Size     = size;
	m_nTexType = nTexType;
	m_nTimer   = nTimeMax;

	// �ϐ��錾
	int nNumber, snbNumber = m_nTimer;

	// �w�茅�����̃��[�v
	for (int nCnt = 0; nCnt < NUM_DIGIT_T; nCnt++)
	{
		// ������
		nNumber = snbNumber % 10;
		snbNumber /= 10;

		// �i���o�[�̐����F�e���̐����̒l�̐ݒ�
		m_apNumber[nCnt] = CNumber::Create(TIME_NUMBER, 
											D3DXVECTOR3((pos.x + size.x * 2.2f) - 35.0f * nCnt, pos.y - 10.0f, 0.0f),
											D3DXVECTOR3(40.0f, 75.0f, 0.0f), nNumber);
	}//for.fin

	// �I�u�W�F�N�g������
	CScene2D::Init();

	// ����I��
	return S_OK;

}

/*-----------------------------------------------------------------------------
 �I������
-----------------------------------------------------------------------------*/
void CTimer::Uninit(void)
{
	// �w�茅�����̃��[�v
	for (int nCnt = 0; nCnt < NUM_DIGIT_T; nCnt++)
	{
		// �i���o�[�̔j��
		m_apNumber[nCnt]->Uninit();
	}//for.fin

	// �I�u�W�F�N�g�I��
	CScene2D::Uninit();

}

/*-----------------------------------------------------------------------------
 �X�V����
-----------------------------------------------------------------------------*/
void CTimer::Update(void)
{
	if (m_bTimer == true)
	{
		// �t���[���J�E���g�A�b�v
		m_nFrameTimer++;

		// �ϐ��錾
		int nNumber, snbNumber;

		// �J�E���g�_�E��
		if (m_nFrameTimer >= FRAME)
		{
			m_nTimer--;
			m_nFrameTimer = 0;
		}//if.fin

		// �X�R�A�̑ޔ�
		snbNumber = m_nTimer;

		// �����̐ݒ�
		for (int nCnt = 0; nCnt < NUM_DIGIT_T; nCnt++)
		{
			// �e���̐����̎Z�o
			nNumber = snbNumber % 10;
			snbNumber /= 10;

			// �e���̐����̒l�ݒ�
			m_apNumber[nCnt]->SetNumber(nNumber);

		}//for.fin

	}//if.fin

}

/*-----------------------------------------------------------------------------
 �`�揈��
-----------------------------------------------------------------------------*/
void CTimer::Draw(void)
{
	// �X�R�A�̕\���̐��l�̐ݒ�
	for (int nCnt = 0; nCnt < NUM_DIGIT_T; nCnt++)
	{
		// �i���o�[�`��
		m_apNumber[nCnt]->Draw();
	}//for.fin

	// �I�u�W�F�N�g�`��
	CScene2D::Draw();

}

