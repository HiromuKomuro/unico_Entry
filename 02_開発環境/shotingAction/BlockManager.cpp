//====================================================================
//
//�u���b�N�Ǘ�����[BlockManager.cpp]
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

// �}�N����`
#define MAX_INTERVAL	(220)		// �C���^�[�o���̎���
#define MAX_INTERVALPOS	(1700.0f)	// �C���^�[�o���̈ʒu
#define MAX_CYLINDER_Z	(1800.0f * 7.0f)	// �V�����_�[�̈ʒu
//========================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//========================================
CBlockManager::~CBlockManager()
{
}
//========================================
//����������
//========================================
HRESULT CBlockManager::Init(void)
{
	//  time�֐����g���������̎�̐ݒ�
	srand((unsigned int)time(NULL));

	// �}�b�v�����[�h����
	if (FAILED(CFile::MapLoad("data\\FILE\\Block.txt", CFile::TYPE_BLOCK, &m_aWave[0], &m_nNumSummon)))
	{//�G�l�~�[�̃��[�h�����s�����ꍇ
	}
	
	return S_OK;
}
//========================================
// �I������
//========================================
void CBlockManager::Uninit(void)
{
}
//=======================================
// �X�V����
//=======================================
void CBlockManager::Update(void)
{
	int nWaveNumber = 0;
	m_nCounterSummon++;

	// �v���C���[�̏��̓���
	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		CObject *pObj = CObject::GetTop(nCntPri);	// �擪�̃I�u�W�F�N�g����

		while (pObj != NULL)
		{
			CObject *pObjectNext = pObj->GetNext();	// ���̃I�u�W�F�N�g��ۑ�

			//��ނ��擾
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

					D3DXVECTOR3 pos = {};	// �ʒu
					D3DXVECTOR3 Scale = { 1.0f,1.0f,1.0f };	// �傫��

					nWaveNumber = rand() % 5 + 0;

					for (int nCntBlock = 0; nCntBlock < m_aWave[nWaveNumber].nNumBlock; nCntBlock++)
					{
						pos = D3DXVECTOR3(m_aWave[nWaveNumber].block[nCntBlock].pos.x, m_aWave[nWaveNumber].block[nCntBlock].pos.y, pPlayer3D->GetPos().z + MAX_INTERVALPOS);	// �ʒu�̑��

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
			pObj = pObjectNext;		// ���̃I�u�W�F�N�g����

		}
	}
}