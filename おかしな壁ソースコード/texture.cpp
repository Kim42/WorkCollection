/*=============================================================================

 テクスチャ管理処理[ texture.cpp ]

=============================================================================*/
/*=============================================================================
 インクルードヘッダ
=============================================================================*/
#include <stdio.h>

#include "manager.h"
#include "renderer.h"
#include "texture.h"

/*-----------------------------------------------------------------------------
ファイル使用による警告のパス
-----------------------------------------------------------------------------*/
#pragma warning(disable:4996)

/*=============================================================================
 メンバ変数の動的宣言
=============================================================================*/
LPDIRECT3DTEXTURE9 *CTexture :: m_pTextureEx  = NULL;
int                 CTexture :: m_nNumTexture = 0;

/*-----------------------------------------------------------------------------
 読み込み処理関数
-----------------------------------------------------------------------------*/
HRESULT CTexture :: Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// オープン(w で新規書き込み・ a で追加書き込み)
	FILE *pFile = fopen("DATA/FILE/texture.txt", "r");

	// NULLCHECK
	if (pFile != NULL)
	{
		// 文字列格納ポインタ
		char aTexNam[36] = {};

		// テクスチャ枚数の取得
		fscanf(pFile, "%d\n", &m_nNumTexture);

		// インターフェースの動的確保：テクスチャ枚数分
		m_pTextureEx = new LPDIRECT3DTEXTURE9[m_nNumTexture];

		// テクスチャの生成
		for(int i = 0; i < m_nNumTexture; i++)
		{
			// ファイルから文字列の取得
			if (fscanf(pFile, "%s\n", aTexNam) != EOF)
			{
				// テクスチャの生成
				if (FAILED(D3DXCreateTextureFromFile(pDevice, aTexNam, &m_pTextureEx[i])))
				{
					MessageBox(NULL, "テクスチャの読み込み失敗しました", "エラー", MB_OK);
					break;
				}//if.fin

			}//if.fin

		}//for.fin

	}
	else
	{
		MessageBox(NULL, "テクスチャデータのロードに失敗しました", "エラー", MB_OK);
	}//if.fin

	// クローズ
	fclose(pFile);

	// 正常終了
	return S_OK;

}

/*-----------------------------------------------------------------------------
 解放処理関数
-----------------------------------------------------------------------------*/
void CTexture :: Release(void)
{
	// テクスチャインターフェースの解放
	for (int i = 0; i < m_nNumTexture; i++) SAFE_RELEASE(*&m_pTextureEx[i]);

	// まとめ破棄
	delete[] m_pTextureEx;

}

