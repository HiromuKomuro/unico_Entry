// =======================================================
//
// 背景処理(bg.h)
// author KOMURO HIROMU
//
// =======================================================
// 二重インクルード防止
#ifndef _BG_H_
#define _BG_H_

#include"object2D.h"
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CBg: public CObject2D
{
public:
	CBg();
	~CBg();

	HRESULT Init(void);			// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理

	void Setpos(D3DXVECTOR3 pos) { m_pos = pos; }				// 位置の設定
	void Setscale(D3DXVECTOR2 scale) { m_scale = scale; }		// 大きさの設定
	void SetFile(char *pfilename) { m_pFilename = pfilename; }	// ファイルネームの設定

	static CBg *Create(D3DXVECTOR3 pos,D3DXVECTOR2 scale,char *pFilename);
private:
	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR2 m_scale;	// 大きさ
	char *m_pFilename;		// ファイルの名前
	int m_nTexType;			// テクスチャの種類
	int m_nIdxTexture;		// テクスチャの番号
};
#endif