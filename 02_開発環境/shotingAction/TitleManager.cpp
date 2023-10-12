//====================================================================
//
// �^�C�g���Ǘ�����[TitleManager.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"Manager.h"
#include"TitleManager.h"
#include"Player3D.h"
#include"object.h"
#include"BlockXbase.h"
#include"file.h"
#include"startBg.h"
#include"tutorialBg.h"
#include"endBg.h"
#include"input.h"
#include"Fade.h"
#include"tutorial.h"

// �}�N����`
#define LEFT_INITPOS	(D3DXVECTOR3(240.0f, 600.0f, 0.0f))		// ���̏����ʒu
#define CENTER_INITPOS	(D3DXVECTOR3(640.0f, 600.0f, 0.0f))		// �����̏����ʒu
#define RIGHT_INITPOS	(D3DXVECTOR3(1040.0f, 600.0f, 0.0f))	// �E�̏����ʒu

// �ÓI�����o�ϐ�
CStartBg *CTitleManager::s_pStartBg = NULL;
CTutorialBg *CTitleManager::s_pTutorialBg = NULL;
CEndBg *CTitleManager::s_pEndBg = NULL;
CTutorial *CTitleManager::s_pTutorial = NULL;

static const D3DXVECTOR3 ObjPos[3] = {
	LEFT_INITPOS,
	CENTER_INITPOS,
	RIGHT_INITPOS
};
static const D3DCOLOR ObjCol[3] = {
	D3DCOLOR_RGBA(255,255,255,155),
	D3DCOLOR_RGBA(0,0,255,155),
	D3DCOLOR_RGBA(255,255,255,155),
};
//========================================
// �R���X�g���N�^
//========================================
CTitleManager::CTitleManager()
{
	m_nCounterSelect = (int)TITLE_START;
	m_TitleSelect = TITLE_NONE;
}
//========================================
// �f�X�g���N�^
//========================================
CTitleManager::~CTitleManager()
{
	s_pStartBg = NULL;
	s_pTutorialBg = NULL;
	s_pEndBg = NULL;
	s_pTutorial = NULL;
}
//========================================
//����������
//========================================
HRESULT CTitleManager::Init(void)
{	
	for (int nCntObj = 0; nCntObj < TITLE_TUTORIAL; nCntObj++)
	{
		CObject2D::Create(ObjPos[nCntObj],ObjCol[nCntObj],D3DXVECTOR2(100.0f,100.0f));	// 2D�I�u�W�F�N�g�̐���
	}
	// �X�^�[�g�w�i�̐���
	if (s_pStartBg != NULL)
	{
		s_pStartBg->Uninit();
		delete s_pStartBg;
		s_pStartBg = NULL;
	}

	// �I���w�i�̐���
	if (s_pEndBg != NULL)
	{
		s_pEndBg->Uninit();
		delete s_pEndBg;
		s_pEndBg = NULL;
	}

	// �`���[�g���A���w�i�̐���
	if (s_pTutorialBg != NULL)
	{
		s_pTutorialBg->Uninit();
		delete s_pTutorialBg;
		s_pTutorialBg = NULL;
	}

	// �C���X�^���X�𐶐�
	s_pStartBg = new CStartBg();
	s_pEndBg = new CEndBg();
	s_pTutorialBg = new CTutorialBg();

	// ����������
	s_pStartBg->Init();
	s_pEndBg->Init();
	s_pTutorialBg->Init();

	// �ʒu�̐ݒ�
	s_pStartBg->SetPos(CENTER_INITPOS);
	s_pEndBg->SetPos(LEFT_INITPOS);
	s_pTutorialBg->SetPos(RIGHT_INITPOS);

	return S_OK;
}
//========================================
// �I������
//========================================
void CTitleManager::Uninit(void)
{
}
//=======================================
// �X�V����
//=======================================
void CTitleManager::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CFade*pFade = CManager::GetCFade();

	//�t�F�[�h��Ԃ��擾
	CFade::FADE Fade = pFade->Get();

	if (m_TitleSelect != TITLE_TUTORIAL)
	{// �`���[�g���A����ԈȊO�̎�
		if (pInputKeyboard->GetKeyboardRelease(DIK_LEFT) == true)
		{
			m_nCounterSelect--;	// �J�E���g�����Z
		}

		if (pInputKeyboard->GetKeyboardRelease(DIK_RIGHT) == true)
		{
			m_nCounterSelect++;	// �J�E���g�����Z
		}

		// �I���̃J�E���g���ő�A�ŏ��̎�
		if (m_nCounterSelect >= TITLE_MAX)
		{
			m_nCounterSelect = TITLE_END;
		}
		else if (m_nCounterSelect <= TITLE_NONE)
		{
			m_nCounterSelect = TITLE_TUTORIAL;
		}

		switch ((TITLE_SELECT)m_nCounterSelect)
		{
		case TITLE_END:
			s_pStartBg->SetPos(RIGHT_INITPOS);
			s_pEndBg->SetPos(CENTER_INITPOS);
			s_pTutorialBg->SetPos(LEFT_INITPOS);
			break;
		case TITLE_START:
			s_pStartBg->SetPos(CENTER_INITPOS);
			s_pEndBg->SetPos(LEFT_INITPOS);
			s_pTutorialBg->SetPos(RIGHT_INITPOS);
			break;
		case TITLE_TUTORIAL:
			s_pStartBg->SetPos(LEFT_INITPOS);
			s_pEndBg->SetPos(RIGHT_INITPOS);
			s_pTutorialBg->SetPos(CENTER_INITPOS);
			break;
		}

		if (pInputKeyboard->GetKeyboardRelease(DIK_RETURN) == true)
		{
			m_TitleSelect = (TITLE_SELECT)m_nCounterSelect;

			switch ((TITLE_SELECT)m_nCounterSelect)
			{
			case TITLE_END:
				//�E�C���h�E��j������(WM_DESTROY���b�Z�[�W)
				//DestroyWindow(hWnd);
				break;
			case TITLE_START:
				if (Fade == CFade::FADE_NONE)
				{//�t�F�[�h��Ԃ������Ȃ��Ƃ�
					 //�t�F�[�h�̐ݒ�(�Q�[����ʂɈڍs)
					pFade->Set(CScene::MODE_GAME);
				}
				break;
			case TITLE_TUTORIAL:
				s_pTutorial = new CTutorial();	// �C���X�^���X�̐���
				s_pTutorial->Init();				// ������
				break;
			}
		}
	}
	else
	{
		if (pInputKeyboard->GetKeyboardRelease(DIK_RETURN) == true)
		{
			if (Fade == CFade::FADE_NONE)
			{//�t�F�[�h��Ԃ������Ȃ��Ƃ�
			 //�t�F�[�h�̐ݒ�(�Q�[����ʂɈڍs)
				pFade->Set(CScene::MODE_GAME);
			}
		} 
	}
}