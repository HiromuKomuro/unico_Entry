// =======================================================
//
// ���C������(main.cpp)
// author KOMURO HIROMU
//
// =======================================================
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include"main.h"
#include"renderer.h"
#include"object.h"
#include"object2D.h"
#include"Manager.h"
#include"input.h"

//�}�N����`
#define CLASS_NAME			"windowclass"						//�E�C���h�N���X�̖��O
#define WINDOW_NAME			"3D�A�N�V�����V���[�e�B���O"		//�E�C���h�E�̖��O(�L���v�`���̕\��)

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hinstancePrev, LPSTR lpCmdLine, int nCmdshow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,						//�E�C���h�̃X�^�C��
		WindowProc,						//�E�C���h�E�v���V���\�W��
		0,								//0�ɂ���(�ʏ�͎g�p���Ȃ�)
		0,								//0�ɂ���(�ʏ�͎g�p���Ȃ�)
		hInstance,						//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),	//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),		//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW),			//�N���C�A���g�̈�̔w�i�F
		NULL,							//���j���[�o�[
		CLASS_NAME,						//�E�C���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)	//�t�@�C���̃A�C�R��
	};
	HWND hWnd;							//�E�C���h�E�n���h��(���ʎq)
	MSG msg;							//���b�Z�[�W���i�[����ϐ�

										//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�E�C���h�E�𐶐�
	hWnd = CreateWindowEx(0,			//�g���E�C���h�E�X�^�C��
		CLASS_NAME,						//�E�C���h�E�N���X�̖��O
		WINDOW_NAME,					//�E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,			//�E�C���h�E�X�^�C��
		CW_USEDEFAULT,					//�E�C���h�E�̍���X���W
		CW_USEDEFAULT,					//    //      ����Y���W
		SCREEN_WIDTH,					//    //      ��
		SCREEN_HEIGHT,					//    //      ����
		NULL,							//�e�E�C���h�E�̃n���h��
		NULL,							//���j���[�n���h���܂��͎q�E�C���h�EID
		hInstance,						//�C���X�^���X�n���h��
		NULL);							//�E�C���h�E�쐬�f�[�^

	CManager *pManager = NULL;
	// �����_���[�̐���
	if (pManager != NULL)
	{
		// �����_���[�̊J��
		delete pManager;
		pManager = NULL;
	}
	pManager = new CManager;	// �����_���[�̃C���X�^���X����

	//�������ݒ�
	if (FAILED(pManager->Init(hInstance,hWnd, TRUE)))
	{//���������������s�����ꍇ

		return -1;

	}

	//�E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdshow);			//�E�C���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);					//�N���C�A���g�̈���X�V

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);			//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);			//�E�C���h�E�v���V�[�W���փ��b�Z�[�W����o
			}
		}
		else
		{//DirectX�̏���
			//�X�V����
			pManager->Update();

			//�`�揈��
			pManager->Draw();
		
		}
	}
	// �����_���[�̏I��
	if (pManager != NULL)
	{
		// �����_���[�̊J��
		pManager->Uninit();
		delete pManager;
		pManager = NULL;
	}

	//�E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//�E�C���h�E�v���V�[�W��
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static POINT pos = { 300,300 };		//�����̎n�_(X���W�EY���W)
	static POINT move = { 1,1 };		//�����̎n�_�̈ړ���(X�����EY����)
	const RECT rect = { 0,0,SCREEN_WIDTH , SCREEN_HEIGHT };		//�E�C���h�E�̗̈�(���񂯂�)
	char aString[256] = "test";			//�`�悷��e�L�X�g���i�[
	int nData = 0,nData1 = 0;


	switch (uMsg)
	{
	case WM_KEYDOWN:					//�L�[�����̃��b�Z�[�W

		switch (wParam)
		{
		case VK_ESCAPE:					//[ESC]�L�[�������ꂽ

			//�E�C���h�E��j������(WM_DESTROY���b�Z�[�W)
			DestroyWindow(hWnd);
			break;

		}
		break;


	case WM_DESTROY:					//�E�C���h�E�j���̃��b�Z�[�W
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);				
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);		//����̏�����Ԃ�
}
