//====================================================================
//
//カメラ処理[Camera.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"Camera.h"
#include"input.h"
#include"Bullet.h"
#include"Manager.h"
#include"renderer.h"
#include"object.h"
#include"Player3D.h"

//マクロ定義
#define CAMERAV_INIT_POS		(D3DXVECTOR3(800.0f, 100.0f, 0.0f))	// カメラの初期位置
#define CAMERA_MOVE			(2)			//カメラの移動量
#define CAMERA_DIS			(550)		//カメラの遠さ
#define CAMERA_HEIGHT		(100.0f)		//カメラの高さ
#define CAMERA_CDIS			(600)		//カメラの中央の遠さ
#define CAMERA_CHEIGHT		(1300)		//カメラの中央の高さ
#define CAMERA_TITLE_CDIS	(200)		//カメラの中央の遠さ
#define CAMERA_TITLE_CHEIGHT		(800)		//カメラの中央の高さ

//========================================
// コンストラクタ
//========================================
CCamera::CCamera()
{
	//カメラの情報の初期化
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//========================================
// コンストラクタ
//========================================
CCamera::~CCamera()
{
}
//========================================
// 初期化処理
//========================================
HRESULT CCamera::Init(void)
{
	//カメラの情報の初期化
	m_posV = D3DXVECTOR3(800.0f, 100.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}
//========================================
//カメラの終了処理
//========================================
void CCamera::Uninit(void)
{
}
//=======================================
//カメラの更新処理
//=======================================
void CCamera::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	//距離を求める
	float ra = m_posV.x - m_posR.x;
	float rb = m_posV.z - m_posR.z;

	float rc = sqrtf(ra * ra + rb * rb);

	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		CObject *pObj = CObject::GetTop(nCntPri);	// 先頭のオブジェクトを代入

		while (pObj != NULL)
		{
			CObject *pObjectNext = pObj->GetNext();	// 次のオブジェクトを保存

				//種類を取得
			CObject::TYPE type = pObj->GetType();

			if (type == CObject::TYPE_PLAYER)
			{
				CPlayer3D *pModel = dynamic_cast<CPlayer3D*>(pObj);

				// カメラの位置を設定
				m_posR = pModel->GetPos();
				m_rot = pModel->GetRot();
				//m_posR.x = m_posV.x + sin(m_rot.y) * rc;
				//m_posR.z = m_posV.z + cos(m_rot.y) * rc;
				m_posV.x = m_posR.x + sinf((D3DX_PI)+m_rot.y) * rc;
				m_posV.y = m_posR.y + CAMERA_HEIGHT;
				m_posV.z = m_posR.z + cosf((D3DX_PI)+m_rot.y) * rc;

			}
			pObj = pObjectNext;		// 次のオブジェクトを代入
		}
	}
	



	//カメラの移動処理

	//if (pInputKeyboard->GetKeyboardPress(DIK_D) == true)
	//{//Dキーが押された時
	//	/*m_posV.x += CAMERA_MOVE;
	//	m_posR.x += CAMERA_MOVE;*/
	//	m_posV.z -= sin(m_rot.y) *CAMERA_MOVE;
	//	m_posR.z -= sin(m_rot.y) *CAMERA_MOVE;
	//	m_posV.x += cos(m_rot.y) * CAMERA_MOVE;
	//	m_posR.x += cos(m_rot.y) * CAMERA_MOVE;
	//	
	//}
	//else if (pInputKeyboard->GetKeyboardPress(DIK_A) == true)
	//{//Aキーが押された時
	//	/*m_posV.x -= CAMERA_MOVE;
	//	m_posR.x -= CAMERA_MOVE;*/
	//	
	//	m_posV.z += sin(m_rot.y) *CAMERA_MOVE;
	//	m_posR.z += sin(m_rot.y) *CAMERA_MOVE;
	//	m_posV.x -= cos(m_rot.y) * CAMERA_MOVE;
	//	m_posR.x -= cos(m_rot.y) * CAMERA_MOVE;
	//
	//}
	//if (pInputKeyboard->GetKeyboardPress(DIK_W) == true)
	//{//Wキーが押された時
	//	/*m_posV.z += CAMERA_MOVE;
	//	m_posR.z += CAMERA_MOVE;*/
	//	m_posV.x += sin(m_rot.y)  *CAMERA_MOVE;
	//	m_posR.x += sin(m_rot.y) * CAMERA_MOVE;
	//	m_posV.z -= cos(D3DX_PI - m_rot.y)  * CAMERA_MOVE;
	//	m_posR.z -= cos(D3DX_PI - m_rot.y) * CAMERA_MOVE;
	//}
	//else if (pInputKeyboard->GetKeyboardPress(DIK_S) == true)
	//{//Sキーが押された時
	//	/*m_posV.z -= CAMERA_MOVE;
	//	m_posR.z -= CAMERA_MOVE;*/
	//	m_posV.x -= sin(m_rot.y) * CAMERA_MOVE;
	//	m_posR.x -= sin(m_rot.y) * CAMERA_MOVE;
	//	m_posV.z += cos(D3DX_PI - m_rot.y) * CAMERA_MOVE;
	//	m_posR.z += cos(D3DX_PI - m_rot.y) * CAMERA_MOVE;
	//}


	//if (pInputKeyboard->GetKeyboardPress(DIK_Q) == true)
	//{//Qキーが押された時
	//	m_rot.y -= 0.01f ;

	//	m_posR.x = m_posV.x + sin( m_rot.y) * rc;
	//	m_posR.z = m_posV.z + cos( m_rot.y) * rc;
	//}
	//else if (pInputKeyboard->GetKeyboardPress(DIK_E) == true)
	//{//Eキーが押された時
	//	m_rot.y += 0.01f;
	//	
	//	m_posR.x = m_posV.x + sin(m_rot.y) * rc;
	//	m_posR.z = m_posV.z + cos(m_rot.y) * rc;
	//}
	//if (pInputKeyboard->GetKeyboardPress(DIK_T) == true)
	//{//Tキーが押された時
	//	/*m_rot.y += 0.01f;

	//	m_posR.y = m_posV.y + tan(m_rot.y) * rc;*/
	//	//m_moveR.y += 1.5f;
	//}
	//else if (pInputKeyboard->GetKeyboardPress(DIK_B) == true)
	//{//Bキーが押された時
	//	/*m_rot.y -= 0.01f;

	//	m_posR.y = m_posV.y + tan(m_rot.y) * rc;*/
	//	//m_moveR.y -= 1.5f;
	//}


	//if (pInputKeyboard->GetKeyboardPress(DIK_Z) == true)
	//{//Zキーが押された時
	//	m_rot.y -= 0.01f;
	//}
	//else if (pInputKeyboard->GetKeyboardPress(DIK_C) == true)
	//{//Cキーが押された時
	//	m_rot.y += 0.01f;
	//}
	//else if (pInputKeyboard->GetKeyboardPress(DIK_Y) == true)
	//{//Yキーが押された時
	//	/*m_rot.y -= 0.01f;

	//	m_posV.y = m_posR.y + tan(-(D3DX_PI - m_rot.y)) * rc;*/
	//	//m_moveV.y += 1.5f;
	//}
	//else if (pInputKeyboard->GetKeyboardPress(DIK_N) == true)
	//{//Nキーが押された時
	///*	m_rot.y += 0.01f;

	//	m_posV.y = m_posR.y + tan(-(D3DX_PI - m_rot.y)) * rc;*/
	//	//m_moveV.y -= 1.5f;
	//}
}
//======================================
//カメラの設定処理
//======================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();


	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスを作成(投資投影)
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
								D3DXToRadian(45.0f),
								(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
								10.0f,			//視野角の最小値
								10000.0f);		//視野角の最大値
												
	////プロジェクションマトリックスを作成(平行投影)
	//D3DXMatrixOrthoLH(&m_mtxProjection,
	//	(float)SCREEN_WIDTH,	// 画面の幅
	//	(float)SCREEN_HEIGHT,	// 画面の高さ
	//	10.0f,			// 視野角の最小値
	//	10000.0f);		// 視野角の最大値
	
	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
						&m_posV,		//視点
						&m_posR,		//注視点
						&m_vecU);	//上方向ベクトル

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}