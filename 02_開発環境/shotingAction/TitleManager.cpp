//====================================================================
//
// タイトル管理処理[TitleManager.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"Manager.h"
#include"TitleManager.h"
#include"Player3D.h"
#include"object.h"
#include"BlockXbase.h"
#include"file.h"
#include"startBg.h"
#include"tutorialBg.h"
#include"endBg.h"
#include"input.h"
#include"Fade.h"
#include"tutorial.h"

// マクロ定義
#define LEFT_INITPOS	(D3DXVECTOR3(240.0f, 600.0f, 0.0f))		// 左の初期位置
#define CENTER_INITPOS	(D3DXVECTOR3(640.0f, 600.0f, 0.0f))		// 中央の初期位置
#define RIGHT_INITPOS	(D3DXVECTOR3(1040.0f, 600.0f, 0.0f))	// 右の初期位置

// 静的メンバ変数
CStartBg *CTitleManager::s_pStartBg = NULL;
CTutorialBg *CTitleManager::s_pTutorialBg = NULL;
CEndBg *CTitleManager::s_pEndBg = NULL;
CTutorial *CTitleManager::s_pTutorial = NULL;

static const D3DXVECTOR3 ObjPos[3] = {
	LEFT_INITPOS,
	CENTER_INITPOS,
	RIGHT_INITPOS
};
static const D3DCOLOR ObjCol[3] = {
	D3DCOLOR_RGBA(255,255,255,155),
	D3DCOLOR_RGBA(0,0,255,155),
	D3DCOLOR_RGBA(255,255,255,155),
};
//========================================
// コンストラクタ
//========================================
CTitleManager::CTitleManager()
{
	m_nCounterSelect = (int)TITLE_START;
	m_TitleSelect = TITLE_NONE;
}
//========================================
// デストラクタ
//========================================
CTitleManager::~CTitleManager()
{
	s_pStartBg = NULL;
	s_pTutorialBg = NULL;
	s_pEndBg = NULL;
	s_pTutorial = NULL;
}
//========================================
//初期化処理
//========================================
HRESULT CTitleManager::Init(void)
{	
	for (int nCntObj = 0; nCntObj < TITLE_TUTORIAL; nCntObj++)
	{
		CObject2D::Create(ObjPos[nCntObj],ObjCol[nCntObj],D3DXVECTOR2(100.0f,100.0f));	// 2Dオブジェクトの生成
	}
	// スタート背景の生成
	if (s_pStartBg != NULL)
	{
		s_pStartBg->Uninit();
		delete s_pStartBg;
		s_pStartBg = NULL;
	}

	// 終了背景の生成
	if (s_pEndBg != NULL)
	{
		s_pEndBg->Uninit();
		delete s_pEndBg;
		s_pEndBg = NULL;
	}

	// チュートリアル背景の生成
	if (s_pTutorialBg != NULL)
	{
		s_pTutorialBg->Uninit();
		delete s_pTutorialBg;
		s_pTutorialBg = NULL;
	}

	// インスタンスを生成
	s_pStartBg = new CStartBg();
	s_pEndBg = new CEndBg();
	s_pTutorialBg = new CTutorialBg();

	// 初期化処理
	s_pStartBg->Init();
	s_pEndBg->Init();
	s_pTutorialBg->Init();

	// 位置の設定
	s_pStartBg->SetPos(CENTER_INITPOS);
	s_pEndBg->SetPos(LEFT_INITPOS);
	s_pTutorialBg->SetPos(RIGHT_INITPOS);

	return S_OK;
}
//========================================
// 終了処理
//========================================
void CTitleManager::Uninit(void)
{
}
//=======================================
// 更新処理
//=======================================
void CTitleManager::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CFade*pFade = CManager::GetCFade();

	//フェード状態を取得
	CFade::FADE Fade = pFade->Get();

	if (m_TitleSelect != TITLE_TUTORIAL)
	{// チュートリアル状態以外の時
		if (pInputKeyboard->GetKeyboardRelease(DIK_LEFT) == true)
		{
			m_nCounterSelect--;	// カウントを減算
		}

		if (pInputKeyboard->GetKeyboardRelease(DIK_RIGHT) == true)
		{
			m_nCounterSelect++;	// カウントを加算
		}

		// 選択のカウントが最大、最小の時
		if (m_nCounterSelect >= TITLE_MAX)
		{
			m_nCounterSelect = TITLE_END;
		}
		else if (m_nCounterSelect <= TITLE_NONE)
		{
			m_nCounterSelect = TITLE_TUTORIAL;
		}

		switch ((TITLE_SELECT)m_nCounterSelect)
		{
		case TITLE_END:
			s_pStartBg->SetPos(RIGHT_INITPOS);
			s_pEndBg->SetPos(CENTER_INITPOS);
			s_pTutorialBg->SetPos(LEFT_INITPOS);
			break;
		case TITLE_START:
			s_pStartBg->SetPos(CENTER_INITPOS);
			s_pEndBg->SetPos(LEFT_INITPOS);
			s_pTutorialBg->SetPos(RIGHT_INITPOS);
			break;
		case TITLE_TUTORIAL:
			s_pStartBg->SetPos(LEFT_INITPOS);
			s_pEndBg->SetPos(RIGHT_INITPOS);
			s_pTutorialBg->SetPos(CENTER_INITPOS);
			break;
		}

		if (pInputKeyboard->GetKeyboardRelease(DIK_RETURN) == true)
		{
			m_TitleSelect = (TITLE_SELECT)m_nCounterSelect;

			switch ((TITLE_SELECT)m_nCounterSelect)
			{
			case TITLE_END:
				//ウインドウを破棄する(WM_DESTROYメッセージ)
				//DestroyWindow(hWnd);
				break;
			case TITLE_START:
				if (Fade == CFade::FADE_NONE)
				{//フェード状態が何もないとき
					 //フェードの設定(ゲーム画面に移行)
					pFade->Set(CScene::MODE_GAME);
				}
				break;
			case TITLE_TUTORIAL:
				s_pTutorial = new CTutorial();	// インスタンスの生成
				s_pTutorial->Init();				// 初期化
				break;
			}
		}
	}
	else
	{
		if (pInputKeyboard->GetKeyboardRelease(DIK_RETURN) == true)
		{
			if (Fade == CFade::FADE_NONE)
			{//フェード状態が何もないとき
			 //フェードの設定(ゲーム画面に移行)
				pFade->Set(CScene::MODE_GAME);
			}
		} 
	}
}