/*******************************************************************************
* タイトル:		プレイヤープログラム
* プログラム名:		player.cpp
* 作成者:		CP11SATA  15  Kim Nakamura
* 作成日:		2016/02/20
********************************************************************************
* 更新履歴:		- 2016/02/20　Kim Nakamura
*			- V1.00　Initial Version
*				・フィールドの情報から当たり判定の取得
*		2/29	・坂道の当たり判定の追加
*		3/01	・床の加速判定の追加
*******************************************************************************/
/*******************************************************************************
* scanf のwarning防止 
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

/*******************************************************************************
* インクルードファイル
*  必要な情報
*	表示のための基本要素
*	プレイヤーの情報
*	コンピューター自身の情報
*	フィールドの情報
*	イテムの情報

*******************************************************************************/
#include "main.h"
#include "player.h"
#include "computer.h"
#include "field.h"

/*******************************************************************************
* マクロ定義
*******************************************************************************/


/*******************************************************************************
* 構造体定義
*******************************************************************************/


/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
#define GRAVITY         (0.1f)		// プレイヤーの受ける重力
#define ZERO_GRAVITY    (0.0f)		// ゼログラヴィティ
#define GRAND           (24.0f)		// 地面の位置
#define POSITION        (10)		// 初期位置
#define JUMP            (0.8f)		// ジャンプ力
#define MOVE_HOR        (0.05f)		// 横移動の移動量
#define SLOPEWAY        (0.5f)		// 坂登り
#define ACCELERATOR_A   (1.0f)		// 加速アクセル：小
#define ACCELERATOR_B   (1.5f)		// 加速アクセル：中
#define ACCELERATOR_C   (2.0f)		// 加速アクセル：大
#define FLY_A           (0.3f)		// 加速ジャンプに伴う上昇値：小
#define FLY_B           (0.3f)		// 加速ジャンプに伴う上昇値：中
#define FLY_C           (0.3f)		// 加速ジャンプに伴う上昇値：大
#define INTERVAL        (25)		// ジャンプしてからの間隔

#define POINT_STAR      (150)
#define POINT_G_STAR    (300)
#define POINT_GOOD      (50)
#define POINT_VERYGOOD  (100)
#define POINT_EXCELLENT (200)
#define POINT_1         (1000)
#define POINT_2         (800)
#define POINT_3         (500)
#define POINT_4         (300)
/*******************************************************************************
* グローバル変数
*******************************************************************************/
// ヘッダーファイルからプレイヤー構造体のグローバル宣言
PLAYER g_player;

/*******************************************************************************
* 関数名:	void InitPlayer( void ):（初期化）関数
* 引数:		void
* 戻り値:	なし
* 説明:		プレイヤーの初期設定
*******************************************************************************/
void InitPlayer( void )
{
	// プログラムスタート

	// 変数宣言 // 初期化設定
	g_player.nPointGeter = ZERO_INT;	// プレイヤーのポイントお初期化
	g_player.fPosY   = GRAND;			// プレイヤーのＹ軸の初期位置の設定
	g_player.fPosX   = POSITION;		// プレイヤーのＸ軸の初期位置の設定
	g_player.fCountTimer = ZERO_INT;	// タイマーの初期化
	g_player.bJump       = false;		// ジャンプしていない状態
	g_player.bPushButton = false;		// ボタンが押されていない状態

	// プレイヤーの初期表示
	COLOR(H_RED);
	LOCATE(g_player.fPosX, (int) g_player.fPosY -1);
	printf("●");
	LOCATE(g_player.fPosX, (int) g_player.fPosY);
	printf(">>");

	// プログラムエンド
}

/*******************************************************************************
* 関数名:	void UpdatePlayer( void ):（更新）関数
* 引数:		void
* 戻り値:	なし
* 説明:		プレイヤーの更新処理
* 処理内容	常に右側移動、減速はするが停止はしない
* 			フィールド情報より当たり判定をする、壁判定は要らない
*			必要な判定は、ジャンプ後キーを離すまで次のジャンプはできない
*			
*******************************************************************************/
void UpdatePlayer( void )
{
	// プログラムスタート

	// 構造体ポインタ変数宣言// フィールド構造体の変数
	FIELD *pField;
	COMPUTER *pComputer;

	// フィールド情報のコピーの取得
	pField = GetField();
	pComputer = GetComputer();

	// 2次元配列で使用する変数の宣言
	int nVertical;
	int nHorizontal;
	int nLocateX = ONE_INT;
	int nLocateY = ONE_INT;

	// 前のポジションの取得
	g_player.fPosXOld = g_player.fPosX;
	g_player.fPosYOld = g_player.fPosY;

	// 常に右移動（遅め）
	g_player.fMoveX += MOVE_HOR;

	// 移動量をポジションに代入
	g_player.fPosX += g_player.fMoveX;
	
	// 設定最低速度で進行（プレイヤーの移動量を設定速度まで落とす処理）
	g_player.fMoveX += (MOVE_HOR - g_player.fMoveX) * SLOW;

	// 1画面内ループ
	if(g_player.fPosX >= WALL_MAX )
	{
		// エンターキー押されたら通る
		if(pField -> bPlay == true)
		{
			// インクリメント
			pField -> nCnt++;
		}//if.fin

		g_player.fPosX = WALL_XMIN;
	}//if.fin

	// 評価メッセージの消し
	if(g_player.fMoveX <= 0.34f)
	{
		LOCATE(10,15); printf("         ");
	}//if.fin

	// ボタンが押されていない時にプレイヤータイマーが０の場合、ジャンプ処理
	if( (g_player.bJump == false) && INP(PK_SP) && (g_player.fCountTimer == ZERO_INT) )
	{
		g_player.fMoveY = JUMP;				// Ｙの移動量に値の代入
		g_player.bJump  = true;				// ジャンプしてます！
		g_player.bPushButton = true;		// ボタンを押しました！

		// 2次元配列フィールドの当たり判定、プレイヤー位置との当たり判定
		for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// 縦軸のループ
		{
			for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// 横軸のループ
			{
				// プレイヤーの位置座標とフィールドの位置を比較後、座標位置にある要素番号により要素の確認
				if( ((int)g_player.fPosY == nVertical) && ( (int)(g_player.fPosX / 2 ) == nHorizontal) )
				{
					// 要素数が加速床の場合の床判定
					if(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == 0)
					{
						// 個の要素番号４：GOOD床の上でボタンフラグが立ったとき
						if((g_player.bJump == true) && (pField -> nPosition[nVertical][nHorizontal] == GOOD))
						{
							COLOR(RED);
							LOCATE(10,15); printf("GOOD");

							// レース開始時から有効
							if((pField -> bStart == true) || (pField ->bPlay == true))
							{
								// ポイントの追加
								g_player.nPointGeter += POINT_GOOD;
							}//if.fin

							// 微妙な加速をして移動量をポジションに代入
							g_player.fMoveX += ACCELERATOR_A;
							g_player.fPosX  += g_player.fMoveX;
							g_player.fMoveY = FLY_A;
						}//if.fin

						// 個の要素番号５：VERYGOOD床の上でボタンフラグが立っている時
						if((g_player.bJump == true) && (pField -> nPosition[nVertical][nHorizontal] == VERYGOOD))
						{
							COLOR(H_RED);
							LOCATE(10,15); printf("VERYGOOD");

							// レース開始時から有効
							if((pField -> bStart == true) || (pField ->bPlay == true))
							{
								// ポイントの追加
								g_player.nPointGeter += POINT_VERYGOOD;
							}//if.fin

							// 加速をして移動量をポジションに代入
							g_player.fMoveX += ACCELERATOR_B;
							g_player.fPosX  += g_player.fMoveX;
							g_player.fMoveY = FLY_B;
						}//if.fin

						// 個の要素番号６：EXCELLENT床の上でボタンフラグが立っている時
						if((g_player.bJump == true) && (pField -> nPosition[nVertical][nHorizontal] == EXCELLENT))
						{
							COLOR(YELLOW);
							LOCATE(10,15); printf("EXCELLENT");

							// レース開始時から有効
							if((pField -> bStart == true) || (pField ->bPlay == true))
							{
								// ポイントの追加
								g_player.nPointGeter += POINT_EXCELLENT;
							}//if.fin

							// 大きく加速をして移動量をポジションに代入
							g_player.fMoveX += ACCELERATOR_C;
							g_player.fPosX  += g_player.fMoveX;
							g_player.fMoveY = FLY_C;
						}//if.fin

						// 個の要素番号７：GOOD坂の上でボタンフラグが立ったとき
						if((g_player.bJump == true) && (pField -> nPosition[nVertical][nHorizontal -1] == S_GOOD))
						{
							COLOR(RED);
							LOCATE(10,15); printf("GOOD");

							// レース開始時から有効
							if((pField -> bStart == true) || (pField ->bPlay == true))
							{
								// ポイントの追加
								g_player.nPointGeter += POINT_GOOD;
							}//if.fin

							// 微妙な加速をして移動量をポジションに代入
							g_player.fMoveX += ACCELERATOR_A;
							g_player.fPosX  += g_player.fMoveX;
							g_player.fMoveY = FLY_A;
						}//if.fin

						// 個の要素番号８：VERYGOOD坂の上でボタンフラグが立っている時
						if((g_player.bJump == true) && (pField -> nPosition[nVertical][nHorizontal -1] == S_VERYGOOD))
						{
							COLOR(H_RED);
							LOCATE(10,15); printf("VERYGOOD");

							// レース開始時から有効
							if((pField -> bStart == true) || (pField ->bPlay == true))
							{
								// ポイントの追加
								g_player.nPointGeter += POINT_VERYGOOD;
							}//if.fin

							// 加速をして移動量をポジションに代入
							g_player.fMoveX += ACCELERATOR_B;
							g_player.fPosX  += g_player.fMoveX;
							g_player.fMoveY = FLY_B;
						}//if.fin

						// 個の要素番号９：EXCELLENT坂の上でボタンフラグが立っている時
						if((g_player.bJump == true) && (pField -> nPosition[nVertical][nHorizontal -1] == S_EXCELLENT))
						{
							COLOR(YELLOW);
							LOCATE(10,15); printf("EXCELLENT");

							// レース開始時から有効
							if((pField -> bStart == true) || (pField ->bPlay == true))
							{
								// ポイントの追加
								g_player.nPointGeter += POINT_EXCELLENT;
							}//if.fin

							// 大きく加速をして移動量をポジションに代入
							g_player.fMoveX += ACCELERATOR_C;
							g_player.fPosX  += g_player.fMoveX;
							g_player.fMoveY = FLY_C;
						}//if.fin

					}//if.fin

				}//if.fin

			}//forX.fin

		}//forY.fin
	}
	else if(g_player.bPushButton == true)	// ボタン判定がtrueである間
	{
		g_player.fCountTimer++;				// フレーム数分カウント
	}//if.fin

	// プレイヤーの移動量をプレイヤーのポジションに代入
	g_player.fPosY -= g_player.fMoveY;

	// プレイヤーの受ける重力
	g_player.fMoveY -= GRAVITY;

	// 2次元配列フィールドの当たり判定、プレイヤー位置との当たり判定
	for(nVertical = ZERO_INT; nVertical < MAX_VERTICAL; nVertical++)				// 縦軸のループ
	{
		for(nHorizontal = ZERO_INT; nHorizontal < MAX_HORAIZONTAL; nHorizontal++)	// 横軸のループ
		{
			// プレイヤーの位置座標とフィールドの位置を比較後、座標位置にある要素番号により要素の確認
			if( ((int)g_player.fPosY == nVertical) && ((int)(g_player.fPosX / 2 ) == nHorizontal) )
			{
				// 要素数が１の場合：地面、下にめり込まないようにする
				if(pField -> nPosition[nVertical][nHorizontal] == BLOCK)
				{
					g_player.fMoveY = ZERO_GRAVITY;				// 重力を０にする
					g_player.bJump  = false;					// ジャンプフラグを下す

					// カウンタがINTERVALに達した時にボタンフラグを下す
					if( (g_player.bPushButton == true) &&(g_player.fCountTimer > INTERVAL) )
					{
						g_player.bPushButton = false;			// ボタンフラグを下す
						g_player.fCountTimer = ZERO_INT;		// ０に初期化する
					}//if.fin
				}//if.fin

				// 要素数が２、７、８、９の場合、坂での自動上昇に加え坂の横判定
				if( (pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == SLOPE)      || 
					(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == S_GOOD)     || 
					(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == S_VERYGOOD) || 
					(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == S_EXCELLENT) )
				{
					g_player.fPosX += SLOPEWAY;					// Ｘポジを繰り上げる
					g_player.fPosY -= SLOPEWAY;					// Ｙポジを繰り上げる
					g_player.fMoveY = ZERO_GRAVITY;				// 重力を０にする
					g_player.bJump  = false;					// ジャンプフラグを下す

					// カウンタがINTERVALに達した時にボタンフラグを下す
					if( (g_player.bPushButton == true) && (g_player.fCountTimer > INTERVAL) )
					{
						g_player.bPushButton = false;			// ボタンフラグを下す
						g_player.fCountTimer = ZERO_INT;		// ０に初期化する
					}//if.fin
				}//if.fin

				// 要素数が３、４、５、６の場合の床判定
				if( (pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == COURSE)   || 
					(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == GOOD)     || 
					(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == VERYGOOD) || 
					(pField -> nPosition[nVertical - ONE_INT][nHorizontal + ONE_INT] == EXCELLENT) )
				{
					g_player.fPosY -= SLOPEWAY;					// Ｙポジを繰り上げる
					g_player.fMoveY = ZERO_GRAVITY;				// 重力を０にする
					g_player.bJump  = false;					// ジャンプフラグを下す

					// カウンタがINTERVALに達した時にボタンフラグを下す
					if( (g_player.bPushButton == true) && (g_player.fCountTimer > INTERVAL) )
					{
						g_player.bPushButton = false;			// ボタンフラグを下す
						g_player.fCountTimer = ZERO_INT;		// ０に初期化する
					}//if.fin
				}//if.fin

			}//if.fin

		}//forX.fin

	}//forY.fin

	// めり込み前の前回位置の座標の代入
	if(g_player.fPosY > GRAND)
	{
		g_player.fMoveY = ZERO_GRAVITY;				// 重力を０にする
		g_player.fPosY = GRAND;						// 地面の位置の値の代入
	}//if.fin

	// プログラムエンド
}

/*******************************************************************************
* 関数名:	void DrawPlayer( void ):（描画）関数
* 引数:		void
* 戻り値:	なし
* 説明:		プレイヤーの描画処理
*******************************************************************************/
void DrawPlayer( void )
{
	// プログラムスタート

	// 構造体ポインタ変数宣言
	FIELD *pField;
	COMPUTER *pComputer;
	
	// 情報のコピーの取得
	pField = GetField();
	pComputer = GetComputer();

	// カウントが２０を超えたら描画終了
	if(pField -> nCnt < 20)
	{
		// 取得ポイントの描画// 自分の位置と相手の位置の見取り図
		if((pField -> bStart == true) || (pField ->bPlay == true))
		{
			COLOR(GREEN);
			LOCATE(1,1); printf("￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣");
			LOCATE(1,3); printf("＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿");

			// 自分
			COLOR(WHITE);
			LOCATE(pField -> nCnt *45, 2); printf("●");

			// 相手
			COLOR(H_BLACK);
			LOCATE(pComputer -> nCnt *4, 2); printf("□");

			COLOR(PINK);
			LOCATE(3,5); printf("MY POINT:%5d ", g_player.nPointGeter);

			LOCATE(3,7); printf("赤と黄色の上でタイミング良くジャンプ！");
		}//if.fin

		// 着色：しろ
		COLOR(H_RED);

		// 前回位置のクリア
		LOCATE(g_player.fPosXOld, (int) g_player.fPosYOld -1);
		printf("　");
		LOCATE(g_player.fPosXOld, (int) g_player.fPosYOld);
		printf("　");

		// 今回位置の描画
		LOCATE(g_player.fPosX, (int) g_player.fPosY -1);
		printf("●");
		LOCATE(g_player.fPosX, (int) g_player.fPosY);
		printf(">>");
	}//if.fin

	// プログラムエンド
}

/*******************************************************************************
* 関数名:	void UninitPlayer( void ):（終了）関数
* 引数:		void
* 戻り値:	なし
* 説明:		プレイヤーの終了処理
*******************************************************************************/
void UninitPlayer( void )
{
	// プログラムスタート

	

	// プログラムエンド
}

/*******************************************************************************
* 関数名:	PLAYER *GetPlayer( void ):（プレイヤー情報の公開）関数
* 引数:		void
* 戻り値:	return &g_player;
* 説明:		プレイヤー情報の公開
*******************************************************************************/
PLAYER *GetPlayer( void )
{
	// プログラムスタート

	// プレイヤー情報の値を返す
	return &g_player;
	
	// プログラムエンド
}
