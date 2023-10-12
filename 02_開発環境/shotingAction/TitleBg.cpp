// =======================================================
//
// �w�i����(bg.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"TitleBg.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Texture.h"

#define MAX_SCALE	(D3DXVECTOR2(300.0f,100.0f))	// �X�P�[���̍ő�
//= == == == == == == == == == == == == == == == == == =
// �R���X�g���N�^
//====================================
TitleBg::TitleBg()
{
	// �p�����[�^�[������
	m_nTexType = 0;
	m_nIdxTexture = 0;
}

//====================================
// �f�X�g���N�^
//====================================
TitleBg::~TitleBg()
{
}
//====================================
// ����������
//====================================
HRESULT TitleBg::Init(void)
{
	CTexture*pTexture = CManager::GetCTexture();

	CObject2D::Init();
	// �ʒu���̐ݒ�
	CObject2D::SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2,200.0f,0.0f));
	CObject2D::SetScale(MAX_SCALE.x, MAX_SCALE.y);

	// �e�N�X�`���̓ǂݍ���
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\title000.png");

	BindTexture(m_nIdxTexture);

	return S_OK;
}
//======================================
// �I������
//=====================================
void TitleBg::Uninit(void)
{
	CObject::Relese();
}
//======================================
// �X�V����
//======================================
void TitleBg::Update(void)
{
	CObject2D::Update();
}
//======================================
// �`�揈��
//======================================
void TitleBg::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}
//======================================
// ��������
//======================================
TitleBg *TitleBg::Create(void)
{
	TitleBg * pTitleBg;
	// �I�u�W�F�N�g2D�̐���
	pTitleBg = new TitleBg;

	// ����������
	pTitleBg->Init();

	return pTitleBg;
}
