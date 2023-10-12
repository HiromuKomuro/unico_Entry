// =======================================================
//
// スコア処理(score.h)
// author KOMURO HIROMU
//
// =======================================================
// 二重インクルード防止
#ifndef _RESULTSCORE_H_
#define _RESULTSCORE_H_

#include"main.h"
// マクロ定義
#define NUM_SCOREPLACE		(8)			//スコアの桁数
//---------------------------------------------------------------------------
//					*****			前方宣言			*****
//---------------------------------------------------------------------------
class CNumber;
//---------------------------------------------------------------------------
//					*****			エネミークラスの定義			*****
//---------------------------------------------------------------------------
class CResultScore
{
public:
	CResultScore();
	~CResultScore();

	HRESULT Init(D3DXVECTOR3 pos);		// 初期化処理
	void Uninit(void);					// 終了処理
	void Update(void);					// 更新処理
	void Draw(void);					// 描画処理

	static void SetScore(int nScore);	// スコアの設定
	static void AddScore(int nValue);	// スコアの加算処理

	static int GetScore(void) { return m_nScore; }		// スコアの入手処理

	static CResultScore *Create(const D3DXVECTOR3 pos);		// オブジェクトの生成処理

private:
	static CNumber *m_apNumber[NUM_SCOREPLACE];			// 数字のポインター
	static int m_nScore;								// スコアの値
};
#endif