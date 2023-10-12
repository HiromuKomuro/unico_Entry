//====================================================================
//
//インプット処理[input.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"input.h"

// 静的メンバ変数
LPDIRECTINPUT8 CInput::m_pInput = NULL;				// DirectInputへのポインタ

//====================================
// コンストラクタ
//====================================
CInput::CInput()
{
	m_pDevice = NULL;
}
//====================================
// デストラクタ
//====================================
CInput::~CInput()
{
}

//====================================
// 入力の初期化処理
//====================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		//Directオブジェクトの生成
		DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL);		
	}

	return S_OK;	
}

//====================================
// 入力の終了処理
//====================================
void CInput::Uninit(void)
{
	//入力デバイス(キーボード)の破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();		//キーボードへのアクセス権を放棄
		m_pDevice->Release();
		m_pDevice = NULL;

	}

	//DirectInputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//====================================
// キーボードのコンストラクタ
//====================================
CInputKeyboard::CInputKeyboard()
{
	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
	{
		m_aKeyState[nCnt] = 0;
		m_aKeyStatePress[nCnt] = 0;
		m_aKeyStateTrigger[nCnt] = 0;
		m_aKeyStateRelease[nCnt] = 0;
	}
}
//====================================
// キーボードのデストラクタ
//====================================
CInputKeyboard::~CInputKeyboard()
{
}
//====================================
// キーボードの初期化処理
//====================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		// 入力の初期化
		CInput::Init(hInstance, hWnd);

		//入力デバイス(キーボード)の生成
		if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
		{
			return E_FAIL;
		}

		//データフォーマットを設定
		if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
		{
			return E_FAIL;
		}

		//協調モードを設定
		if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
		{
			return E_FAIL;
		}

		//キーボードへのアクセス権を獲得
		m_pDevice->Acquire();

		return S_OK;
	}
	return -1;
}
//====================================
// キーボードの終了処理
//====================================
void CInputKeyboard::Uninit(void)
{
	// 入力の終了処理
	CInput::Uninit();
}
//====================================
// キーボードの更新処理
//====================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];				//キーボードの入力情報

	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];	//キーボードのトリガー情報を保存
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] | aKeyState[nCntKey]) ^ aKeyState[nCntKey];	//キーボードのリリース情報を保存
			m_aKeyState[nCntKey] = aKeyState[nCntKey];		//キーボードのプレス情報を保存
		}
	}
	else
	{
		m_pDevice->Acquire();				//キーボードのアクセス権を獲得
	}
}
//====================================
// キーボードのプレス情報を獲得
//====================================
bool CInputKeyboard::GetKeyboardPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true: false;
}
//====================================
// キーボードのトリガー情報を取得
//====================================
bool CInputKeyboard::GetKeyboardTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true: false;
}
//====================================
// キーボードのリリース情報を取得
//====================================
bool CInputKeyboard::GetKeyboardRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}