// =======================================================
//
// チュートリアル処理(tutorial.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"tutorial.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Texture.h"
#include"input.h"

//= == == == == == == == == == == == == == == == == == =
// コンストラクタ
//====================================
CTutorial::CTutorial()
{
}

//====================================
// デストラクタ
//====================================
CTutorial::~CTutorial()
{
}
//====================================
// 初期化処理
//====================================
HRESULT CTutorial::Init(void)
{
	CTexture*pTexture = CManager::GetCTexture();

	CObject2D::Init();
	// 位置情報の設定
	CObject2D::SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f));
	CObject2D::SetScale(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	CObject2D::SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));

	// テクスチャの読み込み
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\tutorial.png");

	// テクスチャの読み込み
	CObject2D::BindTexture(m_nIdxTexture);

	return S_OK;
}
//======================================
// 終了処理
//=====================================
void CTutorial::Uninit(void)
{
	CObject2D::Uninit();
}
//======================================
// 更新処理
//======================================
void CTutorial::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	CObject2D::Update();

	//if (pInputKeyboard->GetKeyboardRelease(DIK_RETURN) == true)
	//{
	//	Uninit();	// オブジェクトの削除
	//}
}
//======================================
// 描画処理
//======================================
void CTutorial::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}
//======================================
// 生成処理
//======================================
CTutorial *CTutorial::Create(void)
{
	CTutorial *pTutorial;

	// オブジェクト2Dの生成
	pTutorial = new CTutorial;

	// 初期化処理
	pTutorial->Init();

	return pTutorial;
}
