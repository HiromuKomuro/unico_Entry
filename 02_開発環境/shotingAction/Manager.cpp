// =======================================================
//
// �}�l�[�W���[����(Manager.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include<stdio.h>

#include"Manager.h"
#include"renderer.h"
#include"input.h"
#include"sound.h"
#include"Camera.h"
#include"light.h"
#include"Texture.h"
#include"TItle.h"
#include"game.h"
#include"rezult.h"
#include"Fade.h"

// �ÓI�����o�ϐ���
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CSound *CManager::m_pSound = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CTexture *CManager::m_pTexture = NULL;
CBlockManager* CManager::m_pBlockManager = NULL;
CScene* CManager::s_pScene = NULL;
CFade *CManager::s_pFade = NULL;
//====================================
// �R���X�g���N�^
//====================================
CManager::CManager()
{

}
//====================================
// �f�X�g���N�^
//====================================
CManager::~CManager()
{

}
//====================================
// ����������
//====================================
HRESULT CManager::Init(HINSTANCE hInstance,HWND hWnd, BOOL bWindow)
{
	// �����_���[�̐���
	if (m_pRenderer != NULL)
	{
		// �����_���[�̊J��
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	m_pRenderer = new CRenderer;	// �����_���[�̃C���X�^���X����

	// �C���v�b�g�̐���
	if (m_pInputKeyboard != NULL)
	{
		// �C���v�b�g�̊J��
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
	m_pInputKeyboard = new CInputKeyboard;	// �L�[�{�[�h�̃C���X�^���X����

	// �T�E���h�̐���
	if (m_pSound != NULL)
	{
		// �T�E���h�̊J��
		delete m_pSound;
		m_pSound = NULL;
	}
	m_pSound = new CSound;	// �T�E���h�̃C���X�^���X����

	// �J�����̐���
	if (m_pCamera != NULL)
	{
		// �J�����̊J��
		delete m_pCamera;
		m_pCamera = NULL;
	}
	m_pCamera = new CCamera;	// �J�����̃C���X�^���X����

	// ���C�g�̐���
	if (m_pLight != NULL)
	{
		// ���C�g�̊J��
		delete m_pLight;
		m_pLight = NULL;
	}
	m_pLight = new CLight;	// ���C�g�̃C���X�^���X����

	// �e�N�X�`���̐���
	if (m_pTexture != NULL)
	{
		// �e�N�X�`���̊J��
		delete m_pTexture;
		m_pTexture = NULL;
	}
	m_pTexture = new CTexture;	// �e�N�X�`���̃C���X�^���X����

	// �V�[���̐���
	if (s_pScene != NULL)
	{
		// �V�[���̊J��
		delete s_pScene;
		s_pScene = NULL;
	}
	s_pScene = new CTitle;	// �V�[���̃C���X�^���X����

	// �t�F�C�h�̐���
	if (s_pFade != NULL)
	{
		// �V�[���̊J��
		delete s_pFade;
		s_pFade = NULL;
	}
	s_pFade = new CFade;	// �V�[���̃C���X�^���X����

	// �����_���[�̏������ݒ�
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{//���������������s�����ꍇ

		return -1;

	}

	// �C���v�b�g�̏������ݒ�
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{//���������������s�����ꍇ

		return -1;

	}

	// �T�E���h�̏������ݒ�
	if (FAILED(m_pSound->Init(hWnd)))
	{//���������������s�����ꍇ

		return -1;

	}
	// �J�����̏������ݒ�
	if (FAILED(m_pCamera->Init()))
	{//���������������s�����ꍇ

		return -1;

	}
	// ���C�g�̏������ݒ�
	if (FAILED(m_pLight->Init()))
	{//���������������s�����ꍇ

		return -1;

	}
	// �e�N�X�`���̏������ݒ�
	if (FAILED(m_pTexture->Load()))
	{//���������������s�����ꍇ

		return -1;

	}	

	//// �V�[���̏������ݒ�
	//if (FAILED(s_pScene->Init()))
	//{//���������������s�����ꍇ

	//	return -1;

	//}
	// �t�F�C�h�̏������ݒ�
	if (FAILED(s_pFade->Init(CScene::MODE_TITLE)))
	{//���������������s�����ꍇ

		return -1;

	}
	return S_OK;
}
//======================================
// �I������
//=====================================
void CManager::Uninit(void)
{
	// �S�I�u�W�F�N�g�̏I������
	CObject::ReleseAll();

	// �����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		//�I������
		m_pRenderer->Uninit();
		delete m_pRenderer;			// �����_���[�̊J��
		m_pRenderer = NULL;
	}
	// �L�[�{�[�h�̔j��
	if (m_pInputKeyboard != NULL)
	{
		//�I������
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;	// �L�[�{�[�h�̊J��
		m_pInputKeyboard = NULL;
	}
	// �T�E���h�̔j��
	if (m_pSound != NULL)
	{
		//�I������
		m_pSound->Uninit();
		delete m_pSound;	// �T�E���h�̊J��
		m_pSound = NULL;
	}
	// �J�����̔j��
	if (m_pCamera != NULL)
	{
		//�I������
		m_pCamera->Uninit();
		delete m_pCamera;	// �J�����̊J��
		m_pCamera = NULL;
	}
	// ���C�g�̔j��
	if (m_pLight != NULL)
	{
		//�I������
		m_pLight->Uninit();
		delete m_pLight;	// ���C�g�̊J��
		m_pLight = NULL;
	}
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		// �I������
		m_pTexture->UnLoad();
		delete m_pTexture;	// �e�N�X�`���̊J��
		m_pTexture = NULL;
	}
	// �V�[���̔j��
	if (s_pScene != NULL)
	{
		// �I������
		s_pScene->Uninit();
		delete s_pScene;	// �V�[���̊J��
		s_pScene = NULL;
	}
	// �t�F�[�h�̔j��
	if (s_pFade != NULL)
	{
		// �I������
		s_pFade->Uninit();
		delete s_pFade;	// �t�F�[�h�̊J��
		s_pFade = NULL;
	}
}
//======================================
// �X�V����
//======================================
void CManager::Update(void)
{
	if (m_pRenderer != NULL)
	{
		// �����_���[�̍X�V����
		m_pRenderer->Update();
	}
	if (m_pInputKeyboard != NULL)
	{
		// �L�[�{�[�h�̍X�V����
		m_pInputKeyboard->Update();
	}
	if (s_pScene != NULL)
	{
		// �V�[���̍X�V����
		s_pScene->Update();
	}
	if (s_pFade != NULL)
	{
		// �t�F�C�h�̍X�V����
		s_pFade->Update();
	}
}
//======================================
// �`�揈��
//======================================
void CManager::Draw(void)
{
	// �����_���[�̕`�揈��
	m_pRenderer->Draw();

	if (s_pScene != NULL)
	{
		// �V�[���̕`�揈��
		s_pScene->Draw();
	}
	if (s_pFade != NULL)
	{
		// �t�F�C�h�̕`�揈��
		s_pFade->Draw();
	}
}
//====================================
// �R���X�g���N�^
//====================================
CScene::CScene()
{
}
//====================================
// �f�X�g���N�^
//====================================
CScene::~CScene()
{

}
//====================================
// ������
//====================================
HRESULT CScene::Init(void)
{
	return S_OK;
}
//====================================
// �I������
//====================================
void CScene::Uninit(void)
{

}
//====================================
// �X�V����
//====================================
void CScene::Update(void)
{

}
//====================================
// �`�揈��
//====================================
void CScene::Draw(void)
{

}
//======================================
// �V�[���̐�������
//======================================
CScene *CScene::Create(MODE mode)
{
	CScene *pScene;
	
	switch (mode)
	{
	case CScene::MODE_TITLE:
		// �C���X�^���X�̐���
		pScene = new CTitle();
		break;
	case CScene::MODE_GAME:
		// �C���X�^���X�̐���
		pScene = new CGame();
		break;
	case CScene::MODE_REZULT:
		// �C���X�^���X�̐���
		pScene = new CRezult();
		break;
	default:
		// �C���X�^���X�̐���
		pScene = new CRezult();
		break;
	}
	// ���[�h�̐ݒ�
	pScene->SetMode(mode);

	// �V�[���̏�����
	pScene->Init();

	return pScene;
}
//======================================
// ���[�h�̐ݒ菈��
//======================================
void CManager::SetMode(CScene::MODE mode)
{
	// �T�E���h�̒�~
	m_pSound->StopSound();

	// ���݂̃��[�h�̔j��
	if (s_pScene != NULL)
	{
		// �I������
		s_pScene->Uninit();
		delete s_pScene;	// �V�[���̊J��
		s_pScene = NULL;
	}

	// �V�������[�h�̐���
	s_pScene = CScene::Create(mode);
}
