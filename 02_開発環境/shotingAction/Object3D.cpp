//====================================================================
//
//3Dオブジェクト処理[Object3D.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"Object3D.h"
#include"renderer.h"
#include"Manager.h"

// マクロ定義
#define OBJECT_WIDTH	(200)	// 横幅
#define OBJECT_HEIGHT	(200)	// 縦幅
#define MAX_IDX			(19)	// インデックスの総数
//========================================
// コンストラクタ
//========================================
CObject3D::CObject3D()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_fDepth = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
}
//========================================
// デストラクタ
//========================================
CObject3D::~CObject3D()
{
}
//========================================
// 初期化処理
//========================================
HRESULT CObject3D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data//block000.jpg", &m_pTexture);
	

	//頂点バッファの読み込み
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_IDX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);
	VERTEX_3D*pVtx;				//頂点情報へのポインタ―


	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, m_fHeight, m_fDepth);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, m_fHeight, m_fDepth);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, m_fHeight, -m_fDepth);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, m_fHeight, -m_fDepth);

	pVtx[4].pos = D3DXVECTOR3(-m_fWidth, -m_fHeight, -m_fDepth);
	pVtx[5].pos = D3DXVECTOR3(m_fWidth, -m_fHeight, -m_fDepth);

	pVtx[6].pos = D3DXVECTOR3(m_fWidth, -m_fHeight, m_fDepth);

	pVtx[7].pos = D3DXVECTOR3(-m_fWidth, -m_fHeight, m_fDepth);

	pVtx[8].pos = D3DXVECTOR3(-m_fWidth, -m_fHeight, m_fDepth);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;
	pVtx[4].col = m_col;
	pVtx[5].col = m_col;
	pVtx[6].col = m_col;
	pVtx[7].col = m_col;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//インデックスの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);
	WORD*pIdx;				//インデックス情報のポインタ

	//インデックスをロックし、頂点情報データへのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//頂点番号データの設定
	pIdx[0] = 0;
	pIdx[1] = 1;
	pIdx[2] = 2;
	pIdx[3] = 3;
	pIdx[4] = 4;
	pIdx[5] = 5;
	pIdx[6] = 3;
	pIdx[7] = 6;
	pIdx[8] = 1;
	pIdx[9] = 7;
	pIdx[10] = 8;
	pIdx[11] = 2;
	pIdx[12] = 8;
	pIdx[13] = 5;

	//頂点バッファをアンロックする
	m_pIdxBuff->Unlock();

	return S_OK;

}
//========================================
// 終了処理
//========================================
void CObject3D::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}
//=======================================
// 更新処理
//=======================================
void CObject3D::Update(void)
{
	VERTEX_3D*pVtx;				//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, m_fHeight, m_fDepth);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, m_fHeight, m_fDepth);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, -m_fHeight, -m_fDepth);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, -m_fHeight, -m_fDepth);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//======================================
// 描画処理
//======================================
void CObject3D::Draw(void)
{
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

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_LINESTRIP,	// これで線の描画
				0,
				4);							// 線の数
}
//======================================
// 設定処理
//======================================
CObject3D *CObject3D::Create(void)
{
	CObject3D *pObject3D;

	// オブジェクト3Dの生成
	pObject3D = new CObject3D();

	// 初期化処理
	pObject3D->Init();

	return pObject3D;
}
//======================================
// 色の設定
//======================================
void CObject3D::SetCol(const D3DCOLOR col)
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
//======================================
// 大きさの設定
//======================================
void CObject3D::SetScale(float fWidth, float fHeight,float fDepth)
{
	// 代入
	m_fHeight = fHeight;
	m_fWidth = fWidth;
	m_fDepth = fDepth;

	// 更新処理
	CObject3D::Update();
}
//======================================
// テクスチャの割り当て
//======================================
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}