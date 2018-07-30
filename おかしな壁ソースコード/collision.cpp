/*=============================================================================

 �R���W����[ collision.cpp ]

=============================================================================*/
/*=============================================================================
 �C���N���[�h�w�b�_
=============================================================================*/
#include "collision.h"

/*-----------------------------------------------------------------------------
 ��`���m�̏Փ˔���F�����֌W�Ȃ�
-----------------------------------------------------------------------------*/
bool C2DCollision::ColRect
(D3DXVECTOR3 posA, D3DXVECTOR3 sizeA, D3DXVECTOR3 posB, D3DXVECTOR3 sizeB)
{
	if ((posA.x < (posB.x + sizeB.x)) && 
		(posB.x < (posA.x + sizeA.x)) &&
		((posA.y + sizeA.y) > posB.y) && 
		((posB.y + sizeB.y) > posA.y))
	{
		// �Փ˂���
		return true;
	}//if.fin

	// �Փ˂Ȃ�
	return false;

}

/*-----------------------------------------------------------------------------
 ��`���m�̏Փ˔���F�����擾
-----------------------------------------------------------------------------*/
C2DCollision::COLDIR C2DCollision::ColRect_Dir
(D3DXVECTOR3 posA, D3DXVECTOR3 sizeA, D3DXVECTOR3 posB, D3DXVECTOR3 sizeB)
{
	// �ՓˑO�̋^���W���ʒu�̐ݒ�
	float fPseudo = 0.2f;

	if (ColRect(posA, sizeA, posB, sizeB) == true)
	{
		// �`���a�̏�Ɉʒu����ꍇ�A�܂��A���E�ɐG��Ă��Ȃ��ꍇ
		if ((posA.y + fPseudo) >= (posB.y + sizeB.y)) return UP;

		// �`���a�̉��Ɉʒu����ꍇ�A�܂��A���E�ɐG��Ă��Ȃ��ꍇ
		if ((posA.y + sizeA.y - fPseudo) <= posB.y) return BOTTOM;

		// �`���a�̍��Ɉʒu����ꍇ�A�܂��A�㉺�ɐG��Ă��Ȃ��ꍇ
		if ((posA.x + sizeA.x - fPseudo) <= posB.x) return LEFT;

		// �`���a�̉E�Ɉʒu����ꍇ�A�܂��A�㉺�ɐG��Ă��Ȃ��ꍇ
		if ((posA.x + fPseudo) >= (posB.x + sizeB.x)) return RIGHT;

	}//if.fin

	// �Փ˂Ȃ�
	return NONE;

}

/*-----------------------------------------------------------------------------
 ��`�Ɠ_�̏Փ˔���
-----------------------------------------------------------------------------*/
bool C2DCollision::ColPoint_Rect
(D3DXVECTOR3 point, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	if ((pos.x < point.x) &&
		(point.x < (pos.x + size.x)) &&
		((pos.y + size.y) > point.y) &&
		(point.y > pos.y))
	{
		// �Փ˂���
		return true;
	}//if.fin

	// �Փ˂Ȃ�
	return false;

}
