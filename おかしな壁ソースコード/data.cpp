/*=============================================================================

 データ管理[ data.cpp ]

=============================================================================*/
/*=============================================================================
インクルードヘッダ
=============================================================================*/
#include <stdio.h>

#include "manager.h"
#include "data.h"

// 管理するデータ
#include "texture.h"
#include "scene3D.h"

// 生成処理
#include "player.h"
#include "wall.h"
#include "field.h"
#include "item.h"
#include "switch.h"

/*-----------------------------------------------------------------------------
 ファイル使用による警告のパス
-----------------------------------------------------------------------------*/
#pragma warning(disable:4996)

/*-----------------------------------------------------------------------------
 データロード
-----------------------------------------------------------------------------*/
void CData :: Load(const char *pFileName)
{
	// 変数宣言
	int nLineCheck;

	// 構造体使用宣言
	OBJ_BASE base;

	// ファイルオープン
	FILE *pFile = fopen(pFileName, "r");

	// NULLCHECK
	if (pFile != NULL)
	{
		// シーンオブジェクトの統括解放・破棄
		CScene::ReleaseAll();

		// ファイルからデータの読み込み
		while ((nLineCheck = fscanf(pFile,							// ファイルポインタ
			"%d,%d,%d,%f,%f,%f,%f,%f,%f\n",							// 読み込む羅列
			&base.nType, 											// オブジェクトタイプ
			&base.nSubType, 										// 派生オブジェクトタイプ
			&base.nTexType, 										// テクスチャタイプ
			&base.pos.x, &base.pos.y, &base.pos.z,					// ポジションデータ
			&base.size.x, &base.size.y, &base.size.z)) != EOF)		// サイズデータ
		{
			switch (base.nType)
			{
				case TYPE_PLAYER:
					CPlayer::Create(base.nTexType, base.pos, base.size);
					break;

				case TYPE_WALL:
					CWall::Create(base.nTexType, base.pos, base.size, base.nSubType);
					break;

				case TYPE_FIELD:
					CField::Create(base.nTexType, base.pos, base.size);
					break;

				case TYPE_ITEM:
					CItem::Create(base.nTexType, base.pos, base.size, base.nSubType);
					break;

				case TYPE_SWITCH:
					CSwitch::Create(base.nTexType, base.pos, base.size, base.nSubType);
					break;

			}//switch.fin

		}//while.fin

	}
	else
	{
		MessageBox(NULL, "オブジェクトデータのロードに失敗しました", "エラー", MB_OK);
	}//if.fin

	// クローズ
	fclose(pFile);

}

