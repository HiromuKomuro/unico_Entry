// =======================================================
//
// 弾の処理(bullet.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"bullet.h"
#include"input.h"
#include"Manager.h"
#include"renderer.h"
#include"Explosion.h"
#include"Effect.h"
#include"Texture.h"
#include"ObjectModel.h"
#include"BlockXbase.h"

// マクロ定義
#define BULLET_SPEED	(20.0f)	// 弾の速度
#define BULLET_SIZE	(D3DXVECTOR3(2.0f, 2.0f, 5.0f))
//====================================
// コンストラクタ
//====================================
CBullet::CBullet()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = BULLET_SIZE;
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_fmove = 0.0f;
	m_posMaxX = 0.0f;
	m_posMinX = 0.0f;
	m_posMaxY = 0.0f;
	m_posMinY = 0.0f;
	m_posMaxZ = 0.0f;
	m_posMinZ = 0.0f;
	m_nLife = 200;
	CObject::SetType(TYPE_BULLET);	// 種類を設定
}
//====================================
// デストラクタ
//====================================
CBullet::~CBullet()
{
}
//====================================
// 初期化処理
//====================================
HRESULT CBullet::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CXModel::Init();

	CXModel::SetPos(pos);	// 位置情報の設定
	CXModel::SetRot(rot);	// 向き情報の設定
	CXModel::SetSize(m_Size);	// 大きさを設定

	m_move.x = BULLET_SPEED * sinf(rot.y);
	m_move.z = BULLET_SPEED * cosf(rot.y);

	D3DXVECTOR3 *posVertex = GetVertexPos();
	m_posMaxX = posVertex[0].x;
	m_posMinX = posVertex[0].x;
	m_posMaxY = posVertex[0].y;
	m_posMinY = posVertex[0].y;
	m_posMaxZ = posVertex[0].z;
	m_posMinZ = posVertex[0].z;

	// 弾のモデルの大きさを取得
	for (int nCntVer = 0; nCntVer < GetnNumVertex(); nCntVer++)
	{
		if (m_posMaxX < posVertex[nCntVer].x)
		{
			m_posMaxX = posVertex[nCntVer].x;
		}
	
		else if (m_posMinX > posVertex[nCntVer].x)
		{
			m_posMinX = posVertex[nCntVer].x;
		}

		if (m_posMaxY < posVertex[nCntVer].y)
		{
			m_posMaxY = posVertex[nCntVer].y;
		}

		else if (m_posMinY > posVertex[nCntVer].y)
		{
			m_posMinY = posVertex[nCntVer].y;
		}
	
		if (m_posMaxZ < posVertex[nCntVer].z)
		{
			m_posMaxZ = posVertex[nCntVer].z;
		}

		else if (m_posMinZ > posVertex[nCntVer].z)
		{
			m_posMinZ = posVertex[nCntVer].z;
		}
	}
	m_posMaxX *= m_Size.x;
	m_posMaxY *= m_Size.y;
	m_posMaxZ *= m_Size.z;
	return S_OK;
}
//======================================
// 終了処理
//=====================================
void CBullet::Uninit(void)
{
	CXModel::Uninit();

	CObject::Relese();
}
//======================================
// 更新処理
//======================================
void CBullet::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	CEffect2D::Create(pos, GetRot(), D3DCOLOR_RGBA(255, 255, 255, 100),50);

	// 位置を保存
	m_posOld = pos;

	// オブジェクトの更新処理
	CXModel::Update();

	// 位置を増加
	pos += m_move;

	// 位置を設定
	SetPos(pos);

	// ブロックとの当たり判定
	if (CBaseBlockX::Collision(&pos, &m_posOld, &m_move, rot, m_posMaxX, m_posMaxY, m_posMinZ,true,false) == TRUE)
	{// 当てっているとき
		Uninit();			// 弾を削除
		CExplosion::Create(pos);	// 爆発を生成

		return;
	}
	m_nLife--;	// 体力を減らす
	if (m_nLife <= 0)
	{// ライフが0の時
		Uninit();	// 弾を削除
		CExplosion::Create(pos);	// 爆発を生成

	}
}
//======================================
// 描画処理
//======================================
void CBullet::Draw(void)
{
	// オブジェクトの描画処理
	CXModel::Draw();
}
//======================================
// 生成処理
//======================================
CBullet *CBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const char* pFilename)
{
	CBullet *pCBullet = NULL;
	
	// オブジェクト2Dの生成
 	pCBullet = new CBullet();
	
	// モデルの設定
	pCBullet->BindModel(pFilename);

	// 初期化処理
	pCBullet->Init(pos,rot);

 	return pCBullet;
}

//====================================
// コンストラクタ
//====================================
CChargeBullet::CChargeBullet()
{
}
//====================================
// デストラクタ
//====================================
CChargeBullet::~CChargeBullet()
{
}
//====================================
// 初期化処理
//====================================
HRESULT CChargeBullet::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CBullet::Init(pos, rot);

	return S_OK;
}
//======================================
// 終了処理
//=====================================
void CChargeBullet::Uninit(void)
{
	CObject::Relese();
}
//======================================
// 更新処理
//======================================
void CChargeBullet::Update(void)
{
	CBullet::Update();
}
//======================================
// 描画処理
//======================================
void CChargeBullet::Draw(void)
{
	// オブジェクトの描画処理
	CBullet::Draw();
}
//======================================
// 生成処理
//======================================
CChargeBullet *CChargeBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, D3DXVECTOR3 size, const char* pFilename)
{
	CChargeBullet *pChargeBullet = NULL;

	// オブジェクト2Dの生成
	pChargeBullet = new CChargeBullet();

	// モデルの設定
	pChargeBullet->BindModel(pFilename);

	// サイズの設定
	pChargeBullet->SetSize(size);

	// 初期化処理
	pChargeBullet->Init(pos, rot);

	return pChargeBullet;
}