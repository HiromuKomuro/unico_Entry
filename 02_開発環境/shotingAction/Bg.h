// =======================================================
//
// �w�i����(bg.h)
// author KOMURO HIROMU
//
// =======================================================
// ��d�C���N���[�h�h�~
#ifndef _BG_H_
#define _BG_H_

#include"object2D.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CBg: public CObject2D
{
public:
	CBg();
	~CBg();

	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

	void Setpos(D3DXVECTOR3 pos) { m_pos = pos; }				// �ʒu�̐ݒ�
	void Setscale(D3DXVECTOR2 scale) { m_scale = scale; }		// �傫���̐ݒ�
	void SetFile(char *pfilename) { m_pFilename = pfilename; }	// �t�@�C���l�[���̐ݒ�

	static CBg *Create(D3DXVECTOR3 pos,D3DXVECTOR2 scale,char *pFilename);
private:
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR2 m_scale;	// �傫��
	char *m_pFilename;		// �t�@�C���̖��O
	int m_nTexType;			// �e�N�X�`���̎��
	int m_nIdxTexture;		// �e�N�X�`���̔ԍ�
};
#endif