// =======================================================
//
// 薄暗い背景処理(dimbg.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"dimbg.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Texture.h"

//= == == == == == == == == == == == == == == == == == =
// コンストラクタ
//====================================
CDimBg::CDimBg()
{
}

//====================================
// デストラクタ
//====================================
CDimBg::~CDimBg()
{
}
//====================================
// 初期化処理
//====================================
HRESULT CDimBg::Init(void)
{
	CTexture*pTexture = CManager::GetCTexture();

	CObject2D::Init();
	// 位置情報の設定
	CObject2D::SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f));
	CObject2D::SetScale(SCREEN_WIDTH, SCREEN_HEIGHT);
	CObject2D::SetCol(D3DCOLOR_RGBA(0, 0, 0, 100));

	return S_OK;
}
//======================================
// 終了処理
//=====================================
void CDimBg::Uninit(void)
{
	CObject2D::Uninit();
}
//======================================
// 更新処理
//======================================
void CDimBg::Update(void)
{
	CObject2D::Update();
}
//======================================
// 描画処理
//======================================
void CDimBg::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}
//======================================
// 生成処理
//======================================
CDimBg *CDimBg::Create(void)
{
	CDimBg *pDimBg;
	// オブジェクト2Dの生成
	pDimBg = new CDimBg;

	// 初期化処理
	pDimBg->Init();

	return pDimBg;
}
