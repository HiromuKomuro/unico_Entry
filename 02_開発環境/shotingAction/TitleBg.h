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
class TitleBg: public CObject2D
{
public:
	TitleBg();
	~TitleBg();

	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��


	static TitleBg *Create(void);
private:

	int m_nTexType;			// �e�N�X�`���̎��
	int m_nIdxTexture;		// �e�N�X�`���̔ԍ�
};
#endif