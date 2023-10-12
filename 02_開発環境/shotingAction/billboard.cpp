//====================================================================
//
//ビルボード処理[Billboard.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"Billboard.h"
#include"input.h"
#include"Manager.h"
#include"renderer.h"
#include"Texture.h"

//マクロ定義
#define Billboard_MOVE			(1.5)
#define Billboard_WIDTH			(200)
#define Billboard_DEPTH			(200)
#define Billboard_HEIGHT		(200)

//========================================
// コンストラクタ
//========================================
CObjectBillboard::CObjectBillboard()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
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
CObjectBillboard::~CObjectBillboard()
{
}
//========================================
//ビルボードの初期化処理
//========================================
HRESULT CObjectBillboard::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ
	CTexture*pTexture = CManager::GetCTexture();

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの読み込み
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);
	VERTEX_3D*pVtx;				//頂点情報へのポインタ―


	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, m_fDepth, m_fHeight);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, m_fDepth, m_fHeight);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, -m_fDepth, -m_fHeight);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, -m_fDepth, -m_fHeight);
												 
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

	return S_OK;
}
//========================================
//ビルボードの終了処理
//========================================
void CObjectBillboard::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	// テクスチャの破棄}
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	CObject::Relese();
}
//=======================================
//ビルボードの更新処理
//=======================================
void CObjectBillboard::Update(void)
{
}
//======================================
//ビルボードの描画処理
//======================================
void CObjectBillboard::Draw(void)
{
	CTexture*pTexture = CManager::GetCTexture();

	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	D3DXMATRIX mtxTrans;	//計算用マトリックス
	D3DXMATRIX mtxView;		//ビューマトリックス取得用


	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);		//逆行列を求める
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Zテストを無効にするにする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

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
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//レンダ―ステートの設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	//レンダ―ステートを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}
//======================================
// 設定処理
//======================================
CObjectBillboard *CObjectBillboard::Create(void)
{
	CObjectBillboard *pObjectBillboard;

	// オブジェクト3Dの生成
	pObjectBillboard = new CObjectBillboard();

	// 初期化処理
	pObjectBillboard->Init();

	return pObjectBillboard;
}
//======================================
// 色の設定
//======================================
void CObjectBillboard::SetCol(const D3DCOLOR col)
{
	m_col = col;
	VERTEX_3D*pVtx;				//頂点情報へ

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
// テクスチャの設定
//======================================
void CObjectBillboard::SetAnimeTex(float Max_Conter, int m_nAnimeCounter)
{
	VERTEX_3D*pVtx;				//頂点情報へ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + (m_nAnimeCounter * (1.0f / Max_Conter)), 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1.0f / Max_Conter) + (m_nAnimeCounter * (1.0f / Max_Conter)), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (m_nAnimeCounter * (1.0f / Max_Conter)), 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1.0f / Max_Conter) + (m_nAnimeCounter * (1.0f / Max_Conter)), 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//======================================
// テクスチャの加算処理
//======================================
void CObjectBillboard::SetAddTex(float fTex)
{
	VERTEX_3D*pVtx;				//頂点情報へ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の更新
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + fTex);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + fTex);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f + fTex);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f + fTex);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//======================================
// テクスチャの割り当て
//======================================
void CObjectBillboard::BindTexture(int pTexture)
{
	m_nIdxTexture = pTexture;
}
//======================================
// 大きさの設定
//======================================
void CObjectBillboard::SetScale(float fWidth, float fHeight)
{
	// 代入
	m_fHeight = fHeight;
	m_fWidth = fWidth;
	m_fDepth = fHeight;
}