//= == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == =
//
// �e�N�X�`���̏���[Texture.h]
// author KOMURO HIROMU
//
//====================================================================
#ifndef _TEXTURE_H_		//���̃}�N����`������ĂȂ�������

#define _TEXTURE_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

// �}�N����`
#define MAX_TEX	(64)	// �e�N�X�`���̍ő吔

#include"main.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CTexture
{
public:

	CTexture();
	~CTexture();

	HRESULT Load(void);		// �e�N�X�`���̃��[�h
	void UnLoad(void);		// �e�N�X�`���̃A�����[�h

	int Regist(char* pFilename);
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);

private:
	LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEX];
	static int m_nNumAll;
	char* m_pFilenameOld[MAX_TEX];
};
#endif