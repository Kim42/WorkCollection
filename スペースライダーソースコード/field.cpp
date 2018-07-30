/*******************************************************************************
* �^�C�g��:		�t�B�[���h�v���O����
* �v���O������:		field.cpp
* �쐬��:		CP11SATA  15  Kim Nakamura
* �쐬��:		2016/02/20
********************************************************************************
* �X�V����:		- 2016/02/20�@Kim Nakamura
*			- V1.00�@Initial Version
*			���[�X�p�t�B�[���h�t���[���̊֐��̒ǉ�
*			�E���[�X�p�t�B�[���h�̍쐬
*	3/4		�E���[�X�p�t�B�[���h�t���[������10���K�v
*			�E2���̓X�^�[�g�ƃS�[���ł���I
*******************************************************************************/
/*******************************************************************************
* scanf ��warning�h�~ 
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

/*******************************************************************************
* �C���N���[�h�t�@�C��
*  �K�v�ȏ��
*  	�\���̂��߂̊�{�v�f
*  	�t�B�[���h�̎��g���
*  	�v���C���[�̏��
*******************************************************************************/
#include "main.h"
#include "field.h"
#include "player.h"
#include "computer.h"

/*******************************************************************************
* �}�N����`
*******************************************************************************/


/*******************************************************************************
* �\���̒�`
*******************************************************************************/


/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/


/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
// �w�b�_�[�t�@�C������v���C���[�\���̂̃O���[�o���錾
FIELD g_nField;

/*******************************************************************************
* �֐���:	void InitField( void ):�i�������j�֐�
* ����:		void
* �߂�l:	�Ȃ�
* ����:		�t�B�[���h�̏����ݒ�
*******************************************************************************/
void InitField( void )
{
	// �v���O�����X�^�[�g

	// ������
	g_nField.nCnt     = ZERO_INT;
	g_nField.nCntSec  = ZERO_INT;
	g_nField.nRanking = ZERO_INT;
	g_nField.bPlay   = false;
	g_nField.bTitle  = false;
	g_nField.bStart  = false;

	RaceFieldStart();			// �X�^�[�g�t�B�[���h�̕\��

	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	void UpdateField( void ):�i�X�V�j�֐�
* ����:		void
* �߂�l:	�Ȃ�
* ����:		�t�B�[���h�̍X�V����
*******************************************************************************/
void UpdateField( void )
{
	// �v���O�����X�^�[�g

	// �^�C�g���̕\��
	if(g_nField.bTitle == false)
	{
		title();
		g_nField.bTitle = true;		// �^�C�g���\�����܂�����
	}//if.fin

	// �G���^�[�L�[����������Q�[���X�^�[�g
	if(INP(PK_ENTER) && g_nField.bPlay == false)
	{
		// �Q�[���X�^�[�g
		g_nField.bStart = true;
	}//if.fin

	// �������A�e�t�B�[���h�f�[�^��z��ɓ���
	if(g_nField.bStart == true)
	{
		RaceFieldStart();			// �X�^�[�g�t�B�[���h�̕\��
		g_nField.bStart = false;
		g_nField.bPlay  = true;
	}//if.fin

	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	void DrawField( void ):�i�`��j�֐�
* ����:		void
* �߂�l:	�Ȃ�
* ����:		���[�X�t�B�[���h�̕`�揈��
*	3/4		���[�X�t�B�[���h���Q�����z���18�̕`��f�[�^�̎󂯎��
*			�S�[���͊��ɍ���Ă������ƁI�i2�����z��Łj
*******************************************************************************/
void DrawField( void )
{
	// �v���O�����X�^�[�g

	// �v���C���[�̍\���̃|�C���^�ϐ��錾
	PLAYER *pPlayer;

	// �v���C���[���̃R�s�[�̎擾
	pPlayer = GetPlayer();

	// �Q�[���J�n
	if(g_nField.bPlay == true)
	{
		// �v���C���[�̂w���W����79���A���̃R�[�X�̕`�悷��
		if((g_nField.nCnt == 1  ) && (g_nField.nCntSec == 0))
		{
			RaceField_40_79_and_320_359_and_640_679();			// �O�Pand�O�Wand�P�U�F�ӂ�
			g_nField.nCntSec++;									// �C���N�������g
		}
		else if((g_nField.nCnt == 2) && (g_nField.nCntSec == 1))
		{
			RaceField_80_119_and_360_399_and_440_479();			// �O�Qand�O�Xand�P�P�F�����n�P
			g_nField.nCntSec++;									// �C���N�������g
		}
		else if((g_nField.nCnt == 3) && (g_nField.nCntSec == 2))
		{
			RaceField_120_159_and_480_519();					// �O�Rand�P�Q�F�x�e�n�P
			g_nField.nCntSec++;									// �C���N�������g
		}
		else if((g_nField.nCnt == 4) && (g_nField.nCntSec == 3))
		{
			RaceField_160_199_and_520_559_and_680_719 ();		// �O�Sand�P�Rand�P�V�F�ӂ�
			g_nField.nCntSec++;									// �C���N�������g
		}
		else if((g_nField.nCnt == 5) && (g_nField.nCntSec == 4))
		{
			RaceField_200_239_and_400_439();					// �O�Tand�P�O�F�ӂ�
			g_nField.nCntSec++;									// �C���N�������g
		}
		else if((g_nField.nCnt == 6) && (g_nField.nCntSec == 5))
		{
			RaceField_240_279_and_560_599();					// �O�Uand�P�S�F�����n�Q
			g_nField.nCntSec++;									// �C���N�������g
		}
		else if((g_nField.nCnt == 7) && (g_nField.nCntSec == 6))
		{
			RaceField_280_319_and_600_639();					// �O�Vand�P�T�F�x�e�n�Q
			g_nField.nCntSec++;									// �C���N�������g
		}
		else if((g_nField.nCnt == 8) && (g_nField.nCntSec == 7))
		{
			RaceField_40_79_and_320_359_and_640_679();			// �O�Pand�O�Wand�P�U�F�ӂ�
			g_nField.nCntSec++;									// �C���N�������g
		}
		else if((g_nField.nCnt == 9) && (g_nField.nCntSec == 8))
		{
			RaceField_80_119_and_360_399_and_440_479();			// �O�Qand�O�Xand�P�P�F�����n�P
			g_nField.nCntSec++;									// �C���N�������g
		}
		else if((g_nField.nCnt == 10) && (g_nField.nCntSec == 9))
		{
			RaceField_200_239_and_400_439();					// �O�Tand�P�O�F�ӂ�
			g_nField.nCntSec++;									// �C���N�������g
		}
		else if((g_nField.nCnt == 11) && (g_nField.nCntSec == 10))
		{
			RaceField_80_119_and_360_399_and_440_479();			// �O�Qand�O�Xand�P�P�F�����n�P
			g_nField.nCntSec++;									// �C���N�������g
		}
		else if((g_nField.nCnt == 12) && (g_nField.nCntSec == 11))
		{
			RaceField_120_159_and_480_519();					// �O�Rand�P�Q�F�x�e�n�P
			g_nField.nCntSec++;									// �C���N�������g
		}
		else if((g_nField.nCnt == 13) && (g_nField.nCntSec == 12))
		{
			RaceField_160_199_and_520_559_and_680_719 ();		// �O�Sand�P�Rand�P�V�F�ӂ�
			g_nField.nCntSec++;									// �C���N�������g
		}
		else if((g_nField.nCnt == 14) && (g_nField.nCntSec == 13))
		{
			RaceField_240_279_and_560_599();					// �O�Uand�P�S�F�����n�Q
			g_nField.nCntSec++;									// �C���N�������g
		}
		else if((g_nField.nCnt == 15) && (g_nField.nCntSec == 14))
		{
			RaceField_280_319_and_600_639();					// �O�Vand�P�T�F�x�e�n�Q
			g_nField.nCntSec++;									// �C���N�������g
		}
		else if((g_nField.nCnt == 16) && (g_nField.nCntSec == 15))
		{
			RaceField_40_79_and_320_359_and_640_679();			// �O�Pand�O�Wand�P�U�F�ӂ�
			g_nField.nCntSec++;									// �C���N�������g
		}
		else if((g_nField.nCnt == 17) && (g_nField.nCntSec == 16))
		{
			RaceField_160_199_and_520_559_and_680_719 ();		// �O�Sand�P�Rand�P�V�F�ӂ�
			g_nField.nCntSec++;									// �C���N�������g
		}
		else if((g_nField.nCnt == 18) && (g_nField.nCntSec == 17))
		{
			RaceField_720_739();								// �P�W�F�X�p�[�g�|�C���g�n
			g_nField.nCntSec++;									// �C���N�������g
		}
		else if((g_nField.nCnt == 19) && (g_nField.nCntSec == 18))
		{
			RaceFieldGoal();									// �P�X�F�S�[��
			g_nField.nCntSec++;									// �C���N�������g
		}//if.fin

	}//if.fin
	
	// �v���O�����G���h
 }

/*******************************************************************************
* �֐���:	void UninitField( void ):�i�I���j�֐�
* ����:		void
* �߂�l:	�Ȃ�
* ����:		�t�B�[���h�̏I������
*******************************************************************************/
void UninitField( void )
{
	// �v���O�����X�^�[�g

	

	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	void RaceFieldStart( void )
* ����:		void
* �߂�l:	�Ȃ�
* ����:		�X�^�[�g
*******************************************************************************/
void RaceFieldStart( void )
{
	// �v���O�����X�^�[�g

	// 2�����z��Ŏg�p����ϐ��̐錾
	int nVertical;
	int nHorizontal;
	int nLocateX = ONE_INT;
	int nLocateY = ONE_INT;

	// 2�����z��̏����������i�v�f����25�~40��int�^2�����z���錾�j
	int nRaceField[MAX_VERTICAL][MAX_HORAIZONTAL] = 
	{
		// ���݈ʒu�̕\���o�[
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// �|�C���g�v���X�̐��i�w�i�j�i�X�^�[�g�Ə����Ă���j
		{0,10,10,10,10,10,0,0,0,0,10,10,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,0,0,0},
		{0,0,0,0,0,10,0,0,0,0,10,0,0,0,10,0,0,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,0,0,0},
		{0,0,0,0,10,0,0,0,0,10,0,10,0,0,10,0,0,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,0,10,10,10,0,0,0},
		{0,0,0,10,0,10,0,0,0,0,0,0,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,10,0,0},
		{0,10,10,0,0,0,10,0,0,0,0,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,0,0,0},

		// ���C���R�[�X
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,6,3,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,3,3,6,2,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,3,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,3,3,2,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,3,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,3,3,2,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,3,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0},

		// ���̕ϓN���Ȃ������̒n��
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	// ���[�X�p�t�B�[���h�̕\������
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		LOCATE(nLocateX, nLocateY++);

		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// �t�B�[���h�̗v�f�̕\��
			if(nRaceField[nVertical][nHorizontal] == BLOCK)				// �P�F�n��
			{
				COLOR(LIME);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == SLOPE)		// �Q�F��
			{
				COLOR(H_CYAN);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == COURSE)		// �R�F��
			{
				COLOR(WHITE);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == GOOD)			// �S�FGOOD��
			{
				COLOR(RED);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == VERYGOOD)		// �T�FVERYGOOD��
			{
				COLOR(H_RED);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == EXCELLENT)	// �U�FEXCELLENT��
			{
				COLOR(YELLOW);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_GOOD)		// �V�FGOOD��
			{
				COLOR(H_CYAN);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_VERYGOOD)	// �W�FVERYGOOD��
			{
				COLOR(H_CYAN);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_EXCELLENT)	// �X�FEXCELLENT��
			{
				COLOR(H_CYAN);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == STAR)			// �P�O�F��(����)
			{
				COLOR(YELLOW);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == STAR +1)		// �P�P�F��(����)
			{
				COLOR(LIME);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == SPACE)		// �O�F��
			{
				BACKCOLOR(BLACK);
				printf("�@");
			}//if.fin
	
		}//forX.fin

		printf("\0");		// NULL

	}//forY.fin

	// �z��̐擪�A�h���X�������Ƃ���UpdatePlayer�ɓn��
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// 2�����z��̐擪����\���̓��̐�p�ϐ��Ɋi�[
			g_nField.nPosition[nVertical][nHorizontal] = nRaceField[nVertical][nHorizontal];
		}//forX.fin

	}//forY.fin

	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	void RaceFieldGoal( void )
* ����:		void
* �߂�l:	�Ȃ�
* ����:		�S�[��
*******************************************************************************/
void RaceFieldGoal( void )
{
	// �v���O�����X�^�[�g

	// 2�����z��Ŏg�p����ϐ��̐錾
	int nVertical;
	int nHorizontal;
	int nLocateX = ONE_INT;
	int nLocateY = ONE_INT;

	// 2�����z��̏����������i�v�f����25�~40��int�^2�����z���錾�j
	int nRaceField[MAX_VERTICAL][MAX_HORAIZONTAL] = 
	{
		// ���݈ʒu�̕\���o�[
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// �|�C���g�v���X�̐��i�w�i�j
		{0,1,0,0,0,10,10,10,10,10,10,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,10,0,0,0,0,0,1,0},
		{0,1,0,0,0,0,0,0,0,0,10,10,0,10,0,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,10,0,0,0,0,0,1,0},
		{0,1,0,0,0,0,0,0,0,0,10,0,10,0,0,10,10,10,10,10,10,10,10,10,10,10,10,10,10,0,10,0,10,0,0,10,0,0,1,0},
		{0,1,0,0,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,10,0,10,0,0,0,1,0},
		{0,1,0,0,0,10,10,10,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,0,10,10,0,0,0,0,1,0},

		// ���C���R�[�X
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,10,10,11,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,11,11,10,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,11,11,10,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,10,10,11,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,11,11,10,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,11,11,10,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,10,10,11,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,11,11,10,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,11,11,10,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,10,10,11,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,11,11,10,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,11,11,10,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,10,10,11,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,11,11,10,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,10,10,11,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,11,11,10,0,0,0,0,0,0,0,0,0,0},

		// ���̕ϓN���Ȃ������̒n��
		{1,1,1,1,1,1,1,6,1,1,1,5,1,1,1,1,4,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	// ���[�X�p�t�B�[���h�̕\������
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		LOCATE(nLocateX, nLocateY++);

		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// �t�B�[���h�̗v�f�̕\��
			if(nRaceField[nVertical][nHorizontal] == BLOCK)				// �P�F�n��
			{
				COLOR(LIME);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == SLOPE)		// �Q�F��
			{
				COLOR(H_CYAN);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == COURSE)		// �R�F��
			{
				COLOR(WHITE);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == GOOD)			// �S�FGOOD��
			{
				COLOR(RED);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == VERYGOOD)		// �T�FVERYGOOD��
			{
				COLOR(H_RED);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == EXCELLENT)	// �U�FEXCELLENT��
			{
				COLOR(YELLOW);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_GOOD)		// �V�FGOOD��
			{
				COLOR(H_CYAN);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_VERYGOOD)	// �W�FVERYGOOD��
			{
				COLOR(H_CYAN);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_EXCELLENT)	// �X�FEXCELLENT��
			{
				COLOR(H_CYAN);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == STAR)			// �P�O�F��(����)
			{
				COLOR(YELLOW);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == STAR +1)		// �P�P�F��(����)
			{
				COLOR(LIME);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == SPACE)		// �O�F��
			{
				BACKCOLOR(BLACK);
				printf("�@");
			}//if.fin
	
		}//forX.fin

		printf("\0");		// NULL

	}//forY.fin

	// �z��̐擪�A�h���X�������Ƃ���UpdatePlayer�ɓn��
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// 2�����z��̐擪����\���̓��̐�p�ϐ��Ɋi�[�i�O�{�z��V�U�O�Ԓn�j
			g_nField.nPosition[nVertical][nHorizontal] = nRaceField[nVertical][nHorizontal];
		}//forX.fin

	}//forY.fin

	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	void RaceField_40_79_and_320_359_and_640_679 ( void )
* ����:		void
* �߂�l:	�Ȃ�											�@��
* ����:		�ӂ��n�R�[�X�O�P�ƂO�W�ƂP�U�Ŏg�p			����
*			���[�X�R�[�X�S�O  �`�V�X						�@��
*			���[�X�R�[�X�R�Q�O�`�R�T�X						�@��
*			���[�X�R�[�X�U�S�O�`�U�V�X						������
*******************************************************************************/
void RaceField_40_79_and_320_359_and_640_679 ( void )
{
	// �v���O�����X�^�[�g

	// 2�����z��Ŏg�p����ϐ��̐錾
	int nVertical;
	int nHorizontal;
	int nLocateX = ONE_INT;
	int nLocateY = ONE_INT;

	// 2�����z��̏����������i�v�f����25�~40��int�^2�����z���錾�j
	int nRaceField[MAX_VERTICAL][MAX_HORAIZONTAL] = 
	{
		// ���݈ʒu�̕\���o�[
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// �|�C���g�v���X�̐��i�w�i�j
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// ���C���R�[�X
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,0,0,0,0,2,3,3,3,3,3,4,3,0,3,3,3,3,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,0,0,0,0,0,3,3,3,3,3,3,4,3,0,3,3,3,2,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0},

		// ���̕ϓN���Ȃ������̒n��
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	// ���[�X�p�t�B�[���h�̕\������
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		LOCATE(nLocateX, nLocateY++);

		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// �t�B�[���h�̗v�f�̕\��
			if(nRaceField[nVertical][nHorizontal] == BLOCK)				// �P�F�n��
			{
				COLOR(LIME);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == SLOPE)		// �Q�F��
			{
				COLOR(H_CYAN);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == COURSE)		// �R�F��
			{
				COLOR(WHITE);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == GOOD)			// �S�FGOOD��
			{
				COLOR(RED);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == VERYGOOD)		// �T�FVERYGOOD��
			{
				COLOR(H_RED);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == EXCELLENT)	// �U�FEXCELLENT��
			{
				COLOR(YELLOW);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_GOOD)		// �V�FGOOD��
			{
				COLOR(RED);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_VERYGOOD)	// �W�FVERYGOOD��
			{
				COLOR(H_RED);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_EXCELLENT)	// �X�FEXCELLENT��
			{
				COLOR(YELLOW);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == STAR)			// �P�O�F��(����)
			{
				COLOR(YELLOW);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == STAR +1)		// �P�P�F��(����)
			{
				COLOR(LIME);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == SPACE)		// �O�F��
			{
				BACKCOLOR(BLACK);
				printf("�@");
			}//if.fin
	
		}//forX.fin

		printf("\0");		// NULL

	}//forY.fin

	// �z��̐擪�A�h���X�������Ƃ���UpdatePlayer�ɓn��
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// 2�����z��̐擪����\���̓��̐�p�ϐ��Ɋi�[�i�O�{�z��S�O�Ԓn�ڂ���j
			g_nField.nPosition[nVertical][nHorizontal] = nRaceField[nVertical][nHorizontal];
		}//forX.fin

	}//forY.fin

	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	void RaceField_80_119_and_360_399_and_440_479 ( void )
* ����:		void
* �߂�l:	�Ȃ�											������
* ����:		�����n�P�R�[�X�O�Q�ƂO�X�ƂP�P�Ŏg�p			���@��
*			���[�X�R�[�X�W�O  �`�P�P�X						�@�@��
*			���[�X�R�[�X�R�U�O�`�R�X�X						�@��
*			���[�X�R�[�X�S�S�O�`�S�V�X						������
*******************************************************************************/
void RaceField_80_119_and_360_399_and_440_479 ( void )
{
	// �v���O�����X�^�[�g

	// 2�����z��Ŏg�p����ϐ��̐錾
	int nVertical;
	int nHorizontal;
	int nLocateX = ONE_INT;
	int nLocateY = ONE_INT;

	// 2�����z��̏����������i�v�f����25�~40��int�^2�����z���錾�j
	int nRaceField[MAX_VERTICAL][MAX_HORAIZONTAL] = 
	{
		// ���݈ʒu�̕\���o�[
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// �|�C���g�v���X�̐��i�w�i�j
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// ���C���R�[�X
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,3,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,9,9,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,2,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,8,8,0,4,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,0,0,0,0},
		{0,0,0,0,0,0,0,0,7,7,0,0,0,5,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,2,0,0,0,0,0,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0,0},
		{0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,4,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0},
		{0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,5,6,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0},

		// ���̕ϓN���Ȃ������̒n��
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	// ���[�X�p�t�B�[���h�̕\������
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		LOCATE(nLocateX, nLocateY++);

		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// �t�B�[���h�̗v�f�̕\��
			if(nRaceField[nVertical][nHorizontal] == BLOCK)				// �P�F�n��
			{
				COLOR(LIME);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == SLOPE)		// �Q�F��
			{
				COLOR(H_CYAN);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == COURSE)		// �R�F��
			{
				COLOR(WHITE);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == GOOD)			// �S�FGOOD��
			{
				COLOR(RED);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == VERYGOOD)		// �T�FVERYGOOD��
			{
				COLOR(H_RED);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == EXCELLENT)	// �U�FEXCELLENT��
			{
				COLOR(YELLOW);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_GOOD)		// �V�FGOOD��
			{
				COLOR(RED);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_VERYGOOD)	// �W�FVERYGOOD��
			{
				COLOR(H_RED);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_EXCELLENT)	// �X�FEXCELLENT��
			{
				COLOR(YELLOW);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == STAR)			// �P�O�F��(����)
			{
				COLOR(YELLOW);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == STAR +1)		// �P�P�F��(����)
			{
				COLOR(LIME);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == SPACE)		// �O�F��
			{
				BACKCOLOR(BLACK);
				printf("�@");
			}//if.fin
	
		}//forX.fin

		printf("\0");		// NULL

	}//forY.fin

	// �z��̐擪�A�h���X�������Ƃ���UpdatePlayer�ɓn��
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// 2�����z��̐擪����\���̓��̐�p�ϐ��Ɋi�[�i�O�{�z��W�O�Ԓn�ڂ���j
			g_nField.nPosition[nVertical][nHorizontal] = nRaceField[nVertical][nHorizontal];
		}//forX.fin

	}//forY.fin

	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	void RaceField_120_159_and_480_519 ( void )
* ����:		void
* �߂�l:	�Ȃ�											������
* ����:		�x�e�n�P�R�[�X�O�R�ƂP�Q�Ŏg�p					�@�@��
*			���[�X�R�[�X�P�Q�O�`�P�T�X						������
*			���[�X�R�[�X�S�W�O�`�T�P�X						�@�@��
*															������
*******************************************************************************/
void RaceField_120_159_and_480_519 ( void )
{
	// �v���O�����X�^�[�g

	// 2�����z��Ŏg�p����ϐ��̐錾
	int nVertical;
	int nHorizontal;
	int nLocateX = ONE_INT;
	int nLocateY = ONE_INT;

	// 2�����z��̏����������i�v�f����25�~40��int�^2�����z���錾�j
	int nRaceField[MAX_VERTICAL][MAX_HORAIZONTAL] = 
	{
		// ���݈ʒu�̕\���o�[
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// �|�C���g�v���X�̐��i�w�i�j
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// ���C���R�[�X
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{3,3,3,3,3,3,3,4,4,4,3,3,3,3,3,3,3,3,3,5,5,5,3,3,3,3,3,3,3,3,3,3,4,4,3,5,5,3,6,3},
		{3,3,3,3,3,3,3,4,4,4,3,3,3,3,3,3,3,3,3,5,5,5,3,3,3,3,3,3,3,3,3,3,4,4,3,5,5,3,6,3},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// ���̕ϓN���Ȃ������̒n��
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	// ���[�X�p�t�B�[���h�̕\������
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		LOCATE(nLocateX, nLocateY++);

		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// �t�B�[���h�̗v�f�̕\��
			if(nRaceField[nVertical][nHorizontal] == BLOCK)				// �P�F�n��
			{
				COLOR(LIME);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == SLOPE)		// �Q�F��
			{
				COLOR(H_CYAN);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == COURSE)		// �R�F��
			{
				COLOR(WHITE);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == GOOD)			// �S�FGOOD��
			{
				COLOR(RED);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == VERYGOOD)		// �T�FVERYGOOD��
			{
				COLOR(H_RED);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == EXCELLENT)	// �U�FEXCELLENT��
			{
				COLOR(YELLOW);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_GOOD)		// �V�FGOOD��
			{
				COLOR(RED);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_VERYGOOD)	// �W�FVERYGOOD��
			{
				COLOR(H_RED);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_EXCELLENT)	// �X�FEXCELLENT��
			{
				COLOR(YELLOW);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == STAR)			// �P�O�F��(����)
			{
				COLOR(YELLOW);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == STAR +1)		// �P�P�F��(����)
			{
				COLOR(LIME);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == SPACE)		// �O�F��
			{
				BACKCOLOR(BLACK);
				printf("�@");
			}//if.fin
	
		}//forX.fin

		printf("\0");		// NULL

	}//forY.fin

	// �z��̐擪�A�h���X�������Ƃ���UpdatePlayer�ɓn��
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// 2�����z��̐擪����\���̓��̐�p�ϐ��Ɋi�[�i�O�{�z��P�Q�O�Ԓn�ڂ���j
			g_nField.nPosition[nVertical][nHorizontal] = nRaceField[nVertical][nHorizontal];
		}//forX.fin

	}//forY.fin

	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	void RaceField_160_199_and_520_559_and_680_719 ( void )
* ����:		void
* �߂�l:	�Ȃ�											���@��
* ����:		�ӂ��R�[�X�O�S�ƂP�R�ƂP�V�Ŏg�p				���@��
*			���[�X�R�[�X�P�U�O�`�P�X�X						������
*			���[�X�R�[�X�T�Q�O�`�T�T�X						�@�@��
*			���[�X�R�[�X�U�W�O�`�V�P�X						�@�@��
*******************************************************************************/
void RaceField_160_199_and_520_559_and_680_719 ( void )
{
	// �v���O�����X�^�[�g

	// 2�����z��Ŏg�p����ϐ��̐錾
	int nVertical;
	int nHorizontal;
	int nLocateX = ONE_INT;
	int nLocateY = ONE_INT;

	// 2�����z��̏����������i�v�f����25�~40��int�^2�����z���錾�j
	int nRaceField[MAX_VERTICAL][MAX_HORAIZONTAL] = 
	{
		// ���݈ʒu�̕\���o�[
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// �|�C���g�v���X�̐��i�w�i�j
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// ���C���R�[�X
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,6,3,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,5,3,3,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,5,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,3,3,3,4,4},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,3,3,3,4,4,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0},
		{0,0,0,0,0,3,3,3,3,3,3,5,3,3,0,0,0,0,0,0,0,0,9,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// ���̕ϓN���Ȃ������̒n��
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	
	// ���[�X�p�t�B�[���h�̕\������
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		LOCATE(nLocateX, nLocateY++);

		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// �t�B�[���h�̗v�f�̕\��
			if(nRaceField[nVertical][nHorizontal] == BLOCK)				// �P�F�n��
			{
				COLOR(LIME);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == SLOPE)		// �Q�F��
			{
				COLOR(H_CYAN);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == COURSE)		// �R�F��
			{
				COLOR(WHITE);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == GOOD)			// �S�FGOOD��
			{
				COLOR(RED);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == VERYGOOD)		// �T�FVERYGOOD��
			{
				COLOR(H_RED);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == EXCELLENT)	// �U�FEXCELLENT��
			{
				COLOR(YELLOW);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_GOOD)		// �V�FGOOD��
			{
				COLOR(RED);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_VERYGOOD)	// �W�FVERYGOOD��
			{
				COLOR(H_RED);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_EXCELLENT)	// �X�FEXCELLENT��
			{
				COLOR(YELLOW);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == STAR)			// �P�O�F��(����)
			{
				COLOR(YELLOW);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == STAR +1)		// �P�P�F��(����)
			{
				COLOR(LIME);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == SPACE)		// �O�F��
			{
				BACKCOLOR(BLACK);
				printf("�@");
			}//if.fin
	
		}//forX.fin

		printf("\0");		// NULL

	}//forY.fin

	// �z��̐擪�A�h���X�������Ƃ���UpdatePlayer�ɓn��
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// 2�����z��̐擪����\���̓��̐�p�ϐ��Ɋi�[�i�O�{�z��P�U�O�Ԓn�ڂ���j
			g_nField.nPosition[nVertical][nHorizontal] = nRaceField[nVertical][nHorizontal];
		}//forX.fin

	}//forY.fin

	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	void RaceField_200_239_and_400_439 ( void )
* ����:		void
* �߂�l:	�Ȃ�											������
* ����:		�x�e�n�Q�R�[�X�O�T�ƂP�O�Ŏg�p					��
*			���[�X�R�[�X�Q�O�O�`�Q�R�X						������
*			���[�X�R�[�X�S�O�O�`�T�R�X						�@�@��
*															������
*******************************************************************************/
void RaceField_200_239_and_400_439 ( void )
{
	// �v���O�����X�^�[�g

	// 2�����z��Ŏg�p����ϐ��̐錾
	int nVertical;
	int nHorizontal;
	int nLocateX = ONE_INT;
	int nLocateY = ONE_INT;

	// 2�����z��̏����������i�v�f����25�~40��int�^2�����z���錾�j
	int nRaceField[MAX_VERTICAL][MAX_HORAIZONTAL] = 
	{
		// ���݈ʒu�̕\���o�[
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// �|�C���g�v���X�̐��i�w�i�j
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// ���C���R�[�X
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,3,3,3,3,3,3,3,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,3,3,3,3,5,3,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,5,2,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,3,3,3,3,6,3,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,9,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,6,2,0},
		{0,0,0,0,0,0,0,0,0,0,0,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0,0,0,0,0,0,0,0,9,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// ���̕ϓN���Ȃ������̒n��
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	
	// ���[�X�p�t�B�[���h�̕\������
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		LOCATE(nLocateX, nLocateY++);

		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// �t�B�[���h�̗v�f�̕\��
			if(nRaceField[nVertical][nHorizontal] == BLOCK)				// �P�F�n��
			{
				COLOR(LIME);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == SLOPE)		// �Q�F��
			{
				COLOR(H_CYAN);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == COURSE)		// �R�F��
			{
				COLOR(WHITE);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == GOOD)			// �S�FGOOD��
			{
				COLOR(RED);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == VERYGOOD)		// �T�FVERYGOOD��
			{
				COLOR(H_RED);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == EXCELLENT)	// �U�FEXCELLENT��
			{
				COLOR(YELLOW);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_GOOD)		// �V�FGOOD��
			{
				COLOR(RED);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_VERYGOOD)	// �W�FVERYGOOD��
			{
				COLOR(H_RED);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_EXCELLENT)	// �X�FEXCELLENT��
			{
				COLOR(YELLOW);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == STAR)			// �P�O�F��(����)
			{
				COLOR(YELLOW);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == STAR +1)		// �P�P�F��(����)
			{
				COLOR(LIME);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == SPACE)		// �O�F��
			{
				BACKCOLOR(BLACK);
				printf("�@");
			}//if.fin
	
		}//forX.fin

		printf("\0");		// NULL

	}//forY.fin

	// �z��̐擪�A�h���X�������Ƃ���UpdatePlayer�ɓn��
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// 2�����z��̐擪����\���̓��̐�p�ϐ��Ɋi�[�i�O�{�z��Q�O�O�Ԓn�ڂ���j
			g_nField.nPosition[nVertical][nHorizontal] = nRaceField[nVertical][nHorizontal];
		}//forX.fin

	}//forY.fin

	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	void RaceField_240_279_and_560_599 ( void )
* ����:		void
* �߂�l:	�Ȃ�											������
* ����:		�����n�Q�R�[�X�O�U�ƂP�S�Ŏg�p					��
*			���[�X�R�[�X�Q�S�O�`�Q�V�X						������
*			���[�X�R�[�X�T�U�O�`�T�X�X						���@��
*															������
*******************************************************************************/
void RaceField_240_279_and_560_599 ( void )
{
	// �v���O�����X�^�[�g

	// 2�����z��Ŏg�p����ϐ��̐錾
	int nVertical;
	int nHorizontal;
	int nLocateX = ONE_INT;
	int nLocateY = ONE_INT;

	// 2�����z��̏����������i�v�f����25�~40��int�^2�����z���錾�j
	int nRaceField[MAX_VERTICAL][MAX_HORAIZONTAL] = 
	{
		// ���݈ʒu�̕\���o�[
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// �|�C���g�v���X�̐��i�w�i�j
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// ���C���R�[�X
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,3,3,3,3,3,3,3,4,4,3,5,3,6,3},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,3,3,3,3,3,3,3,3,4,4,3,5,3,6,3},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,3,3,3,3,3,3,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,0,0,2,4,4,3,5,3,6,3},
		{0,0,0,0,0,2,3,3,3,3,3,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,0,0,0,3,4,4,3,5,3,6,2},
		{0,0,0,0,0,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// ���̕ϓN���Ȃ������̒n��
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	
	// ���[�X�p�t�B�[���h�̕\������
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		LOCATE(nLocateX, nLocateY++);

		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// �t�B�[���h�̗v�f�̕\��
			if(nRaceField[nVertical][nHorizontal] == BLOCK)				// �P�F�n��
			{
				COLOR(LIME);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == SLOPE)		// �Q�F��
			{
				COLOR(H_CYAN);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == COURSE)		// �R�F��
			{
				COLOR(WHITE);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == GOOD)			// �S�FGOOD��
			{
				COLOR(RED);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == VERYGOOD)		// �T�FVERYGOOD��
			{
				COLOR(H_RED);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == EXCELLENT)	// �U�FEXCELLENT��
			{
				COLOR(YELLOW);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_GOOD)		// �V�FGOOD��
			{
				COLOR(RED);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_VERYGOOD)	// �W�FVERYGOOD��
			{
				COLOR(H_RED);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_EXCELLENT)	// �X�FEXCELLENT��
			{
				COLOR(YELLOW);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == STAR)			// �P�O�F��(����)
			{
				COLOR(YELLOW);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == STAR +1)		// �P�P�F��(����)
			{
				COLOR(LIME);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == SPACE)		// �O�F��
			{
				BACKCOLOR(BLACK);
				printf("�@");
			}//if.fin
	
		}//forX.fin

		printf("\0");		// NULL

	}//forY.fin

	// �z��̐擪�A�h���X�������Ƃ���UpdatePlayer�ɓn��
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// 2�����z��̐擪����\���̓��̐�p�ϐ��Ɋi�[�i�O�{�z��Q�S�O�Ԓn�ڂ���j
			g_nField.nPosition[nVertical][nHorizontal] = nRaceField[nVertical][nHorizontal];
		}//forX.fin

	}//forY.fin

	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	void RaceField_280_319_and_600_639 ( void )
* ����:		void
* �߂�l:	�Ȃ�											������
* ����:		�x�e�n�Q�R�[�X�O�V�ƂP�T�Ŏg�p					���@��
*			���[�X�R�[�X�Q�W�O�`�R�P�X						�@�@��
*			���[�X�R�[�X�U�O�O�`�U�R�X						�@�@��
*															�@�@��
*******************************************************************************/
void RaceField_280_319_and_600_639 ( void )
{
	// �v���O�����X�^�[�g

	// 2�����z��Ŏg�p����ϐ��̐錾
	int nVertical;
	int nHorizontal;
	int nLocateX = ONE_INT;
	int nLocateY = ONE_INT;

	// 2�����z��̏����������i�v�f����25�~40��int�^2�����z���錾�j
	int nRaceField[MAX_VERTICAL][MAX_HORAIZONTAL] = 
	{
		// ���݈ʒu�̕\���o�[
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// �|�C���g�v���X�̐��i�w�i�j
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// ���C���R�[�X
		{10,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,1,0,0,0,0,0,10},
		{10,0,0,1,1,1,1,1,1,0,1,0,1,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,1,0,0,1,0,0,0,0,0,10},
		{10,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,10},
		{10,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,10},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{3,3,3,3,3,3,3,4,4,4,3,3,3,3,3,3,3,3,3,5,5,5,3,3,3,3,3,3,3,3,3,3,4,4,3,5,5,3,6,3},
		{3,3,3,3,3,3,3,4,4,4,3,3,3,3,3,3,3,3,3,5,5,5,3,3,3,3,3,3,3,3,3,3,4,4,3,5,5,3,6,3},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// ���̕ϓN���Ȃ������̒n��
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	
	// ���[�X�p�t�B�[���h�̕\������
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		LOCATE(nLocateX, nLocateY++);

		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// �t�B�[���h�̗v�f�̕\��
			if(nRaceField[nVertical][nHorizontal] == BLOCK)				// �P�F�n��
			{
				COLOR(LIME);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == SLOPE)		// �Q�F��
			{
				COLOR(H_CYAN);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == COURSE)		// �R�F��
			{
				COLOR(WHITE);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == GOOD)			// �S�FGOOD��
			{
				COLOR(RED);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == VERYGOOD)		// �T�FVERYGOOD��
			{
				COLOR(H_RED);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == EXCELLENT)	// �U�FEXCELLENT��
			{
				COLOR(YELLOW);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_GOOD)		// �V�FGOOD��
			{
				COLOR(RED);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_VERYGOOD)	// �W�FVERYGOOD��
			{
				COLOR(H_RED);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_EXCELLENT)	// �X�FEXCELLENT��
			{
				COLOR(YELLOW);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == STAR)			// �P�O�F��(����)
			{
				COLOR(YELLOW);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == STAR +1)		// �P�P�F��(����)
			{
				COLOR(LIME);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == SPACE)		// �O�F��
			{
				BACKCOLOR(BLACK);
				printf("�@");
			}//if.fin
	
		}//forX.fin

		printf("\0");		// NULL

	}//forY.fin

	// �z��̐擪�A�h���X�������Ƃ���UpdatePlayer�ɓn��
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// 2�����z��̐擪����\���̓��̐�p�ϐ��Ɋi�[�i�O�{�z��Q�W�O�Ԓn�ڂ���j
			g_nField.nPosition[nVertical][nHorizontal] = nRaceField[nVertical][nHorizontal];
		}//forX.fin

	}//forY.fin

	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	void RaceField_720_739 ( void )
* ����:		void											������
* �߂�l:	�Ȃ�											���@��
* ����:		�X�p�[�g�|�C���g�n�R�[�X�P�W�Ŏg�p				������
*			���[�X�R�[�X�V�Q�O�`�V�R�X						���@��
*															������
*******************************************************************************/
void RaceField_720_739 ( void )
{
	// �v���O�����X�^�[�g

	// 2�����z��Ŏg�p����ϐ��̐錾
	int nVertical;
	int nHorizontal;
	int nLocateX = ONE_INT;
	int nLocateY = ONE_INT;

	// 2�����z��̏����������i�v�f����25�~40��int�^2�����z���錾�j
	int nRaceField[MAX_VERTICAL][MAX_HORAIZONTAL] = 
	{
		// ���݈ʒu�̕\���o�[
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// �|�C���g�v���X�̐��i�w�i�j
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// ���C���R�[�X
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,4,4,3,5,3,6,3},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,4,4,3,5,3,6,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,4,4,3,5,3,6,3},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,4,4,3,5,3,6,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		// ���̕ϓN���Ȃ������̒n��
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	
	// ���[�X�p�t�B�[���h�̕\������
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		LOCATE(nLocateX, nLocateY++);

		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// �t�B�[���h�̗v�f�̕\��
			if(nRaceField[nVertical][nHorizontal] == BLOCK)				// �P�F�n��
			{
				COLOR(LIME);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == SLOPE)		// �Q�F��
			{
				COLOR(H_CYAN);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == COURSE)		// �R�F��
			{
				COLOR(WHITE);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == GOOD)			// �S�FGOOD��
			{
				COLOR(RED);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == VERYGOOD)		// �T�FVERYGOOD��
			{
				COLOR(H_RED);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == EXCELLENT)	// �U�FEXCELLENT��
			{
				COLOR(YELLOW);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_GOOD)		// �V�FGOOD��
			{
				COLOR(RED);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_VERYGOOD)	// �W�FVERYGOOD��
			{
				COLOR(H_RED);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_EXCELLENT)	// �X�FEXCELLENT��
			{
				COLOR(YELLOW);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == STAR)			// �P�O�F��(����)
			{
				COLOR(YELLOW);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == STAR +1)		// �P�P�F��(����)
			{
				COLOR(LIME);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == SPACE)		// �O�F��
			{
				BACKCOLOR(BLACK);
				printf("�@");
			}//if.fin
	
		}//forX.fin

		printf("\0");		// NULL

	}//forY.fin

	// �z��̐擪�A�h���X�������Ƃ���UpdatePlayer�ɓn��
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// 2�����z��̐擪����\���̓��̐�p�ϐ��Ɋi�[�i�O�{�z��V�Q�O�Ԓn�ڂ���j
			g_nField.nPosition[nVertical][nHorizontal] = nRaceField[nVertical][nHorizontal];

		}//forX.fin

	}//forY.fin

	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	FIELD *GetField( void ):�i�n�ʏ��̌��J�j�֐�
* ����:		void
* �߂�l:	return &g_aField[ZERO_INT];
* ����:		�t�B�[���h���̌��J
*******************************************************************************/
FIELD *GetField( void )
{
	// �v���O�����X�^�[�g

	// �t�B�[���h���̒l��Ԃ�
	return &g_nField;
	
	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	void title( void )
* ����:		void
* �߂�l:	�Ȃ�
* ����:		�^�C�g��
*******************************************************************************/
void title( void )
{
	// �v���O�����X�^�[�g

	// 2�����z��Ŏg�p����ϐ��̐錾
	int nVertical;
	int nHorizontal;
	int nLocateX = ONE_INT;
	int nLocateY = ONE_INT;

	// 2�����z��̏����������i�v�f����25�~40��int�^2�����z���錾�j
	int nRaceField[MAX_VERTICAL][MAX_HORAIZONTAL] = 
	{
		// ���݈ʒu�̕\���o�[
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,3,3,3,3,3,3,6,0,0,0,3,0,0,5,3,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,6,0},
		{0,0,0,0,0,0,3,6,0,0,3,6,3,0,3,0,3,0,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,6,0},
		{0,0,0,0,0,3,6,0,0,3,6,0,0,3,6,3,5,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,6,0,0},
		{0,0,0,0,3,6,0,0,3,6,0,0,0,0,3,0,0,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0,0,0,3,6,0,0,0},
		{0,0,0,3,6,3,6,0,0,0,0,0,0,0,0,3,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,6,3,6,0,0},
		{0,0,3,6,0,0,3,6,0,0,0,0,0,0,0,0,3,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,6,0,0,3,6,0},
		{0,3,6,0,0,0,0,3,6,0,0,0,0,0,0,0,0,3,6,0,0,0,0,0,0,0,0,0,0,0,0,0,3,6,0,0,0,0,3,6},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,6,0,0,0,0,0,0,3,6,3,6,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,3,3,3,3,6,0,0,0,0,0,0,3,6,0,3,3,3,3,3,6,0,3,6,3,6,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,6,0,0,3,6,0,0,3,6,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,3,3,3,3,3,3,6,0,3,3,6,3,6,0,3,6,3,0,0,3,6,0,5,6,6,6,6,6,6,6,6,5,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,3,6,0,0,0,0,3,6,3,0,0,0,3,0,3,6,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,3,6,0,0,0,0,3,6,0,0,0,0,0,3,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,3,6,0,0,0,0,0,3,6,0,0,0,0,3,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,3,3,3,6,0,0,0,0,0,0,3,6,0,0,0,3,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,3,3,3,3,3,3,3,3,3,3,3,3},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,5,6,5,6,5,6,5,6,5,6,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,6,12,0,0,0,0,0,0,0,5,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,5,6,5,6,5,6,5,6,5,6,0,0,0,0},

		// ���̕ϓN���Ȃ������̒n��
		{1,4,1,5,1,6,1,1,1,1,1,1,1,4,1,5,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	// ���[�X�p�t�B�[���h�̕\������
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		LOCATE(nLocateX, nLocateY++);

		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// �t�B�[���h�̗v�f�̕\��
			if(nRaceField[nVertical][nHorizontal] == BLOCK)				// �P�F�n��
			{
				COLOR(LIME);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == SLOPE)		// �Q�F��
			{
				COLOR(H_CYAN);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == COURSE)		// �R�F��
			{
				COLOR(WHITE);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == GOOD)			// �S�FGOOD��
			{
				COLOR(RED);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == VERYGOOD)		// �T�FVERYGOOD��
			{
				COLOR(H_RED);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == EXCELLENT)	// �U�FEXCELLENT��
			{
				COLOR(YELLOW);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_GOOD)		// �V�FGOOD��
			{
				COLOR(RED);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_VERYGOOD)	// �W�FVERYGOOD��
			{
				COLOR(H_RED);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == S_EXCELLENT)	// �X�FEXCELLENT��
			{
				COLOR(YELLOW);
				printf("�^");
			}
			else if(nRaceField[nVertical][nHorizontal] == STAR)			// �P�O�F��(����)
			{
				COLOR(LIME);
				printf("�G���^�[�������܂ŗ��K���ł����I");
			}
			else if(nRaceField[nVertical][nHorizontal] == STAR +1)		// �P�P�F��(����)
			{
				COLOR(LIME);
				printf("�X�y�[�X�L�[�ŐԂ̃L�~���W�����v�����I");
			}
			else if(nRaceField[nVertical][nHorizontal] == STAR +2)		// �P�Q�F��(����)
			{
				COLOR(LIME);
				printf("�v���[�Y�G���^�[");
			}
			else if(nRaceField[nVertical][nHorizontal] == SPACE)		// �O�F��
			{
				BACKCOLOR(BLACK);
				printf("�@");
			}//if.fin
	
		}//forX.fin

		printf("\0");		// NULL

	}//forY.fin

	// �z��̐擪�A�h���X�������Ƃ���UpdatePlayer�ɓn��
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// 2�����z��̐擪����\���̓��̐�p�ϐ��Ɋi�[
			g_nField.nPosition[nVertical][nHorizontal] = nRaceField[nVertical][nHorizontal];
		}//forX.fin

	}//forY.fin
	
	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	void result( void )
* ����:		void
* �߂�l:	�Ȃ�
* ����:		���ʔ��\�`
*******************************************************************************/
void result( void )
{
	// �v���O�����X�^�[�g

	// 2�����z��Ŏg�p����ϐ��̐錾
	int nVertical;
	int nHorizontal;
	int nLocateX = ONE_INT;
	int nLocateY = ONE_INT;

	// 2�����z��̏����������i�v�f����25�~40��int�^2�����z���錾�j
	int nRaceField[MAX_VERTICAL][MAX_HORAIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0},
		{0,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0},
		{0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,1,0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0},
		{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
		{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
		{0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0},
		{0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
		{0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,1,0,0,0,0,1,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0},
		{0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0},
		{0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};
	
	// ���[�X�p�t�B�[���h�̕\������
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		LOCATE(nLocateX, nLocateY++);

		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// �t�B�[���h�̗v�f�̕\��
			if(nRaceField[nVertical][nHorizontal] == BLOCK)
			{
				COLOR(CYAN);
				printf("��");
			}
			else if(nRaceField[nVertical][nHorizontal] == 2)
			{
				BACKCOLOR(WHITE);
				printf("�q�{�^�����傢�������Ń^�C�g���ɖ߂�");
			}
			else if(nRaceField[nVertical][nHorizontal] == SPACE)
			{
				BACKCOLOR(BLACK);
				printf("�@");
			}//if.fin
	
		}//forX.fin

		printf("\0");		// NULL

	}//forY.fin


	// �v���O�����G���h
}

