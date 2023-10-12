// =======================================================
//
// �^�C�g������(Title.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include<stdio.h>

#include"Manager.h"
#include"TItle.h"
#include"input.h"
#include"TitleBg.h"
#include"Fade.h"
#include"Player3D.h"
#include"MeshCylinder.h"
#include"TitleManager.h"
#include"Object2D.h"

// �}�N����`
#define PLAYER_INITPOS	(D3DXVECTOR3(0.0f, 800.0f, -2000.0f))	// �v���C���[�̏����ʒu

// �ÓI�����o�ϐ�
CTitleManager * CTitle::s_pTitleManager = NULL;
//====================================
// �R���X�g���N�^
//====================================
CTitle::CTitle()
{
	m_bTutorial = false;
}
//====================================
// �f�X�g���N�^
//====================================
CTitle::~CTitle()
{
	s_pTitleManager = NULL;
}
//====================================
// ����������
//====================================
HRESULT CTitle::Init(void)
{
	TitleBg::Create();	// �^�C�g���̔w�i

	// ���b�V���V�����_�[�̐���
	CMeshClynder::Create();

	// 3D�v���C���[�̐���
	CPlayer3D::Create(PLAYER_INITPOS);

	// NULL�`�F�b�N
	if (s_pTitleManager != NULL)
	{
		s_pTitleManager->Uninit();
		delete s_pTitleManager;
		s_pTitleManager = NULL;
	}

	s_pTitleManager = new CTitleManager();	// �^�C�g���Ǘ��̃C���X�^���X�𐶐�

	s_pTitleManager->Init();	// ����������
	return S_OK;
}
//======================================
// �I������
//=====================================
void CTitle::Uninit(void)
{
	// NULL�`�F�b�N
	if (s_pTitleManager != NULL)
	{
		s_pTitleManager->Uninit();
		delete s_pTitleManager;
		s_pTitleManager = NULL;
	}

	// �S�I�u�W�F�N�g�̏I������
	CObject::ReleseAll();
}
//======================================
// �X�V����
//======================================
void CTitle::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	int Fade;

	if (pInputKeyboard->GetKeyboardTrigger(DIK_P) == true)
	{
		if (m_bTutorial == false)
		{//�f�o�b�N�\����OFF�̎�

		 //�|�[�Y�\����ON�ɂ���
			m_bTutorial = true;
		}
		else
		{//�f�o�b�N�\����ON�̎�

		 //�|�[�Y�\����OFF�ɂ���
			m_bTutorial = false;
		}
	}

	if (s_pTitleManager != NULL)
	{
		s_pTitleManager->Update();
	}
	
}
//======================================
// �`�揈��
//======================================
void CTitle::Draw(void)
{

}

