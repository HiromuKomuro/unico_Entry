// =======================================================
//
// スタート画面背景処理(startBg.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"tutorialBg.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Texture.h"

// マクロ定義
#define MAX_SCALE	(D3DXVECTOR2(100.0f,50.0f))	// スケールの最大
//= == == == == == == == == == == == == == == == == == =
// コンストラクタ
//====================================
CTutorialBg::CTutorialBg()
{
	// パラメーター初期化
	m_nTexType = 0;
	m_nIdxTexture = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//====================================
// デストラクタ
//====================================
CTutorialBg::~CTutorialBg()
{
}
//====================================
// 初期化処理
//====================================
HRESULT CTutorialBg::Init(void)
{
	CTexture*pTexture = CManager::GetCTexture();
	CObject2D::Init();
	// 位置情報の設定
	CObject2D::SetPos(m_pos);
	CObject2D::SetScale(MAX_SCALE.x, MAX_SCALE.y);

	// テクスチャの読み込み
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\tutorial001.png");

	// テクスチャの読み込み
	CObject2D::BindTexture(m_nIdxTexture);

	return S_OK;
}
//======================================
// 終了処理
//=====================================
void CTutorialBg::Uninit(void)
{
	CObject::Relese();
}
//======================================
// 更新処理
//======================================
void CTutorialBg::Update(void)
{
	CObject2D::Update();
}
//======================================
// 描画処理
//======================================
void CTutorialBg::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}
//======================================
// 生成処理
//======================================
CTutorialBg *CTutorialBg::Create(D3DXVECTOR3 pos)
{
	CTutorialBg * pTutorialBg;

	// オブジェクト2Dの生成
	pTutorialBg = new CTutorialBg;

	// 位置の設定
	pTutorialBg->Setpos(pos);

	// 初期化処理
	pTutorialBg->Init();

	return pTutorialBg;
}
