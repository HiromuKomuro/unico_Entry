// =======================================================
//
// ���Â��w�i����(dimbg.h)
// author KOMURO HIROMU
//
// =======================================================
// ��d�C���N���[�h�h�~
#ifndef _DIMBG_H_
#define _DIMBG_H_

#include"object2D.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g2D�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CDimBg : public CObject2D
{
public:
	CDimBg();
	~CDimBg();

	HRESULT Init(void);		// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��


	static CDimBg *Create(void);
private:
};
#endif