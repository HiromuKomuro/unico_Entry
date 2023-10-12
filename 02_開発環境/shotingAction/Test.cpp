// =======================================================
//
// テスト処理(Test.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"Test.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Texture.h"


//= == == == == == == == == == == == == == == == == == =
// コンストラクタ
//====================================
CTest::CTest()
{
	m_pTexture = NULL;
	m_Color = D3DCOLOR_RGBA(255, 255, 255, 255);
}

//====================================
// デストラクタ
//====================================
CTest::~CTest()
{
}
//====================================
// 初期化処理
//====================================
HRESULT CTest::Init(void)
{
	CTexture*pTexture = CManager::GetCTexture();

	CObject2D::Init();
	// 位置情報の設定
	CObject2D::SetPos(D3DXVECTOR3(100.0f,600.0f,0.0f));
	CObject2D::SetScale(300.0f, 200.0f);
	CObject2D::SetCol(m_Color);

	return S_OK;
}
//======================================
// 終了処理
//=====================================
void CTest::Uninit(void)
{
	CObject2D::Uninit();
}
//======================================
// 更新処理
//======================================
void CTest::Update(void)
{
	CObject2D::Update();
}
//======================================
// 描画処理
//======================================
void CTest::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();			// レンダラーの情報を入手

	LPDIRECT3DTEXTURE9 pTexture = pRenderer->GetTextureMT();

	CObject2D::SetTexture(m_pTexture);

	// 描画処理
	CObject2D::Draw();

}
//======================================
// 生成処理
//======================================
CTest *CTest::Create(LPDIRECT3DTEXTURE9 texture, D3DCOLOR color)
{
	CTest *pTest;
	// オブジェクト2Dの生成
	pTest = new CTest;

	// テクスチャの設定
	pTest->SetTexture(texture);

	// 色の設定
	pTest->SetCol(color);

	// 初期化処理
	pTest->Init();
	

	return pTest;
}
