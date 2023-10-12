//====================================================================
//
//メッシュシリンダー処理[MeshCylinder.h]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"MeshCylinder.h"
#include"renderer.h"
#include"Manager.h"
#include"Object.h"
#include"input.h"
#include"Texture.h"

// マクロ定義
#define MAX_BUFF		(14)		// 最大の頂点バッファ
#define OBJECT_WIDTH	(100)		// 横幅
#define OBJECT_HEIGHT	(200)		// 縦幅
#define OBJECT_DEPTH	(2000)		// 奥幅
#define MAGNI			(1.5f)		// 角度
#define MAGNIFICATION	(7.0f)		// 拡大率
#define MAX_IDX			(16)		// インデックスの総数
//========================================
// コンストラクタ
//========================================
CMeshClynder::CMeshClynder()
{
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DCOLOR_RGBA(255, 255, 0, 255);
	m_fDepth = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_nIdxTexture = 0;
	CObject::SetType(TYPE_MESHFILED);	// 種類の設定
}
//========================================
// デストラクタ
//========================================
CMeshClynder::~CMeshClynder()
{
}
//========================================
// 初期化処理
//========================================
HRESULT CMeshClynder::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ
	CTexture*pTexture = CManager::GetCTexture();

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\wood_001.png");

	//頂点バッファの読み込み
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_BUFF,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);
	VERTEX_3D*pVtx;				//頂点情報へのポインタ―


	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の座標の設定
	pVtx[0].pos = D3DXVECTOR3(OBJECT_WIDTH * MAGNIFICATION, -100.0f, OBJECT_DEPTH * MAGNIFICATION);
	pVtx[1].pos = D3DXVECTOR3(-OBJECT_WIDTH * MAGNIFICATION, -100.0f, OBJECT_DEPTH * MAGNIFICATION);
	pVtx[2].pos = D3DXVECTOR3(-OBJECT_WIDTH * MAGNI * MAGNIFICATION, 100.0f * MAGNIFICATION, OBJECT_DEPTH * MAGNIFICATION);
	pVtx[3].pos = D3DXVECTOR3(-OBJECT_WIDTH * MAGNIFICATION, 200.0f * MAGNIFICATION, OBJECT_DEPTH * MAGNIFICATION);
	pVtx[4].pos = D3DXVECTOR3(0.0f, 250.0f * MAGNIFICATION, OBJECT_DEPTH * MAGNIFICATION);
	pVtx[5].pos = D3DXVECTOR3(OBJECT_WIDTH * MAGNIFICATION, 200.0f * MAGNIFICATION, OBJECT_DEPTH * MAGNIFICATION);
	pVtx[6].pos = D3DXVECTOR3(OBJECT_WIDTH * MAGNI * MAGNIFICATION, 100.0f * MAGNIFICATION, OBJECT_DEPTH * MAGNIFICATION);

	pVtx[7].pos  = D3DXVECTOR3(OBJECT_WIDTH * MAGNIFICATION, -100.0f, -OBJECT_DEPTH * MAGNIFICATION);
	pVtx[8].pos  = D3DXVECTOR3(-OBJECT_WIDTH * MAGNIFICATION, -100.0f, -OBJECT_DEPTH * MAGNIFICATION);
	pVtx[9].pos  = D3DXVECTOR3(-OBJECT_WIDTH * MAGNI * MAGNIFICATION, 100.0f * MAGNIFICATION, -OBJECT_DEPTH * MAGNIFICATION);
	pVtx[10].pos = D3DXVECTOR3(-OBJECT_WIDTH * MAGNIFICATION, 200.0f * MAGNIFICATION, -OBJECT_DEPTH * MAGNIFICATION);
	pVtx[11].pos = D3DXVECTOR3(0.0f, 250.0f * MAGNIFICATION, -OBJECT_DEPTH * MAGNIFICATION);
	pVtx[12].pos = D3DXVECTOR3(OBJECT_WIDTH * MAGNIFICATION, 200.0f * MAGNIFICATION, -OBJECT_DEPTH * MAGNIFICATION);
	pVtx[13].pos = D3DXVECTOR3(OBJECT_WIDTH * MAGNI * MAGNIFICATION, 100.0f * MAGNIFICATION, -OBJECT_DEPTH * MAGNIFICATION);


	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[9].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[10].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[11].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[12].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[13].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;
	pVtx[4].col = m_col;
	pVtx[5].col = m_col;
	pVtx[6].col = m_col;
	pVtx[7].col = m_col;
	pVtx[8].col = m_col;
	pVtx[9].col = m_col;
	pVtx[10].col = m_col;
	pVtx[11].col = m_col;
	pVtx[12].col = m_col;
	pVtx[13].col = m_col;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.142f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.142f * 2.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.142f * 3.0f, 0.0f);
	pVtx[4].tex = D3DXVECTOR2(0.142f * 4.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(0.142f * 5.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(1.0f, 0.0f);
	
	pVtx[7].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(0.142f, 1.0f);
	pVtx[9].tex = D3DXVECTOR2(0.142f * 2.0f, 1.0f);
	pVtx[10].tex = D3DXVECTOR2(0.142f * 3.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(0.142f * 4.0f, 1.0f);
	pVtx[12].tex = D3DXVECTOR2(0.142f * 5.0f, 1.0f);
	pVtx[13].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//インデックスの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_IDX,
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
	pIdx[1] = 7;
	pIdx[2] = 1;
	pIdx[3] = 8;
	pIdx[4] = 2;
	pIdx[5] = 9;
	pIdx[6] = 3;
	pIdx[7] = 10;
	pIdx[8] = 4;
	pIdx[9] = 11;
	pIdx[10] = 5;
	pIdx[11] = 12;
	pIdx[12] = 6;
	pIdx[13] = 13;
	pIdx[14] = 0;
	pIdx[15] = 7;

	
	//インデックスバッファをアンロックする
	m_pIdxBuff->Unlock();

	return S_OK;

}
//========================================
// 終了処理
//========================================
void CMeshClynder::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	// インデックスバッファの破棄
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}


	CObject::Relese();
}
//=======================================
// 更新処理
//=======================================
void CMeshClynder::Update(void)
{
}

//======================================
// 描画処理
//======================================
void CMeshClynder::Draw(void)
{
	CTexture*pTexture = CManager::GetCTexture();

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

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
				0,
				0,
				MAX_BUFF,
				0,
		MAX_IDX * 2);
}
//======================================
// 設定処理
//======================================
CMeshClynder *CMeshClynder::Create(void)
{
	CMeshClynder *pObject3D;

	// オブジェクト3Dの生成
	pObject3D = new CMeshClynder();

	// 初期化処理
	pObject3D->Init();

	return pObject3D;
}
//======================================
// 当たり判定処理
//======================================
bool CMeshClynder::Collision(D3DXVECTOR3 pos)
{
	bool bColli = false;

	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		CObject *pObj = CObject::GetTop(nCntPri);	// 先頭のオブジェクトを代入

		while (pObj != NULL)
		{
			CObject *pObjectNext = pObj->GetNext();	// 次のオブジェクトを保存

			//種類を取得
			TYPE type = pObj->GetType();

			if (type == TYPE_MESHFILED)
			{
				CMeshClynder *pMeshClynder = dynamic_cast<CMeshClynder*>(pObj);

				// 変換した後の位置
				D3DXVECTOR3 Meshpos;
				Meshpos.x = pMeshClynder->Getmtx()._41;
				Meshpos.y = pMeshClynder->Getmtx()._42;
				Meshpos.z = pMeshClynder->Getmtx()._43;

				//現在・前回の位置とフィールドの中心位置の差を格納
				D3DXVECTOR2 PosDiff;

				PosDiff.x = powf(pos.x - Meshpos.x, 2.0f);    //現在のＸ座標の差の２乗
				PosDiff.y = powf(pos.y - Meshpos.y, 2.0f);    //現在のＺ座標の差の２乗    変数は  "Ｙ" だけど、Ｚ座標の差を入れます 

				float fLength = sqrtf(PosDiff.x + PosDiff.y);    //現在のＸ・Ｚの長さを取得

				if (fLength >= 750.0f / 2.0f)
				{//中心位置からの距離がフィールドの半径以上だった

					//bColli = true;
				}

				if (Meshpos.z + OBJECT_DEPTH * MAGNIFICATION <= pos.z)
				{
					bColli = true;
				}
			}
			pObj = pObjectNext;		// 次のオブジェクトを代入
		}
	}
	return bColli;
}