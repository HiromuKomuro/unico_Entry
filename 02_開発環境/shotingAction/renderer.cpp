// =======================================================
//
// レンダリング処理(renderer.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"renderer.h"
#include"main.h"
#include"object.h"
#include"Manager.h"
#include"Camera.h"
#include"Test.h"
//====================================
// コンストラクタ
//====================================
CRenderer::CRenderer()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
}
//====================================
// デストラクタ
//====================================
CRenderer::~CRenderer()
{
}
//====================================
// 初期化処理
//====================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;	//プレゼンテーションパラメータ

	//Direct3Dオブジェクトの生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを所得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));		//パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;	//ゲーム画面サイズ（幅）

	d3dpp.BackBufferHeight = SCREEN_HEIGHT;	//ゲーム画面サイズ（高さ）

	d3dpp.BackBufferFormat = d3ddm.Format;	//バックバッファの形式

	d3dpp.BackBufferCount = 1;				//バックバッファの数

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//ダブルバッファの切り替え（映像信号に同期)

	d3dpp.EnableAutoDepthStencil = TRUE;		//デプスバッファとステンシルバッファを作成

	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//デプスバッファとして16bitを使う

	d3dpp.Windowed = bWindow;					//ウインドウモード

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//リフレッシュレート

	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;				//インターバル

																			//Direct3Dデバイスの生成
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))

	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))

		{
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))

			{
				return E_FAIL;
			}
		}
	}
	//レンダ―ステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	LPDIRECT3DSURFACE9 pRenderDef, pZBuffDef;
	for (int nCntmt = 0; nCntmt < 2; nCntmt++)
	{
		// レンダリングターゲット用テクスチャの生成
		m_pD3DDevice->CreateTexture(SCREEN_WIDTH,
			SCREEN_HEIGHT,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&m_pTextureMT[nCntmt],
			NULL);

		// テクスチャレンダリング用インターフェースの生成
		m_pTextureMT[nCntmt]->GetSurfaceLevel(0, &m_pRenderMT[nCntmt]);
	}

	// テクスチャレンダリング用Zバッファの生成
	m_pD3DDevice->CreateDepthStencilSurface(SCREEN_WIDTH,
		SCREEN_HEIGHT,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&m_pZBuffMT,
		NULL);

	// 現在のレンダリングターゲットを取得(保存)
	m_pD3DDevice->GetRenderTarget(0, &pRenderDef);

	// 現在のZバッファを取得(保存)
	m_pD3DDevice->GetDepthStencilSurface(&pZBuffDef);
	for (int nCntmt = 0; nCntmt < 2; nCntmt++)
	{
		// レンダリングターゲットを生成したテクスチャに設定
		m_pD3DDevice->SetRenderTarget(0, m_pRenderMT[nCntmt]);
	}
	// Zバッファを生成したZバッファに設定
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

	// レンダリングターゲット用のテクスチャのクリア
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(255, 255, 255, 255), 1.0f, 0);

	// レンダリングターゲットを元に戻す
	m_pD3DDevice->SetRenderTarget(0, pRenderDef);

	// Zバッファを元に戻す
	m_pD3DDevice->SetDepthStencilSurface(pZBuffDef);

	// テクスチャレンダリング用ビューポートの設定
	m_viewportMT.X = 0;
	m_viewportMT.Y = 0;
	m_viewportMT.Width = SCREEN_WIDTH;
	m_viewportMT.Height = SCREEN_HEIGHT;
	m_viewportMT.MinZ = 0.0f;
	m_viewportMT.MaxZ = 1.0f;


	return S_OK;
}
//======================================
// 終了処理
//=====================================
void CRenderer::Uninit(void)
{
	//Direct3Dデバイスの破棄
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの破棄
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}

	// テクスチャ用の破棄









	// すべてのオブジェクトの終了処理
	CObject::ReleseAll();
}
//======================================
// 更新処理
//======================================
void CRenderer::Update(void)
{
	// 全オブジェクトの更新処理
	CObject::UpdateAll();		
}
//======================================
// 描画処理
//======================================
void CRenderer::Draw(void)
{
	LPDIRECT3DSURFACE9 pRenderWk;
	LPDIRECT3DTEXTURE9  pTextureWk;

	//画面クリア(バックバッファ&Zぶっふぁのクリア)
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(255, 255, 255, 255), 1.0f, 0);


	//描画開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合8

		// 全オブジェクトの描画処理
		CObject::DrawAll();
		//描画終了
		m_pD3DDevice->EndScene();

	}
	//ばっくばっふぁとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//======================================
// レンダリングターゲットの変更
//======================================
void CRenderer::ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 posU)
{
	D3DXMATRIX mtxview, mtxProjection;
	float fAspect;

	// レンダリングターゲットを生成したテクスチャに設定
	m_pD3DDevice->SetRenderTarget(0, m_pRenderMT[0]);

	// Zバッファを生成したZバッファに設定
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

	// テクスチャレンダリング用のビューポート
	m_pD3DDevice->SetViewport(&m_viewportMT);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&mtxview);

	// ビューマトリックスの生成
	D3DXMatrixLookAtLH(&mtxview,
		&posV,	// 視点
		&posR,	// 注視点
		&posU);	// 上方向ベクトル


	// ビューマトリックスの設定
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &mtxview);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&mtxProjection);

	// プロジェクションマトリックスの生成
	fAspect = (float)m_viewportMT.Width / (float)m_viewportMT.Height;

	//プロジェクションマトリックスを作成(投資投影)
	D3DXMatrixPerspectiveFovLH(&mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,			//視野角の最小値
		10000.0f);		//視野角の最大値

	// プロジェクションマトリックスの設定
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);

}
//======================================
// デバイスの取得処理
//======================================
LPDIRECT3DDEVICE9  CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}