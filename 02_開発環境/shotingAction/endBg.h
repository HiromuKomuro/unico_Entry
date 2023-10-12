// =======================================================
//
// �I����ʔw�i����(endBg.h)
// author KOMURO HIROMU
//
// =======================================================
// ��d�C���N���[�h�h�~
#ifndef _ENDBG_H_
#define _ENDBG_H_

#include"object2D.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CEndBg: public CObject2D
{
public:
	CEndBg();
	~CEndBg();

	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

	void Setpos(D3DXVECTOR3 pos) { m_pos = pos; }	// �ʒu�̐ݒ�

	static CEndBg *Create(D3DXVECTOR3 pos);
private:
	D3DXVECTOR3 m_pos;		// �ʒu
	int m_nTexType;			// �e�N�X�`���̎��
	int m_nIdxTexture;		// �e�N�X�`���̔ԍ�
};
#endif