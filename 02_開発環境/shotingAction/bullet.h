// =======================================================
//
// 弾の処理(bullet.h)
// author KOMURO HIROMU
//
// =======================================================
// 二重インクルード防止
#ifndef _BULLET_H_
#define _BULLET_H_

#include"model.h"
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CBullet : public CXModel
{
public:
	CBullet();
	~CBullet();

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);		// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理
	
	D3DXVECTOR3 GetSize(void) {	return m_Size;	}		// 大きさの入手
	void SetSize(D3DXVECTOR3 size) { m_Size = size; }	// 大きさの設定

	static CBullet *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const char* pFilename);	// オブジェクトの生成
private:

	D3DXVECTOR3 m_posOld;	// 前の位置
	D3DXVECTOR3 m_move;		// 移動量
	D3DXVECTOR3 m_Size;	// 大きさ
	D3DCOLOR	m_col;		// 色
	float m_fmove;			// 移動量
	float m_posMaxX;		// 最大の位置X
	float m_posMinX;		// 最小の位置X
	float m_posMaxY;		// 最大の位置Y
	float m_posMinY;		// 最小の位置Y
	float m_posMaxZ;		// 最大の位置Z
	float m_posMinZ;		// 最小の位置Z
	int m_nLife;			// 寿命

};
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CChargeBullet : public CBullet
{
public:
	CChargeBullet();
	~CChargeBullet();

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);		// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理

	static CChargeBullet *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, D3DXVECTOR3 size,const char* pFilename);	// オブジェクトの生成
private:

};
#endif