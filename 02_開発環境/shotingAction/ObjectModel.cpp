//====================================================================
//
//モデル処理[ObjectModel.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"ObjectModel.h"
#include"Player3D.h"
#include"Manager.h"
#include"renderer.h"
#include"Texture.h"


//========================================
// コンストラクタ
//========================================
CObjectModel::CObjectModel()
{
	m_pMesh = NULL;
	m_dwNumMat = NULL;
	m_pBuffMat = NULL;
	m_pVertex = NULL;
	m_SizeFVF = NULL;
	m_pPos = NULL;
	m_state = STATE_NONE;
	m_Size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_aParent = NULL;
	m_nIdxTexture = 0;
	m_nDamgeCounter = 0;
}
//========================================
// デストラクタ
//========================================
CObjectModel::~CObjectModel()
{
}
//========================================
//モデルの初期化処理
//========================================
HRESULT CObjectModel::Init(const char* pFilename)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ
	CTexture*pTexture = CManager::GetCTexture();
	D3DXVECTOR3 pos;

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX(pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);
	
	D3DXMATERIAL *pMat;			//マテリアルへのポインタ

	m_nIdxTexture = new int[(int)m_dwNumMat];

	//マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャファイルが存在する

		 ////テクスチャの読み込み
			m_nIdxTexture[nCntMat] = pTexture->Regist(pMat[nCntMat].pTextureFilename);
		}
	}

	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVertex);

	int nNumVertices = m_pMesh->GetNumVertices();

	m_SizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	m_pPos = new D3DXVECTOR3[nNumVertices];

	for (int nCntVer = 0; nCntVer < nNumVertices; nCntVer++)
	{
		m_pPos[nCntVer] = *(D3DXVECTOR3*)m_pVertex;
		m_pVertex += m_SizeFVF;
		// ここで頂点情報の位置を受け取ってる
		// あとは位置毎の一番大きい数値を入手して当たり判定
	}

	return S_OK;
}
//========================================
//モデルの終了処理
//========================================
void CObjectModel::Uninit(void)
{
	// インスタンスを開放
	if (m_nIdxTexture != NULL)
	{
		delete m_nIdxTexture;
		m_nIdxTexture = NULL;
	}
	if (m_pPos != NULL)
	{
		delete m_pPos;
		m_pPos = NULL;
	}

	//テクスチャの破棄
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//頂点バッファの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}
//=======================================
//モデルの更新処理
//=======================================
void CObjectModel::Update(void)
{
	switch (m_state)
	{
	case STATE_NONE:
		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	case STATE_DAMAGE:
		m_nDamgeCounter++;
		m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		if (m_nDamgeCounter == 120)
		{
			m_state = STATE_NONE;
			m_nDamgeCounter = 0;
		}
		break;
	}
}
//======================================
//モデルの描画処理
//======================================
void CObjectModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ
	D3DXMATRIX mtxParent;			//親のマトリックス

	CTexture*pTexture = CManager::GetCTexture();

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//モデルのサイズを変更
	D3DXMatrixScaling(&m_mtxWorld, GetSize().x, GetSize().y, GetSize().z);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	if (m_aParent != NULL)
	{
		// 親モデルのマトリックスを取得する
		mtxParent = m_aParent->m_mtxWorld;
	}
	else
	{
		// 現在のマトリックスを取得する
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);	
	}
	//算出したパーツのワールドマトリックスと親のマトリックスを掛け合わせる
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxParent);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//色の設定
		pMat[nCntMat].MatD3D.Diffuse.r = m_col.r;
		pMat[nCntMat].MatD3D.Diffuse.g = m_col.g;
		pMat[nCntMat].MatD3D.Diffuse.b = m_col.b;
		pMat[nCntMat].MatD3D.Diffuse.a = m_col.a;

		//マテリアルの取得
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, pTexture->GetAddress(*m_nIdxTexture));

		//モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}
}
//======================================
// 親の設定処理
//======================================
void CObjectModel::SetParent(CObjectModel *pObjectModel)
{
	m_aParent = pObjectModel;
}
//======================================
// 設定処理
//======================================
CObjectModel *CObjectModel::Create(const char* pFilename, D3DXVECTOR3 pos)
{
	CObjectModel *pObjectModel;

	// オブジェクト3Dの生成
	pObjectModel = new CObjectModel();

	// 初期化処理
	pObjectModel->Init(pFilename);
	
	pObjectModel->SetPos(pos);

	return pObjectModel;
}