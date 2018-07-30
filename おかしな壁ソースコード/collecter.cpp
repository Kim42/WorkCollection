/*=============================================================================

 コレクター処理[ collecter.cpp ]

=============================================================================*/
/*=============================================================================
 インクルードヘッダ
=============================================================================*/
#include "manager.h"
#include "collecter.h"
#include "number.h"

/*-----------------------------------------------------------------------------
 生成処理
-----------------------------------------------------------------------------*/
CCollecter *CCollecter::Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 使用宣言
	CCollecter *pScore;

	// スコアの生成
	pScore = new CCollecter;

	// 初期化
	pScore->Init(nTexType, pos, size);

	// クラスポインタを返す
	return pScore;

}

/*-----------------------------------------------------------------------------
 初期化処理
-----------------------------------------------------------------------------*/
HRESULT CCollecter::Init(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_Pos = pos;
	m_Size = size;
	m_nTexType = nTexType;

	// 変数宣言
	int nNumber, snbNumber = 0;

	// 指定桁数分のループ
	for (int nCnt = 0; nCnt < NUM_DIGIT_C; nCnt++)
	{
		// 桁分け
		nNumber = snbNumber % 10;
		snbNumber /= 10;

		// ナンバーの生成：各桁の数字の値の設定
		m_apNumber[nCnt] = CNumber::Create(COUNT_NUMBER,
			D3DXVECTOR3((pos.x + size.x * 1.5f) - 35.0f * nCnt, pos.y, 0.0f),
			D3DXVECTOR3(40.0f, size.y, 0.0f), nNumber);
	}//for.fin

	// オブジェクト初期化
	CScene2D::Init();

	// 正常終了
	return S_OK;

}

/*-----------------------------------------------------------------------------
 終了処理
-----------------------------------------------------------------------------*/
void CCollecter::Uninit(void)
{
	// 指定桁数分のループ
	for (int nCnt = 0; nCnt < NUM_DIGIT_C; nCnt++)
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
void CCollecter::Update(void)
{
	// 変数宣言
	int nNumber, snbNumber;

	// スコアの退避
	snbNumber = m_nNumCollect;

	// 数字の設定
	for (int nCnt = 0; nCnt < NUM_DIGIT_C; nCnt++)
	{
		// 各桁の数字の算出
		nNumber = snbNumber % 10;
		snbNumber /= 10;

		// 各桁の数字の値設定
		m_apNumber[nCnt]->SetNumber(nNumber);

	}//for.fin

}

/*-----------------------------------------------------------------------------
 描画処理
-----------------------------------------------------------------------------*/
void CCollecter::Draw(void)
{
	// スコアの表示の数値の設定
	for (int nCnt = 0; nCnt < NUM_DIGIT_C; nCnt++)
	{
		// ナンバー描画
		m_apNumber[nCnt]->Draw();
	}//for.fin

	// オブジェクト描画
	CScene2D::Draw();

}

