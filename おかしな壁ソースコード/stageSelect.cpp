/*=============================================================================

ステージセレクト[ stageSelect.cpp ]

=============================================================================*/
/*=============================================================================
インクルードヘッダ
=============================================================================*/
#include "manager.h"
#include "stageSelect.h"
/*=============================================================================
３Ｄ頂点情報構造体
=============================================================================*/
struct VERTEX_3D
{
	D3DXVECTOR3 pos;		// 座標位置
	D3DXVECTOR3 nor;		// 法線
	D3DCOLOR    col;		// 色
	D3DXVECTOR2 tex;		// テクスチャ座標
};

/*-----------------------------------------------------------------------------
生成関数
-----------------------------------------------------------------------------*/
CStageSelect *CStageSelect::Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 変数クラス定義
	CStageSelect *pClass;

	// インスタンスの生成
	pClass = new CStageSelect;

	// 初期化
	pClass->Init(nTexType, pos, size);

	// 返還
	return pClass;

}

/*-----------------------------------------------------------------------------
初期化処理関数
-----------------------------------------------------------------------------*/
HRESULT CStageSelect::Init(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 引数の代入
	m_Pos = pos;
	m_Size = size;
	m_nTexType = nTexType;

	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nCounterState = 0;
	m_fAlpha = 1.0f;
	m_nAlphaPlus = 0;

	// オブジェクト初期化
	CScene3D::Init();

	// ポインタ変数
	VERTEX_3D* pVtx;

	// バッファをロックし仮想アドレスを取得する
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);

	// バッファをアンロック
	m_pVtxBuff->Unlock();

	// 正常終了
	return S_OK;

}

/*-----------------------------------------------------------------------------
更新処理関数
-----------------------------------------------------------------------------*/
void CStageSelect::Update(void)
{
	// ぴかぴか
	if (m_nTexType == STAGESELECT000)
	{
		m_color.a = m_fAlpha;

		if (m_nAlphaPlus == 0)
		{
			if ((m_fAlpha = max((m_fAlpha - 0.020f), 0.0f)) <= 0.0f)
			{
				m_nAlphaPlus ^= 1;
			}
		}
		else
		{
			if ((m_fAlpha = min((m_fAlpha + 0.020f), 1.0f)) >= 1.0f)
			{
				m_nAlphaPlus ^= 1;
			}
		}

		// ポインタ変数
		VERTEX_3D* pVtx;

		// バッファをロックし仮想アドレスを取得する
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].col = D3DXCOLOR(m_color.r, m_color.g, m_color.b, m_color.a);
		pVtx[1].col = D3DXCOLOR(m_color.r, m_color.g, m_color.b, m_color.a);
		pVtx[2].col = D3DXCOLOR(m_color.r, m_color.g, m_color.b, m_color.a);
		pVtx[3].col = D3DXCOLOR(m_color.r, m_color.g, m_color.b, m_color.a);

		// バッファをアンロック
		m_pVtxBuff->Unlock();

	}//if.fin

}
