//====================================================================
//
//すり抜ける壁処理[throughWall.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _THROUGHWALL_H_		//このマクロ定義がされてなかったら

#define _THROUGHWALL_H_		//二重インクルード防止のマクロを定義する

#include"Object3D.h"
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CThroughWall3D : public CObject3D
{
public:
	CThroughWall3D();
	~CThroughWall3D();
	// メンバ関数
	HRESULT Init(const D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CThroughWall3D*Create(const D3DXVECTOR3 pos);
	static bool CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 pRot, float fWidth, float fHeight);

private:
	// メンバ変数
	D3DXVECTOR3 m_rot;		// 向き
	int m_nIdxTexture;		// テクスチャの番号

};
#endif
