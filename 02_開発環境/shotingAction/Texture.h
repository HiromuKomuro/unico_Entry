//= == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == =
//
// テクスチャの処理[Texture.h]
// author KOMURO HIROMU
//
//====================================================================
#ifndef _TEXTURE_H_		//このマクロ定義がされてなかったら

#define _TEXTURE_H_		//二重インクルード防止のマクロを定義する

// マクロ定義
#define MAX_TEX	(64)	// テクスチャの最大数

#include"main.h"
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CTexture
{
public:

	CTexture();
	~CTexture();

	HRESULT Load(void);		// テクスチャのロード
	void UnLoad(void);		// テクスチャのアンロード

	int Regist(char* pFilename);
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);

private:
	LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEX];
	static int m_nNumAll;
	char* m_pFilenameOld[MAX_TEX];
};
#endif