// =======================================================
//
// タイトル処理(Title.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include<stdio.h>

#include"Manager.h"
#include"TItle.h"
#include"input.h"
#include"TitleBg.h"
#include"Fade.h"
#include"Player3D.h"
#include"MeshCylinder.h"
#include"TitleManager.h"
#include"Object2D.h"

// マクロ定義
#define PLAYER_INITPOS	(D3DXVECTOR3(0.0f, 800.0f, -2000.0f))	// プレイヤーの初期位置

// 静的メンバ変数
CTitleManager * CTitle::s_pTitleManager = NULL;
//====================================
// コンストラクタ
//====================================
CTitle::CTitle()
{
	m_bTutorial = false;
}
//====================================
// デストラクタ
//====================================
CTitle::~CTitle()
{
	s_pTitleManager = NULL;
}
//====================================
// 初期化処理
//====================================
HRESULT CTitle::Init(void)
{
	TitleBg::Create();	// タイトルの背景

	// メッシュシリンダーの生成
	CMeshClynder::Create();

	// 3Dプレイヤーの生成
	CPlayer3D::Create(PLAYER_INITPOS);

	// NULLチェック
	if (s_pTitleManager != NULL)
	{
		s_pTitleManager->Uninit();
		delete s_pTitleManager;
		s_pTitleManager = NULL;
	}

	s_pTitleManager = new CTitleManager();	// タイトル管理のインスタンスを生成

	s_pTitleManager->Init();	// 初期化処理
	return S_OK;
}
//======================================
// 終了処理
//=====================================
void CTitle::Uninit(void)
{
	// NULLチェック
	if (s_pTitleManager != NULL)
	{
		s_pTitleManager->Uninit();
		delete s_pTitleManager;
		s_pTitleManager = NULL;
	}

	// 全オブジェクトの終了処理
	CObject::ReleseAll();
}
//======================================
// 更新処理
//======================================
void CTitle::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	int Fade;

	if (pInputKeyboard->GetKeyboardTrigger(DIK_P) == true)
	{
		if (m_bTutorial == false)
		{//デバック表示がOFFの時

		 //ポーズ表示をONにする
			m_bTutorial = true;
		}
		else
		{//デバック表示がONの時

		 //ポーズ表示をOFFにする
			m_bTutorial = false;
		}
	}

	if (s_pTitleManager != NULL)
	{
		s_pTitleManager->Update();
	}
	
}
//======================================
// 描画処理
//======================================
void CTitle::Draw(void)
{

}

