// =======================================================
//
// チュートリアル処理(tutorial.h)
// author KOMURO HIROMU
//
// =======================================================
// 二重インクルード防止
#ifndef _TITORIAL_H_
#define _TITORIAL_H_

#include"object2D.h"
//---------------------------------------------------------------------------
//					*****			オブジェクト2Dクラスの定義			*****
//---------------------------------------------------------------------------
class CTutorial : public CObject2D
{
public:
	CTutorial();
	~CTutorial();

	HRESULT Init(void);		// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理


	static CTutorial *Create(void);
private:
	int m_nIdxTexture;	// テクスチャのインデックス
};
#endif