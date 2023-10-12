// =======================================================
//
// 終了画面背景処理(endBg.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"endBg.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Texture.h"

// マクロ定義
#define MAX_SCALE	(D3DXVECTOR2(100.0f,50.0f))	// スケールの最大
//= == == == == == == == == == == == == == == == == == =
// コンストラクタ
//====================================
CEndBg::CEndBg()
{
	// パラメーター初期化
	m_nTexType = 0;
	m_nIdxTexture = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//====================================
// デストラクタ
//====================================
CEndBg::~CEndBg()
{
}
//====================================
// 初期化処理
//====================================
HRESULT CEndBg::Init(void)
{
	CTexture*pTexture = CManager::GetCTexture();
	CObject2D::Init();
	// 位置情報の設定
	CObject2D::SetPos(m_pos);
	CObject2D::SetScale(MAX_SCALE.x, MAX_SCALE.y);

	// テクスチャの読み込み
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\end.png");

	// テクスチャの読み込み
	CObject2D::BindTexture(m_nIdxTexture);

	return S_OK;
}
//======================================
// 終了処理
//=====================================
void CEndBg::Uninit(void)
{
	CObject::Relese();
}
//======================================
// 更新処理
//======================================
void CEndBg::Update(void)
{
	CObject2D::Update();
}
//======================================
// 描画処理
//======================================
void CEndBg::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}
//======================================
// 生成処理
//======================================
CEndBg *CEndBg::Create(D3DXVECTOR3 pos)
{
	CEndBg * pEndBg;

	// オブジェクト2Dの生成
	pEndBg = new CEndBg;

	// 位置の設定
	pEndBg->Setpos(pos);

	// 初期化処理
	pEndBg->Init();

	return pEndBg;
}
