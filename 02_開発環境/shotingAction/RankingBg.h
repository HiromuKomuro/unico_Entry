// =======================================================
//
// ランキング背景処理(Rankingbg.h)
// author KOMURO HIROMU
//
// =======================================================
// 二重インクルード防止
#ifndef _RANKINGBG_H_
#define _RANKINGBG_H_

#include"object2D.h"
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CRankingBg: public CObject2D
{
public:
	CRankingBg();
	~CRankingBg();

	HRESULT Init(void);			// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理

	void Setpos(D3DXVECTOR3 pos) { m_pos = pos; }	// 位置の設定

	static CRankingBg *Create(D3DXVECTOR3 pos);
private:
	D3DXVECTOR3 m_pos;		// 位置
	int m_nTexType;			// テクスチャの種類
	int m_nIdxTexture;		// テクスチャの番号
};
#endif