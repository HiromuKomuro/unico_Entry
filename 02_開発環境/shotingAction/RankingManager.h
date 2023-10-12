//====================================================================
//
//ランキング管理処理[RankingManager.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _RANKINGMANAGER_H_		//このマクロ定義がされてなかったら

#define _RANKINGMANAGER_H_		//二重インクルード防止のマクロを定義する

#define MAX_SCORE	(3)
#include"Score.h"
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CRankingManager
{
public:
	CRankingManager();
	~CRankingManager();

	//メンバ関数
	HRESULT Init(int *pScore);
	void Uninit(void);
	void Update(void);


private:
	CRankScore m_aScore[MAX_SCORE];		// スコアの構造体

};
#endif