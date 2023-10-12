// =======================================================
//
// ���Â��w�i����(dimbg.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"dimbg.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Texture.h"

//= == == == == == == == == == == == == == == == == == =
// �R���X�g���N�^
//====================================
CDimBg::CDimBg()
{
}

//====================================
// �f�X�g���N�^
//====================================
CDimBg::~CDimBg()
{
}
//====================================
// ����������
//====================================
HRESULT CDimBg::Init(void)
{
	CTexture*pTexture = CManager::GetCTexture();

	CObject2D::Init();
	// �ʒu���̐ݒ�
	CObject2D::SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f));
	CObject2D::SetScale(SCREEN_WIDTH, SCREEN_HEIGHT);
	CObject2D::SetCol(D3DCOLOR_RGBA(0, 0, 0, 100));

	return S_OK;
}
//======================================
// �I������
//=====================================
void CDimBg::Uninit(void)
{
	CObject2D::Uninit();
}
//======================================
// �X�V����
//======================================
void CDimBg::Update(void)
{
	CObject2D::Update();
}
//======================================
// �`�揈��
//======================================
void CDimBg::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}
//======================================
// ��������
//======================================
CDimBg *CDimBg::Create(void)
{
	CDimBg *pDimBg;
	// �I�u�W�F�N�g2D�̐���
	pDimBg = new CDimBg;

	// ����������
	pDimBg->Init();

	return pDimBg;
}
