// =======================================================
//
// �X�R�A����(Score.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"Score.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Explosion.h"
#include"Particle.h"
#include"Number.h"
#include"file.h"
// �}�N����`
#define MAX_NUMBERTEX			(10)		// �����̃e�N�X�`���̍ő吔
#define MAX_SCORE_SUMMONTIME	(120)		// �X�R�A�̐�������
#define NUMBER_DISTANCE			(55.0f)		// �i���o�[���̋���
#define MAX_SCALE				(D3DXVECTOR2(20.0f,30.0f))	// �X�R�A�̃X�P�[��

// �ÓI�����o�ϐ�
CNumber *CScore::m_apNumber[NUM_SCOREPLACE] = {};
int CScore::m_nScore = 0;
//====================================
// �R���X�g���N�^
//====================================
CScore::CScore()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//====================================
// �f�X�g���N�^
//====================================
CScore::~CScore()
{
}
//====================================
// ����������
//====================================
HRESULT CScore::Init(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < NUM_SCOREPLACE; nCnt++)
	{
		m_apNumber[nCnt] = new CNumber;	// �X�R�A�̃C���X�^���X����

		if (m_apNumber[nCnt] != NULL)
		{// �g�p����Ă���Ƃ�
			m_apNumber[nCnt]->Init();

			// �ʒu���̐ݒ�
			m_apNumber[nCnt]->SetPos(pos);
			m_apNumber[nCnt]->SetScale(MAX_SCALE.x, MAX_SCALE.y);
			m_apNumber[nCnt]->SetAnimeTex(((float)MAX_NUMBERTEX), 0.0f);
			pos.x += NUMBER_DISTANCE;
		}
	}
	return S_OK;
}
//======================================
// �I������
//=====================================
void CScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_SCOREPLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			//�X�R�A�̊J��
			//m_apNumber[nCnt]->Uninit();
		}
	}
	// �t�@�C���̏������ݏ���
	CFile::Write("data\\FILE\\Score.txt", CFile::TYPE_SCORE,m_nScore);

	m_nScore = 0;

}
//======================================
// �X�V����
//======================================
void CScore::Update(void)
{

}
//======================================
// �`�揈��
//======================================
void CScore::Draw(void)
{

}
//======================================
// ��������
//======================================
CScore *CScore::Create(const D3DXVECTOR3 pos)
{
	CScore *pScore;

	// �I�u�W�F�N�g2D�̐���
	pScore = new CScore();

	// �ʒu�̐ݒ�
	pScore->Setpos(pos);

	// ����������
	pScore->Init(pos);

	return pScore;
}
//======================================
// �X�R�A�̐ݒ菈��
//======================================
void CScore::SetScore(int nScore)
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
void CScore::AddScore(int nValue)
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
//====================================
// �R���X�g���N�^
//====================================
CAddScore::CAddScore()
{
	m_nScoreCnt = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nScore = 0;
	m_nAnimeCounter = 0;
}
//====================================
// �f�X�g���N�^
//====================================
CAddScore::~CAddScore()
{
}
//====================================
// ����������
//====================================
HRESULT CAddScore::Init(void)
{
	D3DXVECTOR3 pos = m_pos;
	for (int nCnt = 0; nCnt < NUM_SCOREPLACE; nCnt++)
	{
		m_apNumber[nCnt] = new CNumber;	// �X�R�A�̃C���X�^���X����

		if (m_apNumber[nCnt] != NULL)
		{// �g�p����Ă���Ƃ�
			m_apNumber[nCnt]->Init();

			// �ʒu���̐ݒ�
			m_apNumber[nCnt]->SetPos(pos);
			m_apNumber[nCnt]->SetScale(MAX_SCALE.x, MAX_SCALE.y);
			m_apNumber[nCnt]->SetAnimeTex(((float)MAX_NUMBERTEX), 0.0f);
			pos.x += NUMBER_DISTANCE;
		}
	}
	return S_OK;
}
//======================================
// �I������
//=====================================
void CAddScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_SCOREPLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			//�X�R�A�̊J��
			m_apNumber[nCnt]->Uninit();
		}
	}
	m_nScore = 0;

	CObject::Relese(); 
}
//======================================
// �X�V����
//======================================
void CAddScore::Update(void)
{
	D3DXVECTOR3 pos;
	m_nScoreCnt++;
	m_move.y += 0.01f;

	m_pos += m_move;

	pos = m_pos;
	for (int nCnt = 0; nCnt < NUM_SCOREPLACE; nCnt++)
	{
		m_apNumber[nCnt]->SetPos(pos);	// �ʒu�̐ݒ�
		pos.x += NUMBER_DISTANCE;
	}

	if (m_nScoreCnt % MAX_SCORE_SUMMONTIME == 0)
	{
		CAddScore::Uninit();
	}
}
//======================================
// �`�揈��
//======================================
void CAddScore::Draw(void)
{
}
//======================================
// �X�R�A�̐ݒ菈��
//======================================
void CAddScore::SetScore(int nScore)
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
// ��������
//======================================
CAddScore *CAddScore::Create(const D3DXVECTOR3 pos,const int nScore)
{
	CAddScore *pAddScore;

	// �I�u�W�F�N�g2D�̐���
	pAddScore = new CAddScore();

	// �ʒu�̐ݒ�
	pAddScore->Setpos(pos);

	// ����������
	pAddScore->Init();
	
	// �X�R�A�̐ݒ�
	pAddScore->SetScore(nScore);

	return pAddScore;
}
//====================================
// �R���X�g���N�^
//====================================
CRankScore::CRankScore()
{

}
//====================================
// �f�X�g���N�^
//====================================
CRankScore::~CRankScore()
{
}
//====================================
// ����������
//====================================
HRESULT CRankScore::Init(void)
{
	for (int nCnt = 0; nCnt < NUM_SCOREPLACE; nCnt++)
	{
		//if (m_apNumber[nCnt] != NULL)
		//{
		//	//�X�R�A�̊J��
		//	m_apNumber[nCnt]->Uninit();
		//	delete m_apNumber[nCnt];
		//	m_apNumber[nCnt] = NULL;
		//}
		m_apNumber[nCnt] = new CNumber;	// �X�R�A�̃C���X�^���X����

		if (m_apNumber[nCnt] != NULL)
		{// �g�p����Ă���Ƃ�
			m_apNumber[nCnt]->Init();

			// �ʒu���̐ݒ�
			m_apNumber[nCnt]->SetPos(D3DXVECTOR3(m_pos.x + (nCnt * 50.0f),m_pos.y,m_pos.z));
			m_apNumber[nCnt]->SetScale(20.0f, 30.0f);
			m_apNumber[nCnt]->SetAnimeTex(((float)MAX_NUMBERTEX), 0.0f);
		}
	}

	
	return S_OK;
}
//======================================
// �I������
//=====================================
void CRankScore::Uninit(void)
{
	m_nScore = 0;
	CObject::Relese();
}
//======================================
// �X�V����
//======================================
void CRankScore::Update(void)
{
}
//======================================
// �`�揈��
//======================================
void CRankScore::Draw(void)
{
}
//======================================
// ��������
//======================================
CRankScore *CRankScore::Create(const D3DXVECTOR3 pos, const int nScore)
{
	CRankScore *pAddScore;

	// �I�u�W�F�N�g2D�̐���
	pAddScore = new CRankScore();

	// �X�R�A�̐ݒ�
	pAddScore->Setpos(pos);

	// ����������
	pAddScore->Init();

	// �X�R�A�̐ݒ�
	pAddScore->SetScore(nScore);
	return pAddScore;
}
//======================================
// �X�R�A�̐ݒ菈��
//======================================
void CRankScore::SetScore(int score)
{
	int aTexU[NUM_SCOREPLACE];	//�e���̐����̊i�[

	int nScore = score;			//�X�R�A�̐ݒ�

	aTexU[0] = nScore % 100000000 / 10000000;
	aTexU[1] = nScore % 10000000 / 1000000;
	aTexU[2] = nScore % 1000000 / 100000;
	aTexU[3] = nScore % 100000 / 10000;
	aTexU[4] = nScore % 10000 / 1000;
	aTexU[5] = nScore % 1000 / 100;
	aTexU[6] = nScore % 100 / 10;
	aTexU[7] = nScore % 10 / 1;


	for (int nCnt = 0; nCnt < NUM_SCOREPLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// �g�p���ꂢ�Ă���Ƃ�
			m_apNumber[nCnt]->SetAnimeTex(MAX_NUMBERTEX, aTexU[nCnt]);
		}
	}
}