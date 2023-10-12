//====================================================================
//
//当たり判定のライン処理[collisionline.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"collisionline.h"
#include"renderer.h"
#include"Manager.h"
#include"BlockXbase.h"
#include"input.h"
#include"game.h"

// 静的メンバ変数
int CCollisionLine::m_nNumLine = 0;
//========================================
// コンストラクタ
//========================================
CCollisionLine::CCollisionLine()
{
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DCOLOR_RGBA(255, 0, 0, 255);
	m_size.z = 0.0f;
	m_size.x = 0.0f;
	m_size.y = 0.0f;
	m_nId = 0;
}
//========================================
// デストラクタ
//========================================
CCollisionLine::~CCollisionLine()
{
}
//========================================
// 初期化処理
//========================================
HRESULT CCollisionLine::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの読み込み
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 5,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);
	VERTEX_3D*pVtx;				//頂点情報へのポインタ―


	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_size.x,m_size.y,m_size.z);
	pVtx[1].pos = D3DXVECTOR3(m_size.x,m_size.y,m_size.z);
	pVtx[2].pos = D3DXVECTOR3(m_size.x,-m_size.y,m_size.z);
	pVtx[3].pos = D3DXVECTOR3(-m_size.x,-m_size.y,m_size.z);
	pVtx[4].pos = D3DXVECTOR3(-m_size.x,+m_size.y,m_size.z);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;
	pVtx[4].col = m_col;


	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;

}
//========================================
// 終了処理
//========================================
void CCollisionLine::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CObject::Relese();
}
//=======================================
// 更新処理
//=======================================
void CCollisionLine::Update(void)
{
	VERTEX_3D*pVtx;				//頂点情報のポインタ
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		CObject *pObj = CObject::GetTop(nCntPri);	// 先頭のオブジェクトを代入

		while (pObj != NULL)
		{
			CObject *pObjectNext = pObj->GetNext();	// 次のオブジェクトを保存

			//種類を取得
			TYPE type = pObj->GetType();

			if (type == TYPE_BLOCKBASE || type == TYPE_BREAKBLOCKBASE)
			{
				CBaseBlockX *pBlockbase = dynamic_cast<CBaseBlockX*>(pObj);
				if (type == TYPE_BREAKBLOCKBASE)
				{// 種類が壊れるブロックの時
					CBreakBaseBlockX *pBlockbase = dynamic_cast<CBreakBaseBlockX*>(pObj);
				}
				
				if (m_nId == pBlockbase->GetId())
				{// 識別番号が一緒の時
					// 位置と向きの入手
					m_rot = pBlockbase->GetRot();
					m_pos.x = pBlockbase->GetBlock()->GetMtx()._41;
					m_pos.y = pBlockbase->GetBlock()->GetMtx()._42;
					m_pos.z = pBlockbase->GetBlock()->GetMtx()._43;
				}
			}
			pObj = pObjectNext;		// 次のオブジェクトを代入
		}
	}

	//頂点座標の座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, -m_size.z);
	pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, -m_size.z);
	pVtx[2].pos = D3DXVECTOR3(m_size.x, -m_size.y, -m_size.z);
	pVtx[3].pos = D3DXVECTOR3(-m_size.x, -m_size.y, -m_size.z);
	pVtx[4].pos = D3DXVECTOR3(-m_size.x, m_size.y, -m_size.z);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;
	pVtx[4].col = m_col;
	

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//======================================
// 描画処理
//======================================
void CCollisionLine::Draw(void)
{
	if (CGame::GetPause() == false)
	{
		return;
	}
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_3D);


	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_LINESTRIP,	// これで線の描画
		0,
		4);							// 線の数
}
//======================================
// 設定処理
//======================================
CCollisionLine *CCollisionLine::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,int *nId)
{
	CCollisionLine *pCollisionLine;

	// インスタンスの生成
	pCollisionLine = new CCollisionLine();

	// 位置の設定
 	pCollisionLine->SetPos(pos);

	// サイズの設定
	pCollisionLine->SetSize(size);

	// 初期化処理
	pCollisionLine->Init();

	// 識別番号の設定
	pCollisionLine->m_nId = *nId = m_nNumLine;

	// 総数の合計
	m_nNumLine++;

	return pCollisionLine;
}
//======================================
// 色の設定
//======================================
void CCollisionLine::SetCol(const D3DCOLOR col)
{
	m_col = col;
	VERTEX_2D*pVtx;				//頂点情報へ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラー設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}
