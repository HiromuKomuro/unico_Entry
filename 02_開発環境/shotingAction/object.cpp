// =======================================================
//
// オブジェクト処理(object.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include "object.h"
#include"main.h"
#include"renderer.h"
#include"Camera.h"
#include"Manager.h"

// 静的メンバ変数宣言
CObject *CObject::m_pTop[PRIORITY_MAX] = {};
CObject *CObject::m_pCur[PRIORITY_MAX] = {};

//====================================
// コンストラクタ
//====================================
CObject::CObject(int nPriority)
{
	if (m_pTop[nPriority] == NULL)
	{// 先頭のアドレスが使われていないとき

		m_pTop[nPriority] = this;				// 先頭のアドレスに自身を代入

		// 次と前のオブジェクトをNULLにする
		this->m_pNext = NULL;
		this->m_pPrev = NULL;
	}
	else
	{// 先頭のアドレスが存在するとき

		this->m_pPrev = m_pCur[nPriority];			// 先頭のアドレスを前のアドレスに代入

		m_pCur[nPriority]->m_pNext = this;			// 前のアドレスの次のアドレスを自身に代入

		// 次のオブジェクトのアドレスをNULLにする
		this->m_pNext = NULL;

	}

	m_pCur[nPriority] = this;		// 最後尾のアドレスに自身を代入

	m_nPriority = nPriority;		// 描画の優先度を設定
	m_bDeath = false;	// 死亡フラグの初期化

}
//====================================
// デストラクタ
//====================================
CObject::~CObject()
{
}
//====================================
// 全オブジェクトの終了処理
//====================================
void CObject::ReleseAll(void)
{
	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		CObject*pObject = m_pTop[nCntPri];	// 先頭のオブジェクトを代入

		while (pObject != NULL)
		{
			CObject*pObjectNext = pObject->m_pNext;		// 次のオブジェクトを保存

			pObject->Uninit();

			// 削除処理
			pObject->Delete(nCntPri);

			pObject = pObjectNext;	// 次のオブジェクトを代入
		}
	}
}
//====================================
// 全オブジェクトの更新処理
//====================================
void CObject::UpdateAll(void)
{
	CCamera*pCamera = CManager::GetCCamera();
	
	pCamera->Update();	// カメラの更新処理

	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		CObject*pObject = m_pTop[nCntPri];	// 先頭のオブジェクトを代入

		while (pObject != NULL)
		{
			CObject*pObjectNext = pObject->m_pNext;		// 次のオブジェクトを保存

			// 更新処理
			if (!pObject->m_bDeath)
				pObject->Update();

			pObject = pObjectNext;	// 次のオブジェクトを代入
		}
	}

	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		CObject*pObject = m_pTop[nCntPri];	// 先頭のオブジェクトを代入

		while (pObject != NULL)
		{
			CObject*pObjectNext = pObject->m_pNext;		// 次のオブジェクトを保存

			// 削除処理
			pObject->Delete(nCntPri);

			pObject = pObjectNext;	// 次のオブジェクトを代入
		}
	}
}
//====================================
// 全オブジェクトの描画処理
//====================================
void CObject::DrawAll(void)
{
	CCamera*pCamera = CManager::GetCCamera();

	pCamera->SetCamera();	// カメラの設定

	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		CObject*pObject = m_pTop[nCntPri];	// 先頭のオブジェクトを代入

		while (pObject != NULL)
		{
			CObject*pObjectNext = pObject->m_pNext;		// 次のオブジェクトを保存

			// 描画処理
			pObject->Draw();

			pObject = pObjectNext;	// 次のオブジェクトを代入
		
		}
	}

}
//====================================
// オブジェクトの破棄処理
//====================================
void CObject::Relese(void)
{
	m_bDeath = true;	// 死亡フラグを有効にする
}
//====================================
// オブジェクトの削除処理
//====================================
void CObject::Delete(int nPriority)
{
	if (m_bDeath == true)
	{// 死亡フラグが友好の時

		if (m_pPrev != NULL && m_pNext != NULL)
		{
			m_pNext->m_pPrev = m_pPrev;		// 自身の次のアドレスの前のアドレスを自身の前のアドレスに代入
			m_pPrev->m_pNext = m_pNext;
		}
		else if (m_pPrev == NULL && m_pNext != NULL)
		{
			m_pTop[nPriority]  = m_pNext;	// 先頭のアドレスにする
			m_pNext->m_pPrev = NULL;
		}
		else if (m_pNext == NULL && m_pPrev != NULL)
		{
			m_pCur[nPriority] = m_pPrev;
			m_pPrev->m_pNext = NULL;
		}
		else
		{
			m_pTop[nPriority] = NULL;
			m_pCur[nPriority] = NULL;
		}
	
		// インスタンスの開放
		delete this;

	}
}