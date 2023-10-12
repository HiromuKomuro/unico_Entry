// =======================================================
//
// リザルト処理(Rezult.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include<stdio.h>

#include"Manager.h"
#include"rezult.h"
#include"input.h"
#include"Fade.h"
#include"RezultBg.h"
#include"RankingManager.h"
#include"file.h"
#include"RankingBg.h"
#include"MeshCylinder.h"
#include"Player3D.h"
#include"dimbg.h"
#include"Score.h"
#include"myscore.h"
#include"Bg.h"

// マクロ定義
#define MAX_SCORE	(3)	// スコアの最大数
#define MYSCORE_POS	(D3DXVECTOR3(450.0f,120.0f,0.0f))	// スコアの位置
#define MYSCOREBG_POS	(D3DXVECTOR3(650.0f,50.0f,0.0f))	// スコアの位置
#define RANKINGBG_POS	(D3DXVECTOR3(650.0f,350.0f,0.0f))	// 自分のスコアの位置
#define SCORE_POS	(D3DXVECTOR3(450.0f,500.0f,0.0f))	// スコアの位置
#define PLAYER_INITPOS	(D3DXVECTOR3(0.0f, 800.0f, -2000.0f))	// プレイヤーの初期位置

// 静的メンバ変数
CRankingManager *CRezult::s_pRankingmanager = NULL;
CScore *CRezult::s_pScore = {};

//====================================
// コンストラクタ
//====================================
CRezult::CRezult()
{
}
//====================================
// デストラクタ
//====================================
CRezult::~CRezult()
{

}
//====================================
// 初期化処理
//====================================
HRESULT CRezult::Init(void)
{
	int nScore[MAX_SCORE] = { 0,0,0 };
	int nMyScore = 0;

	// 3Dプレイヤーの生成
	CPlayer3D::Create(PLAYER_INITPOS);

	// メッシュシリンダーの生成
	CMeshClynder::Create();

	// 薄暗い背景の生成
	CDimBg::Create();

	// 背景の生成
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, RANKINGBG_POS.y + 150.0f, 0.0f), D3DXVECTOR2(300.0f * 1.5, 168.0f * 1.5), "data\\TEXTURE\\Rankingbg.png");

	// 自分のスコア背景の生成
	CMyScore::Create(MYSCOREBG_POS);

	// ランキング背景の生成
	CRankingBg::Create(RANKINGBG_POS);

	// マップをロードする
	if (FAILED(CFile::ScoreLoad("data\\FILE\\Score.txt", &nScore[0], false)))
	{//スコアデータのロードが失敗した場合
		return -1;
	}
	// マップをロードする
	if (FAILED(CFile::ScoreLoad("data\\FILE\\MyScore.txt", &nMyScore, true)))
	{//スコアデータのロードが失敗した場合
		return -1;
	}

	if (s_pScore != NULL)
	{
		// スコア開放
		s_pScore->Uninit();
		delete s_pScore;
		s_pScore = NULL;
	}
	s_pScore = new CScore;	// スコアのインスタンス生成

	// スコアの初期化設定
	if (FAILED(s_pScore->Init(MYSCORE_POS)))
	{//初期化処理が失敗した場合
		return -1;
	}

	// スコアの設定
	s_pScore->SetScore(nMyScore);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		CRankScore::Create(D3DXVECTOR3(SCORE_POS.x, SCORE_POS.y + (100.0f * nCntScore), SCORE_POS.z), nScore[nCntScore]);
	}

	return S_OK;
}
//======================================
// 終了処理
//=====================================
void CRezult::Uninit(void)
{
	// 全オブジェクトの終了処理
	CObject::ReleseAll();	

	// ランキング管理の生成
	if (s_pRankingmanager != NULL)
	{
		s_pRankingmanager->Uninit();
		delete s_pRankingmanager;
		s_pRankingmanager = NULL;
	}

	// スコアの破棄
	if (s_pScore != NULL)
	{
		// 終了処理
		s_pScore->Uninit();
		delete s_pScore;	// スコアの開放
		s_pScore = NULL;
	}
}
//======================================
// 更新処理
//======================================
void CRezult::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	CFade*pFade = CManager::GetCFade();
	int Fade;

	//フェード状態を取得
	Fade = pFade->Get();

	if (Fade == CFade::FADE_NONE)
	{//フェード状態が何もないとき
		if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) == true)
		{
			CManager::SetMode(CScene::MODE_TITLE);
		}
	}
}
//======================================
// 描画処理
//======================================
void CRezult::Draw(void)
{
}

