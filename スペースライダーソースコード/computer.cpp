/*******************************************************************************
* �^�C�g��:		�R���s���[�^�[�v���O����
* �v���O������:		computer.cpp
* �쐬��:		CP11SATA  15  Kim Nakamura
* �쐬��:		2016/02/20
********************************************************************************
* �X�V����:		- 2016/02/20�@Kim Nakamura
*			- V1.00�@Initial Version
*******************************************************************************/
/*******************************************************************************
* scanf ��warning�h�~ 
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

/*******************************************************************************
* �C���N���[�h�t�@�C��
*  �K�v�ȏ��
*  	�\���̂��߂̊�{�v�f
*  	�R���s���[�^�[���g�̏��
*  	�t�B�[���h�̏��
*  	�A�C�e���̏��
*  	�v���C���[�̏��

*******************************************************************************/
#include "main.h"
#include "computer.h"
#include "field.h"
#include "player.h"

/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define GRAVITY         (0.1f)		// �v���C���[�̎󂯂�d��
#define ZERO_GRAVITY    (0.0f)		// �[���O�����B�e�B
#define GRAND           (24.0f)		// �n�ʂ̈ʒu
#define POSITION        (10)		// �����ʒu
#define JUMP            (0.8f)		// �W�����v��
#define MOVE_HOR        (0.05f)		// ���ړ��̈ړ���
#define SLOW            (0.15f)		// �C�ӂ̌�����
#define SLOPEWAY        (0.5f)		// ��o��
#define ACCELERATOR_A   (1.0f)		// �����A�N�Z���F��
#define ACCELERATOR_B   (1.5f)		// �����A�N�Z���F��
#define ACCELERATOR_C   (2.0f)		// �����A�N�Z���F��
#define FLY_A           (0.3f)		// �����W�����v�ɔ����㏸�l�F��
#define FLY_B           (0.3f)		// �����W�����v�ɔ����㏸�l�F��
#define FLY_C           (0.3f)		// �����W�����v�ɔ����㏸�l�F��
#define INTERVAL        (30)		// �W�����v���Ă���̊Ԋu


/*******************************************************************************
* �\���̒�`
*******************************************************************************/


/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/


/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
// �w�b�_�[�t�@�C������R���s���[�^�[�\���̂̃O���[�o���錾
COMPUTER g_computer[THREE];

/*******************************************************************************
* �֐���:	void InitComputer( void ):�i�������j�֐�
* ����:		void
* �߂�l:	�Ȃ�
* ����:		�R���s���[�^�[�̏����ݒ�
*******************************************************************************/
void InitComputer( void )
{
	// �v���O�����X�^�[�g

	// �ϐ��錾
	int nCntComputer;

	// �R���s���[�^�[�̐����̏�����
	for(nCntComputer = ZERO_INT; nCntComputer < THREE; nCntComputer++)
	{
		g_computer[nCntComputer].nCnt    = ZERO_INT;		// �ꏊ�m�F�J�E���^�̏�����
		g_computer[nCntComputer].fPosY   = GRAND;			// �R���s���[�^�[�̂x���̏����ʒu�̐ݒ�
		g_computer[nCntComputer].fPosX   = POSITION;		// �R���s���[�^�[�̂w���̏����ʒu�̐ݒ�
		g_computer[nCntComputer].fCountTimer = ZERO_INT;	// �^�C�}�[�̏�����
		g_computer[nCntComputer].bJump       = false;		// �W�����v���Ă��Ȃ����
		g_computer[nCntComputer].bPushButton = false;		// �{�^����������Ă��Ȃ����
		g_computer[nCntComputer].bUseCOM     = false;		// �܂����Ȃ����
		g_computer[nCntComputer].bGoal       = false;		// �S�[���t���O�������Ă���
	}//for.fin
	
	// �R���s���[�^�[�̐ݒu�i�w���A�x���A�^�C�v�j(�P�F�����A�Q�F�ӂ��A�R�F�ア)
	SetCom(7,21,1);
	SetCom(13,22,1);
	SetCom(20,23,2);

	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	void UpdateComputer( void ):�i�X�V�j�֐�
* ����:		void
* �߂�l:	�Ȃ�
* ����:		�R���s���[�^�[�̍X�V����
*******************************************************************************/
void UpdateComputer( void )
{
	// �v���O�����X�^�[�g

	// �\���̃|�C���^�ϐ��錾
	FIELD *pField;						// �t�B�[���h�\���̂̕ϐ�
	
	// �t�B�[���h���̃R�s�[�̎擾
	pField = GetField();

	// �ϐ��錾
	int nCntComputer;
	int nTheme;
	int nEmpty;

	// �R���s���[�^�[�̐����̏�����
	for(nCntComputer = ZERO_INT; nCntComputer < THREE; nCntComputer++)
	{
		// �R���s���[�^�[�̏������Ďg���Ă��鎞
		if(g_computer[nCntComputer].bUseCOM == true)
		{
			// 2�����z��Ŏg�p����ϐ��̐錾
			int nVertical;
			int nHorizontal;
			int nLocateX = ONE_INT;
			int nLocateY = ONE_INT;

			// �O�̃|�W�V�����̎擾
			g_computer[nCntComputer].fPosXOld = g_computer[nCntComputer].fPosX;
			g_computer[nCntComputer].fPosYOld = g_computer[nCntComputer].fPosY;

			// ��ɉE�ړ��i�x�߁j
			g_computer[nCntComputer].fMoveX += MOVE_HOR;

			// �ړ��ʂ��|�W�V�����ɑ��
			g_computer[nCntComputer].fPosX += g_computer[nCntComputer].fMoveX;
	
			// �ݒ�Œᑬ�x�Ői�s�i�v���C���[�̈ړ��ʂ�ݒ葬�x�܂ŗ��Ƃ������j
			g_computer[nCntComputer].fMoveX += (MOVE_HOR - g_computer[nCntComputer].fMoveX) * SLOW;

			// 1��ʓ����[�v
			if(g_computer[nCntComputer].fPosX >= WALL_MAX )
			{
				// �G���^�[�L�[�����ꂽ��ʂ�
				if(pField -> bPlay == true)
				{
					// �C���N�������g
					g_computer[nCntComputer].nCnt++;
				}//if.fin

				g_computer[nCntComputer].fPosX = WALL_XMIN;
			}//if.fin

			// ��ϐ��ɒl�̊i�[
			nEmpty = (int)g_computer[nCntComputer].fPosX;

			// ��ނɂ���ă^�C�v���Ⴂ
			if(g_computer[nCntComputer].nKind == 1)
			{
				nTheme = nEmpty % 1;					// �m��1/1
			}
			else if(g_computer[nCntComputer].nKind == 2)
			{
				nTheme = nEmpty %2;						// �m��1/2
			}
			else if(g_computer[nCntComputer].nKind == 3)
			{
				nTheme = nEmpty %3;						// �m��1/3
			}//if.fin

			// �����̃W�����v
			if( (g_computer[nCntComputer].bJump == false) && nTheme != ZERO_INT && (g_computer[nCntComputer].fCountTimer == ZERO_INT) )
			{
				g_computer[nCntComputer].fMoveY -= JUMP;
				g_computer[nCntComputer].bJump   = true;			// �W�����v���Ă܂��I
				g_computer[nCntComputer].bPushButton = true;		// �{�^���������܂����I
			}//if.fin

			// �W�����v�����Ă��Ȃ����Ƀ^�C�}�[���O�̏ꍇ�A�R���s���[�^�[�̃W�����v����
			if( (g_computer[nCntComputer].bJump == false) && nTheme == ZERO_INT && (g_computer[nCntComputer].fCountTimer == ZERO_INT) )
			{
				g_computer[nCntComputer].fMoveY -= JUMP;
				g_computer[nCntComputer].bJump   = true;			// �W�����v���Ă܂��I
				g_computer[nCntComputer].bPushButton = true;		// �{�^���������܂����I

				// 2�����z��t�B�[���h�̓����蔻��A�v���C���[�ʒu�Ƃ̓����蔻��
				for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
				{
					for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
					{
						// �v���C���[�̈ʒu���W�ƃt�B�[���h�̈ʒu���r��A���W�ʒu�ɂ���v�f�ԍ��ɂ��v�f�̊m�F
						if( ((int)g_computer[nCntComputer].fPosY == nVertical) && ( (int)(g_computer[nCntComputer].fPosX / 2 ) == nHorizontal) && 
							(nTheme == ZERO_INT) )
						{
							// �v�f�����������̏ꍇ�̏�����
							if(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == 0)
							{
								// �̗v�f�ԍ��S�FGOOD���̏�Ń{�^���t���O���������Ƃ�
								if((g_computer[nCntComputer].bJump == true) && (pField -> nPosition[nVertical][nHorizontal] == GOOD) && 
									(nTheme == ZERO_INT) )
								{
									// �����ȉ��������Ĉړ��ʂ��|�W�V�����ɑ��
									g_computer[nCntComputer].fMoveX += ACCELERATOR_A;
									g_computer[nCntComputer].fPosX += g_computer[nCntComputer].fMoveX;
									g_computer[nCntComputer].fMoveY -= FLY_A;
								}//if.fin

								// �̗v�f�ԍ��T�FVERYGOOD���̏�Ń{�^���t���O�������Ă��鎞
								if((g_computer[nCntComputer].bJump == true) && (pField -> nPosition[nVertical][nHorizontal] == VERYGOOD) && 
									(nTheme == ZERO_INT) )
								{
									// ���������Ĉړ��ʂ��|�W�V�����ɑ��
									g_computer[nCntComputer].fMoveX += ACCELERATOR_B;
									g_computer[nCntComputer].fPosX += g_computer[nCntComputer].fMoveX;
									g_computer[nCntComputer].fMoveY -= FLY_B;
								}//if.fin

								// �̗v�f�ԍ��U�FEXCELLENT���̏�Ń{�^���t���O�������Ă��鎞
								if((g_computer[nCntComputer].bJump == true) && (pField -> nPosition[nVertical][nHorizontal] == EXCELLENT) && 
									(nTheme == ZERO_INT) )
								{
									// �傫�����������Ĉړ��ʂ��|�W�V�����ɑ��
									g_computer[nCntComputer].fMoveX += ACCELERATOR_C;
									g_computer[nCntComputer].fPosX += g_computer[nCntComputer].fMoveX;
									g_computer[nCntComputer].fMoveY -= FLY_C;
								}//if.fin

								// �̗v�f�ԍ��V�FGOOD��̏�Ń{�^���t���O���������Ƃ�
								if((g_computer[nCntComputer].bJump == true) && (pField -> nPosition[nVertical][nHorizontal -1] == S_GOOD) && 
									(nTheme == ZERO_INT) )
								{
									// �����ȉ��������Ĉړ��ʂ��|�W�V�����ɑ��
									g_computer[nCntComputer].fMoveX += ACCELERATOR_A;
									g_computer[nCntComputer].fPosX += g_computer[nCntComputer].fMoveX;
									g_computer[nCntComputer].fMoveY -= FLY_A;
								}//if.fin

								// �̗v�f�ԍ��W�FVERYGOOD��̏�Ń{�^���t���O�������Ă��鎞
								if((g_computer[nCntComputer].bJump == true) && (pField -> nPosition[nVertical][nHorizontal -1] == S_VERYGOOD) && 
									(nTheme == ZERO_INT) )
								{
									// ���������Ĉړ��ʂ��|�W�V�����ɑ��
									g_computer[nCntComputer].fMoveX += ACCELERATOR_B;
									g_computer[nCntComputer].fPosX += g_computer[nCntComputer].fMoveX;
									g_computer[nCntComputer].fMoveY -= FLY_B;
								}//if.fin

								// �̗v�f�ԍ��X�FEXCELLENT��̏�Ń{�^���t���O�������Ă��鎞
								if((g_computer[nCntComputer].bJump == true) && (pField -> nPosition[nVertical][nHorizontal -1] == S_EXCELLENT) && 
									(nTheme == ZERO_INT) )
								{
									// �傫�����������Ĉړ��ʂ��|�W�V�����ɑ��
									g_computer[nCntComputer].fMoveX += ACCELERATOR_C;
									g_computer[nCntComputer].fPosX += g_computer[nCntComputer].fMoveX;
									g_computer[nCntComputer].fMoveY -= FLY_C;
								}//if.fin

							}//if.fin

						}//if.fin

					}//forX.fin

				}//forY.fin
			}
			else if(g_computer[nCntComputer].bPushButton == true)	// �{�^�����肪true�ł����
			{
				g_computer[nCntComputer].fCountTimer++;				// �t���[�������J�E���g
			}//if.fin

			// �v���C���[�̎󂯂�d��
			g_computer[nCntComputer].fMoveY += GRAVITY;

			// �v���C���[�̈ړ��ʂ��v���C���[�̃|�W�V�����ɑ��
			g_computer[nCntComputer].fPosY += g_computer[nCntComputer].fMoveY;

			// 2�����z��t�B�[���h�̓����蔻��A�v���C���[�ʒu�Ƃ̓����蔻��
			for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// �c���̃��[�v
			{
				for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// �����̃��[�v
				{
					// �v���C���[�̈ʒu���W�ƃt�B�[���h�̈ʒu���r��A���W�ʒu�ɂ���v�f�ԍ��ɂ��v�f�̊m�F
					if( ((int)g_computer[nCntComputer].fPosY == nVertical) && ((int)(g_computer[nCntComputer].fPosX / 2 ) == nHorizontal) )
					{
						// �v�f�����P�̏ꍇ�F�n�ʁA���ɂ߂荞�܂Ȃ��悤�ɂ���
						if(pField -> nPosition[nVertical][nHorizontal] == BLOCK)
						{
							g_computer[nCntComputer].fMoveY = ZERO_GRAVITY;				// �d�͂��O�ɂ���
							g_computer[nCntComputer].bJump  = false;					// �W�����v�t���O������

							// �J�E���^��INTERVAL�ɒB�������Ƀ{�^���t���O������
							if( (g_computer[nCntComputer].bPushButton == true) &&(g_computer[nCntComputer].fCountTimer > INTERVAL) )
							{
								g_computer[nCntComputer].bPushButton = false;			// �{�^���t���O������
								g_computer[nCntComputer].fCountTimer = ZERO_INT;		// �O�ɏ���������
							}//if.fin
						}//if.fin

						// �v�f�����Q�A�V�A�W�A�X�̏ꍇ�A��ł̎����㏸�ɉ�����̉�����
						if( (pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == SLOPE)      || 
							(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == S_GOOD)     || 
							(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == S_VERYGOOD) || 
							(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == S_EXCELLENT) )
						{
							g_computer[nCntComputer].fPosX += SLOPEWAY;					// �w�|�W���J��グ��
							g_computer[nCntComputer].fPosY -= SLOPEWAY;					// �x�|�W���J��グ��
							g_computer[nCntComputer].fMoveY = ZERO_GRAVITY;				// �d�͂��O�ɂ���
							g_computer[nCntComputer].bJump  = false;					// �W�����v�t���O������

							// �J�E���^��INTERVAL�ɒB�������Ƀ{�^���t���O������
							if( (g_computer[nCntComputer].bPushButton == true) && (g_computer[nCntComputer].fCountTimer > INTERVAL) )
							{
								g_computer[nCntComputer].bPushButton = false;			// �{�^���t���O������
								g_computer[nCntComputer].fCountTimer = ZERO_INT;		// �O�ɏ���������
							}//if.fin
						}//if.fin

						// �v�f�����R�A�S�A�T�A�U�̏ꍇ�̏�����
						if( (pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == COURSE)   || 
							(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == GOOD)     || 
							(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == VERYGOOD) || 
							(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == EXCELLENT) )
						{
							g_computer[nCntComputer].fPosY -= SLOPEWAY;					// �x�|�W���J��グ��
							g_computer[nCntComputer].fMoveY = ZERO_GRAVITY;				// �d�͂��O�ɂ���
							g_computer[nCntComputer].bJump  = false;					// �W�����v�t���O������

							// �J�E���^��INTERVAL�ɒB�������Ƀ{�^���t���O������
							if( (g_computer[nCntComputer].bPushButton == true) && (g_computer[nCntComputer].fCountTimer > INTERVAL) )
							{
								g_computer[nCntComputer].bPushButton = false;			// �{�^���t���O������
								g_computer[nCntComputer].fCountTimer = ZERO_INT;		// �O�ɏ���������
							}//if.fin
						}//if.fin

					}//if.fin

				}//forX.fin

			}//forY.fin

			// �߂荞�ݑO�̑O��ʒu�̍��W�̑��
			if(g_computer[nCntComputer].fPosY > GRAND)
			{
				g_computer[nCntComputer].fMoveY = ZERO_GRAVITY;				// �d�͂��O�ɂ���
				g_computer[nCntComputer].fPosY  = GRAND;					// �n�ʂ̈ʒu�̒l�̑��
			}//if.fin

		}//if.fin

	}//for.fin

	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	void DrawComputer( void ):�i�`��j�֐�
* ����:		void
* �߂�l:	�Ȃ�
* ����:		�R���s���[�^�[�̕`�揈��
*******************************************************************************/
void DrawComputer( void )
{
	// �v���O�����X�^�[�g

	// �ϐ��錾
	int nCntComputer;

	// �\���̃|�C���^�ϐ��錾// �t�B�[���h�\���̂̕ϐ�
	FIELD *pField;
	
	// �t�B�[���h���̃R�s�[�̎擾
	pField = GetField();

	// �R���s���[�^�[�̐����̕\������
	for(nCntComputer = ZERO_INT; nCntComputer < THREE; nCntComputer++)
	{
		// �R���s���[�^�[�̏������Ďg���Ă��鎞
		if(g_computer[nCntComputer].bUseCOM == true)
		{
			// �F����
			//if(nCntComputer == 0)
			//{
			//	COLOR(BLUE);
			//}
			//else if(nCntComputer == 1)
			//{
			//	COLOR(H_GREEN);
			//}
			//else if(nCntComputer == 2)
			//{
			//	COLOR(PINK);
			//}
			//else if(nCntComputer == 3)
			//{
			//	COLOR(CYAN);
			//}
			//else if(nCntComputer == 4)
			//{
			//	COLOR(H_BLACK);
			//}//if.fin

			COLOR(H_BLACK);

			// �v���[���[�ƈႤ�R�[�X�ɂ�����`�悵�Ȃ��{�J�E���^���Q�O�ȏ�̏ꍇ��
			if( (g_computer[nCntComputer].nCnt == pField -> nCnt) && (g_computer[nCntComputer].nCnt <= 19) )
			{
				// �O��ʒu�̏���
				LOCATE(g_computer[nCntComputer].fPosXOld, g_computer[nCntComputer].fPosYOld -1);
				printf("�@");
				LOCATE(g_computer[nCntComputer].fPosXOld, g_computer[nCntComputer].fPosYOld);
				printf("�@");

				// ����ʒu�̕\��
				LOCATE(g_computer[nCntComputer].fPosX, g_computer[nCntComputer].fPosY -1);
				printf("��");
				LOCATE(g_computer[nCntComputer].fPosX, g_computer[nCntComputer].fPosY);
				printf(">>");
			}//if.fin

		}//if.fin

	}//for.fin

	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	void UninitComputer( void ):�i�I���j�֐�
* ����:		void
* �߂�l:	�Ȃ�
* ����:		�R���s���[�^�[�̏I������
*******************************************************************************/
void UninitComputer( void )
{
	// �v���O�����X�^�[�g

	

	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	void SetCom( float fPosX, float fPosY, int nKind):�i�ݒ�j�֐�
* ����:		float fPosX, float fPosY, int nKind
* �߂�l:	�Ȃ�
* ����:		�R���s���[�^�[�̐ݒ菈��
*******************************************************************************/
void SetCom( float fPosX, float fPosY, int nKind)
{
	// �v���O�����X�^�[�g

	// �ϐ��錾
	int nCntComputer;

	// �R���s���[�^�[�̐����̕\������
	for(nCntComputer = ZERO_INT; nCntComputer < THREE; nCntComputer++)
	{
		// �\�����������t�B�[���h�̐ݒ�
		if(g_computer[nCntComputer].bUseCOM == false)
		{
			g_computer[nCntComputer].fPosX    = fPosX;	// �R���s���[�^�[�̂w���W�̐ݒ�
			g_computer[nCntComputer].fPosY    = fPosY;	// �R���s���[�^�[�̂x���W�̐ݒ�
			g_computer[nCntComputer].nKind    = nKind;	// �t�B�[���h�̈ړ����x
			g_computer[nCntComputer].bUseCOM  = true;	// �R���s���[�^�[���g���܂���A�s�[��

			break;
		}//if.fin
		
	}//for.fin

	// �v���O�����G���h
}

/*******************************************************************************
* �֐���:	FCOMPUTER *GetComputer( void ):�i�R���s���[�^�[�̏��̌��J�j�֐�
* ����:		void
* �߂�l:	return &g_computer[ZERO_INT];
* ����:		�R���s���[�^�[�̏��̌��J
*******************************************************************************/
COMPUTER *GetComputer( void )
{
	// �v���O�����X�^�[�g

	// �R���s���[�^�[�̏��̒l��Ԃ�
	return &g_computer[ZERO_INT];
	
	// �v���O�����G���h
}


