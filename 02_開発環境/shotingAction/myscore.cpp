// =======================================================
//
// �����̃X�R�A����(myscore.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"myscore.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Texture.h"

// �}�N����`
#define MAX_SCALE	(D3DXVECTOR2(300.0f,30.0f))
//= == == == == == == == == == == == == == == == == == =
// �R���X�g���N�^
//====================================
CMyScore::CMyScore()
{
	m_nIdxTexture = 0;
}
//====================================
// �f�X�g���N�^
//====================================
CMyScore::~CMyScore()
{
}
//====================================
// ����������
//====================================
HRESULT CMyScore::Init(void)
{
	CTexture*pTexture = CManager::GetCTexture();

	// �e�N�X�`���̓ǂݍ���
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\my_score.png");
	CObject2D::BindTexture(m_nIdxTexture);
	CObject2D::Init();
	// �ʒu���̐ݒ�
	CObject2D::SetScale(MAX_SCALE.x, MAX_SCALE.y);

	return S_OK;
}
//======================================
// �I������
//=====================================
void CMyScore::Uninit(void)
{
	CObject2D::Uninit();
}
//======================================
// �X�V����
//======================================
void CMyScore::Update(void)
{
	CObject2D::Update();
}
//======================================
// �`�揈��
//======================================
void CMyScore::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}
//======================================
// ��������
//======================================
CMyScore *CMyScore::Create(D3DXVECTOR3 pos)
{
	CMyScore *pMyScore;
	// �I�u�W�F�N�g2D�̐���
	pMyScore = new CMyScore;

	// �ʒu
	pMyScore->SetPos(pos);

	// ����������
	pMyScore->Init();

	return pMyScore;
}
