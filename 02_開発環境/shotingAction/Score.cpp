// =======================================================
//
// スコア処理(Score.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"Score.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"Explosion.h"
#include"Particle.h"
#include"Number.h"
#include"file.h"
// マクロ定義
#define MAX_NUMBERTEX			(10)		// 数字のテクスチャの最大数
#define MAX_SCORE_SUMMONTIME	(120)		// スコアの生成時間
#define NUMBER_DISTANCE			(55.0f)		// ナンバー毎の距離
#define MAX_SCALE				(D3DXVECTOR2(20.0f,30.0f))	// スコアのスケール

// 静的メンバ変数
CNumber *CScore::m_apNumber[NUM_SCOREPLACE] = {};
int CScore::m_nScore = 0;
//====================================
// コンストラクタ
//====================================
CScore::CScore()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//====================================
// デストラクタ
//====================================
CScore::~CScore()
{
}
//====================================
// 初期化処理
//====================================
HRESULT CScore::Init(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < NUM_SCOREPLACE; nCnt++)
	{
		m_apNumber[nCnt] = new CNumber;	// スコアのインスタンス生成

		if (m_apNumber[nCnt] != NULL)
		{// 使用されているとき
			m_apNumber[nCnt]->Init();

			// 位置情報の設定
			m_apNumber[nCnt]->SetPos(pos);
			m_apNumber[nCnt]->SetScale(MAX_SCALE.x, MAX_SCALE.y);
			m_apNumber[nCnt]->SetAnimeTex(((float)MAX_NUMBERTEX), 0.0f);
			pos.x += NUMBER_DISTANCE;
		}
	}
	return S_OK;
}
//======================================
// 終了処理
//=====================================
void CScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_SCOREPLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			//スコアの開放
			//m_apNumber[nCnt]->Uninit();
		}
	}
	// ファイルの書き込み処理
	CFile::Write("data\\FILE\\Score.txt", CFile::TYPE_SCORE,m_nScore);

	m_nScore = 0;

}
//======================================
// 更新処理
//======================================
void CScore::Update(void)
{

}
//======================================
// 描画処理
//======================================
void CScore::Draw(void)
{

}
//======================================
// 生成処理
//======================================
CScore *CScore::Create(const D3DXVECTOR3 pos)
{
	CScore *pScore;

	// オブジェクト2Dの生成
	pScore = new CScore();

	// 位置の設定
	pScore->Setpos(pos);

	// 初期化処理
	pScore->Init(pos);

	return pScore;
}
//======================================
// スコアの設定処理
//======================================
void CScore::SetScore(int nScore)
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
void CScore::AddScore(int nValue)
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
//====================================
// コンストラクタ
//====================================
CAddScore::CAddScore()
{
	m_nScoreCnt = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nScore = 0;
	m_nAnimeCounter = 0;
}
//====================================
// デストラクタ
//====================================
CAddScore::~CAddScore()
{
}
//====================================
// 初期化処理
//====================================
HRESULT CAddScore::Init(void)
{
	D3DXVECTOR3 pos = m_pos;
	for (int nCnt = 0; nCnt < NUM_SCOREPLACE; nCnt++)
	{
		m_apNumber[nCnt] = new CNumber;	// スコアのインスタンス生成

		if (m_apNumber[nCnt] != NULL)
		{// 使用されているとき
			m_apNumber[nCnt]->Init();

			// 位置情報の設定
			m_apNumber[nCnt]->SetPos(pos);
			m_apNumber[nCnt]->SetScale(MAX_SCALE.x, MAX_SCALE.y);
			m_apNumber[nCnt]->SetAnimeTex(((float)MAX_NUMBERTEX), 0.0f);
			pos.x += NUMBER_DISTANCE;
		}
	}
	return S_OK;
}
//======================================
// 終了処理
//=====================================
void CAddScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_SCOREPLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			//スコアの開放
			m_apNumber[nCnt]->Uninit();
		}
	}
	m_nScore = 0;

	CObject::Relese(); 
}
//======================================
// 更新処理
//======================================
void CAddScore::Update(void)
{
	D3DXVECTOR3 pos;
	m_nScoreCnt++;
	m_move.y += 0.01f;

	m_pos += m_move;

	pos = m_pos;
	for (int nCnt = 0; nCnt < NUM_SCOREPLACE; nCnt++)
	{
		m_apNumber[nCnt]->SetPos(pos);	// 位置の設定
		pos.x += NUMBER_DISTANCE;
	}

	if (m_nScoreCnt % MAX_SCORE_SUMMONTIME == 0)
	{
		CAddScore::Uninit();
	}
}
//======================================
// 描画処理
//======================================
void CAddScore::Draw(void)
{
}
//======================================
// スコアの設定処理
//======================================
void CAddScore::SetScore(int nScore)
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
// 生成処理
//======================================
CAddScore *CAddScore::Create(const D3DXVECTOR3 pos,const int nScore)
{
	CAddScore *pAddScore;

	// オブジェクト2Dの生成
	pAddScore = new CAddScore();

	// 位置の設定
	pAddScore->Setpos(pos);

	// 初期化処理
	pAddScore->Init();
	
	// スコアの設定
	pAddScore->SetScore(nScore);

	return pAddScore;
}
//====================================
// コンストラクタ
//====================================
CRankScore::CRankScore()
{

}
//====================================
// デストラクタ
//====================================
CRankScore::~CRankScore()
{
}
//====================================
// 初期化処理
//====================================
HRESULT CRankScore::Init(void)
{
	for (int nCnt = 0; nCnt < NUM_SCOREPLACE; nCnt++)
	{
		//if (m_apNumber[nCnt] != NULL)
		//{
		//	//スコアの開放
		//	m_apNumber[nCnt]->Uninit();
		//	delete m_apNumber[nCnt];
		//	m_apNumber[nCnt] = NULL;
		//}
		m_apNumber[nCnt] = new CNumber;	// スコアのインスタンス生成

		if (m_apNumber[nCnt] != NULL)
		{// 使用されているとき
			m_apNumber[nCnt]->Init();

			// 位置情報の設定
			m_apNumber[nCnt]->SetPos(D3DXVECTOR3(m_pos.x + (nCnt * 50.0f),m_pos.y,m_pos.z));
			m_apNumber[nCnt]->SetScale(20.0f, 30.0f);
			m_apNumber[nCnt]->SetAnimeTex(((float)MAX_NUMBERTEX), 0.0f);
		}
	}

	
	return S_OK;
}
//======================================
// 終了処理
//=====================================
void CRankScore::Uninit(void)
{
	m_nScore = 0;
	CObject::Relese();
}
//======================================
// 更新処理
//======================================
void CRankScore::Update(void)
{
}
//======================================
// 描画処理
//======================================
void CRankScore::Draw(void)
{
}
//======================================
// 生成処理
//======================================
CRankScore *CRankScore::Create(const D3DXVECTOR3 pos, const int nScore)
{
	CRankScore *pAddScore;

	// オブジェクト2Dの生成
	pAddScore = new CRankScore();

	// スコアの設定
	pAddScore->Setpos(pos);

	// 初期化処理
	pAddScore->Init();

	// スコアの設定
	pAddScore->SetScore(nScore);
	return pAddScore;
}
//======================================
// スコアの設定処理
//======================================
void CRankScore::SetScore(int score)
{
	int aTexU[NUM_SCOREPLACE];	//各桁の数字の格納

	int nScore = score;			//スコアの設定

	aTexU[0] = nScore % 100000000 / 10000000;
	aTexU[1] = nScore % 10000000 / 1000000;
	aTexU[2] = nScore % 1000000 / 100000;
	aTexU[3] = nScore % 100000 / 10000;
	aTexU[4] = nScore % 10000 / 1000;
	aTexU[5] = nScore % 1000 / 100;
	aTexU[6] = nScore % 100 / 10;
	aTexU[7] = nScore % 10 / 1;


	for (int nCnt = 0; nCnt < NUM_SCOREPLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// 使用されいているとき
			m_apNumber[nCnt]->SetAnimeTex(MAX_NUMBERTEX, aTexU[nCnt]);
		}
	}
}