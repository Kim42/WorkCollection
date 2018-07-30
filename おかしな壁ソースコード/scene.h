/*=============================================================================

 シーン共通ヘッダ[ scene.h ]

=============================================================================*/
/*-----------------------------------------------------------------------------
 インクルードガード
-----------------------------------------------------------------------------*/
#ifndef _SCENE_H_
#define _SCENE_H_

/*-----------------------------------------------------------------------------
 インクルードファイル
-----------------------------------------------------------------------------*/

// デバイス取得用
#include "manager.h"
#include "renderer.h"
#include "texture.h"

/*-----------------------------------------------------------------------------
 マクロ定義
-----------------------------------------------------------------------------*/
#define NUM_SCENE     (128)		// オブジェクト数
#define NUM_VERTEX    (4)		// 頂点数
#define NUM_PRIMITIVE (2)		// プリミティブ数

/*-----------------------------------------------------------------------------
 オブジェクトタイプ列挙型定義
-----------------------------------------------------------------------------*/
enum OBJTYPE
{
	TYPE_NONE = -1,		// なし
	TYPE_PLAYER,		// プレイヤー
	TYPE_WALL,			// ウォール
	TYPE_FIELD,			// フィールド
	TYPE_ITEM,			// アイテム
	TYPE_SWITCH,		// スイッチ
	TYPE_TIMER,			// タイマー
	TYPE_COLLECTER,		// コレクター
	TYPE_HALFFADE,		// ハーフフェード
	TYPE_TEXTTEXTURE,	// テキストテクスチャ

	OBJTYPE_MAX			// 最大数
};

/*-----------------------------------------------------------------------------
 クラス定義
-----------------------------------------------------------------------------*/
class CScene
{
	private:

		// シーンオブジェクト
		static CScene *m_apScene[NUM_SCENE];

		// シーンオブジェクト数の管理
		static int m_nNumScene;

		// 生成されるシーンオブジェクト識別番号
		int m_nID;

		// オブジェクトタイプ
		OBJTYPE m_objType;

	protected:

		// 頂点バッファインターフェース
		LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;

		// ポジション
		D3DXVECTOR3 m_Pos;

		// サイズ
		D3DXVECTOR3 m_Size;

		// テクスチャ
		int m_nTexType;

		// 解放処理関数
		void Release(void);

	public:

		// コンストラクタ & デスクトラクタ
		CScene();
		virtual ~CScene() {}

		// 各処理純粋仮想関数
		virtual HRESULT Init  (void){ return S_OK; }
		virtual void    Uninit(void) = 0;
		virtual void    Update(void) = 0;
		virtual void    Draw  (void) = 0;

		// 静的統括処理関数
		static void UpdateAll (void);
		static void DrawAll   (void);
		static void ReleaseAll(void);

		// オブジェクト識別番号取得関数
		static CScene *GetScene(int nIdxScene) { return m_apScene[nIdxScene]; }

		// オブジェクトタイプの設定
		void SetObjType(OBJTYPE objType) { m_objType = objType; }

		// オブジェクトタイプの取得
		OBJTYPE GetObjType(void) { return m_objType; }

		// オブジェクト総数の取得
		static int GetNumObj(void) { return m_nNumScene; }

		// オブジェクト固有のデータの取得
		D3DXVECTOR3 GetPos (void)    { return m_Pos; }
		D3DXVECTOR3 GetSize(void)    { return m_Size; }
		int         GetTexType(void) { return m_nTexType; }

		// オブジェクト固有のデータの反映
		void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }

		void SetPosMouse(D3DXVECTOR3 pos)
		{
			m_Pos.x = pos.x - m_Size.x * 0.5f;
			m_Pos.y = pos.y - m_Size.y * 0.5f;
		}//end

};

/*-----------------------------------------------------------------------------
 インクルードエンド
-----------------------------------------------------------------------------*/
#endif
