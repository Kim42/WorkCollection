/*=============================================================================

 タイマー処理[ timer.cpp ]

=============================================================================*/
/*=============================================================================
インクルードヘッダ
=============================================================================*/
#include "manager.h"
#include "timer.h"
#include "number.h"

/*=============================================================================
 マクロ定義
=============================================================================*/
#define FRAME 60

/*-----------------------------------------------------------------------------
 コンストラクタ
-----------------------------------------------------------------------------*/
CTimer::CTimer()
{
	SetObjType(TYPE_TIMER);

	m_bTimer = true;
	m_nTimer = 0;
	m_nFrameTimer = 0;

}

/*-----------------------------------------------------------------------------
 デスクトラクタ
-----------------------------------------------------------------------------*/
CTimer :: ~CTimer()
{

}

/*-----------------------------------------------------------------------------
 生成処理
-----------------------------------------------------------------------------*/
CTimer *CTimer::Create(int nTexType, int nTimeMax, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 使用宣言
	CTimer *pScore;

	// スコアの生成
	pScore = new CTimer;

	// 初期化
	pScore->Init(nTexType, nTimeMax, pos, size);

	// クラスポインタを返す
	return pScore;

}

/*-----------------------------------------------------------------------------
 初期化処理
-----------------------------------------------------------------------------*/
HRESULT CTimer::Init(int nTexType, int nTimeMax, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_Pos      = pos;
	m_Size     = size;
	m_nTexType = nTexType;
	m_nTimer   = nTimeMax;

	// 変数宣言
	int nNumber, snbNumber = m_nTimer;

	// 指定桁数分のループ
	for (int nCnt = 0; nCnt < NUM_DIGIT_T; nCnt++)
	{
		// 桁分け
		nNumber = snbNumber % 10;
		snbNumber /= 10;

		// ナンバーの生成：各桁の数字の値の設定
		m_apNumber[nCnt] = CNumber::Create(TIME_NUMBER, 
											D3DXVECTOR3((pos.x + size.x * 2.2f) - 35.0f * nCnt, pos.y - 10.0f, 0.0f),
											D3DXVECTOR3(40.0f, 75.0f, 0.0f), nNumber);
	}//for.fin

	// オブジェクト初期化
	CScene2D::Init();

	// 正常終了
	return S_OK;

}

/*-----------------------------------------------------------------------------
 終了処理
-----------------------------------------------------------------------------*/
void CTimer::Uninit(void)
{
	// 指定桁数分のループ
	for (int nCnt = 0; nCnt < NUM_DIGIT_T; nCnt++)
	{
		// ナンバーの破棄
		m_apNumber[nCnt]->Uninit();
	}//for.fin

	// オブジェクト終了
	CScene2D::Uninit();

}

/*-----------------------------------------------------------------------------
 更新処理
-----------------------------------------------------------------------------*/
void CTimer::Update(void)
{
	if (m_bTimer == true)
	{
		// フレームカウントアップ
		m_nFrameTimer++;

		// 変数宣言
		int nNumber, snbNumber;

		// カウントダウン
		if (m_nFrameTimer >= FRAME)
		{
			m_nTimer--;
			m_nFrameTimer = 0;
		}//if.fin

		// スコアの退避
		snbNumber = m_nTimer;

		// 数字の設定
		for (int nCnt = 0; nCnt < NUM_DIGIT_T; nCnt++)
		{
			// 各桁の数字の算出
			nNumber = snbNumber % 10;
			snbNumber /= 10;

			// 各桁の数字の値設定
			m_apNumber[nCnt]->SetNumber(nNumber);

		}//for.fin

	}//if.fin

}

/*-----------------------------------------------------------------------------
 描画処理
-----------------------------------------------------------------------------*/
void CTimer::Draw(void)
{
	// スコアの表示の数値の設定
	for (int nCnt = 0; nCnt < NUM_DIGIT_T; nCnt++)
	{
		// ナンバー描画
		m_apNumber[nCnt]->Draw();
	}//for.fin

	// オブジェクト描画
	CScene2D::Draw();

}

