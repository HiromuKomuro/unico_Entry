// =======================================================
//
// スコア処理(score.h)
// author KOMURO HIROMU
//
// =======================================================
// 二重インクルード防止
#ifndef _SCORE_H_
#define _SCORE_H_

#include"main.h"
#include"Object.h"
// マクロ定義
#define NUM_SCOREPLACE		(8)			//スコアの桁数
//---------------------------------------------------------------------------
//					*****			前方宣言			*****
//---------------------------------------------------------------------------
class CNumber;
//---------------------------------------------------------------------------
//					*****			スコアクラスの定義			*****
//---------------------------------------------------------------------------
class CScore
{
public:
	CScore();
	~CScore(); 

	HRESULT Init(D3DXVECTOR3 pos);		// 初期化処理
	void Uninit(void);					// 終了処理
	void Update(void);					// 更新処理
	void Draw(void);					// 描画処理

	static void SetScore(int nScore);	// スコアの設定
	static void AddScore(int nValue);	// スコアの加算処理

	static int GetScore(void) { return m_nScore; }		// スコアの入手処理

	void Setpos(D3DXVECTOR3 pos) { m_pos = pos; }		// 位置の設定
	static CScore *Create(const D3DXVECTOR3 pos);		// オブジェクトの生成処理

private:
	static CNumber *m_apNumber[NUM_SCOREPLACE];			// 数字のポインター
	static int m_nScore;								// スコアの値
	D3DXVECTOR3 m_pos;									// 位置
};
//---------------------------------------------------------------------------
//					*****			スコアクラスの定義			*****
//---------------------------------------------------------------------------
class CAddScore : public CObject
{
public:
	CAddScore();
	~CAddScore();

	HRESULT Init(void);					// 初期化処理
	void Uninit(void);					// 終了処理
	void Update(void);					// 更新処理
	void Draw(void);					// 描画処理

	void SetScore(int nScore);	// スコアの設定

	void Setpos(D3DXVECTOR3 pos) { m_pos = pos; }		// 位置の設定

	static CAddScore *Create(const D3DXVECTOR3 pos,const int score);		// オブジェクトの生成処理

private:
	CNumber *m_apNumber[NUM_SCOREPLACE];			// 数字のポインター
	int m_nScore;								// スコアの値
	D3DXVECTOR3 m_pos;									// 位置
	D3DXVECTOR3 m_move;									// 移動
	int m_nAnimeCounter;								// アニメーションカウンター
	int m_nScoreCnt;									// スコアカウンター
};
//---------------------------------------------------------------------------
//					*****		ランキングスコアクラスの定義		*****
//---------------------------------------------------------------------------
class CRankScore :public CObject
{
public:
	CRankScore();
	~CRankScore();

	HRESULT Init(void);					// 初期化処理
	void Uninit(void);					// 終了処理
	void Update(void);					// 更新処理
	void Draw(void);					// 描画処理

	void SetScore(int score);	// スコアの設定

	void Setpos(D3DXVECTOR3 pos) { m_pos = pos; }		// 位置の設定
	static CRankScore *Create(const D3DXVECTOR3 pos, const int score);		// オブジェクトの生成処理


private:
	CNumber *m_apNumber[NUM_SCOREPLACE];			// 数字のポインター
	int m_nScore;									// スコアの値
	D3DXVECTOR3 m_pos;								// 位置
};
#endif