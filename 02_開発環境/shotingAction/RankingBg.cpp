// =======================================================
//
// ランキング画面背景処理(Rankingbg.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"RankingBg.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Texture.h"

// マクロ定義
#define MAX_SCALE	(D3DXVECTOR2(300.0f,100.0f))	// スケールの最大
//= == == == == == == == == == == == == == == == == == =
// コンストラクタ
//====================================
CRankingBg::CRankingBg()
{
	// パラメーター初期化
	m_nTexType = 0;
	m_nIdxTexture = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//====================================
// デストラクタ
//====================================
CRankingBg::~CRankingBg()
{
}
//====================================
// 初期化処理
//====================================
HRESULT CRankingBg::Init(void)
{
	CTexture*pTexture = CManager::GetCTexture();

	CObject2D::Init();
	// 位置情報の設定
	CObject2D::SetPos(m_pos);
	CObject2D::SetScale(MAX_SCALE.x, MAX_SCALE.y);

	// テクスチャの読み込み
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\ranking001.png");

	// テクスチャの読み込み
	CObject2D::BindTexture(m_nIdxTexture);

	return S_OK;
}
//======================================
// 終了処理
//=====================================
void CRankingBg::Uninit(void)
{
	CObject::Relese();
}
//======================================
// 更新処理
//======================================
void CRankingBg::Update(void)
{
	CObject2D::Update();
}
//======================================
// 描画処理
//======================================
void CRankingBg::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}
//======================================
// 生成処理
//======================================
CRankingBg *CRankingBg::Create(D3DXVECTOR3 pos)
{
	CRankingBg * pCRankingBg;

	// オブジェクト2Dの生成
	pCRankingBg = new CRankingBg;

	// 位置の設定
	pCRankingBg->Setpos(pos);

	// 初期化処理
	pCRankingBg->Init();

	return pCRankingBg;
}
