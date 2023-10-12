//====================================================================
//
//インプット処理[input.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include"dinput.h"				//入力処理に必要
#pragma comment(lib,"dinput8.lib")		//入力処理に必要

//マクロ定義
#define NUM_KEY_MAX			(256)		//キーの最大数


//---------------------------------------------------------------------------
//					*****			入力クラスの定義			*****
//---------------------------------------------------------------------------
class CInput
{
public:
	 CInput();
	 virtual ~CInput();
	// メンバー関数
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化
	virtual void Uninit(void);								// 終了
	virtual void Update(void) = 0;							// 更新

protected:
	static LPDIRECTINPUT8 m_pInput;				// DirectInputへのポインタ
	LPDIRECTINPUTDEVICE8 m_pDevice;				// 入力デバイスへのポインタ
};		
//---------------------------------------------------------------------------
//					*****			キーボードクラスの定義			*****
//---------------------------------------------------------------------------
class CInputKeyboard :public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	// メンバー関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化
	void Uninit(void);								// 終了
	void Update(void);								// 更新

	bool GetKeyboardPress(int nKey);						// プレス
	bool GetKeyboardTrigger(int nKey);						// トリガー
	bool GetKeyboardRelease(int nKey);						// リリース
private:
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aKeyStatePress[NUM_KEY_MAX];
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];

};

#endif 

