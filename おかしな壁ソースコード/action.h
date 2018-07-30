/*=============================================================================

 �s�������w�b�_[ action.h ]

=============================================================================*/
/*-----------------------------------------------------------------------------
 �C���N���[�h�K�[�h
-----------------------------------------------------------------------------*/
#ifndef _ACTION_H_
#define _ACTION_H_

/*-----------------------------------------------------------------------------
 �C���N���[�h�t�@�C��
-----------------------------------------------------------------------------*/
#include "manager.h"

/*-----------------------------------------------------------------------------
 �}�N����`
-----------------------------------------------------------------------------*/
// �b���Z(60 == FPS)
#define SECOND(_sec) ((_sec) * 60)

// ���x�F1�b�Ԃňړ����鋗������Z�o
#define M_S(_speed) (_speed / SECOND(1.0f))

// �����x(m / s ^ 2)
#define M_S2(_acc) (_acc / SECOND(1.0f) * SECOND(1.0f))

// �ő呬�x�F�b���S��
#define MAX_SPEED (4.0f)

// �d�͉����x(�������Ȃ̂ŕ��̒l�Őݒ�)
#define GRAVITY -0.98f  //M_S2(-1.4f)

// �����ی�W���F�����̐��l���Ɛ����s�\�Ȃ̂Łc
#define FALLCARE (0.004f)

// ���C
#define FRICTION (0.15f)

/*-----------------------------------------------------------------------------
 �N���X��`
-----------------------------------------------------------------------------*/
class CAction
{
	public:

		// �����̗񋓌^
		enum DIR
		{
			DIR_RIGHT = 0,	// �E
			DIR_LEFT,		// ��
			DIR_UP,			// ��
			DIR_DOWN		// ��
		};

	private:

		DIR m_Dir;
		bool m_Skill;

	public:

		// �R���X�g���N�^
		CAction() : m_Dir(DIR_RIGHT), m_Skill(false) {}

		// ���ړ�����
		float Move(float moveX, float fSpeed, bool *bGround, bool *bItem);

		// �W�����v����
		float Jump(float moveY, float fJumpingFouce, bool *bGround);

		// �d�͑��E�F�n�ʂɐڐG��Ԏ��ɍD�܂���
		static float Gravity(void)   { return GRAVITY * FALLCARE; }
		static float NoGravity(void) { return -GRAVITY * FALLCARE; }

		// �^������
		void Friction(float *fMove) { *fMove += (0.0f - (*fMove)) * FRICTION; }

		// �X�L������
		void Skill(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);

		// �����̎擾
		DIR GetDir(void) { return m_Dir; }

};

/*-----------------------------------------------------------------------------
 �C���N���[�h�G���h
-----------------------------------------------------------------------------*/
#endif
