// =======================================================
//
// ゲーム処理(game.h)
// author KOMURO HIROMU
//
// =======================================================
// 二重インクルード防止
#ifndef _GAME_H_
#define _GAME_H_

#include"Manager.h"
class CScore;
//---------------------------------------------------------------------------
//					*****			マネージャークラスの定義			*****
//---------------------------------------------------------------------------
class CGame:public CScene
{
public:
	CGame();
	~CGame();

	HRESULT Init(void);		// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理

	static CBlockManager *GetCBlockManager(void) { return s_pBlockManager; }	// ブロック管理の取得処理
	static CScore *GetScore(void) { return s_pScore; }		// スコアの取得処理
	static bool GetPause(void) { return m_bPause; }			// ポーズ状態の入手

private:
	static CBlockManager* s_pBlockManager;
	static CScore* s_pScore;
	static bool m_bPause;				// ポーズ

};
#endif
