/*=============================================================================

 �����_�[�����w�b�_[ renderer.h ]

=============================================================================*/
/*-----------------------------------------------------------------------------
 �C���N���[�h�K�[�h
-----------------------------------------------------------------------------*/
#ifndef _RENDERER_H_
#define _RENDERER_H_

/*-----------------------------------------------------------------------------
 �N���X��`
-----------------------------------------------------------------------------*/
class CRenderer
{
	private:

		// Direct3D�C���^�[�t�F�[�X
		static LPDIRECT3D9 m_pD3D;

		// Direct3D�f�o�C�X�ւ̃|�C���^
		static LPDIRECT3DDEVICE9 m_pD3DDevice;

	public:

		// �R���X�g���N�^ & �f�X�N�g���N�^
		CRenderer() {}
		~CRenderer() {}

		// �e�����֐�
		static HRESULT Init  (HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
		static void    Uninit(void);
		static void    Update(void);
		static HRESULT DrawBigen(void);
		static void    DrawEnd  (void);

		// �f�o�C�X�擾
		static LPDIRECT3DDEVICE9 GetDevice(void){ return m_pD3DDevice; }

		// �f�o�b�O�e�L�X�g
		static LPD3DXFONT m_pFont;

};

/*-----------------------------------------------------------------------------
 �C���N���[�h�G���h
-----------------------------------------------------------------------------*/
#endif
