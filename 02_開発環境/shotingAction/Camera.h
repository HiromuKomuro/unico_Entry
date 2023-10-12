//====================================================================
//
//カメラ処理[Camera.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _CAMERA_H_		//このマクロ定義がされてなかったら

#define _CAMERA_H_		//二重インクルード防止のマクロを定義する
#include"main.h"

//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CCamera
{
public:
	CCamera();
	~CCamera();

	//プロトタイプ宣言
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);

	D3DXVECTOR3 GetCameraV(void) { return m_posV; }	// カメラの始点
	D3DXVECTOR3 GetCameraR(void) { return m_posR; }	// カメラの注視点
private:

		D3DXVECTOR3 m_posV;				//始点
		D3DXVECTOR3 m_posR;				//注視点
		D3DXVECTOR3 m_vecU;				//上方向ベクトル
		D3DXMATRIX  m_mtxProjection;	//プロジェクションマトリックス
		D3DXMATRIX  m_mtxView;			//ビューマトリックス
		D3DXVECTOR3 m_rot;				//向き
};
#endif
