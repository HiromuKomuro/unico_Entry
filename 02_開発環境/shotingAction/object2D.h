// =======================================================
//
// オブジェクト2D処理(object2D.h)
// author KOMURO HIROMU
//
// =======================================================
// 二重インクルード防止
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include"object.h"
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CObject2D : public CObject
{
public:
	CObject2D();
	 ~CObject2D();

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

	 void SetTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }	// テクスチャの設定
	 void BindTexture(int nIdxTexture) { m_nIdxTeture = nIdxTexture; }			// テクスチャの割り当て

	 void SetAnimeTex(float Max_Conter, int m_nAnimeCounter);	// テクスチャの設定
	 void SetAddTex(float fTex);							// テクスチャの加算

	 void SetScale(float fWidth,float fHeight); 	// 大きさの設定

	 static CObject2D *Create(D3DXVECTOR3 pos, D3DCOLOR Col,D3DXVECTOR2 sclae);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャの設定
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 向き
	D3DCOLOR m_col;		// 色
	float m_fWidth;		// 横幅
	float m_fHeight;	// 立幅
	int m_nIdxTeture;	// テクスチャのインデックス
};
#endif