// =======================================================
//
// �����̃X�R�A����(myscore.h)
// author KOMURO HIROMU
//
// =======================================================
// ��d�C���N���[�h�h�~
#ifndef _MY_SCORE_H_
#define _MY_SCORE_H_

#include"object2D.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g2D�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CMyScore : public CObject2D
{
public:
	CMyScore();
	~CMyScore();

	HRESULT Init(void);		// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��


	static CMyScore *Create(D3DXVECTOR3 pos);
private:
	int m_nIdxTexture;	// �e�N�X�`���̃C���f�b�N�X
};
#endif