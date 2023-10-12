//====================================================================
//
//���f������[ObjectModel.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"ObjectModel.h"
#include"Player3D.h"
#include"Manager.h"
#include"renderer.h"
#include"Texture.h"


//========================================
// �R���X�g���N�^
//========================================
CObjectModel::CObjectModel()
{
	m_pMesh = NULL;
	m_dwNumMat = NULL;
	m_pBuffMat = NULL;
	m_pVertex = NULL;
	m_SizeFVF = NULL;
	m_pPos = NULL;
	m_state = STATE_NONE;
	m_Size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_aParent = NULL;
	m_nIdxTexture = 0;
	m_nDamgeCounter = 0;
}
//========================================
// �f�X�g���N�^
//========================================
CObjectModel::~CObjectModel()
{
}
//========================================
//���f���̏���������
//========================================
HRESULT CObjectModel::Init(const char* pFilename)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^
	CTexture*pTexture = CManager::GetCTexture();
	D3DXVECTOR3 pos;

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

		 ////�e�N�X�`���̓ǂݍ���
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
//���f���̏I������
//========================================
void CObjectModel::Uninit(void)
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
//���f���̍X�V����
//=======================================
void CObjectModel::Update(void)
{
	switch (m_state)
	{
	case STATE_NONE:
		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	case STATE_DAMAGE:
		m_nDamgeCounter++;
		m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		if (m_nDamgeCounter == 120)
		{
			m_state = STATE_NONE;
			m_nDamgeCounter = 0;
		}
		break;
	}
}
//======================================
//���f���̕`�揈��
//======================================
void CObjectModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxParent;			//�e�̃}�g���b�N�X

	CTexture*pTexture = CManager::GetCTexture();

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//���f���̃T�C�Y��ύX
	D3DXMatrixScaling(&m_mtxWorld, GetSize().x, GetSize().y, GetSize().z);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	if (m_aParent != NULL)
	{
		// �e���f���̃}�g���b�N�X���擾����
		mtxParent = m_aParent->m_mtxWorld;
	}
	else
	{
		// ���݂̃}�g���b�N�X���擾����
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);	
	}
	//�Z�o�����p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
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
// �e�̐ݒ菈��
//======================================
void CObjectModel::SetParent(CObjectModel *pObjectModel)
{
	m_aParent = pObjectModel;
}
//======================================
// �ݒ菈��
//======================================
CObjectModel *CObjectModel::Create(const char* pFilename, D3DXVECTOR3 pos)
{
	CObjectModel *pObjectModel;

	// �I�u�W�F�N�g3D�̐���
	pObjectModel = new CObjectModel();

	// ����������
	pObjectModel->Init(pFilename);
	
	pObjectModel->SetPos(pos);

	return pObjectModel;
}