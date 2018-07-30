/*******************************************************************************
* タイトル:		コンピュータープログラム
* プログラム名:		computer.cpp
* 作成者:		CP11SATA  15  Kim Nakamura
* 作成日:		2016/02/20
********************************************************************************
* 更新履歴:		- 2016/02/20　Kim Nakamura
*			- V1.00　Initial Version
*******************************************************************************/
/*******************************************************************************
* scanf のwarning防止 
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

/*******************************************************************************
* インクルードファイル
*  必要な情報
*  	表示のための基本要素
*  	コンピューター自身の情報
*  	フィールドの情報
*  	アイテムの情報
*  	プレイヤーの情報

*******************************************************************************/
#include "main.h"
#include "computer.h"
#include "field.h"
#include "player.h"

/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define GRAVITY         (0.1f)		// プレイヤーの受ける重力
#define ZERO_GRAVITY    (0.0f)		// ゼログラヴィティ
#define GRAND           (24.0f)		// 地面の位置
#define POSITION        (10)		// 初期位置
#define JUMP            (0.8f)		// ジャンプ力
#define MOVE_HOR        (0.05f)		// 横移動の移動量
#define SLOW            (0.15f)		// 任意の減速量
#define SLOPEWAY        (0.5f)		// 坂登り
#define ACCELERATOR_A   (1.0f)		// 加速アクセル：小
#define ACCELERATOR_B   (1.5f)		// 加速アクセル：中
#define ACCELERATOR_C   (2.0f)		// 加速アクセル：大
#define FLY_A           (0.3f)		// 加速ジャンプに伴う上昇値：小
#define FLY_B           (0.3f)		// 加速ジャンプに伴う上昇値：中
#define FLY_C           (0.3f)		// 加速ジャンプに伴う上昇値：大
#define INTERVAL        (30)		// ジャンプしてからの間隔


/*******************************************************************************
* 構造体定義
*******************************************************************************/


/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/


/*******************************************************************************
* グローバル変数
*******************************************************************************/
// ヘッダーファイルからコンピューター構造体のグローバル宣言
COMPUTER g_computer[THREE];

/*******************************************************************************
* 関数名:	void InitComputer( void ):（初期化）関数
* 引数:		void
* 戻り値:	なし
* 説明:		コンピューターの初期設定
*******************************************************************************/
void InitComputer( void )
{
	// プログラムスタート

	// 変数宣言
	int nCntComputer;

	// コンピューターの数分の初期化
	for(nCntComputer = ZERO_INT; nCntComputer < THREE; nCntComputer++)
	{
		g_computer[nCntComputer].nCnt    = ZERO_INT;		// 場所確認カウンタの初期化
		g_computer[nCntComputer].fPosY   = GRAND;			// コンピューターのＹ軸の初期位置の設定
		g_computer[nCntComputer].fPosX   = POSITION;		// コンピューターのＸ軸の初期位置の設定
		g_computer[nCntComputer].fCountTimer = ZERO_INT;	// タイマーの初期化
		g_computer[nCntComputer].bJump       = false;		// ジャンプしていない状態
		g_computer[nCntComputer].bPushButton = false;		// ボタンが押されていない状態
		g_computer[nCntComputer].bUseCOM     = false;		// まだいない状態
		g_computer[nCntComputer].bGoal       = false;		// ゴールフラグを下しておく
	}//for.fin
	
	// コンピューターの設置（Ｘ軸、Ｙ軸、タイプ）(１：強い、２：ふつう、３：弱い)
	SetCom(7,21,1);
	SetCom(13,22,1);
	SetCom(20,23,2);

	// プログラムエンド
}

/*******************************************************************************
* 関数名:	void UpdateComputer( void ):（更新）関数
* 引数:		void
* 戻り値:	なし
* 説明:		コンピューターの更新処理
*******************************************************************************/
void UpdateComputer( void )
{
	// プログラムスタート

	// 構造体ポインタ変数宣言
	FIELD *pField;						// フィールド構造体の変数
	
	// フィールド情報のコピーの取得
	pField = GetField();

	// 変数宣言
	int nCntComputer;
	int nTheme;
	int nEmpty;

	// コンピューターの数分の初期化
	for(nCntComputer = ZERO_INT; nCntComputer < THREE; nCntComputer++)
	{
		// コンピューターの情報入って使われている時
		if(g_computer[nCntComputer].bUseCOM == true)
		{
			// 2次元配列で使用する変数の宣言
			int nVertical;
			int nHorizontal;
			int nLocateX = ONE_INT;
			int nLocateY = ONE_INT;

			// 前のポジションの取得
			g_computer[nCntComputer].fPosXOld = g_computer[nCntComputer].fPosX;
			g_computer[nCntComputer].fPosYOld = g_computer[nCntComputer].fPosY;

			// 常に右移動（遅め）
			g_computer[nCntComputer].fMoveX += MOVE_HOR;

			// 移動量をポジションに代入
			g_computer[nCntComputer].fPosX += g_computer[nCntComputer].fMoveX;
	
			// 設定最低速度で進行（プレイヤーの移動量を設定速度まで落とす処理）
			g_computer[nCntComputer].fMoveX += (MOVE_HOR - g_computer[nCntComputer].fMoveX) * SLOW;

			// 1画面内ループ
			if(g_computer[nCntComputer].fPosX >= WALL_MAX )
			{
				// エンターキー押されたら通る
				if(pField -> bPlay == true)
				{
					// インクリメント
					g_computer[nCntComputer].nCnt++;
				}//if.fin

				g_computer[nCntComputer].fPosX = WALL_XMIN;
			}//if.fin

			// 空変数に値の格納
			nEmpty = (int)g_computer[nCntComputer].fPosX;

			// 種類によってタイプが違い
			if(g_computer[nCntComputer].nKind == 1)
			{
				nTheme = nEmpty % 1;					// 確率1/1
			}
			else if(g_computer[nCntComputer].nKind == 2)
			{
				nTheme = nEmpty %2;						// 確率1/2
			}
			else if(g_computer[nCntComputer].nKind == 3)
			{
				nTheme = nEmpty %3;						// 確率1/3
			}//if.fin

			// ただのジャンプ
			if( (g_computer[nCntComputer].bJump == false) && nTheme != ZERO_INT && (g_computer[nCntComputer].fCountTimer == ZERO_INT) )
			{
				g_computer[nCntComputer].fMoveY -= JUMP;
				g_computer[nCntComputer].bJump   = true;			// ジャンプしてます！
				g_computer[nCntComputer].bPushButton = true;		// ボタンを押しました！
			}//if.fin

			// ジャンプをしていない時にタイマーが０の場合、コンピューターのジャンプ処理
			if( (g_computer[nCntComputer].bJump == false) && nTheme == ZERO_INT && (g_computer[nCntComputer].fCountTimer == ZERO_INT) )
			{
				g_computer[nCntComputer].fMoveY -= JUMP;
				g_computer[nCntComputer].bJump   = true;			// ジャンプしてます！
				g_computer[nCntComputer].bPushButton = true;		// ボタンを押しました！

				// 2次元配列フィールドの当たり判定、プレイヤー位置との当たり判定
				for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// 縦軸のループ
				{
					for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// 横軸のループ
					{
						// プレイヤーの位置座標とフィールドの位置を比較後、座標位置にある要素番号により要素の確認
						if( ((int)g_computer[nCntComputer].fPosY == nVertical) && ( (int)(g_computer[nCntComputer].fPosX / 2 ) == nHorizontal) && 
							(nTheme == ZERO_INT) )
						{
							// 要素数が加速床の場合の床判定
							if(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == 0)
							{
								// 個の要素番号４：GOOD床の上でボタンフラグが立ったとき
								if((g_computer[nCntComputer].bJump == true) && (pField -> nPosition[nVertical][nHorizontal] == GOOD) && 
									(nTheme == ZERO_INT) )
								{
									// 微妙な加速をして移動量をポジションに代入
									g_computer[nCntComputer].fMoveX += ACCELERATOR_A;
									g_computer[nCntComputer].fPosX += g_computer[nCntComputer].fMoveX;
									g_computer[nCntComputer].fMoveY -= FLY_A;
								}//if.fin

								// 個の要素番号５：VERYGOOD床の上でボタンフラグが立っている時
								if((g_computer[nCntComputer].bJump == true) && (pField -> nPosition[nVertical][nHorizontal] == VERYGOOD) && 
									(nTheme == ZERO_INT) )
								{
									// 加速をして移動量をポジションに代入
									g_computer[nCntComputer].fMoveX += ACCELERATOR_B;
									g_computer[nCntComputer].fPosX += g_computer[nCntComputer].fMoveX;
									g_computer[nCntComputer].fMoveY -= FLY_B;
								}//if.fin

								// 個の要素番号６：EXCELLENT床の上でボタンフラグが立っている時
								if((g_computer[nCntComputer].bJump == true) && (pField -> nPosition[nVertical][nHorizontal] == EXCELLENT) && 
									(nTheme == ZERO_INT) )
								{
									// 大きく加速をして移動量をポジションに代入
									g_computer[nCntComputer].fMoveX += ACCELERATOR_C;
									g_computer[nCntComputer].fPosX += g_computer[nCntComputer].fMoveX;
									g_computer[nCntComputer].fMoveY -= FLY_C;
								}//if.fin

								// 個の要素番号７：GOOD坂の上でボタンフラグが立ったとき
								if((g_computer[nCntComputer].bJump == true) && (pField -> nPosition[nVertical][nHorizontal -1] == S_GOOD) && 
									(nTheme == ZERO_INT) )
								{
									// 微妙な加速をして移動量をポジションに代入
									g_computer[nCntComputer].fMoveX += ACCELERATOR_A;
									g_computer[nCntComputer].fPosX += g_computer[nCntComputer].fMoveX;
									g_computer[nCntComputer].fMoveY -= FLY_A;
								}//if.fin

								// 個の要素番号８：VERYGOOD坂の上でボタンフラグが立っている時
								if((g_computer[nCntComputer].bJump == true) && (pField -> nPosition[nVertical][nHorizontal -1] == S_VERYGOOD) && 
									(nTheme == ZERO_INT) )
								{
									// 加速をして移動量をポジションに代入
									g_computer[nCntComputer].fMoveX += ACCELERATOR_B;
									g_computer[nCntComputer].fPosX += g_computer[nCntComputer].fMoveX;
									g_computer[nCntComputer].fMoveY -= FLY_B;
								}//if.fin

								// 個の要素番号９：EXCELLENT坂の上でボタンフラグが立っている時
								if((g_computer[nCntComputer].bJump == true) && (pField -> nPosition[nVertical][nHorizontal -1] == S_EXCELLENT) && 
									(nTheme == ZERO_INT) )
								{
									// 大きく加速をして移動量をポジションに代入
									g_computer[nCntComputer].fMoveX += ACCELERATOR_C;
									g_computer[nCntComputer].fPosX += g_computer[nCntComputer].fMoveX;
									g_computer[nCntComputer].fMoveY -= FLY_C;
								}//if.fin

							}//if.fin

						}//if.fin

					}//forX.fin

				}//forY.fin
			}
			else if(g_computer[nCntComputer].bPushButton == true)	// ボタン判定がtrueである間
			{
				g_computer[nCntComputer].fCountTimer++;				// フレーム数分カウント
			}//if.fin

			// プレイヤーの受ける重力
			g_computer[nCntComputer].fMoveY += GRAVITY;

			// プレイヤーの移動量をプレイヤーのポジションに代入
			g_computer[nCntComputer].fPosY += g_computer[nCntComputer].fMoveY;

			// 2次元配列フィールドの当たり判定、プレイヤー位置との当たり判定
			for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// 縦軸のループ
			{
				for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// 横軸のループ
				{
					// プレイヤーの位置座標とフィールドの位置を比較後、座標位置にある要素番号により要素の確認
					if( ((int)g_computer[nCntComputer].fPosY == nVertical) && ((int)(g_computer[nCntComputer].fPosX / 2 ) == nHorizontal) )
					{
						// 要素数が１の場合：地面、下にめり込まないようにする
						if(pField -> nPosition[nVertical][nHorizontal] == BLOCK)
						{
							g_computer[nCntComputer].fMoveY = ZERO_GRAVITY;				// 重力を０にする
							g_computer[nCntComputer].bJump  = false;					// ジャンプフラグを下す

							// カウンタがINTERVALに達した時にボタンフラグを下す
							if( (g_computer[nCntComputer].bPushButton == true) &&(g_computer[nCntComputer].fCountTimer > INTERVAL) )
							{
								g_computer[nCntComputer].bPushButton = false;			// ボタンフラグを下す
								g_computer[nCntComputer].fCountTimer = ZERO_INT;		// ０に初期化する
							}//if.fin
						}//if.fin

						// 要素数が２、７、８、９の場合、坂での自動上昇に加え坂の横判定
						if( (pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == SLOPE)      || 
							(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == S_GOOD)     || 
							(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == S_VERYGOOD) || 
							(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == S_EXCELLENT) )
						{
							g_computer[nCntComputer].fPosX += SLOPEWAY;					// Ｘポジを繰り上げる
							g_computer[nCntComputer].fPosY -= SLOPEWAY;					// Ｙポジを繰り上げる
							g_computer[nCntComputer].fMoveY = ZERO_GRAVITY;				// 重力を０にする
							g_computer[nCntComputer].bJump  = false;					// ジャンプフラグを下す

							// カウンタがINTERVALに達した時にボタンフラグを下す
							if( (g_computer[nCntComputer].bPushButton == true) && (g_computer[nCntComputer].fCountTimer > INTERVAL) )
							{
								g_computer[nCntComputer].bPushButton = false;			// ボタンフラグを下す
								g_computer[nCntComputer].fCountTimer = ZERO_INT;		// ０に初期化する
							}//if.fin
						}//if.fin

						// 要素数が３、４、５、６の場合の床判定
						if( (pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == COURSE)   || 
							(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == GOOD)     || 
							(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == VERYGOOD) || 
							(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == EXCELLENT) )
						{
							g_computer[nCntComputer].fPosY -= SLOPEWAY;					// Ｙポジを繰り上げる
							g_computer[nCntComputer].fMoveY = ZERO_GRAVITY;				// 重力を０にする
							g_computer[nCntComputer].bJump  = false;					// ジャンプフラグを下す

							// カウンタがINTERVALに達した時にボタンフラグを下す
							if( (g_computer[nCntComputer].bPushButton == true) && (g_computer[nCntComputer].fCountTimer > INTERVAL) )
							{
								g_computer[nCntComputer].bPushButton = false;			// ボタンフラグを下す
								g_computer[nCntComputer].fCountTimer = ZERO_INT;		// ０に初期化する
							}//if.fin
						}//if.fin

					}//if.fin

				}//forX.fin

			}//forY.fin

			// めり込み前の前回位置の座標の代入
			if(g_computer[nCntComputer].fPosY > GRAND)
			{
				g_computer[nCntComputer].fMoveY = ZERO_GRAVITY;				// 重力を０にする
				g_computer[nCntComputer].fPosY  = GRAND;					// 地面の位置の値の代入
			}//if.fin

		}//if.fin

	}//for.fin

	// プログラムエンド
}

/*******************************************************************************
* 関数名:	void DrawComputer( void ):（描画）関数
* 引数:		void
* 戻り値:	なし
* 説明:		コンピューターの描画処理
*******************************************************************************/
void DrawComputer( void )
{
	// プログラムスタート

	// 変数宣言
	int nCntComputer;

	// 構造体ポインタ変数宣言// フィールド構造体の変数
	FIELD *pField;
	
	// フィールド情報のコピーの取得
	pField = GetField();

	// コンピューターの数分の表示処理
	for(nCntComputer = ZERO_INT; nCntComputer < THREE; nCntComputer++)
	{
		// コンピューターの情報入って使われている時
		if(g_computer[nCntComputer].bUseCOM == true)
		{
			// 色分け
			//if(nCntComputer == 0)
			//{
			//	COLOR(BLUE);
			//}
			//else if(nCntComputer == 1)
			//{
			//	COLOR(H_GREEN);
			//}
			//else if(nCntComputer == 2)
			//{
			//	COLOR(PINK);
			//}
			//else if(nCntComputer == 3)
			//{
			//	COLOR(CYAN);
			//}
			//else if(nCntComputer == 4)
			//{
			//	COLOR(H_BLACK);
			//}//if.fin

			COLOR(H_BLACK);

			// プレーヤーと違うコースにいたら描画しない＋カウンタが２０以上の場合も
			if( (g_computer[nCntComputer].nCnt == pField -> nCnt) && (g_computer[nCntComputer].nCnt <= 19) )
			{
				// 前回位置の消去
				LOCATE(g_computer[nCntComputer].fPosXOld, g_computer[nCntComputer].fPosYOld -1);
				printf("　");
				LOCATE(g_computer[nCntComputer].fPosXOld, g_computer[nCntComputer].fPosYOld);
				printf("　");

				// 今回位置の表示
				LOCATE(g_computer[nCntComputer].fPosX, g_computer[nCntComputer].fPosY -1);
				printf("■");
				LOCATE(g_computer[nCntComputer].fPosX, g_computer[nCntComputer].fPosY);
				printf(">>");
			}//if.fin

		}//if.fin

	}//for.fin

	// プログラムエンド
}

/*******************************************************************************
* 関数名:	void UninitComputer( void ):（終了）関数
* 引数:		void
* 戻り値:	なし
* 説明:		コンピューターの終了処理
*******************************************************************************/
void UninitComputer( void )
{
	// プログラムスタート

	

	// プログラムエンド
}

/*******************************************************************************
* 関数名:	void SetCom( float fPosX, float fPosY, int nKind):（設定）関数
* 引数:		float fPosX, float fPosY, int nKind
* 戻り値:	なし
* 説明:		コンピューターの設定処理
*******************************************************************************/
void SetCom( float fPosX, float fPosY, int nKind)
{
	// プログラムスタート

	// 変数宣言
	int nCntComputer;

	// コンピューターの数分の表示処理
	for(nCntComputer = ZERO_INT; nCntComputer < THREE; nCntComputer++)
	{
		// 表示させたいフィールドの設定
		if(g_computer[nCntComputer].bUseCOM == false)
		{
			g_computer[nCntComputer].fPosX    = fPosX;	// コンピューターのＸ座標の設定
			g_computer[nCntComputer].fPosY    = fPosY;	// コンピューターのＹ座標の設定
			g_computer[nCntComputer].nKind    = nKind;	// フィールドの移動速度
			g_computer[nCntComputer].bUseCOM  = true;	// コンピューターを使いますよアピール

			break;
		}//if.fin
		
	}//for.fin

	// プログラムエンド
}

/*******************************************************************************
* 関数名:	FCOMPUTER *GetComputer( void ):（コンピューターの情報の公開）関数
* 引数:		void
* 戻り値:	return &g_computer[ZERO_INT];
* 説明:		コンピューターの情報の公開
*******************************************************************************/
COMPUTER *GetComputer( void )
{
	// プログラムスタート

	// コンピューターの情報の値を返す
	return &g_computer[ZERO_INT];
	
	// プログラムエンド
}


