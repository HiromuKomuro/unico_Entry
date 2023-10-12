//====================================================================
//
//ランキング管理処理[RankingManager.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"RankingManager.h"
#include"Player3D.h"
#include"object.h"
#include"BlockXbase.h"
#include"file.h"

// マクロ定義
#define SCORE_POS	(D3DXVECTOR3(600.0f,200.0f,0.0f))	// スコアの位置
//========================================
// コンストラクタ
//========================================
CRankingManager::CRankingManager()
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_aScore[nCnt] = {};
	}
}
//========================================
// デストラクタ
//========================================
CRankingManager::~CRankingManager()
{
	
}
//========================================
//初期化処理
//========================================
HRESULT CRankingManager::Init(int *pScore)
{
	for (int nCntScore= 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		m_aScore[nCntScore].Create(D3DXVECTOR3(SCORE_POS.x, SCORE_POS.y + (100.0f * nCntScore), SCORE_POS.z), pScore[nCntScore]);
	}
	return S_OK;
}
//========================================
// 終了処理
//========================================
void CRankingManager::Uninit(void)
{
}
//=======================================
// 更新処理
//=======================================
void CRankingManager::Update(void)
{

}