//====================================================================
//
//モデル処理[Model.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"BlockX.h"
#include"input.h"
#include"Bullet.h"
#include"Camera.h"
#include"Manager.h"
#include"renderer.h"
#include"sound.h"
#include"Texture.h"
#include"throughWall.h"
#include"collisionline.h"
#include"game.h"

//========================================
// コンストラクタ
//========================================
CBlockX::CBlockX()
{
	// 初期化
	m_Maxpos = { 0,0,0 }; m_Minpos = { 0,0,0 };

	m_fAngle = 0.0f;
	m_fLength = 0.0f;

	m_pMesh = NULL;
	m_dwNumMat = NULL;
	m_pBuffMat = NULL;
	m_pVertex = NULL;
	m_SizeFVF = NULL;
	m_pPos = NULL;
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_aParent = NULL;
	m_nIdxTexture = 0;
}
//========================================
// デストラクタ
//========================================
CBlockX::~CBlockX()
{
}
//========================================
// 初期化処理
//========================================
HRESULT CBlockX::Init(const char* pFilename)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ
	CTexture*pTexture = CManager::GetCTexture();

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
// 終了処理
//========================================
void CBlockX::Uninit(void)
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
// 更新処理
//=======================================
void CBlockX::Update(void)
{
}
//======================================
// 描画処理
//======================================
void CBlockX::Draw(D3DXMATRIX mtxPar)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	CTexture*pTexture = CManager::GetCTexture();

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//モデルのサイズを変更
	D3DXMatrixScaling(&m_mtxWorld, m_Size.x, m_Size.y, m_Size.z);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	
	//マテリアル情報に対するポインタを取得
    pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	
	//算出したパーツのワールドマトリックスと親のマトリックスを掛け合わせる	
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxPar);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (CGame::GetPause() != false)return;
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
// 設定処理
//======================================
CBlockX * CBlockX::Create(D3DXVECTOR3 pos, const char* pFilename,D3DXVECTOR3 Size)
{
	CBlockX *pModel;

	// オブジェクト3Dの生成
	pModel = new CBlockX();

	// 位置の設定
	pModel->SetPos(pos);

	// サイズの設定
	pModel->SetSize(Size);

	// 初期化処理
	pModel->Init(pFilename);

	// 力の向きの設定
	pModel->SetVector();

	return pModel;
}
//======================================
// 外積計算に必要な要素の設定
//======================================
void CBlockX::SetVector(void)
{
	D3DXVECTOR3 *posVertex = m_pPos;
	const int nNumVertices = m_pMesh->GetNumVertices();

	for (int nCntVer = 0; nCntVer < nNumVertices; nCntVer++)
	{
		// 頂点情報の最大,最小うけとる
		if (m_Maxpos.x < posVertex[nCntVer].x)
		{
			m_Maxpos.x = posVertex[nCntVer].x;
		}
		else if (m_Minpos.x > posVertex[nCntVer].x)
		{
			m_Minpos.x = posVertex[nCntVer].x;
		}
		if (m_Maxpos.y < posVertex[nCntVer].y)
		{
			m_Maxpos.y = posVertex[nCntVer].y;
		}
		else if (m_Minpos.y > posVertex[nCntVer].y)
		{
			m_Minpos.y = posVertex[nCntVer].y;
		}
		if (m_Maxpos.z < posVertex[nCntVer].z)
		{
			m_Maxpos.z = posVertex[nCntVer ].z;
		}
		else if (m_Minpos.z > posVertex[nCntVer].z)
		{
			m_Minpos.z = posVertex[nCntVer].z;
		}
	}

	// 頂点情報にサイズを入れる
	m_Maxpos.x *= m_Size.x;
	m_Minpos.x *= m_Size.x;
	m_Maxpos.y *= m_Size.y;
	m_Minpos.y *= m_Size.y;
	m_Maxpos.z *= m_Size.z;
	m_Minpos.z *= m_Size.z;

	//対角線の長さを算出する
	m_fLength = sqrtf(m_Maxpos.y * m_Maxpos.y + m_Maxpos.x * m_Maxpos.x);
	//対角線の角度を算出する
	m_fAngle = atan2f(m_Maxpos.y, m_Maxpos.x);

}

