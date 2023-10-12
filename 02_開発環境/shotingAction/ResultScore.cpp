// =======================================================
//
// スコア処理(Score.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"ResultScore.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Explosion.h"
#include"Particle.h"
#include"Number.h"

// マクロ定義
#define MAX_NUMBERTEX	(10)	// 数字のテクスチャの最大数

// 静的メンバ変数
CNumber *CResultScore::m_apNumber[NUM_SCOREPLACE] = {};
int CResultScore::m_nScore = 0;
//====================================
// コンストラクタ
//====================================
CResultScore::CResultScore()
{
}
//====================================
// デストラクタ
//====================================
CResultScore::~CResultScore()
{
	//m_apNumber[NUM_SCOREPLACE] = {};
}
//====================================
// 初期化処理
//====================================
HRESULT CResultScore::Init(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < NUM_SCOREPLACE; nCnt++)
	{
		// スコアの生成
		//if (m_apNumber[nCnt] != NULL)
		//{
		//	// スコアの開放
		//	m_apNumber[nCnt]->Uninit();
		//	delete m_apNumber[nCnt];
		//	m_apNumber[nCnt] = NULL;
		//}

		m_apNumber[nCnt] = new CNumber;	// スコアのインスタンス生成

		if (m_apNumber[nCnt] != NULL)
		{// 使用されているとき
			m_apNumber[nCnt]->Init();

			// 位置情報の設定
			m_apNumber[nCnt]->SetPos(pos);
			m_apNumber[nCnt]->SetScale(20.0f, 30.0f);
			m_apNumber[nCnt]->SetAnimeTex(((float)MAX_NUMBERTEX), 0.0f);
			pos.x += 50.0f;
		}
	}
	return S_OK;
}
//======================================
// 終了処理
//=====================================
void CResultScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_SCOREPLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			// スコアの開放
			//m_apNumber[nCnt]->Uninit();
			//delete m_apNumber[nCnt];
			//m_apNumber[nCnt] = NULL;
		}
	}
	m_nScore = 0;

}
//======================================
// 更新処理
//======================================
void CResultScore::Update(void)
{

}
//======================================
// 描画処理
//======================================
void CResultScore::Draw(void)
{

}
//======================================
// 生成処理
//======================================
CResultScore *CResultScore::Create(const D3DXVECTOR3 pos)
{
	CResultScore *pScore;

	// オブジェクト2Dの生成
	pScore = new CResultScore();

	// 初期化処理
	pScore->Init(pos);

	return pScore;
}
//======================================
// スコアの設定処理
//======================================
void CResultScore::SetScore(int nScore)
{
	int aTexU[NUM_SCOREPLACE];	//各桁の数字の格納


	m_nScore = nScore;			//スコアの設定

	aTexU[0] = m_nScore % 100000000 / 10000000;
	aTexU[1] = m_nScore % 10000000 / 1000000;
	aTexU[2] = m_nScore % 1000000 / 100000;
	aTexU[3] = m_nScore % 100000 / 10000;
	aTexU[4] = m_nScore % 10000 / 1000;
	aTexU[5] = m_nScore % 1000 / 100;
	aTexU[6] = m_nScore % 100 / 10;
	aTexU[7] = m_nScore % 10 / 1;


	for (int nCnt = 0; nCnt < NUM_SCOREPLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// 使用されいているとき
			m_apNumber[nCnt]->SetAnimeTex(MAX_NUMBERTEX, aTexU[nCnt]);
		}
	}
}
//======================================
// スコアの加算処理
//======================================
void CResultScore::AddScore(int nValue)
{
	int aTexU[NUM_SCOREPLACE];	//各桁の数字の格納
	
	// スコアの加算
 	m_nScore += nValue;

	aTexU[0] = m_nScore % 100000000 / 10000000;
	aTexU[1] = m_nScore % 10000000 / 1000000;
	aTexU[2] = m_nScore % 1000000 / 100000;
	aTexU[3] = m_nScore % 100000 / 10000;
	aTexU[4] = m_nScore % 10000 / 1000;
	aTexU[5] = m_nScore % 1000 / 100;
	aTexU[6] = m_nScore % 100 / 10;
	aTexU[7] = m_nScore % 10 / 1;

	for (int nCnt = 0; nCnt < NUM_SCOREPLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// 使用されいているとき
			m_apNumber[nCnt]->SetAnimeTex(MAX_NUMBERTEX, aTexU[nCnt]);
		}
	}
}