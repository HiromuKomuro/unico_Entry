// =======================================================
//
// スタート画面背景処理(startBg.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"startBg.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Texture.h"

// マクロ定義
#define MAX_SCALE	(D3DXVECTOR2(100.0f,50.0f))	// スケールの最大
//= == == == == == == == == == == == == == == == == == =
// コンストラクタ
//====================================
CStartBg::CStartBg()
{
	// パラメーター初期化
	m_nTexType = 0;
	m_nIdxTexture = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//====================================
// デストラクタ
//====================================
CStartBg::~CStartBg()
{
}
//====================================
// 初期化処理
//====================================
HRESULT CStartBg::Init(void)
{
	CTexture*pTexture = CManager::GetCTexture();
	CObject2D::Init();
	// 位置情報の設定
	CObject2D::SetPos(m_pos);
	CObject2D::SetScale(MAX_SCALE.x, MAX_SCALE.y);

	// テクスチャの読み込み
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\start.png");

	// テクスチャの読み込み
	CObject2D::BindTexture(m_nIdxTexture);

	return S_OK;
}
//======================================
// 終了処理
//=====================================
void CStartBg::Uninit(void)
{
	CObject::Relese();
}
//======================================
// 更新処理
//======================================
void CStartBg::Update(void)
{
	CObject2D::Update();
}
//======================================
// 描画処理
//======================================
void CStartBg::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}
//======================================
// 生成処理
//======================================
CStartBg *CStartBg::Create(D3DXVECTOR3 pos)
{
	CStartBg * pStartBg;

	// オブジェクト2Dの生成
	pStartBg = new CStartBg;

	// 位置の設定
	pStartBg->Setpos(pos);

	// 初期化処理
	pStartBg->Init();

	return pStartBg;
}
