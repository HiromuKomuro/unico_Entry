// =======================================================
//
// リザルト処理(Rezult.h)
// author KOMURO HIROMU
//
// =======================================================
// 二重インクルード防止
#ifndef _REZULT_H_
#define _REZULT_H_

#include"main.h"
#include"Manager.h"

class CRankingManager;
class CScore;

//---------------------------------------------------------------------------
//					*****			マネージャークラスの定義			*****
//---------------------------------------------------------------------------
class CRezult:public CScene
{
public:
	CRezult();
	~CRezult();

	HRESULT Init(void);		// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理

	static CRankingManager *GetRankingManager(void) { return s_pRankingmanager; }	// ランキング管理の取得
	static CScore *GetScore(void) { return s_pScore; }		// スコアの取得処理

private:
	static CRankingManager * s_pRankingmanager;		// ランキング管理のポインタ
	static CScore* s_pScore;
};
#endif
