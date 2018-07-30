/*=============================================================================

 �R���N�^�[����[ collecter.cpp ]

=============================================================================*/
/*=============================================================================
 �C���N���[�h�w�b�_
=============================================================================*/
#include "manager.h"
#include "collecter.h"
#include "number.h"

/*-----------------------------------------------------------------------------
 ��������
-----------------------------------------------------------------------------*/
CCollecter *CCollecter::Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �g�p�錾
	CCollecter *pScore;

	// �X�R�A�̐���
	pScore = new CCollecter;

	// ������
	pScore->Init(nTexType, pos, size);

	// �N���X�|�C���^��Ԃ�
	return pScore;

}

/*-----------------------------------------------------------------------------
 ����������
-----------------------------------------------------------------------------*/
HRESULT CCollecter::Init(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_Pos = pos;
	m_Size = size;
	m_nTexType = nTexType;

	// �ϐ��錾
	int nNumber, snbNumber = 0;

	// �w�茅�����̃��[�v
	for (int nCnt = 0; nCnt < NUM_DIGIT_C; nCnt++)
	{
		// ������
		nNumber = snbNumber % 10;
		snbNumber /= 10;

		// �i���o�[�̐����F�e���̐����̒l�̐ݒ�
		m_apNumber[nCnt] = CNumber::Create(COUNT_NUMBER,
			D3DXVECTOR3((pos.x + size.x * 1.5f) - 35.0f * nCnt, pos.y, 0.0f),
			D3DXVECTOR3(40.0f, size.y, 0.0f), nNumber);
	}//for.fin

	// �I�u�W�F�N�g������
	CScene2D::Init();

	// ����I��
	return S_OK;

}

/*-----------------------------------------------------------------------------
 �I������
-----------------------------------------------------------------------------*/
void CCollecter::Uninit(void)
{
	// �w�茅�����̃��[�v
	for (int nCnt = 0; nCnt < NUM_DIGIT_C; nCnt++)
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
void CCollecter::Update(void)
{
	// �ϐ��錾
	int nNumber, snbNumber;

	// �X�R�A�̑ޔ�
	snbNumber = m_nNumCollect;

	// �����̐ݒ�
	for (int nCnt = 0; nCnt < NUM_DIGIT_C; nCnt++)
	{
		// �e���̐����̎Z�o
		nNumber = snbNumber % 10;
		snbNumber /= 10;

		// �e���̐����̒l�ݒ�
		m_apNumber[nCnt]->SetNumber(nNumber);

	}//for.fin

}

/*-----------------------------------------------------------------------------
 �`�揈��
-----------------------------------------------------------------------------*/
void CCollecter::Draw(void)
{
	// �X�R�A�̕\���̐��l�̐ݒ�
	for (int nCnt = 0; nCnt < NUM_DIGIT_C; nCnt++)
	{
		// �i���o�[�`��
		m_apNumber[nCnt]->Draw();
	}//for.fin

	// �I�u�W�F�N�g�`��
	CScene2D::Draw();

}

