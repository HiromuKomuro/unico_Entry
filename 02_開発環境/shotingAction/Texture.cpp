//= == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == =
//
// テクスチャの処理[Texture.h]
// author KOMURO HIROMU
//
//====================================================================
#include"Texture.h"
#include"Manager.h"
#include"renderer.h"

// 静的メンバ変数
int CTexture::m_nNumAll = 0;

//========================================
// コンストラクタ
//========================================
CTexture::CTexture()
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		m_apTexture[nCnt] = NULL;
		m_pFilenameOld[nCnt] = NULL;
	}
	
}
//========================================
// デストラクタ
//========================================
CTexture::~CTexture()
{
}
//======================================
// テクスチャの生成処理
//======================================
HRESULT CTexture::Load(void)
{
	CRenderer*pRenderer = CManager::GetRenderer();

	//テクスチャの読み込み
	Regist("data\\TEXTURE\\runningman000.png");
	Regist("data//TEXTURE//explosion000.png");
	Regist("data//TEXTURE//effect000.jpg");
	Regist("data//block000.jpg");

	return S_OK;
}
//======================================
// テクスチャの破棄処理
//======================================
void CTexture::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		// テクスチャの破棄
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < m_nNumAll; nCnt++)
	{
		// テクスチャパスの破棄
		if (m_pFilenameOld[nCnt] != NULL)
		{
			delete m_pFilenameOld[nCnt];
			m_pFilenameOld[nCnt] = NULL; 
		}
	}
	m_nNumAll = 0;
}
//======================================
// 指定テクスチャの読み込み処理
//======================================
int CTexture::Regist(char* pFilename)
{
	CRenderer*pRenderer = CManager::GetRenderer();
	int nTexId = 0;

	for (nTexId = 0; nTexId < m_nNumAll; nTexId++)
	{
		if (m_pFilenameOld[nTexId] != NULL)
		{
			if (strcmp(m_pFilenameOld[nTexId], pFilename) == 0)
			{// 文字列の比較
				return nTexId;
			}
		}
	}

	if (m_pFilenameOld[nTexId] == NULL)
	{
		m_nNumAll++;

		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pRenderer->GetDevice(), pFilename, &m_apTexture[nTexId]);

		m_pFilenameOld[nTexId] = new char[(int)strlen(pFilename) + 1];

		strcpy(m_pFilenameOld[nTexId],  pFilename);	// ファイル名の保存
	}

	return nTexId;
}
//======================================
// アドレスの入手処理
//======================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	if(nIdx == NULL)
	{
		return NULL;
	}
	return m_apTexture[nIdx];

}