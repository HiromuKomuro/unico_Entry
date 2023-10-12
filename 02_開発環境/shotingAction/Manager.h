// =======================================================
//
// マネージャー処理(Manager.h)
// author KOMURO HIROMU
//
// =======================================================
// 二重インクルード防止
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include"main.h"
#include"Object.h"
class CRenderer;
class CInputKeyboard;
class CPlayer;
class CBullet;
class CSound;
class CLight;
class CCamera;
class CTexture;
class CBlockManager;
class CFade;
//---------------------------------------------------------------------------
//					*****			モードクラスの定義			*****
//---------------------------------------------------------------------------
class CScene
{
public:
	CScene();
	~CScene();

	enum MODE
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_REZULT,
		MODE_MAX
	};
	static CScene * Create(MODE mode);

	virtual HRESULT Init(void) = 0;			// 初期化処理
	virtual void Uninit(void) = 0;			// 終了処理
	virtual void Update(void) = 0;			// 更新処理
	virtual void Draw(void) = 0;			// 描画処理

	MODE GetMode(void) { return m_mode; }	// モードの取得
	void SetMode(MODE mode) { m_mode = mode; }	// モードの設定
private:
	MODE m_mode;			// モードの種類
};

//---------------------------------------------------------------------------
//					*****			マネージャークラスの定義			*****
//---------------------------------------------------------------------------
class CManager
{
public:
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);		// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理

	static CRenderer *GetRenderer(void) { return m_pRenderer; }					// レンダラーの取得処理
	static CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }	// キーボードの取得処理
	static CSound *GetSound(void) { return m_pSound; }							// サウンドの取得処理
	static CLight *GetCLight(void) { return m_pLight; }							// ライトの取得処理
	static CCamera *GetCCamera(void) { return m_pCamera; }						// カメラの取得処理
	static CTexture *GetCTexture(void) { return m_pTexture; }					// テクスチャの取得処理
	static CBlockManager *GetCBlockManager(void) { return m_pBlockManager; }	// ブロック管理の取得処理
	static CFade *GetCFade(void) { return s_pFade; }							// フェイドの取得処理
	static CScene *GetCScene(void) { return s_pScene; }							// シーンの取得処理

	static void SetMode(CScene::MODE mode);					// モードの設定
private:
	static CRenderer*m_pRenderer;
	static CInputKeyboard*m_pInputKeyboard;
	static CSound* m_pSound;
	static CLight* m_pLight;
	static CCamera* m_pCamera;
	static CTexture* m_pTexture;
	static CBlockManager* m_pBlockManager;
	static CScene *s_pScene;
	static CFade *s_pFade;

};
#endif
