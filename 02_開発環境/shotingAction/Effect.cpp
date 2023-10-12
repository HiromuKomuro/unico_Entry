//====================================================================
//
//エフェクト処理[Effect.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"Effect.h"
#include"Manager.h"
#include"renderer.h"
#include"Texture.h"

// 静的メンバ変数
//====================================
// コンストラクタ
//====================================
CEffect2D::CEffect2D()
{
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_fmove = 0.0f;
	m_nLife = 50;
	m_nIdxTexture = 0;
}
//====================================
// デストラクタ
//====================================
CEffect2D::~CEffect2D()
{
}
//====================================
// 初期化処理
//====================================
HRESULT CEffect2D::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,const D3DCOLOR col, int life)
{
	CTexture*pTexture = CManager::GetCTexture();

	m_nIdxTexture = pTexture->Regist("data//TEXTURE//effect000.jpg");
	CObjectBillboard::BindTexture(m_nIdxTexture);
	CObjectBillboard::SetScale(20.0f, 20.0f);	// 大きさを設定
	CObjectBillboard::Init();

	CObjectBillboard::SetPos(pos);	// 位置情報の設定
	CObjectBillboard::SetRot(rot);	// 向き情報の設定
	CObjectBillboard::SetCol(col);	// 色情報の設定

	m_nLife = life;		// 寿命の設定
	return S_OK;
}
//======================================
// 終了処理
//=====================================
void CEffect2D::Uninit(void)
{
	CObjectBillboard::Uninit();
	CObject::Relese();
}
//======================================
// 更新処理
//======================================
void CEffect2D::Update(void)
{
	// オブジェクトの更新処理
	CObjectBillboard::Update();

	m_nLife--;	// 体力を減らす
	if (m_nLife <= 0)
	{// ライフが0の時
		CEffect2D::Uninit();	// オブジェクトを削除
	}
}
//======================================
// 描画処理
//======================================
void CEffect2D::Draw(void)
{
	// オブジェクトの描画処理
	CObjectBillboard::Draw();
}
//======================================
// 生成処理
//======================================
CEffect2D *CEffect2D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,const D3DCOLOR col, int life)
{
	CEffect2D *pEffect2D;

	// オブジェクト2Dの生成
	pEffect2D = new CEffect2D();

	// 初期化処理
	pEffect2D->Init(pos, rot,col,life);

	return pEffect2D;
}