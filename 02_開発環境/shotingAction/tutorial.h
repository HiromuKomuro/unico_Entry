// =======================================================
//
// �`���[�g���A������(tutorial.h)
// author KOMURO HIROMU
//
// =======================================================
// ��d�C���N���[�h�h�~
#ifndef _TITORIAL_H_
#define _TITORIAL_H_

#include"object2D.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g2D�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CTutorial : public CObject2D
{
public:
	CTutorial();
	~CTutorial();

	HRESULT Init(void);		// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��


	static CTutorial *Create(void);
private:
	int m_nIdxTexture;	// �e�N�X�`���̃C���f�b�N�X
};
#endif