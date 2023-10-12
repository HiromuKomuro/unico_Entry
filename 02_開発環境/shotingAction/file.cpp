//====================================================================
//
//�t�@�C������[File.cpp]
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

//�}�N����`
#define MODEL_MOVE			(3)
#define PLAYER_FAR			(1500.0f)	// �v���C���[�Ƃ̋���

//========================================
// �R���X�g���N�^
//========================================
CFile::CFile()
{
	m_nNum = 0;
	m_pos = { 0,0,0 };
}
//========================================
// �f�X�g���N�^
//========================================
CFile::~CFile()
{
}
//========================================
// �}�b�v���[�h����
//========================================
HRESULT CFile::MapLoad(const char* pFilename, TYPE type, CBlockManager::Wave*m_Wave,int *pNumSummon)
{
	FILE*pFile;
	char aDataSearch[256] = {};	// �����p������
	D3DXVECTOR3 posSet;	// �ݒu����p�̈ʒu
	int nNumSummon = 0;

	// �t�@�C�����J��
	pFile = fopen(pFilename, "r");

	if (pFile != NULL)
	{// �t�@�C�����J�����ꍇ�A
		while (1)
		{
			fscanf(pFile, "%s", aDataSearch); // ����
			if (!strcmp(aDataSearch, "END"))
			{
				pNumSummon[0] = nNumSummon;	// ����
				// �t�@�C�������
				fclose(pFile);
				return S_OK;

			}
			else if (!strcmp(aDataSearch, "SET_NUMBER"))
			{
				fscanf(pFile, "%d", &nNumSummon);	// ���Ԗڂ̃E�F�[�u�̓���
				nNumSummon--;
			}
			else if (!strcmp(aDataSearch, "SET"))
			{
				// �ʒu�̎擾
				fscanf(pFile, "%f", &posSet.x);
				fscanf(pFile, "%f", &posSet.y);
				fscanf(pFile, "%f", &posSet.z);

				switch (type)	// ��������I�u�W�F�N�g�̎��
				{
				case TYPE_BLOCK:
					int nType;
					 
					// �^�C�v�̎擾
					fscanf(pFile, "%d", &nType);

					// �u���b�N�̐ݒ�
					m_Wave[nNumSummon].block[m_Wave[nNumSummon].nNumBlock].nType = nType;
					m_Wave[nNumSummon].block[m_Wave[nNumSummon].nNumBlock].pos = posSet;
					m_Wave[nNumSummon].nNumBlock++;	// �����𑝂₷
					break;
				}
			}
			
			
			// ����
		}
	}

	return NULL;
}
//========================================
// �������ݏ���
//========================================
HRESULT CFile::Write(const char* pFilename, TYPE type,int Score)
{
	FILE*pFile;
	int nNumSummon = 0;
	int nScoreRank[MAX_SCORE];

	// �t�@�C�����J��
	pFile = fopen(pFilename, "r");

	if (pFile != NULL)
	{// �t�@�C�����J�����ꍇ�A

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

	// �t�@�C�����J��
	pFile = fopen(pFilename, "w");

	if (pFile != NULL)
	{// �t�@�C�����J�����ꍇ�A
		
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
	// �t�@�C�����J��
	pFile = fopen("data\\FILE\\MyScore.txt", "w");

	if (pFile != NULL)
	{// �t�@�C�����J�����ꍇ�A	
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
// �ǂݍ��ݏ���
//========================================
HRESULT CFile::ScoreLoad(const char *pFilename,int *pScore,bool bMyScore)
{
	FILE*pFile;
	int nScore = 0;

	// �t�@�C�����J��
	pFile = fopen(pFilename, "r");

	if (pFile != NULL)
	{// �t�@�C�����J�����ꍇ�A	
		if (bMyScore == false)
		{// �����̃X�R�A����Ȃ��ꍇ
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
