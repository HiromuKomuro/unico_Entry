//====================================================================
//
//ビルボード処理[Billboard.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _BILLBOARD_H_		//このマクロ定義がされてなかったら

#define _BILLBOARD_H_		//二重インクルード防止のマクロを定義する
#include"object.h"
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CObjectBillboard : public CObject
{
public:
	CObjectBillboard();
	~CObjectBillboard();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BindTexture(int nTexture);			// テクスチャの割り当て

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }			// 位置の設定
	void SetPosAdd(D3DXVECTOR3 pos) { m_pos += pos; }		// 位置の加算設定
	D3DXVECTOR3 GetPos(void) { return m_pos; }				// 位置情報の入手

	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }			// 向きの設定
	void SetRotAdd(D3DXVECTOR3 rot) { m_rot += rot; }		// 向きの減算設定
	D3DXVECTOR3 GetRot(void) { return m_rot; }				// 向き情報を入手

	void SetCol(const D3DCOLOR col);						//　色の設定

	void SetAnimeTex(float Max_Conter, int m_nAnimeCounter);	// テクスチャの設定
	void SetAddTex(float fTex);							// テクスチャの加算
	void SetScale(float fWidth, float fHeight); 	// 大きさの設定

	static CObjectBillboard * Create(void);
private:
	LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス
	D3DXVECTOR3 m_pos;					// 位置	
	D3DXVECTOR3 m_rot;					// 向き	
	D3DCOLOR m_col;		// 色
	float m_fWidth;		// 横幅
	float m_fDepth;		// 奥幅
	float m_fHeight;	// 縦幅
	int m_nIdxTexture;
};
#endif
