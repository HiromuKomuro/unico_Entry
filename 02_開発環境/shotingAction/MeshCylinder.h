//====================================================================
//
//メッシュシリンダー処理[MeshCylinder.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _MESHCYLINDER_H_		//このマクロ定義がされてなかったら

#define _MESHCYLINDER_H_		//二重インクルード防止のマクロを定義する
#include"object.h"
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CMeshClynder : public CObject
{
public:
	CMeshClynder();
	~CMeshClynder();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }			// 位置の設定
	D3DXVECTOR3 GetPos(void) { return m_pos; }				// 位置情報の入手

	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }			// 向きの設定
	void SetRotAdd(D3DXVECTOR3 rot) { m_rot += rot; }		// 向きの減算設定
	D3DXVECTOR3 GetRot(void) { return m_rot; }				// 向き情報を入手

	D3DXMATRIX Getmtx(void) { return m_mtxWorld; }			// マトリックスの情報の入手

	static CMeshClynder * Create(void);

	static bool Collision(D3DXVECTOR3 pos);	// 当たり判定

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//インデックスバッファのポインタ
	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
	D3DXVECTOR3 m_pos;					//位置	
	D3DXVECTOR3 m_rot;					//向き	
	D3DCOLOR m_col;		// 色
	float m_fWidth;		// 横幅
	float m_fDepth;		// 奥幅
	float m_fHeight;	// 縦幅
	int m_nIdxTexture;	// テクスチャのインデックス
};
#endif
