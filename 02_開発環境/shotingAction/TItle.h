// =======================================================
//
// タイトル処理(Title.h)
// author KOMURO HIROMU
//
// =======================================================
// 二重インクルード防止
#ifndef _TITLE_H_
#define _TITLE_H_

#include"manager.h"
class CTitleManager;
class CObject2D;
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CTitle:public CScene
{
public:
	CTitle();
	~CTitle();

	HRESULT Init(void);		// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理

	static CTitleManager*GetTitleManager(void) { return s_pTitleManager; }	// タイトルマネージャーの入手
private:
	static CTitleManager *s_pTitleManager;	// タイトルマネージャーの情報
	bool m_bTutorial;		// チュートリアル状態かどうか
};
#endif
