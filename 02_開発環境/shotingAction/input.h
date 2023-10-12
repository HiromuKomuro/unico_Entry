//====================================================================
//
//�C���v�b�g����[input.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include"dinput.h"				//���͏����ɕK�v
#pragma comment(lib,"dinput8.lib")		//���͏����ɕK�v

//�}�N����`
#define NUM_KEY_MAX			(256)		//�L�[�̍ő吔


//---------------------------------------------------------------------------
//					*****			���̓N���X�̒�`			*****
//---------------------------------------------------------------------------
class CInput
{
public:
	 CInput();
	 virtual ~CInput();
	// �����o�[�֐�
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ������
	virtual void Uninit(void);								// �I��
	virtual void Update(void) = 0;							// �X�V

protected:
	static LPDIRECTINPUT8 m_pInput;				// DirectInput�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDevice;				// ���̓f�o�C�X�ւ̃|�C���^
};		
//---------------------------------------------------------------------------
//					*****			�L�[�{�[�h�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CInputKeyboard :public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	// �����o�[�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ������
	void Uninit(void);								// �I��
	void Update(void);								// �X�V

	bool GetKeyboardPress(int nKey);						// �v���X
	bool GetKeyboardTrigger(int nKey);						// �g���K�[
	bool GetKeyboardRelease(int nKey);						// �����[�X
private:
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aKeyStatePress[NUM_KEY_MAX];
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];

};

#endif 

