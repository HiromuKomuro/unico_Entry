// =======================================================
//
// 背景処理(bg.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"RezultBg.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Texture.h"

//= == == == == == == == == == == == == == == == == == =
// コンストラクタ
//====================================
CRezulteBg::CRezulteBg()
{
	// パラメーター初期化
	m_nTexType = 0;
	m_nIdxTexture = 0;
}

//====================================
// デストラクタ
//====================================
CRezulteBg::~CRezulteBg()
{
}
//====================================
// 初期化処理
//====================================
HRESULT CRezulteBg::Init(void)
{
	CTexture*pTexture = CManager::GetCTexture();

	CObject2D::Init();
	// 位置情報の設定
	CObject2D::SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f));
	CObject2D::SetScale(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	// テクスチャの読み込み
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\result.png");

	BindTexture(m_nIdxTexture);

	return S_OK;
}
//======================================
// 終了処理
//=====================================
void CRezulteBg::Uninit(void)
{
	CObject2D::Relese();
}
//======================================
// 更新処理
//======================================
void CRezulteBg::Update(void)
{
	CObject2D::Update();
}
//======================================
// 描画処理
//======================================
void CRezulteBg::Draw(void)
{
	// 描画処理
	CObject2D::Draw();

}
//======================================
// 生成処理
//======================================
CRezulteBg *CRezulteBg::Create(void)
{
	CRezulteBg * pRezulteBg;
	// オブジェクト2Dの生成
	pRezulteBg = new CRezulteBg;

	// 初期化処理
	pRezulteBg->Init();

	return pRezulteBg;
}
