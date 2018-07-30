/*=============================================================================

 �A�C�e���w�b�_[ item.h ]

=============================================================================*/
/*-----------------------------------------------------------------------------
 �C���N���[�h�K�[�h
-----------------------------------------------------------------------------*/
#ifndef _ITEM_H_
#define _ITEM_H_

/*-----------------------------------------------------------------------------
 �C���N���[�h�t�@�C��
-----------------------------------------------------------------------------*/
#include "scene3D.h"

/*-----------------------------------------------------------------------------
 �I�u�W�F�N�g�^�C�v�̗񋓌^��`
-----------------------------------------------------------------------------*/
enum SUBTYPE
{
	SUB_GOAL = 0,		// �O�F�S�[��
	SUB_COLLECT_ITEM,	// �P�F�R���N�g�A�C�e��
	SUB_BLOCK,			// �Q�F�u���b�N
	SUB_NEEDLE,			// �R�F�j�[�h��
	SUB_ARROW,			// �S�F���
};

/*-----------------------------------------------------------------------------
 �N���X��`�F�V�[���R�c�p��
-----------------------------------------------------------------------------*/
class CItem : public CScene3D
{
	protected:

		// �T�u�^�C�v
		SUBTYPE m_SubType;

		// �T�u�^�C�v�̃Z�b�g
		void SetType(SUBTYPE sub) { m_SubType = sub; }

	public:

		// �R���X�g���N�^ & �f�X�N�g���N�^
		CItem() { SetObjType(TYPE_ITEM); }
		~CItem() {}

		// �����֐�
		static CItem *Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nSubType);

		// �e�����֐�
		HRESULT Init(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nSubType);
		void    Uninit(void);
		virtual void Update(void) = 0;
		void    Draw(void);

		// �T�u�^�C�v�̎擾
		SUBTYPE GetSubType(void) { return m_SubType; }

};

/*-----------------------------------------------------------------------------
 �S�[���N���X�F�A�C�e���p��
-----------------------------------------------------------------------------*/
class CGoal : public CItem
{
	public:

		// �R���X�g���N�^ & �f�X�N�g���N�^
		CGoal() { SetType(SUB_GOAL); }
		~CGoal() {}

		// �X�V�����̃I�[�o�[���C�h
		void Update(void) override {}

};

/*-----------------------------------------------------------------------------
 �R���N�g�A�C�e���F�A�C�e���p��
-----------------------------------------------------------------------------*/
class CCollect : public CItem
{
	public:

		// �R���X�g���N�^ & �f�X�N�g���N�^
		CCollect() { SetType(SUB_COLLECT_ITEM); }
		~CCollect() {}

		// �X�V�����̃I�[�o�[���C�h
		void Update(void) override {}

};

/*-----------------------------------------------------------------------------
 �u���b�N�F�A�C�e���p��
-----------------------------------------------------------------------------*/
class CBlock : public CItem
{
	private:

		// �ړ�����
		bool m_bMove;

		// �O��ʒu
		D3DXVECTOR3 m_OldPos;

		// �ړ���
		float m_fMoveY;

		// �I�u�W�F�N�g�Ƃ̏Փ˔��菈��(�v���C���[�ȊO)
		void CollisionObjVertical(D3DXVECTOR3 targetPos, D3DXVECTOR3 targetSize);
		bool CollisionObjSide(D3DXVECTOR3 targetPos, D3DXVECTOR3 targetSize);

	public:

		// �R���X�g���N�^ & �f�X�N�g���N�^
		CBlock() { SetType(SUB_BLOCK); m_bMove = true; m_fMoveY = 0.0f; }
		~CBlock() {}

		// �X�V�����̃I�[�o�[���C�h
		void Update(void) override;

		// �|�W�V�����̈ړ�
		void SetPosMove(float m_MoveX) { m_Pos.x += m_MoveX; }

		// ��Ԃ̎擾
		bool GetMove(void) { return m_bMove; }

};

/*-----------------------------------------------------------------------------
 �j�[�h���N���X�F�A�C�e���p��
-----------------------------------------------------------------------------*/
class CNeedle : public CItem
{
	public:

		// �R���X�g���N�^ & �f�X�N�g���N�^
		CNeedle() { SetType(SUB_NEEDLE); }
		~CNeedle() {}

		// �X�V�����̃I�[�o�[���C�h
		void Update(void) override {}

};

/*-----------------------------------------------------------------------------
 ���N���X�F�A�C�e���p��
-----------------------------------------------------------------------------*/
class CArrow : public CItem
{
	public:

		// �R���X�g���N�^ & �f�X�N�g���N�^
		CArrow() { SetType(SUB_ARROW); }
		~CArrow() {}

		// �X�V�����̃I�[�o�[���C�h
		void Update(void) override {}

};

/*-----------------------------------------------------------------------------
 �C���N���[�h�G���h
-----------------------------------------------------------------------------*/
#endif
