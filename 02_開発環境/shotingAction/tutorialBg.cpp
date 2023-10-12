// =======================================================
//
// �X�^�[�g��ʔw�i����(startBg.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"tutorialBg.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Texture.h"

// �}�N����`
#define MAX_SCALE	(D3DXVECTOR2(100.0f,50.0f))	// �X�P�[���̍ő�
//= == == == == == == == == == == == == == == == == == =
// �R���X�g���N�^
//====================================
CTutorialBg::CTutorialBg()
{
	// �p�����[�^�[������
	m_nTexType = 0;
	m_nIdxTexture = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//====================================
// �f�X�g���N�^
//====================================
CTutorialBg::~CTutorialBg()
{
}
//====================================
// ����������
//====================================
HRESULT CTutorialBg::Init(void)
{
	CTexture*pTexture = CManager::GetCTexture();
	CObject2D::Init();
	// �ʒu���̐ݒ�
	CObject2D::SetPos(m_pos);
	CObject2D::SetScale(MAX_SCALE.x, MAX_SCALE.y);

	// �e�N�X�`���̓ǂݍ���
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\tutorial001.png");

	// �e�N�X�`���̓ǂݍ���
	CObject2D::BindTexture(m_nIdxTexture);

	return S_OK;
}
//======================================
// �I������
//=====================================
void CTutorialBg::Uninit(void)
{
	CObject::Relese();
}
//======================================
// �X�V����
//======================================
void CTutorialBg::Update(void)
{
	CObject2D::Update();
}
//======================================
// �`�揈��
//======================================
void CTutorialBg::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}
//======================================
// ��������
//======================================
CTutorialBg *CTutorialBg::Create(D3DXVECTOR3 pos)
{
	CTutorialBg * pTutorialBg;

	// �I�u�W�F�N�g2D�̐���
	pTutorialBg = new CTutorialBg;

	// �ʒu�̐ݒ�
	pTutorialBg->Setpos(pos);

	// ����������
	pTutorialBg->Init();

	return pTutorialBg;
}
