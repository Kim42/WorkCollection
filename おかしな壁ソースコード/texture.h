/*=============================================================================

 テクスチャ管理ヘッダ[ texture.h ]

=============================================================================*/
/*-----------------------------------------------------------------------------
 インクルードガード
-----------------------------------------------------------------------------*/
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

/*-----------------------------------------------------------------------------
 テクスチャ列挙型定義
-----------------------------------------------------------------------------*/
enum TEXTURE
{
	NEUTRAL = 0,		// ニュートラル
	WALK1,				// 歩き１
	WALK2,				// 歩き２
	JUMP,				// ジャンプ
	BAD,				// 失敗
	PUSH1,				// 押す１
	PUSH2,				// 押す２
	GOGOAL1,			// 後ろ姿１
	GOGOAL2,			// 後ろ姿２

	YUKA,				// 床

	SWITCHANIMETION0,	// スイッチのアニメーション：上
	SWITCHANIMETION1,	// スイッチのアニメーション：下
	SWITCHANIMETION2,	// スイッチのアニメーション：左
	SWITCHANIMETION3,	// スイッチのアニメーション：右

	WALL_SWAP,			// 壁：スワップ
	WALL_COPY,			// 壁：コピー
	WALL_SYNC,			// 壁：シンクロ

	SHUTTER1,			// シャッター１
	SHUTTER2,			// シャッター２
	SHUTTER3,			// シャッター３
	GOAL_BACK,			// ゴール背景

	COLLECT_A,			// コレクトアイテム：ビスケット
	COLLECT_B,			// コレクトアイテム：キャンディー
	COLLECT_C,			// コレクトアイテム：チョコレート

	MILLEF_BLOCK,		// ミルフィーユブロック

	NEEDLE,				// ニードル

	SIGNBOARD_TOP,		// 矢印：上
	SIGNBOARD_BOTTOM,	// 矢印：下
	SIGNBOARD_LEFT,		// 矢印：左
	SIGNBOARD_RIGHT,	// 矢印：右

	TIME_CLOCK,			// 時計
	TIME_NUMBER,		// タイム数字

	COUNT_ICON,			// カウントアイコン
	COUNT_KAKERU,		// カウント×
	COUNT_NUMBER,		// カウント数字

	SWEET_BG,			// ゲーム背景

	GOAL_FRAME,			// ゴールフレーム
	EXIT_ICON,			// 出口アイコン

	STAGESELECT000,		// ステージセレクト０
	STAGESELECT001,		// ステージセレクト１
	STAGESELECT002,		// ステージセレクト２
	STAGESELECT003,		// ステージセレクト３

	TITLE,				// タイトルロゴ

	SWEET_BG2,			// 背景

	GOOD,				// プレイヤー：喜ぶ
	TEX_FADE,			// フェード用

	CLEAR,				// クリア文字
	FAILED,				// フェイル文字
	NEXT_STAGE,			// 次のステージ
	STAGE_SELECT,		// ステージセレクト
	RETRY,				// リトライ
	SELECT,				// セレクトアイコン

	START,				// スタート文字
	OK,					// きめる文字

	STAGESELECT004,		// ステージセレクト４
	STAGESELECT005,		// ステージセレクト５
	STAGESELECT006,		// ステージセレクト６

};

/*-----------------------------------------------------------------------------
 クラス定義
-----------------------------------------------------------------------------*/
class CTexture
{
	private:

		// テクスチャインターフェース
		static LPDIRECT3DTEXTURE9 *m_pTextureEx;

	public:

		// テクスチャ枚数
		static int m_nNumTexture;

		// 各処理関数
		static HRESULT Load(void);
		static void    Release(void);

		// テクスチャデータの取得関数
		static LPDIRECT3DTEXTURE9 GetAdr(int ntype) { return &*m_pTextureEx[ntype]; }

};

/*-----------------------------------------------------------------------------
 インクルードエンド
-----------------------------------------------------------------------------*/
#endif
