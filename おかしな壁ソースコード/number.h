/*=============================================================================

 �i���o�[�w�b�_[ number.h ]

=============================================================================*/
/*-----------------------------------------------------------------------------
 �C���N���[�h�K�[�h
-----------------------------------------------------------------------------*/
#ifndef _NUMBER_H_
#define _NUMBER_H_

/*-----------------------------------------------------------------------------
 �N���X��`
-----------------------------------------------------------------------------*/
class CNumber
{
	private:

		// ���_�o�b�t�@�C���^�[�t�F�[�X
		LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;

		// �|�W�V����
		D3DXVECTOR3 m_Pos;

		// �T�C�Y
		D3DXVECTOR3 m_Size;

		// �e�N�X�`���^�C�v
		int m_nTexType;

	public:

		CNumber() {}
		~CNumber() {}

		// ��������
		static CNumber *Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumber);

		// �e�����֐�
		HRESULT Init (int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumber);
		void    Uninit(void);
		void    Draw  (void);

		// �i���o�[�Z�b�g
		void SetNumber(int nNumber);

};

/*-----------------------------------------------------------------------------
 �C���N���[�h�G���h
-----------------------------------------------------------------------------*/
#endif