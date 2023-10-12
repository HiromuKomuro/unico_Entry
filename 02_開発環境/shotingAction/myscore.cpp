// =======================================================
//
// 自分のスコア処理(myscore.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"myscore.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Texture.h"

// マクロ定義
#define MAX_SCALE	(D3DXVECTOR2(300.0f,30.0f))
//= == == == == == == == == == == == == == == == == == =
// コンストラクタ
//====================================
CMyScore::CMyScore()
{
	m_nIdxTexture = 0;
}
//====================================
// デストラクタ
//====================================
CMyScore::~CMyScore()
{
}
//====================================
// 初期化処理
//====================================
HRESULT CMyScore::Init(void)
{
	CTexture*pTexture = CManager::GetCTexture();

	// テクスチャの読み込み
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\my_score.png");
	CObject2D::BindTexture(m_nIdxTexture);
	CObject2D::Init();
	// 位置情報の設定
	CObject2D::SetScale(MAX_SCALE.x, MAX_SCALE.y);

	return S_OK;
}
//======================================
// 終了処理
//=====================================
void CMyScore::Uninit(void)
{
	CObject2D::Uninit();
}
//======================================
// 更新処理
//======================================
void CMyScore::Update(void)
{
	CObject2D::Update();
}
//======================================
// 描画処理
//======================================
void CMyScore::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}
//======================================
// 生成処理
//======================================
CMyScore *CMyScore::Create(D3DXVECTOR3 pos)
{
	CMyScore *pMyScore;
	// オブジェクト2Dの生成
	pMyScore = new CMyScore;

	// 位置
	pMyScore->SetPos(pos);

	// 初期化処理
	pMyScore->Init();

	return pMyScore;
}
