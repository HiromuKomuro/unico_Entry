// =======================================================
//
// 爆発の処理(explosion.h)
// author KOMURO HIROMU
//
// =======================================================
// 二重インクルード防止
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include"billboard.h"
//---------------------------------------------------------------------------
//					*****			プレイヤークラスの定義			*****
//---------------------------------------------------------------------------
class CExplosion : public CObjectBillboard
{
public:
	CExplosion();
	~CExplosion();

	HRESULT Init(const D3DXVECTOR3 pos);		// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理
	
	static CExplosion *Create(const D3DXVECTOR3 pos);
private:
	D3DCOLOR	m_col;		// 色
	int m_nLife;			// 寿命
	int m_nAnimeCounter;	// アニメカウンター
	int m_nPatternCounter;	// パターンカウンター
	static int m_nIdxTexture;		// テクスチャの番号
};
#endif