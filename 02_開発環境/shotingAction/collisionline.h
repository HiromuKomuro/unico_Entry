//====================================================================
//
//当たり判定のライン処理[collisionline.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _COLLISIONLINE_H_		//このマクロ定義がされてなかったら

#define _COLLISIONLINE_H_		//二重インクルード防止のマクロを定義する
#include"object.h"
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CCollisionLine : public CObject
{
public:
	CCollisionLine();
	~CCollisionLine();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }			// 位置の設定
	void SetPosAdd(D3DXVECTOR3 pos) { m_pos += pos; }		// 位置の加算設定
	D3DXVECTOR3 GetPos(void) { return m_pos; }				// 位置情報の入手

	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }			// 向きの設定
	void SetRotAdd(D3DXVECTOR3 rot) { m_rot += rot; }		// 向きの減算設定
	D3DXVECTOR3 GetRot(void) { return m_rot; }				// 向き情報を入手

	void SetSize(D3DXVECTOR3 size) { m_size = size; }		// サイズの設定
	D3DXVECTOR3 GetSize(void) { return m_size; }			// サイズの取得

	void SetCol(const D3DCOLOR col);						//　色の設定

	static int GetId(void) { return m_nNumLine; }				// 識別番号の入手

	static CCollisionLine * Create(D3DXVECTOR3 pos,D3DXVECTOR3 size,int *nId);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// インデックスバッファのポインタ
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス
	D3DXVECTOR3 m_pos;					// 位置	
	D3DXVECTOR3 m_rot;					// 向き	
	D3DCOLOR m_col;						// 色
	D3DXVECTOR3 m_size;					// 大きさ
	static int m_nNumLine;				// ラインの総数
	int m_nId;							// 識別番号
};
#endif
