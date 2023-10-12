// =======================================================
//
// �p�[�e�B�N������(particle.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include<stdlib.h>
#include<time.h>

#include "particle.h"
#include"object2D.h"
#include"main.h"
#include"renderer.h"
#include"Effect.h"

// �}�N����`
#define MAX_LIFE	(50)	// �ő�̃��C�t
// �ÓI�����o�ϐ�
D3DXVECTOR3 CParticle::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0);
D3DCOLOR CParticle::m_col = D3DCOLOR_RGBA(255,255,255,255);

//====================================
// �R���X�g���N�^
//====================================
CParticle::CParticle()
{
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		m_posmove[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0);
		m_move[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0);
		m_rot[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0);
	}
	m_nLife = MAX_LIFE;
}
//====================================
// �f�X�g���N�^
//====================================
CParticle::~CParticle()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0);
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
}
//====================================
// ����������
//====================================
HRESULT CParticle::Init(void)
{
	//�����̎��ݒ�
	srand((unsigned int)time(0));

	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		m_move[nCnt] += D3DXVECTOR3((float)(rand() % 10 - 5), float(rand() % 10 - 5), 0.0f);
		m_rot[nCnt] += D3DXVECTOR3(0.0f, 0.0f, (float)(rand() % 7 - 3));
		m_posmove[nCnt] = m_pos;
	}
	return S_OK;
}
//====================================
// �I������
//====================================
void CParticle::Uninit(void)
{
	CObject::Relese();
}
//====================================
// �X�V����
//====================================
void CParticle::Update(void)
{
 	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		CEffect2D::Create(m_posmove[nCnt],m_rot[nCnt], m_col,10);
		m_posmove[nCnt] += m_move[nCnt];
	}

	m_nLife--;	// �̗͂����炷
	if (m_nLife <= 0)
	{// ���C�t��0�̎�
		Uninit();	// �I�u�W�F�N�g���폜
	}
}
//====================================
// �`�揈��
//====================================
void CParticle::Draw(void)
{
}
//======================================
// ��������
//======================================
CParticle *CParticle::Create(const D3DXVECTOR3 pos, const D3DCOLOR col)
{
	CParticle*pParticle;

	// �I�u�W�F�N�g�̐���
	pParticle = new CParticle();

	// �ʒu�̐ݒ�
	pParticle->m_pos = pos;

	// �F�̐ݒ�
	pParticle->m_col = col;

	// ����������
	pParticle->Init();

	return pParticle;
}