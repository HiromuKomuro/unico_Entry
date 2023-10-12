//====================================================================
//
// タイトル管理処理[TitleManager.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _TITLEMANAGER_H_		//このマクロ定義がされてなかったら

#define _TITLEMANAGER_H_		//二重インクルード防止のマクロを定義する

#define  MAX_WAVE	(64)
#include"main.h"

class CStartBg;
class CTutorialBg;
class CEndBg;
class CTutorial;
class CObject2D;
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CTitleManager
{
public:
	// タイトルの
	typedef enum
	{
		TITLE_NONE = 0,
		TITLE_END,
		TITLE_START,
		TITLE_TUTORIAL,
		TITLE_MAX
	}TITLE_SELECT;

	CTitleManager();
	~CTitleManager();

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	static CStartBg *GetStartBg(void) { return s_pStartBg; }			// スタート背景の入手
	static CTutorialBg *GetTutorialBg(void) { return s_pTutorialBg; }	// スタート背景の入手
	static CEndBg *GetEndBg(void) { return s_pEndBg; }					// 終了背景の入手
	static CTutorial *GetTutorial(void) { return s_pTutorial; }			// チュートリアルの入手

private:
	static CStartBg *s_pStartBg;			// スタート背景のポインタ
	static CTutorialBg  *s_pTutorialBg;	// チュートリアル背景のポインタ
	static CEndBg  *s_pEndBg;				// 終了背景のポインタ
	static CTutorial *s_pTutorial;		// チュートリアルのポインタ
	TITLE_SELECT m_TitleSelect;			// タイトルの情報
	int m_nCounterSelect;				// 選択カウンター

};
#endif