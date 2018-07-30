/*=============================================================================

 �J���������w�b�_[ camera.h ]

=============================================================================*/
/*-----------------------------------------------------------------------------
 �C���N���[�h�K�[�h
-----------------------------------------------------------------------------*/
#ifndef _CAMERA_H_
#define _CAMERA_H_

/*-----------------------------------------------------------------------------
 �N���X��`
-----------------------------------------------------------------------------*/
class CCamera
{
	private:

		static D3DXVECTOR3 m_At;		// �����_���W
		static D3DXVECTOR3 m_Eye;		// �J�������W
		static D3DXVECTOR3 m_Up;		// ������̃x�N�g��

		static float m_fZoom;			// �g��k��

		// �}�g���N�X�̒�`
		static D3DXMATRIX m_mtxProjection;
		static D3DXMATRIX m_mtxView;

	public:

		// �R���X�g���N�^ & �f�X�N�g���N�^
		CCamera() {}
		~CCamera() {}

		// �e�����֐�
		static HRESULT Init  (D3DXVECTOR3 At, D3DXVECTOR3 Eye);
		static void    Uninit(void);
		static void    Update(void);
		static void    Set   (void);

		// �����_���̎擾
		static D3DXVECTOR3 *GetAt(void) { return &m_At; }

		// �J�������W���̎擾
		static D3DXVECTOR3 *GetEye(void) { return &m_Eye; }

		// �r���[�}�g���N�X�̎擾
		static D3DXMATRIX  *GetViewMtx(void) { return &m_mtxView; }

		// �v���W�F�N�V�����}�g���N�X�̎擾
		static D3DXMATRIX  *GetProjectionMtx(void){ return &m_mtxProjection; }

		// �J�������_�̃Z�b�g
		static void SetCamera(D3DXVECTOR3 pos, float fZ)
		{
			m_At.x  = pos.x; m_At.y  = pos.y;
			m_Eye.x = pos.x; m_Eye.y = pos.y; m_Eye.z = fZ;

		}//end

		// �J�����Y�[������
		static void SetZoomFunction(float fZoom) { m_fZoom += fZoom; }

};

/*-----------------------------------------------------------------------------
 �C���N���[�h�G���h
-----------------------------------------------------------------------------*/
#endif
