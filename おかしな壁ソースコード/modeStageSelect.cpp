/*============================================================================

ポリゴン表示[manager.cpp]

Author: Miyu Ishikawa
Date: 2017/04/26

=============================================================================*/

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "manager.h"
#include "mode.h"
#include "stageSelect.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "bg.h"

#include "textTexture.h"
#include "fade.h"

#define MAX_SELECT 7

/*******************************************************************************
* グローバル変数
*******************************************************************************/
CStageSelect* g_pSelect[MAX_SELECT] = {};

/*******************************************************************************
初期化関数
*******************************************************************************/
void CModeStageSelect::Init(void)
{
	// バックグラウンド初期化
	CBg::Init(SWEET_BG);

	// ステージセレクターの生成：すべて原点に配置
	g_pSelect[0] = CStageSelect::Create(STAGESELECT000, D3DXVECTOR3(0.0f, 0.3f, 0.0f), D3DXVECTOR3(7.5f, 6.5f, 0.0f));
	g_pSelect[1] = CStageSelect::Create(STAGESELECT001, D3DXVECTOR3(0.0f, 0.3f, 0.0f), D3DXVECTOR3(7.0f, 6.0f, 0.0f));
	g_pSelect[2] = CStageSelect::Create(STAGESELECT002, D3DXVECTOR3(7.0f, 0.3f, 0.0f), D3DXVECTOR3(7.0f, 6.0f, 0.0f));
	g_pSelect[3] = CStageSelect::Create(STAGESELECT003, D3DXVECTOR3(7.0f * 2.0f, 0.3f, 0.0f), D3DXVECTOR3(7.0f, 6.0f, 0.0f));
	g_pSelect[4] = CStageSelect::Create(STAGESELECT004, D3DXVECTOR3(7.0f * 3.0f, 0.3f, 0.0f), D3DXVECTOR3(7.0f, 6.0f, 0.0f));
	g_pSelect[5] = CStageSelect::Create(STAGESELECT005, D3DXVECTOR3(7.0f * 4.0f, 0.3f, 0.0f), D3DXVECTOR3(7.0f, 6.0f, 0.0f));
	g_pSelect[6] = CStageSelect::Create(STAGESELECT006, D3DXVECTOR3(7.0f * 5.0f, 0.3f, 0.0f), D3DXVECTOR3(7.0f, 6.0f, 0.0f));
	//g_pSelect[7] = CStageSelect::Create(STAGESELECT000, D3DXVECTOR3(7.0f * 6.0f, 0.3f, 0.0f), D3DXVECTOR3(7.0f, 6.0f, 0.0f));
	//g_pSelect[8] = CStageSelect::Create(STAGESELECT000, D3DXVECTOR3(7.0f * 7.0f, 0.3f, 0.0f), D3DXVECTOR3(7.0f, 6.0f, 0.0f));
	//g_pSelect[9] = CStageSelect::Create(STAGESELECT000, D3DXVECTOR3(7.0f * 8.0f, 0.3f, 0.0f), D3DXVECTOR3(7.0f, 6.0f, 0.0f));
	//g_pSelect[10] = CStageSelect::Create(STAGESELECT000, D3DXVECTOR3(7.0f * 9.0f, 0.3f, 0.0f), D3DXVECTOR3(7.0f, 6.0f, 0.0f));

	// 文字
	CTextTexture::Create(OK, D3DXVECTOR3(280.0f, 530.0f, 0.0f), D3DXVECTOR3(400.0f, 70.0f, 0.0f));

	// BGM 再生
	CManager::GetSound()->Play(CSound::SELECT_BGM);

}

/*******************************************************************************
終了関数
*******************************************************************************/
void CModeStageSelect::Uninit( void )
{
	// BGM 停止
	CManager::GetSound()->Stop(CSound::SELECT_BGM);

	// 全てをリリース
	CScene::ReleaseAll();
}


/*******************************************************************************
更新関数
*******************************************************************************/
void CModeStageSelect::Update( void )
{
	// ゲームパッド使用宣言
	CInputGamePad *pGamePad = CManager::GetInputGamePad();

	// ステージID
	static int nStageID = 1;
	
	if (pGamePad->GetPadPOVRepeat() == CInputGamePad::POV_RIGHT)
	{
		// SE 再生
		CManager::GetSound()->Play(CSound::SE_CURSOR);

		nStageID++;

		if (nStageID >= MAX_SELECT) nStageID = 1;

		// SE 停止
		CManager::GetSound()->Stop(CSound::SE_CURSOR);
	}

	if (pGamePad->GetPadPOVTrigger() == CInputGamePad::POV_LEFT)
	{
		// SE 再生
		CManager::GetSound()->Play(CSound::SE_CURSOR);

		nStageID--;

		if (nStageID <= 0) nStageID = MAX_SELECT - 1;

		// SE 停止
		CManager::GetSound()->Stop(CSound::SE_CURSOR);
	}//if.fin
	
	// カメラを常に移動
	CCamera::SetCamera(D3DXVECTOR3(3.5f + g_pSelect[nStageID]->GetPos().x, 3.0f, 0.0f), -5.5f);
	g_pSelect[0]->SetPos(D3DXVECTOR3(g_pSelect[nStageID]->GetPos().x - 0.31f,
									 g_pSelect[nStageID]->GetPos().y - 0.25f, 0.0f));

	if(pGamePad->GetPadButtonTrigger(CInputGamePad::GB_A))
	{
		// ステージ番号の確保
		CManager::m_nNowStage = nStageID;

		CManager::SetMode( new CModeGame ,CManager::m_nNowStage);
	}//if.fin

	CBg::Update();

}

/*******************************************************************************
描画関数
*******************************************************************************/
void CModeStageSelect::Draw( void )
{
	// ライト設置
	CLight :: Set();

	// カメラの設置
	CCamera :: Set();

	CBg::Draw();
}

