//====================================================================
//
//ブロック管理処理[BlockManager.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include<stdlib.h>
#include <time.h>

#include"BlockManager.h"
#include"Player3D.h"
#include"object.h"
#include"BlockXbase.h"
#include"file.h"

// マクロ定義
#define MAX_INTERVAL	(220)		// インターバルの時間
#define MAX_INTERVALPOS	(1700.0f)	// インターバルの位置
#define MAX_CYLINDER_Z	(1800.0f * 7.0f)	// シリンダーの位置
//========================================
// コンストラクタ
//========================================
CBlockManager::CBlockManager()
{
	for (int nCnt = 0; nCnt < MAX_WAVE; nCnt++)
	{
		m_aWave[nCnt] = {};
	}
	m_nCounterSummon = 0;
	m_nNumSummon = 0;
	m_posZ = -2000.0f;
}
//========================================
// デストラクタ
//========================================
CBlockManager::~CBlockManager()
{
}
//========================================
//初期化処理
//========================================
HRESULT CBlockManager::Init(void)
{
	//  time関数を使った乱数の種の設定
	srand((unsigned int)time(NULL));

	// マップをロードする
	if (FAILED(CFile::MapLoad("data\\FILE\\Block.txt", CFile::TYPE_BLOCK, &m_aWave[0], &m_nNumSummon)))
	{//エネミーのロードが失敗した場合
	}
	
	return S_OK;
}
//========================================
// 終了処理
//========================================
void CBlockManager::Uninit(void)
{
}
//=======================================
// 更新処理
//=======================================
void CBlockManager::Update(void)
{
	int nWaveNumber = 0;
	m_nCounterSummon++;

	// プレイヤーの情報の入手
	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		CObject *pObj = CObject::GetTop(nCntPri);	// 先頭のオブジェクトを代入

		while (pObj != NULL)
		{
			CObject *pObjectNext = pObj->GetNext();	// 次のオブジェクトを保存

			//種類を取得
			CObject::TYPE type = pObj->GetType();

			if (type == CObject::TYPE_PLAYER)
			{
				CPlayer3D *pPlayer3D = dynamic_cast<CPlayer3D*>(pObj);


				if (pPlayer3D->GetPos().z >= MAX_CYLINDER_Z)
				{
					break;
				}
				if (pPlayer3D->GetPos().z >= m_posZ + MAX_INTERVALPOS)
				{
					m_posZ = pPlayer3D->GetPos().z;

					D3DXVECTOR3 pos = {};	// 位置
					D3DXVECTOR3 Scale = { 1.0f,1.0f,1.0f };	// 大きさ

					nWaveNumber = rand() % 5 + 0;

					for (int nCntBlock = 0; nCntBlock < m_aWave[nWaveNumber].nNumBlock; nCntBlock++)
					{
						pos = D3DXVECTOR3(m_aWave[nWaveNumber].block[nCntBlock].pos.x, m_aWave[nWaveNumber].block[nCntBlock].pos.y, pPlayer3D->GetPos().z + MAX_INTERVALPOS);	// 位置の代入

						switch (m_aWave[nWaveNumber].block[nCntBlock].nType)
						{
						case 0:
							CBaseBlockX::Create(pos, Scale);
							break;
						case 1:
							CBreakBaseBlockX::Create(pos, Scale);
							break;
						}
					}
				}
			}
			pObj = pObjectNext;		// 次のオブジェクトを代入

		}
	}
}