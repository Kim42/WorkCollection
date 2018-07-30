/*******************************************************************************
* タイトル:		ネームバトラープログラム
* プログラム名:		NAME_BATTLER.cpp
* 作成者:		CP11SATA  15  Kim Nakamura
* 作成日:		2015/12/23
********************************************************************************
* 更新履歴:		- 2016/01/14　Kim Nakamura　Kim Nakamura
*			- V1.03　Initial Version
*******************************************************************************/
/*******************************************************************************
* scanf のwarning防止 
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include "CScreen.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define ZERO                    (0)		// ０
#define ONE                     (1)		// １
#define NUM_TITLE_VERTICAL      (24)	// タイトルの縦軸
#define NUM_TITLE_HORIZONTAL    (40)	// タイトルの横軸
#define NUM_RINK_VERTICAL       (14)	// ソウルリンクの縦軸
#define NUM_RINK_HORIZONTAL     (40)	// ソウルリンクの横軸
#define NUM_SURAIM_VERTICAL     (14)	// スライムの縦軸
#define NUM_SURAIM_HORIZONTAL   (15)	// スライムの横軸
#define NUM_LOCATION_VERTICAL   (7)		// スライムの場所指定縦軸
#define NUM_LOCATION_HORIZONTAL (6)		// スライムの場所指定横軸
#define NUM_WARP_VERTICAL       (24)	// ワープの縦軸
#define NUM_WARP_HORIZONTAL     (80)	// ワープの横軸
#define NUM_WARP_HORIZONTAL2    (80)	// ワープの横軸(特殊)
#define NUM_STATUS_VERTICAL     (24)	// ステイタス表の縦軸
#define NUM_STATUS_HORIZONTAL   (20)	// ステイタス表の横軸
#define NUM_DARK_VERTICAL       (3)		// スライムダークの縦軸
#define NUM_DARK_HORIZONTAL     (26)	// スライムダークの横軸

// ドラキーの初期位置
#define VERTICAL_DORAKI       (3)		// 縦軸
#define HORIZONTAL_DORAKI     (26)		// 横軸

// ダメージエフェクト
#define EFFECT_VERTICAL       (14)		// 縦軸
#define EFFECT_HORIZONTAL     (11)		// 横軸

/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
// スライムアニメーション //
void Suraim( void );									// スライム関数
void Suraim2( void );									// スライム2関数
void MetalSuraim( void );								// メタルスライム関数
void MetalSuraim2( void );								// メタルスライム2関数
void ButiSuraim( void );								// ぶちスライム関数
void ButiSuraim2( void );								// ぶちスライム2関数
void SuraimDark( void );								// スライムダーク関数
void SuraimDark2( void );								// スライムダーク2関数

void wait( void );										// キー入力待ち関数

/*******************************************************************************
 タイトル関数
*******************************************************************************/
int title( void )
{
	// 変数宣言
	int nCntX = 45;
	int nPosition = 11;
	int nSetpositionX = 44;										// X座標
	int nSetpositionY = 9;										// Y座標
	int nSelect = ZERO;
	int nKey = ZERO;

	////タイトル////
	system("cls");												// 画面のクリア

	CLS(H_RED , BLACK);											// 文字を赤、背景色を白に変更

	//// メインタイトル兼モード選択画面 + BGMスタート ////
	char aTitle[NUM_TITLE_VERTICAL][NUM_TITLE_HORIZONTAL] = 
	{
		{3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,4,4,4,4,0,0,4,0,4,4,4,4,4,4,4,0,0,4,4,4,4,0,0,5,5,5,0,0,4,4,4,4,0,0,0,0,0,1},
		{1,0,0,4,0,4,0,4,0,4,0,4,0,0,4,0,4,0,0,4,0,0,0,0,5,0,5,0,5,0,4,0,0,0,0,0,0,0,0,1},
		{1,0,0,4,4,4,0,4,0,4,0,4,0,0,4,0,4,0,0,4,4,4,0,5,5,5,0,5,5,5,5,5,5,0,0,0,0,0,0,1},
		{1,0,0,4,0,0,4,4,4,4,4,4,0,0,4,0,4,0,0,4,0,0,0,0,5,0,5,0,5,0,4,0,0,0,0,0,0,0,0,1},
		{1,0,4,4,4,4,4,0,0,0,4,4,0,0,4,0,4,4,4,4,4,4,4,0,0,5,5,5,0,0,4,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,6,0,0,6,0,0,6,0,0,6,0,0,0,0,0,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,6,6,0,6,0,6,0,6,0,6,6,0,0,0,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,6,6,0,6,0,6,0,6,0,6,6,0,0,0,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,6,0,6,6,6,6,6,6,6,6,0,6,0,6,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,6,0,0,6,6,0,0,0,6,6,0,0,6,0,0,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,4,0,0,0,0,0,0,0,4,0,0,4,0,4,0,4,4,4,0,4,4,4,4,0,4,0,4,4,4,4,4,4,4,4,0,1},
		{1,0,0,0,5,0,0,0,5,0,0,0,5,0,0,5,5,0,5,0,5,0,0,5,0,0,0,5,0,5,0,5,0,5,0,0,0,0,0,1},
		{1,0,0,0,0,5,0,5,0,5,0,5,0,5,5,0,5,0,5,0,5,0,0,5,5,5,0,5,0,5,0,5,0,5,5,5,5,0,0,1},
		{1,0,0,0,0,5,0,5,0,5,0,5,5,0,0,5,5,5,5,5,5,0,0,5,0,0,5,5,5,5,5,5,0,5,0,0,0,0,0,1},
		{1,0,0,0,0,0,4,0,0,0,4,0,4,0,0,4,0,0,0,4,4,0,0,4,0,0,4,0,0,0,4,4,0,4,4,4,4,4,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}

	};

	//タイトル表示の処理
	for(int nVertical = 0; nVertical < NUM_TITLE_VERTICAL; nVertical++)				// 縦軸ループ処理
	{
		//Sleep(200);																//インターバル 0.2秒

		for(int nHorizontal = 0; nHorizontal < NUM_TITLE_HORIZONTAL; nHorizontal++)	// 横軸ループ処理
		{
			if(aTitle[nVertical][nHorizontal] == 1)				// 条件が『１』の時
			{
				printf("｜");
			}
			else if(aTitle[nVertical][nHorizontal] == 2)		// 条件が『２』の時
			{
				printf("―");
			}
			else if(aTitle[nVertical][nHorizontal] == 3)		// 条件が『３』の時
			{
				printf("★");
			}
			else if(aTitle[nVertical][nHorizontal] == 4)		// 条件が『４』の時
			{
				COLOR(WHITE);
				printf("●");
				COLOR(H_RED);
			}
			else if(aTitle[nVertical][nHorizontal] == 5)		// 条件が『５』の時
			{
				COLOR(H_RED);
				printf("◆");
			}
			else if(aTitle[nVertical][nHorizontal] == 6)		// 条件が『６』の時
			{
				COLOR(H_RED);
				printf("■");
				
			}
			else if(aTitle[nVertical][nHorizontal] == 0)		// 条件が『０』の時
			{
				printf("　");
			}//if.fin
		}
		
	}//for.fin

	COLOR(YELLOW);												//文字色を黄色へ

	Sleep(300);
	LOCATE(nSetpositionX, nSetpositionY);
	printf(" ～ 　　　　　　　　　 ～ ");
	Sleep(300);
	LOCATE(nSetpositionX +5, nSetpositionY);
	printf("名");
	Sleep(300);
	LOCATE(nSetpositionX +7, nSetpositionY);
	printf("こ");
	Sleep(300);
	LOCATE(nSetpositionX +9, nSetpositionY);
	printf("そ");
	Sleep(300);
	LOCATE(nSetpositionX +11, nSetpositionY);
	printf("運");
	Sleep(300);
	LOCATE(nSetpositionX +13, nSetpositionY);
	printf("命");
	Sleep(300);
	LOCATE(nSetpositionX +15, nSetpositionY);
	printf("の");
	Sleep(300);
	LOCATE(nSetpositionX +17, nSetpositionY);
	printf("戦");
	Sleep(300);
	LOCATE(nSetpositionX +19, nSetpositionY);
	printf("い");

	////選択コマンド////
	Sleep(300);
	LOCATE(48, 11);
	COLOR(WHITE,BLACK);
	printf(" ノーマルモード");
	LOCATE(45, 11);
	COLOR(WHITE, H_RED);
	printf(" →");

	Sleep(200);
	LOCATE(49, 12);
	COLOR(WHITE,BLACK);
	printf(" 操作マニュアル");

	Sleep(100);
	LOCATE(50, 13);
	COLOR(WHITE,BLACK);
	printf(" EXIT");

	// 簡易操作説明
	LOCATE(10, 22);
	printf("◇ 操作は〔 W S A D 〕を方向キーとして使用します。");
	LOCATE(10, 23);
	printf("◇ ENTERキーで決定をするといった操作方法になります。");
	LOCATE(10, 24);
	printf("◇ 操作は〔 W は↑〕〔 S は↓ 〕〔 A は← 〕〔 D は→ 〕となります。");
	
	// モードの選択
	while(1)
	{
		KEYCLEAR();							// キーボードを初期化する
		
		WAIT(200);							// インターバル 0.2秒
		INKEY(nSelect);						// 何かキーが押されていたら変数に値を入力する

		if(nSelect == 0x77)					// W アスキーコードの入力後
		{
			if(nPosition == 11)				// カーソルが一番上にある時に W を押した場合
			{
				BACKCOLOR(BLACK);
				LOCATE(45, 11);
				printf(" 　");
				BACKCOLOR(BLACK);
				LOCATE(46, 12);
				printf(" 　");
				COLOR(WHITE, LIME);
				LOCATE(47, 13);
				printf(" →");

				nPosition = 13;
			}
			else if(nPosition == 12)		// カーソルが真ん中にある時に W を押した場合
			{
				COLOR(WHITE, H_RED);
				LOCATE(45, 11);
				printf(" →");
				BACKCOLOR(BLACK);
				LOCATE(46, 12);
				printf(" 　");
				BACKCOLOR(BLACK);
				LOCATE(47, 13);
				printf(" 　");

				nPosition = 11;
			}
			else if(nPosition == 13)		// カーソルが一番下にある時に W を押した場合
			{
				BACKCOLOR(BLACK);
				LOCATE(45, 11);
				printf(" 　");
				COLOR(WHITE, H_CYAN);
				LOCATE(46, 12);
				printf(" →");
				BACKCOLOR(BLACK);
				LOCATE(47, 13);
				printf(" 　");

				nPosition = 12;
			}//if.fin
		}//if.fin
		if(nSelect == 0x73)					// S アスキーコードの入力後
		{
			if(nPosition == 11)				// カーソルが一番上にある時に S を押した場合
			{
				BACKCOLOR(BLACK);
				LOCATE(45, 11);
				printf(" 　");
				COLOR(WHITE, H_CYAN);
				LOCATE(46, 12);
				printf(" →");
				BACKCOLOR(BLACK);
				LOCATE(47, 13);
				printf(" 　");

				nPosition = 12;
			}
			else if(nPosition == 12)		// カーソルが真ん中にある時に S を押した場合
			{
				BACKCOLOR(BLACK);
				LOCATE(45, 11);
				printf(" 　");
				BACKCOLOR(BLACK);
				LOCATE(46, 12);
				printf(" 　");
				COLOR(WHITE, LIME);
				LOCATE(47, 13);
				printf(" →");

				nPosition = 13;
			}
			else if(nPosition == 13)		// カーソルが一番下にある時に S を押した場合
			{
				COLOR(WHITE, H_RED);
				LOCATE(45, 11);
				printf(" →");
				BACKCOLOR(BLACK);
				LOCATE(46, 12);
				printf(" 　");
				BACKCOLOR(BLACK);
				LOCATE(47, 13);
				printf(" 　");

				nPosition = 11;
			}//if.fin
		}//if.fin

		if(nSelect == 0xd) break;

	}//while.fin

	// 入力値の受け取り
	if(nPosition == 11)
	{
		nSelect = 0x61;
	}
	else if(nPosition == 12)
	{
		nSelect = 0x73;
	}
	else if(nPosition == 13)
	{
		nSelect = 0x64;
	}//if.fin

	// 値を返す
	return nSelect;

}

/*******************************************************************************
 ソウルリンクタイトル関数
*******************************************************************************/
void Soulrink(void)
{
	//変数宣言、場所指定
	int nVertical = 4;
	int nHorizontal = 1;

	LOCATE(nHorizontal, nVertical);										// 場所指定

	//ソウルリンクタイトルの表示
	char aSoultitle[NUM_RINK_VERTICAL][NUM_RINK_HORIZONTAL] = 
	{
		{2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,3,3,3,0,0,4,4,0,0,4,0,0,4,0,4,0,0,3,3,3,3,3,0,4,4,4,4,4,0,0,4,0,0,0,4,0,1},
		{1,0,3,0,0,0,3,4,0,0,4,0,4,0,0,4,0,4,0,0,3,0,0,0,0,3,0,4,4,0,4,0,0,4,0,0,4,0,0,2},
		{2,0,3,0,0,0,0,4,0,0,4,0,4,0,0,4,0,4,0,0,3,0,0,0,0,3,0,4,4,0,4,4,0,4,0,4,4,0,0,1},
		{1,0,0,3,0,0,0,4,0,0,4,0,4,0,0,4,0,4,0,0,3,3,3,3,3,0,0,4,4,0,4,4,0,4,0,4,0,0,0,2},
		{2,0,0,0,3,0,0,4,0,0,4,0,4,0,0,4,0,4,0,0,3,3,0,0,0,0,0,4,4,0,4,0,4,4,4,4,0,0,0,1},
		{1,0,0,0,0,3,0,4,0,0,4,0,4,0,0,4,0,4,0,0,3,0,3,0,0,0,0,4,4,0,4,0,0,4,4,0,0,0,0,2},
		{2,0,0,0,0,0,3,4,0,0,4,0,4,0,0,4,0,4,0,0,3,0,0,3,0,0,0,4,4,0,4,0,0,4,0,4,0,0,0,1},
		{1,0,0,0,0,0,0,3,0,0,4,0,4,0,0,4,0,4,0,0,3,0,0,0,3,0,0,4,4,0,4,0,0,4,0,4,4,0,0,2},
		{2,0,3,0,0,0,0,3,0,0,4,0,4,0,0,4,0,4,0,0,3,0,0,0,0,3,0,4,4,0,4,0,0,4,0,0,4,4,0,1},
		{1,0,0,3,3,3,3,0,4,4,0,0,0,4,4,0,0,4,4,4,3,0,0,0,0,0,3,4,4,4,4,0,0,4,0,0,0,4,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2}
	};

	// 着色
	for(int nCnt_y = 0; nCnt_y < NUM_RINK_VERTICAL; nCnt_y++)			// 縦軸
	{
		LOCATE(nHorizontal, nVertical++);								// 場所指定

		for(int nCnt_x = 0; nCnt_x < NUM_RINK_HORIZONTAL; nCnt_x++)		// 横軸
		{
			if(aSoultitle[nCnt_y][nCnt_x] == 1)							// 座標が１の場合
			{
				BACKCOLOR(YELLOW);										// 黄色
				printf("　");
			}
			else if(aSoultitle[nCnt_y][nCnt_x] == 2)					// 座標が２の場合
			{
				BACKCOLOR(WHITE);										// 白
				printf("　");
			}
			else if(aSoultitle[nCnt_y][nCnt_x] == 3)					// 座標が３の場合
			{
				BACKCOLOR(H_RED);										// ライム
				printf("　");
			}
			else if(aSoultitle[nCnt_y][nCnt_x] == 4)					// 座標が４の場合
			{
				COLOR(WHITE);											// 白
				printf("□");
			}
			else if(aSoultitle[nCnt_y][nCnt_x] == 0)					// 座標が０の場合
			{
				BACKCOLOR(BLACK);										// 黒
				printf("　");
			}//if.fin
		}
	}//for.fin

}

/*******************************************************************************
 ソウルリンクタイトル2関数
*******************************************************************************/
void Soulrink2(void)
{
	//変数宣言、場所指定
	int nVertical = 4;
	int nHorizontal = 1;

	LOCATE(nHorizontal, nVertical);										// 場所指定

	//ソウルリンクタイトルの表示
	char aSoultitle[NUM_RINK_VERTICAL][NUM_RINK_HORIZONTAL] = 
	{
		{2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,3,3,3,0,0,4,4,0,0,4,0,0,4,0,4,0,0,3,3,3,3,3,0,4,4,4,4,4,0,0,4,0,0,0,4,0,1},
		{1,0,3,0,0,0,3,4,0,0,4,0,4,0,0,4,0,4,0,0,3,0,0,0,0,3,0,4,4,0,4,0,0,4,0,0,4,0,0,2},
		{2,0,3,0,0,0,0,4,0,0,4,0,4,0,0,4,0,4,0,0,3,0,0,0,0,3,0,4,4,0,4,4,0,4,0,4,4,0,0,1},
		{1,0,0,3,0,0,0,4,0,0,4,0,4,0,0,4,0,4,0,0,3,3,3,3,3,0,0,4,4,0,4,4,0,4,0,4,0,0,0,2},
		{2,0,0,0,3,0,0,4,0,0,4,0,4,0,0,4,0,4,0,0,3,3,0,0,0,0,0,4,4,0,4,0,4,4,4,4,0,0,0,1},
		{1,0,0,0,0,3,0,4,0,0,4,0,4,0,0,4,0,4,0,0,3,0,3,0,0,0,0,4,4,0,4,0,0,4,4,0,0,0,0,2},
		{2,0,0,0,0,0,3,4,0,0,4,0,4,0,0,4,0,4,0,0,3,0,0,3,0,0,0,4,4,0,4,0,0,4,0,4,0,0,0,1},
		{1,0,0,0,0,0,0,3,0,0,4,0,4,0,0,4,0,4,0,0,3,0,0,0,3,0,0,4,4,0,4,0,0,4,0,4,4,0,0,2},
		{2,0,3,0,0,0,0,3,0,0,4,0,4,0,0,4,0,4,0,0,3,0,0,0,0,3,0,4,4,0,4,0,0,4,0,0,4,4,0,1},
		{1,0,0,3,3,3,3,0,4,4,0,0,0,4,4,0,0,4,4,4,3,0,0,0,0,0,3,4,4,4,4,0,0,4,0,0,0,4,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2}
	};

	// 着色
	for(int nCnt_y = 0; nCnt_y < NUM_RINK_VERTICAL; nCnt_y++)			// 縦軸
	{
		LOCATE(nHorizontal, nVertical++);								// 場所指定

		for(int nCnt_x = 0; nCnt_x < NUM_RINK_HORIZONTAL; nCnt_x++)		// 横軸
		{
			if(aSoultitle[nCnt_y][nCnt_x] == 1)							// 座標が１の場合
			{
				BACKCOLOR(WHITE);										// 白
				printf("　");
			}
			else if(aSoultitle[nCnt_y][nCnt_x] == 2)					// 座標が２の場合
			{
				BACKCOLOR(YELLOW);										// 黄色
				printf("　");
			}
			else if(aSoultitle[nCnt_y][nCnt_x] == 3)					// 座標が３の場合
			{
				BACKCOLOR(LIME);										// ライム
				printf("　");
			}
			else if(aSoultitle[nCnt_y][nCnt_x] == 4)					// 座標が４の場合
			{
				BACKCOLOR(WHITE);										// 白
				printf("　");
			}
			else if(aSoultitle[nCnt_y][nCnt_x] == 0)					// 座標が０の場合
			{
				BACKCOLOR(BLACK);										// 黒
				printf("　");
			}//if.fin
		}
	}//for.fin

}

/*******************************************************************************
 ステイタス枠関数
*******************************************************************************/
void StatusFrame( int nColor )
{
	// 変数宣言、場所指定
	int nVertical = 1;													// 縦軸用
	int nHorizontal = 41;												// 横軸用

	// ステイタスの表の表示（BEFOR → AFTER）
	char aStatus[NUM_STATUS_VERTICAL][NUM_STATUS_HORIZONTAL] = 
	{
		{1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1}
	};

	// 着色 + 場所指定
	LOCATE(nHorizontal, nVertical);
	for(int nCnt_y = 0; nCnt_y < NUM_STATUS_VERTICAL; nCnt_y++)			// 縦軸
	{
		LOCATE(nHorizontal, nVertical++);								// 縦軸のインクリメント

		for(int nCnt_x = 0; nCnt_x < NUM_STATUS_HORIZONTAL; nCnt_x++)	// 横軸
		{
			if(aStatus[nCnt_y][nCnt_x] == 1)							// 座標１の場合
			{
				COLOR(nColor, WHITE);									// 任意,白
				printf("●");
			}
			else if(aStatus[nCnt_y][nCnt_x] == 2)						// 座標２の場合
			{
				COLOR(nColor, WHITE);									// 任意,白
				printf("｜");
			}
			else if(aStatus[nCnt_y][nCnt_x] == 3)						// 座標３の場合
			{
				COLOR(nColor, WHITE);									// 任意,白
				printf("―");
			}
			else if(aStatus[nCnt_y][nCnt_x] == 0)						// 座標０の場合
			{
				BACKCOLOR(WHITE);										// 白
				printf("　");
			}//if.fin
		}
		printf("\n");
	}//for.fin
}

/*******************************************************************************
 通常時ワ－プ関数
 ******************************************************************************/
void NormalWarp( int nWarpiru )
{
	// 出来れば残してプレイしてほしいな～
	if(nWarpiru == 2)
	{
		// 変数宣言
		int nMP3Handle = ZERO;

		//前画面のクリア
		system("cls");							// 画面のクリア

		// 効果音の再生
		nMP3Handle = OPENMP3("warp.mp3");						// オープン & 初期化
		PLAYMP3(nMP3Handle);									// 繰り返し再生

		//通常ワープ
		char nNormalWarp[NUM_WARP_VERTICAL][NUM_WARP_HORIZONTAL2] = 
		{
			"　■■　■■■■■■■■■■■■■■　■■■■■■■■■■　　　■■■■■■■ ",
			"　■　■■■■■■■■■■■■■■■■　■■■■■■■■■■　　　■■■■■■ ",
			"　■■　■■■■■■■■■■■　■■■■　■■■■■■■■■■　　　■■■■■ ",
			"　■■■　■■■　■■■■■■■　■■■■　■■■■■■■■■■　　　■■■■ ",
			"　■■■■　■■■　■■■■■■■■■■■■　■■■■■■■■■■　　　■■■ ",
			"　■■■■■　■■■■■■■■■■■■■■■■　■■■■■■■■■■　　　■■ ",
			"　■■■■■■　■■■■■■■　　■■■■■■■　　　　　　　　　　　　　　■ ",
			"　■■■■■■■　■■■■■■　　　■■■　■■■　　　　　　　　　　　　　■ ",
			"　■■■■■■■■　■■■■■■　　■■■■■■■■　■■■■■■■■■■■■ ",
			"　■■■■■■■■■　■■■■■■■■■■■　■■■■　■■■■■■■■■■■ ",
			"　■■■■■■■■■■　■■　■■■■■■■■■■■■■　■■■■■■■■■■ ",
			"　■■■■■■■■■■■　■■■■■■■■■■■　■■■■　■■■■■■■■■ ",
			"　■　　　　　　　　　　　　■■■■■■■　■■■■■■■■　■■■■■■■■ ",
			"　■　　　　　　　　　　　　　■■■　■■■■■■■■　■■■　■■■■■■■ ",
			"　■■　　　■■■■■■■■■　■■■■■■■■■　■■■■■■　■■■■■■ ",
			"　■■■　　　■■■■■■■■■　■■■■　■■■■■■■■■■■　■■■■■ ",
			"　■■■■　　　■■■■■■■■■　■■■■■■■■■■■■■■■■　■■■■ ",
			"　■■■■■　　　■■■■■■■■■　■■■■■■■　■■■■　■■■　■■■ ",
			"　■■■■■■　　　■■■■■■■■■　■■■　■■■■■■■■■■■■　■■ ",
			"　■■■■■■■　　　■■■■■■■■■　■■■■■■■■■■■■■■■■　■ ",
			"　■■■■■■■■　　　■■■■■■■■■　■■　■■■■■■■■■　■■■　 ",
			"　■■■■■■■■■　　　■■■■■■■■■　■■■■■■　■■■■■■■■■ ",
			"　■■■■■■■■■■　　　■■■■■■■■■　■■■■■■■■■■■■■■■ ",
		};

		//表示ループ
		for(int nCnt_y = 0; nCnt_y < NUM_WARP_VERTICAL; nCnt_y++)			//縦のループ
		{
			Sleep(100);														// インターバル 0.1秒

			for(int nCnt_x = 0; nCnt_x < NUM_WARP_HORIZONTAL; nCnt_x++)		//横のループ
			{
				COLOR(LIME,BLACK);
				printf("%c", nNormalWarp[nCnt_y][nCnt_x]);
			}

		}//for.fin

		CLOSEMP3(nMP3Handle);									// 停止 & クローズ
	}//if.fin

	system("cls");							// 画面のクリア
}

/*******************************************************************************
 ソウルリンクの説明関数
 ******************************************************************************/
void SoulRinkDescription( int nWarpiru )
{
	//変数宣言
	int nVer;		// 縦軸
	int nHor;		// 横軸
	int nTall = 10;
	int nkey = ZERO;

	NormalWarp( nWarpiru );							// ワープ

	//BOSSのアスキーアート
	char aBrownie[14][74] = 
	{
		"                       ﾉ^｀丶､_",
		"                     ／       ＾丶、",
		"                    /              ＼_",
		"                   ﾉ                 く __              ..、",
		"                  ﾉ /⌒ ‐-‐ ⌒Ｙ  :. ＼｀.^`  ‐---‐_彡",
		"                 /  ＼_･___･__,ノ  : ._ノ ｉ               i",
		"                .ｰ-,- ､__,二..__,. -- '⌒V j      __,       |",
		"              :.:: {  ,          /   ）:.ﾉﾘ}   ...⌒'く:.:.  |.",
		"            :.:::   }_,、       {__／  ／V厶=-----ヘ. ＼‐-' : : .",
		"          .:.:.:::  (⌒) ＞;‐-- ---r_,ノ     :.::.:.＼ ＼: : : :",
		"         .:.:.:.:.(⌒＠⌒)￣              .:.:.:.:.:.:.＼ ＼ :",
		"           :.:.:::_;厶r; ........;.:::.:.:.:.:.:.:.:.:::.＼ ＼_",
		"            :.:.:.⌒¨゛..:..:..:..:..:..:..:..:..:.:.:.:..＼'´）",
		"               . . .::::: : :::::::::::::＾:.",
	};

	// アスキーアート表示
	for(nVer = 0; nVer < 14; nVer++)		// 縦のループ
	{
		LOCATE(1, nTall++);					// 場所指定

		for(nHor = 0; nHor < 74 ; nHor++)	// 横のループ
		{
			COLOR(BROWN);
			printf("%c",aBrownie[nVer][nHor]);
		}
		printf("\n");						// 改行出力
	}

	// ソウルリンクについての説明
	LOCATE(20, 6);
	printf("１：リンクすることでステータスが変化します！");

	LOCATE(20, 8);
	printf("２：選ばずに戦闘を開始することも可能です！");

	LOCATE(20, 10);
	printf("３：スライムによって使える技も違います！");

	// 要所要所の色付け
	COLOR(BLUE);
	LOCATE(24, 10);
	printf("スライム");

	COLOR(H_RED);
	LOCATE(24, 6);
	printf("リンク");

	while(1)
	{
		COLOR(WHITE,LIME);
		LOCATE(33, 13);
		printf("Please Enter");
		 WAIT(300);						// 0.3secの時間待ち 
		INKEY(nkey);					// 何かキーが押されていたら変数に値を入力する 
		if (nkey == 0xd) break;			// 何か押されたら終了する 

		COLOR(LIME,H_CYAN);
		LOCATE(33, 13);
		printf("Please Enter");
		WAIT(300);						// 0.3secの時間待ち 
		INKEY(nkey);					// 何かキーが押されていたら変数に値を入力する 
		if (nkey == 0xd) break;			// 何か押されたら終了する 
	}

	CLS(WHITE, BLACK);

	NormalWarp( nWarpiru );										// ワープ
}

/*******************************************************************************
 ドットマリオ関数
*******************************************************************************/
void Mario( void )
{
	// 変数宣言
	int nVertical = 5;
	int nHorizontal = 6;

	// ドットアスキーアート「 マリオ 」
	COLOR(YELLOW,BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("        ┏━━━━┓         ");
	LOCATE(nHorizontal, nVertical++);
	printf("      ┏┛        ┗━━┓   ");
	LOCATE(nHorizontal, nVertical++);
	printf("      ┣━━┳━┳┳┳━┛   ");
	LOCATE(nHorizontal, nVertical++);
	printf("    ┏╋┓┏┛  ┃┃┗━┓   ");
	LOCATE(nHorizontal, nVertical++);
	printf("    ┃┃┃┗┓  ┗╋┓  ┗┓ ");
	LOCATE(nHorizontal, nVertical++);
	printf("    ┃┗╋━┛  ┏┛┗━┳┛ ");
	LOCATE(nHorizontal, nVertical++);
	printf("    ┗━┫      ┗━━┳┛   ");
	LOCATE(nHorizontal, nVertical++);
	printf("      ┏┻┳┳━━┳━┛     ");
	LOCATE(nHorizontal, nVertical++);
	printf("    ┏┛  ┃┃  ┏╋━━┓   ");
	LOCATE(nHorizontal, nVertical++);
	printf("  ┏┛    ┃┗━┛┃    ┗┓ ");
	LOCATE(nHorizontal, nVertical++);
	printf("  ┣━┓┏╋┓  ┏╋┓┏━┫ ");
	LOCATE(nHorizontal, nVertical++);
	printf("  ┃  ┗┫┗┛  ┗┛┣┛  ┃ ");
	LOCATE(nHorizontal, nVertical++);
	printf("  ┃  ┏┛          ┗┓  ┃ ");
	LOCATE(nHorizontal, nVertical++);
	printf("  ┗━┫    ┏━┓    ┣━┛ ");
	LOCATE(nHorizontal, nVertical++);
	printf("      ┃    ┃  ┃    ┃     ");
	LOCATE(nHorizontal, nVertical++);
	printf("    ┏┻━┳┛  ┗┳━┻┓   ");
	LOCATE(nHorizontal, nVertical++);
	printf("  ┏┛    ┃      ┃    ┗┓ ");
	LOCATE(nHorizontal, nVertical++);
	printf("  ┗━━━┛      ┗━━━┛ ");

}

/*******************************************************************************
 全体説明関数
*******************************************************************************/
void Manual( int nWarpiru )
{
	// ゲームの進行上でのせつめい // 変数宣言	
	int nVertical = 6;
	int nHorizontal = 5;
	int nVer = 4;
	int nHor = 42;
	int nkey = ZERO;

	// ドットアスキーアート「 マリオ 」
	COLOR(YELLOW, H_RED);
	LOCATE(nHorizontal, nVertical++);
	printf("        ┏━━━━┓         ");
	LOCATE(nHorizontal, nVertical++);
	printf("      ┏┛        ┗━━┓   ");
	LOCATE(nHorizontal, nVertical++);
	printf("      ┣━━┳━┳┳┳━┛   ");
	LOCATE(nHorizontal, nVertical++);
	printf("    ┏╋┓┏┛  ┃┃┗━┓   ");
	LOCATE(nHorizontal, nVertical++);
	printf("    ┃┃┃┗┓  ┗╋┓  ┗┓ ");
	LOCATE(nHorizontal, nVertical++);
	printf("    ┃┗╋━┛  ┏┛┗━┳┛ ");
	LOCATE(nHorizontal, nVertical++);
	printf("    ┗━┫      ┗━━┳┛   ");
	LOCATE(nHorizontal, nVertical++);
	printf("      ┏┻┳┳━━┳━┛     ");
	LOCATE(nHorizontal, nVertical++);
	printf("    ┏┛  ┃┃  ┏╋━━┓   ");
	LOCATE(nHorizontal, nVertical++);
	printf("  ┏┛    ┃┗━┛┃    ┗┓ ");
	LOCATE(nHorizontal, nVertical++);
	printf("  ┣━┓┏╋┓  ┏╋┓┏━┫ ");
	LOCATE(nHorizontal, nVertical++);
	printf("  ┃  ┗┫┗┛  ┗┛┣┛  ┃ ");
	LOCATE(nHorizontal, nVertical++);
	printf("  ┃  ┏┛          ┗┓  ┃ ");
	LOCATE(nHorizontal, nVertical++);
	printf("  ┗━┫    ┏━┓    ┣━┛ ");
	LOCATE(nHorizontal, nVertical++);
	printf("      ┃    ┃  ┃    ┃     ");
	LOCATE(nHorizontal, nVertical++);
	printf("    ┏┻━┳┛  ┗┳━┻┓   ");
	LOCATE(nHorizontal, nVertical++);
	printf("  ┏┛    ┃      ┃    ┗┓ ");
	LOCATE(nHorizontal, nVertical++);
	printf("  ┗━━━┛      ┗━━━┛ ");

	int aManual[7][12] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,2,0,0,0,0,10,0,0,0},
		{0,0,0,6,0,0,0,11,12,12,12,11},
		{0,1,5,9,7,3,0,13,14,13,0,0},
		{0,0,0,8,0,0,0,11,12,12,12,11},
		{0,0,0,4,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0}
	};

	// 表示処理
	COLOR(WHITE, BLACK);

	for(int nCnt_y = ZERO; nCnt_y < 7; nCnt_y++)
	{
		LOCATE(nHor, nVer++);

		for(int nCnt_x = ZERO; nCnt_x < 12; nCnt_x++)
		{
			if(aManual[nCnt_y][nCnt_x] == 1)
			{printf("Ａ");}
			else if(aManual[nCnt_y][nCnt_x] == 2)
			{printf("Ｗ");}
			else if(aManual[nCnt_y][nCnt_x] == 3)
			{printf("Ｄ");}
			else if(aManual[nCnt_y][nCnt_x] == 4)
			{printf("Ｓ");}
			else if(aManual[nCnt_y][nCnt_x] == 5)
			{printf("←");}
			else if(aManual[nCnt_y][nCnt_x] == 6)
			{printf("↑");}
			else if(aManual[nCnt_y][nCnt_x] == 7)
			{printf("→");}
			else if(aManual[nCnt_y][nCnt_x] == 8)
			{printf("↓");}
			else if(aManual[nCnt_y][nCnt_x] == 9)
			{printf("◇");}
			else if(aManual[nCnt_y][nCnt_x] == 10)
			{printf("決定！");}
			else if(aManual[nCnt_y][nCnt_x] == 11)
			{printf("＋");}
			else if(aManual[nCnt_y][nCnt_x] == 12)
			{printf("－");}
			else if(aManual[nCnt_y][nCnt_x] == 13)
			{printf("｜");}
			else if(aManual[nCnt_y][nCnt_x] == 14)
			{printf("ENTER ");}
			else if(aManual[nCnt_y][nCnt_x] == 0)
			{printf("　");}
		}

	}//for.fin

	LOCATE(48,3);
	COLOR(WHITE);
	printf("プレーマニュアル！");

	LOCATE(48,12);
	printf("スライムリンク時！");
	LOCATE(42,14);
	printf("Ｏ[オー]　　：使って始める");
	LOCATE(42,15);
	printf("Ｘ[エックス]：使わずに始める");

	while(1)
	{
		COLOR(WHITE,LIME);
		LOCATE(50,18);
		printf("Please Enter");
		 WAIT(300);						// 0.3secの時間待ち 
		INKEY(nkey);					// 何かキーが押されていたら変数に値を入力する 
		if (nkey == 0xd) break;			// 何か押されたら終了する 

		COLOR(LIME,H_CYAN);
		LOCATE(50,18);
		printf("Please Enter");
		WAIT(300);						// 0.3secの時間待ち 
		INKEY(nkey);					// 何かキーが押されていたら変数に値を入力する 
		if (nkey == 0xd) break;			// 何か押されたら終了する 
	}

	CLS(BLACK, BLACK);

	system("cls");										// 画面のクリア
	NormalWarp( nWarpiru );										// ワープ
}

/***********************************************************************************************************************************************************
 動くスライム関数																以下、モンスターの関数
*******************************************************************************/
void SuraimMove( void )
{
	//変数宣言
	int cCode = 0;

	// ボタンが押されるまでアニメーション
	while(1)
	{
		Suraim();							// スライムを表示する
		WAIT(700);							// インターバル 0.7秒
		INKEY(cCode);						// 何かキーが押されていたら変数に値を入力する
		if (cCode != 0) break;				// 何か押されたら終了する
		Suraim2();							// スライム２を表示する
		WAIT(700);							// インターバル 0.7秒
		INKEY(cCode);						// 何かキーが押されていたら変数に値を入力する
		if (cCode != 0) break;				// 何か押されたら終了する
	}
}

/*******************************************************************************
 スライム関数
*******************************************************************************/
void Suraim( void )
{
	//場所指定の変数宣言
	int nVertical = NUM_LOCATION_VERTICAL;
	int nHorizontal = NUM_LOCATION_HORIZONTAL;

	/*
	□□□□□□□□□□□□□□□
	□□□□□□□■□□□□□□□
	□□□□□□□■□□□□□□□
	□□□□□□■■■□□□□□□
	□□□□□■■■■■□□□□□
	□□□■■■■■■■■■□□□
	□□■■■□■■■□■■■□□
	□■■■□■□■□■□■■■□
	■■■■□■□■□■□■■■■
	■■■■■□■■■□■■■■■
	■■■□■■■■■■■□■■■
	■■■□■■■■■■■□■■■
	□■■■□□□□□□□■■■□
	□□□■■■■■■■■■□□□
	*/

	//配列スライム
	char aSuraim[NUM_SURAIM_VERTICAL][NUM_SURAIM_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
		{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,1,1,1,3,1,1,1,3,1,1,1,0,0},
		{0,1,1,1,3,0,3,1,3,0,3,1,1,1,0},
		{1,1,1,1,3,0,3,1,3,0,3,1,1,1,1},
		{1,1,1,1,1,3,1,1,1,3,1,1,1,1,1},
		{1,1,1,2,1,1,1,1,1,1,1,2,1,1,1},
		{1,1,1,2,1,1,1,1,1,1,1,2,1,1,1},
		{0,1,1,1,2,2,2,2,2,2,2,1,1,1,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,0,0,0}
	};

	//スライムの表示
	for(int nCnt_x = 0; nCnt_x < NUM_SURAIM_VERTICAL; nCnt_x++)
	{
		LOCATE(nHorizontal, nVertical++);			// 場所指定

		for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_HORIZONTAL; nCnt_y++)
		{
			if(aSuraim[nCnt_x][nCnt_y] == 1)		//１の場合
			{
				BACKCOLOR(H_BLUE);					//体の部分：青
				printf("　");
			}
			else if(aSuraim[nCnt_x][nCnt_y] == 2)	// ２の場合
			{
				BACKCOLOR(H_RED);					// 口の部分：赤
				printf("　");
			}
			else if(aSuraim[nCnt_x][nCnt_y] == 3)	// ３の場合
			{
				BACKCOLOR(WHITE);					// 目の周り：白
				printf("　");
			}
			else if(aSuraim[nCnt_x][nCnt_y] == 0)	// ０の場合
			{
				BACKCOLOR(BLACK);					// 背景上部分＋目：黒
				printf("　");
			}//if.fin
		}

		printf("\n");

	}//for.fin
}

/*******************************************************************************
 スライム2関数
*******************************************************************************/
void Suraim2( void )
{
	//場所指定の変数宣言
	int nVertical = NUM_LOCATION_VERTICAL;
	int nHorizontal = NUM_LOCATION_HORIZONTAL;

	/*
	□□□□□□□□□□□□□□□
	□□□□□□□■□□□□□□□
	□□□□□□■■■□□□□□□
	□□□□□■■■■■□□□□□
	□□□■■■■■■■■■□□□
	□□■■■■■■■■■■■□□
	□■■■■■■■■■■■■■□
	■■■■■□■■■□■■■■■
	■■■■□■□■□■□■■■■
	■■■■□■□■□■□■■■■
	■■■□■□■■■□■□■■■
	■■■□□■■■■■□□■■■
	□■■■□□□□□□□■■■□
	□□■■■■■■■■■■■□□
	*/

	//配列スライム2
	char aSuraim2[NUM_SURAIM_VERTICAL][NUM_SURAIM_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
		{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{1,1,1,1,1,3,1,1,1,3,1,1,1,1,1},
		{1,1,1,1,3,0,3,1,3,0,3,1,1,1,1},
		{1,1,1,1,3,0,3,1,3,0,3,1,1,1,1},
		{1,1,1,2,1,3,1,1,1,3,1,2,1,1,1},
		{1,1,1,2,2,1,1,1,1,1,2,2,1,1,1},
		{0,1,1,1,2,2,2,2,2,2,2,1,1,1,0},
		{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0}
	};

	//スライムの表示
	for(int nCnt_x = 0; nCnt_x < NUM_SURAIM_VERTICAL; nCnt_x++)
	{
		LOCATE(nHorizontal, nVertical++);			// 場所指定

		for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_HORIZONTAL; nCnt_y++)
		{
			if(aSuraim2[nCnt_x][nCnt_y] == 1)		//１の場合
			{
				BACKCOLOR(H_BLUE);					//体の部分：青
				printf("　");
			}
			else if(aSuraim2[nCnt_x][nCnt_y] == 2)	// ２の場合
			{
				BACKCOLOR(H_RED);					// 口の部分：赤
				printf("　");
			}
			else if(aSuraim2[nCnt_x][nCnt_y] == 3)	// ３の場合
			{
				BACKCOLOR(WHITE);					// 目の周り：白
				printf("　");
			}
			else if(aSuraim2[nCnt_x][nCnt_y] == 0)	// ０の場合
			{
				BACKCOLOR(BLACK);					// 背景上部分＋目：黒
				printf("　");
			}//if.fin
		}

		printf("\n");

	}//for.fin
}

/***********************************************************************************************************************************************************
 動くメタルスライム関数															メタルスライム
*******************************************************************************/
void MetalSuraimMove( void )
{
	//変数宣言
	int cCode = 0;

	// ボタンが押されるまでアニメーション
	while(1)
	{
		MetalSuraim();						// メタルスライムを表示する
		WAIT(700);							// インターバル 0.7秒
		INKEY(cCode);						// 何かキーが押されていたら変数に値を入力する
		if (cCode != 0) break;				// 何か押されたら終了する
		MetalSuraim2();						// メタルスライム２を表示する
		WAIT(700);							// インターバル 0.7秒
		INKEY(cCode);						// 何かキーが押されていたら変数に値を入力する
		if (cCode != 0) break;				// 何か押されたら終了する
	}
}

/*******************************************************************************
 メタルスライム関数
*******************************************************************************/
void MetalSuraim( void )
{
	//場所指定の変数宣言
	int nVertical = NUM_LOCATION_VERTICAL;
	int nHorizontal = NUM_LOCATION_HORIZONTAL;

	/*
	□□□□□□□□□□□□□□□
	□□□□□□□■□□□□□□□
	□□□□□□□■□□□□□□□
	□□□□□□■■■□□□□□□
	□□□□□■■■■■□□□□□
	□□□■■■■■■■■■□□□
	□□■■■□■■■□■■■□□
	□■■■□■□■□■□■■■□
	■■■■□■□■□■□■■■■
	■■■■■□■■■□■■■■■
	■■■□■■■■■■■□■■■
	■■■□■■■■■■■□■■■
	□■■■□□□□□□□■■■□
	□□□■■■■■■■■■□□□
	*/

	//配列スライム
	char aSuraim[NUM_SURAIM_VERTICAL][NUM_SURAIM_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
		{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,1,1,1,3,1,1,1,3,1,1,1,0,0},
		{0,1,1,1,3,0,3,1,3,0,3,1,1,1,0},
		{1,1,1,1,3,0,3,1,3,0,3,1,1,1,1},
		{1,1,1,1,1,3,1,1,1,3,1,1,1,1,1},
		{1,1,1,2,1,1,1,1,1,1,1,2,1,1,1},
		{1,1,1,2,1,1,1,1,1,1,1,2,1,1,1},
		{0,1,1,1,2,2,2,2,2,2,2,1,1,1,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,0,0,0}
	};

	//メタルスライムの表示
	for(int nCnt_x = 0; nCnt_x < NUM_SURAIM_VERTICAL; nCnt_x++)
	{
		LOCATE(nHorizontal, nVertical++);			// 場所指定

		for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_HORIZONTAL; nCnt_y++)
		{
			if(aSuraim[nCnt_x][nCnt_y] == 1)		// １の場合
			{
				BACKCOLOR(GRAY);					// 体の部分：青
				printf("　");
			}
			else if(aSuraim[nCnt_x][nCnt_y] == 2)	// ２の場合
			{
				BACKCOLOR(H_RED);					// 口の部分：赤
				printf("　");
			}
			else if(aSuraim[nCnt_x][nCnt_y] == 3)	// ３の場合
			{
				BACKCOLOR(WHITE);					// 目の周り：白
				printf("　");
			}
			else if(aSuraim[nCnt_x][nCnt_y] == 0)	// ０の場合
			{
				BACKCOLOR(BLACK);					// 背景＋目：黒
				printf("　");
			}//if.fin
		}

		printf("\n");

	}//for.fin
}

/*******************************************************************************
 メタルスライム2関数
*******************************************************************************/
void MetalSuraim2( void )
{
	//場所指定の変数宣言
	int nVertical = NUM_LOCATION_VERTICAL;
	int nHorizontal = NUM_LOCATION_HORIZONTAL;

	/*
	□□□□□□□□□□□□□□□
	□□□□□□□■□□□□□□□
	□□□□□□■■■□□□□□□
	□□□□□■■■■■□□□□□
	□□□■■■■■■■■■□□□
	□□■■■■■■■■■■■□□
	□■■■■■■■■■■■■■□
	■■■■■□■■■□■■■■■
	■■■■□■□■□■□■■■■
	■■■■□■□■□■□■■■■
	■■■□■□■■■□■□■■■
	■■■□□■■■■■□□■■■
	□■■■□□□□□□□■■■□
	□□■■■■■■■■■■■□□
	*/

	//配列スライム2
	char aSuraim2[NUM_SURAIM_VERTICAL][NUM_SURAIM_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
		{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{1,1,1,1,1,3,1,1,1,3,1,1,1,1,1},
		{1,1,1,1,3,0,3,1,3,0,3,1,1,1,1},
		{1,1,1,1,3,0,3,1,3,0,3,1,1,1,1},
		{1,1,1,2,1,3,1,1,1,3,1,2,1,1,1},
		{1,1,1,2,2,1,1,1,1,1,2,2,1,1,1},
		{0,1,1,1,2,2,2,2,2,2,2,1,1,1,0},
		{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0}
	};

	//メタルスライムの表示
	for(int nCnt_x = 0; nCnt_x < NUM_SURAIM_VERTICAL; nCnt_x++)
	{
		LOCATE(nHorizontal, nVertical++);			// 場所指定

		for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_HORIZONTAL; nCnt_y++)
		{
			if(aSuraim2[nCnt_x][nCnt_y] == 1)		// １の場合
			{
				BACKCOLOR(GRAY);					// 体の部分：青
				printf("　");
			}
			else if(aSuraim2[nCnt_x][nCnt_y] == 2)	// ２の場合
			{
				BACKCOLOR(H_RED);					// 口の部分：赤
				printf("　");
			}
			else if(aSuraim2[nCnt_x][nCnt_y] == 3)	// ３の場合
			{
				BACKCOLOR(WHITE);					// 目の周り：白
				printf("　");
			}
			else if(aSuraim2[nCnt_x][nCnt_y] == 0)	// ０の場合
			{
				BACKCOLOR(BLACK);					// 背景＋目：黒
				printf("　");
			}//if.fin
		}

		printf("\n");

	}//for.fin
}

/***********************************************************************************************************************************************************
 動くぶちスライム関数															ぶちスライム
*******************************************************************************/
void ButiSuraimMove( void )
{
	//変数宣言
	int cCode = 0;

	// ボタンが押されるまでアニメーション
	while(1)
	{
		ButiSuraim();						// ぶちスライムを表示する
		WAIT(700);							// インターバル 0.7秒
		INKEY(cCode);						// 何かキーが押されていたら変数に値を入力する
		if (cCode != 0) break;				// 何か押されたら終了する
		ButiSuraim2();						// ぶちスライム２を表示する
		WAIT(700);							// インターバル 0.7秒
		INKEY(cCode);						// 何かキーが押されていたら変数に値を入力する
		if (cCode != 0) break;				// 何か押されたら終了する
	}
}

/*******************************************************************************
 ぶちスライム関数
*******************************************************************************/
void ButiSuraim( void )
{
	//場所指定の変数宣言
	int nVertical = NUM_LOCATION_VERTICAL;
	int nHorizontal = NUM_LOCATION_HORIZONTAL;

	/*
	□□□□□□□□□□□□□□□
	□□□□□□□■□□□□□□□
	□□□□□□□■□□□□□□□
	□□□□□□■■■□□□□□□
	□□□□□■■■■■□□□□□
	□□□■■■■■■■■■□□□
	□□■■■□■■■□■■■□□
	□■■■□■□■□■□■■■□
	■■■■□■□■□■□■■■■
	■■■■■□■■■□■■■■■
	■■■□■■■■■■■□■■■
	■■■□■■■■■■■□■■■
	□■■■□□□□□□□■■■□
	□□□■■■■■■■■■□□□
	*/

	//配列スライム
	char aSuraim[NUM_SURAIM_VERTICAL][NUM_SURAIM_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,4,1,1,0,0,0,0,0,0},
		{0,0,0,0,0,4,4,4,1,1,0,0,0,0,0},
		{0,0,0,1,4,4,4,1,1,4,4,1,0,0,0},
		{0,0,1,1,1,3,1,1,4,3,4,4,1,0,0},
		{0,1,4,1,3,0,3,1,3,0,3,4,1,1,0},
		{1,1,1,1,3,0,3,1,3,0,3,4,1,1,1},
		{1,1,1,1,1,3,1,1,4,3,4,1,1,1,1},
		{4,4,1,2,1,1,1,1,1,1,1,2,1,1,4},
		{4,4,4,2,1,1,1,1,1,1,1,2,4,4,1},
		{0,4,4,1,2,2,2,2,2,2,2,1,4,4,0},
		{0,0,0,1,1,1,1,1,1,1,1,4,0,0,0}
	};

	//ぶちスライムの表示
	for(int nCnt_x = 0; nCnt_x < NUM_SURAIM_VERTICAL; nCnt_x++)
	{
		LOCATE(nHorizontal, nVertical++);			// 場所指定

		for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_HORIZONTAL; nCnt_y++)
		{
			if(aSuraim[nCnt_x][nCnt_y] == 1)		// １の場合
			{
				BACKCOLOR(YELLOW);					// 体の部分：黄色
				printf("　");
			}
			else if(aSuraim[nCnt_x][nCnt_y] == 2)	// ２の場合
			{
				BACKCOLOR(H_RED);					// 口の部分：赤
				printf("　");
			}
			else if(aSuraim[nCnt_x][nCnt_y] == 3)	// ３の場合
			{
				BACKCOLOR(WHITE);					// 目の周り：白
				printf("　");
			}
			else if(aSuraim[nCnt_x][nCnt_y] == 4)	// ４の場合
			{
				BACKCOLOR(H_BLACK);					// ぶち：灰色
				printf("　");
			}
			else if(aSuraim[nCnt_x][nCnt_y] == 0)	// ０の場合
			{
				BACKCOLOR(BLACK);					// 背景＋目：黒
				printf("　");
			}//if.fin
		}

		printf("\n");

	}//for.fin
}

/*******************************************************************************
 ぶちスライム2関数
*******************************************************************************/
void ButiSuraim2( void )
{
	//場所指定の変数宣言
	int nVertical = NUM_LOCATION_VERTICAL;
	int nHorizontal = NUM_LOCATION_HORIZONTAL;

	/*
	□□□□□□□□□□□□□□□
	□□□□□□□■□□□□□□□
	□□□□□□■■■□□□□□□
	□□□□□■■■■■□□□□□
	□□□■■■■■■■■■□□□
	□□■■■■■■■■■■■□□
	□■■■■■■■■■■■■■□
	■■■■■□■■■□■■■■■
	■■■■□■□■□■□■■■■
	■■■■□■□■□■□■■■■
	■■■□■□■■■□■□■■■
	■■■□□■■■■■□□■■■
	□■■■□□□□□□□■■■□
	□□■■■■■■■■■■■□□
	*/

	//配列スライム2
	char aSuraim2[NUM_SURAIM_VERTICAL][NUM_SURAIM_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
		{0,0,0,0,0,4,1,1,1,1,0,0,0,0,0},
		{0,0,0,1,4,4,4,1,1,4,1,1,0,0,0},
		{0,0,1,1,4,4,1,1,1,1,1,1,1,0,0},
		{0,1,1,1,4,1,1,1,1,4,4,1,1,1,0},
		{1,1,1,1,1,3,1,1,4,3,4,4,1,1,1},
		{1,1,4,1,3,0,3,1,3,0,3,4,1,1,1},
		{1,1,1,1,3,0,3,1,3,0,3,4,1,1,1},
		{1,1,1,2,1,3,1,1,4,3,4,2,1,1,1},
		{1,4,1,2,2,1,1,1,1,1,2,2,1,1,4},
		{0,4,4,1,2,2,2,2,2,2,2,1,4,1,0},
		{0,0,4,4,1,1,1,1,1,1,1,4,4,0,0}
	};

	//ぶちスライムの表示
	for(int nCnt_x = 0; nCnt_x < NUM_SURAIM_VERTICAL; nCnt_x++)
	{
		LOCATE(nHorizontal, nVertical++);			// 場所指定

		for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_HORIZONTAL; nCnt_y++)
		{
			if(aSuraim2[nCnt_x][nCnt_y] == 1)		// １の場合
			{
				BACKCOLOR(YELLOW);					// 体の部分：黄色
				printf("　");
			}
			else if(aSuraim2[nCnt_x][nCnt_y] == 2)	// ２の場合
			{
				BACKCOLOR(H_RED);					// 口の部分：赤
				printf("　");
			}
			else if(aSuraim2[nCnt_x][nCnt_y] == 3)	// ３の場合
			{
				BACKCOLOR(WHITE);					// 目の周り：白
				printf("　");
			}
			else if(aSuraim2[nCnt_x][nCnt_y] == 4)	// ４の場合
			{
				BACKCOLOR(H_BLACK);					// ぶち：灰色
				printf("　");
			}
			else if(aSuraim2[nCnt_x][nCnt_y] == 0)	// ０の場合
			{
				BACKCOLOR(BLACK);					// 背景＋目：黒
				printf("　");
			}//if.fin
		}

		printf("\n");

	}//for.fin
}

/***********************************************************************************************************************************************************
 動くスライムダーク関数															スライムダーク
*******************************************************************************/
void SuraimDarkMove( void )
{
	//変数宣言
	int cCode = 0;

	// ボタンが押されるまでアニメーション
	while(1)
	{
		SuraimDark();						// スライムダークを表示する
		WAIT(700);							// インターバル 0.7秒
		INKEY(cCode);						// 何かキーが押されていたら変数に値を入力する
		if (cCode != 0) break;				// 何か押されたら終了する
		SuraimDark2();						// スライムダーク２を表示する
		WAIT(700);							// インターバル 0.7秒
		INKEY(cCode);						// 何かキーが押されていたら変数に値を入力する
		if (cCode != 0) break;				// 何か押されたら終了する
	}
}

/*******************************************************************************
 スライムダーク関数
*******************************************************************************/
void SuraimDark( void )
{
	//場所指定の変数宣言
	int nVertical = NUM_DARK_VERTICAL;
	int nHorizontal = NUM_DARK_HORIZONTAL;
	
	/*
	□□□□□□□□□□□□□□□
	□□□□□□□■□□□□□□□
	□□□□□□□■□□□□□□□
	□□□□□□■■■□□□□□□
	□□□□□■■■■■□□□□□
	□□□■■■■■■■■■□□□
	□□■■■□■■■□■■■□□
	□■■■□■□■□■□■■■□
	■■■■□■□■□■□■■■■
	■■■■■□■■■□■■■■■
	■■■□■■■■■■■□■■■
	■■■□■■■■■■■□■■■
	□■■■□□□□□□□■■■□
	□□□■■■■■■■■■□□□
	*/

	//配列スライム
	char aSuraimDark[NUM_SURAIM_VERTICAL][NUM_SURAIM_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
		{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,1,1,1,3,1,1,1,3,1,1,1,0,0},
		{0,1,1,1,3,4,3,1,3,4,3,1,1,1,0},
		{1,1,1,1,3,4,3,1,3,4,3,1,1,1,1},
		{1,1,1,1,1,3,1,1,1,3,1,1,1,1,1},
		{1,1,1,2,1,1,1,1,1,1,1,2,1,1,1},
		{1,1,1,2,1,1,1,1,1,1,1,2,1,1,1},
		{0,1,1,1,2,2,2,2,2,2,2,1,1,1,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,0,0,0}
	};

	//スライムの表示
	for(int nCnt_x = 0; nCnt_x < NUM_SURAIM_VERTICAL; nCnt_x++)
	{
		LOCATE(nHorizontal, nVertical++);				// 場所指定

		for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_HORIZONTAL; nCnt_y++)
		{
			if(aSuraimDark[nCnt_x][nCnt_y] == 1)		//１の場合
			{
				BACKCOLOR(BLACK);						//体の部分：黒
				printf("　");
			}
			else if(aSuraimDark[nCnt_x][nCnt_y] == 2)	// ２の場合
			{
				BACKCOLOR(H_BLACK);						// 口の部分：灰色
				printf("　");
			}
			else if(aSuraimDark[nCnt_x][nCnt_y] == 3)	// ３の場合
			{
				BACKCOLOR(WHITE);						// 目の周り：白
				printf("　");
			}
			else if(aSuraimDark[nCnt_x][nCnt_y] == 4)	// ４の場合
			{
				BACKCOLOR(BLACK);						// 目の部分：黒
				printf("　");
			}
			else if(aSuraimDark[nCnt_x][nCnt_y] == 0)	// ０の場合
			{
				BACKCOLOR(WHITE);						// 背景部分：白
				printf("　");
			}//if.fin
		}

		printf("\n");

	}//for.fin
}

/*******************************************************************************
 スライムダーク2関数
*******************************************************************************/
void SuraimDark2( void )
{
	//場所指定の変数宣言
	int nVertical = NUM_DARK_VERTICAL;
	int nHorizontal = NUM_DARK_HORIZONTAL;

	/*
	□□□□□□□□□□□□□□□
	□□□□□□□■□□□□□□□
	□□□□□□■■■□□□□□□
	□□□□□■■■■■□□□□□
	□□□■■■■■■■■■□□□
	□□■■■■■■■■■■■□□
	□■■■■■■■■■■■■■□
	■■■■■□■■■□■■■■■
	■■■■□■□■□■□■■■■
	■■■■□■□■□■□■■■■
	■■■□■□■■■□■□■■■
	■■■□□■■■■■□□■■■
	□■■■□□□□□□□■■■□
	□□■■■■■■■■■■■□□
	*/

	//配列スライム2
	char aSuraimDark2[NUM_SURAIM_VERTICAL][NUM_SURAIM_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
		{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{1,1,1,1,1,3,1,1,1,3,1,1,1,1,1},
		{1,1,1,1,3,4,3,1,3,4,3,1,1,1,1},
		{1,1,1,1,3,4,3,1,3,4,3,1,1,1,1},
		{1,1,1,2,1,3,1,1,1,3,1,2,1,1,1},
		{1,1,1,2,2,1,1,1,1,1,2,2,1,1,1},
		{0,1,1,1,2,2,2,2,2,2,2,1,1,1,0},
		{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0}
	};

	//スライムの表示
	for(int nCnt_x = 0; nCnt_x < NUM_SURAIM_VERTICAL; nCnt_x++)
	{
		LOCATE(nHorizontal, nVertical++);				// 場所指定

		for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_HORIZONTAL; nCnt_y++)
		{
			if(aSuraimDark2[nCnt_x][nCnt_y] == 1)		//１の場合
			{
				BACKCOLOR(BLACK);						//体の部分：黒
				printf("　");
			}
			else if(aSuraimDark2[nCnt_x][nCnt_y] == 2)	// ２の場合
			{
				BACKCOLOR(H_BLACK);						// 口の部分：灰色
				printf("　");
			}
			else if(aSuraimDark2[nCnt_x][nCnt_y] == 3)	// ３の場合
			{
				BACKCOLOR(WHITE);						// 目の周り：白
				printf("　");
			}
			else if(aSuraimDark2[nCnt_x][nCnt_y] == 4)	// ４の場合
			{
				BACKCOLOR(BLACK);						// 目の部分：黒
				printf("　");
			}
			else if(aSuraimDark2[nCnt_x][nCnt_y] == 0)	// ０の場合
			{
				BACKCOLOR(WHITE);						// 背景部分：白
				printf("　");
			}//if.fin
		}

		printf("\n");

	}//for.fin
}

/***********************************************************************************************************************************************************
 ドラキー関数																	ドラキー
*******************************************************************************/
void Doraki( void )
{
	// 変数宣言
	int nVerDoraki = 3;
	int nHorDoraki = 26;

	/*
	□□□□□□□□□□□□□□□
	□□□■■□□□□□■■□□□
	□□□□□■□□□■□□□□□
	□■■■□■■■■■□■■■□
	■■■■■■□■□■■■■■■
	□■■■■■□■□■■■■■□
	□□■□■■■■■■■□■□□
	□□□□■□■■■□■□□□□
	□□■□■□□□□□■□■□□
	□□■■■■□□□■■■■■■
	□□□■■■■■■■■■■□□
	□□□□■□□■□□■■□□□
	□□□□□□□□■■■□□□□
	□□□□□□□□□□□□□□□
	*/

	// 配列ドラキー
	char aDoraki[NUM_SURAIM_VERTICAL][NUM_SURAIM_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,1,0,0,0,0,0,1,1,0,0,0},
		{0,0,0,0,0,1,0,0,0,1,0,0,0,0,0},
		{0,1,1,1,0,1,1,1,1,1,0,1,1,1,0},
		{1,1,1,1,1,1,3,1,3,1,1,1,1,1,1},
		{0,1,1,1,1,1,3,1,3,1,1,1,1,1,0},
		{0,0,1,0,1,1,1,1,1,1,1,0,1,0,0},
		{0,0,0,0,1,2,1,1,1,2,1,0,0,0,0},
		{0,0,1,0,1,2,2,2,2,2,1,0,1,0,0},
		{0,0,1,1,1,1,2,2,2,1,1,1,1,0,1},
		{0,0,0,1,1,1,1,1,1,1,1,1,0,1,0},
		{0,0,0,0,1,0,0,1,0,0,1,0,0,1,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,0,1,1,1,1,0,0,0}
	};

	// ドラキーの表示
	for(int nCnt_x = 0; nCnt_x < NUM_SURAIM_VERTICAL; nCnt_x++)
	{
		LOCATE(nHorDoraki, nVerDoraki++);			// 場所指定

		for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_HORIZONTAL; nCnt_y++)
		{
			if(aDoraki[nCnt_x][nCnt_y] == 1)		//１の場合
			{
				BACKCOLOR(L_BLUE);					//体の部分：濃い青
				printf("　");
			}
			else if(aDoraki[nCnt_x][nCnt_y] == 2)	// ２の場合
			{
				BACKCOLOR(H_RED);					// 口の部分：赤
				printf("　");
			}
			else if(aDoraki[nCnt_x][nCnt_y] == 3)	// ３の場合
			{
				BACKCOLOR(WHITE);					// 目：白
				printf("　");
			}
			else if(aDoraki[nCnt_x][nCnt_y] == 0)	// ０の場合
			{
				BACKCOLOR(BLACK);					// 背景部分：黒
				printf("　");
			}//if.fin
		}

		printf("\n");

	}//for.fin
}

/*******************************************************************************
 ドラキー２関数
*******************************************************************************/
void Doraki2( void )
{
	// 変数宣言
	int nVerDoraki = 3;
	int nHorDoraki = 26;

	/*
	□□□□□□□□□□□□□□□
	□□□■□□□□□□□■□□□
	□□□□■□□□□□■□□□□
	□■■□□■□□□■□□■■□
	■■■■□■■■■■□■■■■
	□□■■■■■■■■■■■□□
	□□■□■■□■□■■□■□□
	□□□□■■□■□■■□□□□
	□□□□■□■■■□■□□□□
	□□■□■□□□□□■□■□□
	□□■■■■□□□■■■■■■
	□□□■■■■■■■■■■□□
	□□□□■□□■□□■■□□□
	□□□□□□□□■■■□□□□
	*/

	// 配列ドラキー
	char aDoraki2[NUM_SURAIM_VERTICAL][NUM_SURAIM_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},
		{0,0,0,0,1,0,0,0,0,0,1,0,0,0,0},
		{0,1,1,0,0,1,0,0,0,1,0,0,1,1,0},
		{1,1,1,1,0,1,1,1,1,1,0,1,1,1,1},
		{0,0,1,1,1,1,3,1,3,1,1,1,1,0,0},
		{0,0,1,0,1,1,3,1,3,1,1,0,1,0,0},
		{0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
		{0,0,1,0,1,2,1,1,1,2,1,0,1,0,0},
		{0,0,1,1,1,1,2,2,2,1,1,1,1,0,1},
		{0,0,0,1,1,1,1,1,1,1,1,1,0,1,0},
		{0,0,0,0,1,0,0,1,0,0,1,0,0,1,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,0,1,1,1,1,0,0,0}
	};

	// ドラキーの表示
	for(int nCnt_x = 0; nCnt_x < NUM_SURAIM_VERTICAL; nCnt_x++)
	{
		LOCATE(nHorDoraki, nVerDoraki++);			// 場所指定

		for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_HORIZONTAL; nCnt_y++)
		{
			if(aDoraki2[nCnt_x][nCnt_y] == 1)		//１の場合
			{
				BACKCOLOR(L_BLUE);					//体の部分：濃い青
				printf("　");
			}
			else if(aDoraki2[nCnt_x][nCnt_y] == 2)	// ２の場合
			{
				BACKCOLOR(H_RED);					// 口の部分：赤
				printf("　");
			}
			else if(aDoraki2[nCnt_x][nCnt_y] == 3)	// ３の場合
			{
				BACKCOLOR(WHITE);					// 目：白
				printf("　");
			}
			else if(aDoraki2[nCnt_x][nCnt_y] == 0)	// ０の場合
			{
				BACKCOLOR(BLACK);					// 背景部分：黒
				printf("　");
			}//if.fin
		}

		printf("\n");

	}//for.fin
}

/***********************************************************************************************************************************************************
 ドラキーマ関数																	ドラキーマ
*******************************************************************************/
void DorakiMa( void )
{
	// 変数宣言
	int nVerDoraki = 3;
	int nHorDoraki = 26;

	/*
	□□□□□□□□□□□□□□□
	□□□■■□□□□□■■□□□
	□□□□□■□□□■□□□□□
	□■■■□■■■■■□■■■□
	■■■■■■□■□■■■■■■
	□■■■■■□■□■■■■■□
	□□■□■■■■■■■□■□□
	□□□□■□■■■□■□□□□
	□□■□■□□□□□■□■□□
	□□■■■■□□□■■■■■■
	□□□■■■■■■■■■■□□
	□□□□■□□■□□■■□□□
	□□□□□□□□■■■□□□□
	□□□□□□□□□□□□□□□
	*/

	// 配列ドラキー
	char aDoraki[NUM_SURAIM_VERTICAL][NUM_SURAIM_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,1,0,0,0,0,0,1,1,0,0,0},
		{0,0,0,0,0,1,0,0,0,1,0,0,0,0,0},
		{0,1,1,1,0,1,1,1,1,1,0,1,1,1,0},
		{1,1,1,1,1,1,3,1,3,1,1,1,1,1,1},
		{0,1,1,1,1,1,3,1,3,1,1,1,1,1,0},
		{0,0,1,0,1,1,1,1,1,1,1,0,1,0,0},
		{0,0,0,0,1,2,1,1,1,2,1,0,0,0,0},
		{0,0,1,0,1,2,2,2,2,2,1,0,1,0,0},
		{0,0,1,1,1,1,2,2,2,1,1,1,1,0,1},
		{0,0,0,1,1,1,1,1,1,1,1,1,0,1,0},
		{0,0,0,0,1,0,0,1,0,0,1,0,0,1,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,0,1,1,1,1,0,0,0}
	};

	// ドラキーの表示
	for(int nCnt_x = 0; nCnt_x < NUM_SURAIM_VERTICAL; nCnt_x++)
	{
		LOCATE(nHorDoraki, nVerDoraki++);			// 場所指定

		for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_HORIZONTAL; nCnt_y++)
		{
			if(aDoraki[nCnt_x][nCnt_y] == 1)		//１の場合
			{
				BACKCOLOR(YELLOW);					//体の部分：黄色
				printf("　");
			}
			else if(aDoraki[nCnt_x][nCnt_y] == 2)	// ２の場合
			{
				BACKCOLOR(H_RED);					// 口の部分：赤
				printf("　");
			}
			else if(aDoraki[nCnt_x][nCnt_y] == 3)	// ３の場合
			{
				BACKCOLOR(WHITE);					// 目：白
				printf("　");
			}
			else if(aDoraki[nCnt_x][nCnt_y] == 0)	// ０の場合
			{
				BACKCOLOR(BLACK);					// 背景部分：黒
				printf("　");
			}//if.fin
		}

		printf("\n");

	}//for.fin
}

/*******************************************************************************
 ドラキーマ２関数
*******************************************************************************/
void DorakiMa2( void )
{
	// 変数宣言
	int nVerDoraki = 3;
	int nHorDoraki = 26;

	/*
	□□□□□□□□□□□□□□□
	□□□■□□□□□□□■□□□
	□□□□■□□□□□■□□□□
	□■■□□■□□□■□□■■□
	■■■■□■■■■■□■■■■
	□□■■■■■■■■■■■□□
	□□■□■■□■□■■□■□□
	□□□□■■□■□■■□□□□
	□□□□■□■■■□■□□□□
	□□■□■□□□□□■□■□□
	□□■■■■□□□■■■■■■
	□□□■■■■■■■■■■□□
	□□□□■□□■□□■■□□□
	□□□□□□□□■■■□□□□
	*/

	// 配列ドラキー
	char aDoraki2[NUM_SURAIM_VERTICAL][NUM_SURAIM_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},
		{0,0,0,0,1,0,0,0,0,0,1,0,0,0,0},
		{0,1,1,0,0,1,0,0,0,1,0,0,1,1,0},
		{1,1,1,1,0,1,1,1,1,1,0,1,1,1,1},
		{0,0,1,1,1,1,3,1,3,1,1,1,1,0,0},
		{0,0,1,0,1,1,3,1,3,1,1,0,1,0,0},
		{0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
		{0,0,1,0,1,2,1,1,1,2,1,0,1,0,0},
		{0,0,1,1,1,1,2,2,2,1,1,1,1,0,1},
		{0,0,0,1,1,1,1,1,1,1,1,1,0,1,0},
		{0,0,0,0,1,0,0,1,0,0,1,0,0,1,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,0,1,1,1,1,0,0,0}
	};

	// ドラキーの表示
	for(int nCnt_x = 0; nCnt_x < NUM_SURAIM_VERTICAL; nCnt_x++)
	{
		LOCATE(nHorDoraki, nVerDoraki++);			// 場所指定

		for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_HORIZONTAL; nCnt_y++)
		{
			if(aDoraki2[nCnt_x][nCnt_y] == 1)		//１の場合
			{
				BACKCOLOR(YELLOW);					//体の部分：黄色
				printf("　");
			}
			else if(aDoraki2[nCnt_x][nCnt_y] == 2)	// ２の場合
			{
				BACKCOLOR(H_RED);					// 口の部分：赤
				printf("　");
			}
			else if(aDoraki2[nCnt_x][nCnt_y] == 3)	// ３の場合
			{
				BACKCOLOR(WHITE);					// 目：白
				printf("　");
			}
			else if(aDoraki2[nCnt_x][nCnt_y] == 0)	// ０の場合
			{
				BACKCOLOR(BLACK);					// 背景部分：黒
				printf("　");
			}//if.fin
		}

		printf("\n");

	}//for.fin
}

/***********************************************************************************************************************************************************
 タホドラキー関数																タホドラキー
*******************************************************************************/
void TahoDoraki( void )
{
	// 変数宣言
	int nVerDoraki = 3;
	int nHorDoraki = 26;

	/*
	□□□□□□□□□□□□□□□
	□□□■■□□□□□■■□□□
	□□□□□■□□□■□□□□□
	□■■■□■■■■■□■■■□
	■■■■■■□■□■■■■■■
	□■■■■■□■□■■■■■□
	□□■□■■■■■■■□■□□
	□□□□■□■■■□■□□□□
	□□■□■□□□□□■□■□□
	□□■■■■□□□■■■■■■
	□□□■■■■■■■■■■□□
	□□□□■□□■□□■■□□□
	□□□□□□□□■■■□□□□
	□□□□□□□□□□□□□□□
	*/

	// 配列ドラキー
	char aDoraki[NUM_SURAIM_VERTICAL][NUM_SURAIM_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,1,0,0,0,0,0,1,1,0,0,0},
		{0,0,0,0,0,1,0,0,0,1,0,0,0,0,0},
		{0,1,1,1,0,1,1,1,1,1,0,1,1,1,0},
		{1,1,1,1,1,1,3,1,3,1,1,1,1,1,1},
		{0,1,1,1,1,1,3,1,3,1,1,1,1,1,0},
		{0,0,1,0,1,1,1,1,1,1,1,0,1,0,0},
		{0,0,0,0,1,2,1,1,1,2,1,0,0,0,0},
		{0,0,1,0,1,2,2,2,2,2,1,0,1,0,0},
		{0,0,1,1,1,1,2,2,2,1,1,1,1,0,1},
		{0,0,0,1,1,1,1,1,1,1,1,1,0,1,0},
		{0,0,0,0,1,0,0,1,0,0,1,0,0,1,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,0,1,1,1,1,0,0,0}
	};

	// ドラキーの表示
	for(int nCnt_x = 0; nCnt_x < NUM_SURAIM_VERTICAL; nCnt_x++)
	{
		LOCATE(nHorDoraki, nVerDoraki++);			// 場所指定

		for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_HORIZONTAL; nCnt_y++)
		{
			if(aDoraki[nCnt_x][nCnt_y] == 1)		//１の場合
			{
				BACKCOLOR(LIME);					//体の部分：ライム
				printf("　");
			}
			else if(aDoraki[nCnt_x][nCnt_y] == 2)	// ２の場合
			{
				BACKCOLOR(H_RED);					// 口の部分：赤
				printf("　");
			}
			else if(aDoraki[nCnt_x][nCnt_y] == 3)	// ３の場合
			{
				BACKCOLOR(WHITE);					// 目：白
				printf("　");
			}
			else if(aDoraki[nCnt_x][nCnt_y] == 0)	// ０の場合
			{
				BACKCOLOR(BLACK);					// 背景部分：黒
				printf("　");
			}//if.fin
		}

		printf("\n");

	}//for.fin
}

/*******************************************************************************
 タホドラキー２関数
*******************************************************************************/
void TahoDoraki2( void )
{
	// 変数宣言
	int nVerDoraki = 3;
	int nHorDoraki = 26;

	/*
	□□□□□□□□□□□□□□□
	□□□■□□□□□□□■□□□
	□□□□■□□□□□■□□□□
	□■■□□■□□□■□□■■□
	■■■■□■■■■■□■■■■
	□□■■■■■■■■■■■□□
	□□■□■■□■□■■□■□□
	□□□□■■□■□■■□□□□
	□□□□■□■■■□■□□□□
	□□■□■□□□□□■□■□□
	□□■■■■□□□■■■■■■
	□□□■■■■■■■■■■□□
	□□□□■□□■□□■■□□□
	□□□□□□□□■■■□□□□
	*/

	// 配列ドラキー
	char aDoraki2[NUM_SURAIM_VERTICAL][NUM_SURAIM_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},
		{0,0,0,0,1,0,0,0,0,0,1,0,0,0,0},
		{0,1,1,0,0,1,0,0,0,1,0,0,1,1,0},
		{1,1,1,1,0,1,1,1,1,1,0,1,1,1,1},
		{0,0,1,1,1,1,3,1,3,1,1,1,1,0,0},
		{0,0,1,0,1,1,3,1,3,1,1,0,1,0,0},
		{0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
		{0,0,1,0,1,2,1,1,1,2,1,0,1,0,0},
		{0,0,1,1,1,1,2,2,2,1,1,1,1,0,1},
		{0,0,0,1,1,1,1,1,1,1,1,1,0,1,0},
		{0,0,0,0,1,0,0,1,0,0,1,0,0,1,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,0,1,1,1,1,0,0,0}
	};

	// ドラキーの表示
	for(int nCnt_x = 0; nCnt_x < NUM_SURAIM_VERTICAL; nCnt_x++)
	{
		LOCATE(nHorDoraki, nVerDoraki++);			// 場所指定

		for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_HORIZONTAL; nCnt_y++)
		{
			if(aDoraki2[nCnt_x][nCnt_y] == 1)		//１の場合
			{
				BACKCOLOR(LIME);					//体の部分：ライム
				printf("　");
			}
			else if(aDoraki2[nCnt_x][nCnt_y] == 2)	// ２の場合
			{
				BACKCOLOR(H_RED);					// 口の部分：赤
				printf("　");
			}
			else if(aDoraki2[nCnt_x][nCnt_y] == 3)	// ３の場合
			{
				BACKCOLOR(WHITE);					// 目：白
				printf("　");
			}
			else if(aDoraki2[nCnt_x][nCnt_y] == 0)	// ０の場合
			{
				BACKCOLOR(BLACK);					// 背景部分：黒
				printf("　");
			}//if.fin
		}

		printf("\n");

	}//for.fin
}

/***********************************************************************************************************************************************************
 バトル枠関数																	以下、バトル専用関数
*******************************************************************************/
void BattleFrame( int nFreamCloor, int nFreamBackCloor )
{
	// 変数宣言(場所指定)
	int nVer = 1;
	int nHor = 1;
	int nComandVer = 19;
	int nComandHor = 7;
	int nStatusVer = 19;
	int nStatusHor = 68;

	// バトル時に使用するフレーム
	char aBattleFrame[NUM_TITLE_VERTICAL][NUM_TITLE_HORIZONTAL] = 
	{
		{9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9},
		{2,3,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,9,1,1,1,1,1,9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9,2},
		{2,2,5,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,2},
		{2,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,2},
		{2,2,6,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,2},
		{2,9,1,1,1,1,1,9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9,2},
		{9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9}
	};

	//フレーム表示の処理
	for(int nVertical = 0; nVertical < NUM_TITLE_VERTICAL; nVertical++)				// 縦軸ループ処理
	{
		LOCATE(nHor, nVer++);														// 場所指定

		for(int nHorizontal = 0; nHorizontal < NUM_TITLE_HORIZONTAL; nHorizontal++)	// 横軸ループ処理
		{
			if(aBattleFrame[nVertical][nHorizontal] == 1)			// 条件が『１』の時
			{
				COLOR(nFreamCloor, nFreamBackCloor);				// 着色
				printf("―");
			}
			else if(aBattleFrame[nVertical][nHorizontal] == 2)		// 条件が『２』の時
			{
				COLOR(nFreamCloor, nFreamBackCloor);				// 着色
				printf("｜");
			}
			else if(aBattleFrame[nVertical][nHorizontal] == 3)		// 条件が『３』の時
			{
				COLOR(nFreamCloor, nFreamBackCloor);				// 着色
				printf("《");
			}
			else if(aBattleFrame[nVertical][nHorizontal] == 4)		// 条件が『４』の時
			{
				COLOR(nFreamCloor, nFreamBackCloor);				// 着色
				printf("》");
			}
			else if(aBattleFrame[nVertical][nHorizontal] == 5)		// 条件が『５』の時
			{
				COLOR(nFreamCloor, nFreamBackCloor);				// 着色
				printf("→");
			}
			else if(aBattleFrame[nVertical][nHorizontal] == 6)		// 条件が『６』の時
			{
				COLOR(nFreamCloor, nFreamBackCloor);				// 着色
				printf("B:");
			}
			else if(aBattleFrame[nVertical][nHorizontal] == 9)		// 条件が『９』の時
			{
				COLOR(nFreamCloor, nFreamBackCloor);				// 着色
				printf("◆");
			}
			else if(aBattleFrame[nVertical][nHorizontal] == 0)		// 条件が『０』の時
			{
				printf("　");
			}//if.fin
		}
		printf("\n");												//改行
	}//for.fin

	// コマンド文字の挿入 //
	LOCATE(nComandHor, nComandVer++);
	printf("たたかう");
	LOCATE(nComandHor, nComandVer++);
	printf("スキル ");
	LOCATE(nComandHor, nComandVer++);
	printf("カウンタ");
	LOCATE(nComandHor, nComandVer++);
	printf("もどる ");

	// ステイタス文字の挿入 //
	LOCATE(18, 2);
	printf("体力");
	LOCATE(50, 2);
	printf("魔力");
	LOCATE(nStatusHor, nStatusVer++);
	printf("攻撃 ");
	LOCATE(nStatusHor, nStatusVer++);
	printf("守備 ");
	LOCATE(nStatusHor, nStatusVer++);
	printf("回避値↓");
	LOCATE(nStatusHor, nStatusVer++);

}

/*******************************************************************************
 コメント欄リセット関数
*******************************************************************************/
void ComentReset( void )
{
	// 変数宣言
	int nVer = 19;
	int nHor = 17;

	// コメント欄を空白にする
	for(int nCnt = ZERO; nCnt < 4; nCnt++)
	{
		BACKCOLOR(BLACK);
		LOCATE(nHor,nVer++);
		printf("　　　　　　　　　　　　　　　　　　　　　　　　");
	}

}

/*******************************************************************************
 黒幕関数
*******************************************************************************/
void Koromaku( void )
{
	// 変数宣言
	int nVer = 3;
	int nHor = 26;

	// 黒幕の表示
	char akuromaku[NUM_SURAIM_VERTICAL][NUM_SURAIM_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}	
	};

	// 表示処理
	for(int nCnt_y = ZERO; nCnt_y < NUM_SURAIM_VERTICAL; nCnt_y++)
	{
		LOCATE(nHor, nVer++);										// 場所指定

		for(int nCnt_x = ZERO; nCnt_x < NUM_SURAIM_HORIZONTAL; nCnt_x++)
		{
			if(akuromaku[nCnt_y][nCnt_x] == 0)	// 0の場合
			{
				BACKCOLOR(BLACK);					// 黒
				printf("　");
			}
		}
		printf("\n");												// 改行
	}//forfin

}

/*******************************************************************************
 ブラックエフェクト関数
*******************************************************************************/
void BlackNormalEffect( void )
{
	// 変数宣言
	int nEffect_Ver1 = 3;
	int nEffect_Ver2 = 3;
	int nEffect_Hor1 = 4;
	int nEffect_Hor2 = 56;

	// エフェクト
	char aNormalEffect[NUM_SURAIM_VERTICAL][EFFECT_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0}
	};

	// エフェクト
	for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_VERTICAL; nCnt_y++)
	{
		LOCATE(nEffect_Hor1, nEffect_Ver1++);		// 場所指定

		for(int nCnt_x = 0; nCnt_x < EFFECT_HORIZONTAL; nCnt_x++)
		{
			if(aNormalEffect[nCnt_y][nCnt_x] == 0)	// 0の場合
			{
				BACKCOLOR(BLACK);					// Black
				printf("　");
			}
		}
		printf("\n");
	}//for.fin

	// エフェクト
	char aNormalEffect2[NUM_SURAIM_VERTICAL][EFFECT_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0}
	};

	// エフェクト
	for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_VERTICAL; nCnt_y++)
	{
		LOCATE(nEffect_Hor2, nEffect_Ver2++);				// 場所指定

		for(int nCnt_x = 0; nCnt_x < EFFECT_HORIZONTAL; nCnt_x++)
		{
			if(aNormalEffect2[nCnt_y][nCnt_x] == 0)			// １の場合
			{
				BACKCOLOR(BLACK);							// Black
				printf("　");
			}
		}
		printf("\n");
	}//for.fin

}

/*******************************************************************************
 ホワイトエフェクト関数
*******************************************************************************/
void WhiteNormalEffect( void )
{
	// 変数宣言
	int nEffect_Ver1 = 3;
	int nEffect_Ver2 = 3;
	int nEffect_Hor1 = 4;
	int nEffect_Hor2 = 56;

	// エフェクト：白
	char aNormalEffect[NUM_SURAIM_VERTICAL][EFFECT_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0}
	};

	// エフェクト：白の表示
	for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_VERTICAL; nCnt_y++)
	{
		LOCATE(nEffect_Hor1, nEffect_Ver1++);		// 場所指定

		for(int nCnt_x = 0; nCnt_x < EFFECT_HORIZONTAL; nCnt_x++)
		{
			if(aNormalEffect[nCnt_y][nCnt_x] == 0)	// 0の場合
			{
				BACKCOLOR(WHITE);					// 白
				printf("　");
			}
		}
		printf("\n");
	}//for.fin

	// エフェクト：白
	char aNormalEffect2[NUM_SURAIM_VERTICAL][EFFECT_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0}
	};

	// エフェクト：白の表示
	for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_VERTICAL; nCnt_y++)
	{
		LOCATE(nEffect_Hor2, nEffect_Ver2++);		// 場所指定

		for(int nCnt_x = 0; nCnt_x < EFFECT_HORIZONTAL; nCnt_x++)
		{
			if(aNormalEffect2[nCnt_y][nCnt_x] == 0)			// １の場合
			{
				BACKCOLOR(WHITE);					// 白
				printf("　");
			}
		}
		printf("\n");
	}//for.fin

}

/*******************************************************************************
 バルンダイブフェクト関数
*******************************************************************************/
void BarunDiveEffect( void )
{
	// 変数宣言
	int nEffect_Ver1 = 3;
	int nEffect_Ver2 = 3;
	int nEffect_Hor1 = 4;
	int nEffect_Hor2 = 56;

	// エフェクト
	char aNormalEffect[NUM_SURAIM_VERTICAL][EFFECT_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1}
	};

	// エフェクト：白の表示
	for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_VERTICAL; nCnt_y++)
	{
		LOCATE(nEffect_Hor1, nEffect_Ver1++);			// 場所指定

		for(int nCnt_x = 0; nCnt_x < EFFECT_HORIZONTAL; nCnt_x++)
		{
			if(aNormalEffect[nCnt_y][nCnt_x] == 0)		// 0の場合
			{
				BACKCOLOR(BLUE);						// 青
				printf("　");
			}
			else
			{
				BACKCOLOR(BLACK);						// 黒
				printf("　");
			}
		}
		printf("\n");
	}//for.fin

	// エフェクト：白
	char aNormalEffect2[NUM_SURAIM_VERTICAL][EFFECT_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1}
	};

	// エフェクト：白の表示
	for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_VERTICAL; nCnt_y++)
	{
		LOCATE(nEffect_Hor2, nEffect_Ver2++);			// 場所指定

		for(int nCnt_x = 0; nCnt_x < EFFECT_HORIZONTAL; nCnt_x++)
		{
			if(aNormalEffect2[nCnt_y][nCnt_x] == 0)		// １の場合
			{
				BACKCOLOR(BLUE);						// 青
				printf("　");
			}
			else
			{
				BACKCOLOR(BLACK);						// 黒
				printf("　");
			}
		}
		printf("\n");
	}//for.fin
}

/*******************************************************************************
 スラドラグーンエフェクト関数
*******************************************************************************/
void SuraDragunEffect( void )
{
	// 変数宣言
	int nEffect_Ver1 = 3;
	int nEffect_Ver2 = 3;
	int nEffect_Hor1 = 4;
	int nEffect_Hor2 = 56;

	// エフェクト
	char aNormalEffect[NUM_SURAIM_VERTICAL][EFFECT_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,2,0,0,0,0,3,0,0,0},
		{0,2,0,2,0,0,3,0,3,0,0},
		{2,1,1,2,1,1,3,1,3,1,1},
		{1,1,1,1,2,3,1,1,1,3,1},
		{1,1,1,1,2,3,1,1,1,3,2},
		{3,1,1,1,3,2,1,1,1,2,3},
		{3,1,1,1,3,2,1,1,1,2,1},
		{1,3,1,3,1,1,2,1,2,1,1},
		{0,3,0,3,0,0,2,0,2,0,0},
		{0,0,3,0,0,0,0,2,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0}
	};

	// エフェクト
	for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_VERTICAL; nCnt_y++)
	{
		LOCATE(nEffect_Hor1, nEffect_Ver1++);				// 場所指定

		for(int nCnt_x = 0; nCnt_x < EFFECT_HORIZONTAL; nCnt_x++)
		{
			if(aNormalEffect[nCnt_y][nCnt_x] == 1)			// 1の場合
			{
				BACKCOLOR(BLUE);
				printf("　");
			}
			else if(aNormalEffect[nCnt_y][nCnt_x] == 2)		// 2の場合
			{
				BACKCOLOR(YELLOW);
				printf("　");
			}
			else if(aNormalEffect[nCnt_y][nCnt_x] == 3)		// 3の場合
			{
				BACKCOLOR(LIME);
				printf("　");
			}
			else
			{
				BACKCOLOR(BLACK);
				printf("　");
			}
		}
		printf("\n");
	}//for.fin

	Sleep(200);

	// エフェクト
	char aNormalEffect2[NUM_SURAIM_VERTICAL][EFFECT_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,2,0,0,0,0,3,0,0,0},
		{0,2,0,2,0,0,3,0,3,0,0},
		{2,1,1,2,1,1,3,1,3,1,1},
		{2,1,1,1,2,3,1,1,1,3,2},
		{1,1,1,1,2,3,1,1,1,3,2},
		{3,1,1,1,3,2,1,1,1,2,3},
		{3,1,1,1,3,2,1,1,1,2,3},
		{1,3,1,3,1,1,2,1,2,1,1},
		{0,3,0,3,0,0,2,0,2,0,0},
		{0,0,3,0,0,0,0,2,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0}
	};

	// エフェクト
	for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_VERTICAL; nCnt_y++)
	{
		LOCATE(nEffect_Hor2, nEffect_Ver2++);				// 場所指定

		for(int nCnt_x = 0; nCnt_x < EFFECT_HORIZONTAL; nCnt_x++)
		{
			if(aNormalEffect[nCnt_y][nCnt_x] == 1)			// 1の場合
			{
				BACKCOLOR(BLUE);
				printf("　");
			}
			else if(aNormalEffect[nCnt_y][nCnt_x] == 2)		// 2の場合
			{
				BACKCOLOR(LIME);
				printf("　");
			}
			else if(aNormalEffect[nCnt_y][nCnt_x] == 3)		// 3の場合
			{
				BACKCOLOR(YELLOW);
				printf("　");
			}
			else
			{
				BACKCOLOR(BLACK);
				printf("　");
			}
		}
		printf("\n");
	}//for.fin
}

/*******************************************************************************
 ブラッシュフェクト関数
*******************************************************************************/
void BrushEffect( void )
{
	// 変数宣言
	int nEffect_Ver1 = 3;
	int nEffect_Ver2 = 3;
	int nEffect_Hor1 = 4;
	int nEffect_Hor2 = 56;

	// エフェクト
	char aNormalEffect[NUM_SURAIM_VERTICAL][EFFECT_HORIZONTAL] = 
	{
		{1,0,0,0,0,0,0,0,0,0,0},
		{0,1,0,0,0,0,0,0,0,0,0},
		{0,0,1,0,0,0,0,0,0,0,0},
		{0,0,0,1,0,0,0,0,0,0,1},
		{0,0,0,0,1,0,0,0,0,1,0},
		{0,0,0,0,0,1,0,0,1,0,0},
		{0,0,0,0,0,0,1,1,0,0,0},
		{0,0,0,0,0,0,1,1,0,0,0},
		{0,0,0,0,0,1,0,0,1,0,0},
		{0,0,0,0,1,0,0,0,0,1,0},
		{0,0,0,1,0,0,0,0,0,0,1},
		{0,0,1,0,0,0,0,0,0,0,0},
		{0,1,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0}
	};

	// エフェクト
	for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_VERTICAL; nCnt_y++)
	{
		LOCATE(nEffect_Hor1, nEffect_Ver1++);		// 場所指定

		for(int nCnt_x = 0; nCnt_x < EFFECT_HORIZONTAL; nCnt_x++)
		{
			if(aNormalEffect[nCnt_y][nCnt_x] == 1)	// 1の場合
			{
				BACKCOLOR(YELLOW);
				printf("　");
			}
			else
			{
				BACKCOLOR(BLACK);
				printf("　");
			}
		}
		printf("\n");
	}//for.fin

	// エフェクト：白
	char aNormalEffect2[NUM_SURAIM_VERTICAL][EFFECT_HORIZONTAL] = 
	{
		{0,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,1,0},
		{0,0,0,0,0,0,0,0,1,0,0},
		{1,0,0,0,0,0,0,1,0,0,0},
		{0,1,0,0,0,0,1,0,0,0,0},
		{0,0,1,0,0,1,0,0,0,0,0},
		{0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,1,1,0,0,0,0,0,0},
		{0,0,1,0,0,1,0,0,0,0,0},
		{0,1,0,0,0,0,1,0,0,0,0},
		{1,0,0,0,0,0,0,1,0,0,0},
		{0,0,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,0,0,1,0},
		{0,0,0,0,0,0,0,0,0,0,1}
	};

	// エフェクト
	for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_VERTICAL; nCnt_y++)
	{
		LOCATE(nEffect_Hor2, nEffect_Ver2++);		// 場所指定

		for(int nCnt_x = 0; nCnt_x < EFFECT_HORIZONTAL; nCnt_x++)
		{
			if(aNormalEffect2[nCnt_y][nCnt_x] == 1)			// １の場合
			{
				BACKCOLOR(YELLOW);
				printf("　");
			}
			else
			{
				BACKCOLOR(BLACK);
				printf("　");
			}
		}
		printf("\n");
	}//for.fin

}

/*******************************************************************************
 暗光弾エフェクト関数
*******************************************************************************/
void AnkouDanEffect( void )
{
	// 変数宣言
	int nEffect_Ver1 = 3;
	int nEffect_Ver2 = 3;
	int nEffect_Hor1 = 4;
	int nEffect_Hor2 = 56;

	// エフェクト
	char aNormalEffect[NUM_SURAIM_VERTICAL][EFFECT_HORIZONTAL] = 
	{
		{0,1,0,1,0,1,0,1,0,1,0},
		{1,0,1,0,1,0,1,0,1,0,1},
		{0,1,0,1,0,1,0,1,0,1,0},
		{1,0,1,0,1,0,1,0,1,0,1},
		{0,1,0,1,0,1,0,1,0,1,0},
		{1,0,1,0,1,0,1,0,1,0,1},
		{0,1,0,1,0,1,0,1,0,1,0},
		{1,0,1,0,1,0,1,0,1,0,1},
		{0,1,0,1,0,1,0,1,0,1,0},
		{1,0,1,0,1,0,1,0,1,0,1},
		{0,1,0,1,0,1,0,1,0,1,0},
		{1,0,1,0,1,0,1,0,1,0,1},
		{0,1,0,1,0,1,0,1,0,1,0},
		{1,0,1,0,1,0,1,0,1,0,1}
	};

	// エフェクト
	for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_VERTICAL; nCnt_y++)
	{
		LOCATE(nEffect_Hor1, nEffect_Ver1++);		// 場所指定

		for(int nCnt_x = 0; nCnt_x < EFFECT_HORIZONTAL; nCnt_x++)
		{
			if(aNormalEffect[nCnt_y][nCnt_x] == 0)			// １の場合
			{
				BACKCOLOR(YELLOW);
				printf("　");
			}
			else
			{
				BACKCOLOR(BLACK);
				printf("　");
			}
		}
		printf("\n");
	}//for.fin

	// エフェクト
	char aNormalEffect2[NUM_SURAIM_VERTICAL][EFFECT_HORIZONTAL] = 
	{
		{1,0,1,0,1,0,1,0,1,0,1},
		{0,1,0,1,0,1,0,1,0,1,0},
		{1,0,1,0,1,0,1,0,1,0,1},
		{0,1,0,1,0,1,0,1,0,1,0},
		{1,0,1,0,1,0,1,0,1,0,1},
		{0,1,0,1,0,1,0,1,0,1,0},
		{1,0,1,0,1,0,1,0,1,0,1},
		{0,1,0,1,0,1,0,1,0,1,0},
		{1,0,1,0,1,0,1,0,1,0,1},
		{0,1,0,1,0,1,0,1,0,1,0},
		{1,0,1,0,1,0,1,0,1,0,1},
		{0,1,0,1,0,1,0,1,0,1,0},
		{1,0,1,0,1,0,1,0,1,0,1},
		{0,1,0,1,0,1,0,1,0,1,0}
	};

	// エフェクト
	for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_VERTICAL; nCnt_y++)
	{
		LOCATE(nEffect_Hor2, nEffect_Ver2++);				// 場所指定

		for(int nCnt_x = 0; nCnt_x < EFFECT_HORIZONTAL; nCnt_x++)
		{
			if(aNormalEffect2[nCnt_y][nCnt_x] == 0)			// １の場合
			{
				BACKCOLOR(YELLOW);
				printf("　");
			}
			else
			{
				BACKCOLOR(BLACK);
				printf("　");
			}
		}
		printf("\n");
	}//for.fin
}

/*******************************************************************************
 メタルスターエフェクト関数
*******************************************************************************/
void MetalStarEffect( void )
{
	// 変数宣言
	int nEffect_Ver1 = 3;
	int nEffect_Ver2 = 3;
	int nEffect_Hor1 = 4;
	int nEffect_Hor2 = 56;
	int nMP3Handle = ZERO;

	// エフェクト
	char aNormalEffect[NUM_SURAIM_VERTICAL][EFFECT_HORIZONTAL] = 
	{
		{0,0,0,0,0,1,0,0,0,0,0},
		{0,0,2,0,0,0,1,0,0,2,0},
		{1,0,0,0,0,0,0,1,0,0,0},
		{0,1,1,0,0,0,0,0,1,0,0},
		{0,0,0,1,1,0,0,0,0,1,0},
		{0,0,2,0,0,1,1,0,0,0,1},
		{0,0,0,0,0,0,0,1,1,1,1},
		{0,0,0,0,0,0,0,1,1,1,1},
		{0,0,0,0,0,1,1,0,0,0,1},
		{0,2,0,1,1,0,0,0,0,1,0},
		{0,1,1,0,0,0,0,0,1,0,0},
		{1,0,0,0,0,2,0,1,0,2,0},
		{0,0,0,0,0,0,1,0,0,0,0},
		{0,0,0,0,0,1,0,0,0,0,0}
	};

	// エフェクト
	for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_VERTICAL; nCnt_y++)
	{
		LOCATE(nEffect_Hor1, nEffect_Ver1++);		// 場所指定

		for(int nCnt_x = 0; nCnt_x < EFFECT_HORIZONTAL; nCnt_x++)
		{
			if(aNormalEffect[nCnt_y][nCnt_x] == 0)			// 0の場合
			{
				BACKCOLOR(BLACK);
				printf("　");
			}
			else if(aNormalEffect[nCnt_y][nCnt_x] == 1)	// 1の場合
			{
				BACKCOLOR(H_BLACK);
				printf("　");
			}
			else
			{
				BACKCOLOR(YELLOW);
				printf("　");
			}
		}
		printf("\n");
	}//for.fin

	Sleep(200);

	// エフェクト
	char aNormalEffect2[NUM_SURAIM_VERTICAL][EFFECT_HORIZONTAL] = 
	{
		{0,0,0,0,0,1,0,0,2,0,0},
		{0,0,0,0,0,0,1,0,0,0,0},
		{1,0,0,0,0,0,0,1,0,0,0},
		{0,1,1,0,0,0,0,0,1,0,0},
		{0,0,0,1,1,0,2,0,0,1,0},
		{0,2,0,0,0,1,1,0,0,0,1},
		{0,0,0,0,0,0,0,1,1,1,1},
		{0,0,0,2,0,0,0,1,1,1,1},
		{0,0,0,0,0,1,1,0,0,0,1},
		{0,0,0,1,1,0,0,0,0,1,0},
		{0,1,1,0,2,0,0,0,1,0,0},
		{1,0,0,0,0,0,0,1,0,0,0},
		{0,0,0,0,0,0,1,0,2,0,0},
		{0,0,0,0,0,1,0,0,0,0,0}
	};

	// エフェクト
	for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_VERTICAL; nCnt_y++)
	{
		LOCATE(nEffect_Hor2, nEffect_Ver2++);				// 場所指定

		for(int nCnt_x = 0; nCnt_x < EFFECT_HORIZONTAL; nCnt_x++)
		{
			if(aNormalEffect2[nCnt_y][nCnt_x] == 0)			// 0の場合
			{
				BACKCOLOR(BLACK);
				printf("　");
			}
			else if(aNormalEffect2[nCnt_y][nCnt_x] == 1)	// 1の場合
			{
				BACKCOLOR(H_BLACK);
				printf("　");
			}
			else
			{
				BACKCOLOR(YELLOW);
				printf("　");
			}
		}
		printf("\n");
	}//for.fin

}

/*******************************************************************************
 グラビドンエフェクト関数
*******************************************************************************/
void GurabiDonEffect( void )
{
	// 変数宣言
	int nEffect_Ver1 = 3;
	int nEffect_Ver2 = 3;
	int nEffect_Hor1 = 4;
	int nEffect_Hor2 = 56;

	// エフェクト
	char aNormalEffect[NUM_SURAIM_VERTICAL][EFFECT_HORIZONTAL] = 
	{
		{1,0,0,0,0,1,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,0,0,0,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,2,2,2,0,0,0,0},
		{1,0,0,0,2,3,2,0,0,0,1},
		{1,0,0,0,2,2,2,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,0,0,0,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,1,0,0,0,0,1}
	};

	// エフェクト
	for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_VERTICAL; nCnt_y++)
	{
		LOCATE(nEffect_Hor1, nEffect_Ver1++);			// 場所指定

		for(int nCnt_x = 0; nCnt_x < EFFECT_HORIZONTAL; nCnt_x++)
		{
			if(aNormalEffect[nCnt_y][nCnt_x] == 1)		// 1の場合
			{
				BACKCOLOR(WHITE);
				printf("　");
			}
			else if(aNormalEffect[nCnt_y][nCnt_x] == 2)	// 2の場合
			{
				BACKCOLOR(LIME);
				printf("　");
			}
			else if(aNormalEffect[nCnt_y][nCnt_x] == 3)	// 3の場合
			{
				BACKCOLOR(YELLOW);
				printf("　");
			}
			else
			{
				BACKCOLOR(BLACK);
				printf("　");
			}
		}
		printf("\n");
	}//for.fin

	// エフェクト
	char aNormalEffect2[NUM_SURAIM_VERTICAL][EFFECT_HORIZONTAL] = 
	{
		{1,0,0,0,0,1,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,0,0,0,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,2,2,2,0,0,0,0},
		{1,0,0,0,2,3,2,0,0,0,1},
		{1,0,0,0,2,2,2,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,0,0,0,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,1,0,0,0,0,1}
	};

	// エフェクト
	for(int nCnt_y = 0; nCnt_y < NUM_SURAIM_VERTICAL; nCnt_y++)
	{
		LOCATE(nEffect_Hor2, nEffect_Ver2++);				// 場所指定

		for(int nCnt_x = 0; nCnt_x < EFFECT_HORIZONTAL; nCnt_x++)
		{
			if(aNormalEffect2[nCnt_y][nCnt_x] == 1)			// 1の場合
			{
				BACKCOLOR(WHITE);
				printf("　");
			}
			else if(aNormalEffect2[nCnt_y][nCnt_x] == 2)	// 2の場合
			{
				BACKCOLOR(LIME);
				printf("　");
			}
			else if(aNormalEffect2[nCnt_y][nCnt_x] == 3)	// 3の場合
			{
				BACKCOLOR(YELLOW);
				printf("　");
			}
			else
			{
				BACKCOLOR(BLACK);
				printf("　");
			}
		}
		printf("\n");
	}//for.fin

	COLOR(WHITE,BLACK);

}

/*******************************************************************************
 回復エフェクト関数
*******************************************************************************/
void KifukuEffect( void )
{
	COLOR(H_MAGENTA);
	LOCATE(31,3);
	printf("◆");
	Sleep(200);
	LOCATE(42,4);
	printf("◆");
	Sleep(200);
	LOCATE(27,5);
	printf("◆");
	Sleep(200);
	LOCATE(35,6);
	printf("◆");
	Sleep(200);
	LOCATE(50,7);
	printf("◆");
	Sleep(200);
	LOCATE(37,8);
	printf("◆");

}

/*******************************************************************************
 上昇エフェクト関数
*******************************************************************************/
void Joshoffect( void )
{
	COLOR(H_CYAN);
	LOCATE(26,15);
	printf("↑　↑　↑　↑　↑　↑　↑　↑");
	
	LOCATE(26,16);
	printf("↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑");

}

/*******************************************************************************
 カーソル移動関数
*******************************************************************************/
int Cursor( void )
{
	// 変数宣言
	int nPosition = ONE;
	int nMytern   = ZERO;
	int nSelect   = ZERO;

	// コマンドの選択
	while(1)
	{
		KEYCLEAR();							// キーボードを初期化する
		
		WAIT(100);							// インターバル 0.1秒
		INKEY(nSelect);						// 何かキーが押されていたら変数に値を入力する

		if(nSelect == 0x77)					// W アスキーコードの入力後
		{
			if(nPosition == ONE)			// カーソルが一番上にある時に W を押した場合
			{
				BACKCOLOR(BLACK);
				LOCATE(5, 19);
				printf("　");
				BACKCOLOR(BLACK);
				LOCATE(5, 20);
				printf("　");
				COLOR(WHITE, BLACK);
				LOCATE(5, 21);
				printf("→");

				nPosition = 3;
			}
			else if(nPosition == 2)			// カーソルが真ん中にある時に W を押した場合
			{
				COLOR(WHITE, BLACK);
				LOCATE(5, 19);
				printf("→");
				BACKCOLOR(BLACK);
				LOCATE(5, 20);
				printf("　");
				BACKCOLOR(BLACK);
				LOCATE(5, 21);
				printf("　");

				nPosition = ONE;
			}
			else if(nPosition == 3)			// カーソルが一番下にある時に W を押した場合
			{
				BACKCOLOR(BLACK);
				LOCATE(5, 19);
				printf("　");
				COLOR(WHITE, BLACK);
				LOCATE(5, 20);
				printf("→");
				BACKCOLOR(BLACK);
				LOCATE(5, 21);
				printf("　");

				nPosition = 2;
			}//if.fin
		}//if.fin
		if(nSelect == 0x73)					// S アスキーコードの入力後
		{
			if(nPosition == ONE)			// カーソルが一番上にある時に S を押した場合
			{
				BACKCOLOR(BLACK);
				LOCATE(5, 19);
				printf("　");
				COLOR(WHITE, BLACK);
				LOCATE(5, 20);
				printf("→");
				BACKCOLOR(BLACK);
				LOCATE(5, 21);
				printf("　");

				nPosition = 2;
			}
			else if(nPosition == 2)			// カーソルが真ん中にある時に S を押した場合
			{
				BACKCOLOR(BLACK);
				LOCATE(5, 19);
				printf("　");
				BACKCOLOR(BLACK);
				LOCATE(5, 20);
				printf("　");
				COLOR(WHITE, BLACK);
				LOCATE(5, 21);
				printf("→");

				nPosition = 3;
			}
			else if(nPosition == 3)			// カーソルが一番下にある時に S を押した場合
			{
				COLOR(WHITE, BLACK);
				LOCATE(5, 19);
				printf("→");
				BACKCOLOR(BLACK);
				LOCATE(5, 20);
				printf("　");
				BACKCOLOR(BLACK);
				LOCATE(5, 21);
				printf("　");
				
				nPosition = ONE;
			}//if.fin
		}//if.fin

		if(nSelect == 0xd) break;

	}//while.fin

	// 値の代入
	if(nPosition == ONE)					// カーソルの位置が一番上の時
	{
		nMytern = 0x61;
	}
	else if(nPosition == 2)					// カーソルの位置が真ん中上の時
	{
		nMytern = 0x73;
	}
	else if(nPosition == 3)					// カーソルの位置が一番下の時
	{
		nMytern = 0x64;
	}//if.fin

	// 値を返す
	return nMytern;
}

/*******************************************************************************
 スキルカーソル移動関数
*******************************************************************************/
int SkillCursor( void )
{
	// 変数宣言
	int nPosition = ONE;
	int nMytern   = ZERO;
	int nSelect   = ZERO;

	// コマンドの選択
	while(1)
	{
		KEYCLEAR();							// キーボードを初期化する

		WAIT(100);							// インターバル 0.1秒
		INKEY(nSelect);						// 何かキーが押されていたら変数に値を入力する

		if(nSelect == 0x77)					// W アスキーコードの入力後
		{
			if(nPosition == ONE)			// カーソルが一番上にある時に W を押した場合
			{
				BACKCOLOR(BLACK);
				LOCATE(17, 19);
				printf("　");
				BACKCOLOR(BLACK);
				LOCATE(17, 20);
				printf("　");
				BACKCOLOR(BLACK);
				LOCATE(17, 21);
				printf("　");
				COLOR(WHITE, BLACK);
				LOCATE(17, 22);
				printf("→");

				nPosition = 4;
			}
			else if(nPosition == 2)			// カーソルが真ん中上にある時に W を押した場合
			{
				COLOR(WHITE, BLACK);
				LOCATE(17, 19);
				printf("→");
				BACKCOLOR(BLACK);
				LOCATE(17, 20);
				printf("　");
				BACKCOLOR(BLACK);
				LOCATE(17, 21);
				printf("　");
				BACKCOLOR(BLACK);
				LOCATE(17, 22);
				printf("　");

				nPosition = ONE;
			}
			else if(nPosition == 3)			// カーソルが真ん中下にある時に W を押した場合
			{
				BACKCOLOR(BLACK);
				LOCATE(17, 19);
				printf("　");
				COLOR(WHITE, BLACK);
				LOCATE(17, 20);
				printf("→");
				BACKCOLOR(BLACK);
				LOCATE(17, 21);
				printf("　");
				BACKCOLOR(BLACK);
				LOCATE(17, 22);
				printf("　");

				nPosition = 2;
			}
			else if(nPosition == 4)			// カーソルが一番下にある時に W を押した場合
			{
				BACKCOLOR(BLACK);
				LOCATE(17, 19);
				printf("　");
				BACKCOLOR(BLACK);
				LOCATE(17, 20);
				printf("　");
				COLOR(WHITE, BLACK);
				LOCATE(17, 21);
				printf("→");
				BACKCOLOR(BLACK);
				LOCATE(17, 22);
				printf("　");

				nPosition = 3;
			}//if.fin
		}//if.fin
		if(nSelect == 0x73)					// S アスキーコードの入力後
		{
			if(nPosition == ONE)			// カーソルが一番上にある時に S を押した場合
			{
				BACKCOLOR(BLACK);
				LOCATE(17, 19);
				printf("　");
				COLOR(WHITE, BLACK);
				LOCATE(17, 20);
				printf("→");
				BACKCOLOR(BLACK);
				LOCATE(17, 21);
				printf("　");
				BACKCOLOR(BLACK);
				LOCATE(17, 22);
				printf("　");

				nPosition = 2;
			}
			else if(nPosition == 2)			// カーソルが真ん中上にある時に S を押した場合
			{
				BACKCOLOR(BLACK);
				LOCATE(17, 19);
				printf("　");
				BACKCOLOR(BLACK);
				LOCATE(17, 20);
				printf("　");
				COLOR(WHITE, BLACK);
				LOCATE(17, 21);
				printf("→");
				BACKCOLOR(BLACK);
				LOCATE(17, 22);
				printf("　");

				nPosition = 3;
			}
			else if(nPosition == 3)			// カーソルが真ん中下にある時に S を押した場合
			{
				BACKCOLOR(BLACK);
				LOCATE(17, 19);
				printf("　");
				BACKCOLOR(BLACK);
				LOCATE(17, 20);
				printf("　");
				BACKCOLOR(BLACK);
				LOCATE(17, 21);
				printf("　");
				COLOR(WHITE, BLACK);
				LOCATE(17, 22);
				printf("→");

				nPosition = 4;
			}
			else if(nPosition == 4)			// カーソルが一番下にある時に S を押した場合
			{
				COLOR(WHITE, BLACK);
				LOCATE(17, 19);
				printf("→");
				BACKCOLOR(BLACK);
				LOCATE(17, 20);
				printf("　");
				BACKCOLOR(BLACK);
				LOCATE(17, 21);
				printf("　");
				BACKCOLOR(BLACK);
				LOCATE(17, 22);
				printf("　");

				nPosition = ONE;
			}//if.fin
		}//if.fin

		if(nSelect == 0xd)  break;
		if(nSelect == 0x62) break;

	}//while.fin

	// 値の代入
	if(nPosition == ONE)					// カーソルの位置が一番上の時
	{
		nMytern = 0x68;
	}
	else if(nPosition == 2)					// カーソルの位置が真ん中上の時
	{
		nMytern = 0x6a;
	}
	else if(nPosition == 3)					// カーソルの位置が真ん中下の時
	{
		nMytern = 0x6b;
	}
	else if(nPosition == 4)					// カーソルの位置が一番下の時
	{
		nMytern = 0x6c;
	}//if.fin

	if(nSelect == 0x62)						// Bが押された場合
	{
		ComentReset();

		LOCATE(18,20);
		COLOR(WHITE,BLACK);
		printf("コマンドを入力してください...");
		LOCATE(18,21);
		printf("〔Ｗ：↑〕　〔Ｓ：↓〕");

		LOCATE(5, 19);
		printf("→");
		LOCATE(5, 20);
		printf("　");

		nMytern = Cursor();
	}//if.fin

	// 値を返す
	return nMytern;
}

