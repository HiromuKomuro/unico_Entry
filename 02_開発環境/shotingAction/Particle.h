// =======================================================
//
// �p�[�e�B�N������(particle.h)
// author KOMURO HIROMU
//
// =======================================================
// ��d�C���N���[�h�h�~
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

// �}�N����`
#define MAX_PARTICLE		(64)	// �p�[�e�B�N���̍ő吔

#include"object.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CParticle :public CObject
{
public:	//�A�N�Z�X�w��q

	CParticle();
	 ~CParticle();

	 HRESULT Init(void);		// ����������
	 void Uninit(void);			// �I������
	 void Update(void);			// �X�V����
	 void Draw(void);			// �`�揈��

	 static CParticle *Create(const D3DXVECTOR3 pos,const D3DCOLOR col);	// �I�u�W�F�N�g�̓��菈��
private:

	static D3DXVECTOR3 m_pos;	// �ʒu
	static D3DCOLOR m_col;		// �F
	D3DXVECTOR3 m_posmove[MAX_PARTICLE];	// �ړ��ʒu
	D3DXVECTOR3 m_move[MAX_PARTICLE];	// �ړ���
	D3DXVECTOR3 m_rot[MAX_PARTICLE];	// �ړ���
	int m_nLife;					// ����
};
#endif