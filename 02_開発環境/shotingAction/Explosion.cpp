// =======================================================
//
// 爆発の処理(Explosion.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"Explosion.h"
#include"input.h"
#include"Manager.h"
#include"renderer.h"
#include"billboard.h"
#include"Texture.h"

// マクロ定義
#define MAX_LIFE			(100)	// ライフの最大数
#define MAX_SCALE			(100.0f)// スケール
#define MAX_TEXTUREPATTERN	(8)		// テクスチャのパターン数
#define MAX_ANIMECUNTER		(10)	// 最大のアニメカウンター
// 静的メンバ変数
int CExplosion::m_nIdxTexture = 0;
//====================================
// コンストラクタ
//====================================
CExplosion::CExplosion()
{
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_nLife = MAX_LIFE;
	m_nAnimeCounter = 0;	// アニメカウンター
	m_nPatternCounter = 0;	// パターンカウンター
}
//====================================
// デストラクタ
//====================================
CExplosion::~CExplosion()
{
}
//====================================
// 初期化処理
//====================================
HRESULT CExplosion::Init(const D3DXVECTOR3 pos)
{
	CTexture*pTexture = CManager::GetCTexture();

	CObjectBillboard::Init();

	// 情報の設定
	CExplosion::SetPos(pos);
	CExplosion::SetScale(MAX_SCALE, MAX_SCALE);
	CExplosion::SetAnimeTex((float)(MAX_TEXTUREPATTERN), 0.0f);

	m_nIdxTexture = pTexture->Regist("data//TEXTURE//explosion000.png");

	return S_OK;
}
//======================================
// 終了処理
//=====================================
void CExplosion::Uninit(void)
{
	CObjectBillboard::Uninit();
	CObject::Relese();
}
//======================================
// 更新処理
//======================================
void CExplosion::Update(void)
{
	// オブジェクトの更新処理
	CObjectBillboard::Update();
	
	// テクスチャの設定
	CObjectBillboard::SetAnimeTex((float)MAX_TEXTUREPATTERN, m_nPatternCounter);

	m_nAnimeCounter++;		// アニメーションのカウンターを増加

	if (m_nAnimeCounter % MAX_ANIMECUNTER == 0)
	{
		m_nAnimeCounter = 0;	// 初期化
		m_nPatternCounter++;

		if (m_nPatternCounter >= MAX_TEXTUREPATTERN)
		{
			m_nPatternCounter = 0;	// 初期化
			CExplosion::Relese();	// オブジェクトの削除

		}
	}

}
//======================================
// 描画処理
//======================================
void CExplosion::Draw(void)
{
	// オブジェクトの描画処理
	CObjectBillboard::Draw();
}
//======================================
// 生成処理
//======================================
CExplosion *CExplosion::Create(const D3DXVECTOR3 pos)
{
	CTexture*pTexture = CManager::GetCTexture();
	CRenderer *pRenderer = CManager::GetRenderer();

	CExplosion *pCExplosion = NULL;
	
	// オブジェクト2Dの生成
	pCExplosion = new CExplosion();

	// 初期化処理
	pCExplosion->Init(pos);

	pCExplosion->BindTexture(m_nIdxTexture);

 	return pCExplosion;
}