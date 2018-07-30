/*============================================================================

ポリゴン表示[scene.h]

Author: Miyu Ishikawa
Date: 2017/04/26

=============================================================================*/
#ifndef _MODE_H_	     // ２重インクルード防止のマクロ定義
#define _MODE_H_

/*******************************************************************************
* インクルードファイル
*******************************************************************************/

/*******************************************************************************
* マクロ定義
*******************************************************************************/

/*******************************************************************************
* 前方宣言
*******************************************************************************/
class CCamera;
class CLight;

/*******************************************************************************
* クラス定義
*******************************************************************************/

class CMode
{
public:
	virtual void Init( void ){}	// 初期化
	virtual void Init( int ){}
	virtual void Uninit( void ) = 0;								// 終了
	virtual void Update( void ) = 0;								// 更新
	virtual void Draw( void )	= 0;								// 描画

protected:
	

};

class CModeGame:public CMode
{
public:
	void Init( int StageID );							// 初期化
	void Uninit( void );						// 終了
	void Update( void );						// 更新
	void Draw( void );							// 描画

private:
	static CCamera *m_pCamera;					// カメラポインタ
	static CLight *m_pLight;					// ライトポインタ

};

class CModeStageSelect:public CMode
{
public:
	void Init( void );							// 初期化
	void Uninit( void );						// 終了
	void Update( void );						// 更新
	void Draw( void );							// 描画


	private:
	static CCamera *m_pCamera;					// カメラポインタ
	static CLight *m_pLight;					// ライトポインタ


};

class CModeTitle:public CMode
{
public:
	void Init( void );// 初期化
	void Uninit( void );						// 終了
	void Update( void );						// 更新
	void Draw( void );							// 描画


private:
	

};

#endif
#pragma once
