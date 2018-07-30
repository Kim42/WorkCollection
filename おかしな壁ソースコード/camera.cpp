/*=============================================================================

 カメラ処理[ camera.cpp ]

=============================================================================*/
/*=============================================================================
 インクルードヘッダ
=============================================================================*/
#include "manager.h"
#include "renderer.h"
#include "camera.h"

#include "player.h"
#include "action.h"

/*=============================================================================
 メンバ変数の動的宣言
=============================================================================*/
D3DXVECTOR3 CCamera :: m_At  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CCamera :: m_Eye = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CCamera :: m_Up  = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

D3DXMATRIX  CCamera :: m_mtxProjection;
D3DXMATRIX  CCamera :: m_mtxView;

float       CCamera ::m_fZoom = 60.0f;

/*-----------------------------------------------------------------------------
 初期化処理関数
-----------------------------------------------------------------------------*/
HRESULT CCamera :: Init(D3DXVECTOR3 At, D3DXVECTOR3 Eye)
{
	// 値の初期化
	m_At = At;
	m_Eye = Eye;

	// 正常終了
	return S_OK;

}

/*-----------------------------------------------------------------------------
 終了処理関数
-----------------------------------------------------------------------------*/
void CCamera :: Uninit(void)
{
	// 使用したメンバ変数のゼロ初期化
	m_At  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Eye = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Up  = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

}

/*-----------------------------------------------------------------------------
 更新処理関数
-----------------------------------------------------------------------------*/
void CCamera :: Update(void)
{
	// シーンオブジェクト数分のループ
	for (int nCnt = 0; nCnt < NUM_SCENE; nCnt++)
	{
		// IDの取得
		CScene *pScene = CScene::GetScene(nCnt);

		// NULLCHECK
		if (pScene == NULL) continue;

		// オブジェクトタイプの識別
		if (pScene->GetObjType() == TYPE_PLAYER)
		{
			CPlayer *pClass = (CPlayer*)pScene;

			// カメラポジション
			m_Eye.z = -13.0f;

			 // プレイヤーポジションＸが１０以上、６０以下の場合
			if ((pClass->GetPos().x > 10.0f) && (pClass->GetPos().x < 60.0f))
			{
				m_At.x = pClass->GetPos().x;
				m_Eye.x = pClass->GetPos().x;
			}
			else if (pClass->GetPos().x < 10.0f)
			{
				m_At.x = 10.0f;
				m_Eye.x = 10.0f;
			}
			else if (pClass->GetPos().x > 60.0f)
			{
				m_At.x = 60.0f;
				m_Eye.x = 60.0f;
			}//if.fin

			// プレイヤーポジションＹが５．５以上の場合
			if (pClass->GetPos().y > 5.5f)
			{
				m_At.y = pClass->GetPos().y;
				m_Eye.y = pClass->GetPos().y;
			}
			else
			{
				m_At.y = 5.5f;
				m_Eye.y = 5.5f;
			}//if.fin

		}//if.fin

	}//for.fin

}

/*-----------------------------------------------------------------------------
 設置処理関数
-----------------------------------------------------------------------------*/
void CCamera :: Set(void)
{
	// 頂点フォーマットの設定
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// マトリクスの正規化
	D3DXMatrixIdentity(&m_mtxView);
	
	// ビューポートマトリクスの設定
	D3DXMatrixLookAtLH(&m_mtxView, &m_Eye, &m_At, &m_Up);

	// ビューポートマトリクスの座標変換を行う
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
	
	// マトリクスの正規化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクション(投影)マトリクスの設置
	D3DXMatrixPerspectiveFovLH(
		&m_mtxProjection,							// プロジェクションマトリクスアドレス
		D3DXToRadian(m_fZoom),						// 画角(視野角度)
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,		// アスペクト比：６０度
		0.1f,										// NEAR 近場(必ず０より大きく)
		100.0f);									// FAR  遠場

	// プロジェクションマトリクスの座標変換を行う
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

}

