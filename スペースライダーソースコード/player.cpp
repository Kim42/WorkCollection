/*******************************************************************************
* �^�C�g��:		�v���C���[�v���O����
* �v���O������:		player.cpp
* �쐬��:		CP11SATA  15  Kim Nakamura
* �쐬��:		2016/02/20
********************************************************************************
* �X�V����:		- 2016/02/20�@Kim Nakamura
*			- V1.00�@Initial Version
*				�E�t�B�[���h�̏�񂩂瓖���蔻��̎擾
*		2/29	�E�⓹�̓����蔻��̒ǉ�
*		3/01	�E���̉�������̒ǉ�
*******************************************************************************/
/*******************************************************************************
* scanf ��warning�h�~ 
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

/*******************************************************************************
* �C���N���[�h�t�@�C��
*  �K�v�ȏ��
*	�\���̂��߂̊�{�v�f
*	�v���C���[�̏��
*	�R���s���[�^�[���g�̏��
*	�t�B�[���h�̏��
*	�C�e���̏��

*******************************************************************************/
#include "main.h"
#include "player.h"
#include "computer.h"
#include "field.h"

/*******************************************************************************
* �}�N����`
*******************************************************************************/


/*******************************************************************************
* �\���̒�`
*******************************************************************************/


/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
#define GRAVITY         (0.1f)		// �v���C���[�̎󂯂�d��
#define ZERO_GRAVITY    (0.0f)		// �[���O�����B�e�B
#define GRAND           (24.0f)		// �n�ʂ̈ʒu
#define POSITION        (10)		// �����ʒu
#define JUMP            (0.8f)		// �W�����v��
#define MOVE_HOR        (0.05f)		// ���ړ��̈ړ���
#define SLOPEWAY        (0.5f)		// ��o��
#define ACCELERATOR_A   (1.0f)		// �����A�N�Z���F��
#define ACCELERATOR_B   (1.5f)		// �����A�N�Z���F��
#define ACCELERATOR_C   (2.0f)		// �����A�N�Z���F��
#define FLY_A           (0.3f)		// �����W�����v�ɔ����㏸�l�F��
#define FLY_B           (0.3f)		// �����W�����v�ɔ����㏸�l�F��
#define FLY_C           (0.3f)		// �����W�����v�ɔ����㏸�l�F��
#define INTERVAL        (25)		// �W�����v���Ă���̊Ԋu

#define POINT_STAR      (150)
#define POINT_G_STAR    (300)
#define POINT_GOOD      (50)
#define POINT_VERYGOOD  (100)
#define POINT_EXCELLENT (200)
#define POINT_1         (1000)
#define POINT_2         (800)
#define POINT_3         (500)
#define POINT_4         (300)
/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
// �w�b�_�[�t�@�C������v���C���[�\���̂̃O���[�o���錾
PLAYER g_player;

/*******************************************************************************
* �֐���:	void InitPlayer( void ):�i�������j�֐�
* ����:		void
* �߂�l:	�Ȃ�
* ����:		�v���C���[�̏����ݒ�
*******************************************************************************/
void InitPlayer( void )
{
	// �v���O�����X�^�[�g

	// �ϐ��錾 // �������ݒ�
	g_player.nPointGeter = ZERO_INT;	// �v���C���[�̃|�C���g��������
	g_player.fPosY   = GRAND;			// �v���C���[�̂x���̏����ʒu�̐ݒ�
	g_player.fPosX   = POSITION;		// �v���C���[�̂w���̏����ʒu�̐ݒ�
	g_player.fCountTimer = ZERO_INT;	// �^�C�}�[�̏�����
	g_player.bJump       = false;		// �W�����v���Ă��Ȃ����
	g_player.bPushButton = false;		// �{�^����������Ă��Ȃ����

	// �v���C���[�̏����\��
	COLOR(H_RED);
	LOCATE(g_player.fPosX, (int) g_player.fPosY -1);
	printf("��");
	LOCATE(g_player.fPosX, (int) g_player.fPosY);
	printf(">>");

	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	void UpdatePlayer( void ):�i�X�V�j�֐�
* ����:		void
* �߂�l:	�Ȃ�
* ����:		�v���C���[�̍X�V����
* �������e	��ɉE���ړ��A�����͂��邪��~�͂��Ȃ�
* 			�t�B�[���h����蓖���蔻�������A�ǔ���͗v��Ȃ�
*			�K�v�Ȕ���́A�W�����v��L�[�𗣂��܂Ŏ��̃W�����v�͂ł��Ȃ�
*			
*******************************************************************************/
void UpdatePlayer( void )
{
	// �v���O�����X�^�[�g

	// �\���̃|�C���^�ϐ��錾// �t�B�[���h�\���̂̕ϐ�
	FIELD *pField;
	COMPUTER *pComputer;

	// �t�B�[���h���̃R�s�[�̎擾
	pField = GetField();
	pComputer = GetComputer();

	// 2�����z��Ŏg�p����ϐ��̐錾
	int nVertical;
	int nHorizontal;
	int nLocateX = ONE_INT;
	int nLocateY = ONE_INT;

	// �O�̃|�W�V�����̎擾
	g_player.fPosXOld = g_player.fPosX;
	g_player.fPosYOld = g_player.fPosY;

	// ��ɉE�ړ��i�x�߁j
	g_player.fMoveX += MOVE_HOR;

	// �ړ��ʂ��|�W�V�����ɑ��
	g_player.fPosX += g_player.fMoveX;
	
	// �ݒ�Œᑬ�x�Ői�s�i�v���C���[�̈ړ��ʂ�ݒ葬�x�܂ŗ��Ƃ������j
	g_player.fMoveX += (MOVE_HOR - g_player.fMoveX) * SLOW;

	// 1��ʓ����[�v
	if(g_player.fPosX >= WALL_MAX )
	{
		// �G���^�[�L�[�����ꂽ��ʂ�
		if(pField -> bPlay == true)
		{
			// �C���N�������g
			pField -> nCnt++;
		}//if.fin

		g_player.fPosX = WALL_XMIN;
	}//if.fin

	// �]�����b�Z�[�W�̏���
	if(g_player.fMoveX <= 0.34f)
	{
		LOCATE(10,15); printf("         ");
	}//if.fin

	// �{�^����������Ă��Ȃ����Ƀv���C���[�^�C�}�[���O�̏ꍇ�A�W�����v����
	if( (g_player.bJump == false) && INP(PK_SP) && (g_player.fCountTimer == ZERO_INT) )
	{
		g_player.fMoveY = JUMP;				// �x�̈ړ��ʂɒl�̑��
		g_player.bJump  = true;				// �W�����v���Ă܂��I
		g_player.bPushButton = true;		// �{�^���������܂����I

		// 2�����z��t�B�[���h�̓����蔻��A�v���C���[�ʒu�Ƃ̓����蔻��
		for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
		{
			for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
			{
				// �v���C���[�̈ʒu���W�ƃt�B�[���h�̈ʒu���r��A���W�ʒu�ɂ���v�f�ԍ��ɂ��v�f�̊m�F
				if( ((int)g_player.fPosY == nVertical) && ( (int)(g_player.fPosX / 2 ) == nHorizontal) )
				{
					// �v�f�����������̏ꍇ�̏�����
					if(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == 0)
					{
						// �̗v�f�ԍ��S�FGOOD���̏�Ń{�^���t���O���������Ƃ�
						if((g_player.bJump == true) && (pField -> nPosition[nVertical][nHorizontal] == GOOD))
						{
							COLOR(RED);
							LOCATE(10,15); printf("GOOD");

							// ���[�X�J�n������L��
							if((pField -> bStart == true) || (pField ->bPlay == true))
							{
								// �|�C���g�̒ǉ�
								g_player.nPointGeter += POINT_GOOD;
							}//if.fin

							// �����ȉ��������Ĉړ��ʂ��|�W�V�����ɑ��
							g_player.fMoveX += ACCELERATOR_A;
							g_player.fPosX  += g_player.fMoveX;
							g_player.fMoveY = FLY_A;
						}//if.fin

						// �̗v�f�ԍ��T�FVERYGOOD���̏�Ń{�^���t���O�������Ă��鎞
						if((g_player.bJump == true) && (pField -> nPosition[nVertical][nHorizontal] == VERYGOOD))
						{
							COLOR(H_RED);
							LOCATE(10,15); printf("VERYGOOD");

							// ���[�X�J�n������L��
							if((pField -> bStart == true) || (pField ->bPlay == true))
							{
								// �|�C���g�̒ǉ�
								g_player.nPointGeter += POINT_VERYGOOD;
							}//if.fin

							// ���������Ĉړ��ʂ��|�W�V�����ɑ��
							g_player.fMoveX += ACCELERATOR_B;
							g_player.fPosX  += g_player.fMoveX;
							g_player.fMoveY = FLY_B;
						}//if.fin

						// �̗v�f�ԍ��U�FEXCELLENT���̏�Ń{�^���t���O�������Ă��鎞
						if((g_player.bJump == true) && (pField -> nPosition[nVertical][nHorizontal] == EXCELLENT))
						{
							COLOR(YELLOW);
							LOCATE(10,15); printf("EXCELLENT");

							// ���[�X�J�n������L��
							if((pField -> bStart == true) || (pField ->bPlay == true))
							{
								// �|�C���g�̒ǉ�
								g_player.nPointGeter += POINT_EXCELLENT;
							}//if.fin

							// �傫�����������Ĉړ��ʂ��|�W�V�����ɑ��
							g_player.fMoveX += ACCELERATOR_C;
							g_player.fPosX  += g_player.fMoveX;
							g_player.fMoveY = FLY_C;
						}//if.fin

						// �̗v�f�ԍ��V�FGOOD��̏�Ń{�^���t���O���������Ƃ�
						if((g_player.bJump == true) && (pField -> nPosition[nVertical][nHorizontal -1] == S_GOOD))
						{
							COLOR(RED);
							LOCATE(10,15); printf("GOOD");

							// ���[�X�J�n������L��
							if((pField -> bStart == true) || (pField ->bPlay == true))
							{
								// �|�C���g�̒ǉ�
								g_player.nPointGeter += POINT_GOOD;
							}//if.fin

							// �����ȉ��������Ĉړ��ʂ��|�W�V�����ɑ��
							g_player.fMoveX += ACCELERATOR_A;
							g_player.fPosX  += g_player.fMoveX;
							g_player.fMoveY = FLY_A;
						}//if.fin

						// �̗v�f�ԍ��W�FVERYGOOD��̏�Ń{�^���t���O�������Ă��鎞
						if((g_player.bJump == true) && (pField -> nPosition[nVertical][nHorizontal -1] == S_VERYGOOD))
						{
							COLOR(H_RED);
							LOCATE(10,15); printf("VERYGOOD");

							// ���[�X�J�n������L��
							if((pField -> bStart == true) || (pField ->bPlay == true))
							{
								// �|�C���g�̒ǉ�
								g_player.nPointGeter += POINT_VERYGOOD;
							}//if.fin

							// ���������Ĉړ��ʂ��|�W�V�����ɑ��
							g_player.fMoveX += ACCELERATOR_B;
							g_player.fPosX  += g_player.fMoveX;
							g_player.fMoveY = FLY_B;
						}//if.fin

						// �̗v�f�ԍ��X�FEXCELLENT��̏�Ń{�^���t���O�������Ă��鎞
						if((g_player.bJump == true) && (pField -> nPosition[nVertical][nHorizontal -1] == S_EXCELLENT))
						{
							COLOR(YELLOW);
							LOCATE(10,15); printf("EXCELLENT");

							// ���[�X�J�n������L��
							if((pField -> bStart == true) || (pField ->bPlay == true))
							{
								// �|�C���g�̒ǉ�
								g_player.nPointGeter += POINT_EXCELLENT;
							}//if.fin

							// �傫�����������Ĉړ��ʂ��|�W�V�����ɑ��
							g_player.fMoveX += ACCELERATOR_C;
							g_player.fPosX  += g_player.fMoveX;
							g_player.fMoveY = FLY_C;
						}//if.fin

					}//if.fin

				}//if.fin

			}//forX.fin

		}//forY.fin
	}
	else if(g_player.bPushButton == true)	// �{�^�����肪true�ł����
	{
		g_player.fCountTimer++;				// �t���[�������J�E���g
	}//if.fin

	// �v���C���[�̈ړ��ʂ��v���C���[�̃|�W�V�����ɑ��
	g_player.fPosY -= g_player.fMoveY;

	// �v���C���[�̎󂯂�d��
	g_player.fMoveY -= GRAVITY;

	// 2�����z��t�B�[���h�̓����蔻��A�v���C���[�ʒu�Ƃ̓����蔻��
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
	{
		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
		{
			// �v���C���[�̈ʒu���W�ƃt�B�[���h�̈ʒu���r��A���W�ʒu�ɂ���v�f�ԍ��ɂ��v�f�̊m�F
			if( ((int)g_player.fPosY == nVertical) && ((int)(g_player.fPosX / 2 ) == nHorizontal) )
			{
				// �v�f�����P�̏ꍇ�F�n�ʁA���ɂ߂荞�܂Ȃ��悤�ɂ���
				if(pField -> nPosition[nVertical][nHorizontal] == BLOCK)
				{
					g_player.fMoveY = ZERO_GRAVITY;				// �d�͂��O�ɂ���
					g_player.bJump  = false;					// �W�����v�t���O������

					// �J�E���^��INTERVAL�ɒB�������Ƀ{�^���t���O������
					if( (g_player.bPushButton == true) &&(g_player.fCountTimer > INTERVAL) )
					{
						g_player.bPushButton = false;			// �{�^���t���O������
						g_player.fCountTimer = ZERO_INT;		// �O�ɏ���������
					}//if.fin
				}//if.fin

				// �v�f�����Q�A�V�A�W�A�X�̏ꍇ�A��ł̎����㏸�ɉ�����̉�����
				if( (pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == SLOPE)      || 
					(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == S_GOOD)     || 
					(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == S_VERYGOOD) || 
					(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == S_EXCELLENT) )
				{
					g_player.fPosX += SLOPEWAY;					// �w�|�W���J��グ��
					g_player.fPosY -= SLOPEWAY;					// �x�|�W���J��グ��
					g_player.fMoveY = ZERO_GRAVITY;				// �d�͂��O�ɂ���
					g_player.bJump  = false;					// �W�����v�t���O������

					// �J�E���^��INTERVAL�ɒB�������Ƀ{�^���t���O������
					if( (g_player.bPushButton == true) && (g_player.fCountTimer > INTERVAL) )
					{
						g_player.bPushButton = false;			// �{�^���t���O������
						g_player.fCountTimer = ZERO_INT;		// �O�ɏ���������
					}//if.fin
				}//if.fin

				// �v�f�����R�A�S�A�T�A�U�̏ꍇ�̏�����
				if( (pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == COURSE)   || 
					(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == GOOD)     || 
					(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == VERYGOOD) || 
					(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == EXCELLENT) )
				{
					g_player.fPosY -= SLOPEWAY;					// �x�|�W���J��グ��
					g_player.fMoveY = ZERO_GRAVITY;				// �d�͂��O�ɂ���
					g_player.bJump  = false;					// �W�����v�t���O������

					// �J�E���^��INTERVAL�ɒB�������Ƀ{�^���t���O������
					if( (g_player.bPushButton == true) && (g_player.fCountTimer > INTERVAL) )
					{
						g_player.bPushButton = false;			// �{�^���t���O������
						g_player.fCountTimer = ZERO_INT;		// �O�ɏ���������
					}//if.fin
				}//if.fin

			}//if.fin

		}//forX.fin

	}//forY.fin

	// �߂荞�ݑO�̑O��ʒu�̍��W�̑��
	if(g_player.fPosY > GRAND)
	{
		g_player.fMoveY = ZERO_GRAVITY;				// �d�͂��O�ɂ���
		g_player.fPosY = GRAND;						// �n�ʂ̈ʒu�̒l�̑��
	}//if.fin

	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	void DrawPlayer( void ):�i�`��j�֐�
* ����:		void
* �߂�l:	�Ȃ�
* ����:		�v���C���[�̕`�揈��
*******************************************************************************/
void DrawPlayer( void )
{
	// �v���O�����X�^�[�g

	// �\���̃|�C���^�ϐ��錾
	FIELD *pField;
	COMPUTER *pComputer;
	
	// ���̃R�s�[�̎擾
	pField = GetField();
	pComputer = GetComputer();

	// �J�E���g���Q�O�𒴂�����`��I��
	if(pField -> nCnt < 20)
	{
		// �擾�|�C���g�̕`��// �����̈ʒu�Ƒ���̈ʒu�̌����}
		if((pField -> bStart == true) || (pField ->bPlay == true))
		{
			COLOR(GREEN);
			LOCATE(1,1); printf("�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P");
			LOCATE(1,3); printf("�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q");

			// ����
			COLOR(WHITE);
			LOCATE(pField -> nCnt *45, 2); printf("��");

			// ����
			COLOR(H_BLACK);
			LOCATE(pComputer -> nCnt *4, 2); printf("��");

			COLOR(PINK);
			LOCATE(3,5); printf("MY POINT:%5d ", g_player.nPointGeter);

			LOCATE(3,7); printf("�ԂƉ��F�̏�Ń^�C�~���O�ǂ��W�����v�I");
		}//if.fin

		// ���F�F����
		COLOR(H_RED);

		// �O��ʒu�̃N���A
		LOCATE(g_player.fPosXOld, (int) g_player.fPosYOld -1);
		printf("�@");
		LOCATE(g_player.fPosXOld, (int) g_player.fPosYOld);
		printf("�@");

		// ����ʒu�̕`��
		LOCATE(g_player.fPosX, (int) g_player.fPosY -1);
		printf("��");
		LOCATE(g_player.fPosX, (int) g_player.fPosY);
		printf(">>");
	}//if.fin

	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	void UninitPlayer( void ):�i�I���j�֐�
* ����:		void
* �߂�l:	�Ȃ�
* ����:		�v���C���[�̏I������
*******************************************************************************/
void UninitPlayer( void )
{
	// �v���O�����X�^�[�g

	

	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	PLAYER *GetPlayer( void ):�i�v���C���[���̌��J�j�֐�
* ����:		void
* �߂�l:	return &g_player;
* ����:		�v���C���[���̌��J
*******************************************************************************/
PLAYER *GetPlayer( void )
{
	// �v���O�����X�^�[�g

	// �v���C���[���̒l��Ԃ�
	return &g_player;
	
	// �v���O�����G���h
}
