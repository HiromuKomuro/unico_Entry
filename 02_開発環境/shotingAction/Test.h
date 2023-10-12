// =======================================================
//
// テスト処理(Test.h)
// author KOMURO HIROMU
//
// =======================================================
// 二重インクルード防止
#ifndef _TEST_H_
#define _TEST_H_

#include"object2D.h"
//---------------------------------------------------------------------------
//					*****			オブジェクト2Dクラスの定義			*****
//---------------------------------------------------------------------------
class CTest : public CObject2D
{
public:
	CTest();
	~CTest();

	HRESULT Init(void);		// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理

	void SetTexture(LPDIRECT3DTEXTURE9 texture) { m_pTexture = texture; }
	void SetCol(D3DCOLOR color) { m_Color = color; }

	static CTest *Create(LPDIRECT3DTEXTURE9 texture,D3DCOLOR color);
private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DCOLOR		m_Color;
};
#endif