/*=============================================================================

 �e�N�X�`���Ǘ��w�b�_[ texture.h ]

=============================================================================*/
/*-----------------------------------------------------------------------------
 �C���N���[�h�K�[�h
-----------------------------------------------------------------------------*/
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

/*-----------------------------------------------------------------------------
 �e�N�X�`���񋓌^��`
-----------------------------------------------------------------------------*/
enum TEXTURE
{
	NEUTRAL = 0,		// �j���[�g����
	WALK1,				// �����P
	WALK2,				// �����Q
	JUMP,				// �W�����v
	BAD,				// ���s
	PUSH1,				// �����P
	PUSH2,				// �����Q
	GOGOAL1,			// ���p�P
	GOGOAL2,			// ���p�Q

	YUKA,				// ��

	SWITCHANIMETION0,	// �X�C�b�`�̃A�j���[�V�����F��
	SWITCHANIMETION1,	// �X�C�b�`�̃A�j���[�V�����F��
	SWITCHANIMETION2,	// �X�C�b�`�̃A�j���[�V�����F��
	SWITCHANIMETION3,	// �X�C�b�`�̃A�j���[�V�����F�E

	WALL_SWAP,			// �ǁF�X���b�v
	WALL_COPY,			// �ǁF�R�s�[
	WALL_SYNC,			// �ǁF�V���N��

	SHUTTER1,			// �V���b�^�[�P
	SHUTTER2,			// �V���b�^�[�Q
	SHUTTER3,			// �V���b�^�[�R
	GOAL_BACK,			// �S�[���w�i

	COLLECT_A,			// �R���N�g�A�C�e���F�r�X�P�b�g
	COLLECT_B,			// �R���N�g�A�C�e���F�L�����f�B�[
	COLLECT_C,			// �R���N�g�A�C�e���F�`���R���[�g

	MILLEF_BLOCK,		// �~���t�B�[���u���b�N

	NEEDLE,				// �j�[�h��

	SIGNBOARD_TOP,		// ���F��
	SIGNBOARD_BOTTOM,	// ���F��
	SIGNBOARD_LEFT,		// ���F��
	SIGNBOARD_RIGHT,	// ���F�E

	TIME_CLOCK,			// ���v
	TIME_NUMBER,		// �^�C������

	COUNT_ICON,			// �J�E���g�A�C�R��
	COUNT_KAKERU,		// �J�E���g�~
	COUNT_NUMBER,		// �J�E���g����

	SWEET_BG,			// �Q�[���w�i

	GOAL_FRAME,			// �S�[���t���[��
	EXIT_ICON,			// �o���A�C�R��

	STAGESELECT000,		// �X�e�[�W�Z���N�g�O
	STAGESELECT001,		// �X�e�[�W�Z���N�g�P
	STAGESELECT002,		// �X�e�[�W�Z���N�g�Q
	STAGESELECT003,		// �X�e�[�W�Z���N�g�R

	TITLE,				// �^�C�g�����S

	SWEET_BG2,			// �w�i

	GOOD,				// �v���C���[�F���
	TEX_FADE,			// �t�F�[�h�p

	CLEAR,				// �N���A����
	FAILED,				// �t�F�C������
	NEXT_STAGE,			// ���̃X�e�[�W
	STAGE_SELECT,		// �X�e�[�W�Z���N�g
	RETRY,				// ���g���C
	SELECT,				// �Z���N�g�A�C�R��

	START,				// �X�^�[�g����
	OK,					// ���߂镶��

	STAGESELECT004,		// �X�e�[�W�Z���N�g�S
	STAGESELECT005,		// �X�e�[�W�Z���N�g�T
	STAGESELECT006,		// �X�e�[�W�Z���N�g�U

};

/*-----------------------------------------------------------------------------
 �N���X��`
-----------------------------------------------------------------------------*/
class CTexture
{
	private:

		// �e�N�X�`���C���^�[�t�F�[�X
		static LPDIRECT3DTEXTURE9 *m_pTextureEx;

	public:

		// �e�N�X�`������
		static int m_nNumTexture;

		// �e�����֐�
		static HRESULT Load(void);
		static void    Release(void);

		// �e�N�X�`���f�[�^�̎擾�֐�
		static LPDIRECT3DTEXTURE9 GetAdr(int ntype) { return &*m_pTextureEx[ntype]; }

};

/*-----------------------------------------------------------------------------
 �C���N���[�h�G���h
-----------------------------------------------------------------------------*/
#endif
