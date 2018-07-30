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
#include "title.h"
#include "sound.h"
#include "scene.h"

#include "light.h"
#include "camera.h"
#include "bg.h"

#include "player.h"
#include "field.h"

#include "textTexture.h"

#include "fade.h"

/*******************************************************************************
* マクロ定義
*******************************************************************************/

/*******************************************************************************
* 静的メンバ変数
*******************************************************************************/

/*******************************************************************************
初期化関数
*******************************************************************************/
void CModeTitle::Init( void )
{
	CTitle::Create(D3DXVECTOR3(100.0f, 5.0f, 0.0f), D3DXVECTOR3(800, 400, 0.0f));

	// バックグラウンド初期化
	CBg::Init(SWEET_BG2);

	// カメラの初期化
	CCamera :: Init(D3DXVECTOR3(10.0f, 4.0f, 0.0f), D3DXVECTOR3(10.0f, 4.0f, -13.0f));

	// プレイヤー生成
	CPlayer :: Create(WALK2, D3DXVECTOR3(13.0f, -2.0f, 0.0f), D3DXVECTOR3(1.0f, 1.5f, 0.0f));

	// 規定床
	CField::Create(YUKA, D3DXVECTOR3(-3.0f, -4.0f, 0.0f), D3DXVECTOR3(30.0f, 2.0f, 0.0f));

	// 文字
	CTextTexture::Create(START, D3DXVECTOR3(280.0f, 400.0f, 0.0f), D3DXVECTOR3(450.0f, 70.0f, 0.0f));

	// BGM 再生
	CManager::GetSound()->Play(CSound::TITLE_BGM);

}

/*******************************************************************************
終了関数
*******************************************************************************/
void CModeTitle::Uninit( void )
{
	// BGM 停止
	CManager::GetSound()->Stop(CSound::TITLE_BGM);

	CBg::Uninit();

	// 全てをリリース
	CScene::ReleaseAll();
}


/*******************************************************************************
更新関数
*******************************************************************************/
void CModeTitle::Update( void )
{
	// ゲームパッド使用宣言
	CInputGamePad *pGamePad = CManager::GetInputGamePad();

	CBg::Update();

	if(pGamePad->GetPadButtonTrigger(CInputGamePad::GB_A))
	{
		// SE
		CManager::GetSound()->Play(CSound::SE_SKILL_SWAP);

		CManager::SetMode(new CModeStageSelect);

		// SE
		CManager::GetSound()->Stop(CSound::SE_SKILL_SWAP);
	}

}

/*******************************************************************************
描画関数
*******************************************************************************/
void CModeTitle::Draw( void )
{
	// ライト設置
	CLight :: Set();

	// カメラの設置
	CCamera :: Set();

	CBg::Draw();

}

