// =======================================================
//
// レンダリング処理(renderer.h)
// author KOMURO HIROMU
//
// =======================================================
// 二重インクルード防止
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include"main.h"

//---------------------------------------------------------------------------
//					*****			レンダラークラスの定義			*****
//---------------------------------------------------------------------------
class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, BOOL bWindow);	// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	LPDIRECT3DDEVICE9 GetDevice(void);

	void ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 posU);
	LPDIRECT3DTEXTURE9 GetTextureMT(void) { return m_pTextureMT[0]; }
private:

	LPDIRECT3D9				m_pD3D;			// DirectX3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Direct3Dデバイスへのポインタ

	LPDIRECT3DTEXTURE9		m_pTextureMT[2];// レンダリングターゲット用テクスチャ
	LPDIRECT3DSURFACE9		m_pRenderMT[2];	// テクスチャレンダリング用インターフェース
	LPDIRECT3DSURFACE9		m_pZBuffMT;		// テクスチャレンダリング用Zバッファ
	D3DVIEWPORT9			m_viewportMT;	// テクスチャレンダリング用ビューポート

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMT;	// フィードバック用ポリゴンの頂点バッファ
	
};

#endif