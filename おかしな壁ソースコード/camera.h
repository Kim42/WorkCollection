/*=============================================================================

 カメラ処理ヘッダ[ camera.h ]

=============================================================================*/
/*-----------------------------------------------------------------------------
 インクルードガード
-----------------------------------------------------------------------------*/
#ifndef _CAMERA_H_
#define _CAMERA_H_

/*-----------------------------------------------------------------------------
 クラス定義
-----------------------------------------------------------------------------*/
class CCamera
{
	private:

		static D3DXVECTOR3 m_At;		// 注視点座標
		static D3DXVECTOR3 m_Eye;		// カメラ座標
		static D3DXVECTOR3 m_Up;		// 上向きのベクトル

		static float m_fZoom;			// 拡大縮小

		// マトリクスの定義
		static D3DXMATRIX m_mtxProjection;
		static D3DXMATRIX m_mtxView;

	public:

		// コンストラクタ & デスクトラクタ
		CCamera() {}
		~CCamera() {}

		// 各処理関数
		static HRESULT Init  (D3DXVECTOR3 At, D3DXVECTOR3 Eye);
		static void    Uninit(void);
		static void    Update(void);
		static void    Set   (void);

		// 注視点情報の取得
		static D3DXVECTOR3 *GetAt(void) { return &m_At; }

		// カメラ座標情報の取得
		static D3DXVECTOR3 *GetEye(void) { return &m_Eye; }

		// ビューマトリクスの取得
		static D3DXMATRIX  *GetViewMtx(void) { return &m_mtxView; }

		// プロジェクションマトリクスの取得
		static D3DXMATRIX  *GetProjectionMtx(void){ return &m_mtxProjection; }

		// カメラ視点のセット
		static void SetCamera(D3DXVECTOR3 pos, float fZ)
		{
			m_At.x  = pos.x; m_At.y  = pos.y;
			m_Eye.x = pos.x; m_Eye.y = pos.y; m_Eye.z = fZ;

		}//end

		// カメラズーム処理
		static void SetZoomFunction(float fZoom) { m_fZoom += fZoom; }

};

/*-----------------------------------------------------------------------------
 インクルードエンド
-----------------------------------------------------------------------------*/
#endif
