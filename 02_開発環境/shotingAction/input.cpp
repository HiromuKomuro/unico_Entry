//====================================================================
//
//�C���v�b�g����[input.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"input.h"

// �ÓI�����o�ϐ�
LPDIRECTINPUT8 CInput::m_pInput = NULL;				// DirectInput�ւ̃|�C���^

//====================================
// �R���X�g���N�^
//====================================
CInput::CInput()
{
	m_pDevice = NULL;
}
//====================================
// �f�X�g���N�^
//====================================
CInput::~CInput()
{
}

//====================================
// ���͂̏���������
//====================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		//Direct�I�u�W�F�N�g�̐���
		DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL);		
	}

	return S_OK;	
}

//====================================
// ���͂̏I������
//====================================
void CInput::Uninit(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();		//�L�[�{�[�h�ւ̃A�N�Z�X�������
		m_pDevice->Release();
		m_pDevice = NULL;

	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//====================================
// �L�[�{�[�h�̃R���X�g���N�^
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
// �L�[�{�[�h�̃f�X�g���N�^
//====================================
CInputKeyboard::~CInputKeyboard()
{
}
//====================================
// �L�[�{�[�h�̏���������
//====================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		// ���͂̏�����
		CInput::Init(hInstance, hWnd);

		//���̓f�o�C�X(�L�[�{�[�h)�̐���
		if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
		{
			return E_FAIL;
		}

		//�f�[�^�t�H�[�}�b�g��ݒ�
		if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
		{
			return E_FAIL;
		}

		//�������[�h��ݒ�
		if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
		{
			return E_FAIL;
		}

		//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
		m_pDevice->Acquire();

		return S_OK;
	}
	return -1;
}
//====================================
// �L�[�{�[�h�̏I������
//====================================
void CInputKeyboard::Uninit(void)
{
	// ���͂̏I������
	CInput::Uninit();
}
//====================================
// �L�[�{�[�h�̍X�V����
//====================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];				//�L�[�{�[�h�̓��͏��

	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];	//�L�[�{�[�h�̃g���K�[����ۑ�
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] | aKeyState[nCntKey]) ^ aKeyState[nCntKey];	//�L�[�{�[�h�̃����[�X����ۑ�
			m_aKeyState[nCntKey] = aKeyState[nCntKey];		//�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire();				//�L�[�{�[�h�̃A�N�Z�X�����l��
	}
}
//====================================
// �L�[�{�[�h�̃v���X�����l��
//====================================
bool CInputKeyboard::GetKeyboardPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true: false;
}
//====================================
// �L�[�{�[�h�̃g���K�[�����擾
//====================================
bool CInputKeyboard::GetKeyboardTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true: false;
}
//====================================
// �L�[�{�[�h�̃����[�X�����擾
//====================================
bool CInputKeyboard::GetKeyboardRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}