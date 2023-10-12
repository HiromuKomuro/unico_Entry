//====================================================================
//
//フェード処理[Fade.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _FADE_H_		//このマクロ定義がされてなかったら
#define _FADE_H_		//二重インクルード防止のマクロを定義する

#include "Manager.h"
//---------------------------------------------------------------------------
//					*****			フェードクラスの定義			*****
//---------------------------------------------------------------------------
class CFade
{
public:
	//フェードの状態
	typedef enum
	{
		FADE_NONE = 0,		//何もしていない状態
		FADE_IN,			//フェードイン状態
		FADE_OUT,			//フェードアウト状態
		FADE_MAX
	}FADE;

	CFade();
	~CFade();

	HRESULT Init(CScene::MODE modeNext);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(CScene::MODE modeNext);
	FADE Get(void) { return m_fade; };
private:
	static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuff;	//頂点バッファのポインタ
	FADE m_fade;									//フェードの状態
	CScene::MODE m_modeNext;						//次の画面(モード)
	D3DXCOLOR m_colorFade;							//ポリゴン(フェード)の色
};
#endif
