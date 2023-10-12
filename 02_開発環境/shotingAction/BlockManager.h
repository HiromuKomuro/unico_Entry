//====================================================================
//
//ブロック管理処理[BlockManager.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _BLOCKMANAGER_H_		//このマクロ定義がされてなかったら

#define _BLOCKMANAGER_H_		//二重インクルード防止のマクロを定義する

#define  MAX_WAVE	(64)
#include"main.h"
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CBlockManager
{
public:
	// ブロックの構造体
	typedef struct
	{
		D3DXVECTOR3 pos;	// 位置
		int nType;			// 種類
	}Block;

	// ウェーブの構造体
	typedef struct
	{
		Block block[MAX_WAVE];	// ブロックの構造体
		int nNumBlock;		// ブロックの総数
	}Wave;

	CBlockManager();
	~CBlockManager();

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);


private:
	Wave m_aWave[MAX_WAVE];		// ウェーブの構造体
	int m_nCounterSummon;	// 召喚カウンター
	int m_nNumSummon;		// 召喚した総数
	float m_posZ;			// 位置

};
#endif