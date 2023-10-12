//====================================================================
//
//���f������[Model.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"BlockX.h"
#include"input.h"
#include"Bullet.h"
#include"Camera.h"
#include"Manager.h"
#include"renderer.h"
#include"sound.h"
#include"Texture.h"
#include"throughWall.h"
#include"collisionline.h"
#include"game.h"

//========================================
// �R���X�g���N�^
//========================================
CBlockX::CBlockX()
{
	// ������
	m_Maxpos = { 0,0,0 }; m_Minpos = { 0,0,0 };

	m_fAngle = 0.0f;
	m_fLength = 0.0f;

	m_pMesh = NULL;
	m_dwNumMat = NULL;
	m_pBuffMat = NULL;
	m_pVertex = NULL;
	m_SizeFVF = NULL;
	m_pPos = NULL;
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_aParent = NULL;
	m_nIdxTexture = 0;
}
//========================================
// �f�X�g���N�^
//========================================
CBlockX::~CBlockX()
{
}
//========================================
// ����������
//========================================
HRESULT CBlockX::Init(const char* pFilename)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^
	CTexture*pTexture = CManager::GetCTexture();

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);
	
	D3DXMATERIAL *pMat;			//�}�e���A���ւ̃|�C���^

	m_nIdxTexture = new int[(int)m_dwNumMat];

	//�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂���
			m_nIdxTexture[nCntMat] = pTexture->Regist(pMat[nCntMat].pTextureFilename);
		}
	}

	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVertex);

	int nNumVertices = m_pMesh->GetNumVertices();

	m_SizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	m_pPos = new D3DXVECTOR3[nNumVertices];

	for (int nCntVer = 0; nCntVer < nNumVertices; nCntVer++)
	{
		m_pPos[nCntVer] = *(D3DXVECTOR3*)m_pVertex;
		m_pVertex += m_SizeFVF;
		// �����Œ��_���̈ʒu���󂯎���Ă�
		// ���Ƃ͈ʒu���̈�ԑ傫�����l����肵�ē����蔻��
	}
	return S_OK;
}
//========================================
// �I������
//========================================
void CBlockX::Uninit(void)
{
	// �C���X�^���X���J��
	if (m_nIdxTexture != NULL)
	{
		delete m_nIdxTexture;
		m_nIdxTexture = NULL;
	}
	if (m_pPos != NULL)
	{
		delete m_pPos;
		m_pPos = NULL;
	}

	//�e�N�X�`���̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}
//=======================================
// �X�V����
//=======================================
void CBlockX::Update(void)
{
}
//======================================
// �`�揈��
//======================================
void CBlockX::Draw(D3DXMATRIX mtxPar)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	CTexture*pTexture = CManager::GetCTexture();

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//���f���̃T�C�Y��ύX
	D3DXMatrixScaling(&m_mtxWorld, m_Size.x, m_Size.y, m_Size.z);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	
	//�}�e���A�����ɑ΂���|�C���^���擾
    pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	
	//�Z�o�����p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��	
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxPar);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (CGame::GetPause() != false)return;
			//�F�̐ݒ�
			pMat[nCntMat].MatD3D.Diffuse.r = m_col.r;
			pMat[nCntMat].MatD3D.Diffuse.g = m_col.g;
			pMat[nCntMat].MatD3D.Diffuse.b = m_col.b;
			pMat[nCntMat].MatD3D.Diffuse.a = m_col.a;

			//�}�e���A���̎擾
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTexture->GetAddress(*m_nIdxTexture));

			//���f��(�p�[�c)�̕`��
			m_pMesh->DrawSubset(nCntMat);
	}
}
//======================================
// �ݒ菈��
//======================================
CBlockX * CBlockX::Create(D3DXVECTOR3 pos, const char* pFilename,D3DXVECTOR3 Size)
{
	CBlockX *pModel;

	// �I�u�W�F�N�g3D�̐���
	pModel = new CBlockX();

	// �ʒu�̐ݒ�
	pModel->SetPos(pos);

	// �T�C�Y�̐ݒ�
	pModel->SetSize(Size);

	// ����������
	pModel->Init(pFilename);

	// �͂̌����̐ݒ�
	pModel->SetVector();

	return pModel;
}
//======================================
// �O�όv�Z�ɕK�v�ȗv�f�̐ݒ�
//======================================
void CBlockX::SetVector(void)
{
	D3DXVECTOR3 *posVertex = m_pPos;
	const int nNumVertices = m_pMesh->GetNumVertices();

	for (int nCntVer = 0; nCntVer < nNumVertices; nCntVer++)
	{
		// ���_���̍ő�,�ŏ������Ƃ�
		if (m_Maxpos.x < posVertex[nCntVer].x)
		{
			m_Maxpos.x = posVertex[nCntVer].x;
		}
		else if (m_Minpos.x > posVertex[nCntVer].x)
		{
			m_Minpos.x = posVertex[nCntVer].x;
		}
		if (m_Maxpos.y < posVertex[nCntVer].y)
		{
			m_Maxpos.y = posVertex[nCntVer].y;
		}
		else if (m_Minpos.y > posVertex[nCntVer].y)
		{
			m_Minpos.y = posVertex[nCntVer].y;
		}
		if (m_Maxpos.z < posVertex[nCntVer].z)
		{
			m_Maxpos.z = posVertex[nCntVer ].z;
		}
		else if (m_Minpos.z > posVertex[nCntVer].z)
		{
			m_Minpos.z = posVertex[nCntVer].z;
		}
	}

	// ���_���ɃT�C�Y������
	m_Maxpos.x *= m_Size.x;
	m_Minpos.x *= m_Size.x;
	m_Maxpos.y *= m_Size.y;
	m_Minpos.y *= m_Size.y;
	m_Maxpos.z *= m_Size.z;
	m_Minpos.z *= m_Size.z;

	//�Ίp���̒������Z�o����
	m_fLength = sqrtf(m_Maxpos.y * m_Maxpos.y + m_Maxpos.x * m_Maxpos.x);
	//�Ίp���̊p�x���Z�o����
	m_fAngle = atan2f(m_Maxpos.y, m_Maxpos.x);

}

