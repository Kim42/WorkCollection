/*******************************************************************************
* タイトル:		フィールドヘッダ
* プログラム名:		field.h
* 作成者:		CP11SATA  15  Kim Nakamura
* 作成日:		2016/02/20
********************************************************************************
* 更新履歴:		- 2016/02/20　Kim Nakamura
*			- V1.01　Initial Version
*				・フィールドに要素番号の振り分けのマクロ定義
*		3/4	・コースのプロトタイプ宣言の追加
*******************************************************************************/
/*******************************************************************************
* 二重インクルードの防止 
*******************************************************************************/
#ifndef _FIELD_H_
#define _FIELD_H_

/*******************************************************************************
* インクルードファイル
*******************************************************************************/


/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define WALL_XMIN        (1)	// 最低壁位置
#define WALL_MAX        (79)	// 最大壁位置
#define WALL_XMAX        (80)	// 最大壁位置
#define MAX_HORAIZONTAL  (40)	// ２バイト文字最大Ｘ軸
#define MAX_VERTICAL     (25)	// ２バイト文字最大Ｙ軸

#define BLOCK            (1)	// フィールド要素が（１）
#define SLOPE            (2)	// フィールド要素が（２）
#define COURSE           (3)	// フィールド要素が（３）

#define GOOD             (4)	// フィールド要素が（４）
#define VERYGOOD         (5)	// フィールド要素が（５）
#define EXCELLENT        (6)	// フィールド要素が（６）

#define S_GOOD           (7)	// フィールド要素が（７）
#define S_VERYGOOD       (8)	// フィールド要素が（８）
#define S_EXCELLENT      (9)	// フィールド要素が（９）

#define STAR             (10)	// フィールド要素が（１０）
#define SPACE            (0)	// フィールド要素が（０）

/*******************************************************************************
* 構造体定義
*******************************************************************************/
typedef struct
{
	int nPosition[MAX_VERTICAL][MAX_HORAIZONTAL];	// フィールドの要素位置
	int nCnt;
	int nCntSec;
	int nRanking;									// ランキングを通り過ぎた順でとる

	bool bStart;									// スタート判定
	bool bPlay;										// ゲーム判定
	bool bTitle;									// タイトルの判定
}FIELD;												// 配列で作ったフィールドの当たり判定専用構造体

/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
void InitField   ( void );
void UpdateField ( void );
void DrawField   ( void );
void UninitField ( void );

// レース用フィールドの表示
void RaceFieldStart ( void );		// スタート画面
void RaceField_40_79_and_320_359_and_640_679   ( void );	// コース（配列 40〜79,320〜359,640〜679に格納分） ０１and０８and１６：ふつう
void RaceField_80_119_and_360_399_and_440_479  ( void );	// コース（配列 80〜119,360〜399,440〜479に格納分）０２and０９and１１：加速地１
void RaceField_120_159_and_480_519             ( void );	// コース（配列120〜159,480〜519に格納分）         ０３and１２：休憩地１
void RaceField_160_199_and_520_559_and_680_719 ( void );	// コース（配列160〜199,520〜559,680〜719に格納分）０４and１３and１７：ふつう
void RaceField_200_239_and_400_439             ( void );	// コース（配列200〜239,400〜439に格納分）         ０５and１０：ふつう
void RaceField_240_279_and_560_599             ( void );	// コース（配列240〜279,560〜599に格納分）         ０６and１４：加速地２
void RaceField_280_319_and_600_639             ( void );	// コース（配列280〜319,600〜639に格納分）         ０７and１５：休憩地２
void RaceField_720_739                         ( void );	// コース（配列720〜739に格納分）                  １８：スパートポイント地
void RaceFieldGoal    ( void );		// ゴール画面

// タイトル関数
void title( void );

// 結果発表
void result( void );

// 構造体フィールド情報のコピーを公開
FIELD *GetField( void );

/*******************************************************************************
 インクルードファイルの二重インクルードの防止の閉じ
*******************************************************************************/
#endif

