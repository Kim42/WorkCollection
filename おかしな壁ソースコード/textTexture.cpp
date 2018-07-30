/*=============================================================================

 テキストテクスチャ表示処理[ texttexture.cpp ]

=============================================================================*/
/*=============================================================================
 インクルードヘッダ
=============================================================================*/
#include "manager.h"
#include "mode.h"
#include "textTexture.h"
#include "fade.h"
#include "sound.h"

/*=============================================================================
 2D頂点情報構造体
=============================================================================*/
struct VERTEX_2D
{
	D3DXVECTOR3 pos;		// 座標位置
	float       rhw;		// 変換済み座標
	D3DCOLOR    col;		// 色
	D3DXVECTOR2 tex;		// テクスチャ座標
};

/*=============================================================================
 静的メンバの動的確保
=============================================================================*/
int CTextTexture::m_nCursor = NEXT_STAGE;

/*-----------------------------------------------------------------------------
 生成処理
-----------------------------------------------------------------------------*/
CTextTexture *CTextTexture::Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 使用宣言
	CTextTexture *pText;

	// クラスの生成
	pText = new CTextTexture;

	// 初期化
	pText->Init(nTexType, pos, size);

	// クラスポインタを返す
	return pText;

}

/*-----------------------------------------------------------------------------
初期化処理
-----------------------------------------------------------------------------*/
HRESULT CTextTexture::Init(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_Pos = pos;
	m_Size = size;
	m_nTexType = nTexType;

	// オブジェクトの初期化
	CScene2D::Init();

	// 正常終了
	return S_OK;

}

/*-----------------------------------------------------------------------------
 終了処理
-----------------------------------------------------------------------------*/
void CTextTexture::Uninit(void)
{
	// オブジェクトの破棄
	CScene2D::Uninit();

}

/*-----------------------------------------------------------------------------
 更新処理
-----------------------------------------------------------------------------*/
void CTextTexture::Update(void)
{
	// ゲームパッド使用宣言
	CInputGamePad *pGamePad = CManager::GetInputGamePad();

	if (m_nTexType == SELECT)
	{
		static int nCus1 = STAGE_SELECT, nCus2 = RETRY;
		int nEmpty1;

		if (CInputGamePad::POV_UP == pGamePad->GetPadPOVRepeat())
		{
			// SE 再生
			CManager::GetSound()->Play(CSound::SE_CURSOR);

			nEmpty1   = nCus2;
			nCus2     = nCus1;
			nCus1     = m_nCursor;
			m_nCursor = nEmpty1;

			// SE 停止
			CManager::GetSound()->Stop(CSound::SE_CURSOR);
		}
		
		if (CInputGamePad::POV_DOWN == pGamePad->GetPadPOVTrigger())
		{
			// SE 再生
			CManager::GetSound()->Play(CSound::SE_CURSOR);

			nEmpty1   = m_nCursor;
			m_nCursor = nCus1;
			nCus1     = nCus2;
			nCus2     = nEmpty1;

			// SE 停止
			CManager::GetSound()->Stop(CSound::SE_CURSOR);
		}//if.fin

		// 座標の設定
		switch (m_nCursor)
		{
			case NEXT_STAGE:

				// 次のステージへ遷移
				// 現ステージが最終ステージの場合は最初のステージへ
				if (pGamePad->GetPadButtonTrigger(CInputGamePad::GB_A))
				{
					// オブジェクトの破棄
					CScene::ReleaseAll();

					CManager::m_nNowStage++;

					if (CManager::m_nNowStage > 6) CManager::m_nNowStage = 1;

					CManager::SetMode(new CModeGame, CManager::m_nNowStage);

					return;
				}//if.fin
					

				m_Pos.y = 300.0f;
				break;

			case STAGE_SELECT:

				// ステージセレクトへ遷移
				if (pGamePad->GetPadButtonTrigger(CInputGamePad::GB_A)) 
				{
					// オブジェクトの破棄
					CScene::ReleaseAll();

					CManager::SetMode(new CModeStageSelect);

					return;
				}//if.fin

				m_Pos.y = 380.0f;
				break;

			case RETRY:

				// もう１度このステージをプレイ
				if (pGamePad->GetPadButtonTrigger(CInputGamePad::GB_A))
				{
					// オブジェクトの破棄
					CScene::ReleaseAll();

					CManager::SetMode( new CModeGame , CManager::m_nNowStage);

					return;
				}//if.fin

				m_Pos.y = 460.0f;
				break;
		}//switch.fin

		// オブジェクトの更新
		CScene2D::Update();

	}//if.fin

}

/*-----------------------------------------------------------------------------
 描画処理
-----------------------------------------------------------------------------*/
void CTextTexture::Draw(void)
{
	// オブジェクトの描画
	CScene2D::Draw();

}

