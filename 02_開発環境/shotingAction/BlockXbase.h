//====================================================================
//
//ブロックの基礎位置の処理[BlockXbase.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _BLOCKXBASE_H_		//このマクロ定義がされてなかったら

#define _BLOCKXBASE_H_		//二重インクルード防止のマクロを定義する

// マクロ定義
#define MAX_BLOCK	(1)
#include"object.h"
#include"BlockX.h"
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CBaseBlockX: public CObject
{
public:
	CBaseBlockX();
	~CBaseBlockX();

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }			// 位置の設定
	D3DXVECTOR3 GetPos(void) { return m_pos; }				// 位置情報の入手

	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }			// 向きの設定
	void SetRotAdd(D3DXVECTOR3 rot) { m_rot += rot; }		// 向きの減算設定
	D3DXVECTOR3 GetRot(void) { return m_rot; }				// 向き情報を入手

	void SetSize(D3DXVECTOR3 size) { m_Size = size; }		// サイズの設定
	D3DXVECTOR3 GetSize(void) { return m_Size; }			// サイズ情報の入手

	int GetId(void) { return m_nId; }						// 識別番号の入手
	void SetId(int id) { m_nId = id; }						// 識別番号の設定

	void SetFile(char *pFilename) { m_pFilename = pFilename; }	// ファイルの設定
	char *GetFile(void) { return m_pFilename; }					// ファイル名の入手

	CBlockX *GetBlock(void) { return m_apModel; }			// ブロックの情報を入手

	D3DXMATRIX Getmtx(void) { return m_mtxWorld; }	// マトリックスの取得

	void SetDeath(void) { m_bDeath = true; }		// 死亡フラグを確立
	bool GetDeath(void) { return m_bDeath; }		// 死亡フラグを入手
	static CBaseBlockX*Create(D3DXVECTOR3 pos, D3DXVECTOR3 Size);	// モデルオブジェクトの生成

	static bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 pRot, float fWidth, float fHeight, float fDepth,bool bBullet,bool bPlayer);	// 壁との当たり判定
	static bool  AddScore(D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepth);				// スコアの増加

private:
		D3DXMATRIX m_mtxWorld;			// ワールドマトリックス
		D3DXVECTOR3 m_pos;				// 位置
		D3DXVECTOR3 m_posOld;			// 前の位置
		D3DXVECTOR3 m_move;				// 移動量
		D3DXVECTOR3 m_rot;				// 向き		
		D3DXVECTOR3 m_rotmove;			// 向き移動量		
		D3DXVECTOR3 m_Size;				// モデルのサイズ
		CBlockX *m_apModel;				// モデルへのポインタ
		int m_nNumModel;				// モデルの総数	

		int m_nId;			// 識別番号	
		char* m_pFilename;	// ファイル名
		bool m_bDeath;		// 死亡フラグ
};
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CBreakBaseBlockX : public CBaseBlockX
{
public:
	CBreakBaseBlockX();
	~CBreakBaseBlockX();

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetLife(void) { return m_nLife; }			// ライフの入手
	void SetLife(int nLife) { m_nLife = nLife; }	// ライフの設定

	static CBreakBaseBlockX*Create(D3DXVECTOR3 pos, D3DXVECTOR3 Size);	// モデルオブジェクトの生成

private:
	int m_nLife;		// ライフ
};

#endif
