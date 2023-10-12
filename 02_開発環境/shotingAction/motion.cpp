//====================================================================
//
//���[�V��������[motion.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"motion.h"
#include"ObjectModel.h"

#include<stdio.h>
//========================================
// �R���X�g���N�^
//========================================
CMotion::CMotion()
{
	// �e���̏�����
	m_aInfo[0] = {};
	m_nCounter = 0;
	m_nKey = 0;
	m_nNumAll = 0;
	m_nNumKey = 0;
	m_nNumModel = 0;
	m_nType = 0;
	m_bFinish = true;
	m_bLoop = false;
}
//========================================
// �f�X�X�g���N�^
//========================================
CMotion::~CMotion()
{

}
//========================================
// �ݒ菈��
//========================================
void CMotion::Set(int nType)
{
	nType = m_nType;

	m_bLoop = false;	// ���[�v�������Ȃ�
	m_bFinish = false;	// �I�����Ă��Ȃ�


	m_aInfo[m_nType].aKeyInfo[0].Key[0].fPosx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[0].fPosy = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[0].fPosz = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[0].fRotx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[0].fRoty = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[0].fRotz = 0.0f;

	m_aInfo[m_nType].aKeyInfo[1].Key[0].fPosx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[0].fPosy = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[0].fPosz = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[0].fRotx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[0].fRoty = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[0].fRotz = 0.0f;

	m_aInfo[m_nType].aKeyInfo[0].Key[1].fPosx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[1].fPosy = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[1].fPosz = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[1].fRotx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[1].fRoty = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[1].fRotz = 0.0f;
					   
	m_aInfo[m_nType].aKeyInfo[1].Key[1].fPosx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[1].fPosy = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[1].fPosz = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[1].fRotx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[1].fRoty = 6.28f;
	m_aInfo[m_nType].aKeyInfo[1].Key[1].fRotz = 0.0f;

	m_aInfo[m_nType].aKeyInfo[0].Key[2].fPosx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[2].fPosy = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[2].fPosz = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[2].fRotx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[2].fRoty = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[2].fRotz = 0.0f;
							  
	m_aInfo[m_nType].aKeyInfo[1].Key[2].fPosx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[2].fPosy = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[2].fPosz = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[2].fRotx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[2].fRoty = 6.28f;
	m_aInfo[m_nType].aKeyInfo[1].Key[2].fRotz = 0.0f;

	m_aInfo[m_nType].aKeyInfo[0].nFrame = 40;
	m_aInfo[m_nType].aKeyInfo[1].nFrame = 30;
	m_aInfo[m_nType].aKeyInfo[2].nFrame = 20;


	// �S���f���̍X�V
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		D3DXVECTOR3 pos = m_ppObjectModel[nCntModel]->GetPos() + D3DXVECTOR3(m_aInfo[m_nType].aKeyInfo[nCntModel].Key[0].fPosx, m_aInfo[m_nType].aKeyInfo[nCntModel].Key[0].fPosy, m_aInfo[m_nType].aKeyInfo[nCntModel].Key[0].fPosz);
		D3DXVECTOR3 rot = m_ppObjectModel[nCntModel]->GetRot() + D3DXVECTOR3(m_aInfo[m_nType].aKeyInfo[nCntModel].Key[0].fRotx, m_aInfo[m_nType].aKeyInfo[nCntModel].Key[0].fRoty, m_aInfo[m_nType].aKeyInfo[nCntModel].Key[0].fRotz);
																										
		// �p�[�c�̈ʒu.������ݒ�
		m_ppObjectModel[nCntModel]->SetPos(pos);
		m_ppObjectModel[nCntModel]->SetRot(rot);
	}
}
//========================================
// �X�V����
//========================================
void CMotion::Update(void)
{
	KEY Key;

	if (m_bFinish == false)
	{
		// �S���f���̍X�V
		for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
		{
			Key.fPosx = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].Key[nCntModel].fPosx - m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fPosx;
			Key.fPosy = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].Key[nCntModel].fPosy - m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fPosy;
			Key.fPosz = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].Key[nCntModel].fPosz - m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fPosz;

			Key.fRotx = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].Key[nCntModel].fRotx - m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fRotx;
			Key.fRoty = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].Key[nCntModel].fRoty - m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fRoty;
			Key.fRotz = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].Key[nCntModel].fRotz - m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fRotz;

			D3DXVECTOR3 pos = m_ppObjectModel[nCntModel]->GetPos() + D3DXVECTOR3(m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fPosx + Key.fPosx * (m_nCounter % m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame),
				m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fPosy + Key.fPosy * (m_nCounter % m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame),
				m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fPosz + Key.fPosz * (m_nCounter % m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame));

			D3DXVECTOR3 rot = m_ppObjectModel[nCntModel]->GetRot() + D3DXVECTOR3(m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fRotx + Key.fRotx * (m_nCounter % m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame),
				m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fRoty + Key.fRoty * (m_nCounter % m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame),
				m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fRotz + Key.fRotz * (m_nCounter % m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame));

			// �p�[�c�̈ʒu.������ݒ�
			m_ppObjectModel[nCntModel]->SetPos(pos);

			m_ppObjectModel[nCntModel]->SetRot(rot);

		}
		m_nCounter++;	// �J�E���^�[�𑝉�

		if (m_nCounter > m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame)
		{// �Đ��t���[�����ɒB�����Ƃ�
			m_nKey++;		// �L�[��i�߂�
			m_nCounter = 0;	// �J�E���^�[��������

			if (m_nKey > m_nNumKey)
			{// �L�[�̑����ɒB�����Ƃ�
				if (m_bLoop == false)
				{// ���[�v�����Ȃ��Ƃ�
					m_bFinish = true;	// �I��������	
				}
				m_nKey = 0;	// �ŏ�����

			}
		}
	}
}
//========================================
// �C���t�H�̐ݒ菈��
//========================================
void CMotion::SetInfo(INFO info)
{
	m_aInfo[m_nNumAll] = info;

	m_nNumAll++;
}
//========================================
// ���f���̐ݒ菈��
//========================================
void CMotion::SetModel(CObjectModel**ppObjectModel,int nNumModel)
{
	m_ppObjectModel = ppObjectModel;	// �I�u�W�F�N�g���f��
	m_nNumModel = nNumModel;			// ���f���̑���
}