/*=============================================================================

 管理処理[ manager.cpp ]

=============================================================================*/
/*=============================================================================
インクルードヘッダ
=============================================================================*/
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "sound.h"
#include "scene.h"

#include "mode.h"
#include "fade.h"

/*=============================================================================
 メンバ変数の動的宣言
=============================================================================*/
CInputKeyboard  *CManager :: m_pInputKeyboard  = NULL;
CInputGamePad  *CManager :: m_pInputGamePad  = NULL;
CMode* CManager::m_pMode = NULL;
CSound* CManager::m_Sound = NULL;
CFade* CManager::m_pFade = NULL;

int CManager::m_nNowStage = 0;

/*-----------------------------------------------------------------------------
 初期化処理関数
-----------------------------------------------------------------------------*/
HRESULT CManager :: Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// レンダラーの生成
	CRenderer :: Init(hInstance, hWnd, bWindow);

	// テクスチャデータの読み込み
	CTexture::Load();

	// サウンドデータの読み込み
	m_Sound = new CSound;
	m_Sound->Init(hWnd);

	// インプット：キーボードの生成
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	// インプット：ゲームパッドの生成
	m_pInputGamePad = new CInputGamePad;
	m_pInputGamePad->Init(hInstance, hWnd);

	// ゲームパッド未接続の場合
	//if (!m_pInputGamePad->GetGamePad()) return E_FAIL;

	// フェードの生成
	m_pFade = CFade::Create(TEX_FADE, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));

	// フェードセット
	m_pFade->SetFade(CFade::FADE_IN);

	// セットモード：タイトル
	SetMode(new CModeTitle);

	// 正常終了
	return S_OK;
	
}

/*-----------------------------------------------------------------------------
 終了処理関数
-----------------------------------------------------------------------------*/
void CManager :: Uninit(void)
{
	// フェードの破棄
	SAFE_DELETE_Ex(m_pFade);

	// モードの破棄
	if( m_pMode != NULL )
	{
		m_pMode->Uninit();
		delete m_pMode;
	}//if.fin

	// シーンオブジェクトの統括解放・破棄
	CScene::ReleaseAll();

	// サウンドデータの解放
	m_Sound->Uninit();

	// テクスチャデータの解放
	CTexture::Release();

	// レンダラ破棄
	CRenderer :: Uninit();

	// インプット処理の破棄
	SAFE_DELETE_Ex(m_pInputKeyboard);
	SAFE_DELETE_Ex(m_pInputGamePad);

}

/*-----------------------------------------------------------------------------
 更新処理
-----------------------------------------------------------------------------*/
void CManager :: Update(void)
{
	// インプット：ゲームパッド更新
	m_pInputKeyboard->Update();
	m_pInputGamePad->Update();

	// モード更新
	m_pMode->Update();

	// フェード更新
	m_pFade->Update();

	// シーンオブジェクトの更新
	CScene::UpdateAll();

}

/*-----------------------------------------------------------------------------
 描画管理処理
-----------------------------------------------------------------------------*/
void CManager :: Draw(void)
{
	// レンダリング開始
	if(SUCCEEDED(CRenderer :: DrawBigen()))
	{
		// モード描画
		m_pMode->Draw();

		// シーンオブジェクトの描画
		CScene::DrawAll();

		// フェード描画
		m_pFade->Draw();

	}//if.fin

	// レンダリング終了
	CRenderer :: DrawEnd();

}


/*******************************************************************************
モードのあれをあれする関数
*******************************************************************************/
void CManager::SetMode( CMode *pMode )
{
	if( m_pMode != NULL )
	{
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = NULL;
	}

	m_pMode = pMode;

	if( m_pMode != NULL )
	{
		m_pMode->Init();
	}
}

/*******************************************************************************
モードのあれをあれする関数(その弐)
*******************************************************************************/
void CManager::SetMode( CMode *pMode , int StageID)
{
	if( m_pMode != NULL )
	{
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = NULL;
	}

	m_pMode = pMode;

	if( m_pMode != NULL )
	{
		m_pMode->Init(StageID);
	}
}

