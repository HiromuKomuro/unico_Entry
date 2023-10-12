//====================================================================
//
//�G�t�F�N�g����[Effect.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"Effect.h"
#include"Manager.h"
#include"renderer.h"
#include"Texture.h"

// �ÓI�����o�ϐ�
//====================================
// �R���X�g���N�^
//====================================
CEffect2D::CEffect2D()
{
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_fmove = 0.0f;
	m_nLife = 50;
	m_nIdxTexture = 0;
}
//====================================
// �f�X�g���N�^
//====================================
CEffect2D::~CEffect2D()
{
}
//====================================
// ����������
//====================================
HRESULT CEffect2D::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,const D3DCOLOR col, int life)
{
	CTexture*pTexture = CManager::GetCTexture();

	m_nIdxTexture = pTexture->Regist("data//TEXTURE//effect000.jpg");
	CObjectBillboard::BindTexture(m_nIdxTexture);
	CObjectBillboard::SetScale(20.0f, 20.0f);	// �傫����ݒ�
	CObjectBillboard::Init();

	CObjectBillboard::SetPos(pos);	// �ʒu���̐ݒ�
	CObjectBillboard::SetRot(rot);	// �������̐ݒ�
	CObjectBillboard::SetCol(col);	// �F���̐ݒ�

	m_nLife = life;		// �����̐ݒ�
	return S_OK;
}
//======================================
// �I������
//=====================================
void CEffect2D::Uninit(void)
{
	CObjectBillboard::Uninit();
	CObject::Relese();
}
//======================================
// �X�V����
//======================================
void CEffect2D::Update(void)
{
	// �I�u�W�F�N�g�̍X�V����
	CObjectBillboard::Update();

	m_nLife--;	// �̗͂����炷
	if (m_nLife <= 0)
	{// ���C�t��0�̎�
		CEffect2D::Uninit();	// �I�u�W�F�N�g���폜
	}
}
//======================================
// �`�揈��
//======================================
void CEffect2D::Draw(void)
{
	// �I�u�W�F�N�g�̕`�揈��
	CObjectBillboard::Draw();
}
//======================================
// ��������
//======================================
CEffect2D *CEffect2D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,const D3DCOLOR col, int life)
{
	CEffect2D *pEffect2D;

	// �I�u�W�F�N�g2D�̐���
	pEffect2D = new CEffect2D();

	// ����������
	pEffect2D->Init(pos, rot,col,life);

	return pEffect2D;
}