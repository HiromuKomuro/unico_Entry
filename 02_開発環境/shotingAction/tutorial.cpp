// =======================================================
//
// �`���[�g���A������(tutorial.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"tutorial.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Texture.h"
#include"input.h"

//= == == == == == == == == == == == == == == == == == =
// �R���X�g���N�^
//====================================
CTutorial::CTutorial()
{
}

//====================================
// �f�X�g���N�^
//====================================
CTutorial::~CTutorial()
{
}
//====================================
// ����������
//====================================
HRESULT CTutorial::Init(void)
{
	CTexture*pTexture = CManager::GetCTexture();

	CObject2D::Init();
	// �ʒu���̐ݒ�
	CObject2D::SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f));
	CObject2D::SetScale(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	CObject2D::SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));

	// �e�N�X�`���̓ǂݍ���
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\tutorial.png");

	// �e�N�X�`���̓ǂݍ���
	CObject2D::BindTexture(m_nIdxTexture);

	return S_OK;
}
//======================================
// �I������
//=====================================
void CTutorial::Uninit(void)
{
	CObject2D::Uninit();
}
//======================================
// �X�V����
//======================================
void CTutorial::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	CObject2D::Update();

	//if (pInputKeyboard->GetKeyboardRelease(DIK_RETURN) == true)
	//{
	//	Uninit();	// �I�u�W�F�N�g�̍폜
	//}
}
//======================================
// �`�揈��
//======================================
void CTutorial::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}
//======================================
// ��������
//======================================
CTutorial *CTutorial::Create(void)
{
	CTutorial *pTutorial;

	// �I�u�W�F�N�g2D�̐���
	pTutorial = new CTutorial;

	// ����������
	pTutorial->Init();

	return pTutorial;
}
