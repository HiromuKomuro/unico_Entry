//====================================================================
//
//エフェクト処理[Effect.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _Effect_H_		//このマクロ定義がされてなかったら
#define _Effect_H_		//二重インクルード防止のマクロを定義する

#include"billboard.h"
//---------------------------------------------------------------------------
//					*****			プレイヤークラスの定義			*****
//---------------------------------------------------------------------------
class CEffect2D : public CObjectBillboard
{
public:
	CEffect2D();
	~CEffect2D();

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DCOLOR col, int life);		// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理

	static CEffect2D *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,const D3DCOLOR col,int life);
private:
	D3DCOLOR	m_col;		// 色
	float m_fmove;			// 移動量
	int m_nLife;			// 寿命
	int m_nIdxTexture;		// テクスチャの番号
};
#endif