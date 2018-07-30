/*=============================================================================

 �V�[�����ʃw�b�_[ scene.h ]

=============================================================================*/
/*-----------------------------------------------------------------------------
 �C���N���[�h�K�[�h
-----------------------------------------------------------------------------*/
#ifndef _SCENE_H_
#define _SCENE_H_

/*-----------------------------------------------------------------------------
 �C���N���[�h�t�@�C��
-----------------------------------------------------------------------------*/

// �f�o�C�X�擾�p
#include "manager.h"
#include "renderer.h"
#include "texture.h"

/*-----------------------------------------------------------------------------
 �}�N����`
-----------------------------------------------------------------------------*/
#define NUM_SCENE     (128)		// �I�u�W�F�N�g��
#define NUM_VERTEX    (4)		// ���_��
#define NUM_PRIMITIVE (2)		// �v���~�e�B�u��

/*-----------------------------------------------------------------------------
 �I�u�W�F�N�g�^�C�v�񋓌^��`
-----------------------------------------------------------------------------*/
enum OBJTYPE
{
	TYPE_NONE = -1,		// �Ȃ�
	TYPE_PLAYER,		// �v���C���[
	TYPE_WALL,			// �E�H�[��
	TYPE_FIELD,			// �t�B�[���h
	TYPE_ITEM,			// �A�C�e��
	TYPE_SWITCH,		// �X�C�b�`
	TYPE_TIMER,			// �^�C�}�[
	TYPE_COLLECTER,		// �R���N�^�[
	TYPE_HALFFADE,		// �n�[�t�t�F�[�h
	TYPE_TEXTTEXTURE,	// �e�L�X�g�e�N�X�`��

	OBJTYPE_MAX			// �ő吔
};

/*-----------------------------------------------------------------------------
 �N���X��`
-----------------------------------------------------------------------------*/
class CScene
{
	private:

		// �V�[���I�u�W�F�N�g
		static CScene *m_apScene[NUM_SCENE];

		// �V�[���I�u�W�F�N�g���̊Ǘ�
		static int m_nNumScene;

		// ���������V�[���I�u�W�F�N�g���ʔԍ�
		int m_nID;

		// �I�u�W�F�N�g�^�C�v
		OBJTYPE m_objType;

	protected:

		// ���_�o�b�t�@�C���^�[�t�F�[�X
		LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;

		// �|�W�V����
		D3DXVECTOR3 m_Pos;

		// �T�C�Y
		D3DXVECTOR3 m_Size;

		// �e�N�X�`��
		int m_nTexType;

		// ��������֐�
		void Release(void);

	public:

		// �R���X�g���N�^ & �f�X�N�g���N�^
		CScene();
		virtual ~CScene() {}

		// �e�����������z�֐�
		virtual HRESULT Init  (void){ return S_OK; }
		virtual void    Uninit(void) = 0;
		virtual void    Update(void) = 0;
		virtual void    Draw  (void) = 0;

		// �ÓI���������֐�
		static void UpdateAll (void);
		static void DrawAll   (void);
		static void ReleaseAll(void);

		// �I�u�W�F�N�g���ʔԍ��擾�֐�
		static CScene *GetScene(int nIdxScene) { return m_apScene[nIdxScene]; }

		// �I�u�W�F�N�g�^�C�v�̐ݒ�
		void SetObjType(OBJTYPE objType) { m_objType = objType; }

		// �I�u�W�F�N�g�^�C�v�̎擾
		OBJTYPE GetObjType(void) { return m_objType; }

		// �I�u�W�F�N�g�����̎擾
		static int GetNumObj(void) { return m_nNumScene; }

		// �I�u�W�F�N�g�ŗL�̃f�[�^�̎擾
		D3DXVECTOR3 GetPos (void)    { return m_Pos; }
		D3DXVECTOR3 GetSize(void)    { return m_Size; }
		int         GetTexType(void) { return m_nTexType; }

		// �I�u�W�F�N�g�ŗL�̃f�[�^�̔��f
		void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }

		void SetPosMouse(D3DXVECTOR3 pos)
		{
			m_Pos.x = pos.x - m_Size.x * 0.5f;
			m_Pos.y = pos.y - m_Size.y * 0.5f;
		}//end

};

/*-----------------------------------------------------------------------------
 �C���N���[�h�G���h
-----------------------------------------------------------------------------*/
#endif
