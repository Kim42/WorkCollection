/*=============================================================================

 �v���C���[�w�b�_[ player.h ]

=============================================================================*/
/*-----------------------------------------------------------------------------
 �C���N���[�h�K�[�h
-----------------------------------------------------------------------------*/
#ifndef _PLAYER_H_
#define _PLAYER_H_

/*-----------------------------------------------------------------------------
 �C���N���[�h�t�@�C��
-----------------------------------------------------------------------------*/
#include "scene3D.h"

/*-----------------------------------------------------------------------------
 �v���C���[���\�b�h�O���錾
-----------------------------------------------------------------------------*/
class CAction;

/*-----------------------------------------------------------------------------
 �N���X��`�F�V�[���R�c�p��
-----------------------------------------------------------------------------*/
class CPlayer : public CScene3D
{
	private:

		// �ڒn����t���O
		bool m_bGround;
		bool m_bItem;
		bool m_bGoal;
		bool m_bOver;
		bool bRe;
		bool bCreate;

		int GoalCount;

		// �O��ʒu
		D3DXVECTOR3 m_OldPos;

		// �ړ���
		D3DXVECTOR3 m_Move;

		// �ړ������@�\
		CAction *m_Action;

		// �Փ˔���ɂ�鋤�ʋ�������
		void CollisionBehavior(D3DXVECTOR3 targetPos, D3DXVECTOR3 targetSize);

		// �I�u�W�F�N�g�Ƃ̏Փ˔��菈��
		void CollisionField(void);
		void CollisionWall(void);
		void CollisionItem(void);

		// �e�N�X�`���A�j���[�V����
		void ChangeTexture(void);

		// �؉H�l�܂��Ă���̂ŋ����Ăˏ����֐�
		void SubResult(void);

	public:

		// �R���X�g���N�^ & �f�X�N�g���N�^
		CPlayer();
		~CPlayer();

		// �����֐�
		static CPlayer *Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size);

		// �e�����֐�
		HRESULT Init  (int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size);
		void    Uninit(void);
		void    Update(void);
		void    Draw  (void);

		// �ړ��ʂ̎擾
		D3DXVECTOR3 GetMove(void) { return m_Move; }

		// �ړ��ʂ̐ݒu
		void InitializeMove(void) { m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); }

		// ��Ԃ̎擾
		bool GetGoal(void) { return m_bGoal; }
		bool GetOver(void) { return m_bOver; }

};

/*-----------------------------------------------------------------------------
 �C���N���[�h�G���h
-----------------------------------------------------------------------------*/
#endif
