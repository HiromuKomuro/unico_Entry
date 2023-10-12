//====================================================================
//
//ファイル処理[File.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include<stdio.h>

#include"main.h"
#include"file.h"
#include"Bullet.h"
#include"Manager.h"
#include"renderer.h"
#include"BlockXbase.h"
#include"Player3D.h"
#include"Score.h"
#include"RankingManager.h"

//マクロ定義
#define MODEL_MOVE			(3)
#define PLAYER_FAR			(1500.0f)	// プレイヤーとの距離

//========================================
// コンストラクタ
//========================================
CFile::CFile()
{
	m_nNum = 0;
	m_pos = { 0,0,0 };
}
//========================================
// デストラクタ
//========================================
CFile::~CFile()
{
}
//========================================
// マップロード処理
//========================================
HRESULT CFile::MapLoad(const char* pFilename, TYPE type, CBlockManager::Wave*m_Wave,int *pNumSummon)
{
	FILE*pFile;
	char aDataSearch[256] = {};	// 検索用文字列
	D3DXVECTOR3 posSet;	// 設置する用の位置
	int nNumSummon = 0;

	// ファイルを開く
	pFile = fopen(pFilename, "r");

	if (pFile != NULL)
	{// ファイルが開けた場合、
		while (1)
		{
			fscanf(pFile, "%s", aDataSearch); // 検索
			if (!strcmp(aDataSearch, "END"))
			{
				pNumSummon[0] = nNumSummon;	// 総数
				// ファイルを閉じる
				fclose(pFile);
				return S_OK;

			}
			else if (!strcmp(aDataSearch, "SET_NUMBER"))
			{
				fscanf(pFile, "%d", &nNumSummon);	// 何番目のウェーブの入手
				nNumSummon--;
			}
			else if (!strcmp(aDataSearch, "SET"))
			{
				// 位置の取得
				fscanf(pFile, "%f", &posSet.x);
				fscanf(pFile, "%f", &posSet.y);
				fscanf(pFile, "%f", &posSet.z);

				switch (type)	// 生成するオブジェクトの種類
				{
				case TYPE_BLOCK:
					int nType;
					 
					// タイプの取得
					fscanf(pFile, "%d", &nType);

					// ブロックの設定
					m_Wave[nNumSummon].block[m_Wave[nNumSummon].nNumBlock].nType = nType;
					m_Wave[nNumSummon].block[m_Wave[nNumSummon].nNumBlock].pos = posSet;
					m_Wave[nNumSummon].nNumBlock++;	// 総数を増やす
					break;
				}
			}
			
			
			// 生成
		}
	}

	return NULL;
}
//========================================
// 書き込み処理
//========================================
HRESULT CFile::Write(const char* pFilename, TYPE type,int Score)
{
	FILE*pFile;
	int nNumSummon = 0;
	int nScoreRank[MAX_SCORE];

	// ファイルを開く
	pFile = fopen(pFilename, "r");

	if (pFile != NULL)
	{// ファイルが開けた場合、

		for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{
			fscanf(pFile, "%d", &nScoreRank[nCntScore]);

		}
		fclose(pFile);

	}
	else
	{
		return NULL;
	}

	int nScorekeep[MAX_SCORE] = {};
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		if (Score > nScoreRank[nCntScore])
		{
			nScorekeep[nCntScore] = nScoreRank[nCntScore];

			for (int nCnt = nCntScore + 1; nCnt < MAX_SCORE; nCnt++)
			{
				nScorekeep[nCnt] = nScoreRank[nCnt];
				nScoreRank[nCnt] = nScorekeep[nCnt - 1];

			}
			nScoreRank[nCntScore] = Score;
			break;
		}
	}

	// ファイルを開く
	pFile = fopen(pFilename, "w");

	if (pFile != NULL)
	{// ファイルが開けた場合、
		
		for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{
			fprintf(pFile, "%d", nScoreRank[nCntScore]);
			fprintf(pFile, "%s", "\n");
		}
		fclose(pFile);
	}
	else
	{
		return NULL;
	}
	// ファイルを開く
	pFile = fopen("data\\FILE\\MyScore.txt", "w");

	if (pFile != NULL)
	{// ファイルが開けた場合、	
		fprintf(pFile, "%d", Score);
		fclose(pFile);
	}
	else
	{
		return NULL;
	}
	return S_OK;
}
//========================================
// 読み込み処理
//========================================
HRESULT CFile::ScoreLoad(const char *pFilename,int *pScore,bool bMyScore)
{
	FILE*pFile;
	int nScore = 0;

	// ファイルを開く
	pFile = fopen(pFilename, "r");

	if (pFile != NULL)
	{// ファイルが開けた場合、	
		if (bMyScore == false)
		{// 自分のスコアじゃない場合
			for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
			{
				fscanf(pFile, "%d", &pScore[nCntScore]);
			}
		}
		else
		{
			fscanf(pFile, "%d", pScore);
		}

		fclose(pFile);
		return S_OK;

	}
	else
	{
		return NULL;
	}


}
