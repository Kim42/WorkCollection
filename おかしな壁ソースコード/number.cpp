/*=============================================================================

 ナンバー描画処理[ number.cpp ]

=============================================================================*/
/*=============================================================================
 インクルードヘッダ
=============================================================================*/
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "number.h"

/*=============================================================================
 マクロ定義
=============================================================================*/
#define NUM_VERTEX  (4)		// 頂点数
#define NUM_POLYGON (2)		// プリミティブ数
#define TEX_U       (0.1f)

/*=============================================================================
 ２Ｄ頂点フォーマット
=============================================================================*/
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

/*=============================================================================
 2D頂点情報構造体
=============================================================================*/
struct VERTEX_2D
{
	D3DXVECTOR3 pos;		// 座標位置
	float       rhw;		// 変換済み座標
	D3DCOLOR    col;		// 色
	D3DXVECTOR2 tex;		// テクスチャ座標
};

//=============================================================================
// 生成処理
//=============================================================================
CNumber *CNumber :: Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumber)
{
	// 使用宣言
	CNumber *pNumber;

	// ナンバーの生成
	pNumber = new CNumber;

	// 初期化
	pNumber -> Init(nTexType, pos, size, nNumber );

	// クラスポインタを返す
	return pNumber;

}

/*-----------------------------------------------------------------------------
 初期化処理
-----------------------------------------------------------------------------*/
HRESULT CNumber :: Init( int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumber )
{
	// 値の代入
	m_Pos = pos;
	m_Size = size;
	m_nTexType = nTexType;

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer:: GetDevice();

	// 頂点バッファの生成
	if( FAILED ( pDevice -> CreateVertexBuffer(
		sizeof(VERTEX_2D) * NUM_VERTEX ,		// 作成する頂点バッファのサイズ
		D3DUSAGE_WRITEONLY,						// 書き込みのみ実行
		FVF_VERTEX_2D,							// 頂点フォーマットの設定
		D3DPOOL_MANAGED,						// メモリ管理 ⇒ お任せ
		&m_pVtxBuff,							// 頂点バーテックスアドレス
		NULL ) ) )
	{
		MessageBox(NULL, "頂点バッファの生成に失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}//if.fin

	// 頂点情報を設定
	VERTEX_2D *pVtx = NULL;

	// 頂点バッファのロック
	m_pVtxBuff -> Lock( 0, 0, ( void** )&pVtx, 0 );

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3( m_Pos.x         , m_Pos.y         , 0.0f );
	pVtx[1].pos = D3DXVECTOR3( m_Pos.x + size.x, m_Pos.y         , 0.0f );
	pVtx[2].pos = D3DXVECTOR3( m_Pos.x         , m_Pos.y + size.y, 0.0f );
	pVtx[3].pos = D3DXVECTOR3( m_Pos.x + size.x, m_Pos.y + size.y, 0.0f );

	// rhwの設定(必ず1.0f)
	pVtx[0].rhw = 
	pVtx[1].rhw = 
	pVtx[2].rhw = 
	pVtx[3].rhw = 1.0f;

	// 頂点カラ―の設定(0～255の整数値)
	pVtx[0].col = 
	pVtx[1].col = 
	pVtx[2].col = 
	pVtx[3].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );

	// ＵＶ値の設定
	pVtx[0].tex = D3DXVECTOR2( 0.1f * nNumber,         0 );
	pVtx[1].tex = D3DXVECTOR2( 0.1f * nNumber + TEX_U, 0 );
	pVtx[2].tex = D3DXVECTOR2( 0.1f * nNumber,         1 );
	pVtx[3].tex = D3DXVECTOR2( 0.1f * nNumber + TEX_U, 1 );

	// 頂点バッファのアンロック
	m_pVtxBuff -> Unlock();

	// 正常終了
	return S_OK;

}

/*-----------------------------------------------------------------------------
 終了管理処理
-----------------------------------------------------------------------------*/
void CNumber :: Uninit( void )
{
	// 頂点バッファの破棄
	SAFE_RELEASE(m_pVtxBuff);

	// 自身の破棄
	delete this;

}

/*-----------------------------------------------------------------------------
 描画管理処理
-----------------------------------------------------------------------------*/
void CNumber :: Draw( void )
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice -> SetStreamSource( 0, m_pVtxBuff, 0, sizeof(VERTEX_2D) );

	// 頂点フォーマットの設定
	pDevice -> SetFVF( FVF_VERTEX_2D );

	// テクスチャの設定
	pDevice -> SetTexture( 0, CTexture::GetAdr(m_nTexType));

	// ポリゴンの描画
	pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON );

}

/*-----------------------------------------------------------------------------
 数字の値設置
-----------------------------------------------------------------------------*/
void CNumber :: SetNumber( int nNumber )
{
	// 頂点情報を設定
	VERTEX_2D *pVtx = NULL;

	// 頂点バッファのロック
	m_pVtxBuff -> Lock( 0, 0, ( void** )&pVtx, 0 );

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2( 0.1f * nNumber,         0 );
	pVtx[1].tex = D3DXVECTOR2( 0.1f * nNumber + TEX_U, 0 );
	pVtx[2].tex = D3DXVECTOR2( 0.1f * nNumber,         1 );
	pVtx[3].tex = D3DXVECTOR2( 0.1f * nNumber + TEX_U, 1 );

	// 頂点バッファのアンロック
	m_pVtxBuff -> Unlock();

}

