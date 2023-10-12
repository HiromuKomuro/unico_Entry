// =======================================================
//
// �w�i����(bg.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"RezultBg.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Texture.h"

//= == == == == == == == == == == == == == == == == == =
// �R���X�g���N�^
//====================================
CRezulteBg::CRezulteBg()
{
	// �p�����[�^�[������
	m_nTexType = 0;
	m_nIdxTexture = 0;
}

//====================================
// �f�X�g���N�^
//====================================
CRezulteBg::~CRezulteBg()
{
}
//====================================
// ����������
//====================================
HRESULT CRezulteBg::Init(void)
{
	CTexture*pTexture = CManager::GetCTexture();

	CObject2D::Init();
	// �ʒu���̐ݒ�
	CObject2D::SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f));
	CObject2D::SetScale(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	// �e�N�X�`���̓ǂݍ���
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\result.png");

	BindTexture(m_nIdxTexture);

	return S_OK;
}
//======================================
// �I������
//=====================================
void CRezulteBg::Uninit(void)
{
	CObject2D::Relese();
}
//======================================
// �X�V����
//======================================
void CRezulteBg::Update(void)
{
	CObject2D::Update();
}
//======================================
// �`�揈��
//======================================
void CRezulteBg::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();

}
//======================================
// ��������
//======================================
CRezulteBg *CRezulteBg::Create(void)
{
	CRezulteBg * pRezulteBg;
	// �I�u�W�F�N�g2D�̐���
	pRezulteBg = new CRezulteBg;

	// ����������
	pRezulteBg->Init();

	return pRezulteBg;
}
