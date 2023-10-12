//====================================================================
//
//フェード処理[Fade.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"Fade.h"
#include"renderer.h"

// 静的メンバ変数
LPDIRECT3DVERTEXBUFFER9 CFade::s_pVtxBuff = NULL;
//========================================
// コンストラクタ
//========================================
CFade::CFade()
{
	m_fade = FADE_NONE;										// フェード状態に
	m_modeNext = CScene::MODE_TITLE;						// 次の画面(モード)に設定
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		// 黒いポリゴン(不透明)にしておく
}
//========================================
// デストラクタ
//========================================
CFade::~CFade()
{

}
//========================================
// 初期化処理
//========================================
HRESULT CFade::Init(CScene::MODE modeNext)
{
	m_modeNext = modeNext;	//次の画面(モード)に設定

	CRenderer *pRenderer = CManager::GetRenderer();

	//頂点バッファの読み込み
	if (FAILED(pRenderer->GetDevice()
		->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&s_pVtxBuff,
			NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D*pVtx;				//頂点情報へ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 00.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 00.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);


	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;


	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);


	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	s_pVtxBuff->Unlock();

	//モードの設定
	Set(m_modeNext);

	return S_OK;
}
//========================================
//フェードの終了処理
//========================================
void CFade::Uninit(void)
{
	//頂点バッファの破棄
	if (s_pVtxBuff != NULL)
	{
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;

	}
}
//=======================================
//フェードの更新処理
//=======================================
void CFade::Update(void)
{
	VERTEX_2D*pVtx;				//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{//フェードイン状態の時
			m_colorFade.a -= 0.05f;			//ポリゴンを透明にしていく

			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;
				m_fade = FADE_NONE;			//何もしていない状態に

			}
		}
		else if (m_fade == FADE_OUT)
		{//フェードアウト状態
			m_colorFade.a += 0.05f;			//ポリゴンを不透明にしていく

			if (m_colorFade.a >= 1.0f)
			{
				m_colorFade.a = 1.0f;
				m_fade = FADE_IN;			//フェードイン状態に

				//モード設定(次の画面に移行)
				CManager::SetMode(m_modeNext);
			}
		}
	
	}
	
	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colorFade.a);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colorFade.a);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colorFade.a);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colorFade.a);

	//頂点バッファをアンロックする
	s_pVtxBuff->Unlock();
}

//======================================
//フェードの描画処理
//======================================
void CFade::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

	//頂点バッファのデータストリームに設定
	pRenderer->GetDevice()->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマット
	pRenderer->GetDevice()->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pRenderer->GetDevice()->SetTexture(0, NULL);		//テクスチャを使わない(NULL)にする

	//ポリゴンの描画
	pRenderer->GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}
//=======================================
//フェードの設定処理
//=======================================
void CFade::Set(CScene::MODE modeNext)
{
	m_fade = FADE_OUT;				//フェードアウト状態に

	m_modeNext = modeNext;			//次の画面(モード)を設定

	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//黒いポリゴン(透明)にしておく

}
