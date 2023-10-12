//====================================================================
//
//モデル処理[Model.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"Model.h"
#include"input.h"
#include"Bullet.h"
#include"Camera.h"
#include"Manager.h"
#include"renderer.h"
#include"sound.h"
#include"Texture.h"

//マクロ定義
#define MODEL_MOVE			(3)

//========================================
// コンストラクタ
//========================================
CXModel::CXModel()
{
	m_pMesh = NULL;
	m_pTexture = NULL;
	m_dwNumMat = NULL;
	m_pBuffMat = NULL;
	m_pVertex = NULL;
	m_SizeFVF = NULL;
	m_pPos = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nIdxMode = -1;
	m_nIdxModelParent = 0;
	CObject::SetType(TYPE_XMODEL);	// 種類を設定
	m_nIdxTexture = NULL;
}
//========================================
// デストラクタ
//========================================
CXModel::~CXModel()
{
}
//========================================
//モデルの初期化処理
//========================================
HRESULT CXModel::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ
	CTexture*pTexture = CManager::GetCTexture();
	D3DXVECTOR3 pos;

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATERIAL *pMat;			//マテリアルへのポインタ

	//m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_dwNumMat];
	m_nIdxTexture = new int[(int)m_dwNumMat];

	//マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャファイルが存在する

		 //テクスチャの読み込み
			//D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_pTexture[nCntMat]);
			m_nIdxTexture[nCntMat] = pTexture->Regist(pMat[nCntMat].pTextureFilename);
		}
		else
		{
			m_nIdxTexture[nCntMat] = NULL;
		}
	}

	//影を設定

	return S_OK;
}
//========================================
//モデルの終了処理
//========================================
void CXModel::Uninit(void)
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
void CXModel::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	if (pInputKeyboard->GetKeyboardTrigger(DIK_Q) == true)
	{
		m_rot.z += ROT_TRANS;
	}
	if (pInputKeyboard->GetKeyboardTrigger(DIK_E) == true)
	{
		m_rot.z -= ROT_TRANS;
	}
}
//======================================
//モデルの描画処理
//======================================
void CXModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ
	CTexture*pTexture = CManager::GetCTexture();
	D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f };

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//モデルのサイズを変更
	D3DXMatrixScaling(&m_mtxWorld, m_Size.x, m_Size.y, m_Size.z);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//D3DXMatrixRotationAxis(&mtxRot, &pos, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

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

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}
//======================================
// 設定処理
//======================================
CXModel *CXModel::Create(const char* pFilename)
{
	CXModel *pModel;

	// オブジェクト3Dの生成
	pModel = new CXModel();

	// モデルの設定
	pModel->BindModel(pFilename);

	// 初期化処理
	pModel->Init();

	return pModel;
}

//======================================
// モデルの設定処理
//======================================
void CXModel::BindModel(const char* pFilename)
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

	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVertex);

	int nNumVertices = m_pMesh->GetNumVertices();

	m_SizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	m_pPos = new D3DXVECTOR3[nNumVertices];

	for (int nCntVer = 0; nCntVer < nNumVertices; nCntVer++)
	{
		m_pPos[nCntVer] = *(D3DXVECTOR3*)m_pVertex;
		m_pVertex += m_SizeFVF;
		// 頂点情報の位置を受け取る

	}

}