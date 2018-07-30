/*******************************************************************************
* �^�C�g��:		�l�[���o�g���[�v���O����
* �v���O������:		NAME_BATTLER.cpp
* �쐬��:		CP11SATA  15  Kim Nakamura
* �쐬��:		2015/12/23
********************************************************************************
* �X�V����:		- 2016/01/14�@Kim Nakamura�@Kim Nakamura
*			- V1.03�@Initial Version
*******************************************************************************/
/*******************************************************************************
* scanf ��warning�h�~ 
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include "CScreen.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define ZERO                  (0)		// ���[��[
#define ONE                   (1)		// �����I
#define HANDRET               (100)		// �n���h���b�g
#define MAX_MOJI              (8)		// �ő啶����
#define MIN_MOJI              (3)		// �ŏ�������
#define NUM_STATUS_A          (0.2)		// �X�e�C�^�X�ω�(0.2)
#define NUM_STATUS_B          (0.3)		// �X�e�C�^�X�ω�(0.3)
#define NUM_STATUS_C          (0.5)		// �X�e�C�^�X�ω�(0.5)
#define NUM_STATUS_D          (0.7)		// �X�e�C�^�X�ω�(0.7)

// �x�[�X�X�e�C�^�X��`
#define BASE_LIFE             (600)		// �x�[�X�̗͒l
#define BASE_MAGIC            (30)		// �x�[�X���͒l
#define BASE_ATTACK           (90)		// �x�[�X�U����
#define BASE_DEFENSE          (30)		// �x�[�X�����
#define BASE_AVOIDANCE        (1)		// �x�[�X���l

// �h���L�[�̏����ʒu
#define VERTICAL_DORAKI       (3)		// �c��
#define HORIZONTAL_DORAKI     (23)		// ����

// �X���C���R�����g��
#define NUM_UEKARA            (19)		// �c��
#define NUM_YOKOKARA          (17)		// ����

/*******************************************************************************
* �\���̒�`
*******************************************************************************/
typedef struct
{
	char  aName[8];					// ���O
	int  nLife;						// �̗͒l
	int  nMagic;					// ���͒l
	int  nAttack;					// �U���l
	int  nDefense;					// ����l
	int  nAvoidance;				// ���l

}PLAYER;								// �ϐ��^ �v���C���[

typedef struct
{
	int  nLife;							// �̗͒l
	int  nMagic;						// ���͒l
	int  nAttack;						// �U���l
	int  nDefense;						// ����l
	int  nAvoidance;					// ���l

}INITIAL;								// �v���C���[�̏����l�i�[

typedef struct
{
	char aName[8];						// ���O
	int  nLife;							// �̗͒l
	int  nMagic;						// ���͒l
	int  nAttack;						// �U���l
	int  nDefense;						// ����l
	int  nAvoidance;					// ���l

}ENEMY;								// �ϐ��^ �G

/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
int  title( void );												// �^�C�g���֐�
void Soulrink(void);											// �\�E�������N�^�C�g���֐�
void Soulrink2(void);											// �\�E�������N�^�C�g��2�֐�

int  CompetitionInput( PLAYER *pPlayer, ENEMY *pEnemy);			// Competition�p�f�[�^���͊֐�
int  Output( PLAYER *pPlayer, INITIAL *pInitial, ENEMY *pEnemy);	// �f�[�^�o�͊֐�

int Cursor( void );												// �J�[�\���ړ��֐�
int SkillCursor( void );										// �X�L���J�[�\���ړ��֐�
void Enter( void );												// �v���[�Y�G���^�[�֐�

// �X���C���A�j���[�V���� //
void Suraim( void );											// �X���C���֐�
void Suraim2( void );											// �X���C��2�֐�
void SuraimMove( void );										// �����X���C���֐�

void MetalSuraim( void );										// ���^���X���C���֐�
void MetalSuraim2( void );										// ���^���X���C��2�֐�
void MetalSuraimMove( void );									// �������^���X���C���֐�

void ButiSuraim( void );										// �Ԃ��X���C���֐�
void ButiSuraim2( void );										// �Ԃ��X���C��2�֐�
void ButiSuraimMove( void );									// �����Ԃ��X���C���֐�

void SuraimDark( void );										// �X���C���_�[�N�֐�
void SuraimDark2( void );										// �X���C���_�[�N2�֐�
void SuraimDarkMove( void );									// �����X���C���_�[�N�֐�

int SuraimRink( int nWarpiru );									// �X���C�������N�֐�
int SuraimMoveStatus     ( PLAYER *pPlayer, INITIAL *pInitial, ENEMY *pEnemy);	// �����X���C�� + Status�֐�
int MetalSuraimMoveStatus( PLAYER *pPlayer, INITIAL *pInitial, ENEMY *pEnemy);	// �������^���X���C�� + Status�֐�
int ButiSuraimMoveStatus ( PLAYER *pPlayer, INITIAL *pInitial, ENEMY *pEnemy);	// �����Ԃ��X���C�� + Status�֐�

// �h���L�[�A�j���[�V���� //
void Doraki( void );											// �h���L�[�֐�
void Doraki2( void );											// �h���L�[2�֐�
void DorakiMa( void );											// �h���L�[�}�֐�
void DorakiMa2( void );											// �h���L�[�}2�֐�
void TahoDoraki( void );										// �^�z�h���L�[�֐�
void TahoDoraki2( void );										// �^�z�h���L�[2�֐�

// �A�[�g //
void StatusFrame( int nColor );									// �X�e�C�^�X�g�֐�
void Mario( void );												// �h�b�g�}���I�֐�

// �o�g����p //
void BattleFrame(  int nFreamCloor, int nFreamBackCloor );		// �o�g���t���[���֐�
void Player     ( PLAYER *pPlayer, ENEMY *pEnemy, int nAction, int nMytern );						// �v���C���[�̍s��
void Enemy      ( PLAYER *pPlayer, ENEMY *pEnemy, int nAction, int nMytern, int nDorakiIllusion);	// �G�l�~�[�̍s��
void ComentReset( void );										// �R�����g�����Z�b�g�֐�
void Status(PLAYER *pPlayer);									// �X�e�C�^�X�\���֐�
void Name(ENEMY *pEnemy);										// ���O�݂̂̕\���֐�
int  Order( PLAYER *pPlayer, ENEMY *pEnemy );					// ���Ԍ��ߊ֐�
int  FrameColor( PLAYER *pPlayer);								// �t���[���J���[
int  Judge( PLAYER *pPlayer, ENEMY *pEnemy);					// ���s����֐�
int  DorakiIllusion( ENEMY *pEnemy );							// �h���L�[�ω��֐�
void Ending(PLAYER *pPlayer, ENEMY *pEnemy, int nJudge, int nWarpiru, int nTurnCount);		// �G���f�B���O�֐�

// �o�g���G�t�F�N�g //
void Koromaku( void );											// �����֐�
void BlackNormalEffect( void );									// �u���b�N�G�t�F�N�g�֐�
void WhiteNormalEffect( void );									// �z���C�g�G�t�F�N�g�֐�
void BarunDiveEffect( void );									// �o�����_�C�u�G�t�F�N�g�֐�
void SuraDragunEffect( void );									// �X���h���O�[���G�t�F�N�g�֐�
void BrushEffect( void );										// �u���b�V���G�t�F�N�g�֐�
void AnkouDanEffect( void );									// �Ì��e�G�t�F�N�g�֐�
void MetalStarEffect( void );									// ���^���X�^�[�G�t�F�N�g�֐�
void GurabiDonEffect( void );									// �O���r�h���G�t�F�N�g�֐�
void Joshoffect( void );										// �㏸�G�t�F�N�g�֐�
void KifukuEffect( void );										// �񕜃G�t�F�N�g�֐�

// �����X�^�[�̍s�� //
int  Akira  ( PLAYER *pPlayer );								// �����[��̍s���֐�
int  Doni   ( PLAYER *pPlayer );								// �h���E�C�̍s���֐�
int  Adabuti( PLAYER *pPlayer );								// �A�_�Ԃ��̍s���֐�
int  BattleDoraki( ENEMY *pEnemy);								// �h���L�[�̍s���֐�
int  BattleDorakiMa( void );									// �h���L�[�}�̍s���֐�
int  BattleTahoDoraki( void );									// �^�z�h���L�[�̍s���֐�

// �ő�l�A�ŏ��l�̗����̐��� //
int  GetRandom(int nMin,int nMax);								//�����_���Ȑ����̍ő�l�A�ŏ��l�̕ϐ�

// ���y�[�W�O�ɃA�j���[�V�������[�v //
void NormalWarp( int nWarpiru );								// �ʏ펞���[�v

// ����
void SoulRinkDescription( int nWarpiru );						// �\�E�������N�̐����֐�
void Manual( int nWarpiru );									// �S�̐����֐�

/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/

/*******************************************************************************
 �֐���:	int main( void )
 ����:		void
 �߂�l:	����I��: int�^�� 0
 ����:		
*******************************************************************************/
int main( void )
{
	//// �v���O�����J�n �ϐ��錾 ////
	PLAYER  aPlayer[ONE];										// �v���C���[�̕ϐ�
	INITIAL aInitial[ONE];										// �����l�i�[�̕ϐ�
	ENEMY   aEnemy[ONE];										// �G�l�~�[�̕ϐ�
	int nkey = ZERO;											// �G���^�[���[�v�Ɏg�p
	int nSuraimSelect = ZERO;									// �o�g���O�̃X���C���̎���
	int nSelect = ZERO;											// ���[�h�̑I��
	int nVertical = 9;											// �c��
	int nHorizontal = 27;										// ����
	int nFreamCloor = WHITE;									// �o�g���p�t���[���̒��F
	int nFreamBackCloor = BLACK;								// �o�g���p�t���[���̔w�i���F
	int nMytern = ZERO;											// �����̍s������Ɏg�p
	int nAction = ZERO;											// �s������Ɏg�p
	int nResult = ZERO;											// �_���[�W�i�[
	int nDamage  = ZERO;										// �G�l�~�[�̃_���[�W�i�[
	int nOrder = ZERO;											// ���Ԍ���
	int nJudge = ZERO;											// ���s����
	int nDorakiIllusion = ZERO;									// �h���L�[�ω�
	int nColor = ZERO;											// �t���[���J���[����
	int nTheme = ZERO;											// �Ȍ���
	int nWarpiru;												// ���[�v��ʂ��Ȃ����܂����H
	int nTurnCount = ZERO;										// �o�߃^�[���̃J�E���g

	// MP3 �p�i�[�ϐ��錾 //
	int nMP3Handle = ZERO;
	
	LOCATE(25,10);
	printf("���X���[�h��ʓI�̂�����܂����Ȃ����܂����H");
	LOCATE(26,11);
	printf("�P�F�Ȃ���");
	LOCATE(26,12);
	printf("�Q�F�̂����Ă���");
	LOCATE(26,13);
	printf("��");
	LOCATE(28,13);
	scanf("%d", &nWarpiru);

	CUROFF();													// �J�[�\��������

	CLS(WHITE,BLACK);											// ��ʂ𕶎������A�w�i�����ɂ���B

	// [ EXIT ]���������܂ŃG���h���X�I�I�I�I�I�I�I
	do
	{
		// �Q�[���̃e�[�}�� //
		nMP3Handle = OPENMP3("GameTheme.mp3");					// �I�[�v�� & ������
		PLAYMP3(nMP3Handle, 1);									// �J��Ԃ��Đ�

		//// �Q�[���X�^�[�g ////
		nSelect = title();										// �^�C�g��
		NormalWarp( nWarpiru );									// �ʏ펞���[�v

		// �^�C�g����胂�[�h�̑I�� //
		switch(nSelect)
		{
			case 0x61:				// 1P Competition���[�h
				
				CompetitionInput( &aPlayer[ZERO], &aEnemy[ZERO]);			// ���O����X�e�C�^�X�֕ϊ�

				NormalWarp( nWarpiru );										// �ʏ펞���[�v

				Output( &aPlayer[ZERO], &aInitial[ZERO], &aEnemy[ZERO]);	// �X�e�C�^�X�̕\��

				NormalWarp( nWarpiru );										// �ʏ펞���[�v

				nSuraimSelect = SuraimRink(nWarpiru );						//�X���C�������N
				
				// �X���C���̑I��(�����[��/�h���E�C/�A�_�Ԃ�) // ���߂�܂Ń��[�v
				while(1)
				{
					if(nSuraimSelect == 1)
					{
						// �����[���I�Ԃ��ύX�O�̃X�e�C�^�X�Ŏn�߂邩
						KEYCLEAR();											// �O�̂��߃L�[�{�[�h������������
						system("cls");										// ��ʂ̃N���A
						INKEY(nSuraimSelect);								// �����L�[��������Ă�����ϐ��ɒl����͂���
						nSuraimSelect = SuraimMoveStatus( &aPlayer[ZERO], &aInitial[ZERO], &aEnemy[ZERO]);

						if(nSuraimSelect == 0x61)							// [ a ]��I�������ꍇ
						{
							nSuraimSelect = 3;								// �h���E�C�̃y�[�W��
							continue;
						}
						else if(nSuraimSelect == 0x64)						// [ d ]��I�������ꍇ
						{
							nSuraimSelect = 2;								// �A�_�Ԃ��̃y�[�W��
							continue;
						}
						else if(nSuraimSelect == 0x6f || nSuraimSelect == 0x78)
						{
							nSuraimSelect = 1;								// �����[��Ŏn�߂�
							break;
						}//if.fin
					}
					else if(nSuraimSelect == 2)
					{
						// �A�_�Ԃ���I�Ԃ��ύX�O�̃X�e�C�^�X�Ŏn�߂邩
						KEYCLEAR();											// �O�̂��߃L�[�{�[�h������������
						system("cls");										// ��ʂ̃N���A
						nSuraimSelect = ButiSuraimMoveStatus( &aPlayer[ZERO], &aInitial[ZERO], &aEnemy[ZERO]);

						if(nSuraimSelect == 0x61)							// [ a ]��I�������ꍇ
						{
							nSuraimSelect = 1;								// �����[��̃y�[�W��
							continue;
						}
						else if(nSuraimSelect == 0x64)						// [ d ]��I�������ꍇ
						{
							nSuraimSelect = 3;								// �h���E�C�̃y�[�W��
							continue;
						}
						else if(nSuraimSelect == 0x6f || nSuraimSelect == 0x78)
						{
							nSuraimSelect = 2;								// �A�_�Ԃ��Ŏn�߂�
							break;
						}//if.fin
					}
					else if(nSuraimSelect == 3)
					{
						// �h���E�C��I�Ԃ��ύX�O�̃X�e�C�^�X�Ŏn�߂邩
						KEYCLEAR();											// �O�̂��߃L�[�{�[�h������������
						system("cls");										// ��ʂ̃N���A
						nSuraimSelect = MetalSuraimMoveStatus( &aPlayer[ZERO], &aInitial[ZERO], &aEnemy[ZERO]);

						if(nSuraimSelect == 0x61)							// [ a ]��I�������ꍇ
						{
							nSuraimSelect = 2;								// �A�_�Ԃ��̃y�[�W��
							continue;
						}
						else if(nSuraimSelect == 0x64)						// [ d ]��I�������ꍇ
						{
							nSuraimSelect = 1;								// �����[��̃y�[�W��
							continue;
						}
						else if(nSuraimSelect == 0x6f || nSuraimSelect == 0x78)
						{
							nSuraimSelect = 3;								// �h���E�C�Ŏn�߂�
							break;
						}//if.fin
					}//if.fin
				}// while.fin												// �X���C�����߃��[�v

				NormalWarp( nWarpiru );										// ���[�v

				CLOSEMP3(nMP3Handle);										// ��~ & �N���[�Y

				//�������������
				srand(( unsigned ) time( NULL ));
				nTheme = rand() %3;							// �m��1/4

				// �����_�����肷��a�f�l
				if(nTheme == ZERO)
				{
					// �a�f�l�Đ�
					nMP3Handle = OPENMP3("Fighting Spirit.mp3");			// �I�[�v�� & ������
					PLAYMP3(nMP3Handle,1);									// �J��Ԃ��Đ�
				}
				else if(nTheme == 1)
				{
					// �a�f�l�Đ�
					nMP3Handle = OPENMP3("Dragon_Ball_Z.mp3");				// �I�[�v�� & ������
					PLAYMP3(nMP3Handle,1);									// �J��Ԃ��Đ�
				}
				else if(nTheme == 2)
				{
					// �a�f�l�Đ�
					nMP3Handle = OPENMP3("DQ7.mp3");						// �I�[�v�� & ������
					PLAYMP3(nMP3Handle,1);									// �J��Ԃ��Đ�
				}
				
				// ��������o�g�������[�[�[�[�Ɓ[�[�[�I�I�I //
				BattleFrame( nFreamCloor, nFreamBackCloor );				// �o�g���p�t���[���̕\��
				Status(&aPlayer[ZERO]);										// �X�e�C�^�X�̕\��

				Doraki();													// �h���L�[�̕\��
				Name(&aEnemy[ZERO]);										// �G�l�~�[�l�[��

				Enter();													// �v���[�Y�G���^�[

				nTurnCount = ZERO;											// �^�[���J�E���g���̏�����

				// �o�g�� �����[�[�[�[�Ɓ[�[�[�I�I�I // ���^�[���m���ŁA��𗦂̉� //
				while(1)
				{
					// �^�[���J�E���g
					nTurnCount++;

					COLOR(WHITE, BLACK);
					LOCATE(3,17);
					printf("�k %d �^�[���ځl", nTurnCount);

					// �����ɂ���ăh���L�[�̕ω�
					nDorakiIllusion = DorakiIllusion( &aEnemy[ZERO] );		// �h���L�[�̕ω�

					if(nDorakiIllusion == 1)								// �̗͂� 500 �ȏ�̏ꍇ
					{
						Doraki();											// �h���L�[�ɕω�
						nAction = BattleDoraki(&aEnemy[ZERO]);				// �h���L�[�̍s��
					}
					else if(nDorakiIllusion == 2)							// �̗͂� 499 �ȏ�̏ꍇ
					{
						TahoDoraki();										// �^�z�h���L�[�ɕω�
						nAction = BattleTahoDoraki();						// �^�z�h���L�[�̍s��
					}
					else if(nDorakiIllusion == 3)							// �̗͂� 300 �����̏ꍇ
					{
						DorakiMa();											// �h���L�[�}�ɕω�
						nAction = BattleDorakiMa();							// �h���L�[�}�̍s��
					}//if.fin

					LOCATE(18,20);
					COLOR(WHITE,BLACK);
					printf("�R�}���h����͂��Ă�������...");
					LOCATE(18,21);
					printf("�k�v�F���l�@�k�r�F���l");

					// �g�p����X���C���̃X�L���g�p
					if(nSuraimSelect == 1)									// �����[��
					{
						nMytern = Akira(&aPlayer[ZERO]);					// �֐��őI�������l�̑��

					}
					else if(nSuraimSelect == 3)								// �h���E�C
					{
						nMytern = Doni(&aPlayer[ZERO]);						// �֐��őI�������l�̑��
					}
					else if(nSuraimSelect == 2)								// �A�_�Ԃ�
					{
						nMytern = Adabuti(&aPlayer[ZERO]);					// �֐��őI�������l�̑��
					}//if.fin

					nOrder = Order( &aPlayer[ZERO], &aEnemy[ZERO] );		// ���Ԍ���

					Sleep(700);												// �C���^�[�o��0.7�b

					// ���l�̍���������搧 //
					if(nOrder == ONE)										// �v���C���[�̐搧 //
					{
						LOCATE(17,19);
						printf("�v���C���[�̐搧");

						Player( &aPlayer[ZERO], &aEnemy[ZERO], nAction, nMytern );// �v���C���[�̍s��
						Status(&aPlayer[ZERO]);								// ��ʂ̍X�V
						BlackNormalEffect();								// �u���b�N�G�t�F�N�g

						// ���s����
						nJudge = Judge( &aPlayer[ZERO], &aEnemy[ZERO]);

						if(nJudge == ONE || nJudge == ZERO)
						{
							CLOSEMP3(nMP3Handle);								// ��~ & �N���[�Y
							// ���[�v����
							break;
						}//if.fin

						Enemy( &aPlayer[ZERO], &aEnemy[ZERO] , nAction, nMytern, nDorakiIllusion);// �G�l�~�[�̍s��
						Status(&aPlayer[ZERO]);								// ��ʂ̍X�V
						
					}
					else if(nOrder == ZERO)									// �G�l�~�[�̐搧 //
					{
						LOCATE(17,19);
						printf("�G�l�~�[�̐搧");

						Enemy( &aPlayer[ZERO], &aEnemy[ZERO] , nAction, nMytern, nDorakiIllusion);// �G�l�~�[�̍s��
						Status(&aPlayer[ZERO]);								// ��ʂ̍X�V

						// ���s����
						nJudge = Judge( &aPlayer[ZERO], &aEnemy[ZERO]);

						if(nJudge == ONE || nJudge == ZERO)
						{
							CLOSEMP3(nMP3Handle);								// ��~ & �N���[�Y
							// ���[�v����
							break;
						}//if.fin

						Player( &aPlayer[ZERO], &aEnemy[ZERO] , nAction, nMytern );// �v���C���[�̍s��
						Status(&aPlayer[ZERO]);								// ��ʂ̍X�V
						BlackNormalEffect();								// �u���b�N�G�t�F�N�g

					}//if.fin

					// ���s���� //////////////////////////////////////////////
					nColor = FrameColor( &aPlayer[ZERO]);					// �������Œ��F

					if(nColor == ZERO)										// �v���C���[�̗̑͂�400�ȏ�̏ꍇ
					{
						nFreamCloor = WHITE;								// �o�g���p�t���[���̒��F�F��
					}
					else if(nColor == 1)									// �v���C���[�̗̑͂�399�ȉ��̏ꍇ
					{
						nFreamCloor = YELLOW;								// �o�g���p�t���[���̒��F�F���F
					}
					else if(nColor == 2)									// �v���C���[�̗̑͂�200�ȉ��̏ꍇ
					{
						nFreamCloor = H_RED;								// �o�g���p�t���[���̒��F�F��
					}//if.fin

					nJudge = Judge( &aPlayer[ZERO], &aEnemy[ZERO]);			// ���s����

					if(nJudge == ONE || nJudge == ZERO)
					{
						CLOSEMP3(nMP3Handle);								// ��~ & �N���[�Y
						// ���[�v����
						break;
					}//if.fin

				}//while.fin												// �o�g�����[�v

				// �G���f�B���O //
				Ending(&aPlayer[ZERO], &aEnemy[ZERO], nJudge, nWarpiru, nTurnCount);

				break;

			case 0x73:						// �S�̐���

				Manual(nWarpiru);			// �v���[����ɂ������Ă̊Ȍ��Ȑ���
				break;

			case 0x64:						// �I��

				CLS(WHITE,BLACK);

				COLOR(LIME);
				LOCATE(33,12);
				printf("  See You Again !");

				while(1)
				{
					COLOR(WHITE,LIME);
					LOCATE(33,14);
					printf("�` Please Enter �`");
					 WAIT(300);						// 0.3sec�̎��ԑ҂� 
					INKEY(nkey);					// �����L�[��������Ă�����ϐ��ɒl����͂��� 
					if (nkey == 0xd) break;			// ���������ꂽ��I������ 

					COLOR(LIME,H_CYAN);
					LOCATE(33,14);
					printf("�` Please Enter �`");
					WAIT(300);						// 0.3sec�̎��ԑ҂� 
					INKEY(nkey);					// �����L�[��������Ă�����ϐ��ɒl����͂��� 
					if (nkey == 0xd) break;			// ���������ꂽ��I������ 
				}
				break;

		}//switch.fin

		CLOSEMP3(nMP3Handle);						// ��~ & �N���[�Y

	}while(nSelect != 0x64);		// [ d ]���������܂ŃG���h���X�I�I�I�I�I�I�I

	// �v���O�����G���h �Q�[���Z�b�g�I�I�I //
}

/***********************************************************************************************************************************************************
 �ȉ��A���슮���֐�
***********************************************************************************************************************************************************/

/*******************************************************************************
 �����[��i�o�g���j�֐�
*******************************************************************************/
int Akira( PLAYER *pPlayer )
{
	// �ϐ��錾
	int nMytern = ZERO;
	int nVer = NUM_UEKARA;
	int nHor = NUM_YOKOKARA;

	// �R�}���h�̑I��( a s d f �������ꂽ��o��I)
	while(1)
	{
		nMytern = Cursor();						// �J�[�\���ړ��ŃR�}���h�I����A�l�̑��

		if(nMytern == 0x61)
		{
			nMytern = 1;						// �Ԃ��l�ւ̑��
			break;
		}
		else if(nMytern == 0x64)
		{
			if(pPlayer -> nAvoidance == ZERO)	// ���l���Ȃ��ꍇ
			{
				LOCATE(18, 20);
				printf(" ����ł���]�͂��Ȃ��悤��...");
				Enter();						// �G���^�[�v���[�Y
				continue;
			}//if.fin

			nMytern = 2;						// �Ԃ��l�ւ̑��
			break;
		}
		else if(nMytern == 0x73)
		{
			// �R�}���h�̑I��( h j k l �������ꂽ��o��I)
			while(1)
			{
				// ���[�v���ɂƂǂ߂邽��
				nVer = NUM_UEKARA;
				nHor = NUM_YOKOKARA;

				// �X�L���̕\��
				COLOR(WHITE,BLACK);
				LOCATE(nHor, nVer++);
				printf("���F�`���[��       ���|5      �̗͂��񕜂�����");
				LOCATE(nHor, nVer++);
				printf("�@�F���u�}         ���|3      ����̖��͂����΂�");
				LOCATE(nHor, nVer++);
				printf("�@�F�o�����_�C�u   ���|15     ��_���[�W��^����");
				LOCATE(nHor, nVer++);
				printf("�@�F�X���h���O�[�� ���|30     �U����A���lUP");

				nMytern = SkillCursor();		// �X�L���p�J�[�\���ړ�

				// �l�̕Ԋ�
				if(nMytern == 0x68)				// h �̏ꍇ
				{
					if(pPlayer -> nMagic < 5)			// ���͒l���Ȃ��ꍇ
					{
						ComentReset();					// �R�����g���Z�b�g
						LOCATE(18, 20);
						printf(" ���͂�����Ȃ��悤��...");
						Enter();						// �G���^�[�v���[�Y
						continue;
					}//if.fin

					nMytern = 3;						// �Ԃ��l�ւ̑��
					break;
				}
				else if(nMytern == 0x6a)				// j �̏ꍇ
				{
					if(pPlayer -> nMagic < 3)			// ���͒l���Ȃ��ꍇ
					{
						ComentReset();					// �R�����g���Z�b�g
						LOCATE(18, 20);
						printf(" ���͂�����Ȃ��悤��...");
						Enter();						// �G���^�[�v���[�Y
						continue;
					}//if.fin

					nMytern = 4;				// �Ԃ��l�ւ̑��
					break;
				}
				else if(nMytern == 0x6b)		// k �̏ꍇ
				{
					if(pPlayer -> nMagic < 15)		// ���͒l���Ȃ��ꍇ
					{
						ComentReset();					// �R�����g���Z�b�g
						LOCATE(18, 20);
						printf(" ���͂�����Ȃ��悤��...");
						Enter();						// �G���^�[�v���[�Y
						continue;
					}//if.fin

					nMytern = 5;				// �Ԃ��l�ւ̑��
					break;
				}
				else if(nMytern == 0x6c)				// l �̏ꍇ
				{
					if(pPlayer -> nMagic < 30)			// ���͒l���Ȃ��ꍇ
					{
						ComentReset();					// �R�����g���Z�b�g
						LOCATE(18, 20);
						printf(" ���͂�����Ȃ��悤��...");
						Enter();						// �G���^�[�v���[�Y
						continue;
					}//if.fin

					nMytern = 6;						// �Ԃ��l�ւ̑��
					break;
				}
				else if(nMytern == 0x61)
				{
					nMytern = 1;						// �Ԃ��l�ւ̑��
					break;
				}
				else if(nMytern == 0x64)
				{
					if(pPlayer -> nAvoidance == ZERO)	// ���l���Ȃ��ꍇ
					{
						ComentReset();					// �R�����g���Z�b�g
						LOCATE(18, 20);
						printf(" ����ł���]�͂��Ȃ��悤��...");
						Enter();						// �G���^�[�v���[�Y
						continue;
					}//if.fin

					nMytern = 2;						// �Ԃ��l�ւ̑��
					break;
				}//if.fin

				Sleep(200);								// �C���^�[�o��0.2�b

			}//while.fin

			break;

		}//if.fin
	}//while.fin

	ComentReset();								// �R�����g���̃��Z�b�g

	// �l��Ԃ��ďI�� //
	return nMytern;
}

/*******************************************************************************
 �h���E�C�i�o�g���j�֐�
*******************************************************************************/
int Doni( PLAYER *pPlayer )
{
	// �ϐ��錾
	int nMytern = ZERO;
	int nVer = NUM_UEKARA;
	int nHor = NUM_YOKOKARA;

	// �R�}���h�̑I��( a s d f �������ꂽ��o��I)
	while(1)
	{
		nMytern = Cursor();						// �J�[�\���ړ��ŃR�}���h�I����A�l�̑��

		if(nMytern == 0x61)
		{
			nMytern = 1;						// �Ԃ��l�ւ̑��
			break;
		}
		else if(nMytern == 0x64)
		{
			if(pPlayer -> nAvoidance == ZERO)	// ���l���Ȃ��ꍇ
			{
				LOCATE(18, 20);
				printf(" ����ł���]�͂��Ȃ��悤��...");
				Enter();						// �G���^�[�v���[�Y
				continue;
			}//if.fin

			nMytern = 2;						// �Ԃ��l�ւ̑��
			break;
		}
		else if(nMytern == 0x73)
		{
			// �R�}���h�̑I��( h j k l �������ꂽ��o��I)
			while(1)
			{
				// ���[�v���ɂƂǂ߂邽��
				nVer = NUM_UEKARA;
				nHor = NUM_YOKOKARA;

				// �X�L���̕\��
				COLOR(WHITE,BLACK);
				LOCATE(nHor, nVer++);
				printf("���F�`���[��       ���|5      �̗͂��񕜂�����");
				LOCATE(nHor, nVer++);
				printf("  �F���u�}         ���|3      ����̖��͂����΂�");
				LOCATE(nHor, nVer++);
				printf("  �F���^���X�^�[   ���|15     ��_���[�W��^����");
				LOCATE(nHor, nVer++);
				printf("  �F�O���r�h��     ���|30     �U����A�̗͉�");

				nMytern = SkillCursor();				// �X�L���p�J�[�\���ړ�

				// �l�̕Ԋ�
				if(nMytern == 0x68)						// h �̏ꍇ
				{
					if(pPlayer -> nMagic < 5)			// ���͒l���Ȃ��ꍇ
					{
						LOCATE(18, 20);
						printf(" ���͂�����Ȃ��悤��...");
						Enter();						// �G���^�[�v���[�Y
						continue;
					}//if.fin

					nMytern = 3;						// �Ԃ��l�ւ̑��
					break;
				}
				else if(nMytern == 0x6a)				// j �̏ꍇ
				{
					if(pPlayer -> nMagic < 3)			// ���͒l���Ȃ��ꍇ
					{
						ComentReset();					// �R�����g���Z�b�g
						LOCATE(18, 20);
						printf(" ���͂�����Ȃ��悤��...");
						Enter();						// �G���^�[�v���[�Y
						continue;
					}//if.fin

					nMytern = 4;						// �Ԃ��l�ւ̑��
					break;
				}
				else if(nMytern == 0x6b)				// k �̏ꍇ
				{
					if(pPlayer -> nMagic < 15)			// ���͒l���Ȃ��ꍇ
					{
						ComentReset();					// �R�����g���Z�b�g
						LOCATE(18, 20);
						printf(" ���͂�����Ȃ��悤��...");
						Enter();						// �G���^�[�v���[�Y
						continue;
					}//if.fin

					nMytern = 7;						// �Ԃ��l�ւ̑��
					break;
				}
				else if(nMytern == 0x6c)				// l �̏ꍇ
				{
					if(pPlayer -> nMagic < 30)			// ���͒l���Ȃ��ꍇ
					{
						ComentReset();					// �R�����g���Z�b�g
						LOCATE(18, 20);
						printf(" ���͂�����Ȃ��悤��...");
						Enter();						// �G���^�[�v���[�Y
						continue;
					}//if.fin

					nMytern = 8;						// �Ԃ��l�ւ̑��
					break;
				}
				else if(nMytern == 0x61)
				{
					nMytern = 1;						// �Ԃ��l�ւ̑��
					break;
				}
				else if(nMytern == 0x64)
				{
					if(pPlayer -> nAvoidance == ZERO)	// ���l���Ȃ��ꍇ
					{
						ComentReset();					// �R�����g���Z�b�g
						LOCATE(18, 20);
						printf(" ����ł���]�͂��Ȃ��悤��...");
						Enter();						// �G���^�[�v���[�Y
						continue;
					}//if.fin

					nMytern = 2;						// �Ԃ��l�ւ̑��
					break;
				}//if.fin

				Sleep(200);								// �C���^�[�o��0.2�b

			}//while.fin
		}//if.fin

		break;

	}//while.fin

	ComentReset();										// �R�����g���̃��Z�b�g

	return nMytern;
}

/*******************************************************************************
 �A�_�Ԃ��i�o�g���j�֐�
*******************************************************************************/
int Adabuti( PLAYER *pPlayer )
{
	// �ϐ��錾
	int nMytern = ZERO;
	int nVer = NUM_UEKARA;
	int nHor = NUM_YOKOKARA;

	// �R�}���h�̑I��( a s d f �������ꂽ��o��I)
	while(1)
	{
		nMytern = Cursor();						// �J�[�\���ړ��ŃR�}���h�I����A�l�̑��
		
		if(nMytern == 0x61)
		{
			nMytern = 1;						// �Ԃ��l�ւ̑��
			break;
		}
		else if(nMytern == 0x64)
		{
			if(pPlayer -> nAvoidance == ZERO)	// ���l���Ȃ��ꍇ
			{
				LOCATE(18, 20);
				printf(" ����ł���]�͂��Ȃ��悤��...");
				Enter();						// �G���^�[�v���[�Y
				continue;
			}//if.fin

			nMytern = 2;						// �Ԃ��l�ւ̑��
			break;
		}
		else if(nMytern == 0x73)
		{
			// �R�}���h�̑I��( h j k l �������ꂽ��o��I)
			while(1)
			{
				// ���[�v���ɂƂǂ߂邽��
				nVer = NUM_UEKARA;
				nHor = NUM_YOKOKARA;

				// �X�L���̕\��
				COLOR(WHITE,BLACK);
				LOCATE(nHor, nVer++);
				printf("���F�`���[��       ���|5      �̗͂��񕜂�����");
				LOCATE(nHor, nVer++);
				printf("�@�F���u�}         ���|3      ����̖��͂����΂�");
				LOCATE(nHor, nVer++);
				printf("�@�F�u���b�V��     ���|15     ��_���[�W��^����");
				LOCATE(nHor, nVer++);
				printf("�@�F�Ì��e         ���|30     �U����A�U���UP");

				nMytern = SkillCursor();		// �X�L���p�J�[�\���ړ�

				// �l�̕Ԋ�
				if(nMytern == 0x68)						// h �̏ꍇ
				{
					if(pPlayer -> nMagic < 5)			// ���͒l���Ȃ��ꍇ
					{
						ComentReset();					// �R�����g���Z�b�g
						LOCATE(18, 20);
						printf(" ���͂�����Ȃ��悤��...");
						Enter();						// �G���^�[�v���[�Y
						continue;
					}//if.fin

					nMytern = 3;						// �Ԃ��l�ւ̑��
					break;
				}
				else if(nMytern == 0x6a)				// j �̏ꍇ
				{
					if(pPlayer -> nMagic < 3)			// ���͒l���Ȃ��ꍇ
					{
						ComentReset();					// �R�����g���Z�b�g
						LOCATE(18, 20);
						printf(" ���͂�����Ȃ��悤��...");
						Enter();						// �G���^�[�v���[�Y
						continue;
					}//if.fin

					nMytern = 4;						// �Ԃ��l�ւ̑��
					break;
				}
				else if(nMytern == 0x6b)				// k �̏ꍇ
				{
					if(pPlayer -> nMagic < 15)			// ���͒l���Ȃ��ꍇ
					{
						LOCATE(18, 20);
						printf(" ���͂�����Ȃ��悤��...");
						Enter();						// �G���^�[�v���[�Y
						continue;
					}//if.fin

					nMytern = 9;						// �Ԃ��l�ւ̑��
					break;
				}
				else if(nMytern == 0x6c)				// l �̏ꍇ
				{
					if(pPlayer -> nMagic < 30)			// ���͒l���Ȃ��ꍇ
					{
						ComentReset();					// �R�����g���Z�b�g
						LOCATE(18, 20);
						printf(" ���͂�����Ȃ��悤��...");
						Enter();						// �G���^�[�v���[�Y
						continue;
					}//if.fin

					nMytern = 10;						// �Ԃ��l�ւ̑��
					break;
				}
				else if(nMytern == 0x61)
				{
					nMytern = 1;						// �Ԃ��l�ւ̑��
					break;
				}
				else if(nMytern == 0x64)
				{
					if(pPlayer -> nAvoidance == ZERO)	// ���l���Ȃ��ꍇ
					{
						ComentReset();					// �R�����g���Z�b�g
						LOCATE(18, 20);
						printf(" ����ł���]�͂��Ȃ��悤��...");
						Enter();						// �G���^�[�v���[�Y
						continue;
					}//if.fin

					nMytern = 2;						// �Ԃ��l�ւ̑��
					break;
				}//if.fin

				Sleep(200);								// �C���^�[�o��0.2�b

			}//while.fin
		}//if.fin

		break;

	}//while.fin

	ComentReset();								// �R�����g���̃��Z�b�g

	return nMytern;
}

/*******************************************************************************
 �h���L�[�i�o�g���j�֐�
*******************************************************************************/
int BattleDoraki( ENEMY *pEnemy)
{
	// �ϐ��錾
	int nRandDoraki;
	int nAction = ZERO;									// �s������Ɏg�p

	//�������������
	srand(( unsigned ) time( NULL ));
	nRandDoraki = rand() %5;							// �m��1/5

	// �h���L�[�̐퓬�p�^�[�� //
	if(pEnemy -> nAvoidance != ZERO)					// ���l���c���Ă���ꍇ
	{
		if(nRandDoraki == 0 || nRandDoraki == 1 || nRandDoraki == 3)
		{
			// �ʏ�U��(�v���C���[����� �| (�G�l�~�[�U���� + (-10,10))
			// �g�p��֐��ŎZ�o����
			
			// �Ԃ��l �U�����P��Ԃ�
			nAction = 1;
		}
		else if(nRandDoraki == 2)
		{
			// �Ђ��Ɛg�����킷(���l �|�P)
			pEnemy -> nAvoidance -= ONE;

			// �Ԃ��l ������Q��Ԃ�
			nAction = 2;

		}
		else if(nRandDoraki == 4)
		{
			// �H���x�߂Ă���(���l �{�P)
			pEnemy -> nAvoidance += ONE;

			// �Ԃ��l �H�x�ߎ��R��Ԃ�
			nAction = 3;

		}//if.fin
	}
	else if(pEnemy -> nAvoidance == ZERO)				// ���l���c���Ă��Ȃ��ꍇ
	{
		if(nRandDoraki == 0 || nRandDoraki == 1 || nRandDoraki == 3)
		{
			// �ʏ�U��(�v���C���[����� �| (�G�l�~�[�U���� + (-10,10))
			// �g�p��֐��ŎZ�o����

			// �Ԃ��l �U�����P��Ԃ�
			nAction = 1;
		}
		else if(nRandDoraki == 2 || nRandDoraki == 4)
		{
			// �H���x�߂Ă���(���l �{�P)
			pEnemy -> nAvoidance += ONE;

			// �Ԃ��l �H�x�ߎ��R��Ԃ�
			nAction = 3;

		}//if.fin

	}//if.fin

	// �l��Ԃ��ďI�� //
	return nAction;
}

/*******************************************************************************
 �h���L�[�}�i�o�g���j�֐�
*******************************************************************************/
int BattleDorakiMa( void )
{
	// �ϐ��錾
	int nRandDorakiMa;
	int nAction = ZERO;									// �s������Ɏg�p

	//�������������
	srand(( unsigned ) time( NULL ));
	nRandDorakiMa = rand() %5;							// �m��1/5

	// �h���L�[�}�̐퓬�p�^�[�� //
	if(nRandDorakiMa == 0 || nRandDorakiMa == 1 || nRandDorakiMa == 3)
	{
		// �ʏ�U��(�v���C���[����� �| (�G�l�~�[�U���� + (-10,10))
		// �g�p��֐��ŎZ�o����

		// �Ԃ��l �U�����P��Ԃ�
		nAction = 1;
	}
	else if(nRandDorakiMa == 2 || nRandDorakiMa == 4)
	{
		// ���u�}�`���[��(�̗́{���͂̓�����)
		// �g�p��֐��ŎZ�o����

		// �Ԃ��l ������S��Ԃ�
		nAction = 4;
	}//if.fin

	// �l��Ԃ��ďI�� //
	return nAction;
}

/*******************************************************************************
 �^�z�h���L�[�i�o�g���j�֐�
*******************************************************************************/
int BattleTahoDoraki( void )
{
	// �ϐ��錾
	int nTahoRandDoraki;
	int nAction = ZERO;									// �s������Ɏg�p

	//�������������
	srand(( unsigned ) time( NULL ));
	nTahoRandDoraki = rand() %7;						// �m��1/7

	// �^�z�h���L�[�̐퓬�p�^�[�� //
	if(nTahoRandDoraki == 3)
	{
		// �ʏ�U��(�v���C���[����� �| (�G�l�~�[�U���� + (-10,10))
		// �g�p��֐��ŎZ�o����

		// �Ԃ��l �U�����P��Ԃ�
		nAction = 1;
	}
	else if(nTahoRandDoraki == 1)
	{
		// �l���[(�x������)
		// �g�p��֐��ŎZ�o����

		// �Ԃ��l �l���[���T��Ԃ�
		nAction = 5;
	}
	else if(nTahoRandDoraki == 2 || nTahoRandDoraki == 6)
	{
		// ���P����(���l��������)
		// �g�p��֐��ŎZ�o����

		// �Ԃ��l ���P�������U��Ԃ�
		nAction = 6;
	}
	else if(nTahoRandDoraki == 0 || nTahoRandDoraki == 4 || nTahoRandDoraki == 5)
	{
		// �����~(����͖����_���[�W)
		// �g�p��֐��ŎZ�o����

		// �Ԃ��l �����~���V��Ԃ�
		nAction = 7;
	}//if.fin

	// �l��Ԃ��ďI�� //
	return nAction;
}

/*******************************************************************************
 �v���C���[�̍s���֐�
*******************************************************************************/
void Player( PLAYER *pPlayer, ENEMY *pEnemy, int nAction, int nMytern )
{
	// �ϐ��錾
	int nResult = ZERO;								// �_���[�W�i�[
	int nMagicMax = HANDRET;						// ���͍ő�l
	int nMP3Handle = ZERO;

	if(pPlayer -> nLife >= 1000)					// �񕜂ōő�l�𒴂����ꍇ
	{
		pPlayer -> nLife = 999;						// �ő�l�̑��
	}

	COLOR(WHITE,BLACK);								// ���F

	// �v���C���[�̍s�� //////////////////////////////////////
	if (nAction != 5)										//�^�z�h���L�[�̖��@����
	{
		if(nMytern == 1)									// �ʏ�U��
		{
			if(nAction != 2)								// ���肪�����ԂłȂ��ꍇ
			{
				nResult = pPlayer -> nAttack - (pEnemy -> nDefense + GetRandom(-10,10));
				pEnemy -> nLife -= nResult;					// �_���[�W�̑��

				// �����������ʉ� //
				nMP3Handle = OPENMP3("Attack.mp3");						// �I�[�v�� & ������

				PLAYMP3(nMP3Handle, 1);									// �J��Ԃ��Đ�

				WhiteNormalEffect();						// �m�[�}���G�t�F�N�g
				BlackNormalEffect();						// �u���b�N�G�t�F�N�g
				WhiteNormalEffect();						// �m�[�}���G�t�F�N�g
				BlackNormalEffect();						// �u���b�N�G�t�F�N�g
				WhiteNormalEffect();						// �m�[�}���G�t�F�N�g
				BlackNormalEffect();						// �u���b�N�G�t�F�N�g

				CLOSEMP3(nMP3Handle);									// ��~ & �N���[�Y

				LOCATE(18,20);
				printf("�s %s �t�̂��������I", pPlayer -> aName);
				LOCATE(18,21);
				printf("�s %s �t�� %d �̃_���[�W�I", pEnemy -> aName, nResult);
			}
			else if(nAction == 2)							// ���肪�����Ԃł���ꍇ
			{
				nResult = GetRandom(30,120);
				pPlayer -> nLife -= nResult;

				LOCATE(18,20);
				printf("�s %s �t�̂��������I", pPlayer -> aName);
				LOCATE(18,21);
				printf("�s %s �t�̃J�E���^�[�I", pEnemy -> aName);
				LOCATE(18,22);
				printf("�s %s �t�� %d �̃_���[�W", pPlayer -> aName, nResult);
			}//if.fin
		}
		else if(nMytern == 2)								// ���
		{
			pPlayer -> nAvoidance -= ONE;					// ���l�̏���-1

			LOCATE(18,20);
			printf("�s %s �t�͂��������ɐg�\���Ă���I", pPlayer -> aName);
		}
		else if(nMytern == 3)								// �񕜖��@�F�`���[��
		{
			pPlayer -> nMagic -= 5;							// ���͂̏���-5
			nResult += GetRandom(90,120);
			pPlayer -> nLife += nResult;					// �̗͂̉�

			if(pPlayer -> nLife >= 1000)					// �񕜂ōő�l�𒴂����ꍇ
			{
				pPlayer -> nLife = 999;						// �ő�l�̑��
			}

			LOCATE(18,20);
			printf("�s %s �t�͉񕜖��@�F�`���[�����������I", pPlayer -> aName);
			LOCATE(18,21);
			printf("�̗͂� %d �����ӂ��I", nResult);
		}
		else if(nMytern == 4)								// ���D���@�F���u�}
		{
			if(pEnemy  -> nMagic >= 7)						// ���͂�����ꍇ
			{
				pPlayer -> nMagic -= 3;						// ���͂̏���-3
				nResult += GetRandom(7,15);
				pEnemy  -> nMagic -= nResult;				// ���͂̋z��
				pPlayer -> nMagic += nResult;				// ���͂̉�

				if(pPlayer -> nMagic > HANDRET)				// �񕜂ōő�l�𒴂����ꍇ
				{
					pPlayer -> nMagic = HANDRET;			// �ő�l�̑��
				}

				LOCATE(18,20);
				printf("�s %s �t�͖��D���@�F���u�}���������I", pPlayer -> aName);
				LOCATE(18,21);
				printf("�s %s �t�̖��͂� %d ���΂����I", pEnemy -> aName, nResult);
			}
			else if(pEnemy  -> nMagic <= 6)					// ���͂��Ȃ��ꍇ
			{
				LOCATE(18,20);
				printf("�s %s �t�͖��D���@�F���u�}���������I", pPlayer -> aName);
				LOCATE(18,21);
				printf("�s %s �t�̖��͎͂c���Ă��Ȃ������I", pEnemy -> aName, nResult);
			}
		}
		else if(nMytern == 5 || nMytern == 7 || nMytern == 9)// ����͖����U��
		{
			nResult = pPlayer -> nAttack + GetRandom(-10,10);
			pEnemy -> nLife -= nResult;						// �_���[�W�̑��

			if(nAction != 2)								// ���肪�����ԂłȂ��ꍇ
			{
				pPlayer -> nMagic -= 15;					// ���́|15
				nResult = pPlayer -> nAttack + GetRandom(-10,10);
				pEnemy -> nLife -= nResult;					// �_���[�W�̑��

				if(nMytern == 5)
				{
					// ���ʉ��̍Đ�
					nMP3Handle = OPENMP3("BarunDive.mp3");					// �I�[�v�� & ������
					PLAYMP3(nMP3Handle);									// �J��Ԃ��Đ�

					BarunDiveEffect();						// �o�����_�C�u�G�t�F�N�g

					COLOR(WHITE,BLACK);
					LOCATE(18,20);
					printf("�s %s �t�̃o�����_�C�u�I", pPlayer -> aName);
				}
				else if(nMytern == 7)
				{
					// ���ʉ��̍Đ�
					nMP3Handle = OPENMP3("MetalStar.mp3");					// �I�[�v�� & ������
					PLAYMP3(nMP3Handle);									// �J��Ԃ��Đ�

					MetalStarEffect();						// ���^���X�^�[�G�t�F�N�g

					COLOR(WHITE,BLACK);
					LOCATE(18,20);
					printf("�s %s �t�̃��^���X�^�[�I", pPlayer -> aName);
				}
				else if(nMytern == 9)
				{
					// ���ʉ��̍Đ�
					nMP3Handle = OPENMP3("Brush.mp3");						// �I�[�v�� & ������
					PLAYMP3(nMP3Handle);									// �J��Ԃ��Đ�

					BrushEffect();							// �u���b�V���G�t�F�N�g

					COLOR(WHITE,BLACK);
					LOCATE(18,20);
					printf("�s %s �t�̃u���b�V���I", pPlayer -> aName);
				}//if.fin

				LOCATE(18,21);
				printf("�s %s �t�� %d �̃_���[�W�I", pEnemy -> aName, nResult);
			}
			else if(nAction == 2)							// ���肪�����Ԃł���ꍇ
			{
				COLOR(WHITE,BLACK);
				LOCATE(18,20);
				printf("�s %s �t�̂��������I", pPlayer -> aName);
				LOCATE(18,21);
				printf("�s %s �t�͂Ђ��Ɛg�����킵���I", pEnemy -> aName);
			}//if.fin
		}
		else if(nMytern == 6)								// �X���h���O�[��
		{
			pPlayer -> nMagic -= 30;						// ���́|30
			nResult = pPlayer -> nAttack + GetRandom(10,40);
			pEnemy -> nLife -= nResult;						// �_���[�W�̑��
			pPlayer -> nAvoidance += 2;						// ���l�̒ǉ�
			
			// ���ʉ��̍Đ�
			nMP3Handle = OPENMP3("SuraDragun.mp3");					// �I�[�v�� & ������
			PLAYMP3(nMP3Handle);									// �J��Ԃ��Đ�

			SuraDragunEffect();								// �X���h���O�[���G�t�F�N�g

			COLOR(WHITE,BLACK);
			LOCATE(18,20);
			printf("�s %s �t�̃X���h���O�[���I�I�I", pPlayer -> aName);
			LOCATE(18,21);
			printf("�s %s �t�� %d �̃_���[�W�I", pEnemy -> aName, nResult);
		}
		else if(nMytern == 8)								// �O���r�h��
		{
			pPlayer -> nMagic -= 30;						// ���́|30
			nResult = pPlayer -> nAttack + GetRandom(60,70);
			pEnemy -> nLife -= nResult;						// �_���[�W�̑��
			pPlayer -> nLife += GetRandom(50,60);			// �̗͂̏���

			// ���ʉ��̍Đ�
			nMP3Handle = OPENMP3("GurabiDon.mp3");					// �I�[�v�� & ������
			PLAYMP3(nMP3Handle);									// �J��Ԃ��Đ�

			GurabiDonEffect();								// �O���r�h���G�t�F�N�g

			COLOR(WHITE,BLACK);
			LOCATE(18,20);
			printf("�s %s �t�̃O���r�h���I�I�I", pPlayer -> aName);
			LOCATE(18,21);
			printf("�s %s �t�� %d �̃_���[�W�I", pEnemy -> aName, nResult);
		}
		else if(nMytern == 10)								// �Ì��e
		{
			pPlayer -> nMagic -= 30;						// ���́|30
			nResult = pPlayer -> nAttack + GetRandom(-10,10);
			pEnemy -> nLife -= nResult;						// �_���[�W�̑��
			pPlayer -> nLife += GetRandom(100,200);			// �̗͂̑��
			pPlayer -> nAttack += GetRandom(10,20);			// �U����UP
			pPlayer -> nDefense += GetRandom(10,20);		// �����UP

			// ���ʉ��̍Đ�
			nMP3Handle = OPENMP3("Ankoudan.mp3");			// �I�[�v�� & ������
			PLAYMP3(nMP3Handle);							// �J��Ԃ��Đ�

			AnkouDanEffect();								// �Ì��e�G�t�F�N�g

			COLOR(WHITE,BLACK);
			LOCATE(18,20);
			printf("�s %s �t�̈Ì��e�I�I�I", pPlayer -> aName);
			LOCATE(18,21);
			printf("�s %s �t�� %d �̃_���[�W�I", pEnemy -> aName, nResult);
		}//if.fin

		Enter();											// �v���[�Y�G���^�[

	}//if.fin(�^�z�h���L�[�̖��@����)
	else if(nAction == 5)
	{
		LOCATE(18,20);
		printf("�s %s �t�͖����Ă���I", pPlayer -> aName);

		Enter();											// �v���[�Y�G���^�[

	}//if.fin

	CLOSEMP3(nMP3Handle);									// ��~ & �N���[�Y

}

/*******************************************************************************
 �G�l�~�[�̍s���֐�
*******************************************************************************/
void Enemy( PLAYER *pPlayer, ENEMY *pEnemy, int nAction, int nMytern, int nDorakiIllusion)
{
	// �ϐ��錾
	int nDamage  = ZERO;						// �G�l�~�[�_���[�W�i�[
	int nMP3Handle = ZERO;

	COLOR(WHITE,BLACK);							// ���F

	// �G�l�~�[�̍s�� ////////////////////////////////////
	if(nAction == 1)										// �G�l�~�[�ʏ�U��
	{
		if(nMytern != 2)									// �v���C���[�������Ԃł͂Ȃ���
		{
			nDamage = pEnemy -> nAttack - (pPlayer -> nDefense + GetRandom(-10,10));
			pPlayer -> nLife -= nDamage;

			if(nDorakiIllusion == 1)						// �h���L�[
			{
				Doraki2();									// �h���L�[�A�N�V����
			}
			else if(nDorakiIllusion == 2)					// �^�z�h���L�[
			{
				TahoDoraki2();								// �^�z�h���L�[�A�N�V����
			}
			else if(nDorakiIllusion == 3)					// �h���L�[�}
			{
				DorakiMa2();								// �h���L�[�}�A�N�V����
			}//if.fin

			// ���ʉ��̍Đ�
			nMP3Handle = OPENMP3("DorakiAttack.mp3");				// �I�[�v�� & ������
			PLAYMP3(nMP3Handle);									// �J��Ԃ��Đ�

			LOCATE(18,20);
			printf("�s %s �t�̂��������I", pEnemy -> aName);
			LOCATE(18,21);
			printf("�s %s �t�� %d �̃_���[�W�I", pPlayer -> aName, nDamage);
		}
		else if(nMytern == 2)
		{
			nDamage = GetRandom(30,120);					// �J�E���^�[�_���[�W
			pEnemy -> nLife -= nDamage;

			WhiteNormalEffect();							// �m�[�}���G�t�F�N�g
			BlackNormalEffect();							// �u���b�N�G�t�F�N�g
			WhiteNormalEffect();							// �m�[�}���G�t�F�N�g
			BlackNormalEffect();							// �u���b�N�G�t�F�N�g
			WhiteNormalEffect();							// �m�[�}���G�t�F�N�g
			BlackNormalEffect();							// �u���b�N�G�t�F�N�g

			LOCATE(18,20);
			printf("�s %s �t�̂��������I", pEnemy -> aName);
			LOCATE(18,21);
			printf("�s %s �t�̃J�E���^�[�I", pPlayer -> aName);
			LOCATE(18,22);
			printf("�s %s �t�� %d �̃_���[�W�I", pEnemy -> aName, nDamage);
		}//if.fin
	}
	else if(nAction == 2)									// �G�l�~�[���
	{
		Doraki2();											// �h���L�[�A�N�V����
		LOCATE(18,20);
		printf("�s %s �t�͂��������ɔ����Ă���I", pEnemy -> aName);
	}
	else if(nAction == 3)									// �H�x��
	{
		// ���ʉ��̍Đ�
		nMP3Handle = OPENMP3("Josho.mp3");						// �I�[�v�� & ������
		PLAYMP3(nMP3Handle);									// �J��Ԃ��Đ�

		Doraki2();											// �h���L�[�A�N�V����
		Joshoffect();										// �㏸�G�t�F�N�g

		LOCATE(18,20);
		printf("�s %s �t�͉H���x�߂Ă���", pEnemy -> aName);
		LOCATE(18,21);
		printf("�s %s �t�����l�㏸�I", pEnemy -> aName);
	}
	else if(nAction == 4)										// �񖂖��@�F
	{
		if(pEnemy -> nMagic >= ONE)
		{
			// ���ʉ��̍Đ�
			nMP3Handle = OPENMP3("Kaifuku.mp3");					// �I�[�v�� & ������
			PLAYMP3(nMP3Handle);									// �J��Ԃ��Đ�

			pEnemy -> nMagic -= ONE;
			pEnemy -> nLife += GetRandom(100,370);				// ��
			pEnemy -> nMagic += GetRandom(20,25);				// ��
			Doraki2();											// �h���L�[�}�A�N�V����

			KifukuEffect();										// �񕜃G�t�F�N�g

			LOCATE(18,20);
			printf("�s %s �t�͉񖂖��@�F���u�}�`���[����������", pEnemy -> aName);
			LOCATE(18,21);
			printf("�s %s �t�݂͂�݂�񕜂��Ă����I", pEnemy -> aName);
		}
		else if(pEnemy -> nMagic <= ZERO)
		{
			LOCATE(18,20);
			printf("�s %s �t�͉񖂖��@�F���u�}�`���[����������", pEnemy -> aName);
			LOCATE(18,21);
			printf("�������A���͂�����Ȃ��悤���I");
		}
	}
	else if(nAction == 5)									// ���~���@�F�l���[
	{
		// ���ʉ��̍Đ�
		nMP3Handle = OPENMP3("warp.mp3");						// �I�[�v�� & ������
		PLAYMP3(nMP3Handle);									// �J��Ԃ��Đ�

		TahoDoraki2();										// �^�z�h���L�[�A�N�V����

		CLOSEMP3(nMP3Handle);									// ��~ & �N���[�Y
		
		LOCATE(18,20);
		printf("�s %s �t�͐��~���@�F�l���[�������Ă����I", pEnemy -> aName);
		LOCATE(18,21);
		printf("�s %s �t�͂Ȃ�Ɩ����Ă����I", pPlayer -> aName);
	}
	else if(nAction == 6)									// ���x���@�F���P����
	{
		// ���ʉ��̍Đ�
		nMP3Handle = OPENMP3("warp.mp3");						// �I�[�v�� & ������
		PLAYMP3(nMP3Handle);									// �J��Ԃ��Đ�

		pPlayer -> nAvoidance -= ONE;						// ���l����
		TahoDoraki2();										// �^�z�h���L�[�A�N�V����

		CLOSEMP3(nMP3Handle);									// ��~ & �N���[�Y
		
		LOCATE(18,20);
		printf("�s %s �t�͑��x���@�F���P�������������I", pEnemy -> aName);
		LOCATE(18,21);
		printf("�s %s �t�̑̂͏d���Ȃ��Ă����I", pPlayer -> aName);
	}
	else if(nAction == 7)									// �����~
	{
		if(pEnemy -> nMagic >= 7)
		{
			pEnemy -> nMagic -= 7;
			nDamage = pEnemy -> nAttack + GetRandom(-10,10);
			pPlayer -> nLife -= nDamage;

			// ���ʉ��̍Đ�
			nMP3Handle = OPENMP3("GurabiDon.mp3");					// �I�[�v�� & ������
			PLAYMP3(nMP3Handle);									// �J��Ԃ��Đ�

			TahoDoraki2();									// �^�z�h���L�[�A�N�V����

			LOCATE(18,20);
			printf("�s %s �t�͍U�����@�F�����~���������I", pEnemy -> aName);
			LOCATE(18,21);
			printf("�s %s �t�� %d �̃_���[�W�I", pPlayer -> aName, nDamage);
		}
		else if(pEnemy -> nMagic <= 6)
		{
			LOCATE(18,20);
			printf("�s %s �t�͍U�����@�F�����~���������I", pEnemy -> aName);
			LOCATE(18,21);
			printf("�������A���͂�����Ȃ��悤���I");
		}

	}//if.fin

	CLOSEMP3(nMP3Handle);									// ��~ & �N���[�Y

	Enter();												// �v���[�Y�G���^�[

}

/*******************************************************************************
 �v���[�Y�G���^�[�֐�
*******************************************************************************/
void Enter( void )
{
	// �ϐ��錾
	int nkey = ZERO;
	int nMP3Handle = ZERO;

	// �v���[�Y�G���^�[
	while(1)
	{
		KEYCLEAR();												// �L�[�{�[�h������������ 
		COLOR(YELLOW);
		LOCATE(48, 22);
		printf("�sPlease ENTER�t");
		WAIT(300);												// 0.3sec�̎��ԑ҂� 
		INKEY(nkey);											// �����L�[��������Ă�����ϐ��ɒl����͂��� 
		if (nkey == 0xd) break;									// ���������ꂽ��I������ 

		KEYCLEAR();												// �L�[�{�[�h������������ 
		COLOR(LIME);
		LOCATE(48, 22);
		printf("�sPlease ENTER�t");
		WAIT(300);												// 0.3sec�̎��ԑ҂� 
		INKEY(nkey);											// �����L�[��������Ă�����ϐ��ɒl����͂��� 
		if (nkey == 0xd) break;									// ���������ꂽ��I������
	}//while.fin

	// ���ʉ��̍Đ�
	nMP3Handle = OPENMP3("Select.mp3");						// �I�[�v�� & ������
	PLAYMP3(nMP3Handle);									// �J��Ԃ��Đ�

	CLOSEMP3(nMP3Handle);									// �N���[�Y & ��~

	ComentReset();											// �R�����g���̃��Z�b�g

}

/******************************************************************************
 �X���C�������N�֐�(�\�E�������N)
*******************************************************************************/
int SuraimRink( int nWarpiru )
{
	// �ϐ��錾
	int cCode = ZERO;
	int nSelect = ZERO;
	int nSuraimSelect = ZERO;
	int nPosition = ZERO;
	int nReslut = ZERO;
	
	CLS(WHITE, BLACK);

	// ���b�Z�[�W�̕\�� // �{�^�����������܂ŃA�j���[�V����
	while(1)
	{
		KEYCLEAR();											// �O�̂��߃L�[�{�[�h������������
		Soulrink();											// �\�E�������N�^�C�g����\������

		COLOR(BLACK,LIME);
		LOCATE(35 , 21);									// �ꏊ�w��
		printf(" PLEASE ENTER ");

		WAIT(700);											// �C���^�[�o�� 0.7�b
		INKEY(cCode);										// �����L�[��������Ă�����ϐ��ɒl����͂���
		if (cCode == 0xd) break;							// �G���^�[�������ꂽ��I������
		KEYCLEAR();											// �O�̂��߃L�[�{�[�h������������
		Soulrink2();										// �\�E�������N�^�C�g���Q��\������

		LOCATE(35 , 21);									// �ꏊ�w��
		printf(" PLEASE ENTER ");

		WAIT(700);											// �C���^�[�o�� 0.7�b
		INKEY(cCode);										// �����L�[��������Ă�����ϐ��ɒl����͂���
		if (cCode == 0xd) break;							// �G���^�[�������ꂽ��I������
	}//while.fin

	// �\�E�������N�̐��������邩���̂܂܎n�߂邩�̑I��
	COLOR(WHITE,BLACK);
	LOCATE(35, 20);											// �ꏊ�w��
	printf("�� SOUL RINK !!!");
	LOCATE(35, 21);											// �ꏊ�w��
	printf("�� �\�E�������N�ɂ���");
	
	LOCATE(31, 20);											// �ꏊ�w��
	COLOR(WHITE,H_RED);
	printf(" ��");
	LOCATE(31, 21);											// �ꏊ�w��
	COLOR(WHITE,BLACK);
	printf("   ");

	nReslut = 0x61;
	
	// ��L�I��������̑I���R�}���h
	while(1)
	{
		while(1)												// �J�[�\���ړ��p���[�v
		{
			INKEY(nSelect);										// �����L�[��������Ă�����ϐ��ɒl����͂���

			if(nSelect == 0x77)									// W �A�X�L�[�R�[�h�̓��͌�
			{
				if(nPosition == ZERO)							// �J�[�\������ɂ��鎞�� W ���������ꍇ
				{
					BACKCOLOR(BLACK);
					LOCATE(31, 20);
					printf(" �@");
					COLOR(WHITE, BLUE);
					LOCATE(31, 21);
					printf(" ��");

					nReslut = 0x73;
					nPosition = ONE;
				}
				else if(nPosition == ONE)						// �J�[�\�������ɂ��鎞�� W ���������ꍇ
				{
					COLOR(WHITE, H_RED);
					LOCATE(31, 20);
					printf(" ��");
					BACKCOLOR(BLACK);
					LOCATE(31, 21);
					printf(" �@");

					nReslut = 0x61;
					nPosition = ZERO;
				}//if.fin
			}//if.fin
			if(nSelect == 0x73)									// S �A�X�L�[�R�[�h�̓��͌�
			{
				if(nPosition == ZERO)							// �J�[�\������ɂ��鎞�� S ���������ꍇ
				{
					BACKCOLOR(BLACK);
					LOCATE(31, 20);
					printf(" �@");
					COLOR(WHITE, BLUE);
					LOCATE(31, 21);
					printf(" ��");

					nReslut = 0x73;
					nPosition = ONE;
				}
				else if(nPosition == ONE)						// �J�[�\�������ɂ��鎞�� S ���������ꍇ
				{
					COLOR(WHITE, H_RED);
					LOCATE(31, 20);
					printf(" ��");
					BACKCOLOR(BLACK);
					LOCATE(31, 21);
					printf(" �@");

					nReslut = 0x61;
					nPosition = ZERO;
				}//if.fin
			}//if.fin

			if(nSelect == 0xd) break;

		}//while.fin

		BACKCOLOR(BLACK);

		// �I����
		if(nReslut == 0x61)									// a ��I�񂾏ꍇ
		{
			NormalWarp( nWarpiru );							// ���[�v
			break;
		}
		else if(nReslut == 0x73)							// d ��I�񂾏ꍇ
		{
			SoulRinkDescription(nWarpiru);					// �\�E�������N�ɂ��Ă̐���

			system("cls");									// ��ʂ̃N���A
			Soulrink2();									// �\�E�������N�^�C�g���Q��\������

			BACKCOLOR(BLACK);

			// �\�E�������N�̐��������邩���̂܂܎n�߂邩�̑I��
			COLOR(WHITE,BLACK);
			LOCATE(35, 20);									// �ꏊ�w��
			printf("�� SOUL RINK !!!");
			LOCATE(35, 21);									// �ꏊ�w��
			printf("�� �\�E�������N�ɂ���");

			LOCATE(31, 20);									// �ꏊ�w��
			COLOR(WHITE,BLACK);
			printf("   ");
			LOCATE(31, 21);									// �ꏊ�w��
			COLOR(WHITE, BLUE);
			printf(" ��");

			continue;
		}//if.fin
	}//while.fin

	nSuraimSelect = ONE;								// �Ԃ��l��[ 1 ]�̑��

	// �l��Ԃ�(�߂�l)
	return nSuraimSelect;

}

/*******************************************************************************
 �����X���C�� + Status�֐�(�����[��)
*******************************************************************************/
int SuraimMoveStatus( PLAYER *pPlayer, INITIAL *pInitial, ENEMY *pEnemy)
{
	//�ϐ��錾
	int cCode = ZERO;
	int nSuraimSelect;										// �X���C���̑I���Ɏg�p
	int nColor = BLUE;										// �X�e�C�^�X�g�̒��F
	int nVertical = 2;										// �c��
	int nHorizontal = 44;									// ����

	StatusFrame( nColor );									// �X�e�C�^�X�g�̕\��

	// �X���C���̔w�i�֕����̑}��
	COLOR(nColor);
	LOCATE(13,3);
	printf("�{�`�`�`�`�`�`�{");
	LOCATE(13,4);
	COLOR(BLACK);
	printf("�@�@�����[��@�@");
	COLOR(nColor);
	LOCATE(13,5);
	printf("�{�`�`�`�`�`�`�{");

	// �X�e�C�^�X�g�ւ̕����̑}��
	COLOR(H_RED);
	LOCATE(nHorizontal -1, nVertical++);
	printf("��--------------------------------��");
	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("�����܂����E���ȃX���C��");
	LOCATE(nHorizontal, nVertical++);
	printf("���A�O����������̂��ʂɃL�Y...");
	LOCATE(nHorizontal, nVertical++);
	printf("�̗́E���́E�U���͂�UP���邼�I");
	LOCATE(nHorizontal, nVertical++);
	printf("���l�E����͂�DOWN���Ă��܂����I");
	COLOR(H_RED);
	LOCATE(nHorizontal -1, nVertical++);
	printf("��--------------------------------��");

	// �O���ւ̕⑫
	LOCATE(nHorizontal +20, nVertical -3);
	COLOR(H_RED);
	printf("UP");
	LOCATE(nHorizontal +16, nVertical -2);
	COLOR(BLUE);
	printf("DOWN");

	nVertical++;											// �X�y�[�X���̃C���N�������g

	LOCATE(nHorizontal -1, nVertical++);
	COLOR(GREEN);
	printf("* BEFOR AFTER + BASESTATUS  RESULT *");

	nVertical++;											// �X�y�[�X���̃C���N�������g

	// �ϐ��錾 int�^����double�^�֕ϊ� �̂��̃X���C������ő��
	int    nStatusLif;										// �̗͒l�̉��ϐ�
	int    nStatusMag;										// ���͒l�̉��ϐ�
	int    nStatusAtk;										// �U���͂̉��ϐ�
	int    nStatusDef;										// ����͂̉��ϐ�
	int    nStatusAvo;										// ���l�̉��ϐ�

	int    nStatus;
	double dStatus;

	// �̗͒l�̕ω��\��(�ω��O���ϊ��と����)
	nStatus = pPlayer -> nLife;								// nStatus�ɓ������l����
	dStatus = nStatus;										// �^��int�^����double�^�֕ϊ�
	dStatus *= NUM_STATUS_B;								// �ω����̐��l�̎Z�o
	nStatus = dStatus;										// �^��double�^����int�^�֕ϊ�

	nStatusLif = pPlayer -> nLife + nStatus + BASE_LIFE;	// ���ϐ��ɐ��l�̑��(�X�e�C�^�X���莞�Ɏg�p)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("�̗͒l %3d ��      �{ %3d �� %3d", pPlayer -> nLife, BASE_LIFE, pPlayer -> nLife + nStatus + BASE_LIFE);
	COLOR(H_RED);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d", pPlayer -> nLife + nStatus);
	
	nVertical++;											// �X�y�[�X���̃C���N�������g

	// ���͒l�̕ω��\��(�ω��O���ϊ��と����)
	nStatus = pPlayer -> nMagic;							// nStatus�ɓ������l����
	dStatus = nStatus;										// �^��int�^����double�^�֕ϊ�
	dStatus *= NUM_STATUS_B;								// �ω����̐��l�̎Z�o
	nStatus = dStatus;										// �^��double�^����int�^�֕ϊ�

	nStatusMag = pPlayer -> nMagic + nStatus + BASE_MAGIC;	// ���ϐ��ɐ��l�̑��(�X�e�C�^�X���莞�Ɏg�p)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("���͒l %3d ��      �{ %3d �� %3d", pPlayer -> nMagic, BASE_MAGIC, pPlayer -> nMagic + nStatus + BASE_MAGIC);
	COLOR(H_RED);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d",pPlayer -> nMagic + nStatus);

	nVertical++;											// �X�y�[�X���̃C���N�������g

	// �U���͂̕ω��\��(�ω��O���ϊ��と����)
	nStatus = pPlayer ->nAttack;							// nStatus�ɓ������l����
	dStatus = nStatus;										// �^��int�^����double�^�֕ϊ�
	dStatus *= NUM_STATUS_A;								// �ω����̐��l�̎Z�o
	nStatus = dStatus;										// �^��double�^����int�^�֕ϊ�

	nStatusAtk = pPlayer -> nAttack + nStatus + BASE_ATTACK;	// ���ϐ��ɐ��l�̑��(�X�e�C�^�X���莞�Ɏg�p)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("�U���� %3d ��      �{ %3d �� %3d", pPlayer -> nAttack, BASE_ATTACK, pPlayer -> nAttack + nStatus + BASE_ATTACK);
	COLOR(H_RED);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d",pPlayer -> nAttack + nStatus);

	nVertical++;											// �X�y�[�X���̃C���N�������g

	// ����͂̕ω��\��(�ω��O���ϊ��と����)
	nStatus = pPlayer ->nDefense;							// nStatus�ɓ������l����
	dStatus = nStatus;										// �^��int�^����double�^�֕ϊ�
	dStatus *= NUM_STATUS_C;								// �ω����̐��l�̎Z�o
	nStatus = dStatus;										// �^��double�^����int�^�֕ϊ�

	nStatusDef = pPlayer -> nDefense - nStatus + BASE_DEFENSE;	// ���ϐ��ɐ��l�̑��(�X�e�C�^�X���莞�Ɏg�p)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("����� %3d ��      �{ %3d �� %3d", pPlayer ->nDefense, BASE_DEFENSE, pPlayer -> nDefense - nStatus + BASE_DEFENSE);
	COLOR(BLUE);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d",pPlayer -> nDefense - nStatus);

	nVertical++;											// �X�y�[�X���̃C���N�������g

	// ���l�̕ω��\��(�ω��O���ϊ��と����)
	nStatusAvo = pPlayer -> nAvoidance - 1 + BASE_AVOIDANCE;	// ���ϐ��ɐ��l�̑��(�X�e�C�^�X���莞�Ɏg�p)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("���l %3d ��      �{ %3d �� %3d", pPlayer -> nAvoidance, BASE_AVOIDANCE, pPlayer -> nAvoidance - 1 + BASE_AVOIDANCE);
	COLOR(BLUE);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d",pPlayer -> nAvoidance - 1);

	nVertical++;											// �X�y�[�X���̃C���N�������g

	// �����[���I�Ԃ��ύX�O�̃X�e�C�^�X�Ŏn�߂邩
	COLOR(BLACK);
	LOCATE(nHorizontal +3, nVertical++);
	printf("�s        �t�ƃ����N���Ďn�߂�I");
	LOCATE(nHorizontal +3, nVertical++);
	printf("�s        �t�ƃ����N�����Ɏn�߂�");

	COLOR(BLUE);
	LOCATE(nHorizontal +5, nVertical -2);
	printf("�����[��");
	LOCATE(nHorizontal +5, nVertical -1);
	printf("�����[��");

	// �I�����̕\��
	COLOR(WHITE,H_RED);
	LOCATE(nHorizontal -1, nVertical -2);
	printf(" O�F");
	COLOR(WHITE,BLUE);
	LOCATE(nHorizontal -1, nVertical -1);
	printf(" X�F");

	// �I�����̕\��
	LOCATE(3,22);
	COLOR(WHITE,BLACK);
	printf("A �� �s�h���E�C�t�b�s�A�_�Ԃ��t �� D");

	// �O�̂��߃L�[�{�[�h������������
	KEYCLEAR();

	// �{�^�����������܂ŃA�j���[�V����
	while(1)
	{
		KEYCLEAR();									// �O�̂��߃L�[�{�[�h������������
		Suraim();									// �X���C����\������
		WAIT(700);									// �C���^�[�o�� 0.7�b
		INKEY(nSuraimSelect);						// �����L�[��������Ă�����ϐ��ɒl����͂���
		if (nSuraimSelect == 0x78 || nSuraimSelect == 0x6f || nSuraimSelect == 0x61 || nSuraimSelect == 0x64) break;  // a / d / o / x �����ꂽ��I������
		KEYCLEAR();									// �O�̂��߃L�[�{�[�h������������
		Suraim2();									// �X���C���Q��\������
		WAIT(700);									// �C���^�[�o�� 0.7�b
		INKEY(nSuraimSelect);						// �����L�[��������Ă�����ϐ��ɒl����͂���
		if (nSuraimSelect == 0x78 || nSuraimSelect == 0x6f || nSuraimSelect == 0x61 || nSuraimSelect == 0x64) break;  // a / d / o / x �����ꂽ��I������
	}//while.fin

	//��ʓ��̑I���������͂��ꂽ�l�Ŕ��f
	if(nSuraimSelect == 0x6f)							// [ o ]���I�����ꂽ�ꍇ�A�l�̑��
	{
		// �I�񂾃X���C���ɂ���ăp���[�A�b�v�I�I�I
		pPlayer -> nLife      = nStatusLif;				// �̗͒l�̑��
		pPlayer -> nMagic     = nStatusMag;				// ���͒l�̑��
		pPlayer -> nAttack    = nStatusAtk;				// �U���͂̑��
		pPlayer -> nDefense   = nStatusDef;				// ����͂̑��
		pPlayer -> nAvoidance = nStatusAvo;				// ���l�̑��

		// ����̃X�e�C�^�X�������㏸
		pEnemy -> nLife    += 130;
		pEnemy -> nAttack  += 20;
	}
	else if(nSuraimSelect == 0x78)						// [ x ]���I�����ꂽ�ꍇ�A�l�̑��
	{
		// �I�΂��ɃX�^�[�g�I�I�I
		pPlayer -> nLife      = pInitial -> nLife;		// �̗͒l�̏����l�̑��
		pPlayer -> nMagic     = pInitial -> nMagic;		// ���͒l�̏����l�̑��
		pPlayer -> nAttack    = pInitial -> nAttack;	// �U���͂̏����l�̑��
		pPlayer -> nDefense   = pInitial -> nDefense;	// ����͂̏����l�̑��
		pPlayer -> nAvoidance = pInitial -> nAvoidance;	// ���l�̏����l�̑��
	}

	// �I�����̒l��߂�
	return nSuraimSelect;
}

/*******************************************************************************
 �������^���X���C�� + Status�֐�(�h���E�C)
*******************************************************************************/
int MetalSuraimMoveStatus( PLAYER *pPlayer, INITIAL *pInitial, ENEMY *pEnemy)
{
	//�ϐ��錾
	int cCode = ZERO;
	int nSuraimSelect;										// �X���C���̑I���Ɏg�p
	int nColor = H_BLACK;									// �X�e�C�^�X�g�̒��F
	int nVertical = 2;										// �c��
	int nHorizontal = 44;									// ����

	StatusFrame( nColor );									// �X�e�C�^�X�g�̕\��

	// �X���C���̔w�i�֕����̑}��
	COLOR(nColor);
	LOCATE(13,3);
	printf("�{�`�`�`�`�`�`�{");
	LOCATE(13,4);
	COLOR(BLACK);
	printf("�@�@�h���E�C�@�@");
	COLOR(nColor);
	LOCATE(13,5);
	printf("�{�`�`�`�`�`�`�{");

	// �X�e�C�^�X�g�ւ̕����̑}��
	COLOR(H_RED);
	LOCATE(nHorizontal -1, nVertical++);
	printf("��--------------------------------��");
	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("���蓾�Ȃ��قǂ̎��M�̎�����I");
	LOCATE(nHorizontal, nVertical++);
	printf("�v���قǑf���������Ȃ�...(�x��)");
	LOCATE(nHorizontal, nVertical++);
	printf("�U���́E����́E���l��UP���邼�I");
	LOCATE(nHorizontal, nVertical++);
	printf("�̗͂�DOWN���Ă��܂����I");
	COLOR(H_RED);
	LOCATE(nHorizontal -1, nVertical++);
	printf("��--------------------------------��");

	// �O���ւ̕⑫
	LOCATE(nHorizontal +24, nVertical -3);
	COLOR(H_RED);
	printf("UP");
	LOCATE(nHorizontal +6, nVertical -2);
	COLOR(BLUE);
	printf("DOWN");

	nVertical++;											// �X�y�[�X���̃C���N�������g

	LOCATE(nHorizontal -1, nVertical++);
	COLOR(GREEN);
	printf("* BEFOR AFTER + BASESTATUS  RESULT *");

	nVertical++;											// �X�y�[�X���̃C���N�������g

	// �ϐ��錾 int�^����double�^�֕ϊ� �̂��̃X���C������ő��
	int    nStatusLif;										// �̗͒l�̉��ϐ�
	int    nStatusMag;										// ���͒l�̉��ϐ�
	int    nStatusAtk;										// �U���͂̉��ϐ�
	int    nStatusDef;										// ����͂̉��ϐ�
	int    nStatusAvo;										// ���l�̉��ϐ�

	int    nStatus;
	double dStatus;

	// �̗͒l�̕ω��\��(�ω��O���ϊ��と����)
	nStatus = pPlayer -> nLife;								// nStatus�ɓ������l����
	dStatus = nStatus;										// �^��int�^����double�^�֕ϊ�
	dStatus *= NUM_STATUS_D;								// �ω����̐��l�̎Z�o
	nStatus = dStatus;										// �^��double�^����int�^�֕ϊ�

	nStatusLif = pPlayer -> nLife - nStatus + BASE_LIFE;	// ���ϐ��ɐ��l�̑��(�X�e�C�^�X���莞�Ɏg�p)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("�̗͒l %3d ��      �{ %3d �� %3d", pPlayer -> nLife, BASE_LIFE, pPlayer -> nLife - nStatus + BASE_LIFE);
	COLOR(BLUE);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d", pPlayer -> nLife - nStatus);
	
	nVertical++;											// �X�y�[�X���̃C���N�������g

	// ���͒l�̕ω��\��(�ω��O���ϊ��と����)
	nStatusMag = pPlayer -> nMagic + BASE_MAGIC;	// ���ϐ��ɐ��l�̑��(�X�e�C�^�X���莞�Ɏg�p)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("���͒l %3d ��  %3d �{ %3d �� %3d", pPlayer -> nMagic, pPlayer -> nMagic, BASE_MAGIC, pPlayer -> nMagic + BASE_MAGIC);

	nVertical++;											// �X�y�[�X���̃C���N�������g

	// �U���͂̕ω��\��(�ω��O���ϊ��と����)
	nStatus = pPlayer -> nAttack;							// nStatus�ɓ������l����
	dStatus = nStatus;										// �^��int�^����double�^�֕ϊ�
	dStatus *= NUM_STATUS_B;								// �ω����̐��l�̎Z�o
	nStatus = dStatus;										// �^��double�^����int�^�֕ϊ�

	nStatusAtk = pPlayer -> nAttack + nStatus + BASE_ATTACK;	// ���ϐ��ɐ��l�̑��(�X�e�C�^�X���莞�Ɏg�p)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("�U���� %3d ��      �{ %3d �� %3d", pPlayer -> nAttack, BASE_ATTACK, pPlayer -> nAttack + nStatus + BASE_ATTACK);
	COLOR(H_RED);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d",pPlayer -> nAttack + nStatus);

	nVertical++;											// �X�y�[�X���̃C���N�������g

	// ����͂̕ω��\��(�ω��O���ϊ��と����)
	nStatus = pPlayer ->nDefense;							// nStatus�ɓ������l����
	dStatus = nStatus;										// �^��int�^����double�^�֕ϊ�
	dStatus *= NUM_STATUS_C;								// �ω����̐��l�̎Z�o
	nStatus = dStatus;										// �^��double�^����int�^�֕ϊ�

	nStatusDef = pPlayer -> nDefense + nStatus + BASE_DEFENSE;	// ���ϐ��ɐ��l�̑��(�X�e�C�^�X���莞�Ɏg�p)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("����� %3d ��      �{ %3d �� %3d", pPlayer ->nDefense, BASE_DEFENSE, pPlayer -> nDefense + nStatus + BASE_DEFENSE);
	COLOR(H_RED);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d",pPlayer -> nDefense + nStatus);

	nVertical++;											// �X�y�[�X���̃C���N�������g

	// ���l�̕ω��\��(�ω��O���ϊ��と����)
	nStatusAvo = pPlayer -> nAvoidance + 1 + BASE_AVOIDANCE;	// ���ϐ��ɐ��l�̑��(�X�e�C�^�X���莞�Ɏg�p)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("���l %3d ��      �{ %3d �� %3d", pPlayer -> nAvoidance, BASE_AVOIDANCE, pPlayer -> nAvoidance + 1 + BASE_AVOIDANCE);
	COLOR(H_RED);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d",pPlayer -> nAvoidance + 1);

	nVertical++;											// �X�y�[�X���̃C���N�������g

	// �����[���I�Ԃ��ύX�O�̃X�e�C�^�X�Ŏn�߂邩
	COLOR(BLACK);
	LOCATE(nHorizontal +3, nVertical++);
	printf("�s        �t�ƃ����N���Ďn�߂�I");
	LOCATE(nHorizontal +3, nVertical++);
	printf("�s        �t�ƃ����N�����Ɏn�߂�");

	COLOR(H_BLACK);
	LOCATE(nHorizontal +5, nVertical -1);
	printf("�h���E�C");
	LOCATE(nHorizontal +5, nVertical -2);
	printf("�h���E�C");

	// �I�����̕\��
	COLOR(WHITE,H_RED);
	LOCATE(nHorizontal -1, nVertical -2);
	printf(" O�F");
	COLOR(WHITE,BLUE);
	LOCATE(nHorizontal -1, nVertical -1);
	printf(" X�F");

	// �I�����̕\��
	LOCATE(3,22);
	COLOR(WHITE,BLACK);
	printf("A �� �s�A�_�Ԃ��t�b�s�����[��t �� D");

	// �O�̂��߃L�[�{�[�h������������
	KEYCLEAR();

	// �{�^�����������܂ŃA�j���[�V����
	while(1)
	{
		KEYCLEAR();									// �O�̂��߃L�[�{�[�h������������
		MetalSuraim();								// ���^���X���C����\������
		WAIT(700);									// �C���^�[�o�� 0.7�b
		INKEY(nSuraimSelect);						// �����L�[��������Ă�����ϐ��ɒl����͂���
		if (nSuraimSelect == 0x78 || nSuraimSelect == 0x6f || nSuraimSelect == 0x61 || nSuraimSelect == 0x64) break;  // a / d / o / x �����ꂽ��I������
		KEYCLEAR();									// �O�̂��߃L�[�{�[�h������������
		MetalSuraim2();								// ���^���X���C���Q��\������
		WAIT(700);									// �C���^�[�o�� 0.7�b
		INKEY(nSuraimSelect);						// �����L�[��������Ă�����ϐ��ɒl����͂���
		if (nSuraimSelect == 0x78 || nSuraimSelect == 0x6f || nSuraimSelect == 0x61 || nSuraimSelect == 0x64) break;  // a / d / o / x �����ꂽ��I������
	}//while.fin

	//��ʓ��̑I���������͂��ꂽ�l�Ŕ��f
	if(nSuraimSelect == 0x6f)						// [ o ]���I�����ꂽ�ꍇ�A�l�̑��
	{
		// �I�񂾃X���C���ɂ���ăp���[�A�b�v�I�I�I
		pPlayer -> nLife = nStatusLif;				// �̗͒l�̑��
		pPlayer -> nMagic = nStatusMag;				// ���͒l�̑��
		pPlayer -> nAttack = nStatusAtk;			// �U���͂̑��
		pPlayer -> nDefense = nStatusDef;			// ����͂̑��
		pPlayer -> nAvoidance = nStatusAvo;			// ���l�̑��

		// ����̃X�e�C�^�X�������㏸
		pEnemy -> nLife    += 130;
		pEnemy -> nAttack  += 40;
	}
	else if(nSuraimSelect == 0x78)						// [ x ]���I�����ꂽ�ꍇ�A�l�̑��
	{
		// �I�΂��ɃX�^�[�g�I�I�I
		pPlayer -> nLife      = pInitial -> nLife;		// �̗͒l�̏����l�̑��
		pPlayer -> nMagic     = pInitial -> nMagic;		// ���͒l�̏����l�̑��
		pPlayer -> nAttack    = pInitial -> nAttack;	// �U���͂̏����l�̑��
		pPlayer -> nDefense   = pInitial -> nDefense;	// ����͂̏����l�̑��
		pPlayer -> nAvoidance = pInitial -> nAvoidance;	// ���l�̏����l�̑��
	}

	// �I�����̒l��߂�
	return nSuraimSelect;

}

/*******************************************************************************
 �����Ԃ��X���C�� + Status�֐�(�A�_�Ԃ�)
*******************************************************************************/
int ButiSuraimMoveStatus( PLAYER *pPlayer, INITIAL *pInitial, ENEMY *pEnemy)
{
	//�ϐ��錾
	int cCode = ZERO;
	int nSuraimSelect;										// �X���C���̑I���Ɏg�p
	int nColor = YELLOW;									// �X�e�C�^�X�g�̒��F
	int nVertical = 2;										// �c��
	int nHorizontal = 44;									// ����

	StatusFrame( nColor );									// �X�e�C�^�X�g�̕\��

	// �X���C���̔w�i�֕����̑}��
	COLOR(nColor);
	LOCATE(13,3);
	printf("�{�`�`�`�`�`�`�{");
	LOCATE(13,4);
	COLOR(BLACK);
	printf("�@�@�A�_�Ԃ��@�@");
	COLOR(nColor);
	LOCATE(13,5);
	printf("�{�`�`�`�`�`�`�{");

	// �X�e�C�^�X�g�ւ̕����̑}��
	COLOR(H_RED);
	LOCATE(nHorizontal -1, nVertical++);
	printf("��--------------------------------��");
	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("���傢���傢�{�P�邪�c�̋�����I");
	LOCATE(nHorizontal, nVertical++);
	printf("�u�`�͂Ȃ�Ɛ��ݍ��񂾏ݖ��炵��(��");
	LOCATE(nHorizontal, nVertical++);
	printf("�̗́E���́E���l��UP���邼�I");
	LOCATE(nHorizontal, nVertical++);
	printf("����͂�DOWN���Ă��܂����I");
	COLOR(H_RED);
	LOCATE(nHorizontal -1, nVertical++);
	printf("��--------------------------------��");

	// �O���ւ̕⑫
	LOCATE(nHorizontal +20, nVertical -3);
	COLOR(H_RED);
	printf("UP");
	LOCATE(nHorizontal +8, nVertical -2);
	COLOR(BLUE);
	printf("DOWN");

	nVertical++;											// �X�y�[�X���̃C���N�������g

	LOCATE(nHorizontal -1, nVertical++);
	COLOR(GREEN);
	printf("* BEFOR AFTER + BASESTATUS  RESULT *");

	nVertical++;											// �X�y�[�X���̃C���N�������g

	// �ϐ��錾 int�^����double�^�֕ϊ� �̂��̃X���C������ő��
	int    nStatusLif;										// �̗͒l�̉��ϐ�
	int    nStatusMag;										// ���͒l�̉��ϐ�
	int    nStatusAtk;										// �U���͂̉��ϐ�
	int    nStatusDef;										// ����͂̉��ϐ�
	int    nStatusAvo;										// ���l�̉��ϐ�

	int    nStatus;
	double dStatus;

	// �̗͒l�̕ω��\��(�ω��O���ϊ��と����)
	nStatus = pPlayer -> nLife;								// nStatus�ɓ������l����
	dStatus = nStatus;										// �^��int�^����double�^�֕ϊ�
	dStatus *= NUM_STATUS_B;								// �ω����̐��l�̎Z�o
	nStatus = dStatus;										// �^��double�^����int�^�֕ϊ�

	nStatusLif = pPlayer -> nLife + nStatus + BASE_LIFE;	// ���ϐ��ɐ��l�̑��(�X�e�C�^�X���莞�Ɏg�p)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("�̗͒l %3d ��      �{ %3d �� %3d", pPlayer -> nLife, BASE_LIFE, pPlayer -> nLife + nStatus + BASE_LIFE);
	COLOR(H_RED);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d", pPlayer -> nLife + nStatus);
	
	nVertical++;											// �X�y�[�X���̃C���N�������g

	// ���͒l�̕ω��\��(�ω��O���ϊ��と����)
	nStatus = pPlayer ->nMagic;								// nStatus�ɓ������l����
	dStatus = nStatus;										// �^��int�^����double�^�֕ϊ�
	dStatus *= NUM_STATUS_D;								// �ω����̐��l�̎Z�o
	nStatus = dStatus;										// �^��double�^����int�^�֕ϊ�

	nStatusMag = pPlayer -> nMagic + nStatus + BASE_MAGIC;	// ���ϐ��ɐ��l�̑��(�X�e�C�^�X���莞�Ɏg�p)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("�̗͒l %3d ��      �{ %3d �� %3d", pPlayer -> nMagic, BASE_MAGIC, pPlayer -> nMagic + nStatus + BASE_MAGIC);
	COLOR(H_RED);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d", pPlayer -> nMagic + nStatus);

	nVertical++;											// �X�y�[�X���̃C���N�������g

	// �U���͂̕ω��\��(�ω��O���ϊ��と����)
	nStatusAtk = pPlayer -> nAttack + nStatus + BASE_ATTACK;	// ���ϐ��ɐ��l�̑��(�X�e�C�^�X���莞�Ɏg�p)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("�U���� %3d ��  %3d �{ %3d �� %3d", pPlayer -> nAttack, pPlayer -> nAttack, BASE_ATTACK, pPlayer -> nAttack + BASE_ATTACK);

	nVertical++;											// �X�y�[�X���̃C���N�������g

	// ����͂̕ω��\��(�ω��O���ϊ��と����)
	nStatus = pPlayer ->nDefense;							// nStatus�ɓ������l����
	dStatus = nStatus;										// �^��int�^����double�^�֕ϊ�
	dStatus *= NUM_STATUS_B;								// �ω����̐��l�̎Z�o
	nStatus = dStatus;										// �^��double�^����int�^�֕ϊ�

	nStatusDef = pPlayer -> nDefense - nStatus + BASE_DEFENSE;	// ���ϐ��ɐ��l�̑��(�X�e�C�^�X���莞�Ɏg�p)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("����� %3d ��      �{ %3d �� %3d", pPlayer -> nDefense, BASE_DEFENSE, pPlayer -> nDefense - nStatus + BASE_DEFENSE);
	COLOR(BLUE);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d",pPlayer -> nDefense - nStatus);

	nVertical++;											// �X�y�[�X���̃C���N�������g

	// ���l�̕ω��\��(�ω��O���ϊ��と����)
	nStatusAvo = pPlayer -> nAvoidance +1 + BASE_AVOIDANCE;	// ���ϐ��ɐ��l�̑��(�X�e�C�^�X���莞�Ɏg�p)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("���l %3d ��      �{ %3d �� %3d", pPlayer -> nAvoidance, BASE_AVOIDANCE, pPlayer -> nAvoidance +1 + BASE_AVOIDANCE);
	COLOR(H_RED);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d",pPlayer -> nAvoidance +1);

	nVertical++;											// �X�y�[�X���̃C���N�������g

	// �����[���I�Ԃ��ύX�O�̃X�e�C�^�X�Ŏn�߂邩
	COLOR(BLACK);
	LOCATE(nHorizontal +3, nVertical++);
	printf("�s        �t�ƃ����N���Ďn�߂�I");
	LOCATE(nHorizontal +3, nVertical++);
	printf("�s        �t�ƃ����N�����Ɏn�߂�");

	COLOR(BROWN);
	LOCATE(nHorizontal +5, nVertical -1);
	printf("�A�_�Ԃ�");
	LOCATE(nHorizontal +5, nVertical -2);
	printf("�A�_�Ԃ�");

	// �I�����̕\��
	COLOR(WHITE,H_RED);
	LOCATE(nHorizontal -1, nVertical -2);
	printf(" O�F");
	COLOR(WHITE,BLUE);
	LOCATE(nHorizontal -1, nVertical -1);
	printf(" X�F");

	// �I�����̕\��
	LOCATE(3,22);
	COLOR(WHITE,BLACK);
	printf("A �� �s�����[��t�b�s�h���E�C�t �� D");

	// �O�̂��߃L�[�{�[�h������������
	KEYCLEAR();

	// �{�^�����������܂ŃA�j���[�V����
	while(1)
	{
		KEYCLEAR();									// �O�̂��߃L�[�{�[�h������������
		ButiSuraim();								// �Ԃ��X���C����\������
		WAIT(700);									// �C���^�[�o�� 0.7�b
		INKEY(nSuraimSelect);						// �����L�[��������Ă�����ϐ��ɒl����͂���
		if (nSuraimSelect == 0x78 || nSuraimSelect == 0x6f || nSuraimSelect == 0x61 || nSuraimSelect == 0x64) break;  // a / d / o / x �����ꂽ��I������
		KEYCLEAR();									// �O�̂��߃L�[�{�[�h������������
		ButiSuraim2();								// �Ԃ��X���C���Q��\������
		WAIT(700);									// �C���^�[�o�� 0.7�b
		INKEY(nSuraimSelect);						// �����L�[��������Ă�����ϐ��ɒl����͂���
		if (nSuraimSelect == 0x78 || nSuraimSelect == 0x6f || nSuraimSelect == 0x61 || nSuraimSelect == 0x64) break;  // a / d / o / x �����ꂽ��I������
	}//while.fin

	//��ʓ��̑I���������͂��ꂽ�l�Ŕ��f
	if(nSuraimSelect == 0x6f)						// [ o ]���I�����ꂽ�ꍇ�A�l�̑��
	{
		// �I�񂾃X���C���ɂ���ăp���[�A�b�v�I�I�I
		pPlayer -> nLife = nStatusLif;				// �̗͒l�̑��
		pPlayer -> nMagic = nStatusMag;				// ���͒l�̑��
		pPlayer -> nAttack = nStatusAtk;			// �U���͂̑��
		pPlayer -> nDefense = nStatusDef;			// ����͂̑��
		pPlayer -> nAvoidance = nStatusAvo;			// ���l�̑��

		// ����̃X�e�C�^�X�������㏸
		pEnemy -> nLife    += 130;
		pEnemy -> nAttack  += 20;
	}
	else if(nSuraimSelect == 0x78)						// [ x ]���I�����ꂽ�ꍇ�A�l�̑��
	{
		// �I�΂��ɃX�^�[�g�I�I�I
		pPlayer -> nLife      = pInitial -> nLife;		// �̗͒l�̏����l�̑��
		pPlayer -> nMagic     = pInitial -> nMagic;		// ���͒l�̏����l�̑��
		pPlayer -> nAttack    = pInitial -> nAttack;	// �U���͂̏����l�̑��
		pPlayer -> nDefense   = pInitial -> nDefense;	// ����͂̏����l�̑��
		pPlayer -> nAvoidance = pInitial -> nAvoidance;	// ���l�̏����l�̑��
	}

	// �I�����̒l��߂�
	return nSuraimSelect;

}

/*******************************************************************************
 �f�[�^���͊֐� 1P Competition �p
*******************************************************************************/
int CompetitionInput( PLAYER *pPlayer, ENEMY *pEnemy)
{
	// �ϐ��錾
	int nLengthWord;									//������̒���(������)���i�[
	int nNamedata;										//�ϊ���̃f�[�^�i�[
	char *pName;										//aData[MOJI]�֊i�[����|�C���^�ϐ�
	
	bool bMojisu = true;								//���͕������^���U���̔���
	int  nAkira  = ZERO;
	int  nkim    = ZERO;
	int  nnAkira = ZERO;
	int  nnkim   = ZERO;

	CLS(H_RED,WHITE);

	// ���O���͎��̐���
	COLOR(BLACK);
	LOCATE(21,12);
	printf("�� ���͂ł��镶�����͂R�`�W�����܂łł��I");
	LOCATE(21,14);
	printf("�� �Ȃ��A���͕����������Ȃ������葽�������ꍇ��");
	LOCATE(21,15);
	printf("  �s �t�����󔒂ɂȂ�̂ŁA����������͂��Ă��������I");
	LOCATE(21,16);
	printf("�� ���O���͏o���镶���͔��p�p����,���p�L���ł���Ή\�ł��I");

	// ���͕�������3�`8�ȊO�̏ꍇ��蒼��
	do
	{
		// �v���C���[�i�����j�̖��O�̓��� //
		LOCATE(28,6);
		COLOR(H_RED);
		printf("�s PLEASE INPUT YOUR NAME �t");
		LOCATE(30,8);
		COLOR(H_RED);
		printf("�s                    �t");
		LOCATE(37,8);
		scanf("%s", &pPlayer -> aName[ZERO]);

		// �A�X�L�[�R�[�h�̊i�[
		pName = &pPlayer -> aName[ZERO];

		// strlen�͕�����̒���(������)���擾����
		nLengthWord = strlen(pName);

		// ���͕�������3�`8�ȊO�̏ꍇ bMojisu �� false ����
		if(nLengthWord < MIN_MOJI || nLengthWord > MAX_MOJI)
		{
			bMojisu = false;
			system("cls");

			// ���O���͎��̐���
			COLOR(BLACK);
			LOCATE(21,12);
			printf("�� ���͂ł��镶�����͂R�`�W�����܂łł��I");
			LOCATE(21,14);
			printf("�� �Ȃ��A���͕����������Ȃ������葽�������ꍇ��");
			LOCATE(21,15);
			printf("  �s �t�����󔒂ɂȂ�̂ŁA����������͂��Ă��������I");
			LOCATE(21,16);
			printf("�� ���O���͏o���镶���͔��p�p����,���p�L���ł���Ή\�ł��I");
		}
		else
		{
			bMojisu = true;
		}//if.fin

	}while(bMojisu == false);

	//// �A�X�L�[�R�[�h�֕ϊ� ////
	nNamedata = (int) pPlayer -> aName[ZERO];

	// ���͕�������
	nAkira = pPlayer -> aName[0] + pPlayer -> aName[1] + pPlayer -> aName[2] + pPlayer -> aName[3] + pPlayer -> aName[4];
	nkim = pPlayer -> aName[0] + pPlayer -> aName[1] + pPlayer -> aName[2];

	// �X�e�[�^�X�����Ȃ����Ⴄ���`
	if(nAkira == 520)
	{
		pPlayer -> nLife      = 400;
		pPlayer -> nMagic     = 50;
		pPlayer -> nAttack    = 410;
		pPlayer -> nDefense   = ZERO;
		pPlayer -> nAvoidance = 3;
	}
	else if(nkim == 321)
	{
		pPlayer -> nLife      = -100;
		pPlayer -> nMagic     = 50;
		pPlayer -> nAttack    = 300;
		pPlayer -> nDefense   = 170;
		pPlayer -> nAvoidance = 4;
	}
	else
	{
		//�������ʕϊ�
		if(nLengthWord == 3)							// ���͂��ꂽ�������R�����̎�
		{
			//// �̗͒l�̌v�Z����o�� // (1������ +70 - 3������) *4 == �̗͒l //����
			pPlayer -> nLife = (pPlayer -> aName[0] - pPlayer -> aName[2]) +70 *4;

			//// ���͒l�̌v�Z����o�� // (1������ + 2������ + 3������) /10 == ���͒l //
			pPlayer -> nMagic = (pPlayer -> aName[0] + pPlayer -> aName[1] + pPlayer -> aName[2]) /12;

			//// �U���͂̌v�Z����o�� // (1������ - 2������ + 3������) %10 + (1������ - 2������ + 3������) //
			pPlayer -> nAttack = (pPlayer -> aName[0] - pPlayer -> aName[1] + pPlayer -> aName[2]) %20
			+ (pPlayer -> aName[0] - pPlayer -> aName[1] + pPlayer -> aName[2]);

			//// ����͂̌v�Z����o�� // (3������ -20 ) + (2������ -85) //
			pPlayer -> nDefense = (pPlayer -> aName[2] -20 ) + (pPlayer -> aName[1] -85);

			//// ���l�̌v�Z����o�� // 2������ %5 //
			pPlayer -> nAvoidance = pPlayer -> aName[1] %5;
		}
		else if(nLengthWord == 4)						// ���͂��ꂽ�������S�����̎�
		{
			//// �̗͒l�̌v�Z����o�� // (1������ +70 - 3������) *4 == �̗͒l //����
			pPlayer -> nLife = (pPlayer -> aName[0] - pPlayer -> aName[2]) +70 *4;

			//// ���͒l�̌v�Z����o�� // (4������ + 2������ + 3������) /10 == ���͒l //
			pPlayer -> nMagic = (pPlayer -> aName[3] + pPlayer -> aName[1] + pPlayer -> aName[2]) /12;

			//// �U���͂̌v�Z����o�� // (1������ - 2������ + 3������) %10 + (4������ - 1������ + 2������) //
			pPlayer -> nAttack = (pPlayer -> aName[0] - pPlayer -> aName[1] + pPlayer -> aName[2]) %20
			+ (pPlayer -> aName[3] - pPlayer -> aName[0] + pPlayer -> aName[1]);

			//// ����͂̌v�Z����o�� // (1������ -20 ) + (4������ -85) //
			pPlayer -> nDefense = (pPlayer -> aName[0] -20 ) + (pPlayer -> aName[3] -85);

			//// ���l�̌v�Z����o�� // 4������ %5 //
			pPlayer -> nAvoidance = pPlayer -> aName[3] %5;
		}
		else if(nLengthWord == 5)						// ���͂��ꂽ�������T�����̎�
		{
			//// �̗͒l�̌v�Z����o�� // (1������ +70 - 3������) *4 == �̗͒l //����
			pPlayer -> nLife = (pPlayer -> aName[0] - pPlayer -> aName[2]) +70 *4;

			//// ���͒l�̌v�Z����o�� // (5������ + 1������ + 3������) /10 == ���͒l //
			pPlayer -> nMagic = (pPlayer -> aName[4] + pPlayer -> aName[1] + pPlayer -> aName[2]) /12;

			//// �U���͂̌v�Z����o�� // (4������ - 2������ + 3������) %10 + (4������ - 1������ + 3������) //
			pPlayer -> nAttack = (pPlayer -> aName[3] - pPlayer -> aName[1] + pPlayer -> aName[2]) %20
			+ (pPlayer -> aName[3] - pPlayer -> aName[0] + pPlayer -> aName[2]);

			//// ����͂̌v�Z����o�� // (5������ -20 ) + (4������ -85) //
			pPlayer -> nDefense = (pPlayer -> aName[4] -20 ) + (pPlayer -> aName[3] -85);

			//// ���l�̌v�Z����o�� // 5������ %5 //
			pPlayer -> nAvoidance = pPlayer -> aName[4] %5;
		}
		else if(nLengthWord == 6)						// ���͂��ꂽ�������U�����̎�
		{
			//// �̗͒l�̌v�Z����o�� // (1������ +70 - 3������) *4 == �̗͒l //����
			pPlayer -> nLife = (pPlayer -> aName[0] - pPlayer -> aName[2]) +70 *4;

			//// ���͒l�̌v�Z����o�� // (3������ + 1������ + 5������) /10 == ���͒l //
			pPlayer -> nMagic = (pPlayer -> aName[4] + pPlayer -> aName[1] + pPlayer -> aName[2]) /12;

			//// �U���͂̌v�Z����o�� // (6������ - 2������ + 6������) %10 + (5������ - 1������ + 3������) //
			pPlayer -> nAttack = (pPlayer -> aName[5] - pPlayer -> aName[1] + pPlayer -> aName[5]) %20
			+ (pPlayer -> aName[4] - pPlayer -> aName[0] + pPlayer -> aName[2]);

			//// ����͂̌v�Z����o�� // (3������ -20 ) + (6������ -85) //
			pPlayer -> nDefense = (pPlayer -> aName[2] -20 ) + (pPlayer -> aName[5] -85);

			//// ���l�̌v�Z����o�� // 6������ %5 //
			pPlayer -> nAvoidance = pPlayer -> aName[5] %5;
		}
		else if(nLengthWord == 7)						// ���͂��ꂽ�������V�����̎�
		{
			//// �̗͒l�̌v�Z����o�� // (1������ +70 - 3������) *4 == �̗͒l //����
			pPlayer -> nLife = (pPlayer -> aName[0] - pPlayer -> aName[2]) +70 *4;

			//// ���͒l�̌v�Z����o�� // (7������ + 1������ + 6������) /10 == ���͒l //
			pPlayer -> nMagic = (pPlayer -> aName[6] + pPlayer -> aName[1] + pPlayer -> aName[5]) /12;

			//// �U���͂̌v�Z����o�� // (4������ - 7������ + 3������) %10 + (5������ - 7������ + 3������) //
			pPlayer -> nAttack = (pPlayer -> aName[3] - pPlayer -> aName[6] + pPlayer -> aName[2]) %20
			+ (pPlayer -> aName[4] - pPlayer -> aName[6] + pPlayer -> aName[2]);

			//// ����͂̌v�Z����o�� // (7������ -20 ) + (3������ -85) //
			pPlayer -> nDefense = (pPlayer -> aName[6] -20 ) + (pPlayer -> aName[2] -85);

			//// ���l�̌v�Z����o�� // 7������ %5 //
			pPlayer -> nAvoidance = pPlayer -> aName[6] %5;
		}
		else if(nLengthWord == 8)						// ���͂��ꂽ�������W�����̎�
		{
			//// �̗͒l�̌v�Z����o�� // (8������ +70 - 8������) *4 == �̗͒l //����
			pPlayer -> nLife = (pPlayer -> aName[7] - pPlayer -> aName[7]) +70 *4;

			//// ���͒l�̌v�Z����o�� // (8������ + 8������ + 8������) /10 == ���͒l //
			pPlayer -> nMagic = (pPlayer -> aName[7] + pPlayer -> aName[7] + pPlayer -> aName[7]) /12;

			//// �U���͂̌v�Z����o�� // (8������ - 8������ + 8������) %10 + (8������ - 8������ + 8������) //
			pPlayer -> nAttack = (pPlayer -> aName[7] - pPlayer -> aName[7] + pPlayer -> aName[7]) %20
			+ (pPlayer -> aName[4] - pPlayer -> aName[7] + pPlayer -> aName[7]);

			//// ����͂̌v�Z����o�� // (8������ -20 ) + (8������ -85) //
			pPlayer -> nDefense = (pPlayer -> aName[7] -20 ) + (pPlayer -> aName[7] -85);

			//// ���l�̌v�Z����o�� // 8������ %5 //
			pPlayer -> nAvoidance = pPlayer -> aName[7] %5;
		}//if.fin
	}//����if.fin
	
	// ���O���͎��̐���
	COLOR(BLACK);
	LOCATE(21,12);
	printf("�� ���͂ł��镶�����͂R�`�W�����܂łł��I");
	LOCATE(21,14);
	printf("�� �Ȃ��A���͕����������Ȃ������葽�������ꍇ��");
	LOCATE(21,15);
	printf("  �s �t�����󔒂ɂȂ�̂ŁA����������͂��Ă��������I");
	LOCATE(21,16);
	printf("�� ���O���͏o���镶���͔��p�p����,���p�L���ł���Ή\�ł��I");

	// ���͕�������3�`8�ȊO�̏ꍇ��蒼��
	do
	{
		// �G�l�~�[�i�G�j�̖��O�̓��� //
		LOCATE(28,6);
		COLOR(BLUE);
		printf("�s PLEASE INPUT ENEMY NAME �t");
		LOCATE(30,8);
		COLOR(BLUE);
		printf("�s                     �t");
		LOCATE(37,8);
		scanf("%s", &pEnemy -> aName[ZERO]);

		// �A�X�L�[�R�[�h�̊i�[
		pName = &pEnemy -> aName[ZERO];

		// strlen�͕�����̒���(������)���擾����
		nLengthWord = strlen(pName);

		// ���͕�������3�`8�ȊO�̏ꍇ bMojisu �� false ����
		if(nLengthWord < MIN_MOJI || nLengthWord > MAX_MOJI)
		{
			bMojisu = false;
			system("cls");

			// ���O���͎��̐���
			COLOR(BLACK);
			LOCATE(21,12);
			printf("�� ���͂ł��镶�����͂R�`�W�����܂łł��I");
			LOCATE(21,14);
			printf("�� �Ȃ��A���͕����������Ȃ������葽�������ꍇ��");
			LOCATE(21,15);
			printf("  �s �t�����󔒂ɂȂ�̂ŁA����������͂��Ă��������I");
			LOCATE(21,16);
			printf("�� ���O���͏o���镶���͔��p�p����,���p�L���ł���Ή\�ł��I");
		}
		else
		{
			bMojisu = true;
		}//if.fin

	}while(bMojisu == false);

	//// �A�X�L�[�R�[�h�֕ϊ� ////
	nNamedata = (int) pEnemy -> aName[ZERO];

	// ���͕�������
	nnAkira = pEnemy -> aName[0] + pEnemy -> aName[1] + pEnemy -> aName[2] + pEnemy -> aName[3] + pEnemy -> aName[4];
	nnkim   = pEnemy -> aName[0] + pEnemy -> aName[1] + pEnemy -> aName[2];

	//�������ʕϊ�// �X�e�[�^�X�����Ȃ����Ⴄ���`
	if(nnAkira == 520)
	{
		pEnemy -> nLife      = 400;
		pEnemy -> nMagic     = 50;
		pEnemy -> nAttack    = 310;
		pEnemy -> nDefense   = 170;
		pEnemy -> nAvoidance = 4;
	}
	else if(nnkim == 321)
	{
		pEnemy -> nLife      = 400;
		pEnemy -> nMagic     = 50;
		pEnemy -> nAttack    = 310;
		pEnemy -> nDefense   = 170;
		pEnemy -> nAvoidance = 4;
	}
	else
	{
		if(nLengthWord == 3)							// ���͂��ꂽ�������R�����̎�
		{
			//// �̗͒l�̌v�Z����o�� // (1������ +70 - 3������) *4 == �̗͒l //����
			pEnemy -> nLife = (pEnemy -> aName[0] - pEnemy -> aName[2]) +70 *4;

			//// ���͒l�̌v�Z����o�� // (1������ + 2������ + 3������) /10 == ���͒l //
			pEnemy -> nMagic = (pEnemy -> aName[0] + pEnemy -> aName[1] + pEnemy -> aName[2]) /12;

			//// �U���͂̌v�Z����o�� // (1������ - 2������ + 3������) %10 + (1������ - 2������ + 3������) //
			pEnemy -> nAttack = (pEnemy -> aName[0] - pEnemy -> aName[1] + pEnemy -> aName[2]) %20
			+ (pEnemy -> aName[0] - pEnemy -> aName[1] + pEnemy -> aName[2]);

			//// ����͂̌v�Z����o�� // (3������ -20 ) + (2������ -85) //
			pEnemy -> nDefense = (pEnemy -> aName[2] -20 ) + (pEnemy -> aName[1] -85);

			//// ���l�̌v�Z����o�� // 2������ %5 //
			pEnemy -> nAvoidance = pEnemy -> aName[1] %5;
		}
		else if(nLengthWord == 4)						// ���͂��ꂽ�������S�����̎�
		{
			//// �̗͒l�̌v�Z����o�� // (1������ +70 - 3������) *4 == �̗͒l //����
			pEnemy -> nLife = (pEnemy -> aName[0] - pEnemy -> aName[2]) +70 *4;

			//// ���͒l�̌v�Z����o�� // (4������ + 2������ + 3������) /10 == ���͒l //
			pEnemy -> nMagic = (pEnemy -> aName[3] + pEnemy -> aName[1] + pEnemy -> aName[2]) /12;

			//// �U���͂̌v�Z����o�� // (1������ - 2������ + 3������) %10 + (4������ - 1������ + 2������) //
			pEnemy -> nAttack = (pEnemy -> aName[0] - pEnemy -> aName[1] + pEnemy -> aName[2]) %20
			+ (pEnemy -> aName[3] - pEnemy -> aName[0] + pEnemy -> aName[1]);

			//// ����͂̌v�Z����o�� // (1������ -20 ) + (4������ -85) //
			pEnemy -> nDefense = (pEnemy -> aName[0] -20 ) + (pEnemy -> aName[3] -85);

			//// ���l�̌v�Z����o�� // 4������ %5 //
			pEnemy -> nAvoidance = pEnemy -> aName[3] %5;
		}
		else if(nLengthWord == 5)						// ���͂��ꂽ�������T�����̎�
		{
			//// �̗͒l�̌v�Z����o�� // (1������ +70 - 3������) *4 == �̗͒l //����
			pEnemy -> nLife = (pEnemy -> aName[0] - pEnemy -> aName[2]) +70 *4;

			//// ���͒l�̌v�Z����o�� // (5������ + 1������ + 3������) /10 == ���͒l //
			pEnemy -> nMagic = (pEnemy -> aName[4] + pEnemy -> aName[1] + pEnemy -> aName[2]) /12;

			//// �U���͂̌v�Z����o�� // (4������ - 2������ + 3������) %10 + (4������ - 1������ + 3������) //
			pEnemy -> nAttack = (pEnemy -> aName[3] - pEnemy -> aName[1] + pEnemy -> aName[2]) %20
			+ (pEnemy -> aName[3] - pEnemy -> aName[0] + pEnemy -> aName[2]);

			//// ����͂̌v�Z����o�� // (5������ -20 ) + (4������ -85) //
			pEnemy -> nDefense = (pEnemy -> aName[4] -20 ) + (pEnemy -> aName[3] -85);

			//// ���l�̌v�Z����o�� // 5������ %5 //
			pEnemy -> nAvoidance = pEnemy -> aName[4] %5;
		}
		else if(nLengthWord == 6)						// ���͂��ꂽ�������U�����̎�
		{
			//// �̗͒l�̌v�Z����o�� // (1������ +70 - 3������) *4 == �̗͒l //����
			pEnemy -> nLife = (pEnemy -> aName[0] - pEnemy -> aName[2]) +70 *4;

			//// ���͒l�̌v�Z����o�� // (3������ + 1������ + 5������) /10 == ���͒l //
			pEnemy -> nMagic = (pEnemy -> aName[4] + pEnemy -> aName[1] + pEnemy -> aName[2]) /12;

			//// �U���͂̌v�Z����o�� // (6������ - 2������ + 6������) %10 + (5������ - 1������ + 3������) //
			pEnemy -> nAttack = (pEnemy -> aName[5] - pEnemy -> aName[1] + pEnemy -> aName[5]) %20
			+ (pEnemy -> aName[4] - pEnemy -> aName[0] + pEnemy -> aName[2]);

			//// ����͂̌v�Z����o�� // (3������ -20 ) + (6������ -85) //
			pEnemy -> nDefense = (pEnemy -> aName[2] -20 ) + (pEnemy -> aName[5] -85);

			//// ���l�̌v�Z����o�� // 6������ %5 //
			pEnemy -> nAvoidance = pEnemy -> aName[5] %5;
		}
		else if(nLengthWord == 7)						// ���͂��ꂽ�������V�����̎�
		{
			//// �̗͒l�̌v�Z����o�� // (1������ +70 - 3������) *4 == �̗͒l //����
			pEnemy -> nLife = (pEnemy -> aName[0] - pEnemy -> aName[2]) +70 *4;

			//// ���͒l�̌v�Z����o�� // (7������ + 1������ + 6������) /10 == ���͒l //
			pEnemy -> nMagic = (pEnemy -> aName[6] + pEnemy -> aName[1] + pEnemy -> aName[5]) /12;

			//// �U���͂̌v�Z����o�� // (4������ - 7������ + 3������) %10 + (5������ - 7������ + 3������) //
			pEnemy -> nAttack = (pEnemy -> aName[3] - pEnemy -> aName[6] + pEnemy -> aName[2]) %20
			+ (pEnemy -> aName[4] - pEnemy -> aName[6] + pEnemy -> aName[2]);

			//// ����͂̌v�Z����o�� // (7������ -20 ) + (3������ -85) //
			pEnemy -> nDefense = (pEnemy -> aName[6] -20 ) + (pEnemy -> aName[2] -85);

			//// ���l�̌v�Z����o�� // 7������ %5 //
			pEnemy -> nAvoidance = pEnemy -> aName[6] %5;
		}
		else if(nLengthWord == 8)						// ���͂��ꂽ�������W�����̎�
		{
			//// �̗͒l�̌v�Z����o�� // (8������ +70 - 8������) *4 == �̗͒l //����
			pEnemy -> nLife = (pEnemy -> aName[7] - pEnemy -> aName[7]) +70 *4;

			//// ���͒l�̌v�Z����o�� // (8������ + 8������ + 8������) /10 == ���͒l //
			pEnemy -> nMagic = (pEnemy -> aName[7] + pEnemy -> aName[7] + pEnemy -> aName[7]) /12;

			//// �U���͂̌v�Z����o�� // (8������ - 8������ + 8������) %10 + (8������ - 8������ + 8������) //
			pEnemy -> nAttack = (pEnemy -> aName[7] - pEnemy -> aName[7] + pEnemy -> aName[7]) %20
			+ (pEnemy -> aName[4] - pEnemy -> aName[7] + pEnemy -> aName[7]);

			//// ����͂̌v�Z����o�� // (8������ -20 ) + (8������ -85) //
			pEnemy -> nDefense = (pEnemy -> aName[7] -20 ) + (pEnemy -> aName[7] -85);

			//// ���l�̌v�Z����o�� // 8������ %5 //
			pEnemy -> nAvoidance = pEnemy -> aName[7] %5;
		}//if.fin
	}//����if.fin

	CLS(H_RED,BLACK);

	//�l��main�ɕԂ�
	return 0;
}

/*******************************************************************************
 �f�[�^�o�͊֐�
*******************************************************************************/
int Output( PLAYER *pPlayer, INITIAL *pInitial, ENEMY *pEnemy)
{
	// �ϐ��錾
	int nkey;
	int nVer = 4;
	int nHor = 45;
	int nColor = H_GREEN;										// �g�ւ̒��F

	system("cls");												// �O��ʂ̃N���A

	StatusFrame( nColor );										// ��p�g�̎g�p

	LOCATE(8,2);
	COLOR(LIME,BLACK);
	printf("�`�`�` �X�e�[�^�X �`�`�`");

	Mario();													// �A�X�L�[�A�[�g�u �}���I �v

	LOCATE(43,2);
	COLOR(H_RED,WHITE);
	printf("�` YOUR �`");

	LOCATE(43,12);
	COLOR(BLUE);
	printf("�` ENEMY �`");

	// �v���C���[�ƃG�l�~�[�̃X�e�C�^�X�̕\��
	COLOR(BLACK);
	LOCATE(nHor, nVer++);
	printf("�s  %s  �t",pPlayer -> aName);						// �v���C���[�̖��O�̏o��
	LOCATE(nHor, nVer++);
	printf("�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\");
	LOCATE(nHor, nVer++);
	printf(" ���̗͒l �� %3d �{ %3d > %3d",pPlayer -> nLife, BASE_LIFE, pPlayer -> nLife + BASE_LIFE);						// �̗͒l�̏o��
	LOCATE(nHor, nVer++);
	printf(" �����͒l �� %3d �{ %3d > %3d",pPlayer -> nMagic, BASE_MAGIC, pPlayer -> nMagic + BASE_MAGIC);					// ���͒l�̏o��
	LOCATE(nHor, nVer++);
	printf(" ���U���� �� %3d �{ %3d > %3d",pPlayer -> nAttack, BASE_ATTACK, pPlayer -> nAttack + BASE_ATTACK);				// �U���l�̏o��
	LOCATE(nHor, nVer++);
	printf(" ������� �� %3d �{ %3d > %3d",pPlayer -> nDefense, BASE_DEFENSE, pPlayer -> nDefense + BASE_DEFENSE);			// ����l�̏o��
	LOCATE(nHor, nVer++);
	printf(" �����l �� %3d �{ %3d > %3d",pPlayer -> nAvoidance, BASE_AVOIDANCE, pPlayer -> nAvoidance + BASE_AVOIDANCE);	// ���l�̏o��
	LOCATE(nHor, nVer++);
	printf("�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\");

	nVer++;														// �P�P�s��
	nVer++;														// �P�Q�s�� ���͂P�R�s�ڂ���

	LOCATE(nHor, nVer++);
	printf("�s  %s  �t",pEnemy -> aName);						// �G�l�~�[�̖��O�̏o��
	LOCATE(nHor, nVer++);
	printf("�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\");
	LOCATE(nHor, nVer++);
	printf(" ���̗͒l �� %3d �{ %3d > %3d",pEnemy -> nLife, BASE_LIFE, pEnemy -> nLife + BASE_LIFE);						// �̗͒l�̏o��
	LOCATE(nHor, nVer++);
	printf(" �����͒l �� %3d �{ %3d > %3d",pEnemy -> nMagic, BASE_MAGIC, pEnemy -> nMagic + BASE_MAGIC);					// ���͒l�̏o��
	LOCATE(nHor, nVer++);
	printf(" ���U���� �� %3d �{ %3d > %3d",pEnemy -> nAttack, BASE_ATTACK, pEnemy -> nAttack + BASE_ATTACK);				// �U���l�̏o��
	LOCATE(nHor, nVer++);
	printf(" ������� �� %3d �{ %3d > %3d",pEnemy -> nDefense, BASE_DEFENSE, pEnemy -> nDefense + BASE_DEFENSE);			// ����l�̏o��
	LOCATE(nHor, nVer++);
	printf(" �����l �� %3d �{ %3d > %3d",pEnemy -> nAvoidance, BASE_AVOIDANCE, pEnemy -> nAvoidance + BASE_AVOIDANCE);	// ���l�̏o��
	LOCATE(nHor, nVer++);
	printf("�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\");

	// �v���C���[�̃X�e�C�^�X�����l�̑��
	pInitial -> nLife       = pPlayer -> nLife      + BASE_LIFE;		// �̗͒l�̏����l�̑��
	pInitial -> nMagic      = pPlayer -> nMagic     + BASE_MAGIC;		// ���͒l�̏����l�̑��
	pInitial -> nAttack     = pPlayer -> nAttack    + BASE_ATTACK;		// �U���͂̏����l�̑��
	pInitial -> nDefense    = pPlayer -> nDefense   + BASE_DEFENSE;		// ����͂̏����l�̑��
	pInitial -> nAvoidance  = pPlayer -> nAvoidance + BASE_AVOIDANCE;	// ���l�̏����l�̑��

	// �G�l�~�[�̃X�e�C�^�X�̑��
	pEnemy -> nLife += BASE_LIFE;										// �̗͒l�̑��
	pEnemy -> nMagic += BASE_MAGIC;										// ���͒l�̑��
	pEnemy -> nAttack += BASE_ATTACK;									// �U���͂̑��
	pEnemy -> nDefense += BASE_DEFENSE;									// ����͂̑��
	pEnemy -> nAvoidance += BASE_AVOIDANCE;								// ���l�̑��

	while(1)
	{
		COLOR(WHITE,LIME);
		LOCATE(52,23);
		printf("�` Please Enter �`");
		 WAIT(300);						// 0.3sec�̎��ԑ҂� 
		INKEY(nkey);					// �����L�[��������Ă�����ϐ��ɒl����͂��� 
		if (nkey == 0xd) break;			// ���������ꂽ��I������ 

		COLOR(LIME,H_CYAN);
		LOCATE(52,23);
		printf("�` Please Enter �`");
		WAIT(300);						// 0.3sec�̎��ԑ҂� 
		INKEY(nkey);					// �����L�[��������Ă�����ϐ��ɒl����͂��� 
		if (nkey == 0xd) break;			// ���������ꂽ��I������ 
	}

	// �l��Ԃ�
	return 0;
}

/*******************************************************************************
* �����_�������̍쐬����֐�
*******************************************************************************/
int GetRandom(int nMin,int nMax)
{
	return nMin+(int)(rand()*(nMax-nMin+1)/(1+RAND_MAX));
}

/*******************************************************************************
 �t���[���ɃX�e�C�^�X�\���֐�
*******************************************************************************/
void Status(PLAYER *pPlayer)
{
	// �ϐ��錾(���W�݂̂̎g�p)
	int nCnt  = ZERO;
	int nVerAvi = 22;
	int nHorAvi = 68;
	int nVerLMT = 2;
	int nHorLif = 23;
	int nHorMag = 55;
	int nLife  = ZERO;
	int nMagic = ZERO;

	// �X�e�C�^�X�̕\��
	LOCATE(5,2);
	printf(" %s", pPlayer -> aName);				// ���O
	LOCATE(72,19);
	printf(" %d", pPlayer -> nAttack);				// �U����
	LOCATE(72,20);
	printf(" %d", pPlayer -> nDefense);				// �����

	// �Q�[�W�h��Ԃ��i���l�p�j
	LOCATE(nHorAvi, nVerAvi);
	BACKCOLOR(BLACK);
	printf("        ");

	// �Q�[�W�^�X�e�C�^�X�̕\���i���n�p�j
	for(nCnt = ZERO; nCnt < pPlayer -> nAvoidance; nCnt++)
	{
		LOCATE(nHorAvi++, nVerAvi);
		COLOR(H_CYAN);
		printf("#");
	}//for.fin

	// �Q�[�W�h��Ԃ��i�̗͒l�p�j
	LOCATE(nHorLif, nVerLMT);
	BACKCOLOR(BLACK);
	printf("�@�@�@�@�@�@�@�@�@�@");

	if(pPlayer -> nLife > 900)						// �̗͂� 900 �ȏ�̏ꍇ
	{
		nLife = 10;									// �l�̑��

		// �Q�[�W�^�X�e�C�^�X�̕\���i�̗͒l�p�j
		for(nCnt = ZERO; nCnt < nLife; nCnt++)		// �l�Ԃ�񂵂ĕ\��
		{
			LOCATE(nHorLif++, nVerLMT);
			BACKCOLOR(H_RED);
			printf("�@");
		}//for.fin
	}
	else if(pPlayer -> nLife > 800)					// �̗͂� 800 �ȏ�̏ꍇ
	{
		nLife = 9;									// �l�̑��

		// �Q�[�W�^�X�e�C�^�X�̕\���i�̗͒l�p�j
		for(nCnt = ZERO; nCnt < nLife; nCnt++)		// �l�Ԃ�񂵂ĕ\��
		{
			LOCATE(nHorLif++, nVerLMT);
			BACKCOLOR(H_RED);
			printf("�@");
		}//for.fin
	}else if(pPlayer -> nLife > 700)					// �̗͂� 700 �ȏ�̏ꍇ
	{
		nLife = 8;									// �l�̑��

		// �Q�[�W�^�X�e�C�^�X�̕\���i�̗͒l�p�j
		for(nCnt = ZERO; nCnt < nLife; nCnt++)		// �l�Ԃ�񂵂ĕ\��
		{
			LOCATE(nHorLif++, nVerLMT);
			BACKCOLOR(H_RED);
			printf("�@");
		}//for.fin
	}
	else if(pPlayer -> nLife > 600)					// �̗͂� 600 �ȏ�̏ꍇ
	{
		nLife = 7;									// �l�̑��

		// �Q�[�W�^�X�e�C�^�X�̕\���i�̗͒l�p�j
		for(nCnt = ZERO; nCnt < nLife; nCnt++)		// �l�Ԃ�񂵂ĕ\��
		{
			LOCATE(nHorLif++, nVerLMT);
			BACKCOLOR(H_RED);
			printf("�@");
		}//for.fin
	}
	else if(pPlayer -> nLife > 500)					// �̗͂� 500 �ȏ�̏ꍇ
	{
		nLife = 6;									// �l�̑��

		// �Q�[�W�^�X�e�C�^�X�̕\���i�̗͒l�p�j
		for(nCnt = ZERO; nCnt < nLife; nCnt++)		// �l�Ԃ�񂵂ĕ\��
		{
			LOCATE(nHorLif++, nVerLMT);
			BACKCOLOR(H_RED);
			printf("�@");
		}//for.fin
	}
	else if(pPlayer -> nLife > 400)					// �̗͂� 400 �ȏ�̏ꍇ
	{
		nLife = 5;									// �l�̑��

		// �Q�[�W�^�X�e�C�^�X�̕\���i�̗͒l�p�j
		for(nCnt = ZERO; nCnt < nLife; nCnt++)		// �l�Ԃ�񂵂ĕ\��
		{
			LOCATE(nHorLif++, nVerLMT);
			BACKCOLOR(H_RED);
			printf("�@");
		}//for.fin
	}
	else if(pPlayer -> nLife > 300)					// �̗͂� 300 �ȏ�̏ꍇ
	{
		nLife = 4;									// �l�̑��

		// �Q�[�W�^�X�e�C�^�X�̕\���i�̗͒l�p�j
		for(nCnt = ZERO; nCnt < nLife; nCnt++)		// �l�Ԃ�񂵂ĕ\��
		{
			LOCATE(nHorLif++, nVerLMT);
			BACKCOLOR(H_RED);
			printf("�@");
		}//for.fin
	}
	else if(pPlayer -> nLife > 200)					// �̗͂� 200 �ȏ�̏ꍇ
	{
		nLife = 3;									// �l�̑��

		// �Q�[�W�^�X�e�C�^�X�̕\���i�̗͒l�p�j
		for(nCnt = ZERO; nCnt < nLife; nCnt++)		// �l�Ԃ�񂵂ĕ\��
		{
			LOCATE(nHorLif++, nVerLMT);
			BACKCOLOR(H_RED);
			printf("�@");
		}//for.fin
	}
	else if(pPlayer -> nLife > 100)					// �̗͂� 100 �ȏ�̏ꍇ
	{
		nLife = 2;									// �l�̑��

		// �Q�[�W�^�X�e�C�^�X�̕\���i�̗͒l�p�j
		for(nCnt = ZERO; nCnt < nLife; nCnt++)		// �l�Ԃ�񂵂ĕ\��
		{
			LOCATE(nHorLif++, nVerLMT);
			BACKCOLOR(H_RED);
			printf("�@");
		}//for.fin
	}
	else if(pPlayer -> nLife < 101)					// �̗͂� 101 �ȉ��̏ꍇ
	{
		nLife = 1;									// �l�̑��

		// �Q�[�W�^�X�e�C�^�X�̕\���i�̗͒l�p�j
		for(nCnt = ZERO; nCnt < nLife; nCnt++)		// �l�Ԃ�񂵂ĕ\��
		{
			LOCATE(nHorLif++, nVerLMT);
			BACKCOLOR(H_RED);
			printf("�@");
		}//for.fin
	}//if.fin

	LOCATE(23, nVerLMT);
	COLOR(WHITE);
	printf("%d", pPlayer -> nLife );

	// �Q�[�W�h��Ԃ��i���͒l�p�j
	LOCATE(nHorMag, nVerLMT);
	BACKCOLOR(BLACK);
	printf("�@�@�@�@�@�@�@�@�@�@");

	if(pPlayer -> nMagic > 90)						// ���͂� 90 �ȏ�̏ꍇ
	{
		nMagic = 10;								// �l�̑��

		// �Q�[�W�^�X�e�C�^�X�̕\���i���͒l�p�j
		for(nCnt = ZERO; nCnt < nMagic; nCnt++)		// �l�Ԃ�񂵂ĕ\��
		{
			LOCATE(nHorMag++, nVerLMT);
			BACKCOLOR(BLUE);
			printf("�@");
		}
	}
	else if(pPlayer -> nMagic > 80)					// ���͂� 80 �ȏ�̏ꍇ
	{
		nMagic = 9;									// �l�̑��

		// �Q�[�W�^�X�e�C�^�X�̕\���i���͒l�p�j
		for(nCnt = ZERO; nCnt < nMagic; nCnt++)		// �l�Ԃ�񂵂ĕ\��
		{
			LOCATE(nHorMag++, nVerLMT);
			BACKCOLOR(BLUE);
			printf("�@");
		}
	}
	else if(pPlayer -> nMagic > 70)					// ���͂� 70 �ȏ�̏ꍇ
	{
		nMagic = 8;									// �l�̑��

		// �Q�[�W�^�X�e�C�^�X�̕\���i���͒l�p�j
		for(nCnt = ZERO; nCnt < nMagic; nCnt++)		// �l�Ԃ�񂵂ĕ\��
		{
			LOCATE(nHorMag++, nVerLMT);
			BACKCOLOR(BLUE);
			printf("�@");
		}
	}
	else if(pPlayer -> nMagic > 60)					// ���͂� 60 �ȏ�̏ꍇ
	{
		nMagic = 7;									// �l�̑��

		// �Q�[�W�^�X�e�C�^�X�̕\���i���͒l�p�j
		for(nCnt = ZERO; nCnt < nMagic; nCnt++)		// �l�Ԃ�񂵂ĕ\��
		{
			LOCATE(nHorMag++, nVerLMT);
			BACKCOLOR(BLUE);
			printf("�@");
		}
	}
	else if(pPlayer -> nMagic > 50)					// ���͂� 50 �ȏ�̏ꍇ
	{
		nMagic = 6;									// �l�̑��

		// �Q�[�W�^�X�e�C�^�X�̕\���i���͒l�p�j
		for(nCnt = ZERO; nCnt < nMagic; nCnt++)		// �l�Ԃ�񂵂ĕ\��
		{
			LOCATE(nHorMag++, nVerLMT);
			BACKCOLOR(BLUE);
			printf("�@");
		}
	}
	else if(pPlayer -> nMagic > 40)					// ���͂� 40 �ȏ�̏ꍇ
	{
		nMagic = 5;									// �l�̑��

		// �Q�[�W�^�X�e�C�^�X�̕\���i���͒l�p�j
		for(nCnt = ZERO; nCnt < nMagic; nCnt++)		// �l�Ԃ�񂵂ĕ\��
		{
			LOCATE(nHorMag++, nVerLMT);
			BACKCOLOR(BLUE);
			printf("�@");
		}
	}
	else if(pPlayer -> nMagic > 30)					// ���͂� 30 �ȏ�̏ꍇ
	{
		nMagic = 4;									// �l�̑��

		// �Q�[�W�^�X�e�C�^�X�̕\���i���͒l�p�j
		for(nCnt = ZERO; nCnt < nMagic; nCnt++)		// �l�Ԃ�񂵂ĕ\��
		{
			LOCATE(nHorMag++, nVerLMT);
			BACKCOLOR(BLUE);
			printf("�@");
		}
	}
	else if(pPlayer -> nMagic > 20)					// ���͂� 20 �ȏ�̏ꍇ
	{
		nMagic = 3;									// �l�̑��

		// �Q�[�W�^�X�e�C�^�X�̕\���i���͒l�p�j
		for(nCnt = ZERO; nCnt < nMagic; nCnt++)		// �l�Ԃ�񂵂ĕ\��
		{
			LOCATE(nHorMag++, nVerLMT);
			BACKCOLOR(BLUE);
			printf("�@");
		}
	}
	else if(pPlayer -> nMagic > 10)					// ���͂� 10 �ȏ�̏ꍇ
	{
		nMagic = 2;									// �l�̑��

		// �Q�[�W�^�X�e�C�^�X�̕\���i���͒l�p�j
		for(nCnt = ZERO; nCnt < nMagic; nCnt++)		// �l�Ԃ�񂵂ĕ\��
		{
			LOCATE(nHorMag++, nVerLMT);
			BACKCOLOR(BLUE);
			printf("�@");
		}
	}
	else if(pPlayer -> nMagic < 11)					// ���͂� 11 �ȉ��̏ꍇ
	{
		nMagic = 1;									// �l�̑��

		// �Q�[�W�^�X�e�C�^�X�̕\���i���͒l�p�j
		for(nCnt = ZERO; nCnt < nMagic; nCnt++)		// �l�Ԃ�񂵂ĕ\��
		{
			LOCATE(nHorMag++, nVerLMT);
			BACKCOLOR(BLUE);
			printf("�@");
		}
	}//if.fin

	LOCATE(55, nVerLMT);
	COLOR(WHITE);
	printf("%d", pPlayer -> nMagic);

	COLOR(WHITE, BLACK);
	LOCATE(5,19);
	printf("��");
	LOCATE(5,20);
	printf("�@");
	LOCATE(5,21);
	printf("�@");
}

/*******************************************************************************
 ����̖��O�̕\���֐�
*******************************************************************************/
void Name(ENEMY *pEnemy)
{
	LOCATE(18,20);
	COLOR(WHITE,BLACK);
	printf("�s %s �t�����ꂽ�I�I�I", &pEnemy -> aName);

}

/*******************************************************************************
 ��U��U�b�s�I�֐�
*******************************************************************************/
int Order( PLAYER *pPlayer, ENEMY *pEnemy )
{
	// �ϐ��錾
	int nOrder = ZERO;

	// ���l�̍���������搧 //
	if(pPlayer -> nAvoidance > pEnemy -> nAvoidance)		// �v���C���[�̐搧 //
	{
		nOrder = ONE;										// 1��Ԃ�
	}
	else if(pEnemy -> nAvoidance > pPlayer -> nAvoidance)	// �G�l�~�[�̐搧 //
	{
		nOrder = ZERO;										// 0��Ԃ�
	}
	else if(pEnemy -> nAvoidance == pPlayer -> nAvoidance)	// �G�l�~�[�̐搧 //
	{
		nOrder = ONE;										// 1��Ԃ�
	}//if.fin

	// �l��Ԃ� //
	return nOrder;
}

/*******************************************************************************
 �t���[���J���[�֐�
*******************************************************************************/
int FrameColor( PLAYER *pPlayer )
{
	// �ϐ��錾
	int nColor = ZERO;

	// �����ʒ��F
	if(pPlayer -> nLife > 400)								// �v���C���[�̗̑͂�400�ȏ�̏ꍇ
	{
		nColor = ZERO;										// �o�g���p�t���[���̒��F�F��
	}
	if(pPlayer -> nLife <= 399)								// �v���C���[�̗̑͂�399�ȉ��̏ꍇ
	{
		nColor = 1;											// �o�g���p�t���[���̒��F�F���F
	}
	if(pPlayer -> nLife <= 200)								// �v���C���[�̗̑͂�200�ȉ��̏ꍇ
	{
		nColor = 2;											// �o�g���p�t���[���̒��F�F��
	}//if.fin

	// �l��Ԃ�
	return nColor;
}

/*******************************************************************************
 ���s����֐�
*******************************************************************************/
int Judge( PLAYER *pPlayer, ENEMY *pEnemy)
{
	// �ϐ��錾
	int nJudeg = ZERO;

	// ����
	if(pPlayer -> nLife <= 0 )			// �v���C���[�̗̑͂�0�ȉ��̏ꍇ
	{
		nJudeg = ONE;					// 1��Ԃ�
	}
	else if(pEnemy -> nLife <= 0)		// �G�l�~�[�̗̑͂�0�ȉ��̏ꍇ
	{
		nJudeg = ZERO;					// 0��Ԃ�
	}
	else								// �����ꍇ
	{
		nJudeg = 2;						// 2��Ԃ�
	}//if.fin

	// �l��Ԃ�
	return nJudeg;
}

/*******************************************************************************
 �h���L�[�ω��֐�
*******************************************************************************/
int DorakiIllusion( ENEMY *pEnemy )
{
	// �ϐ��錾
	int nDorakiIllusion = ZERO;

	//����
	if(pEnemy -> nLife > 500)								// �̗͂� 500 �ȏ�̏ꍇ
	{
		nDorakiIllusion = 1;								// ����P
	}
	if(pEnemy -> nLife < 499)								// �̗͂� 499 �ȏ�̏ꍇ
	{
		nDorakiIllusion = 2;								// ����Q
	}
	if(pEnemy -> nLife < 200)								// �̗͂� 200 �����̏ꍇ
	{
		nDorakiIllusion = 3;								// ����R
	}//if.fin

	// �l��Ԃ�
	return nDorakiIllusion;
}

/*******************************************************************************
 �G���f�B���O�֐�
*******************************************************************************/
void Ending(PLAYER *pPlayer, ENEMY *pEnemy, int nJudge, int nWarpiru, int nTurnCount)
{
	// �ϐ��錾
	int nMP3Handle = ZERO;

	// ���Ă΃n�b�s�[�G���h�I ������΃o�b�h�G���h�I //
	Enter();					// �v���[�Y�G���^�[

	if(nJudge == ZERO)			// �n�b�s�[�G���h�I
	{
		Koromaku();					// ��������

		// ���ʉ��̍Đ�
		nMP3Handle = OPENMP3("Winner.mp3");						// �I�[�v�� & ������
		PLAYMP3(nMP3Handle);									// �J��Ԃ��Đ�

		Koromaku();				// ������������
		LOCATE(18,20);
		printf("�s %s �t�́s %s �t�ɏ��������I�I�I", pPlayer -> aName, pEnemy -> aName);

	}
	else if(nJudge == ONE)		// �o�b�h�G���h�I
	{
		// ���ʉ��̍Đ�
		nMP3Handle = OPENMP3("Loose.mp3");						// �I�[�v�� & ������
		PLAYMP3(nMP3Handle);									// �J��Ԃ��Đ�

		LOCATE(18,20);
		printf("�s %s �t�́s %s �t�ɔs�k�����I�I�I", pPlayer -> aName, pEnemy -> aName);
	}//if.fin

	Enter();					// �v���[�Y�G���^�[

	CLOSEMP3(nMP3Handle);										// �N���[�Y & ��~

	NormalWarp( nWarpiru );		// ���[�v

	// ���ʉ��̍Đ�
	nMP3Handle = OPENMP3("EndingTheme.mp3");				// �I�[�v�� & ������
	PLAYMP3(nMP3Handle);									// �J��Ԃ��Đ�

	// �G���f�B���O //
	if(nJudge == ZERO)			// �n�b�s�[�G���h
	{
		CLS(BLACK,WHITE);

		SuraimDarkMove();		// �X���C���_�[�N

		if(nTurnCount <= 4)
		{
			LOCATE(22,2);
			COLOR(H_RED);
			printf("�k %d �^�[�����j�I�I�I�l��������I�I�I�I", nTurnCount);
		}
		if(nTurnCount >= 5)
		{
			LOCATE(22,2);
			COLOR(H_RED);
			printf("�k %d �^�[�����j�I�I�I�l���߂łƂ��I�I�I", nTurnCount);
		}
		if(nTurnCount >= 7)
		{
			LOCATE(22,2);
			COLOR(H_RED);
			printf("�k %d �^�[�����j�I�I�I�l�܂��܂����ˁI", nTurnCount);
		}

		LOCATE(18,20);
		printf("�s %s �t...", pPlayer -> aName);
		COLOR(H_RED);
		LOCATE(20,21);
		printf("Thank You Playing This Game!!!");
	}
	else if(nJudge == ONE)		// �G���h
	{
		CLS(WHITE,BLACK);

		Mario();				// �}���I

		LOCATE(18,20);
		printf("�s %s �t...", pPlayer -> aName);
		LOCATE(20,21);
		printf("�}���}�~�`�A");

	}//if.fin

	Enter();					// �v���[�Y�G���^�[

	CLOSEMP3(nMP3Handle);										// �N���[�Y & ��~

	NormalWarp( nWarpiru );		// ���[�v
}


