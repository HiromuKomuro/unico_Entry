// =======================================================
//
// マネージャー処理(Manager.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include<stdio.h>

#include"Manager.h"
#include"renderer.h"
#include"input.h"
#include"sound.h"
#include"Camera.h"
#include"light.h"
#include"Texture.h"
#include"TItle.h"
#include"game.h"
#include"rezult.h"
#include"Fade.h"

// 静的メンバ変数宣
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CSound *CManager::m_pSound = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CTexture *CManager::m_pTexture = NULL;
CBlockManager* CManager::m_pBlockManager = NULL;
CScene* CManager::s_pScene = NULL;
CFade *CManager::s_pFade = NULL;
//====================================
// コンストラクタ
//====================================
CManager::CManager()
{

}
//====================================
// デストラクタ
//====================================
CManager::~CManager()
{

}
//====================================
// 初期化処理
//====================================
HRESULT CManager::Init(HINSTANCE hInstance,HWND hWnd, BOOL bWindow)
{
	// レンダラーの生成
	if (m_pRenderer != NULL)
	{
		// レンダラーの開放
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	m_pRenderer = new CRenderer;	// レンダラーのインスタンス生成

	// インプットの生成
	if (m_pInputKeyboard != NULL)
	{
		// インプットの開放
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
	m_pInputKeyboard = new CInputKeyboard;	// キーボードのインスタンス生成

	// サウンドの生成
	if (m_pSound != NULL)
	{
		// サウンドの開放
		delete m_pSound;
		m_pSound = NULL;
	}
	m_pSound = new CSound;	// サウンドのインスタンス生成

	// カメラの生成
	if (m_pCamera != NULL)
	{
		// カメラの開放
		delete m_pCamera;
		m_pCamera = NULL;
	}
	m_pCamera = new CCamera;	// カメラのインスタンス生成

	// ライトの生成
	if (m_pLight != NULL)
	{
		// ライトの開放
		delete m_pLight;
		m_pLight = NULL;
	}
	m_pLight = new CLight;	// ライトのインスタンス生成

	// テクスチャの生成
	if (m_pTexture != NULL)
	{
		// テクスチャの開放
		delete m_pTexture;
		m_pTexture = NULL;
	}
	m_pTexture = new CTexture;	// テクスチャのインスタンス生成

	// シーンの生成
	if (s_pScene != NULL)
	{
		// シーンの開放
		delete s_pScene;
		s_pScene = NULL;
	}
	s_pScene = new CTitle;	// シーンのインスタンス生成

	// フェイドの生成
	if (s_pFade != NULL)
	{
		// シーンの開放
		delete s_pFade;
		s_pFade = NULL;
	}
	s_pFade = new CFade;	// シーンのインスタンス生成

	// レンダラーの初期化設定
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{//初期化処理が失敗した場合

		return -1;

	}

	// インプットの初期化設定
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{//初期化処理が失敗した場合

		return -1;

	}

	// サウンドの初期化設定
	if (FAILED(m_pSound->Init(hWnd)))
	{//初期化処理が失敗した場合

		return -1;

	}
	// カメラの初期化設定
	if (FAILED(m_pCamera->Init()))
	{//初期化処理が失敗した場合

		return -1;

	}
	// ライトの初期化設定
	if (FAILED(m_pLight->Init()))
	{//初期化処理が失敗した場合

		return -1;

	}
	// テクスチャの初期化設定
	if (FAILED(m_pTexture->Load()))
	{//初期化処理が失敗した場合

		return -1;

	}	

	//// シーンの初期化設定
	//if (FAILED(s_pScene->Init()))
	//{//初期化処理が失敗した場合

	//	return -1;

	//}
	// フェイドの初期化設定
	if (FAILED(s_pFade->Init(CScene::MODE_TITLE)))
	{//初期化処理が失敗した場合

		return -1;

	}
	return S_OK;
}
//======================================
// 終了処理
//=====================================
void CManager::Uninit(void)
{
	// 全オブジェクトの終了処理
	CObject::ReleseAll();

	// レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		//終了処理
		m_pRenderer->Uninit();
		delete m_pRenderer;			// レンダラーの開放
		m_pRenderer = NULL;
	}
	// キーボードの破棄
	if (m_pInputKeyboard != NULL)
	{
		//終了処理
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;	// キーボードの開放
		m_pInputKeyboard = NULL;
	}
	// サウンドの破棄
	if (m_pSound != NULL)
	{
		//終了処理
		m_pSound->Uninit();
		delete m_pSound;	// サウンドの開放
		m_pSound = NULL;
	}
	// カメラの破棄
	if (m_pCamera != NULL)
	{
		//終了処理
		m_pCamera->Uninit();
		delete m_pCamera;	// カメラの開放
		m_pCamera = NULL;
	}
	// ライトの破棄
	if (m_pLight != NULL)
	{
		//終了処理
		m_pLight->Uninit();
		delete m_pLight;	// ライトの開放
		m_pLight = NULL;
	}
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		// 終了処理
		m_pTexture->UnLoad();
		delete m_pTexture;	// テクスチャの開放
		m_pTexture = NULL;
	}
	// シーンの破棄
	if (s_pScene != NULL)
	{
		// 終了処理
		s_pScene->Uninit();
		delete s_pScene;	// シーンの開放
		s_pScene = NULL;
	}
	// フェードの破棄
	if (s_pFade != NULL)
	{
		// 終了処理
		s_pFade->Uninit();
		delete s_pFade;	// フェードの開放
		s_pFade = NULL;
	}
}
//======================================
// 更新処理
//======================================
void CManager::Update(void)
{
	if (m_pRenderer != NULL)
	{
		// レンダラーの更新処理
		m_pRenderer->Update();
	}
	if (m_pInputKeyboard != NULL)
	{
		// キーボードの更新処理
		m_pInputKeyboard->Update();
	}
	if (s_pScene != NULL)
	{
		// シーンの更新処理
		s_pScene->Update();
	}
	if (s_pFade != NULL)
	{
		// フェイドの更新処理
		s_pFade->Update();
	}
}
//======================================
// 描画処理
//======================================
void CManager::Draw(void)
{
	// レンダラーの描画処理
	m_pRenderer->Draw();

	if (s_pScene != NULL)
	{
		// シーンの描画処理
		s_pScene->Draw();
	}
	if (s_pFade != NULL)
	{
		// フェイドの描画処理
		s_pFade->Draw();
	}
}
//====================================
// コンストラクタ
//====================================
CScene::CScene()
{
}
//====================================
// デストラクタ
//====================================
CScene::~CScene()
{

}
//====================================
// 初期化
//====================================
HRESULT CScene::Init(void)
{
	return S_OK;
}
//====================================
// 終了処理
//====================================
void CScene::Uninit(void)
{

}
//====================================
// 更新処理
//====================================
void CScene::Update(void)
{

}
//====================================
// 描画処理
//====================================
void CScene::Draw(void)
{

}
//======================================
// シーンの生成処理
//======================================
CScene *CScene::Create(MODE mode)
{
	CScene *pScene;
	
	switch (mode)
	{
	case CScene::MODE_TITLE:
		// インスタンスの生成
		pScene = new CTitle();
		break;
	case CScene::MODE_GAME:
		// インスタンスの生成
		pScene = new CGame();
		break;
	case CScene::MODE_REZULT:
		// インスタンスの生成
		pScene = new CRezult();
		break;
	default:
		// インスタンスの生成
		pScene = new CRezult();
		break;
	}
	// モードの設定
	pScene->SetMode(mode);

	// シーンの初期化
	pScene->Init();

	return pScene;
}
//======================================
// モードの設定処理
//======================================
void CManager::SetMode(CScene::MODE mode)
{
	// サウンドの停止
	m_pSound->StopSound();

	// 現在のモードの破棄
	if (s_pScene != NULL)
	{
		// 終了処理
		s_pScene->Uninit();
		delete s_pScene;	// シーンの開放
		s_pScene = NULL;
	}

	// 新しいモードの生成
	s_pScene = CScene::Create(mode);
}
