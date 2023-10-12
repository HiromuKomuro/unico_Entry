// =======================================================
//
// パーティクル処理(particle.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include<stdlib.h>
#include<time.h>

#include "particle.h"
#include"object2D.h"
#include"main.h"
#include"renderer.h"
#include"Effect.h"

// マクロ定義
#define MAX_LIFE	(50)	// 最大のライフ
// 静的メンバ変数
D3DXVECTOR3 CParticle::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0);
D3DCOLOR CParticle::m_col = D3DCOLOR_RGBA(255,255,255,255);

//====================================
// コンストラクタ
//====================================
CParticle::CParticle()
{
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		m_posmove[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0);
		m_move[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0);
		m_rot[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0);
	}
	m_nLife = MAX_LIFE;
}
//====================================
// デストラクタ
//====================================
CParticle::~CParticle()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0);
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
}
//====================================
// 初期化処理
//====================================
HRESULT CParticle::Init(void)
{
	//乱数の種を設定
	srand((unsigned int)time(0));

	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		m_move[nCnt] += D3DXVECTOR3((float)(rand() % 10 - 5), float(rand() % 10 - 5), 0.0f);
		m_rot[nCnt] += D3DXVECTOR3(0.0f, 0.0f, (float)(rand() % 7 - 3));
		m_posmove[nCnt] = m_pos;
	}
	return S_OK;
}
//====================================
// 終了処理
//====================================
void CParticle::Uninit(void)
{
	CObject::Relese();
}
//====================================
// 更新処理
//====================================
void CParticle::Update(void)
{
 	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		CEffect2D::Create(m_posmove[nCnt],m_rot[nCnt], m_col,10);
		m_posmove[nCnt] += m_move[nCnt];
	}

	m_nLife--;	// 体力を減らす
	if (m_nLife <= 0)
	{// ライフが0の時
		Uninit();	// オブジェクトを削除
	}
}
//====================================
// 描画処理
//====================================
void CParticle::Draw(void)
{
}
//======================================
// 生成処理
//======================================
CParticle *CParticle::Create(const D3DXVECTOR3 pos, const D3DCOLOR col)
{
	CParticle*pParticle;

	// オブジェクトの生成
	pParticle = new CParticle();

	// 位置の設定
	pParticle->m_pos = pos;

	// 色の設定
	pParticle->m_col = col;

	// 初期化処理
	pParticle->Init();

	return pParticle;
}