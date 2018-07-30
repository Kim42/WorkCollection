/*=============================================================================

 コリジョン[ collision.cpp ]

=============================================================================*/
/*=============================================================================
 インクルードヘッダ
=============================================================================*/
#include "collision.h"

/*-----------------------------------------------------------------------------
 矩形同士の衝突判定：向き関係なし
-----------------------------------------------------------------------------*/
bool C2DCollision::ColRect
(D3DXVECTOR3 posA, D3DXVECTOR3 sizeA, D3DXVECTOR3 posB, D3DXVECTOR3 sizeB)
{
	if ((posA.x < (posB.x + sizeB.x)) && 
		(posB.x < (posA.x + sizeA.x)) &&
		((posA.y + sizeA.y) > posB.y) && 
		((posB.y + sizeB.y) > posA.y))
	{
		// 衝突あり
		return true;
	}//if.fin

	// 衝突なし
	return false;

}

/*-----------------------------------------------------------------------------
 矩形同士の衝突判定：向き取得
-----------------------------------------------------------------------------*/
C2DCollision::COLDIR C2DCollision::ColRect_Dir
(D3DXVECTOR3 posA, D3DXVECTOR3 sizeA, D3DXVECTOR3 posB, D3DXVECTOR3 sizeB)
{
	// 衝突前の疑似係数位置の設定
	float fPseudo = 0.2f;

	if (ColRect(posA, sizeA, posB, sizeB) == true)
	{
		// ＡがＢの上に位置する場合、また、左右に触れていない場合
		if ((posA.y + fPseudo) >= (posB.y + sizeB.y)) return UP;

		// ＡがＢの下に位置する場合、また、左右に触れていない場合
		if ((posA.y + sizeA.y - fPseudo) <= posB.y) return BOTTOM;

		// ＡがＢの左に位置する場合、また、上下に触れていない場合
		if ((posA.x + sizeA.x - fPseudo) <= posB.x) return LEFT;

		// ＡがＢの右に位置する場合、また、上下に触れていない場合
		if ((posA.x + fPseudo) >= (posB.x + sizeB.x)) return RIGHT;

	}//if.fin

	// 衝突なし
	return NONE;

}

/*-----------------------------------------------------------------------------
 矩形と点の衝突判定
-----------------------------------------------------------------------------*/
bool C2DCollision::ColPoint_Rect
(D3DXVECTOR3 point, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	if ((pos.x < point.x) &&
		(point.x < (pos.x + size.x)) &&
		((pos.y + size.y) > point.y) &&
		(point.y > pos.y))
	{
		// 衝突あり
		return true;
	}//if.fin

	// 衝突なし
	return false;

}
