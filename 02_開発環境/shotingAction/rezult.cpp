// =======================================================
//
// ���U���g����(Rezult.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include<stdio.h>

#include"Manager.h"
#include"rezult.h"
#include"input.h"
#include"Fade.h"
#include"RezultBg.h"
#include"RankingManager.h"
#include"file.h"
#include"RankingBg.h"
#include"MeshCylinder.h"
#include"Player3D.h"
#include"dimbg.h"
#include"Score.h"
#include"myscore.h"
#include"Bg.h"

// �}�N����`
#define MAX_SCORE	(3)	// �X�R�A�̍ő吔
#define MYSCORE_POS	(D3DXVECTOR3(450.0f,120.0f,0.0f))	// �X�R�A�̈ʒu
#define MYSCOREBG_POS	(D3DXVECTOR3(650.0f,50.0f,0.0f))	// �X�R�A�̈ʒu
#define RANKINGBG_POS	(D3DXVECTOR3(650.0f,350.0f,0.0f))	// �����̃X�R�A�̈ʒu
#define SCORE_POS	(D3DXVECTOR3(450.0f,500.0f,0.0f))	// �X�R�A�̈ʒu
#define PLAYER_INITPOS	(D3DXVECTOR3(0.0f, 800.0f, -2000.0f))	// �v���C���[�̏����ʒu

// �ÓI�����o�ϐ�
CRankingManager *CRezult::s_pRankingmanager = NULL;
CScore *CRezult::s_pScore = {};

//====================================
// �R���X�g���N�^
//====================================
CRezult::CRezult()
{
}
//====================================
// �f�X�g���N�^
//====================================
CRezult::~CRezult()
{

}
//====================================
// ����������
//====================================
HRESULT CRezult::Init(void)
{
	int nScore[MAX_SCORE] = { 0,0,0 };
	int nMyScore = 0;

	// 3D�v���C���[�̐���
	CPlayer3D::Create(PLAYER_INITPOS);

	// ���b�V���V�����_�[�̐���
	CMeshClynder::Create();

	// ���Â��w�i�̐���
	CDimBg::Create();

	// �w�i�̐���
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, RANKINGBG_POS.y + 150.0f, 0.0f), D3DXVECTOR2(300.0f * 1.5, 168.0f * 1.5), "data\\TEXTURE\\Rankingbg.png");

	// �����̃X�R�A�w�i�̐���
	CMyScore::Create(MYSCOREBG_POS);

	// �����L���O�w�i�̐���
	CRankingBg::Create(RANKINGBG_POS);

	// �}�b�v�����[�h����
	if (FAILED(CFile::ScoreLoad("data\\FILE\\Score.txt", &nScore[0], false)))
	{//�X�R�A�f�[�^�̃��[�h�����s�����ꍇ
		return -1;
	}
	// �}�b�v�����[�h����
	if (FAILED(CFile::ScoreLoad("data\\FILE\\MyScore.txt", &nMyScore, true)))
	{//�X�R�A�f�[�^�̃��[�h�����s�����ꍇ
		return -1;
	}

	if (s_pScore != NULL)
	{
		// �X�R�A�J��
		s_pScore->Uninit();
		delete s_pScore;
		s_pScore = NULL;
	}
	s_pScore = new CScore;	// �X�R�A�̃C���X�^���X����

	// �X�R�A�̏������ݒ�
	if (FAILED(s_pScore->Init(MYSCORE_POS)))
	{//���������������s�����ꍇ
		return -1;
	}

	// �X�R�A�̐ݒ�
	s_pScore->SetScore(nMyScore);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		CRankScore::Create(D3DXVECTOR3(SCORE_POS.x, SCORE_POS.y + (100.0f * nCntScore), SCORE_POS.z), nScore[nCntScore]);
	}

	return S_OK;
}
//======================================
// �I������
//=====================================
void CRezult::Uninit(void)
{
	// �S�I�u�W�F�N�g�̏I������
	CObject::ReleseAll();	

	// �����L���O�Ǘ��̐���
	if (s_pRankingmanager != NULL)
	{
		s_pRankingmanager->Uninit();
		delete s_pRankingmanager;
		s_pRankingmanager = NULL;
	}

	// �X�R�A�̔j��
	if (s_pScore != NULL)
	{
		// �I������
		s_pScore->Uninit();
		delete s_pScore;	// �X�R�A�̊J��
		s_pScore = NULL;
	}
}
//======================================
// �X�V����
//======================================
void CRezult::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	CFade*pFade = CManager::GetCFade();
	int Fade;

	//�t�F�[�h��Ԃ��擾
	Fade = pFade->Get();

	if (Fade == CFade::FADE_NONE)
	{//�t�F�[�h��Ԃ������Ȃ��Ƃ�
		if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) == true)
		{
			CManager::SetMode(CScene::MODE_TITLE);
		}
	}
}
//======================================
// �`�揈��
//======================================
void CRezult::Draw(void)
{
}

