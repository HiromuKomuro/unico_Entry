// =======================================================
//
// ゲーム処理(Game.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include<stdio.h>

#include"Manager.h"
#include"game.h"
#include"object.h"
#include"object2D.h"
#include"renderer.h"
#include"input.h"
#include"bullet.h"
#include"Explosion.h"
#include"Effect.h"
#include"sound.h"
#include"Score.h"
#include"Camera.h"
#include"light.h"
#include"Object3D.h"
#include"billboard.h"
#include"model.h"
#include"Texture.h"
#include"Player3D.h"
#include"file.h"
#include"BlockXbase.h"
#include"BlockManager.h"
#include"MeshCylinder.h"
#include"Fade.h"
#include"Time.h"
#include"Test.h"

// マクロ定義
#define PLAYER_INITPOS	(D3DXVECTOR3(0.0f, 800.0f, -2000.0f))	// プレイヤーの初期位置

// 静的メンバ変数宣言
CBlockManager*CGame::s_pBlockManager = NULL;
CScore * CGame::s_pScore = NULL;
bool CGame::m_bPause = false;

//====================================
// コンストラクタ
//====================================
CGame::CGame()
{

}
//====================================
// デストラクタ
//====================================
CGame::~CGame()
{

}
//====================================
// 初期化処理
//====================================
HRESULT CGame::Init(void)
{
	if (s_pBlockManager != NULL)
	{
		// ブロックマネージャーの開放
		s_pBlockManager->Uninit();
		delete s_pBlockManager;
		s_pBlockManager = NULL;
	}
	s_pBlockManager = new CBlockManager;	// ブロックマネージャーのインスタンス生成

	// ブロックマネージャーの初期化設定
	if (FAILED(s_pBlockManager->Init()))
	{//初期化処理が失敗した場合

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
	if (FAILED(s_pScore->Init(D3DXVECTOR3(800.0f, 40.0f, 0.0f))))
	{//初期化処理が失敗した場合

		return -1;

	}

	// メッシュシリンダーの生成
	CMeshClynder::Create();

	// 3Dプレイヤーの生成
	CPlayer3D::Create(PLAYER_INITPOS);
	
	// テストの生成
	//CTest::Create();
	return S_OK;
}
//======================================
// 終了処理
//=====================================
void CGame::Uninit(void)
{
	// 全オブジェクトの終了処理
	CObject::ReleseAll();

	// ブロックマネージャーの破棄
	if (s_pBlockManager != NULL)
	{
		// 終了処理
		s_pBlockManager->Uninit();
		delete s_pBlockManager;	// ブロックマネージャーの開放
		s_pBlockManager = NULL;
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
void CGame::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CFade*pFade = CManager::GetCFade();
	int Fade;

	if (pInputKeyboard->GetKeyboardTrigger(DIK_F1) == true)
	{
		if (m_bPause == false)
		{//デバック表示がOFFの時

		 //ポーズ表示をONにする
			m_bPause = true;
		}
		else
		{//デバック表示がONの時

		 //ポーズ表示をOFFにする
			m_bPause = false;
		}
	}

	if (s_pBlockManager != NULL)
	{
		s_pBlockManager->Update();
	}

	//フェード状態を取得
	Fade = pFade->Get();

	//if (Fade == CFade::FADE_NONE)
	//{//フェード状態が何もないとき
	//	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) == true)
	//	{//決定キーが押された		
	//	 //フェードの設定(ゲーム画面に移行)
	//		pFade->Set(CScene::MODE_REZULT);
	//	}
	//}

}
//======================================
// 描画処理
//======================================
void CGame::Draw(void)
{
}

