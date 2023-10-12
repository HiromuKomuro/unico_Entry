// =======================================================
//
// �Q�[������(Game.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include<stdio.h>

#include"Manager.h"
#include"game.h"
#include"object.h"
#include"object2D.h"
#include"renderer.h"
#include"input.h"
#include"bullet.h"
#include"Explosion.h"
#include"Effect.h"
#include"sound.h"
#include"Score.h"
#include"Camera.h"
#include"light.h"
#include"Object3D.h"
#include"billboard.h"
#include"model.h"
#include"Texture.h"
#include"Player3D.h"
#include"file.h"
#include"BlockXbase.h"
#include"BlockManager.h"
#include"MeshCylinder.h"
#include"Fade.h"
#include"Time.h"
#include"Test.h"

// �}�N����`
#define PLAYER_INITPOS	(D3DXVECTOR3(0.0f, 800.0f, -2000.0f))	// �v���C���[�̏����ʒu

// �ÓI�����o�ϐ��錾
CBlockManager*CGame::s_pBlockManager = NULL;
CScore * CGame::s_pScore = NULL;
bool CGame::m_bPause = false;

//====================================
// �R���X�g���N�^
//====================================
CGame::CGame()
{

}
//====================================
// �f�X�g���N�^
//====================================
CGame::~CGame()
{

}
//====================================
// ����������
//====================================
HRESULT CGame::Init(void)
{
	if (s_pBlockManager != NULL)
	{
		// �u���b�N�}�l�[�W���[�̊J��
		s_pBlockManager->Uninit();
		delete s_pBlockManager;
		s_pBlockManager = NULL;
	}
	s_pBlockManager = new CBlockManager;	// �u���b�N�}�l�[�W���[�̃C���X�^���X����

	// �u���b�N�}�l�[�W���[�̏������ݒ�
	if (FAILED(s_pBlockManager->Init()))
	{//���������������s�����ꍇ

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
	if (FAILED(s_pScore->Init(D3DXVECTOR3(800.0f, 40.0f, 0.0f))))
	{//���������������s�����ꍇ

		return -1;

	}

	// ���b�V���V�����_�[�̐���
	CMeshClynder::Create();

	// 3D�v���C���[�̐���
	CPlayer3D::Create(PLAYER_INITPOS);
	
	// �e�X�g�̐���
	//CTest::Create();
	return S_OK;
}
//======================================
// �I������
//=====================================
void CGame::Uninit(void)
{
	// �S�I�u�W�F�N�g�̏I������
	CObject::ReleseAll();

	// �u���b�N�}�l�[�W���[�̔j��
	if (s_pBlockManager != NULL)
	{
		// �I������
		s_pBlockManager->Uninit();
		delete s_pBlockManager;	// �u���b�N�}�l�[�W���[�̊J��
		s_pBlockManager = NULL;
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
void CGame::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CFade*pFade = CManager::GetCFade();
	int Fade;

	if (pInputKeyboard->GetKeyboardTrigger(DIK_F1) == true)
	{
		if (m_bPause == false)
		{//�f�o�b�N�\����OFF�̎�

		 //�|�[�Y�\����ON�ɂ���
			m_bPause = true;
		}
		else
		{//�f�o�b�N�\����ON�̎�

		 //�|�[�Y�\����OFF�ɂ���
			m_bPause = false;
		}
	}

	if (s_pBlockManager != NULL)
	{
		s_pBlockManager->Update();
	}

	//�t�F�[�h��Ԃ��擾
	Fade = pFade->Get();

	//if (Fade == CFade::FADE_NONE)
	//{//�t�F�[�h��Ԃ������Ȃ��Ƃ�
	//	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) == true)
	//	{//����L�[�������ꂽ		
	//	 //�t�F�[�h�̐ݒ�(�Q�[����ʂɈڍs)
	//		pFade->Set(CScene::MODE_REZULT);
	//	}
	//}

}
//======================================
// �`�揈��
//======================================
void CGame::Draw(void)
{
}

