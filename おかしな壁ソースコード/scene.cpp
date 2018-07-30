/*=============================================================================

 シーン共通処理[ scene.cpp ]

=============================================================================*/
/*=============================================================================
 インクルードヘッダ
=============================================================================*/
#include "scene.h"

/*=============================================================================
 メンバ変数の動的メモリ確保
=============================================================================*/
CScene *CScene :: m_apScene[NUM_SCENE] = {};
int     CScene :: m_nNumScene = 0;

/*-----------------------------------------------------------------------------
 コンストラクタ
-----------------------------------------------------------------------------*/
CScene :: CScene()
{
	// オブジェクトカウンタ
	for(int nCntScene = 0; nCntScene < NUM_SCENE; nCntScene++)
	{
		// NULLCHECK
		if(m_apScene[nCntScene] == NULL)
		{
			m_apScene[nCntScene] = this;		// 自身の登録処理
			m_nID = nCntScene;					// 識別番号の設定
			m_nNumScene++;						// カウントアップ

			break;

		}//if.fin

	}//for.fin

}

/*-----------------------------------------------------------------------------
 更新統括処理
-----------------------------------------------------------------------------*/
void CScene :: UpdateAll(void)
{
	// インスタンス化されたオブジェクトの更新
	for(int nCntScene = 0; nCntScene < NUM_SCENE; nCntScene++)
	{
		// NULLCHECK
		if(m_apScene[nCntScene] != NULL)
		{
			m_apScene[nCntScene] -> Update();
		}//if.fin

	}//for.fin

}

/*-----------------------------------------------------------------------------
 描画統括処理
-----------------------------------------------------------------------------*/
void CScene :: DrawAll(void)
{
	// インスタンス化されたオブジェクトの描画
	for(int nCntScene = 0; nCntScene < NUM_SCENE; nCntScene++)
	{
		// NULLCHECK
		if(m_apScene[nCntScene] != NULL)
		{
			m_apScene[nCntScene] -> Draw();
		}//if.fin

	}//for.fin

}

/*-----------------------------------------------------------------------------
 解放統括処理
-----------------------------------------------------------------------------*/
void CScene :: ReleaseAll(void)
{
	// インスタンス化されたオブジェクトの終了
	for(int nCntScene = 0; nCntScene < NUM_SCENE; nCntScene++)
	{
		// NULLCHECK
		if(m_apScene[nCntScene] != NULL)
		{
			m_apScene[nCntScene] -> Uninit();

			// メモリ開放
			delete m_apScene[nCntScene];
			m_apScene[nCntScene] = NULL;

		}//if.fin

	}//for.fin

}

/*-----------------------------------------------------------------------------
 解放処理
-----------------------------------------------------------------------------*/
void CScene :: Release(void)
{
	// NLLCHECK
	if(m_apScene[m_nID] != NULL)
	{
		// 識別番号の退避
		int nID = m_nID;

		// 番号の内データの破棄
		delete m_apScene[nID];
		m_apScene[nID] = NULL;

		// カウントダウン
		m_nNumScene--;

	}//if.fin

}



