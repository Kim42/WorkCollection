/*=============================================================================

 �n�[�t�t�F�[�h�w�b�_[ halfFade.h ]

=============================================================================*/
/*-----------------------------------------------------------------------------
 �C���N���[�h�K�[�h
-----------------------------------------------------------------------------*/
#ifndef _HALFFADE_H_
#define _HALFFADE_H_

/*-----------------------------------------------------------------------------
 �C���N���[�h�t�@�C��
-----------------------------------------------------------------------------*/
#include "scene2D.h"

/*-----------------------------------------------------------------------------
 �N���X��`
-----------------------------------------------------------------------------*/
class CHalfFade : public CScene2D
{
	public:

		// �t�F�[�h��Ԃ̗񋓌^
		enum FADE
		{
			FADE_NONE = 0,		// �Ȃ�
			FADE_IN,			// �t�F�[�h�C��
			FADE_OUT,			// �t�F�[�h�A�E�g
			FADE_MAX			// �ő�
		};

	private:

		// �t�F�[�h�̏��
		FADE m_Fade;

		// �J���[���
		D3DXCOLOR m_Color;

	public:

		CHalfFade() { SetObjType(TYPE_HALFFADE); }
		~CHalfFade() {}

		// ��������
		static CHalfFade *Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);

		// �e�����֐�
		HRESULT Init(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);
		void    Uninit(void);
		void    Update(void);
		void    Draw(void);

		// �Z�b�g
		void SetFade(FADE fade) { m_Fade = fade; }

		// �Q�b�g�J���[
		float GetColor(void) { return m_Color.a; }

};

/*-----------------------------------------------------------------------------
 �C���N���[�h�G���h
-----------------------------------------------------------------------------*/
#endif