/*=============================================================================

 �t�F�[�h�w�b�_[ fade.h ]

=============================================================================*/
/*-----------------------------------------------------------------------------
 �C���N���[�h�K�[�h
-----------------------------------------------------------------------------*/
#ifndef _FADE_H_
#define _FADE_H_

/*-----------------------------------------------------------------------------
 �N���X��`
-----------------------------------------------------------------------------*/
class CFade
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

		// ���_�o�b�t�@�C���^�[�t�F�[�X
		LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;

		// �|�W�V����
		D3DXVECTOR3 m_Pos;

		// �T�C�Y
		D3DXVECTOR3 m_Size;

		// �e�N�X�`��
		int m_nTexType;

		// �J���[���
		D3DXCOLOR m_Color;

	public:

		CFade() { m_pVtxBuff = NULL; }
		~CFade() {}

		// ��������
		static CFade *Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);

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