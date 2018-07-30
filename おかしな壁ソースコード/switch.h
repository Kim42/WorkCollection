/*=============================================================================

 �X�C�b�`�w�b�_[ switch.h ]

=============================================================================*/
/*-----------------------------------------------------------------------------
 �C���N���[�h�K�[�h
-----------------------------------------------------------------------------*/
#ifndef _SWITCH_H_
#define _SWITCH_H_

/*-----------------------------------------------------------------------------
 �C���N���[�h�t�@�C��
-----------------------------------------------------------------------------*/
#include "scene3D.h"

/*-----------------------------------------------------------------------------
 �N���X��`�F�V�[���R�c�p��
-----------------------------------------------------------------------------*/
class CSwitch : public CScene3D
{
	private:

		// ����t���O
		bool m_bSwitch;

		// �Ή�����t�B�[���h�̔ԍ�
		int m_nFieldID;

		// ����
		enum DIRECTION
		{
			UP = 0,
			BOTTOM,
			LEFT,
			RIGHT
		};

		// �e�N�X�`���A�j���[�V����
		float m_fTexX;
		int   m_nTimer;
		
		void Animtion(void);

		// �Փ˔��菈��
		void CollisionObj(void);

	public:

		// �R���X�g���N�^ & �f�X�N�g���N�^
		CSwitch();
		~CSwitch();

		// �����֐�
		static CSwitch *Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nFieldID);

		// �e�����֐�
		HRESULT Init(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nFieldID);
		void    Uninit(void);
		void    Update(void);
		void    Draw(void);

		// �ԍ��̎擾
		int GetFieldID(void) { return m_nFieldID; }

};

/*-----------------------------------------------------------------------------
 �C���N���[�h�G���h
-----------------------------------------------------------------------------*/
#endif
