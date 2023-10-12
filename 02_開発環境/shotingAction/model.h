//====================================================================
//
//モデル処理[Model.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _MODEL_H_		//このマクロ定義がされてなかったら

#define _MODEL_H_		//二重インクルード防止のマクロを定義する

#include"object.h"
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CXModel: public CObject
{
public:
	CXModel();
	~CXModel();

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BindModel(const char* pFilename);			// モデルの割り当て

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }			// 位置の設定
	void SetPosAdd(D3DXVECTOR3 pos) { m_pos += pos; }		// 位置の加算設定
	D3DXVECTOR3 GetPos(void) { return m_pos; }				// 位置情報の入手

	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }			// 向きの設定
	void SetRotAdd(D3DXVECTOR3 rot) { m_rot += rot; }		// 向きの減算設定
	D3DXVECTOR3 GetRot(void) { return m_rot; }				// 向き情報を入手

	void SetCol(D3DXCOLOR col) { m_col = col; }				// 色の設定
	D3DXCOLOR GetCol(void) { return m_col; }				// 色の入手

	void SetSize(D3DXVECTOR3 size) { m_Size = size; }				// サイズの設定
	D3DXVECTOR3 GetSize(void) { return m_Size; }					// サイズの入手

	D3DXVECTOR3 *GetVertexPos(void) { return m_pPos; }		// 頂点情報の位置を入手
	WORD GetSizeFVF(void) { return m_SizeFVF; }					// サイズの情報を入手	
	int GetnNumVertex(void) { return m_pMesh->GetNumVertices(); }	// 頂点の数を入手

	static CXModel*Create(const char* pFilename);	// モデルオブジェクトの生成
private:
		LPD3DXMESH m_pMesh;				// メッシュ(頂点情報)へのポインタ
		LPD3DXBUFFER m_pBuffMat;		// マテリアルへのポインタ
		DWORD m_dwNumMat;				// マテリアルの数
		LPDIRECT3DTEXTURE9 *m_pTexture;	// テクスチャのポインタ
		WORD m_SizeFVF;					// バッファのサイズ
		D3DXVECTOR3 *m_pPos;			// 頂点毎の位置
		BYTE *m_pVertex;				// 頂点情報
		D3DXVECTOR3 m_pos;				// 位置
		D3DXVECTOR3 m_rot;				// 向き		
		D3DXMATRIX m_mtxWorld;			// ワールドマトリックス
		D3DXVECTOR3 m_Size;				// モデルのサイズ
		D3DXCOLOR  m_col;				// 色
		int m_nIdxMode;					// 対象の影のインデックス(番号)
		int m_nIdxModelParent;			// 親モデルのインデックス
		int *m_nIdxTexture;				// テクスチャの番号
};
#endif
