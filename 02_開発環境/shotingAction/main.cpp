// =======================================================
//
// メイン処理(main.cpp)
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

//マクロ定義
#define CLASS_NAME			"windowclass"						//ウインドクラスの名前
#define WINDOW_NAME			"3Dアクションシューティング"		//ウインドウの名前(キャプチャの表示)

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hinstancePrev, LPSTR lpCmdLine, int nCmdshow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,						//ウインドのスタイル
		WindowProc,						//ウインドウプロシャ―ジャ
		0,								//0にする(通常は使用しない)
		0,								//0にする(通常は使用しない)
		hInstance,						//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),	//タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),		//マウスカーソル
		(HBRUSH)(COLOR_WINDOW),			//クライアント領域の背景色
		NULL,							//メニューバー
		CLASS_NAME,						//ウインドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)	//ファイルのアイコン
	};
	HWND hWnd;							//ウインドウハンドル(識別子)
	MSG msg;							//メッセージを格納する変数

										//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	//ウインドウを生成
	hWnd = CreateWindowEx(0,			//拡張ウインドウスタイル
		CLASS_NAME,						//ウインドウクラスの名前
		WINDOW_NAME,					//ウインドウの名前
		WS_OVERLAPPEDWINDOW,			//ウインドウスタイル
		CW_USEDEFAULT,					//ウインドウの左上X座標
		CW_USEDEFAULT,					//    //      左上Y座標
		SCREEN_WIDTH,					//    //      幅
		SCREEN_HEIGHT,					//    //      高さ
		NULL,							//親ウインドウのハンドル
		NULL,							//メニューハンドルまたは子ウインドウID
		hInstance,						//インスタンスハンドル
		NULL);							//ウインドウ作成データ

	CManager *pManager = NULL;
	// レンダラーの生成
	if (pManager != NULL)
	{
		// レンダラーの開放
		delete pManager;
		pManager = NULL;
	}
	pManager = new CManager;	// レンダラーのインスタンス生成

	//初期化設定
	if (FAILED(pManager->Init(hInstance,hWnd, TRUE)))
	{//初期化処理が失敗した場合

		return -1;

	}

	//ウインドウの表示
	ShowWindow(hWnd, nCmdshow);			//ウインドウの表示状態を設定
	UpdateWindow(hWnd);					//クライアント領域を更新

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);			//仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);			//ウインドウプロシージャへメッセージを放出
			}
		}
		else
		{//DirectXの処理
			//更新処理
			pManager->Update();

			//描画処理
			pManager->Draw();
		
		}
	}
	// レンダラーの終了
	if (pManager != NULL)
	{
		// レンダラーの開放
		pManager->Uninit();
		delete pManager;
		pManager = NULL;
	}

	//ウインドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//ウインドウプロシージャ
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static POINT pos = { 300,300 };		//線分の始点(X座標・Y座標)
	static POINT move = { 1,1 };		//線分の始点の移動量(X方向・Y方向)
	const RECT rect = { 0,0,SCREEN_WIDTH , SCREEN_HEIGHT };		//ウインドウの領域(たんけい)
	char aString[256] = "test";			//描画するテキストを格納
	int nData = 0,nData1 = 0;


	switch (uMsg)
	{
	case WM_KEYDOWN:					//キー押下のメッセージ

		switch (wParam)
		{
		case VK_ESCAPE:					//[ESC]キーが押された

			//ウインドウを破棄する(WM_DESTROYメッセージ)
			DestroyWindow(hWnd);
			break;

		}
		break;


	case WM_DESTROY:					//ウインドウ破棄のメッセージ
		//WM_QUITメッセージを送る
		PostQuitMessage(0);				
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);		//既定の処理を返す
}
