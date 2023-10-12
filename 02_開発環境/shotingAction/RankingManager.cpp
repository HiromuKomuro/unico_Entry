//====================================================================
//
//�����L���O�Ǘ�����[RankingManager.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"RankingManager.h"
#include"Player3D.h"
#include"object.h"
#include"BlockXbase.h"
#include"file.h"

// �}�N����`
#define SCORE_POS	(D3DXVECTOR3(600.0f,200.0f,0.0f))	// �X�R�A�̈ʒu
//========================================
// �R���X�g���N�^
//========================================
CRankingManager::CRankingManager()
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_aScore[nCnt] = {};
	}
}
//========================================
// �f�X�g���N�^
//========================================
CRankingManager::~CRankingManager()
{
	
}
//========================================
//����������
//========================================
HRESULT CRankingManager::Init(int *pScore)
{
	for (int nCntScore= 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		m_aScore[nCntScore].Create(D3DXVECTOR3(SCORE_POS.x, SCORE_POS.y + (100.0f * nCntScore), SCORE_POS.z), pScore[nCntScore]);
	}
	return S_OK;
}
//========================================
// �I������
//========================================
void CRankingManager::Uninit(void)
{
}
//=======================================
// �X�V����
//=======================================
void CRankingManager::Update(void)
{

}