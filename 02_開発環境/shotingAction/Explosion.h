// =======================================================
//
// �����̏���(explosion.h)
// author KOMURO HIROMU
//
// =======================================================
// ��d�C���N���[�h�h�~
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include"billboard.h"
//---------------------------------------------------------------------------
//					*****			�v���C���[�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CExplosion : public CObjectBillboard
{
public:
	CExplosion();
	~CExplosion();

	HRESULT Init(const D3DXVECTOR3 pos);		// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��
	
	static CExplosion *Create(const D3DXVECTOR3 pos);
private:
	D3DCOLOR	m_col;		// �F
	int m_nLife;			// ����
	int m_nAnimeCounter;	// �A�j���J�E���^�[
	int m_nPatternCounter;	// �p�^�[���J�E���^�[
	static int m_nIdxTexture;		// �e�N�X�`���̔ԍ�
};
#endif