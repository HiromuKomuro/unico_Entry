// =======================================================
//
// �^�C�g������(Title.h)
// author KOMURO HIROMU
//
// =======================================================
// ��d�C���N���[�h�h�~
#ifndef _TITLE_H_
#define _TITLE_H_

#include"manager.h"
class CTitleManager;
class CObject2D;
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CTitle:public CScene
{
public:
	CTitle();
	~CTitle();

	HRESULT Init(void);		// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

	static CTitleManager*GetTitleManager(void) { return s_pTitleManager; }	// �^�C�g���}�l�[�W���[�̓���
private:
	static CTitleManager *s_pTitleManager;	// �^�C�g���}�l�[�W���[�̏��
	bool m_bTutorial;		// �`���[�g���A����Ԃ��ǂ���
};
#endif
