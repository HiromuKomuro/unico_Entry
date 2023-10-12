// =======================================================
//
// �e�̏���(bullet.h)
// author KOMURO HIROMU
//
// =======================================================
// ��d�C���N���[�h�h�~
#ifndef _BULLET_H_
#define _BULLET_H_

#include"model.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CBullet : public CXModel
{
public:
	CBullet();
	~CBullet();

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);		// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��
	
	D3DXVECTOR3 GetSize(void) {	return m_Size;	}		// �傫���̓���
	void SetSize(D3DXVECTOR3 size) { m_Size = size; }	// �傫���̐ݒ�

	static CBullet *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const char* pFilename);	// �I�u�W�F�N�g�̐���
private:

	D3DXVECTOR3 m_posOld;	// �O�̈ʒu
	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR3 m_Size;	// �傫��
	D3DCOLOR	m_col;		// �F
	float m_fmove;			// �ړ���
	float m_posMaxX;		// �ő�̈ʒuX
	float m_posMinX;		// �ŏ��̈ʒuX
	float m_posMaxY;		// �ő�̈ʒuY
	float m_posMinY;		// �ŏ��̈ʒuY
	float m_posMaxZ;		// �ő�̈ʒuZ
	float m_posMinZ;		// �ŏ��̈ʒuZ
	int m_nLife;			// ����

};
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CChargeBullet : public CBullet
{
public:
	CChargeBullet();
	~CChargeBullet();

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);		// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

	static CChargeBullet *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, D3DXVECTOR3 size,const char* pFilename);	// �I�u�W�F�N�g�̐���
private:

};
#endif