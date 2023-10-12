// =======================================================
//
// 終了画面背景処理(endBg.h)
// author KOMURO HIROMU
//
// =======================================================
// 二重インクルード防止
#ifndef _ENDBG_H_
#define _ENDBG_H_

#include"object2D.h"
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CEndBg: public CObject2D
{
public:
	CEndBg();
	~CEndBg();

	HRESULT Init(void);			// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理

	void Setpos(D3DXVECTOR3 pos) { m_pos = pos; }	// 位置の設定

	static CEndBg *Create(D3DXVECTOR3 pos);
private:
	D3DXVECTOR3 m_pos;		// 位置
	int m_nTexType;			// テクスチャの種類
	int m_nIdxTexture;		// テクスチャの番号
};
#endif