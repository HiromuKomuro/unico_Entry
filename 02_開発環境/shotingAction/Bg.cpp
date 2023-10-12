// =======================================================
//
// 背景処理(bg.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"Bg.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Texture.h"

//= == == == == == == == == == == == == == == == == == =
// コンストラクタ
//====================================
CBg::CBg()
{
	// パラメーター初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR2(0.0f, 0.0f);
	m_pFilename = NULL;
	m_nTexType = 0;
	m_nIdxTexture = 0;
}

//====================================
// デストラクタ
//====================================
CBg::~CBg()
{
}
//====================================
// 初期化処理
//====================================
HRESULT CBg::Init(void)
{
	CTexture*pTexture = CManager::GetCTexture();

	CObject2D::Init();
	// 位置情報の設定
	CObject2D::SetPos(m_pos);
	CObject2D::SetScale(m_scale.x,m_scale.y);

	// テクスチャの読み込み
	m_nIdxTexture = pTexture->Regist(m_pFilename);

	BindTexture(m_nIdxTexture);

	return S_OK;
}
//======================================
// 終了処理
//=====================================
void CBg::Uninit(void)
{
	CObject2D::Relese();
}
//======================================
// 更新処理
//======================================
void CBg::Update(void)
{
	CObject2D::Update();
}
//======================================
// 描画処理
//======================================
void CBg::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}
//======================================
// 生成処理
//======================================
CBg *CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR2 scale, char *pFilename)
{
	CBg * pBg;
	
	// オブジェクト2Dの生成
	pBg = new CBg;

	// 各種の設定
	pBg->Setpos(pos);
	pBg->Setscale(scale);
	pBg->SetFile(pFilename);

	// 初期化処理
	pBg->Init();

	return pBg;
}
