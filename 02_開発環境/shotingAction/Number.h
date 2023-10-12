// =======================================================
//
// ナンバー処理(Number.h)
// author KOMURO HIROMU
//
// =======================================================
// 二重インクルード防止
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include"object2D.h"
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CNumber :public CObject
{
public:
	CNumber();
	 ~CNumber();

	 HRESULT Init(void);		// 初期化処理
	 void Uninit(void);			// 終了処理
	 void Update(void);			// 更新処理
	 void Draw(void);			// 描画処理
	
	 void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }			// 位置の設定
	 void SetPosAdd(D3DXVECTOR3 pos) { m_pos += pos; }		// 位置の加算設定
	 D3DXVECTOR3 GetPos(void) { return m_pos; }				// 位置情報の入手

	 void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }			// 向きの設定
	 void SetRotAdd(D3DXVECTOR3 rot) { m_rot += rot; }		// 向きの減算設定
	 D3DXVECTOR3 GetRot(void) { return m_rot; }				// 向き情報を入手

	 void SetCol(const D3DCOLOR col);						//　色の設定

	 void SetAnimeTex(float Max_Conter, int m_nAnimeCounter);	// テクスチャの設定
	 void SetAddTex(float fTex);							// テクスチャの加算

	 void SetScale(float fHeight, float fWidth); 	// 大きさの設定

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファのポインタ
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 向き
	D3DCOLOR m_col;		// 色
	float m_fWidth;		// 横幅
	float m_fHeight;	// 立幅
	int m_nIdxTexture;		// テクスチャのインデックス

};
#endif