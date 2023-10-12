// =======================================================
//
// 背景処理(bg.h)
// author KOMURO HIROMU
//
// =======================================================
// 二重インクルード防止
#ifndef _BG_H_
#define _BG_H_

#include"object2D.h"
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class TitleBg: public CObject2D
{
public:
	TitleBg();
	~TitleBg();

	HRESULT Init(void);			// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理


	static TitleBg *Create(void);
private:

	int m_nTexType;			// テクスチャの種類
	int m_nIdxTexture;		// テクスチャの番号
};
#endif