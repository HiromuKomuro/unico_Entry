// =======================================================
//
// �����L���O�w�i����(Rankingbg.h)
// author KOMURO HIROMU
//
// =======================================================
// ��d�C���N���[�h�h�~
#ifndef _RANKINGBG_H_
#define _RANKINGBG_H_

#include"object2D.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CRankingBg: public CObject2D
{
public:
	CRankingBg();
	~CRankingBg();

	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

	void Setpos(D3DXVECTOR3 pos) { m_pos = pos; }	// �ʒu�̐ݒ�

	static CRankingBg *Create(D3DXVECTOR3 pos);
private:
	D3DXVECTOR3 m_pos;		// �ʒu
	int m_nTexType;			// �e�N�X�`���̎��
	int m_nIdxTexture;		// �e�N�X�`���̔ԍ�
};
#endif