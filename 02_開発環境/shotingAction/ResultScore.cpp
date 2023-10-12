// =======================================================
//
// �X�R�A����(Score.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"ResultScore.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Explosion.h"
#include"Particle.h"
#include"Number.h"

// �}�N����`
#define MAX_NUMBERTEX	(10)	// �����̃e�N�X�`���̍ő吔

// �ÓI�����o�ϐ�
CNumber *CResultScore::m_apNumber[NUM_SCOREPLACE] = {};
int CResultScore::m_nScore = 0;
//====================================
// �R���X�g���N�^
//====================================
CResultScore::CResultScore()
{
}
//====================================
// �f�X�g���N�^
//====================================
CResultScore::~CResultScore()
{
	//m_apNumber[NUM_SCOREPLACE] = {};
}
//====================================
// ����������
//====================================
HRESULT CResultScore::Init(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < NUM_SCOREPLACE; nCnt++)
	{
		// �X�R�A�̐���
		//if (m_apNumber[nCnt] != NULL)
		//{
		//	// �X�R�A�̊J��
		//	m_apNumber[nCnt]->Uninit();
		//	delete m_apNumber[nCnt];
		//	m_apNumber[nCnt] = NULL;
		//}

		m_apNumber[nCnt] = new CNumber;	// �X�R�A�̃C���X�^���X����

		if (m_apNumber[nCnt] != NULL)
		{// �g�p����Ă���Ƃ�
			m_apNumber[nCnt]->Init();

			// �ʒu���̐ݒ�
			m_apNumber[nCnt]->SetPos(pos);
			m_apNumber[nCnt]->SetScale(20.0f, 30.0f);
			m_apNumber[nCnt]->SetAnimeTex(((float)MAX_NUMBERTEX), 0.0f);
			pos.x += 50.0f;
		}
	}
	return S_OK;
}
//======================================
// �I������
//=====================================
void CResultScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_SCOREPLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			// �X�R�A�̊J��
			//m_apNumber[nCnt]->Uninit();
			//delete m_apNumber[nCnt];
			//m_apNumber[nCnt] = NULL;
		}
	}
	m_nScore = 0;

}
//======================================
// �X�V����
//======================================
void CResultScore::Update(void)
{

}
//======================================
// �`�揈��
//======================================
void CResultScore::Draw(void)
{

}
//======================================
// ��������
//======================================
CResultScore *CResultScore::Create(const D3DXVECTOR3 pos)
{
	CResultScore *pScore;

	// �I�u�W�F�N�g2D�̐���
	pScore = new CResultScore();

	// ����������
	pScore->Init(pos);

	return pScore;
}
//======================================
// �X�R�A�̐ݒ菈��
//======================================
void CResultScore::SetScore(int nScore)
{
	int aTexU[NUM_SCOREPLACE];	//�e���̐����̊i�[


	m_nScore = nScore;			//�X�R�A�̐ݒ�

	aTexU[0] = m_nScore % 100000000 / 10000000;
	aTexU[1] = m_nScore % 10000000 / 1000000;
	aTexU[2] = m_nScore % 1000000 / 100000;
	aTexU[3] = m_nScore % 100000 / 10000;
	aTexU[4] = m_nScore % 10000 / 1000;
	aTexU[5] = m_nScore % 1000 / 100;
	aTexU[6] = m_nScore % 100 / 10;
	aTexU[7] = m_nScore % 10 / 1;


	for (int nCnt = 0; nCnt < NUM_SCOREPLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// �g�p���ꂢ�Ă���Ƃ�
			m_apNumber[nCnt]->SetAnimeTex(MAX_NUMBERTEX, aTexU[nCnt]);
		}
	}
}
//======================================
// �X�R�A�̉��Z����
//======================================
void CResultScore::AddScore(int nValue)
{
	int aTexU[NUM_SCOREPLACE];	//�e���̐����̊i�[
	
	// �X�R�A�̉��Z
 	m_nScore += nValue;

	aTexU[0] = m_nScore % 100000000 / 10000000;
	aTexU[1] = m_nScore % 10000000 / 1000000;
	aTexU[2] = m_nScore % 1000000 / 100000;
	aTexU[3] = m_nScore % 100000 / 10000;
	aTexU[4] = m_nScore % 10000 / 1000;
	aTexU[5] = m_nScore % 1000 / 100;
	aTexU[6] = m_nScore % 100 / 10;
	aTexU[7] = m_nScore % 10 / 1;

	for (int nCnt = 0; nCnt < NUM_SCOREPLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// �g�p���ꂢ�Ă���Ƃ�
			m_apNumber[nCnt]->SetAnimeTex(MAX_NUMBERTEX, aTexU[nCnt]);
		}
	}
}