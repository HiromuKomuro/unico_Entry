//====================================================================
//
//�G�t�F�N�g����[Effect.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _Effect_H_		//���̃}�N����`������ĂȂ�������
#define _Effect_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

#include"billboard.h"
//---------------------------------------------------------------------------
//					*****			�v���C���[�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CEffect2D : public CObjectBillboard
{
public:
	CEffect2D();
	~CEffect2D();

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DCOLOR col, int life);		// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

	static CEffect2D *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,const D3DCOLOR col,int life);
private:
	D3DCOLOR	m_col;		// �F
	float m_fmove;			// �ړ���
	int m_nLife;			// ����
	int m_nIdxTexture;		// �e�N�X�`���̔ԍ�
};
#endif