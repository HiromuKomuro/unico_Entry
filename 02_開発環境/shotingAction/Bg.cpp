// =======================================================
//
// �w�i����(bg.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"Bg.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Texture.h"

//= == == == == == == == == == == == == == == == == == =
// �R���X�g���N�^
//====================================
CBg::CBg()
{
	// �p�����[�^�[������
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR2(0.0f, 0.0f);
	m_pFilename = NULL;
	m_nTexType = 0;
	m_nIdxTexture = 0;
}

//====================================
// �f�X�g���N�^
//====================================
CBg::~CBg()
{
}
//====================================
// ����������
//====================================
HRESULT CBg::Init(void)
{
	CTexture*pTexture = CManager::GetCTexture();

	CObject2D::Init();
	// �ʒu���̐ݒ�
	CObject2D::SetPos(m_pos);
	CObject2D::SetScale(m_scale.x,m_scale.y);

	// �e�N�X�`���̓ǂݍ���
	m_nIdxTexture = pTexture->Regist(m_pFilename);

	BindTexture(m_nIdxTexture);

	return S_OK;
}
//======================================
// �I������
//=====================================
void CBg::Uninit(void)
{
	CObject2D::Relese();
}
//======================================
// �X�V����
//======================================
void CBg::Update(void)
{
	CObject2D::Update();
}
//======================================
// �`�揈��
//======================================
void CBg::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}
//======================================
// ��������
//======================================
CBg *CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR2 scale, char *pFilename)
{
	CBg * pBg;
	
	// �I�u�W�F�N�g2D�̐���
	pBg = new CBg;

	// �e��̐ݒ�
	pBg->Setpos(pos);
	pBg->Setscale(scale);
	pBg->SetFile(pFilename);

	// ����������
	pBg->Init();

	return pBg;
}
