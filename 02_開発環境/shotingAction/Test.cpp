// =======================================================
//
// �e�X�g����(Test.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"Test.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Texture.h"


//= == == == == == == == == == == == == == == == == == =
// �R���X�g���N�^
//====================================
CTest::CTest()
{
	m_pTexture = NULL;
	m_Color = D3DCOLOR_RGBA(255, 255, 255, 255);
}

//====================================
// �f�X�g���N�^
//====================================
CTest::~CTest()
{
}
//====================================
// ����������
//====================================
HRESULT CTest::Init(void)
{
	CTexture*pTexture = CManager::GetCTexture();

	CObject2D::Init();
	// �ʒu���̐ݒ�
	CObject2D::SetPos(D3DXVECTOR3(100.0f,600.0f,0.0f));
	CObject2D::SetScale(300.0f, 200.0f);
	CObject2D::SetCol(m_Color);

	return S_OK;
}
//======================================
// �I������
//=====================================
void CTest::Uninit(void)
{
	CObject2D::Uninit();
}
//======================================
// �X�V����
//======================================
void CTest::Update(void)
{
	CObject2D::Update();
}
//======================================
// �`�揈��
//======================================
void CTest::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();			// �����_���[�̏������

	LPDIRECT3DTEXTURE9 pTexture = pRenderer->GetTextureMT();

	CObject2D::SetTexture(m_pTexture);

	// �`�揈��
	CObject2D::Draw();

}
//======================================
// ��������
//======================================
CTest *CTest::Create(LPDIRECT3DTEXTURE9 texture, D3DCOLOR color)
{
	CTest *pTest;
	// �I�u�W�F�N�g2D�̐���
	pTest = new CTest;

	// �e�N�X�`���̐ݒ�
	pTest->SetTexture(texture);

	// �F�̐ݒ�
	pTest->SetCol(color);

	// ����������
	pTest->Init();
	

	return pTest;
}
