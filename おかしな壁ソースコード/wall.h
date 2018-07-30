/*=============================================================================

 �E�H�[���w�b�_[ wall.h ]

=============================================================================*/
/*-----------------------------------------------------------------------------
 �C���N���[�h�K�[�h
-----------------------------------------------------------------------------*/
#ifndef _WALL_H_
#define _WALL_H_

/*-----------------------------------------------------------------------------
 �C���N���[�h�t�@�C��
-----------------------------------------------------------------------------*/
#include "scene3D.h"

/*-----------------------------------------------------------------------------
 �X�L���^�C�v�̗񋓌^��`
-----------------------------------------------------------------------------*/
enum SKILL
{
	SKILL_SWAP = 0,		// �O�F�X���b�v�F����ւ�
	SKILL_COPY,			// �P�F�R�s�[  �F����
	SKILL_SYNC			// �Q�F�V���N���F����
};

/*-----------------------------------------------------------------------------
 �E�H�[���N���X��`�F�V�[���R�c�p��
-----------------------------------------------------------------------------*/
class CWall : public CScene3D
{
	protected:

		// �X�L���^�C�v
		SKILL m_SkillType;

		// �X�L���^�C�v�ݒ�
		void SetSkillType(SKILL skill) { m_SkillType = skill; }

	public:

		// �R���X�g���N�^ & �f�X�N�g���N�^
		CWall() { SetObjType(TYPE_WALL); }
		~CWall() {}

		// �����֐�
		static CWall *Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nSkill);

		// �e�����֐�
		HRESULT Init(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nSkill);
		void    Uninit(void);
		void    Update(void);
		void    Draw(void);

		// �����Ă���X�L���̎g�p����
		virtual bool Skill(void) { return false; }

		// �����Ă���X�L���̎擾
		SKILL GetSkillType(void) { return m_SkillType; }

};

/*-----------------------------------------------------------------------------
 �X���b�v�N���X��`�F�E�H�[���p��
-----------------------------------------------------------------------------*/
class CSwap : public CWall
{
	private:

		bool Swap(void);

	public:

		// �R���X�g���N�^ & �f�X�N�g���N�^
		CSwap() { SetSkillType(SKILL_SWAP); }
		~CSwap() {}

		// �X�L���g�p����
		bool Skill(void) { return Swap(); }

};


/*-----------------------------------------------------------------------------
 �R�s�[�N���X��`�F�E�H�[���p��
-----------------------------------------------------------------------------*/
class CCopy : public CWall
{
	private:

		bool Copy(void);

	public:

		// �R���X�g���N�^ & �f�X�N�g���N�^
		CCopy() { SetSkillType(SKILL_COPY); }
		~CCopy() {}

		// �X�L���g�p����
		bool Skill(void) { return Copy(); }

};

/*-----------------------------------------------------------------------------
 �V���N���N���X��`�F�E�H�[���p��
-----------------------------------------------------------------------------*/
class CSync : public CWall
{
	private:

		bool Sync(void);
		bool m_SyncFrag;

	public:

		// �R���X�g���N�^ & �f�X�N�g���N�^
		CSync() 
		{ 
			SetSkillType(SKILL_SYNC);
			m_SyncFrag = false;
		}//end

		~CSync() {}

		// �X�L���X�V
		void Update(void);

		// �X�L���g�p����
		bool Skill(void);

};

/*-----------------------------------------------------------------------------
 �C���N���[�h�G���h
-----------------------------------------------------------------------------*/
#endif
