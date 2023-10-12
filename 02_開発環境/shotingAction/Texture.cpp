//= == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == =
//
// �e�N�X�`���̏���[Texture.h]
// author KOMURO HIROMU
//
//====================================================================
#include"Texture.h"
#include"Manager.h"
#include"renderer.h"

// �ÓI�����o�ϐ�
int CTexture::m_nNumAll = 0;

//========================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//========================================
CTexture::~CTexture()
{
}
//======================================
// �e�N�X�`���̐�������
//======================================
HRESULT CTexture::Load(void)
{
	CRenderer*pRenderer = CManager::GetRenderer();

	//�e�N�X�`���̓ǂݍ���
	Regist("data\\TEXTURE\\runningman000.png");
	Regist("data//TEXTURE//explosion000.png");
	Regist("data//TEXTURE//effect000.jpg");
	Regist("data//block000.jpg");

	return S_OK;
}
//======================================
// �e�N�X�`���̔j������
//======================================
void CTexture::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < m_nNumAll; nCnt++)
	{
		// �e�N�X�`���p�X�̔j��
		if (m_pFilenameOld[nCnt] != NULL)
		{
			delete m_pFilenameOld[nCnt];
			m_pFilenameOld[nCnt] = NULL; 
		}
	}
	m_nNumAll = 0;
}
//======================================
// �w��e�N�X�`���̓ǂݍ��ݏ���
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
			{// ������̔�r
				return nTexId;
			}
		}
	}

	if (m_pFilenameOld[nTexId] == NULL)
	{
		m_nNumAll++;

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pRenderer->GetDevice(), pFilename, &m_apTexture[nTexId]);

		m_pFilenameOld[nTexId] = new char[(int)strlen(pFilename) + 1];

		strcpy(m_pFilenameOld[nTexId],  pFilename);	// �t�@�C�����̕ۑ�
	}

	return nTexId;
}
//======================================
// �A�h���X�̓��菈��
//======================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	if(nIdx == NULL)
	{
		return NULL;
	}
	return m_apTexture[nIdx];

}