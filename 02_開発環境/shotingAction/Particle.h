// =======================================================
//
// パーティクル処理(particle.h)
// author KOMURO HIROMU
//
// =======================================================
// 二重インクルード防止
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

// マクロ定義
#define MAX_PARTICLE		(64)	// パーティクルの最大数

#include"object.h"
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CParticle :public CObject
{
public:	//アクセス指定子

	CParticle();
	 ~CParticle();

	 HRESULT Init(void);		// 初期化処理
	 void Uninit(void);			// 終了処理
	 void Update(void);			// 更新処理
	 void Draw(void);			// 描画処理

	 static CParticle *Create(const D3DXVECTOR3 pos,const D3DCOLOR col);	// オブジェクトの入手処理
private:

	static D3DXVECTOR3 m_pos;	// 位置
	static D3DCOLOR m_col;		// 色
	D3DXVECTOR3 m_posmove[MAX_PARTICLE];	// 移動位置
	D3DXVECTOR3 m_move[MAX_PARTICLE];	// 移動量
	D3DXVECTOR3 m_rot[MAX_PARTICLE];	// 移動量
	int m_nLife;					// 寿命
};
#endif