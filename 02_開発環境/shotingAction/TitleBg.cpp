// =======================================================
//
// 背景処理(bg.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"TitleBg.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Texture.h"

#define MAX_SCALE	(D3DXVECTOR2(300.0f,100.0f))	// スケールの最大
//= == == == == == == == == == == == == == == == == == =
// コンストラクタ
//====================================
TitleBg::TitleBg()
{
	// パラメーター初期化
	m_nTexType = 0;
	m_nIdxTexture = 0;
}

//====================================
// デストラクタ
//====================================
TitleBg::~TitleBg()
{
}
//====================================
// 初期化処理
//====================================
HRESULT TitleBg::Init(void)
{
	CTexture*pTexture = CManager::GetCTexture();

	CObject2D::Init();
	// 位置情報の設定
	CObject2D::SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2,200.0f,0.0f));
	CObject2D::SetScale(MAX_SCALE.x, MAX_SCALE.y);

	// テクスチャの読み込み
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\title000.png");

	BindTexture(m_nIdxTexture);

	return S_OK;
}
//======================================
// 終了処理
//=====================================
void TitleBg::Uninit(void)
{
	CObject::Relese();
}
//======================================
// 更新処理
//======================================
void TitleBg::Update(void)
{
	CObject2D::Update();
}
//======================================
// 描画処理
//======================================
void TitleBg::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}
//======================================
// 生成処理
//======================================
TitleBg *TitleBg::Create(void)
{
	TitleBg * pTitleBg;
	// オブジェクト2Dの生成
	pTitleBg = new TitleBg;

	// 初期化処理
	pTitleBg->Init();

	return pTitleBg;
}
