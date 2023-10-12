//====================================================================
//
//プレイヤー3D処理[Player3D.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _PLAYER3D_H_		//このマクロ定義がされてなかったら

#define _PLAYER3D_H_		//二重インクルード防止のマクロを定義する

// マクロ定義
#define MAX_PLAYER_PARTS	(3)
#include"object.h"
class CObjectModel;
class CMotion;
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CPlayer3D: public CObject
{
public:
	CPlayer3D();
	~CPlayer3D();

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

	static CPlayer3D*Create(D3DXVECTOR3 pos);	// モデルオブジェクトの生成
private:
		D3DXMATRIX m_mtxWorld;			//ワールドマトリックス
		D3DXVECTOR3 m_pos;				//位置
		D3DXVECTOR3 m_posOld;			// 前の位置
		D3DXVECTOR3 m_move;				// 移動量
		D3DXVECTOR3 m_boostmove;		// ブーストした移動量
		D3DXVECTOR3 m_rot;				//向き		
		CObjectModel *m_apModel[MAX_PLAYER_PARTS];		// モデルへのポインタ
		CMotion*m_pMotion;				// モーションのポインタ―
		int m_nNumModel;				// モデルの総数
		int m_nLife;					// 命
		int m_nSpeedCnt;				// 速度のカウント
		int m_nBoostCnt;				// ブーストのカウント
		bool m_bBoost;					// ブーストしているかどうか
};
#endif
