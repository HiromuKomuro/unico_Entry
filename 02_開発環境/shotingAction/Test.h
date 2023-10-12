// =======================================================
//
// �e�X�g����(Test.h)
// author KOMURO HIROMU
//
// =======================================================
// ��d�C���N���[�h�h�~
#ifndef _TEST_H_
#define _TEST_H_

#include"object2D.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g2D�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CTest : public CObject2D
{
public:
	CTest();
	~CTest();

	HRESULT Init(void);		// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

	void SetTexture(LPDIRECT3DTEXTURE9 texture) { m_pTexture = texture; }
	void SetCol(D3DCOLOR color) { m_Color = color; }

	static CTest *Create(LPDIRECT3DTEXTURE9 texture,D3DCOLOR color);
private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DCOLOR		m_Color;
};
#endif