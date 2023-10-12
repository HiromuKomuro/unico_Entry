 //====================================================================
//
//ブロックX処理[BlockX.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _BLOCKX_H_		//このマクロ定義がされてなかったら

#define _BLOCKX_H_		//二重インクルード防止のマクロを定義する

#include"Model.h"
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CBlockX
{
public:
	CBlockX();
	~CBlockX();

	//メンバ関数
	HRESULT Init(const char* pFilename);
	void Uninit(void);
	void Update(void);
	void Draw(D3DXMATRIX mtxPar);

	void SetVector(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }			// 位置の設定
	D3DXVECTOR3 GetPos(void) { return m_pos; }				// 位置情報の入手

	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }			// 向きの設定
	D3DXVECTOR3 GetRot(void) { return m_rot; }				// 向き情報を入手

	void SetCol(D3DXCOLOR col) { m_col = col; }				//　色の設定
	D3DXCOLOR GetCol(void) { return m_col; }				//  色の入手

	void SetType(int nType) { m_nType = nType; }			// 種類の設定
	int GetType(void) { return m_nType; }					// 種類の入手

	void SetSize(D3DXVECTOR3 size) { m_Size = size; }		// サイズの設定
	D3DXVECTOR3 GetSize(void) { return m_Size; }			// サイズ情報の入手

	D3DXMATRIX GetMtx(void) { return m_mtxWorld; }		// マトリックスの取得
	void SetParent(CBlockX*pBlockX) { m_aParent = pBlockX; }	// 親モデルの設定

	D3DXVECTOR3 GetMaxpos(void) { return m_Maxpos; }	// モデルの最大位置を入手
	D3DXVECTOR3 GetMinpos(void) { return m_Minpos; }	// モデルの最小位置を入手

	float GetLength(void) { return m_fLength; }	// 対角線の長さを入手
	float GetAngle(void) { return m_fAngle; }	// 対角線の角度を入手

	static CBlockX*Create(D3DXVECTOR3 pos,const char* pFilename,D3DXVECTOR3 Size);	// モデルオブジェクトの生成


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
	D3DXVECTOR3 m_Size;				// モデルのサイズ
	D3DXMATRIX m_mtxWorld;			// ワールドマトリックス
	CBlockX* m_aParent;				// 親モデルのポインタ
	int*m_nIdxTexture;				// テクスチャの総数

	D3DXVECTOR3 m_Maxpos;	// 最大の位置
	D3DXVECTOR3 m_Minpos;	// 最小の位置

	float m_fLength;	// 対角線の長さ
	float m_fAngle;		// 対角線の角度

	int m_nType;		// 種類

};
#endif
