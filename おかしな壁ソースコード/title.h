/*******************************************************************************
* タイトル:		ポリゴン表示
* プログラム名:		player.h
* 作成者:		AT-12A-248 石川　未友
* 作成日:		2016/MM/DD
********************************************************************************
* 更新履歴:		- 2016/MM/DD　石川　未友
*			- V1.00　Initial Version
*******************************************************************************/
#ifndef _TITLE_H_	     // ２重インクルード防止のマクロ定義
#define _TITLE_H_

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "manager.h"
#include "scene2D.h"

/*******************************************************************************
* 前方宣言
*******************************************************************************/

/*******************************************************************************
* マクロ定義
*******************************************************************************/

/*******************************************************************************
* クラス定義
*******************************************************************************/
class CTitle:public CScene2D
{
public:
	static CTitle *Create( D3DXVECTOR3 pos, D3DXVECTOR3 size );

	HRESULT Init( D3DXVECTOR3 pos, D3DXVECTOR3 size );
	void Uninit( void );
	void Update( void );
	void Draw( void );

protected:

private:

};


#endif