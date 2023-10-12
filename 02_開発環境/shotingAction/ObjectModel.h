//====================================================================
//
//モデル処理[ObjectModel.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _OBJECTMODEL_H_		//このマクロ定義がされてなかったら

#define _OBJECTMODEL_H_		//二重インクルード防止のマクロを定義する

#include"main.h"
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CObjectModel
{
public:
	// 状態の列挙型
	typedef enum
	{
		STATE_NONE = 0,
		STATE_DAMAGE,
		STATE_MAX
	}STATE;

	CObjectModel();
	~CObjectModel();

	//メンバ関数
	HRESULT Init(const char* pFilename);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXMATRIX GetMtx(void) { return m_mtxWorld; }		// マトリックスの取得
	void SetParent(CObjectModel*pObjectModel);	// 親モデルの設定

	static CObjectModel*Create(const char* pFilename, D3DXVECTOR3 pos);	// モデルオブジェクトの生成

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }			// 位置の設定
	D3DXVECTOR3 GetPos(void) { return m_pos; }				// 位置情報の入手

	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }			// 向きの設定
	D3DXVECTOR3 GetRot(void) { return m_rot; }				// 向き情報を入手

	void SetCol(D3DCOLOR col) { m_col = col; }			// 色の設定
	D3DXCOLOR GetCol(void) { return m_col; }				// 色情報を入手

	void SetSize(D3DXVECTOR3 size) { m_Size = size; }			// サイズの設定
	D3DXVECTOR3 GetSize(void) { return m_Size; }				// サイズの入手

	void SetState(STATE state) { m_state = state; }		// 状態の設定
	STATE GetState(void) { return m_state; }			// 状態の入手

	D3DXVECTOR3 *GetVertexPos(void) { return m_pPos; }		// 頂点情報の位置を入手
	WORD GetSizeFVF(void) { return m_SizeFVF; }					// サイズの情報を入手	
	int GetnNumVertex(void) { return m_pMesh->GetNumVertices(); }	// 頂点の数を入手

private:
		LPD3DXMESH m_pMesh;				//メッシュ(頂点情報)へのポインタ
		LPD3DXBUFFER m_pBuffMat;		//マテリアルへのポインタ
		DWORD m_dwNumMat;				//マテリアルの数
		WORD m_SizeFVF;					// バッファのサイズ
		BYTE *m_pVertex;				// 頂点情報
		D3DXVECTOR3 *m_pPos;			// 頂点毎の位置
		D3DXVECTOR3 m_pos;				// 位置	
		D3DXVECTOR3 m_rot;				// 向き
		D3DXCOLOR	m_col;				// 色
		STATE		m_state;			// 状態
		D3DXVECTOR3 m_Size;				// モデルのサイズ
		D3DXMATRIX m_mtxWorld;			// ワールドマトリックス
		CObjectModel* m_aParent;		// 親モデルのポインタ
		int*m_nIdxTexture;				// テクスチャの総数
		int m_nDamgeCounter;			// ダメージカウンター
};
#endif
