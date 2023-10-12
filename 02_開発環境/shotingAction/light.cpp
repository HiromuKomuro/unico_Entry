//====================================================================
//
//ライト処理[Light.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"Light.h"
#include"Manager.h"
#include"renderer.h"

//========================================
// コンストラクタ
//========================================
CLight::CLight()
{
}
//========================================
// デストラクタ
//========================================
CLight::~CLight()
{
}
//========================================
//ライトの初期化処理
//========================================
HRESULT CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ
	D3DXVECTOR3 VecDir;				//設定用方向ベクトル

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//ライトの情報をクリアする
		ZeroMemory(&m_alight[nCntLight], sizeof(D3DLIGHT9));

		//ライトの種類を設定
		m_alight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		////ライトの拡散光を設定
		//m_alight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		
		if (nCntLight == 0)
		{
			/*m_alight[nCntLight].Position = D3DXVECTOR3(0.0f, -10.8f, -12.4f);*/
			//ライトの拡散光を設定
			m_alight[nCntLight].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
			//ライトの方向を設定
			VecDir = D3DXVECTOR3(-1.6f, 3.0f, 1.4f);
		
		}
		else if (nCntLight == 1)
		{
			/*m_alight[nCntLight].Position = D3DXVECTOR3(1.6f, -1.6f, -0.3f);*/
			//ライトの拡散光を設定
			m_alight[nCntLight].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
			//ライトの方向を設定
			VecDir = D3DXVECTOR3(1.6f, 0.0f, 0.6f);
		}
		else
		{
			/*m_alight[nCntLight].Position = D3DXVECTOR3(-1.6f, 10.8f, -10.0f);*/
			//ライトの拡散光を設定
			m_alight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//ライトの方向を設定
			VecDir = D3DXVECTOR3(0.0f, -3.0f, -0.0f);
		}
		D3DXVec3Normalize(&VecDir, &VecDir);		//ベクトルを正規化する
		m_alight[nCntLight].Direction = VecDir;

		//ライトを設定する
		pDevice->SetLight(nCntLight, &m_alight[nCntLight]);

		//ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}
	return S_OK;

}
//========================================
//ライトの終了処理
//========================================
void CLight::Uninit(void)
{
}
//=======================================
//ライトの更新処理
//=======================================
void CLight::Update(void)
{
}