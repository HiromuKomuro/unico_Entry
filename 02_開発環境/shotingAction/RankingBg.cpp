// =======================================================
//
// �����L���O��ʔw�i����(Rankingbg.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"RankingBg.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Texture.h"

// �}�N����`
#define MAX_SCALE	(D3DXVECTOR2(300.0f,100.0f))	// �X�P�[���̍ő�
//= == == == == == == == == == == == == == == == == == =
// �R���X�g���N�^
//====================================
CRankingBg::CRankingBg()
{
	// �p�����[�^�[������
	m_nTexType = 0;
	m_nIdxTexture = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//====================================
// �f�X�g���N�^
//====================================
CRankingBg::~CRankingBg()
{
}
//====================================
// ����������
//====================================
HRESULT CRankingBg::Init(void)
{
	CTexture*pTexture = CManager::GetCTexture();

	CObject2D::Init();
	// �ʒu���̐ݒ�
	CObject2D::SetPos(m_pos);
	CObject2D::SetScale(MAX_SCALE.x, MAX_SCALE.y);

	// �e�N�X�`���̓ǂݍ���
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\ranking001.png");

	// �e�N�X�`���̓ǂݍ���
	CObject2D::BindTexture(m_nIdxTexture);

	return S_OK;
}
//======================================
// �I������
//=====================================
void CRankingBg::Uninit(void)
{
	CObject::Relese();
}
//======================================
// �X�V����
//======================================
void CRankingBg::Update(void)
{
	CObject2D::Update();
}
//======================================
// �`�揈��
//======================================
void CRankingBg::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}
//======================================
// ��������
//======================================
CRankingBg *CRankingBg::Create(D3DXVECTOR3 pos)
{
	CRankingBg * pCRankingBg;

	// �I�u�W�F�N�g2D�̐���
	pCRankingBg = new CRankingBg;

	// �ʒu�̐ݒ�
	pCRankingBg->Setpos(pos);

	// ����������
	pCRankingBg->Init();

	return pCRankingBg;
}
