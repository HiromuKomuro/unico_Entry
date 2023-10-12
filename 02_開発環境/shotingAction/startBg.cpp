// =======================================================
//
// �X�^�[�g��ʔw�i����(startBg.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"startBg.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Texture.h"

// �}�N����`
#define MAX_SCALE	(D3DXVECTOR2(100.0f,50.0f))	// �X�P�[���̍ő�
//= == == == == == == == == == == == == == == == == == =
// �R���X�g���N�^
//====================================
CStartBg::CStartBg()
{
	// �p�����[�^�[������
	m_nTexType = 0;
	m_nIdxTexture = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//====================================
// �f�X�g���N�^
//====================================
CStartBg::~CStartBg()
{
}
//====================================
// ����������
//====================================
HRESULT CStartBg::Init(void)
{
	CTexture*pTexture = CManager::GetCTexture();
	CObject2D::Init();
	// �ʒu���̐ݒ�
	CObject2D::SetPos(m_pos);
	CObject2D::SetScale(MAX_SCALE.x, MAX_SCALE.y);

	// �e�N�X�`���̓ǂݍ���
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\start.png");

	// �e�N�X�`���̓ǂݍ���
	CObject2D::BindTexture(m_nIdxTexture);

	return S_OK;
}
//======================================
// �I������
//=====================================
void CStartBg::Uninit(void)
{
	CObject::Relese();
}
//======================================
// �X�V����
//======================================
void CStartBg::Update(void)
{
	CObject2D::Update();
}
//======================================
// �`�揈��
//======================================
void CStartBg::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}
//======================================
// ��������
//======================================
CStartBg *CStartBg::Create(D3DXVECTOR3 pos)
{
	CStartBg * pStartBg;

	// �I�u�W�F�N�g2D�̐���
	pStartBg = new CStartBg;

	// �ʒu�̐ݒ�
	pStartBg->Setpos(pos);

	// ����������
	pStartBg->Init();

	return pStartBg;
}
