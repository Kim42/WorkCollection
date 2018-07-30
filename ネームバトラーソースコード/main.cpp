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
#define ZERO                  (0)		// ぜーろー
#define ONE                   (1)		// ワン！
#define HANDRET               (100)		// ハンドレット
#define MAX_MOJI              (8)		// 最大文字数
#define MIN_MOJI              (3)		// 最小文字数
#define NUM_STATUS_A          (0.2)		// ステイタス変化(0.2)
#define NUM_STATUS_B          (0.3)		// ステイタス変化(0.3)
#define NUM_STATUS_C          (0.5)		// ステイタス変化(0.5)
#define NUM_STATUS_D          (0.7)		// ステイタス変化(0.7)

// ベースステイタス定義
#define BASE_LIFE             (600)		// ベース体力値
#define BASE_MAGIC            (30)		// ベース魔力値
#define BASE_ATTACK           (90)		// ベース攻撃力
#define BASE_DEFENSE          (30)		// ベース守備力
#define BASE_AVOIDANCE        (1)		// ベース回避値

// ドラキーの初期位置
#define VERTICAL_DORAKI       (3)		// 縦軸
#define HORIZONTAL_DORAKI     (23)		// 横軸

// スライムコメント欄
#define NUM_UEKARA            (19)		// 縦軸
#define NUM_YOKOKARA          (17)		// 横軸

/*******************************************************************************
* 構造体定義
*******************************************************************************/
typedef struct
{
	char  aName[8];					// 名前
	int  nLife;						// 体力値
	int  nMagic;					// 魔力値
	int  nAttack;					// 攻撃値
	int  nDefense;					// 守備値
	int  nAvoidance;				// 回避値

}PLAYER;								// 変数型 プレイヤー

typedef struct
{
	int  nLife;							// 体力値
	int  nMagic;						// 魔力値
	int  nAttack;						// 攻撃値
	int  nDefense;						// 守備値
	int  nAvoidance;					// 回避値

}INITIAL;								// プレイヤーの初期値格納

typedef struct
{
	char aName[8];						// 名前
	int  nLife;							// 体力値
	int  nMagic;						// 魔力値
	int  nAttack;						// 攻撃値
	int  nDefense;						// 守備値
	int  nAvoidance;					// 回避値

}ENEMY;								// 変数型 敵

/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
int  title( void );												// タイトル関数
void Soulrink(void);											// ソウルリンクタイトル関数
void Soulrink2(void);											// ソウルリンクタイトル2関数

int  CompetitionInput( PLAYER *pPlayer, ENEMY *pEnemy);			// Competition用データ入力関数
int  Output( PLAYER *pPlayer, INITIAL *pInitial, ENEMY *pEnemy);	// データ出力関数

int Cursor( void );												// カーソル移動関数
int SkillCursor( void );										// スキルカーソル移動関数
void Enter( void );												// プリーズエンター関数

// スライムアニメーション //
void Suraim( void );											// スライム関数
void Suraim2( void );											// スライム2関数
void SuraimMove( void );										// 動くスライム関数

void MetalSuraim( void );										// メタルスライム関数
void MetalSuraim2( void );										// メタルスライム2関数
void MetalSuraimMove( void );									// 動くメタルスライム関数

void ButiSuraim( void );										// ぶちスライム関数
void ButiSuraim2( void );										// ぶちスライム2関数
void ButiSuraimMove( void );									// 動くぶちスライム関数

void SuraimDark( void );										// スライムダーク関数
void SuraimDark2( void );										// スライムダーク2関数
void SuraimDarkMove( void );									// 動くスライムダーク関数

int SuraimRink( int nWarpiru );									// スライムリンク関数
int SuraimMoveStatus     ( PLAYER *pPlayer, INITIAL *pInitial, ENEMY *pEnemy);	// 動くスライム + Status関数
int MetalSuraimMoveStatus( PLAYER *pPlayer, INITIAL *pInitial, ENEMY *pEnemy);	// 動くメタルスライム + Status関数
int ButiSuraimMoveStatus ( PLAYER *pPlayer, INITIAL *pInitial, ENEMY *pEnemy);	// 動くぶちスライム + Status関数

// ドラキーアニメーション //
void Doraki( void );											// ドラキー関数
void Doraki2( void );											// ドラキー2関数
void DorakiMa( void );											// ドラキーマ関数
void DorakiMa2( void );											// ドラキーマ2関数
void TahoDoraki( void );										// タホドラキー関数
void TahoDoraki2( void );										// タホドラキー2関数

// アート //
void StatusFrame( int nColor );									// ステイタス枠関数
void Mario( void );												// ドットマリオ関数

// バトル専用 //
void BattleFrame(  int nFreamCloor, int nFreamBackCloor );		// バトルフレーム関数
void Player     ( PLAYER *pPlayer, ENEMY *pEnemy, int nAction, int nMytern );						// プレイヤーの行動
void Enemy      ( PLAYER *pPlayer, ENEMY *pEnemy, int nAction, int nMytern, int nDorakiIllusion);	// エネミーの行動
void ComentReset( void );										// コメント欄リセット関数
void Status(PLAYER *pPlayer);									// ステイタス表示関数
void Name(ENEMY *pEnemy);										// 名前のみの表示関数
int  Order( PLAYER *pPlayer, ENEMY *pEnemy );					// 順番決め関数
int  FrameColor( PLAYER *pPlayer);								// フレームカラー
int  Judge( PLAYER *pPlayer, ENEMY *pEnemy);					// 勝敗判定関数
int  DorakiIllusion( ENEMY *pEnemy );							// ドラキー変化関数
void Ending(PLAYER *pPlayer, ENEMY *pEnemy, int nJudge, int nWarpiru, int nTurnCount);		// エンディング関数

// バトルエフェクト //
void Koromaku( void );											// 黒幕関数
void BlackNormalEffect( void );									// ブラックエフェクト関数
void WhiteNormalEffect( void );									// ホワイトエフェクト関数
void BarunDiveEffect( void );									// バルンダイブエフェクト関数
void SuraDragunEffect( void );									// スラドラグーンエフェクト関数
void BrushEffect( void );										// ブラッシュエフェクト関数
void AnkouDanEffect( void );									// 暗光弾エフェクト関数
void MetalStarEffect( void );									// メタルスターエフェクト関数
void GurabiDonEffect( void );									// グラビドンエフェクト関数
void Joshoffect( void );										// 上昇エフェクト関数
void KifukuEffect( void );										// 回復エフェクト関数

// モンスターの行動 //
int  Akira  ( PLAYER *pPlayer );								// あきーらの行動関数
int  Doni   ( PLAYER *pPlayer );								// ドン・イの行動関数
int  Adabuti( PLAYER *pPlayer );								// アダぶちの行動関数
int  BattleDoraki( ENEMY *pEnemy);								// ドラキーの行動関数
int  BattleDorakiMa( void );									// ドラキーマの行動関数
int  BattleTahoDoraki( void );									// タホドラキーの行動関数

// 最大値、最小値の乱数の生成 //
int  GetRandom(int nMin,int nMax);								//ランダムな整数の最大値、最小値の変数

// 次ページ前にアニメーションワープ //
void NormalWarp( int nWarpiru );								// 通常時ワープ

// 説明
void SoulRinkDescription( int nWarpiru );						// ソウルリンクの説明関数
void Manual( int nWarpiru );									// 全体説明関数

/*******************************************************************************
* グローバル変数
*******************************************************************************/

/*******************************************************************************
 関数名:	int main( void )
 引数:		void
 戻り値:	正常終了: int型の 0
 説明:		
*******************************************************************************/
int main( void )
{
	//// プログラム開始 変数宣言 ////
	PLAYER  aPlayer[ONE];										// プレイヤーの変数
	INITIAL aInitial[ONE];										// 初期値格納の変数
	ENEMY   aEnemy[ONE];										// エネミーの変数
	int nkey = ZERO;											// エンターループに使用
	int nSuraimSelect = ZERO;									// バトル前のスライムの識別
	int nSelect = ZERO;											// モードの選択
	int nVertical = 9;											// 縦軸
	int nHorizontal = 27;										// 横軸
	int nFreamCloor = WHITE;									// バトル用フレームの着色
	int nFreamBackCloor = BLACK;								// バトル用フレームの背景着色
	int nMytern = ZERO;											// 自分の行動判定に使用
	int nAction = ZERO;											// 行動判定に使用
	int nResult = ZERO;											// ダメージ格納
	int nDamage  = ZERO;										// エネミーのダメージ格納
	int nOrder = ZERO;											// 順番決め
	int nJudge = ZERO;											// 勝敗判定
	int nDorakiIllusion = ZERO;									// ドラキー変化
	int nColor = ZERO;											// フレームカラー判定
	int nTheme = ZERO;											// 曲決め
	int nWarpiru;												// ワープ画面をなくしますか？
	int nTurnCount = ZERO;										// 経過ターンのカウント

	// MP3 用格納変数宣言 //
	int nMP3Handle = ZERO;
	
	LOCATE(25,10);
	printf("所々ロード画面的のがありますがなくしますか？");
	LOCATE(26,11);
	printf("１：なくす");
	LOCATE(26,12);
	printf("２：のこしておく");
	LOCATE(26,13);
	printf("→");
	LOCATE(28,13);
	scanf("%d", &nWarpiru);

	CUROFF();													// カーソルを消す

	CLS(WHITE,BLACK);											// 画面を文字＞白、背景＞黒にする。

	// [ EXIT ]が押されるまでエンドレス！！！！！！！
	do
	{
		// ゲームのテーマ曲 //
		nMP3Handle = OPENMP3("GameTheme.mp3");					// オープン & 初期化
		PLAYMP3(nMP3Handle, 1);									// 繰り返し再生

		//// ゲームスタート ////
		nSelect = title();										// タイトル
		NormalWarp( nWarpiru );									// 通常時ワープ

		// タイトルよりモードの選択 //
		switch(nSelect)
		{
			case 0x61:				// 1P Competitionモード
				
				CompetitionInput( &aPlayer[ZERO], &aEnemy[ZERO]);			// 名前からステイタスへ変換

				NormalWarp( nWarpiru );										// 通常時ワープ

				Output( &aPlayer[ZERO], &aInitial[ZERO], &aEnemy[ZERO]);	// ステイタスの表示

				NormalWarp( nWarpiru );										// 通常時ワープ

				nSuraimSelect = SuraimRink(nWarpiru );						//スライムリンク
				
				// スライムの選択(あきーら/ドン・イ/アダぶち) // 決めるまでループ
				while(1)
				{
					if(nSuraimSelect == 1)
					{
						// あきーらを選ぶか変更前のステイタスで始めるか
						KEYCLEAR();											// 念のためキーボードを初期化する
						system("cls");										// 画面のクリア
						INKEY(nSuraimSelect);								// 何かキーが押されていたら変数に値を入力する
						nSuraimSelect = SuraimMoveStatus( &aPlayer[ZERO], &aInitial[ZERO], &aEnemy[ZERO]);

						if(nSuraimSelect == 0x61)							// [ a ]を選択した場合
						{
							nSuraimSelect = 3;								// ドン・イのページへ
							continue;
						}
						else if(nSuraimSelect == 0x64)						// [ d ]を選択した場合
						{
							nSuraimSelect = 2;								// アダぶちのページへ
							continue;
						}
						else if(nSuraimSelect == 0x6f || nSuraimSelect == 0x78)
						{
							nSuraimSelect = 1;								// あきーらで始める
							break;
						}//if.fin
					}
					else if(nSuraimSelect == 2)
					{
						// アダぶちを選ぶか変更前のステイタスで始めるか
						KEYCLEAR();											// 念のためキーボードを初期化する
						system("cls");										// 画面のクリア
						nSuraimSelect = ButiSuraimMoveStatus( &aPlayer[ZERO], &aInitial[ZERO], &aEnemy[ZERO]);

						if(nSuraimSelect == 0x61)							// [ a ]を選択した場合
						{
							nSuraimSelect = 1;								// あきーらのページへ
							continue;
						}
						else if(nSuraimSelect == 0x64)						// [ d ]を選択した場合
						{
							nSuraimSelect = 3;								// ドン・イのページへ
							continue;
						}
						else if(nSuraimSelect == 0x6f || nSuraimSelect == 0x78)
						{
							nSuraimSelect = 2;								// アダぶちで始める
							break;
						}//if.fin
					}
					else if(nSuraimSelect == 3)
					{
						// ドン・イを選ぶか変更前のステイタスで始めるか
						KEYCLEAR();											// 念のためキーボードを初期化する
						system("cls");										// 画面のクリア
						nSuraimSelect = MetalSuraimMoveStatus( &aPlayer[ZERO], &aInitial[ZERO], &aEnemy[ZERO]);

						if(nSuraimSelect == 0x61)							// [ a ]を選択した場合
						{
							nSuraimSelect = 2;								// アダぶちのページへ
							continue;
						}
						else if(nSuraimSelect == 0x64)						// [ d ]を選択した場合
						{
							nSuraimSelect = 1;								// あきーらのページへ
							continue;
						}
						else if(nSuraimSelect == 0x6f || nSuraimSelect == 0x78)
						{
							nSuraimSelect = 3;								// ドン・イで始める
							break;
						}//if.fin
					}//if.fin
				}// while.fin												// スライム決めループ

				NormalWarp( nWarpiru );										// ワープ

				CLOSEMP3(nMP3Handle);										// 停止 & クローズ

				//乱数列を初期化
				srand(( unsigned ) time( NULL ));
				nTheme = rand() %3;							// 確率1/4

				// ランダム決定するＢＧＭ
				if(nTheme == ZERO)
				{
					// ＢＧＭ再生
					nMP3Handle = OPENMP3("Fighting Spirit.mp3");			// オープン & 初期化
					PLAYMP3(nMP3Handle,1);									// 繰り返し再生
				}
				else if(nTheme == 1)
				{
					// ＢＧＭ再生
					nMP3Handle = OPENMP3("Dragon_Ball_Z.mp3");				// オープン & 初期化
					PLAYMP3(nMP3Handle,1);									// 繰り返し再生
				}
				else if(nTheme == 2)
				{
					// ＢＧＭ再生
					nMP3Handle = OPENMP3("DQ7.mp3");						// オープン & 初期化
					PLAYMP3(nMP3Handle,1);									// 繰り返し再生
				}
				
				// ここからバトルすたーーーーとーーー！！！ //
				BattleFrame( nFreamCloor, nFreamBackCloor );				// バトル用フレームの表示
				Status(&aPlayer[ZERO]);										// ステイタスの表示

				Doraki();													// ドラキーの表示
				Name(&aEnemy[ZERO]);										// エネミーネーム

				Enter();													// プリーズエンター

				nTurnCount = ZERO;											// ターンカウント数の初期化

				// バトル すたーーーーとーーー！！！ // 毎ターン確率で、回避率の回復 //
				while(1)
				{
					// ターンカウント
					nTurnCount++;

					COLOR(WHITE, BLACK);
					LOCATE(3,17);
					printf("〔 %d ターン目〕", nTurnCount);

					// 条件によってドラキーの変化
					nDorakiIllusion = DorakiIllusion( &aEnemy[ZERO] );		// ドラキーの変化

					if(nDorakiIllusion == 1)								// 体力が 500 以上の場合
					{
						Doraki();											// ドラキーに変化
						nAction = BattleDoraki(&aEnemy[ZERO]);				// ドラキーの行動
					}
					else if(nDorakiIllusion == 2)							// 体力が 499 以上の場合
					{
						TahoDoraki();										// タホドラキーに変化
						nAction = BattleTahoDoraki();						// タホドラキーの行動
					}
					else if(nDorakiIllusion == 3)							// 体力が 300 未満の場合
					{
						DorakiMa();											// ドラキーマに変化
						nAction = BattleDorakiMa();							// ドラキーマの行動
					}//if.fin

					LOCATE(18,20);
					COLOR(WHITE,BLACK);
					printf("コマンドを入力してください...");
					LOCATE(18,21);
					printf("〔Ｗ：↑〕　〔Ｓ：↓〕");

					// 使用するスライムのスキル使用
					if(nSuraimSelect == 1)									// あきーら
					{
						nMytern = Akira(&aPlayer[ZERO]);					// 関数で選択した値の代入

					}
					else if(nSuraimSelect == 3)								// ドン・イ
					{
						nMytern = Doni(&aPlayer[ZERO]);						// 関数で選択した値の代入
					}
					else if(nSuraimSelect == 2)								// アダぶち
					{
						nMytern = Adabuti(&aPlayer[ZERO]);					// 関数で選択した値の代入
					}//if.fin

					nOrder = Order( &aPlayer[ZERO], &aEnemy[ZERO] );		// 順番決め

					Sleep(700);												// インターバル0.7秒

					// 回避値の高い方から先制 //
					if(nOrder == ONE)										// プレイヤーの先制 //
					{
						LOCATE(17,19);
						printf("プレイヤーの先制");

						Player( &aPlayer[ZERO], &aEnemy[ZERO], nAction, nMytern );// プレイヤーの行動
						Status(&aPlayer[ZERO]);								// 画面の更新
						BlackNormalEffect();								// ブラックエフェクト

						// 勝敗判定
						nJudge = Judge( &aPlayer[ZERO], &aEnemy[ZERO]);

						if(nJudge == ONE || nJudge == ZERO)
						{
							CLOSEMP3(nMP3Handle);								// 停止 & クローズ
							// ループ解除
							break;
						}//if.fin

						Enemy( &aPlayer[ZERO], &aEnemy[ZERO] , nAction, nMytern, nDorakiIllusion);// エネミーの行動
						Status(&aPlayer[ZERO]);								// 画面の更新
						
					}
					else if(nOrder == ZERO)									// エネミーの先制 //
					{
						LOCATE(17,19);
						printf("エネミーの先制");

						Enemy( &aPlayer[ZERO], &aEnemy[ZERO] , nAction, nMytern, nDorakiIllusion);// エネミーの行動
						Status(&aPlayer[ZERO]);								// 画面の更新

						// 勝敗判定
						nJudge = Judge( &aPlayer[ZERO], &aEnemy[ZERO]);

						if(nJudge == ONE || nJudge == ZERO)
						{
							CLOSEMP3(nMP3Handle);								// 停止 & クローズ
							// ループ解除
							break;
						}//if.fin

						Player( &aPlayer[ZERO], &aEnemy[ZERO] , nAction, nMytern );// プレイヤーの行動
						Status(&aPlayer[ZERO]);								// 画面の更新
						BlackNormalEffect();								// ブラックエフェクト

					}//if.fin

					// 勝敗判定 //////////////////////////////////////////////
					nColor = FrameColor( &aPlayer[ZERO]);					// 条件下で着色

					if(nColor == ZERO)										// プレイヤーの体力が400以上の場合
					{
						nFreamCloor = WHITE;								// バトル用フレームの着色：白
					}
					else if(nColor == 1)									// プレイヤーの体力が399以下の場合
					{
						nFreamCloor = YELLOW;								// バトル用フレームの着色：黄色
					}
					else if(nColor == 2)									// プレイヤーの体力が200以下の場合
					{
						nFreamCloor = H_RED;								// バトル用フレームの着色：赤
					}//if.fin

					nJudge = Judge( &aPlayer[ZERO], &aEnemy[ZERO]);			// 勝敗判定

					if(nJudge == ONE || nJudge == ZERO)
					{
						CLOSEMP3(nMP3Handle);								// 停止 & クローズ
						// ループ解除
						break;
					}//if.fin

				}//while.fin												// バトルループ

				// エンディング //
				Ending(&aPlayer[ZERO], &aEnemy[ZERO], nJudge, nWarpiru, nTurnCount);

				break;

			case 0x73:						// 全体説明

				Manual(nWarpiru);			// プレーするにあたっての簡潔な説明
				break;

			case 0x64:						// 終了

				CLS(WHITE,BLACK);

				COLOR(LIME);
				LOCATE(33,12);
				printf("  See You Again !");

				while(1)
				{
					COLOR(WHITE,LIME);
					LOCATE(33,14);
					printf("～ Please Enter ～");
					 WAIT(300);						// 0.3secの時間待ち 
					INKEY(nkey);					// 何かキーが押されていたら変数に値を入力する 
					if (nkey == 0xd) break;			// 何か押されたら終了する 

					COLOR(LIME,H_CYAN);
					LOCATE(33,14);
					printf("～ Please Enter ～");
					WAIT(300);						// 0.3secの時間待ち 
					INKEY(nkey);					// 何かキーが押されていたら変数に値を入力する 
					if (nkey == 0xd) break;			// 何か押されたら終了する 
				}
				break;

		}//switch.fin

		CLOSEMP3(nMP3Handle);						// 停止 & クローズ

	}while(nSelect != 0x64);		// [ d ]が押されるまでエンドレス！！！！！！！

	// プログラムエンド ゲームセット！！！ //
}

/***********************************************************************************************************************************************************
 以下、制作完了関数
***********************************************************************************************************************************************************/

/*******************************************************************************
 あきーら（バトル）関数
*******************************************************************************/
int Akira( PLAYER *pPlayer )
{
	// 変数宣言
	int nMytern = ZERO;
	int nVer = NUM_UEKARA;
	int nHor = NUM_YOKOKARA;

	// コマンドの選択( a s d f が押されたら出る！)
	while(1)
	{
		nMytern = Cursor();						// カーソル移動でコマンド選択後、値の代入

		if(nMytern == 0x61)
		{
			nMytern = 1;						// 返す値への代入
			break;
		}
		else if(nMytern == 0x64)
		{
			if(pPlayer -> nAvoidance == ZERO)	// 回避値がない場合
			{
				LOCATE(18, 20);
				printf(" 回避できる余力がないようだ...");
				Enter();						// エンタープリーズ
				continue;
			}//if.fin

			nMytern = 2;						// 返す値への代入
			break;
		}
		else if(nMytern == 0x73)
		{
			// コマンドの選択( h j k l が押されたら出る！)
			while(1)
			{
				// ループ時にとどめるため
				nVer = NUM_UEKARA;
				nHor = NUM_YOKOKARA;

				// スキルの表示
				COLOR(WHITE,BLACK);
				LOCATE(nHor, nVer++);
				printf("→：チュール       魔－5      体力を回復させる");
				LOCATE(nHor, nVer++);
				printf("　：ロブマ         魔－3      相手の魔力をうばう");
				LOCATE(nHor, nVer++);
				printf("　：バルンダイブ   魔－15     大ダメージを与える");
				LOCATE(nHor, nVer++);
				printf("　：スラドラグーン 魔－30     攻撃後、回避値UP");

				nMytern = SkillCursor();		// スキル用カーソル移動

				// 値の返還
				if(nMytern == 0x68)				// h の場合
				{
					if(pPlayer -> nMagic < 5)			// 魔力値がない場合
					{
						ComentReset();					// コメントリセット
						LOCATE(18, 20);
						printf(" 魔力がたりないようだ...");
						Enter();						// エンタープリーズ
						continue;
					}//if.fin

					nMytern = 3;						// 返す値への代入
					break;
				}
				else if(nMytern == 0x6a)				// j の場合
				{
					if(pPlayer -> nMagic < 3)			// 魔力値がない場合
					{
						ComentReset();					// コメントリセット
						LOCATE(18, 20);
						printf(" 魔力がたりないようだ...");
						Enter();						// エンタープリーズ
						continue;
					}//if.fin

					nMytern = 4;				// 返す値への代入
					break;
				}
				else if(nMytern == 0x6b)		// k の場合
				{
					if(pPlayer -> nMagic < 15)		// 魔力値がない場合
					{
						ComentReset();					// コメントリセット
						LOCATE(18, 20);
						printf(" 魔力がたりないようだ...");
						Enter();						// エンタープリーズ
						continue;
					}//if.fin

					nMytern = 5;				// 返す値への代入
					break;
				}
				else if(nMytern == 0x6c)				// l の場合
				{
					if(pPlayer -> nMagic < 30)			// 魔力値がない場合
					{
						ComentReset();					// コメントリセット
						LOCATE(18, 20);
						printf(" 魔力がたりないようだ...");
						Enter();						// エンタープリーズ
						continue;
					}//if.fin

					nMytern = 6;						// 返す値への代入
					break;
				}
				else if(nMytern == 0x61)
				{
					nMytern = 1;						// 返す値への代入
					break;
				}
				else if(nMytern == 0x64)
				{
					if(pPlayer -> nAvoidance == ZERO)	// 回避値がない場合
					{
						ComentReset();					// コメントリセット
						LOCATE(18, 20);
						printf(" 回避できる余力がないようだ...");
						Enter();						// エンタープリーズ
						continue;
					}//if.fin

					nMytern = 2;						// 返す値への代入
					break;
				}//if.fin

				Sleep(200);								// インターバル0.2秒

			}//while.fin

			break;

		}//if.fin
	}//while.fin

	ComentReset();								// コメント欄のリセット

	// 値を返して終了 //
	return nMytern;
}

/*******************************************************************************
 ドン・イ（バトル）関数
*******************************************************************************/
int Doni( PLAYER *pPlayer )
{
	// 変数宣言
	int nMytern = ZERO;
	int nVer = NUM_UEKARA;
	int nHor = NUM_YOKOKARA;

	// コマンドの選択( a s d f が押されたら出る！)
	while(1)
	{
		nMytern = Cursor();						// カーソル移動でコマンド選択後、値の代入

		if(nMytern == 0x61)
		{
			nMytern = 1;						// 返す値への代入
			break;
		}
		else if(nMytern == 0x64)
		{
			if(pPlayer -> nAvoidance == ZERO)	// 回避値がない場合
			{
				LOCATE(18, 20);
				printf(" 回避できる余力がないようだ...");
				Enter();						// エンタープリーズ
				continue;
			}//if.fin

			nMytern = 2;						// 返す値への代入
			break;
		}
		else if(nMytern == 0x73)
		{
			// コマンドの選択( h j k l が押されたら出る！)
			while(1)
			{
				// ループ時にとどめるため
				nVer = NUM_UEKARA;
				nHor = NUM_YOKOKARA;

				// スキルの表示
				COLOR(WHITE,BLACK);
				LOCATE(nHor, nVer++);
				printf("→：チュール       魔－5      体力を回復させる");
				LOCATE(nHor, nVer++);
				printf("  ：ロブマ         魔－3      相手の魔力をうばう");
				LOCATE(nHor, nVer++);
				printf("  ：メタルスター   魔－15     大ダメージを与える");
				LOCATE(nHor, nVer++);
				printf("  ：グラビドン     魔－30     攻撃後、体力回復");

				nMytern = SkillCursor();				// スキル用カーソル移動

				// 値の返還
				if(nMytern == 0x68)						// h の場合
				{
					if(pPlayer -> nMagic < 5)			// 魔力値がない場合
					{
						LOCATE(18, 20);
						printf(" 魔力がたりないようだ...");
						Enter();						// エンタープリーズ
						continue;
					}//if.fin

					nMytern = 3;						// 返す値への代入
					break;
				}
				else if(nMytern == 0x6a)				// j の場合
				{
					if(pPlayer -> nMagic < 3)			// 魔力値がない場合
					{
						ComentReset();					// コメントリセット
						LOCATE(18, 20);
						printf(" 魔力がたりないようだ...");
						Enter();						// エンタープリーズ
						continue;
					}//if.fin

					nMytern = 4;						// 返す値への代入
					break;
				}
				else if(nMytern == 0x6b)				// k の場合
				{
					if(pPlayer -> nMagic < 15)			// 魔力値がない場合
					{
						ComentReset();					// コメントリセット
						LOCATE(18, 20);
						printf(" 魔力がたりないようだ...");
						Enter();						// エンタープリーズ
						continue;
					}//if.fin

					nMytern = 7;						// 返す値への代入
					break;
				}
				else if(nMytern == 0x6c)				// l の場合
				{
					if(pPlayer -> nMagic < 30)			// 魔力値がない場合
					{
						ComentReset();					// コメントリセット
						LOCATE(18, 20);
						printf(" 魔力がたりないようだ...");
						Enter();						// エンタープリーズ
						continue;
					}//if.fin

					nMytern = 8;						// 返す値への代入
					break;
				}
				else if(nMytern == 0x61)
				{
					nMytern = 1;						// 返す値への代入
					break;
				}
				else if(nMytern == 0x64)
				{
					if(pPlayer -> nAvoidance == ZERO)	// 回避値がない場合
					{
						ComentReset();					// コメントリセット
						LOCATE(18, 20);
						printf(" 回避できる余力がないようだ...");
						Enter();						// エンタープリーズ
						continue;
					}//if.fin

					nMytern = 2;						// 返す値への代入
					break;
				}//if.fin

				Sleep(200);								// インターバル0.2秒

			}//while.fin
		}//if.fin

		break;

	}//while.fin

	ComentReset();										// コメント欄のリセット

	return nMytern;
}

/*******************************************************************************
 アダぶち（バトル）関数
*******************************************************************************/
int Adabuti( PLAYER *pPlayer )
{
	// 変数宣言
	int nMytern = ZERO;
	int nVer = NUM_UEKARA;
	int nHor = NUM_YOKOKARA;

	// コマンドの選択( a s d f が押されたら出る！)
	while(1)
	{
		nMytern = Cursor();						// カーソル移動でコマンド選択後、値の代入
		
		if(nMytern == 0x61)
		{
			nMytern = 1;						// 返す値への代入
			break;
		}
		else if(nMytern == 0x64)
		{
			if(pPlayer -> nAvoidance == ZERO)	// 回避値がない場合
			{
				LOCATE(18, 20);
				printf(" 回避できる余力がないようだ...");
				Enter();						// エンタープリーズ
				continue;
			}//if.fin

			nMytern = 2;						// 返す値への代入
			break;
		}
		else if(nMytern == 0x73)
		{
			// コマンドの選択( h j k l が押されたら出る！)
			while(1)
			{
				// ループ時にとどめるため
				nVer = NUM_UEKARA;
				nHor = NUM_YOKOKARA;

				// スキルの表示
				COLOR(WHITE,BLACK);
				LOCATE(nHor, nVer++);
				printf("→：チュール       魔－5      体力を回復させる");
				LOCATE(nHor, nVer++);
				printf("　：ロブマ         魔－3      相手の魔力をうばう");
				LOCATE(nHor, nVer++);
				printf("　：ブラッシュ     魔－15     大ダメージを与える");
				LOCATE(nHor, nVer++);
				printf("　：暗光弾         魔－30     攻撃後、攻守力UP");

				nMytern = SkillCursor();		// スキル用カーソル移動

				// 値の返還
				if(nMytern == 0x68)						// h の場合
				{
					if(pPlayer -> nMagic < 5)			// 魔力値がない場合
					{
						ComentReset();					// コメントリセット
						LOCATE(18, 20);
						printf(" 魔力がたりないようだ...");
						Enter();						// エンタープリーズ
						continue;
					}//if.fin

					nMytern = 3;						// 返す値への代入
					break;
				}
				else if(nMytern == 0x6a)				// j の場合
				{
					if(pPlayer -> nMagic < 3)			// 魔力値がない場合
					{
						ComentReset();					// コメントリセット
						LOCATE(18, 20);
						printf(" 魔力がたりないようだ...");
						Enter();						// エンタープリーズ
						continue;
					}//if.fin

					nMytern = 4;						// 返す値への代入
					break;
				}
				else if(nMytern == 0x6b)				// k の場合
				{
					if(pPlayer -> nMagic < 15)			// 魔力値がない場合
					{
						LOCATE(18, 20);
						printf(" 魔力がたりないようだ...");
						Enter();						// エンタープリーズ
						continue;
					}//if.fin

					nMytern = 9;						// 返す値への代入
					break;
				}
				else if(nMytern == 0x6c)				// l の場合
				{
					if(pPlayer -> nMagic < 30)			// 魔力値がない場合
					{
						ComentReset();					// コメントリセット
						LOCATE(18, 20);
						printf(" 魔力がたりないようだ...");
						Enter();						// エンタープリーズ
						continue;
					}//if.fin

					nMytern = 10;						// 返す値への代入
					break;
				}
				else if(nMytern == 0x61)
				{
					nMytern = 1;						// 返す値への代入
					break;
				}
				else if(nMytern == 0x64)
				{
					if(pPlayer -> nAvoidance == ZERO)	// 回避値がない場合
					{
						ComentReset();					// コメントリセット
						LOCATE(18, 20);
						printf(" 回避できる余力がないようだ...");
						Enter();						// エンタープリーズ
						continue;
					}//if.fin

					nMytern = 2;						// 返す値への代入
					break;
				}//if.fin

				Sleep(200);								// インターバル0.2秒

			}//while.fin
		}//if.fin

		break;

	}//while.fin

	ComentReset();								// コメント欄のリセット

	return nMytern;
}

/*******************************************************************************
 ドラキー（バトル）関数
*******************************************************************************/
int BattleDoraki( ENEMY *pEnemy)
{
	// 変数宣言
	int nRandDoraki;
	int nAction = ZERO;									// 行動判定に使用

	//乱数列を初期化
	srand(( unsigned ) time( NULL ));
	nRandDoraki = rand() %5;							// 確率1/5

	// ドラキーの戦闘パターン //
	if(pEnemy -> nAvoidance != ZERO)					// 回避値が残っている場合
	{
		if(nRandDoraki == 0 || nRandDoraki == 1 || nRandDoraki == 3)
		{
			// 通常攻撃(プレイヤー守備力 － (エネミー攻撃力 + (-10,10))
			// 使用先関数で算出処理
			
			// 返す値 攻撃時１を返す
			nAction = 1;
		}
		else if(nRandDoraki == 2)
		{
			// ひらりと身をかわす(回避値 －１)
			pEnemy -> nAvoidance -= ONE;

			// 返す値 回避時２を返す
			nAction = 2;

		}
		else if(nRandDoraki == 4)
		{
			// 羽を休めている(回避値 ＋１)
			pEnemy -> nAvoidance += ONE;

			// 返す値 羽休め時３を返す
			nAction = 3;

		}//if.fin
	}
	else if(pEnemy -> nAvoidance == ZERO)				// 回避値が残っていない場合
	{
		if(nRandDoraki == 0 || nRandDoraki == 1 || nRandDoraki == 3)
		{
			// 通常攻撃(プレイヤー守備力 － (エネミー攻撃力 + (-10,10))
			// 使用先関数で算出処理

			// 返す値 攻撃時１を返す
			nAction = 1;
		}
		else if(nRandDoraki == 2 || nRandDoraki == 4)
		{
			// 羽を休めている(回避値 ＋１)
			pEnemy -> nAvoidance += ONE;

			// 返す値 羽休め時３を返す
			nAction = 3;

		}//if.fin

	}//if.fin

	// 値を返して終了 //
	return nAction;
}

/*******************************************************************************
 ドラキーマ（バトル）関数
*******************************************************************************/
int BattleDorakiMa( void )
{
	// 変数宣言
	int nRandDorakiMa;
	int nAction = ZERO;									// 行動判定に使用

	//乱数列を初期化
	srand(( unsigned ) time( NULL ));
	nRandDorakiMa = rand() %5;							// 確率1/5

	// ドラキーマの戦闘パターン //
	if(nRandDorakiMa == 0 || nRandDorakiMa == 1 || nRandDorakiMa == 3)
	{
		// 通常攻撃(プレイヤー守備力 － (エネミー攻撃力 + (-10,10))
		// 使用先関数で算出処理

		// 返す値 攻撃時１を返す
		nAction = 1;
	}
	else if(nRandDorakiMa == 2 || nRandDorakiMa == 4)
	{
		// ロブマチューラ(体力＋魔力の同時回復)
		// 使用先関数で算出処理

		// 返す値 回避時４を返す
		nAction = 4;
	}//if.fin

	// 値を返して終了 //
	return nAction;
}

/*******************************************************************************
 タホドラキー（バトル）関数
*******************************************************************************/
int BattleTahoDoraki( void )
{
	// 変数宣言
	int nTahoRandDoraki;
	int nAction = ZERO;									// 行動判定に使用

	//乱数列を初期化
	srand(( unsigned ) time( NULL ));
	nTahoRandDoraki = rand() %7;						// 確率1/7

	// タホドラキーの戦闘パターン //
	if(nTahoRandDoraki == 3)
	{
		// 通常攻撃(プレイヤー守備力 － (エネミー攻撃力 + (-10,10))
		// 使用先関数で算出処理

		// 返す値 攻撃時１を返す
		nAction = 1;
	}
	else if(nTahoRandDoraki == 1)
	{
		// ネロー(遅延効果)
		// 使用先関数で算出処理

		// 返す値 ネロー時５を返す
		nAction = 5;
	}
	else if(nTahoRandDoraki == 2 || nTahoRandDoraki == 6)
	{
		// ヨケンレ(回避値減少効果)
		// 使用先関数で算出処理

		// 返す値 ヨケンレ時６を返す
		nAction = 6;
	}
	else if(nTahoRandDoraki == 0 || nTahoRandDoraki == 4 || nTahoRandDoraki == 5)
	{
		// メラミ(守備力無視ダメージ)
		// 使用先関数で算出処理

		// 返す値 メラミ時７を返す
		nAction = 7;
	}//if.fin

	// 値を返して終了 //
	return nAction;
}

/*******************************************************************************
 プレイヤーの行動関数
*******************************************************************************/
void Player( PLAYER *pPlayer, ENEMY *pEnemy, int nAction, int nMytern )
{
	// 変数宣言
	int nResult = ZERO;								// ダメージ格納
	int nMagicMax = HANDRET;						// 魔力最大値
	int nMP3Handle = ZERO;

	if(pPlayer -> nLife >= 1000)					// 回復で最大値を超えた場合
	{
		pPlayer -> nLife = 999;						// 最大値の代入
	}

	COLOR(WHITE,BLACK);								// 着色

	// プレイヤーの行動 //////////////////////////////////////
	if (nAction != 5)										//タホドラキーの魔法効果
	{
		if(nMytern == 1)									// 通常攻撃
		{
			if(nAction != 2)								// 相手が回避状態でない場合
			{
				nResult = pPlayer -> nAttack - (pEnemy -> nDefense + GetRandom(-10,10));
				pEnemy -> nLife -= nResult;					// ダメージの代入

				// こうげき効果音 //
				nMP3Handle = OPENMP3("Attack.mp3");						// オープン & 初期化

				PLAYMP3(nMP3Handle, 1);									// 繰り返し再生

				WhiteNormalEffect();						// ノーマルエフェクト
				BlackNormalEffect();						// ブラックエフェクト
				WhiteNormalEffect();						// ノーマルエフェクト
				BlackNormalEffect();						// ブラックエフェクト
				WhiteNormalEffect();						// ノーマルエフェクト
				BlackNormalEffect();						// ブラックエフェクト

				CLOSEMP3(nMP3Handle);									// 停止 & クローズ

				LOCATE(18,20);
				printf("《 %s 》のこうげき！", pPlayer -> aName);
				LOCATE(18,21);
				printf("《 %s 》に %d のダメージ！", pEnemy -> aName, nResult);
			}
			else if(nAction == 2)							// 相手が回避状態である場合
			{
				nResult = GetRandom(30,120);
				pPlayer -> nLife -= nResult;

				LOCATE(18,20);
				printf("《 %s 》のこうげき！", pPlayer -> aName);
				LOCATE(18,21);
				printf("《 %s 》のカウンター！", pEnemy -> aName);
				LOCATE(18,22);
				printf("《 %s 》に %d のダメージ", pPlayer -> aName, nResult);
			}//if.fin
		}
		else if(nMytern == 2)								// 回避
		{
			pPlayer -> nAvoidance -= ONE;					// 回避値の消費-1

			LOCATE(18,20);
			printf("《 %s 》はこうげきに身構えている！", pPlayer -> aName);
		}
		else if(nMytern == 3)								// 回復魔法：チュール
		{
			pPlayer -> nMagic -= 5;							// 魔力の消費-5
			nResult += GetRandom(90,120);
			pPlayer -> nLife += nResult;					// 体力の回復

			if(pPlayer -> nLife >= 1000)					// 回復で最大値を超えた場合
			{
				pPlayer -> nLife = 999;						// 最大値の代入
			}

			LOCATE(18,20);
			printf("《 %s 》は回復魔法：チュールを唱えた！", pPlayer -> aName);
			LOCATE(18,21);
			printf("体力が %d かいふく！", nResult);
		}
		else if(nMytern == 4)								// 魔奪魔法：ロブマ
		{
			if(pEnemy  -> nMagic >= 7)						// 魔力がある場合
			{
				pPlayer -> nMagic -= 3;						// 魔力の消費-3
				nResult += GetRandom(7,15);
				pEnemy  -> nMagic -= nResult;				// 魔力の吸収
				pPlayer -> nMagic += nResult;				// 魔力の回復

				if(pPlayer -> nMagic > HANDRET)				// 回復で最大値を超えた場合
				{
					pPlayer -> nMagic = HANDRET;			// 最大値の代入
				}

				LOCATE(18,20);
				printf("《 %s 》は魔奪魔法：ロブマを唱えた！", pPlayer -> aName);
				LOCATE(18,21);
				printf("《 %s 》の魔力を %d うばった！", pEnemy -> aName, nResult);
			}
			else if(pEnemy  -> nMagic <= 6)					// 魔力がない場合
			{
				LOCATE(18,20);
				printf("《 %s 》は魔奪魔法：ロブマを唱えた！", pPlayer -> aName);
				LOCATE(18,21);
				printf("《 %s 》の魔力は残っていなかった！", pEnemy -> aName, nResult);
			}
		}
		else if(nMytern == 5 || nMytern == 7 || nMytern == 9)// 守備力無視攻撃
		{
			nResult = pPlayer -> nAttack + GetRandom(-10,10);
			pEnemy -> nLife -= nResult;						// ダメージの代入

			if(nAction != 2)								// 相手が回避状態でない場合
			{
				pPlayer -> nMagic -= 15;					// 魔力－15
				nResult = pPlayer -> nAttack + GetRandom(-10,10);
				pEnemy -> nLife -= nResult;					// ダメージの代入

				if(nMytern == 5)
				{
					// 効果音の再生
					nMP3Handle = OPENMP3("BarunDive.mp3");					// オープン & 初期化
					PLAYMP3(nMP3Handle);									// 繰り返し再生

					BarunDiveEffect();						// バルンダイブエフェクト

					COLOR(WHITE,BLACK);
					LOCATE(18,20);
					printf("《 %s 》のバルンダイブ！", pPlayer -> aName);
				}
				else if(nMytern == 7)
				{
					// 効果音の再生
					nMP3Handle = OPENMP3("MetalStar.mp3");					// オープン & 初期化
					PLAYMP3(nMP3Handle);									// 繰り返し再生

					MetalStarEffect();						// メタルスターエフェクト

					COLOR(WHITE,BLACK);
					LOCATE(18,20);
					printf("《 %s 》のメタルスター！", pPlayer -> aName);
				}
				else if(nMytern == 9)
				{
					// 効果音の再生
					nMP3Handle = OPENMP3("Brush.mp3");						// オープン & 初期化
					PLAYMP3(nMP3Handle);									// 繰り返し再生

					BrushEffect();							// ブラッシュエフェクト

					COLOR(WHITE,BLACK);
					LOCATE(18,20);
					printf("《 %s 》のブラッシュ！", pPlayer -> aName);
				}//if.fin

				LOCATE(18,21);
				printf("《 %s 》に %d のダメージ！", pEnemy -> aName, nResult);
			}
			else if(nAction == 2)							// 相手が回避状態である場合
			{
				COLOR(WHITE,BLACK);
				LOCATE(18,20);
				printf("《 %s 》のこうげき！", pPlayer -> aName);
				LOCATE(18,21);
				printf("《 %s 》はひらりと身をかわした！", pEnemy -> aName);
			}//if.fin
		}
		else if(nMytern == 6)								// スラドラグーン
		{
			pPlayer -> nMagic -= 30;						// 魔力－30
			nResult = pPlayer -> nAttack + GetRandom(10,40);
			pEnemy -> nLife -= nResult;						// ダメージの代入
			pPlayer -> nAvoidance += 2;						// 回避値の追加
			
			// 効果音の再生
			nMP3Handle = OPENMP3("SuraDragun.mp3");					// オープン & 初期化
			PLAYMP3(nMP3Handle);									// 繰り返し再生

			SuraDragunEffect();								// スラドラグーンエフェクト

			COLOR(WHITE,BLACK);
			LOCATE(18,20);
			printf("《 %s 》のスラドラグーン！！！", pPlayer -> aName);
			LOCATE(18,21);
			printf("《 %s 》に %d のダメージ！", pEnemy -> aName, nResult);
		}
		else if(nMytern == 8)								// グラビドン
		{
			pPlayer -> nMagic -= 30;						// 魔力－30
			nResult = pPlayer -> nAttack + GetRandom(60,70);
			pEnemy -> nLife -= nResult;						// ダメージの代入
			pPlayer -> nLife += GetRandom(50,60);			// 体力の小回復

			// 効果音の再生
			nMP3Handle = OPENMP3("GurabiDon.mp3");					// オープン & 初期化
			PLAYMP3(nMP3Handle);									// 繰り返し再生

			GurabiDonEffect();								// グラビドンエフェクト

			COLOR(WHITE,BLACK);
			LOCATE(18,20);
			printf("《 %s 》のグラビドン！！！", pPlayer -> aName);
			LOCATE(18,21);
			printf("《 %s 》に %d のダメージ！", pEnemy -> aName, nResult);
		}
		else if(nMytern == 10)								// 暗光弾
		{
			pPlayer -> nMagic -= 30;						// 魔力－30
			nResult = pPlayer -> nAttack + GetRandom(-10,10);
			pEnemy -> nLife -= nResult;						// ダメージの代入
			pPlayer -> nLife += GetRandom(100,200);			// 体力の大回復
			pPlayer -> nAttack += GetRandom(10,20);			// 攻撃力UP
			pPlayer -> nDefense += GetRandom(10,20);		// 守備力UP

			// 効果音の再生
			nMP3Handle = OPENMP3("Ankoudan.mp3");			// オープン & 初期化
			PLAYMP3(nMP3Handle);							// 繰り返し再生

			AnkouDanEffect();								// 暗光弾エフェクト

			COLOR(WHITE,BLACK);
			LOCATE(18,20);
			printf("《 %s 》の暗光弾！！！", pPlayer -> aName);
			LOCATE(18,21);
			printf("《 %s 》に %d のダメージ！", pEnemy -> aName, nResult);
		}//if.fin

		Enter();											// プリーズエンター

	}//if.fin(タホドラキーの魔法効果)
	else if(nAction == 5)
	{
		LOCATE(18,20);
		printf("《 %s 》は眠っている！", pPlayer -> aName);

		Enter();											// プリーズエンター

	}//if.fin

	CLOSEMP3(nMP3Handle);									// 停止 & クローズ

}

/*******************************************************************************
 エネミーの行動関数
*******************************************************************************/
void Enemy( PLAYER *pPlayer, ENEMY *pEnemy, int nAction, int nMytern, int nDorakiIllusion)
{
	// 変数宣言
	int nDamage  = ZERO;						// エネミーダメージ格納
	int nMP3Handle = ZERO;

	COLOR(WHITE,BLACK);							// 着色

	// エネミーの行動 ////////////////////////////////////
	if(nAction == 1)										// エネミー通常攻撃
	{
		if(nMytern != 2)									// プレイヤーが回避状態ではない時
		{
			nDamage = pEnemy -> nAttack - (pPlayer -> nDefense + GetRandom(-10,10));
			pPlayer -> nLife -= nDamage;

			if(nDorakiIllusion == 1)						// ドラキー
			{
				Doraki2();									// ドラキーアクション
			}
			else if(nDorakiIllusion == 2)					// タホドラキー
			{
				TahoDoraki2();								// タホドラキーアクション
			}
			else if(nDorakiIllusion == 3)					// ドラキーマ
			{
				DorakiMa2();								// ドラキーマアクション
			}//if.fin

			// 効果音の再生
			nMP3Handle = OPENMP3("DorakiAttack.mp3");				// オープン & 初期化
			PLAYMP3(nMP3Handle);									// 繰り返し再生

			LOCATE(18,20);
			printf("《 %s 》のこうげき！", pEnemy -> aName);
			LOCATE(18,21);
			printf("《 %s 》に %d のダメージ！", pPlayer -> aName, nDamage);
		}
		else if(nMytern == 2)
		{
			nDamage = GetRandom(30,120);					// カウンターダメージ
			pEnemy -> nLife -= nDamage;

			WhiteNormalEffect();							// ノーマルエフェクト
			BlackNormalEffect();							// ブラックエフェクト
			WhiteNormalEffect();							// ノーマルエフェクト
			BlackNormalEffect();							// ブラックエフェクト
			WhiteNormalEffect();							// ノーマルエフェクト
			BlackNormalEffect();							// ブラックエフェクト

			LOCATE(18,20);
			printf("《 %s 》のこうげき！", pEnemy -> aName);
			LOCATE(18,21);
			printf("《 %s 》のカウンター！", pPlayer -> aName);
			LOCATE(18,22);
			printf("《 %s 》に %d のダメージ！", pEnemy -> aName, nDamage);
		}//if.fin
	}
	else if(nAction == 2)									// エネミー回避
	{
		Doraki2();											// ドラキーアクション
		LOCATE(18,20);
		printf("《 %s 》はこうげきに備えている！", pEnemy -> aName);
	}
	else if(nAction == 3)									// 羽休め
	{
		// 効果音の再生
		nMP3Handle = OPENMP3("Josho.mp3");						// オープン & 初期化
		PLAYMP3(nMP3Handle);									// 繰り返し再生

		Doraki2();											// ドラキーアクション
		Joshoffect();										// 上昇エフェクト

		LOCATE(18,20);
		printf("《 %s 》は羽を休めている", pEnemy -> aName);
		LOCATE(18,21);
		printf("《 %s 》が回避値上昇！", pEnemy -> aName);
	}
	else if(nAction == 4)										// 回魔魔法：
	{
		if(pEnemy -> nMagic >= ONE)
		{
			// 効果音の再生
			nMP3Handle = OPENMP3("Kaifuku.mp3");					// オープン & 初期化
			PLAYMP3(nMP3Handle);									// 繰り返し再生

			pEnemy -> nMagic -= ONE;
			pEnemy -> nLife += GetRandom(100,370);				// 回復
			pEnemy -> nMagic += GetRandom(20,25);				// 回復
			Doraki2();											// ドラキーマアクション

			KifukuEffect();										// 回復エフェクト

			LOCATE(18,20);
			printf("《 %s 》は回魔魔法：ロブマチューラを唱えた", pEnemy -> aName);
			LOCATE(18,21);
			printf("《 %s 》はみるみる回復していく！", pEnemy -> aName);
		}
		else if(pEnemy -> nMagic <= ZERO)
		{
			LOCATE(18,20);
			printf("《 %s 》は回魔魔法：ロブマチューラを唱えた", pEnemy -> aName);
			LOCATE(18,21);
			printf("しかし、魔力がたらないようだ！");
		}
	}
	else if(nAction == 5)									// 睡欲魔法：ネロー
	{
		// 効果音の再生
		nMP3Handle = OPENMP3("warp.mp3");						// オープン & 初期化
		PLAYMP3(nMP3Handle);									// 繰り返し再生

		TahoDoraki2();										// タホドラキーアクション

		CLOSEMP3(nMP3Handle);									// 停止 & クローズ
		
		LOCATE(18,20);
		printf("《 %s 》は睡欲魔法：ネローを唱えていた！", pEnemy -> aName);
		LOCATE(18,21);
		printf("《 %s 》はなんと眠っていた！", pPlayer -> aName);
	}
	else if(nAction == 6)									// 増遅魔法：ヨケンレ
	{
		// 効果音の再生
		nMP3Handle = OPENMP3("warp.mp3");						// オープン & 初期化
		PLAYMP3(nMP3Handle);									// 繰り返し再生

		pPlayer -> nAvoidance -= ONE;						// 回避値減少
		TahoDoraki2();										// タホドラキーアクション

		CLOSEMP3(nMP3Handle);									// 停止 & クローズ
		
		LOCATE(18,20);
		printf("《 %s 》は増遅魔法：ヨケンレを唱えた！", pEnemy -> aName);
		LOCATE(18,21);
		printf("《 %s 》の体は重くなっていく！", pPlayer -> aName);
	}
	else if(nAction == 7)									// メラミ
	{
		if(pEnemy -> nMagic >= 7)
		{
			pEnemy -> nMagic -= 7;
			nDamage = pEnemy -> nAttack + GetRandom(-10,10);
			pPlayer -> nLife -= nDamage;

			// 効果音の再生
			nMP3Handle = OPENMP3("GurabiDon.mp3");					// オープン & 初期化
			PLAYMP3(nMP3Handle);									// 繰り返し再生

			TahoDoraki2();									// タホドラキーアクション

			LOCATE(18,20);
			printf("《 %s 》は攻撃魔法：メラミを唱えた！", pEnemy -> aName);
			LOCATE(18,21);
			printf("《 %s 》に %d のダメージ！", pPlayer -> aName, nDamage);
		}
		else if(pEnemy -> nMagic <= 6)
		{
			LOCATE(18,20);
			printf("《 %s 》は攻撃魔法：メラミを唱えた！", pEnemy -> aName);
			LOCATE(18,21);
			printf("しかし、魔力がたらないようだ！");
		}

	}//if.fin

	CLOSEMP3(nMP3Handle);									// 停止 & クローズ

	Enter();												// プリーズエンター

}

/*******************************************************************************
 プリーズエンター関数
*******************************************************************************/
void Enter( void )
{
	// 変数宣言
	int nkey = ZERO;
	int nMP3Handle = ZERO;

	// プリーズエンター
	while(1)
	{
		KEYCLEAR();												// キーボードを初期化する 
		COLOR(YELLOW);
		LOCATE(48, 22);
		printf("《Please ENTER》");
		WAIT(300);												// 0.3secの時間待ち 
		INKEY(nkey);											// 何かキーが押されていたら変数に値を入力する 
		if (nkey == 0xd) break;									// 何か押されたら終了する 

		KEYCLEAR();												// キーボードを初期化する 
		COLOR(LIME);
		LOCATE(48, 22);
		printf("《Please ENTER》");
		WAIT(300);												// 0.3secの時間待ち 
		INKEY(nkey);											// 何かキーが押されていたら変数に値を入力する 
		if (nkey == 0xd) break;									// 何か押されたら終了する
	}//while.fin

	// 効果音の再生
	nMP3Handle = OPENMP3("Select.mp3");						// オープン & 初期化
	PLAYMP3(nMP3Handle);									// 繰り返し再生

	CLOSEMP3(nMP3Handle);									// クローズ & 停止

	ComentReset();											// コメント欄のリセット

}

/******************************************************************************
 スライムリンク関数(ソウルリンク)
*******************************************************************************/
int SuraimRink( int nWarpiru )
{
	// 変数宣言
	int cCode = ZERO;
	int nSelect = ZERO;
	int nSuraimSelect = ZERO;
	int nPosition = ZERO;
	int nReslut = ZERO;
	
	CLS(WHITE, BLACK);

	// メッセージの表示 // ボタンが押されるまでアニメーション
	while(1)
	{
		KEYCLEAR();											// 念のためキーボードを初期化する
		Soulrink();											// ソウルリンクタイトルを表示する

		COLOR(BLACK,LIME);
		LOCATE(35 , 21);									// 場所指定
		printf(" PLEASE ENTER ");

		WAIT(700);											// インターバル 0.7秒
		INKEY(cCode);										// 何かキーが押されていたら変数に値を入力する
		if (cCode == 0xd) break;							// エンターが押されたら終了する
		KEYCLEAR();											// 念のためキーボードを初期化する
		Soulrink2();										// ソウルリンクタイトル２を表示する

		LOCATE(35 , 21);									// 場所指定
		printf(" PLEASE ENTER ");

		WAIT(700);											// インターバル 0.7秒
		INKEY(cCode);										// 何かキーが押されていたら変数に値を入力する
		if (cCode == 0xd) break;							// エンターが押されたら終了する
	}//while.fin

	// ソウルリンクの説明を見るかそのまま始めるかの選択
	COLOR(WHITE,BLACK);
	LOCATE(35, 20);											// 場所指定
	printf("◇ SOUL RINK !!!");
	LOCATE(35, 21);											// 場所指定
	printf("◇ ソウルリンクについて");
	
	LOCATE(31, 20);											// 場所指定
	COLOR(WHITE,H_RED);
	printf(" →");
	LOCATE(31, 21);											// 場所指定
	COLOR(WHITE,BLACK);
	printf("   ");

	nReslut = 0x61;
	
	// 上記選択肢からの選択コマンド
	while(1)
	{
		while(1)												// カーソル移動用ループ
		{
			INKEY(nSelect);										// 何かキーが押されていたら変数に値を入力する

			if(nSelect == 0x77)									// W アスキーコードの入力後
			{
				if(nPosition == ZERO)							// カーソルが上にある時に W を押した場合
				{
					BACKCOLOR(BLACK);
					LOCATE(31, 20);
					printf(" 　");
					COLOR(WHITE, BLUE);
					LOCATE(31, 21);
					printf(" →");

					nReslut = 0x73;
					nPosition = ONE;
				}
				else if(nPosition == ONE)						// カーソルが下にある時に W を押した場合
				{
					COLOR(WHITE, H_RED);
					LOCATE(31, 20);
					printf(" →");
					BACKCOLOR(BLACK);
					LOCATE(31, 21);
					printf(" 　");

					nReslut = 0x61;
					nPosition = ZERO;
				}//if.fin
			}//if.fin
			if(nSelect == 0x73)									// S アスキーコードの入力後
			{
				if(nPosition == ZERO)							// カーソルが上にある時に S を押した場合
				{
					BACKCOLOR(BLACK);
					LOCATE(31, 20);
					printf(" 　");
					COLOR(WHITE, BLUE);
					LOCATE(31, 21);
					printf(" →");

					nReslut = 0x73;
					nPosition = ONE;
				}
				else if(nPosition == ONE)						// カーソルが下にある時に S を押した場合
				{
					COLOR(WHITE, H_RED);
					LOCATE(31, 20);
					printf(" →");
					BACKCOLOR(BLACK);
					LOCATE(31, 21);
					printf(" 　");

					nReslut = 0x61;
					nPosition = ZERO;
				}//if.fin
			}//if.fin

			if(nSelect == 0xd) break;

		}//while.fin

		BACKCOLOR(BLACK);

		// 選択後
		if(nReslut == 0x61)									// a を選んだ場合
		{
			NormalWarp( nWarpiru );							// ワープ
			break;
		}
		else if(nReslut == 0x73)							// d を選んだ場合
		{
			SoulRinkDescription(nWarpiru);					// ソウルリンクについての説明

			system("cls");									// 画面のクリア
			Soulrink2();									// ソウルリンクタイトル２を表示する

			BACKCOLOR(BLACK);

			// ソウルリンクの説明を見るかそのまま始めるかの選択
			COLOR(WHITE,BLACK);
			LOCATE(35, 20);									// 場所指定
			printf("◇ SOUL RINK !!!");
			LOCATE(35, 21);									// 場所指定
			printf("◇ ソウルリンクについて");

			LOCATE(31, 20);									// 場所指定
			COLOR(WHITE,BLACK);
			printf("   ");
			LOCATE(31, 21);									// 場所指定
			COLOR(WHITE, BLUE);
			printf(" →");

			continue;
		}//if.fin
	}//while.fin

	nSuraimSelect = ONE;								// 返す値に[ 1 ]の代入

	// 値を返す(戻り値)
	return nSuraimSelect;

}

/*******************************************************************************
 動くスライム + Status関数(あきーら)
*******************************************************************************/
int SuraimMoveStatus( PLAYER *pPlayer, INITIAL *pInitial, ENEMY *pEnemy)
{
	//変数宣言
	int cCode = ZERO;
	int nSuraimSelect;										// スライムの選択に使用
	int nColor = BLUE;										// ステイタス枠の着色
	int nVertical = 2;										// 縦軸
	int nHorizontal = 44;									// 横軸

	StatusFrame( nColor );									// ステイタス枠の表示

	// スライムの背景へ文字の挿入
	COLOR(nColor);
	LOCATE(13,3);
	printf("＋～～～～～～＋");
	LOCATE(13,4);
	COLOR(BLACK);
	printf("　　あきーら　　");
	COLOR(nColor);
	LOCATE(13,5);
	printf("＋～～～～～～＋");

	// ステイタス枠への文字の挿入
	COLOR(H_RED);
	LOCATE(nHorizontal -1, nVertical++);
	printf("◇--------------------------------◇");
	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("たくましく勇敢なスライム");
	LOCATE(nHorizontal, nVertical++);
	printf("が、前向きすぎるのが玉にキズ...");
	LOCATE(nHorizontal, nVertical++);
	printf("体力・魔力・攻撃力がUPするぞ！");
	LOCATE(nHorizontal, nVertical++);
	printf("回避値・守備力がDOWNしてしまうぞ！");
	COLOR(H_RED);
	LOCATE(nHorizontal -1, nVertical++);
	printf("◇--------------------------------◇");

	// 前文への補足
	LOCATE(nHorizontal +20, nVertical -3);
	COLOR(H_RED);
	printf("UP");
	LOCATE(nHorizontal +16, nVertical -2);
	COLOR(BLUE);
	printf("DOWN");

	nVertical++;											// スペース作りのインクリメント

	LOCATE(nHorizontal -1, nVertical++);
	COLOR(GREEN);
	printf("* BEFOR AFTER + BASESTATUS  RESULT *");

	nVertical++;											// スペース作りのインクリメント

	// 変数宣言 int型からdouble型へ変換 のちのスライム決定で代入
	int    nStatusLif;										// 体力値の仮変数
	int    nStatusMag;										// 魔力値の仮変数
	int    nStatusAtk;										// 攻撃力の仮変数
	int    nStatusDef;										// 守備力の仮変数
	int    nStatusAvo;										// 回避値の仮変数

	int    nStatus;
	double dStatus;

	// 体力値の変化表示(変化前→変換後→結果)
	nStatus = pPlayer -> nLife;								// nStatusに得た数値を代入
	dStatus = nStatus;										// 型をint型からdouble型へ変換
	dStatus *= NUM_STATUS_B;								// 変化分の数値の算出
	nStatus = dStatus;										// 型をdouble型からint型へ変換

	nStatusLif = pPlayer -> nLife + nStatus + BASE_LIFE;	// 仮変数に数値の代入(ステイタス決定時に使用)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("体力値 %3d →      ＋ %3d ＞ %3d", pPlayer -> nLife, BASE_LIFE, pPlayer -> nLife + nStatus + BASE_LIFE);
	COLOR(H_RED);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d", pPlayer -> nLife + nStatus);
	
	nVertical++;											// スペース作りのインクリメント

	// 魔力値の変化表示(変化前→変換後→結果)
	nStatus = pPlayer -> nMagic;							// nStatusに得た数値を代入
	dStatus = nStatus;										// 型をint型からdouble型へ変換
	dStatus *= NUM_STATUS_B;								// 変化分の数値の算出
	nStatus = dStatus;										// 型をdouble型からint型へ変換

	nStatusMag = pPlayer -> nMagic + nStatus + BASE_MAGIC;	// 仮変数に数値の代入(ステイタス決定時に使用)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("魔力値 %3d →      ＋ %3d ＞ %3d", pPlayer -> nMagic, BASE_MAGIC, pPlayer -> nMagic + nStatus + BASE_MAGIC);
	COLOR(H_RED);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d",pPlayer -> nMagic + nStatus);

	nVertical++;											// スペース作りのインクリメント

	// 攻撃力の変化表示(変化前→変換後→結果)
	nStatus = pPlayer ->nAttack;							// nStatusに得た数値を代入
	dStatus = nStatus;										// 型をint型からdouble型へ変換
	dStatus *= NUM_STATUS_A;								// 変化分の数値の算出
	nStatus = dStatus;										// 型をdouble型からint型へ変換

	nStatusAtk = pPlayer -> nAttack + nStatus + BASE_ATTACK;	// 仮変数に数値の代入(ステイタス決定時に使用)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("攻撃力 %3d →      ＋ %3d ＞ %3d", pPlayer -> nAttack, BASE_ATTACK, pPlayer -> nAttack + nStatus + BASE_ATTACK);
	COLOR(H_RED);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d",pPlayer -> nAttack + nStatus);

	nVertical++;											// スペース作りのインクリメント

	// 守備力の変化表示(変化前→変換後→結果)
	nStatus = pPlayer ->nDefense;							// nStatusに得た数値を代入
	dStatus = nStatus;										// 型をint型からdouble型へ変換
	dStatus *= NUM_STATUS_C;								// 変化分の数値の算出
	nStatus = dStatus;										// 型をdouble型からint型へ変換

	nStatusDef = pPlayer -> nDefense - nStatus + BASE_DEFENSE;	// 仮変数に数値の代入(ステイタス決定時に使用)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("守備力 %3d →      ＋ %3d ＞ %3d", pPlayer ->nDefense, BASE_DEFENSE, pPlayer -> nDefense - nStatus + BASE_DEFENSE);
	COLOR(BLUE);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d",pPlayer -> nDefense - nStatus);

	nVertical++;											// スペース作りのインクリメント

	// 回避値の変化表示(変化前→変換後→結果)
	nStatusAvo = pPlayer -> nAvoidance - 1 + BASE_AVOIDANCE;	// 仮変数に数値の代入(ステイタス決定時に使用)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("回避値 %3d →      ＋ %3d ＞ %3d", pPlayer -> nAvoidance, BASE_AVOIDANCE, pPlayer -> nAvoidance - 1 + BASE_AVOIDANCE);
	COLOR(BLUE);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d",pPlayer -> nAvoidance - 1);

	nVertical++;											// スペース作りのインクリメント

	// あきーらを選ぶか変更前のステイタスで始めるか
	COLOR(BLACK);
	LOCATE(nHorizontal +3, nVertical++);
	printf("《        》とリンクして始める！");
	LOCATE(nHorizontal +3, nVertical++);
	printf("《        》とリンクせずに始める");

	COLOR(BLUE);
	LOCATE(nHorizontal +5, nVertical -2);
	printf("あきーら");
	LOCATE(nHorizontal +5, nVertical -1);
	printf("あきーら");

	// 選択肢の表示
	COLOR(WHITE,H_RED);
	LOCATE(nHorizontal -1, nVertical -2);
	printf(" O：");
	COLOR(WHITE,BLUE);
	LOCATE(nHorizontal -1, nVertical -1);
	printf(" X：");

	// 選択肢の表示
	LOCATE(3,22);
	COLOR(WHITE,BLACK);
	printf("A ← 《ドン・イ》｜《アダぶち》 → D");

	// 念のためキーボードを初期化する
	KEYCLEAR();

	// ボタンが押されるまでアニメーション
	while(1)
	{
		KEYCLEAR();									// 念のためキーボードを初期化する
		Suraim();									// スライムを表示する
		WAIT(700);									// インターバル 0.7秒
		INKEY(nSuraimSelect);						// 何かキーが押されていたら変数に値を入力する
		if (nSuraimSelect == 0x78 || nSuraimSelect == 0x6f || nSuraimSelect == 0x61 || nSuraimSelect == 0x64) break;  // a / d / o / x 押されたら終了する
		KEYCLEAR();									// 念のためキーボードを初期化する
		Suraim2();									// スライム２を表示する
		WAIT(700);									// インターバル 0.7秒
		INKEY(nSuraimSelect);						// 何かキーが押されていたら変数に値を入力する
		if (nSuraimSelect == 0x78 || nSuraimSelect == 0x6f || nSuraimSelect == 0x61 || nSuraimSelect == 0x64) break;  // a / d / o / x 押されたら終了する
	}//while.fin

	//画面内の選択肢より入力された値で判断
	if(nSuraimSelect == 0x6f)							// [ o ]が選択された場合、値の代入
	{
		// 選んだスライムによってパワーアップ！！！
		pPlayer -> nLife      = nStatusLif;				// 体力値の代入
		pPlayer -> nMagic     = nStatusMag;				// 魔力値の代入
		pPlayer -> nAttack    = nStatusAtk;				// 攻撃力の代入
		pPlayer -> nDefense   = nStatusDef;				// 守備力の代入
		pPlayer -> nAvoidance = nStatusAvo;				// 回避値の代入

		// 相手のステイタスも少し上昇
		pEnemy -> nLife    += 130;
		pEnemy -> nAttack  += 20;
	}
	else if(nSuraimSelect == 0x78)						// [ x ]が選択された場合、値の代入
	{
		// 選ばずにスタート！！！
		pPlayer -> nLife      = pInitial -> nLife;		// 体力値の初期値の代入
		pPlayer -> nMagic     = pInitial -> nMagic;		// 魔力値の初期値の代入
		pPlayer -> nAttack    = pInitial -> nAttack;	// 攻撃力の初期値の代入
		pPlayer -> nDefense   = pInitial -> nDefense;	// 守備力の初期値の代入
		pPlayer -> nAvoidance = pInitial -> nAvoidance;	// 回避値の初期値の代入
	}

	// 選択肢の値を戻す
	return nSuraimSelect;
}

/*******************************************************************************
 動くメタルスライム + Status関数(ドン・イ)
*******************************************************************************/
int MetalSuraimMoveStatus( PLAYER *pPlayer, INITIAL *pInitial, ENEMY *pEnemy)
{
	//変数宣言
	int cCode = ZERO;
	int nSuraimSelect;										// スライムの選択に使用
	int nColor = H_BLACK;									// ステイタス枠の着色
	int nVertical = 2;										// 縦軸
	int nHorizontal = 44;									// 横軸

	StatusFrame( nColor );									// ステイタス枠の表示

	// スライムの背景へ文字の挿入
	COLOR(nColor);
	LOCATE(13,3);
	printf("＋～～～～～～＋");
	LOCATE(13,4);
	COLOR(BLACK);
	printf("　　ドン・イ　　");
	COLOR(nColor);
	LOCATE(13,5);
	printf("＋～～～～～～＋");

	// ステイタス枠への文字の挿入
	COLOR(H_RED);
	LOCATE(nHorizontal -1, nVertical++);
	printf("◇--------------------------------◇");
	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("あり得ないほどの自信の持ち主！");
	LOCATE(nHorizontal, nVertical++);
	printf("思うほど素早く動かない...(遅い)");
	LOCATE(nHorizontal, nVertical++);
	printf("攻撃力・守備力・回避値がUPするぞ！");
	LOCATE(nHorizontal, nVertical++);
	printf("体力がDOWNしてしまうぞ！");
	COLOR(H_RED);
	LOCATE(nHorizontal -1, nVertical++);
	printf("◇--------------------------------◇");

	// 前文への補足
	LOCATE(nHorizontal +24, nVertical -3);
	COLOR(H_RED);
	printf("UP");
	LOCATE(nHorizontal +6, nVertical -2);
	COLOR(BLUE);
	printf("DOWN");

	nVertical++;											// スペース作りのインクリメント

	LOCATE(nHorizontal -1, nVertical++);
	COLOR(GREEN);
	printf("* BEFOR AFTER + BASESTATUS  RESULT *");

	nVertical++;											// スペース作りのインクリメント

	// 変数宣言 int型からdouble型へ変換 のちのスライム決定で代入
	int    nStatusLif;										// 体力値の仮変数
	int    nStatusMag;										// 魔力値の仮変数
	int    nStatusAtk;										// 攻撃力の仮変数
	int    nStatusDef;										// 守備力の仮変数
	int    nStatusAvo;										// 回避値の仮変数

	int    nStatus;
	double dStatus;

	// 体力値の変化表示(変化前→変換後→結果)
	nStatus = pPlayer -> nLife;								// nStatusに得た数値を代入
	dStatus = nStatus;										// 型をint型からdouble型へ変換
	dStatus *= NUM_STATUS_D;								// 変化分の数値の算出
	nStatus = dStatus;										// 型をdouble型からint型へ変換

	nStatusLif = pPlayer -> nLife - nStatus + BASE_LIFE;	// 仮変数に数値の代入(ステイタス決定時に使用)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("体力値 %3d →      ＋ %3d ＞ %3d", pPlayer -> nLife, BASE_LIFE, pPlayer -> nLife - nStatus + BASE_LIFE);
	COLOR(BLUE);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d", pPlayer -> nLife - nStatus);
	
	nVertical++;											// スペース作りのインクリメント

	// 魔力値の変化表示(変化前→変換後→結果)
	nStatusMag = pPlayer -> nMagic + BASE_MAGIC;	// 仮変数に数値の代入(ステイタス決定時に使用)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("魔力値 %3d →  %3d ＋ %3d ＞ %3d", pPlayer -> nMagic, pPlayer -> nMagic, BASE_MAGIC, pPlayer -> nMagic + BASE_MAGIC);

	nVertical++;											// スペース作りのインクリメント

	// 攻撃力の変化表示(変化前→変換後→結果)
	nStatus = pPlayer -> nAttack;							// nStatusに得た数値を代入
	dStatus = nStatus;										// 型をint型からdouble型へ変換
	dStatus *= NUM_STATUS_B;								// 変化分の数値の算出
	nStatus = dStatus;										// 型をdouble型からint型へ変換

	nStatusAtk = pPlayer -> nAttack + nStatus + BASE_ATTACK;	// 仮変数に数値の代入(ステイタス決定時に使用)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("攻撃力 %3d →      ＋ %3d ＞ %3d", pPlayer -> nAttack, BASE_ATTACK, pPlayer -> nAttack + nStatus + BASE_ATTACK);
	COLOR(H_RED);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d",pPlayer -> nAttack + nStatus);

	nVertical++;											// スペース作りのインクリメント

	// 守備力の変化表示(変化前→変換後→結果)
	nStatus = pPlayer ->nDefense;							// nStatusに得た数値を代入
	dStatus = nStatus;										// 型をint型からdouble型へ変換
	dStatus *= NUM_STATUS_C;								// 変化分の数値の算出
	nStatus = dStatus;										// 型をdouble型からint型へ変換

	nStatusDef = pPlayer -> nDefense + nStatus + BASE_DEFENSE;	// 仮変数に数値の代入(ステイタス決定時に使用)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("守備力 %3d →      ＋ %3d ＞ %3d", pPlayer ->nDefense, BASE_DEFENSE, pPlayer -> nDefense + nStatus + BASE_DEFENSE);
	COLOR(H_RED);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d",pPlayer -> nDefense + nStatus);

	nVertical++;											// スペース作りのインクリメント

	// 回避値の変化表示(変化前→変換後→結果)
	nStatusAvo = pPlayer -> nAvoidance + 1 + BASE_AVOIDANCE;	// 仮変数に数値の代入(ステイタス決定時に使用)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("回避値 %3d →      ＋ %3d ＞ %3d", pPlayer -> nAvoidance, BASE_AVOIDANCE, pPlayer -> nAvoidance + 1 + BASE_AVOIDANCE);
	COLOR(H_RED);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d",pPlayer -> nAvoidance + 1);

	nVertical++;											// スペース作りのインクリメント

	// あきーらを選ぶか変更前のステイタスで始めるか
	COLOR(BLACK);
	LOCATE(nHorizontal +3, nVertical++);
	printf("《        》とリンクして始める！");
	LOCATE(nHorizontal +3, nVertical++);
	printf("《        》とリンクせずに始める");

	COLOR(H_BLACK);
	LOCATE(nHorizontal +5, nVertical -1);
	printf("ドン・イ");
	LOCATE(nHorizontal +5, nVertical -2);
	printf("ドン・イ");

	// 選択肢の表示
	COLOR(WHITE,H_RED);
	LOCATE(nHorizontal -1, nVertical -2);
	printf(" O：");
	COLOR(WHITE,BLUE);
	LOCATE(nHorizontal -1, nVertical -1);
	printf(" X：");

	// 選択肢の表示
	LOCATE(3,22);
	COLOR(WHITE,BLACK);
	printf("A ← 《アダぶち》｜《あきーら》 → D");

	// 念のためキーボードを初期化する
	KEYCLEAR();

	// ボタンが押されるまでアニメーション
	while(1)
	{
		KEYCLEAR();									// 念のためキーボードを初期化する
		MetalSuraim();								// メタルスライムを表示する
		WAIT(700);									// インターバル 0.7秒
		INKEY(nSuraimSelect);						// 何かキーが押されていたら変数に値を入力する
		if (nSuraimSelect == 0x78 || nSuraimSelect == 0x6f || nSuraimSelect == 0x61 || nSuraimSelect == 0x64) break;  // a / d / o / x 押されたら終了する
		KEYCLEAR();									// 念のためキーボードを初期化する
		MetalSuraim2();								// メタルスライム２を表示する
		WAIT(700);									// インターバル 0.7秒
		INKEY(nSuraimSelect);						// 何かキーが押されていたら変数に値を入力する
		if (nSuraimSelect == 0x78 || nSuraimSelect == 0x6f || nSuraimSelect == 0x61 || nSuraimSelect == 0x64) break;  // a / d / o / x 押されたら終了する
	}//while.fin

	//画面内の選択肢より入力された値で判断
	if(nSuraimSelect == 0x6f)						// [ o ]が選択された場合、値の代入
	{
		// 選んだスライムによってパワーアップ！！！
		pPlayer -> nLife = nStatusLif;				// 体力値の代入
		pPlayer -> nMagic = nStatusMag;				// 魔力値の代入
		pPlayer -> nAttack = nStatusAtk;			// 攻撃力の代入
		pPlayer -> nDefense = nStatusDef;			// 守備力の代入
		pPlayer -> nAvoidance = nStatusAvo;			// 回避値の代入

		// 相手のステイタスも少し上昇
		pEnemy -> nLife    += 130;
		pEnemy -> nAttack  += 40;
	}
	else if(nSuraimSelect == 0x78)						// [ x ]が選択された場合、値の代入
	{
		// 選ばずにスタート！！！
		pPlayer -> nLife      = pInitial -> nLife;		// 体力値の初期値の代入
		pPlayer -> nMagic     = pInitial -> nMagic;		// 魔力値の初期値の代入
		pPlayer -> nAttack    = pInitial -> nAttack;	// 攻撃力の初期値の代入
		pPlayer -> nDefense   = pInitial -> nDefense;	// 守備力の初期値の代入
		pPlayer -> nAvoidance = pInitial -> nAvoidance;	// 回避値の初期値の代入
	}

	// 選択肢の値を戻す
	return nSuraimSelect;

}

/*******************************************************************************
 動くぶちスライム + Status関数(アダぶち)
*******************************************************************************/
int ButiSuraimMoveStatus( PLAYER *pPlayer, INITIAL *pInitial, ENEMY *pEnemy)
{
	//変数宣言
	int cCode = ZERO;
	int nSuraimSelect;										// スライムの選択に使用
	int nColor = YELLOW;									// ステイタス枠の着色
	int nVertical = 2;										// 縦軸
	int nHorizontal = 44;									// 横軸

	StatusFrame( nColor );									// ステイタス枠の表示

	// スライムの背景へ文字の挿入
	COLOR(nColor);
	LOCATE(13,3);
	printf("＋～～～～～～＋");
	LOCATE(13,4);
	COLOR(BLACK);
	printf("　　アダぶち　　");
	COLOR(nColor);
	LOCATE(13,5);
	printf("＋～～～～～～＋");

	// ステイタス枠への文字の挿入
	COLOR(H_RED);
	LOCATE(nHorizontal -1, nVertical++);
	printf("◇--------------------------------◇");
	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("ちょいちょいボケるが芯の強いやつ！");
	LOCATE(nHorizontal, nVertical++);
	printf("ブチはなんと染み込んだ醤油らしい(笑");
	LOCATE(nHorizontal, nVertical++);
	printf("体力・魔力・回避値がUPするぞ！");
	LOCATE(nHorizontal, nVertical++);
	printf("守備力がDOWNしてしまうぞ！");
	COLOR(H_RED);
	LOCATE(nHorizontal -1, nVertical++);
	printf("◇--------------------------------◇");

	// 前文への補足
	LOCATE(nHorizontal +20, nVertical -3);
	COLOR(H_RED);
	printf("UP");
	LOCATE(nHorizontal +8, nVertical -2);
	COLOR(BLUE);
	printf("DOWN");

	nVertical++;											// スペース作りのインクリメント

	LOCATE(nHorizontal -1, nVertical++);
	COLOR(GREEN);
	printf("* BEFOR AFTER + BASESTATUS  RESULT *");

	nVertical++;											// スペース作りのインクリメント

	// 変数宣言 int型からdouble型へ変換 のちのスライム決定で代入
	int    nStatusLif;										// 体力値の仮変数
	int    nStatusMag;										// 魔力値の仮変数
	int    nStatusAtk;										// 攻撃力の仮変数
	int    nStatusDef;										// 守備力の仮変数
	int    nStatusAvo;										// 回避値の仮変数

	int    nStatus;
	double dStatus;

	// 体力値の変化表示(変化前→変換後→結果)
	nStatus = pPlayer -> nLife;								// nStatusに得た数値を代入
	dStatus = nStatus;										// 型をint型からdouble型へ変換
	dStatus *= NUM_STATUS_B;								// 変化分の数値の算出
	nStatus = dStatus;										// 型をdouble型からint型へ変換

	nStatusLif = pPlayer -> nLife + nStatus + BASE_LIFE;	// 仮変数に数値の代入(ステイタス決定時に使用)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("体力値 %3d →      ＋ %3d ＞ %3d", pPlayer -> nLife, BASE_LIFE, pPlayer -> nLife + nStatus + BASE_LIFE);
	COLOR(H_RED);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d", pPlayer -> nLife + nStatus);
	
	nVertical++;											// スペース作りのインクリメント

	// 魔力値の変化表示(変化前→変換後→結果)
	nStatus = pPlayer ->nMagic;								// nStatusに得た数値を代入
	dStatus = nStatus;										// 型をint型からdouble型へ変換
	dStatus *= NUM_STATUS_D;								// 変化分の数値の算出
	nStatus = dStatus;										// 型をdouble型からint型へ変換

	nStatusMag = pPlayer -> nMagic + nStatus + BASE_MAGIC;	// 仮変数に数値の代入(ステイタス決定時に使用)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("体力値 %3d →      ＋ %3d ＞ %3d", pPlayer -> nMagic, BASE_MAGIC, pPlayer -> nMagic + nStatus + BASE_MAGIC);
	COLOR(H_RED);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d", pPlayer -> nMagic + nStatus);

	nVertical++;											// スペース作りのインクリメント

	// 攻撃力の変化表示(変化前→変換後→結果)
	nStatusAtk = pPlayer -> nAttack + nStatus + BASE_ATTACK;	// 仮変数に数値の代入(ステイタス決定時に使用)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("攻撃力 %3d →  %3d ＋ %3d ＞ %3d", pPlayer -> nAttack, pPlayer -> nAttack, BASE_ATTACK, pPlayer -> nAttack + BASE_ATTACK);

	nVertical++;											// スペース作りのインクリメント

	// 守備力の変化表示(変化前→変換後→結果)
	nStatus = pPlayer ->nDefense;							// nStatusに得た数値を代入
	dStatus = nStatus;										// 型をint型からdouble型へ変換
	dStatus *= NUM_STATUS_B;								// 変化分の数値の算出
	nStatus = dStatus;										// 型をdouble型からint型へ変換

	nStatusDef = pPlayer -> nDefense - nStatus + BASE_DEFENSE;	// 仮変数に数値の代入(ステイタス決定時に使用)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("守備力 %3d →      ＋ %3d ＞ %3d", pPlayer -> nDefense, BASE_DEFENSE, pPlayer -> nDefense - nStatus + BASE_DEFENSE);
	COLOR(BLUE);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d",pPlayer -> nDefense - nStatus);

	nVertical++;											// スペース作りのインクリメント

	// 回避値の変化表示(変化前→変換後→結果)
	nStatusAvo = pPlayer -> nAvoidance +1 + BASE_AVOIDANCE;	// 仮変数に数値の代入(ステイタス決定時に使用)

	COLOR(BLACK);
	LOCATE(nHorizontal, nVertical++);
	printf("回避値 %3d →      ＋ %3d ＞ %3d", pPlayer -> nAvoidance, BASE_AVOIDANCE, pPlayer -> nAvoidance +1 + BASE_AVOIDANCE);
	COLOR(H_RED);
	LOCATE(nHorizontal +15, nVertical -1);
	printf("%3d",pPlayer -> nAvoidance +1);

	nVertical++;											// スペース作りのインクリメント

	// あきーらを選ぶか変更前のステイタスで始めるか
	COLOR(BLACK);
	LOCATE(nHorizontal +3, nVertical++);
	printf("《        》とリンクして始める！");
	LOCATE(nHorizontal +3, nVertical++);
	printf("《        》とリンクせずに始める");

	COLOR(BROWN);
	LOCATE(nHorizontal +5, nVertical -1);
	printf("アダぶち");
	LOCATE(nHorizontal +5, nVertical -2);
	printf("アダぶち");

	// 選択肢の表示
	COLOR(WHITE,H_RED);
	LOCATE(nHorizontal -1, nVertical -2);
	printf(" O：");
	COLOR(WHITE,BLUE);
	LOCATE(nHorizontal -1, nVertical -1);
	printf(" X：");

	// 選択肢の表示
	LOCATE(3,22);
	COLOR(WHITE,BLACK);
	printf("A ← 《あきーら》｜《ドン・イ》 → D");

	// 念のためキーボードを初期化する
	KEYCLEAR();

	// ボタンが押されるまでアニメーション
	while(1)
	{
		KEYCLEAR();									// 念のためキーボードを初期化する
		ButiSuraim();								// ぶちスライムを表示する
		WAIT(700);									// インターバル 0.7秒
		INKEY(nSuraimSelect);						// 何かキーが押されていたら変数に値を入力する
		if (nSuraimSelect == 0x78 || nSuraimSelect == 0x6f || nSuraimSelect == 0x61 || nSuraimSelect == 0x64) break;  // a / d / o / x 押されたら終了する
		KEYCLEAR();									// 念のためキーボードを初期化する
		ButiSuraim2();								// ぶちスライム２を表示する
		WAIT(700);									// インターバル 0.7秒
		INKEY(nSuraimSelect);						// 何かキーが押されていたら変数に値を入力する
		if (nSuraimSelect == 0x78 || nSuraimSelect == 0x6f || nSuraimSelect == 0x61 || nSuraimSelect == 0x64) break;  // a / d / o / x 押されたら終了する
	}//while.fin

	//画面内の選択肢より入力された値で判断
	if(nSuraimSelect == 0x6f)						// [ o ]が選択された場合、値の代入
	{
		// 選んだスライムによってパワーアップ！！！
		pPlayer -> nLife = nStatusLif;				// 体力値の代入
		pPlayer -> nMagic = nStatusMag;				// 魔力値の代入
		pPlayer -> nAttack = nStatusAtk;			// 攻撃力の代入
		pPlayer -> nDefense = nStatusDef;			// 守備力の代入
		pPlayer -> nAvoidance = nStatusAvo;			// 回避値の代入

		// 相手のステイタスも少し上昇
		pEnemy -> nLife    += 130;
		pEnemy -> nAttack  += 20;
	}
	else if(nSuraimSelect == 0x78)						// [ x ]が選択された場合、値の代入
	{
		// 選ばずにスタート！！！
		pPlayer -> nLife      = pInitial -> nLife;		// 体力値の初期値の代入
		pPlayer -> nMagic     = pInitial -> nMagic;		// 魔力値の初期値の代入
		pPlayer -> nAttack    = pInitial -> nAttack;	// 攻撃力の初期値の代入
		pPlayer -> nDefense   = pInitial -> nDefense;	// 守備力の初期値の代入
		pPlayer -> nAvoidance = pInitial -> nAvoidance;	// 回避値の初期値の代入
	}

	// 選択肢の値を戻す
	return nSuraimSelect;

}

/*******************************************************************************
 データ入力関数 1P Competition 用
*******************************************************************************/
int CompetitionInput( PLAYER *pPlayer, ENEMY *pEnemy)
{
	// 変数宣言
	int nLengthWord;									//文字列の長さ(文字数)を格納
	int nNamedata;										//変換後のデータ格納
	char *pName;										//aData[MOJI]へ格納するポインタ変数
	
	bool bMojisu = true;								//入力文字が真か偽かの判定
	int  nAkira  = ZERO;
	int  nkim    = ZERO;
	int  nnAkira = ZERO;
	int  nnkim   = ZERO;

	CLS(H_RED,WHITE);

	// 名前入力時の説明
	COLOR(BLACK);
	LOCATE(21,12);
	printf("◇ 入力できる文字数は３～８文字までです！");
	LOCATE(21,14);
	printf("◇ なお、入力文字数が少なかったり多かった場合は");
	LOCATE(21,15);
	printf("  《 》内が空白になるので、そしたら入力してください！");
	LOCATE(21,16);
	printf("◇ 名前入力出来る文字は半角英数字,半角記号であれば可能です！");

	// 入力文字数が3～8以外の場合やり直し
	do
	{
		// プレイヤー（自分）の名前の入力 //
		LOCATE(28,6);
		COLOR(H_RED);
		printf("《 PLEASE INPUT YOUR NAME 》");
		LOCATE(30,8);
		COLOR(H_RED);
		printf("《                    》");
		LOCATE(37,8);
		scanf("%s", &pPlayer -> aName[ZERO]);

		// アスキーコードの格納
		pName = &pPlayer -> aName[ZERO];

		// strlenは文字列の長さ(文字数)を取得する
		nLengthWord = strlen(pName);

		// 入力文字数が3～8以外の場合 bMojisu に false を代入
		if(nLengthWord < MIN_MOJI || nLengthWord > MAX_MOJI)
		{
			bMojisu = false;
			system("cls");

			// 名前入力時の説明
			COLOR(BLACK);
			LOCATE(21,12);
			printf("◇ 入力できる文字数は３～８文字までです！");
			LOCATE(21,14);
			printf("◇ なお、入力文字数が少なかったり多かった場合は");
			LOCATE(21,15);
			printf("  《 》内が空白になるので、そしたら入力してください！");
			LOCATE(21,16);
			printf("◇ 名前入力出来る文字は半角英数字,半角記号であれば可能です！");
		}
		else
		{
			bMojisu = true;
		}//if.fin

	}while(bMojisu == false);

	//// アスキーコードへ変換 ////
	nNamedata = (int) pPlayer -> aName[ZERO];

	// 入力文字判定
	nAkira = pPlayer -> aName[0] + pPlayer -> aName[1] + pPlayer -> aName[2] + pPlayer -> aName[3] + pPlayer -> aName[4];
	nkim = pPlayer -> aName[0] + pPlayer -> aName[1] + pPlayer -> aName[2];

	// ステータス強くなっちゃうわよ～
	if(nAkira == 520)
	{
		pPlayer -> nLife      = 400;
		pPlayer -> nMagic     = 50;
		pPlayer -> nAttack    = 410;
		pPlayer -> nDefense   = ZERO;
		pPlayer -> nAvoidance = 3;
	}
	else if(nkim == 321)
	{
		pPlayer -> nLife      = -100;
		pPlayer -> nMagic     = 50;
		pPlayer -> nAttack    = 300;
		pPlayer -> nDefense   = 170;
		pPlayer -> nAvoidance = 4;
	}
	else
	{
		//文字数別変換
		if(nLengthWord == 3)							// 入力された文字が３文字の時
		{
			//// 体力値の計算割り出し // (1文字目 +70 - 3文字目) *4 == 体力値 //共通
			pPlayer -> nLife = (pPlayer -> aName[0] - pPlayer -> aName[2]) +70 *4;

			//// 魔力値の計算割り出し // (1文字目 + 2文字目 + 3文字目) /10 == 魔力値 //
			pPlayer -> nMagic = (pPlayer -> aName[0] + pPlayer -> aName[1] + pPlayer -> aName[2]) /12;

			//// 攻撃力の計算割り出し // (1文字目 - 2文字目 + 3文字目) %10 + (1文字目 - 2文字目 + 3文字目) //
			pPlayer -> nAttack = (pPlayer -> aName[0] - pPlayer -> aName[1] + pPlayer -> aName[2]) %20
			+ (pPlayer -> aName[0] - pPlayer -> aName[1] + pPlayer -> aName[2]);

			//// 守備力の計算割り出し // (3文字目 -20 ) + (2文字目 -85) //
			pPlayer -> nDefense = (pPlayer -> aName[2] -20 ) + (pPlayer -> aName[1] -85);

			//// 回避値の計算割り出し // 2文字目 %5 //
			pPlayer -> nAvoidance = pPlayer -> aName[1] %5;
		}
		else if(nLengthWord == 4)						// 入力された文字が４文字の時
		{
			//// 体力値の計算割り出し // (1文字目 +70 - 3文字目) *4 == 体力値 //共通
			pPlayer -> nLife = (pPlayer -> aName[0] - pPlayer -> aName[2]) +70 *4;

			//// 魔力値の計算割り出し // (4文字目 + 2文字目 + 3文字目) /10 == 魔力値 //
			pPlayer -> nMagic = (pPlayer -> aName[3] + pPlayer -> aName[1] + pPlayer -> aName[2]) /12;

			//// 攻撃力の計算割り出し // (1文字目 - 2文字目 + 3文字目) %10 + (4文字目 - 1文字目 + 2文字目) //
			pPlayer -> nAttack = (pPlayer -> aName[0] - pPlayer -> aName[1] + pPlayer -> aName[2]) %20
			+ (pPlayer -> aName[3] - pPlayer -> aName[0] + pPlayer -> aName[1]);

			//// 守備力の計算割り出し // (1文字目 -20 ) + (4文字目 -85) //
			pPlayer -> nDefense = (pPlayer -> aName[0] -20 ) + (pPlayer -> aName[3] -85);

			//// 回避値の計算割り出し // 4文字目 %5 //
			pPlayer -> nAvoidance = pPlayer -> aName[3] %5;
		}
		else if(nLengthWord == 5)						// 入力された文字が５文字の時
		{
			//// 体力値の計算割り出し // (1文字目 +70 - 3文字目) *4 == 体力値 //共通
			pPlayer -> nLife = (pPlayer -> aName[0] - pPlayer -> aName[2]) +70 *4;

			//// 魔力値の計算割り出し // (5文字目 + 1文字目 + 3文字目) /10 == 魔力値 //
			pPlayer -> nMagic = (pPlayer -> aName[4] + pPlayer -> aName[1] + pPlayer -> aName[2]) /12;

			//// 攻撃力の計算割り出し // (4文字目 - 2文字目 + 3文字目) %10 + (4文字目 - 1文字目 + 3文字目) //
			pPlayer -> nAttack = (pPlayer -> aName[3] - pPlayer -> aName[1] + pPlayer -> aName[2]) %20
			+ (pPlayer -> aName[3] - pPlayer -> aName[0] + pPlayer -> aName[2]);

			//// 守備力の計算割り出し // (5文字目 -20 ) + (4文字目 -85) //
			pPlayer -> nDefense = (pPlayer -> aName[4] -20 ) + (pPlayer -> aName[3] -85);

			//// 回避値の計算割り出し // 5文字目 %5 //
			pPlayer -> nAvoidance = pPlayer -> aName[4] %5;
		}
		else if(nLengthWord == 6)						// 入力された文字が６文字の時
		{
			//// 体力値の計算割り出し // (1文字目 +70 - 3文字目) *4 == 体力値 //共通
			pPlayer -> nLife = (pPlayer -> aName[0] - pPlayer -> aName[2]) +70 *4;

			//// 魔力値の計算割り出し // (3文字目 + 1文字目 + 5文字目) /10 == 魔力値 //
			pPlayer -> nMagic = (pPlayer -> aName[4] + pPlayer -> aName[1] + pPlayer -> aName[2]) /12;

			//// 攻撃力の計算割り出し // (6文字目 - 2文字目 + 6文字目) %10 + (5文字目 - 1文字目 + 3文字目) //
			pPlayer -> nAttack = (pPlayer -> aName[5] - pPlayer -> aName[1] + pPlayer -> aName[5]) %20
			+ (pPlayer -> aName[4] - pPlayer -> aName[0] + pPlayer -> aName[2]);

			//// 守備力の計算割り出し // (3文字目 -20 ) + (6文字目 -85) //
			pPlayer -> nDefense = (pPlayer -> aName[2] -20 ) + (pPlayer -> aName[5] -85);

			//// 回避値の計算割り出し // 6文字目 %5 //
			pPlayer -> nAvoidance = pPlayer -> aName[5] %5;
		}
		else if(nLengthWord == 7)						// 入力された文字が７文字の時
		{
			//// 体力値の計算割り出し // (1文字目 +70 - 3文字目) *4 == 体力値 //共通
			pPlayer -> nLife = (pPlayer -> aName[0] - pPlayer -> aName[2]) +70 *4;

			//// 魔力値の計算割り出し // (7文字目 + 1文字目 + 6文字目) /10 == 魔力値 //
			pPlayer -> nMagic = (pPlayer -> aName[6] + pPlayer -> aName[1] + pPlayer -> aName[5]) /12;

			//// 攻撃力の計算割り出し // (4文字目 - 7文字目 + 3文字目) %10 + (5文字目 - 7文字目 + 3文字目) //
			pPlayer -> nAttack = (pPlayer -> aName[3] - pPlayer -> aName[6] + pPlayer -> aName[2]) %20
			+ (pPlayer -> aName[4] - pPlayer -> aName[6] + pPlayer -> aName[2]);

			//// 守備力の計算割り出し // (7文字目 -20 ) + (3文字目 -85) //
			pPlayer -> nDefense = (pPlayer -> aName[6] -20 ) + (pPlayer -> aName[2] -85);

			//// 回避値の計算割り出し // 7文字目 %5 //
			pPlayer -> nAvoidance = pPlayer -> aName[6] %5;
		}
		else if(nLengthWord == 8)						// 入力された文字が８文字の時
		{
			//// 体力値の計算割り出し // (8文字目 +70 - 8文字目) *4 == 体力値 //共通
			pPlayer -> nLife = (pPlayer -> aName[7] - pPlayer -> aName[7]) +70 *4;

			//// 魔力値の計算割り出し // (8文字目 + 8文字目 + 8文字目) /10 == 魔力値 //
			pPlayer -> nMagic = (pPlayer -> aName[7] + pPlayer -> aName[7] + pPlayer -> aName[7]) /12;

			//// 攻撃力の計算割り出し // (8文字目 - 8文字目 + 8文字目) %10 + (8文字目 - 8文字目 + 8文字目) //
			pPlayer -> nAttack = (pPlayer -> aName[7] - pPlayer -> aName[7] + pPlayer -> aName[7]) %20
			+ (pPlayer -> aName[4] - pPlayer -> aName[7] + pPlayer -> aName[7]);

			//// 守備力の計算割り出し // (8文字目 -20 ) + (8文字目 -85) //
			pPlayer -> nDefense = (pPlayer -> aName[7] -20 ) + (pPlayer -> aName[7] -85);

			//// 回避値の計算割り出し // 8文字目 %5 //
			pPlayer -> nAvoidance = pPlayer -> aName[7] %5;
		}//if.fin
	}//強化if.fin
	
	// 名前入力時の説明
	COLOR(BLACK);
	LOCATE(21,12);
	printf("◇ 入力できる文字数は３～８文字までです！");
	LOCATE(21,14);
	printf("◇ なお、入力文字数が少なかったり多かった場合は");
	LOCATE(21,15);
	printf("  《 》内が空白になるので、そしたら入力してください！");
	LOCATE(21,16);
	printf("◇ 名前入力出来る文字は半角英数字,半角記号であれば可能です！");

	// 入力文字数が3～8以外の場合やり直し
	do
	{
		// エネミー（敵）の名前の入力 //
		LOCATE(28,6);
		COLOR(BLUE);
		printf("《 PLEASE INPUT ENEMY NAME 》");
		LOCATE(30,8);
		COLOR(BLUE);
		printf("《                     》");
		LOCATE(37,8);
		scanf("%s", &pEnemy -> aName[ZERO]);

		// アスキーコードの格納
		pName = &pEnemy -> aName[ZERO];

		// strlenは文字列の長さ(文字数)を取得する
		nLengthWord = strlen(pName);

		// 入力文字数が3～8以外の場合 bMojisu に false を代入
		if(nLengthWord < MIN_MOJI || nLengthWord > MAX_MOJI)
		{
			bMojisu = false;
			system("cls");

			// 名前入力時の説明
			COLOR(BLACK);
			LOCATE(21,12);
			printf("◇ 入力できる文字数は３～８文字までです！");
			LOCATE(21,14);
			printf("◇ なお、入力文字数が少なかったり多かった場合は");
			LOCATE(21,15);
			printf("  《 》内が空白になるので、そしたら入力してください！");
			LOCATE(21,16);
			printf("◇ 名前入力出来る文字は半角英数字,半角記号であれば可能です！");
		}
		else
		{
			bMojisu = true;
		}//if.fin

	}while(bMojisu == false);

	//// アスキーコードへ変換 ////
	nNamedata = (int) pEnemy -> aName[ZERO];

	// 入力文字判定
	nnAkira = pEnemy -> aName[0] + pEnemy -> aName[1] + pEnemy -> aName[2] + pEnemy -> aName[3] + pEnemy -> aName[4];
	nnkim   = pEnemy -> aName[0] + pEnemy -> aName[1] + pEnemy -> aName[2];

	//文字数別変換// ステータス強くなっちゃうわよ～
	if(nnAkira == 520)
	{
		pEnemy -> nLife      = 400;
		pEnemy -> nMagic     = 50;
		pEnemy -> nAttack    = 310;
		pEnemy -> nDefense   = 170;
		pEnemy -> nAvoidance = 4;
	}
	else if(nnkim == 321)
	{
		pEnemy -> nLife      = 400;
		pEnemy -> nMagic     = 50;
		pEnemy -> nAttack    = 310;
		pEnemy -> nDefense   = 170;
		pEnemy -> nAvoidance = 4;
	}
	else
	{
		if(nLengthWord == 3)							// 入力された文字が３文字の時
		{
			//// 体力値の計算割り出し // (1文字目 +70 - 3文字目) *4 == 体力値 //共通
			pEnemy -> nLife = (pEnemy -> aName[0] - pEnemy -> aName[2]) +70 *4;

			//// 魔力値の計算割り出し // (1文字目 + 2文字目 + 3文字目) /10 == 魔力値 //
			pEnemy -> nMagic = (pEnemy -> aName[0] + pEnemy -> aName[1] + pEnemy -> aName[2]) /12;

			//// 攻撃力の計算割り出し // (1文字目 - 2文字目 + 3文字目) %10 + (1文字目 - 2文字目 + 3文字目) //
			pEnemy -> nAttack = (pEnemy -> aName[0] - pEnemy -> aName[1] + pEnemy -> aName[2]) %20
			+ (pEnemy -> aName[0] - pEnemy -> aName[1] + pEnemy -> aName[2]);

			//// 守備力の計算割り出し // (3文字目 -20 ) + (2文字目 -85) //
			pEnemy -> nDefense = (pEnemy -> aName[2] -20 ) + (pEnemy -> aName[1] -85);

			//// 回避値の計算割り出し // 2文字目 %5 //
			pEnemy -> nAvoidance = pEnemy -> aName[1] %5;
		}
		else if(nLengthWord == 4)						// 入力された文字が４文字の時
		{
			//// 体力値の計算割り出し // (1文字目 +70 - 3文字目) *4 == 体力値 //共通
			pEnemy -> nLife = (pEnemy -> aName[0] - pEnemy -> aName[2]) +70 *4;

			//// 魔力値の計算割り出し // (4文字目 + 2文字目 + 3文字目) /10 == 魔力値 //
			pEnemy -> nMagic = (pEnemy -> aName[3] + pEnemy -> aName[1] + pEnemy -> aName[2]) /12;

			//// 攻撃力の計算割り出し // (1文字目 - 2文字目 + 3文字目) %10 + (4文字目 - 1文字目 + 2文字目) //
			pEnemy -> nAttack = (pEnemy -> aName[0] - pEnemy -> aName[1] + pEnemy -> aName[2]) %20
			+ (pEnemy -> aName[3] - pEnemy -> aName[0] + pEnemy -> aName[1]);

			//// 守備力の計算割り出し // (1文字目 -20 ) + (4文字目 -85) //
			pEnemy -> nDefense = (pEnemy -> aName[0] -20 ) + (pEnemy -> aName[3] -85);

			//// 回避値の計算割り出し // 4文字目 %5 //
			pEnemy -> nAvoidance = pEnemy -> aName[3] %5;
		}
		else if(nLengthWord == 5)						// 入力された文字が５文字の時
		{
			//// 体力値の計算割り出し // (1文字目 +70 - 3文字目) *4 == 体力値 //共通
			pEnemy -> nLife = (pEnemy -> aName[0] - pEnemy -> aName[2]) +70 *4;

			//// 魔力値の計算割り出し // (5文字目 + 1文字目 + 3文字目) /10 == 魔力値 //
			pEnemy -> nMagic = (pEnemy -> aName[4] + pEnemy -> aName[1] + pEnemy -> aName[2]) /12;

			//// 攻撃力の計算割り出し // (4文字目 - 2文字目 + 3文字目) %10 + (4文字目 - 1文字目 + 3文字目) //
			pEnemy -> nAttack = (pEnemy -> aName[3] - pEnemy -> aName[1] + pEnemy -> aName[2]) %20
			+ (pEnemy -> aName[3] - pEnemy -> aName[0] + pEnemy -> aName[2]);

			//// 守備力の計算割り出し // (5文字目 -20 ) + (4文字目 -85) //
			pEnemy -> nDefense = (pEnemy -> aName[4] -20 ) + (pEnemy -> aName[3] -85);

			//// 回避値の計算割り出し // 5文字目 %5 //
			pEnemy -> nAvoidance = pEnemy -> aName[4] %5;
		}
		else if(nLengthWord == 6)						// 入力された文字が６文字の時
		{
			//// 体力値の計算割り出し // (1文字目 +70 - 3文字目) *4 == 体力値 //共通
			pEnemy -> nLife = (pEnemy -> aName[0] - pEnemy -> aName[2]) +70 *4;

			//// 魔力値の計算割り出し // (3文字目 + 1文字目 + 5文字目) /10 == 魔力値 //
			pEnemy -> nMagic = (pEnemy -> aName[4] + pEnemy -> aName[1] + pEnemy -> aName[2]) /12;

			//// 攻撃力の計算割り出し // (6文字目 - 2文字目 + 6文字目) %10 + (5文字目 - 1文字目 + 3文字目) //
			pEnemy -> nAttack = (pEnemy -> aName[5] - pEnemy -> aName[1] + pEnemy -> aName[5]) %20
			+ (pEnemy -> aName[4] - pEnemy -> aName[0] + pEnemy -> aName[2]);

			//// 守備力の計算割り出し // (3文字目 -20 ) + (6文字目 -85) //
			pEnemy -> nDefense = (pEnemy -> aName[2] -20 ) + (pEnemy -> aName[5] -85);

			//// 回避値の計算割り出し // 6文字目 %5 //
			pEnemy -> nAvoidance = pEnemy -> aName[5] %5;
		}
		else if(nLengthWord == 7)						// 入力された文字が７文字の時
		{
			//// 体力値の計算割り出し // (1文字目 +70 - 3文字目) *4 == 体力値 //共通
			pEnemy -> nLife = (pEnemy -> aName[0] - pEnemy -> aName[2]) +70 *4;

			//// 魔力値の計算割り出し // (7文字目 + 1文字目 + 6文字目) /10 == 魔力値 //
			pEnemy -> nMagic = (pEnemy -> aName[6] + pEnemy -> aName[1] + pEnemy -> aName[5]) /12;

			//// 攻撃力の計算割り出し // (4文字目 - 7文字目 + 3文字目) %10 + (5文字目 - 7文字目 + 3文字目) //
			pEnemy -> nAttack = (pEnemy -> aName[3] - pEnemy -> aName[6] + pEnemy -> aName[2]) %20
			+ (pEnemy -> aName[4] - pEnemy -> aName[6] + pEnemy -> aName[2]);

			//// 守備力の計算割り出し // (7文字目 -20 ) + (3文字目 -85) //
			pEnemy -> nDefense = (pEnemy -> aName[6] -20 ) + (pEnemy -> aName[2] -85);

			//// 回避値の計算割り出し // 7文字目 %5 //
			pEnemy -> nAvoidance = pEnemy -> aName[6] %5;
		}
		else if(nLengthWord == 8)						// 入力された文字が８文字の時
		{
			//// 体力値の計算割り出し // (8文字目 +70 - 8文字目) *4 == 体力値 //共通
			pEnemy -> nLife = (pEnemy -> aName[7] - pEnemy -> aName[7]) +70 *4;

			//// 魔力値の計算割り出し // (8文字目 + 8文字目 + 8文字目) /10 == 魔力値 //
			pEnemy -> nMagic = (pEnemy -> aName[7] + pEnemy -> aName[7] + pEnemy -> aName[7]) /12;

			//// 攻撃力の計算割り出し // (8文字目 - 8文字目 + 8文字目) %10 + (8文字目 - 8文字目 + 8文字目) //
			pEnemy -> nAttack = (pEnemy -> aName[7] - pEnemy -> aName[7] + pEnemy -> aName[7]) %20
			+ (pEnemy -> aName[4] - pEnemy -> aName[7] + pEnemy -> aName[7]);

			//// 守備力の計算割り出し // (8文字目 -20 ) + (8文字目 -85) //
			pEnemy -> nDefense = (pEnemy -> aName[7] -20 ) + (pEnemy -> aName[7] -85);

			//// 回避値の計算割り出し // 8文字目 %5 //
			pEnemy -> nAvoidance = pEnemy -> aName[7] %5;
		}//if.fin
	}//強化if.fin

	CLS(H_RED,BLACK);

	//値をmainに返す
	return 0;
}

/*******************************************************************************
 データ出力関数
*******************************************************************************/
int Output( PLAYER *pPlayer, INITIAL *pInitial, ENEMY *pEnemy)
{
	// 変数宣言
	int nkey;
	int nVer = 4;
	int nHor = 45;
	int nColor = H_GREEN;										// 枠への着色

	system("cls");												// 前画面のクリア

	StatusFrame( nColor );										// 専用枠の使用

	LOCATE(8,2);
	COLOR(LIME,BLACK);
	printf("～～～ ステータス ～～～");

	Mario();													// アスキーアート「 マリオ 」

	LOCATE(43,2);
	COLOR(H_RED,WHITE);
	printf("～ YOUR ～");

	LOCATE(43,12);
	COLOR(BLUE);
	printf("～ ENEMY ～");

	// プレイヤーとエネミーのステイタスの表示
	COLOR(BLACK);
	LOCATE(nHor, nVer++);
	printf("《  %s  》",pPlayer -> aName);						// プレイヤーの名前の出力
	LOCATE(nHor, nVer++);
	printf("――――――――――――――――");
	LOCATE(nHor, nVer++);
	printf(" ◇体力値 → %3d ＋ %3d > %3d",pPlayer -> nLife, BASE_LIFE, pPlayer -> nLife + BASE_LIFE);						// 体力値の出力
	LOCATE(nHor, nVer++);
	printf(" ◇魔力値 → %3d ＋ %3d > %3d",pPlayer -> nMagic, BASE_MAGIC, pPlayer -> nMagic + BASE_MAGIC);					// 魔力値の出力
	LOCATE(nHor, nVer++);
	printf(" ◇攻撃力 → %3d ＋ %3d > %3d",pPlayer -> nAttack, BASE_ATTACK, pPlayer -> nAttack + BASE_ATTACK);				// 攻撃値の出力
	LOCATE(nHor, nVer++);
	printf(" ◇守備力 → %3d ＋ %3d > %3d",pPlayer -> nDefense, BASE_DEFENSE, pPlayer -> nDefense + BASE_DEFENSE);			// 守備値の出力
	LOCATE(nHor, nVer++);
	printf(" ◇回避値 → %3d ＋ %3d > %3d",pPlayer -> nAvoidance, BASE_AVOIDANCE, pPlayer -> nAvoidance + BASE_AVOIDANCE);	// 回避値の出力
	LOCATE(nHor, nVer++);
	printf("――――――――――――――――");

	nVer++;														// １１行目
	nVer++;														// １２行目 次は１３行目から

	LOCATE(nHor, nVer++);
	printf("《  %s  》",pEnemy -> aName);						// エネミーの名前の出力
	LOCATE(nHor, nVer++);
	printf("――――――――――――――――");
	LOCATE(nHor, nVer++);
	printf(" ◇体力値 → %3d ＋ %3d > %3d",pEnemy -> nLife, BASE_LIFE, pEnemy -> nLife + BASE_LIFE);						// 体力値の出力
	LOCATE(nHor, nVer++);
	printf(" ◇魔力値 → %3d ＋ %3d > %3d",pEnemy -> nMagic, BASE_MAGIC, pEnemy -> nMagic + BASE_MAGIC);					// 魔力値の出力
	LOCATE(nHor, nVer++);
	printf(" ◇攻撃力 → %3d ＋ %3d > %3d",pEnemy -> nAttack, BASE_ATTACK, pEnemy -> nAttack + BASE_ATTACK);				// 攻撃値の出力
	LOCATE(nHor, nVer++);
	printf(" ◇守備力 → %3d ＋ %3d > %3d",pEnemy -> nDefense, BASE_DEFENSE, pEnemy -> nDefense + BASE_DEFENSE);			// 守備値の出力
	LOCATE(nHor, nVer++);
	printf(" ◇回避値 → %3d ＋ %3d > %3d",pEnemy -> nAvoidance, BASE_AVOIDANCE, pEnemy -> nAvoidance + BASE_AVOIDANCE);	// 回避値の出力
	LOCATE(nHor, nVer++);
	printf("――――――――――――――――");

	// プレイヤーのステイタス初期値の代入
	pInitial -> nLife       = pPlayer -> nLife      + BASE_LIFE;		// 体力値の初期値の代入
	pInitial -> nMagic      = pPlayer -> nMagic     + BASE_MAGIC;		// 魔力値の初期値の代入
	pInitial -> nAttack     = pPlayer -> nAttack    + BASE_ATTACK;		// 攻撃力の初期値の代入
	pInitial -> nDefense    = pPlayer -> nDefense   + BASE_DEFENSE;		// 守備力の初期値の代入
	pInitial -> nAvoidance  = pPlayer -> nAvoidance + BASE_AVOIDANCE;	// 回避値の初期値の代入

	// エネミーのステイタスの代入
	pEnemy -> nLife += BASE_LIFE;										// 体力値の代入
	pEnemy -> nMagic += BASE_MAGIC;										// 魔力値の代入
	pEnemy -> nAttack += BASE_ATTACK;									// 攻撃力の代入
	pEnemy -> nDefense += BASE_DEFENSE;									// 守備力の代入
	pEnemy -> nAvoidance += BASE_AVOIDANCE;								// 回避値の代入

	while(1)
	{
		COLOR(WHITE,LIME);
		LOCATE(52,23);
		printf("～ Please Enter ～");
		 WAIT(300);						// 0.3secの時間待ち 
		INKEY(nkey);					// 何かキーが押されていたら変数に値を入力する 
		if (nkey == 0xd) break;			// 何か押されたら終了する 

		COLOR(LIME,H_CYAN);
		LOCATE(52,23);
		printf("～ Please Enter ～");
		WAIT(300);						// 0.3secの時間待ち 
		INKEY(nkey);					// 何かキーが押されていたら変数に値を入力する 
		if (nkey == 0xd) break;			// 何か押されたら終了する 
	}

	// 値を返す
	return 0;
}

/*******************************************************************************
* ランダム整数の作成する関数
*******************************************************************************/
int GetRandom(int nMin,int nMax)
{
	return nMin+(int)(rand()*(nMax-nMin+1)/(1+RAND_MAX));
}

/*******************************************************************************
 フレームにステイタス表示関数
*******************************************************************************/
void Status(PLAYER *pPlayer)
{
	// 変数宣言(座標のみの使用)
	int nCnt  = ZERO;
	int nVerAvi = 22;
	int nHorAvi = 68;
	int nVerLMT = 2;
	int nHorLif = 23;
	int nHorMag = 55;
	int nLife  = ZERO;
	int nMagic = ZERO;

	// ステイタスの表示
	LOCATE(5,2);
	printf(" %s", pPlayer -> aName);				// 名前
	LOCATE(72,19);
	printf(" %d", pPlayer -> nAttack);				// 攻撃力
	LOCATE(72,20);
	printf(" %d", pPlayer -> nDefense);				// 守備力

	// ゲージ塗りつぶし（回避値用）
	LOCATE(nHorAvi, nVerAvi);
	BACKCOLOR(BLACK);
	printf("        ");

	// ゲージ型ステイタスの表示（回避地用）
	for(nCnt = ZERO; nCnt < pPlayer -> nAvoidance; nCnt++)
	{
		LOCATE(nHorAvi++, nVerAvi);
		COLOR(H_CYAN);
		printf("#");
	}//for.fin

	// ゲージ塗りつぶし（体力値用）
	LOCATE(nHorLif, nVerLMT);
	BACKCOLOR(BLACK);
	printf("　　　　　　　　　　");

	if(pPlayer -> nLife > 900)						// 体力が 900 以上の場合
	{
		nLife = 10;									// 値の代入

		// ゲージ型ステイタスの表示（体力値用）
		for(nCnt = ZERO; nCnt < nLife; nCnt++)		// 値ぶん回して表示
		{
			LOCATE(nHorLif++, nVerLMT);
			BACKCOLOR(H_RED);
			printf("　");
		}//for.fin
	}
	else if(pPlayer -> nLife > 800)					// 体力が 800 以上の場合
	{
		nLife = 9;									// 値の代入

		// ゲージ型ステイタスの表示（体力値用）
		for(nCnt = ZERO; nCnt < nLife; nCnt++)		// 値ぶん回して表示
		{
			LOCATE(nHorLif++, nVerLMT);
			BACKCOLOR(H_RED);
			printf("　");
		}//for.fin
	}else if(pPlayer -> nLife > 700)					// 体力が 700 以上の場合
	{
		nLife = 8;									// 値の代入

		// ゲージ型ステイタスの表示（体力値用）
		for(nCnt = ZERO; nCnt < nLife; nCnt++)		// 値ぶん回して表示
		{
			LOCATE(nHorLif++, nVerLMT);
			BACKCOLOR(H_RED);
			printf("　");
		}//for.fin
	}
	else if(pPlayer -> nLife > 600)					// 体力が 600 以上の場合
	{
		nLife = 7;									// 値の代入

		// ゲージ型ステイタスの表示（体力値用）
		for(nCnt = ZERO; nCnt < nLife; nCnt++)		// 値ぶん回して表示
		{
			LOCATE(nHorLif++, nVerLMT);
			BACKCOLOR(H_RED);
			printf("　");
		}//for.fin
	}
	else if(pPlayer -> nLife > 500)					// 体力が 500 以上の場合
	{
		nLife = 6;									// 値の代入

		// ゲージ型ステイタスの表示（体力値用）
		for(nCnt = ZERO; nCnt < nLife; nCnt++)		// 値ぶん回して表示
		{
			LOCATE(nHorLif++, nVerLMT);
			BACKCOLOR(H_RED);
			printf("　");
		}//for.fin
	}
	else if(pPlayer -> nLife > 400)					// 体力が 400 以上の場合
	{
		nLife = 5;									// 値の代入

		// ゲージ型ステイタスの表示（体力値用）
		for(nCnt = ZERO; nCnt < nLife; nCnt++)		// 値ぶん回して表示
		{
			LOCATE(nHorLif++, nVerLMT);
			BACKCOLOR(H_RED);
			printf("　");
		}//for.fin
	}
	else if(pPlayer -> nLife > 300)					// 体力が 300 以上の場合
	{
		nLife = 4;									// 値の代入

		// ゲージ型ステイタスの表示（体力値用）
		for(nCnt = ZERO; nCnt < nLife; nCnt++)		// 値ぶん回して表示
		{
			LOCATE(nHorLif++, nVerLMT);
			BACKCOLOR(H_RED);
			printf("　");
		}//for.fin
	}
	else if(pPlayer -> nLife > 200)					// 体力が 200 以上の場合
	{
		nLife = 3;									// 値の代入

		// ゲージ型ステイタスの表示（体力値用）
		for(nCnt = ZERO; nCnt < nLife; nCnt++)		// 値ぶん回して表示
		{
			LOCATE(nHorLif++, nVerLMT);
			BACKCOLOR(H_RED);
			printf("　");
		}//for.fin
	}
	else if(pPlayer -> nLife > 100)					// 体力が 100 以上の場合
	{
		nLife = 2;									// 値の代入

		// ゲージ型ステイタスの表示（体力値用）
		for(nCnt = ZERO; nCnt < nLife; nCnt++)		// 値ぶん回して表示
		{
			LOCATE(nHorLif++, nVerLMT);
			BACKCOLOR(H_RED);
			printf("　");
		}//for.fin
	}
	else if(pPlayer -> nLife < 101)					// 体力が 101 以下の場合
	{
		nLife = 1;									// 値の代入

		// ゲージ型ステイタスの表示（体力値用）
		for(nCnt = ZERO; nCnt < nLife; nCnt++)		// 値ぶん回して表示
		{
			LOCATE(nHorLif++, nVerLMT);
			BACKCOLOR(H_RED);
			printf("　");
		}//for.fin
	}//if.fin

	LOCATE(23, nVerLMT);
	COLOR(WHITE);
	printf("%d", pPlayer -> nLife );

	// ゲージ塗りつぶし（魔力値用）
	LOCATE(nHorMag, nVerLMT);
	BACKCOLOR(BLACK);
	printf("　　　　　　　　　　");

	if(pPlayer -> nMagic > 90)						// 魔力が 90 以上の場合
	{
		nMagic = 10;								// 値の代入

		// ゲージ型ステイタスの表示（魔力値用）
		for(nCnt = ZERO; nCnt < nMagic; nCnt++)		// 値ぶん回して表示
		{
			LOCATE(nHorMag++, nVerLMT);
			BACKCOLOR(BLUE);
			printf("　");
		}
	}
	else if(pPlayer -> nMagic > 80)					// 魔力が 80 以上の場合
	{
		nMagic = 9;									// 値の代入

		// ゲージ型ステイタスの表示（魔力値用）
		for(nCnt = ZERO; nCnt < nMagic; nCnt++)		// 値ぶん回して表示
		{
			LOCATE(nHorMag++, nVerLMT);
			BACKCOLOR(BLUE);
			printf("　");
		}
	}
	else if(pPlayer -> nMagic > 70)					// 魔力が 70 以上の場合
	{
		nMagic = 8;									// 値の代入

		// ゲージ型ステイタスの表示（魔力値用）
		for(nCnt = ZERO; nCnt < nMagic; nCnt++)		// 値ぶん回して表示
		{
			LOCATE(nHorMag++, nVerLMT);
			BACKCOLOR(BLUE);
			printf("　");
		}
	}
	else if(pPlayer -> nMagic > 60)					// 魔力が 60 以上の場合
	{
		nMagic = 7;									// 値の代入

		// ゲージ型ステイタスの表示（魔力値用）
		for(nCnt = ZERO; nCnt < nMagic; nCnt++)		// 値ぶん回して表示
		{
			LOCATE(nHorMag++, nVerLMT);
			BACKCOLOR(BLUE);
			printf("　");
		}
	}
	else if(pPlayer -> nMagic > 50)					// 魔力が 50 以上の場合
	{
		nMagic = 6;									// 値の代入

		// ゲージ型ステイタスの表示（魔力値用）
		for(nCnt = ZERO; nCnt < nMagic; nCnt++)		// 値ぶん回して表示
		{
			LOCATE(nHorMag++, nVerLMT);
			BACKCOLOR(BLUE);
			printf("　");
		}
	}
	else if(pPlayer -> nMagic > 40)					// 魔力が 40 以上の場合
	{
		nMagic = 5;									// 値の代入

		// ゲージ型ステイタスの表示（魔力値用）
		for(nCnt = ZERO; nCnt < nMagic; nCnt++)		// 値ぶん回して表示
		{
			LOCATE(nHorMag++, nVerLMT);
			BACKCOLOR(BLUE);
			printf("　");
		}
	}
	else if(pPlayer -> nMagic > 30)					// 魔力が 30 以上の場合
	{
		nMagic = 4;									// 値の代入

		// ゲージ型ステイタスの表示（魔力値用）
		for(nCnt = ZERO; nCnt < nMagic; nCnt++)		// 値ぶん回して表示
		{
			LOCATE(nHorMag++, nVerLMT);
			BACKCOLOR(BLUE);
			printf("　");
		}
	}
	else if(pPlayer -> nMagic > 20)					// 魔力が 20 以上の場合
	{
		nMagic = 3;									// 値の代入

		// ゲージ型ステイタスの表示（魔力値用）
		for(nCnt = ZERO; nCnt < nMagic; nCnt++)		// 値ぶん回して表示
		{
			LOCATE(nHorMag++, nVerLMT);
			BACKCOLOR(BLUE);
			printf("　");
		}
	}
	else if(pPlayer -> nMagic > 10)					// 魔力が 10 以上の場合
	{
		nMagic = 2;									// 値の代入

		// ゲージ型ステイタスの表示（魔力値用）
		for(nCnt = ZERO; nCnt < nMagic; nCnt++)		// 値ぶん回して表示
		{
			LOCATE(nHorMag++, nVerLMT);
			BACKCOLOR(BLUE);
			printf("　");
		}
	}
	else if(pPlayer -> nMagic < 11)					// 魔力が 11 以下の場合
	{
		nMagic = 1;									// 値の代入

		// ゲージ型ステイタスの表示（魔力値用）
		for(nCnt = ZERO; nCnt < nMagic; nCnt++)		// 値ぶん回して表示
		{
			LOCATE(nHorMag++, nVerLMT);
			BACKCOLOR(BLUE);
			printf("　");
		}
	}//if.fin

	LOCATE(55, nVerLMT);
	COLOR(WHITE);
	printf("%d", pPlayer -> nMagic);

	COLOR(WHITE, BLACK);
	LOCATE(5,19);
	printf("→");
	LOCATE(5,20);
	printf("　");
	LOCATE(5,21);
	printf("　");
}

/*******************************************************************************
 相手の名前の表示関数
*******************************************************************************/
void Name(ENEMY *pEnemy)
{
	LOCATE(18,20);
	COLOR(WHITE,BLACK);
	printf("《 %s 》が現れた！！！", &pEnemy -> aName);

}

/*******************************************************************************
 先攻後攻ッピ！関数
*******************************************************************************/
int Order( PLAYER *pPlayer, ENEMY *pEnemy )
{
	// 変数宣言
	int nOrder = ZERO;

	// 回避値の高い方から先制 //
	if(pPlayer -> nAvoidance > pEnemy -> nAvoidance)		// プレイヤーの先制 //
	{
		nOrder = ONE;										// 1を返す
	}
	else if(pEnemy -> nAvoidance > pPlayer -> nAvoidance)	// エネミーの先制 //
	{
		nOrder = ZERO;										// 0を返す
	}
	else if(pEnemy -> nAvoidance == pPlayer -> nAvoidance)	// エネミーの先制 //
	{
		nOrder = ONE;										// 1を返す
	}//if.fin

	// 値を返す //
	return nOrder;
}

/*******************************************************************************
 フレームカラー関数
*******************************************************************************/
int FrameColor( PLAYER *pPlayer )
{
	// 変数宣言
	int nColor = ZERO;

	// 条件別着色
	if(pPlayer -> nLife > 400)								// プレイヤーの体力が400以上の場合
	{
		nColor = ZERO;										// バトル用フレームの着色：白
	}
	if(pPlayer -> nLife <= 399)								// プレイヤーの体力が399以下の場合
	{
		nColor = 1;											// バトル用フレームの着色：黄色
	}
	if(pPlayer -> nLife <= 200)								// プレイヤーの体力が200以下の場合
	{
		nColor = 2;											// バトル用フレームの着色：赤
	}//if.fin

	// 値を返す
	return nColor;
}

/*******************************************************************************
 勝敗判定関数
*******************************************************************************/
int Judge( PLAYER *pPlayer, ENEMY *pEnemy)
{
	// 変数宣言
	int nJudeg = ZERO;

	// 判定
	if(pPlayer -> nLife <= 0 )			// プレイヤーの体力が0以下の場合
	{
		nJudeg = ONE;					// 1を返す
	}
	else if(pEnemy -> nLife <= 0)		// エネミーの体力が0以下の場合
	{
		nJudeg = ZERO;					// 0を返す
	}
	else								// 続く場合
	{
		nJudeg = 2;						// 2を返す
	}//if.fin

	// 値を返す
	return nJudeg;
}

/*******************************************************************************
 ドラキー変化関数
*******************************************************************************/
int DorakiIllusion( ENEMY *pEnemy )
{
	// 変数宣言
	int nDorakiIllusion = ZERO;

	//判定
	if(pEnemy -> nLife > 500)								// 体力が 500 以上の場合
	{
		nDorakiIllusion = 1;								// 判定１
	}
	if(pEnemy -> nLife < 499)								// 体力が 499 以上の場合
	{
		nDorakiIllusion = 2;								// 判定２
	}
	if(pEnemy -> nLife < 200)								// 体力が 200 未満の場合
	{
		nDorakiIllusion = 3;								// 判定３
	}//if.fin

	// 値を返す
	return nDorakiIllusion;
}

/*******************************************************************************
 エンディング関数
*******************************************************************************/
void Ending(PLAYER *pPlayer, ENEMY *pEnemy, int nJudge, int nWarpiru, int nTurnCount)
{
	// 変数宣言
	int nMP3Handle = ZERO;

	// 勝てばハッピーエンド！ 負ければバッドエンド！ //
	Enter();					// プリーズエンター

	if(nJudge == ZERO)			// ハッピーエンド！
	{
		Koromaku();					// 黒幕発動

		// 効果音の再生
		nMP3Handle = OPENMP3("Winner.mp3");						// オープン & 初期化
		PLAYMP3(nMP3Handle);									// 繰り返し再生

		Koromaku();				// 黒幕をかける
		LOCATE(18,20);
		printf("《 %s 》は《 %s 》に勝利した！！！", pPlayer -> aName, pEnemy -> aName);

	}
	else if(nJudge == ONE)		// バッドエンド！
	{
		// 効果音の再生
		nMP3Handle = OPENMP3("Loose.mp3");						// オープン & 初期化
		PLAYMP3(nMP3Handle);									// 繰り返し再生

		LOCATE(18,20);
		printf("《 %s 》は《 %s 》に敗北した！！！", pPlayer -> aName, pEnemy -> aName);
	}//if.fin

	Enter();					// プリーズエンター

	CLOSEMP3(nMP3Handle);										// クローズ & 停止

	NormalWarp( nWarpiru );		// ワープ

	// 効果音の再生
	nMP3Handle = OPENMP3("EndingTheme.mp3");				// オープン & 初期化
	PLAYMP3(nMP3Handle);									// 繰り返し再生

	// エンディング //
	if(nJudge == ZERO)			// ハッピーエンド
	{
		CLS(BLACK,WHITE);

		SuraimDarkMove();		// スライムダーク

		if(nTurnCount <= 4)
		{
			LOCATE(22,2);
			COLOR(H_RED);
			printf("〔 %d ターン撃破！！！〕すごいよ！！！！", nTurnCount);
		}
		if(nTurnCount >= 5)
		{
			LOCATE(22,2);
			COLOR(H_RED);
			printf("〔 %d ターン撃破！！！〕おめでとう！！！", nTurnCount);
		}
		if(nTurnCount >= 7)
		{
			LOCATE(22,2);
			COLOR(H_RED);
			printf("〔 %d ターン撃破！！！〕まだまだだね！", nTurnCount);
		}

		LOCATE(18,20);
		printf("《 %s 》...", pPlayer -> aName);
		COLOR(H_RED);
		LOCATE(20,21);
		printf("Thank You Playing This Game!!!");
	}
	else if(nJudge == ONE)		// エンド
	{
		CLS(WHITE,BLACK);

		Mario();				// マリオ

		LOCATE(18,20);
		printf("《 %s 》...", pPlayer -> aName);
		LOCATE(20,21);
		printf("マンマミ～ア");

	}//if.fin

	Enter();					// プリーズエンター

	CLOSEMP3(nMP3Handle);										// クローズ & 停止

	NormalWarp( nWarpiru );		// ワープ
}


