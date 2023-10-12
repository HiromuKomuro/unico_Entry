// =======================================================
//
// 薄暗い背景処理(dimbg.h)
// author KOMURO HIROMU
//
// =======================================================
// 二重インクルード防止
#ifndef _DIMBG_H_
#define _DIMBG_H_

#include"object2D.h"
//---------------------------------------------------------------------------
//					*****			オブジェクト2Dクラスの定義			*****
//---------------------------------------------------------------------------
class CDimBg : public CObject2D
{
public:
	CDimBg();
	~CDimBg();

	HRESULT Init(void);		// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理


	static CDimBg *Create(void);
private:
};
#endif