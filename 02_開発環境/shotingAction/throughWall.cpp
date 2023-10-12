//====================================================================
//
//すり抜けるウ壁処理[ThroughWall.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"throughWall.h"
#include"Manager.h"
#include"renderer.h"
#include"Texture.h"
#include"input.h"

//マクロ定義　
#define Wall_WIDTH		(200.0)
#define Wall_HEIGHT		(250.0)
//====================================
// コンストラクタ
//====================================
CThroughWall3D::CThroughWall3D()
{
	CObject::SetType(TYPE_THROUGHWALL);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//====================================
// デストラクタ
//====================================
CThroughWall3D::~CThroughWall3D()
{
}
//========================================
//　初期化処理
//========================================
HRESULT CThroughWall3D::Init(const D3DXVECTOR3 pos)
{
	CObject3D::Init();

	// 位置情報の設定
	CObject3D::SetPos(pos);
	CObject3D::SetScale(Wall_WIDTH , Wall_HEIGHT,0.0f);

	return S_OK;
}
//========================================
// 終了処理
//========================================
void CThroughWall3D::Uninit(void)
{
	CObject3D::Uninit();
}
//=======================================
// 更新処理
//=======================================
void CThroughWall3D::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	CObject3D::Update();

	if (pInputKeyboard->GetKeyboardPress(DIK_E) == true)
	{
		m_rot.z += ROT_TRANS;
	}
	if (pInputKeyboard->GetKeyboardPress(DIK_Q) == true)
	{
		m_rot.z -= ROT_TRANS;
	}

	SetRot(m_rot);
}

//======================================
//ポリゴンの描画処理
//======================================
void CThroughWall3D::Draw(void)
{
	CTexture*pTexture = CManager::GetCTexture();
	CRenderer *pRenderer = CManager::GetRenderer();

	//テクスチャの設定
	pRenderer->GetDevice()->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	CObject3D::Draw();
}
//======================================
// 生成処理
//======================================
CThroughWall3D *CThroughWall3D::Create(const D3DXVECTOR3 pos)
{
	CThroughWall3D *pThroughWall3D = NULL;

	// オブジェクト3Dの生成
	pThroughWall3D = new CThroughWall3D();

	// 初期化処理
	pThroughWall3D->Init(pos);

	return pThroughWall3D;
}
//======================================
// 壁との当たり判定
//======================================
bool CThroughWall3D::CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 pRot, float fWidth, float fHeight)
{
	bool bLand = false;			//着地したかどうか

	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		CObject *pObj = CObject::GetTop(nCntPri);	// 先頭のオブジェクトを代入

		while (pObj != NULL)
		{
			CObject *pObjectNext = pObj->GetNext();	// 次のオブジェクトを保存

			// 種類を取得
			TYPE type = pObj->GetType();

			if (type == TYPE_THROUGHWALL)
			{
				CThroughWall3D *pWall3D = dynamic_cast<CThroughWall3D*>(pObj);

				// 対角線の長さを算出する
				float fLength = sqrtf(Wall_WIDTH * Wall_WIDTH + Wall_HEIGHT * Wall_HEIGHT);

				// 対角線の角度を算出する
				float fAngle = atan2f(Wall_WIDTH, Wall_HEIGHT);

				if (pPos->x - fWidth / 2 <= pWall3D->GetPos().x + Wall_WIDTH &&
					pPos->x + fWidth / 2 >= pWall3D->GetPos().x - Wall_WIDTH &&
					pPos->y - fHeight / 2 <= pWall3D->GetPos().y + Wall_HEIGHT &&
					pPos->y + fHeight / 2 >= pWall3D->GetPos().y - Wall_HEIGHT &&
					pPos->z - fHeight / 2 <= pWall3D->GetPos().z  &&
					pPos->z + fHeight / 2 >= pWall3D->GetPos().z)
				{


				}
			}
			pObj = pObjectNext;		// 次のオブジェクトを代入
		}
	}
	return bLand;
}
