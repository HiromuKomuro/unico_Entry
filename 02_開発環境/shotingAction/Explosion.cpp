// =======================================================
//
// �����̏���(Explosion.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"Explosion.h"
#include"input.h"
#include"Manager.h"
#include"renderer.h"
#include"billboard.h"
#include"Texture.h"

// �}�N����`
#define MAX_LIFE			(100)	// ���C�t�̍ő吔
#define MAX_SCALE			(100.0f)// �X�P�[��
#define MAX_TEXTUREPATTERN	(8)		// �e�N�X�`���̃p�^�[����
#define MAX_ANIMECUNTER		(10)	// �ő�̃A�j���J�E���^�[
// �ÓI�����o�ϐ�
int CExplosion::m_nIdxTexture = 0;
//====================================
// �R���X�g���N�^
//====================================
CExplosion::CExplosion()
{
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_nLife = MAX_LIFE;
	m_nAnimeCounter = 0;	// �A�j���J�E���^�[
	m_nPatternCounter = 0;	// �p�^�[���J�E���^�[
}
//====================================
// �f�X�g���N�^
//====================================
CExplosion::~CExplosion()
{
}
//====================================
// ����������
//====================================
HRESULT CExplosion::Init(const D3DXVECTOR3 pos)
{
	CTexture*pTexture = CManager::GetCTexture();

	CObjectBillboard::Init();

	// ���̐ݒ�
	CExplosion::SetPos(pos);
	CExplosion::SetScale(MAX_SCALE, MAX_SCALE);
	CExplosion::SetAnimeTex((float)(MAX_TEXTUREPATTERN), 0.0f);

	m_nIdxTexture = pTexture->Regist("data//TEXTURE//explosion000.png");

	return S_OK;
}
//======================================
// �I������
//=====================================
void CExplosion::Uninit(void)
{
	CObjectBillboard::Uninit();
	CObject::Relese();
}
//======================================
// �X�V����
//======================================
void CExplosion::Update(void)
{
	// �I�u�W�F�N�g�̍X�V����
	CObjectBillboard::Update();
	
	// �e�N�X�`���̐ݒ�
	CObjectBillboard::SetAnimeTex((float)MAX_TEXTUREPATTERN, m_nPatternCounter);

	m_nAnimeCounter++;		// �A�j���[�V�����̃J�E���^�[�𑝉�

	if (m_nAnimeCounter % MAX_ANIMECUNTER == 0)
	{
		m_nAnimeCounter = 0;	// ������
		m_nPatternCounter++;

		if (m_nPatternCounter >= MAX_TEXTUREPATTERN)
		{
			m_nPatternCounter = 0;	// ������
			CExplosion::Relese();	// �I�u�W�F�N�g�̍폜

		}
	}

}
//======================================
// �`�揈��
//======================================
void CExplosion::Draw(void)
{
	// �I�u�W�F�N�g�̕`�揈��
	CObjectBillboard::Draw();
}
//======================================
// ��������
//======================================
CExplosion *CExplosion::Create(const D3DXVECTOR3 pos)
{
	CTexture*pTexture = CManager::GetCTexture();
	CRenderer *pRenderer = CManager::GetRenderer();

	CExplosion *pCExplosion = NULL;
	
	// �I�u�W�F�N�g2D�̐���
	pCExplosion = new CExplosion();

	// ����������
	pCExplosion->Init(pos);

	pCExplosion->BindTexture(m_nIdxTexture);

 	return pCExplosion;
}