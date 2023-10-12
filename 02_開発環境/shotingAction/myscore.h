// =======================================================
//
// 自分のスコア処理(myscore.h)
// author KOMURO HIROMU
//
// =======================================================
// 二重インクルード防止
#ifndef _MY_SCORE_H_
#define _MY_SCORE_H_

#include"object2D.h"
//---------------------------------------------------------------------------
//					*****			オブジェクト2Dクラスの定義			*****
//---------------------------------------------------------------------------
class CMyScore : public CObject2D
{
public:
	CMyScore();
	~CMyScore();

	HRESULT Init(void);		// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理


	static CMyScore *Create(D3DXVECTOR3 pos);
private:
	int m_nIdxTexture;	// テクスチャのインデックス
};
#endif