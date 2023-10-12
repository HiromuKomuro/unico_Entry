//====================================================================
//
//���f������[Model.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"Model.h"
#include"input.h"
#include"Bullet.h"
#include"Camera.h"
#include"Manager.h"
#include"renderer.h"
#include"sound.h"
#include"Texture.h"

//�}�N����`
#define MODEL_MOVE			(3)

//========================================
// �R���X�g���N�^
//========================================
CXModel::CXModel()
{
	m_pMesh = NULL;
	m_pTexture = NULL;
	m_dwNumMat = NULL;
	m_pBuffMat = NULL;
	m_pVertex = NULL;
	m_SizeFVF = NULL;
	m_pPos = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nIdxMode = -1;
	m_nIdxModelParent = 0;
	CObject::SetType(TYPE_XMODEL);	// ��ނ�ݒ�
	m_nIdxTexture = NULL;
}
//========================================
// �f�X�g���N�^
//========================================
CXModel::~CXModel()
{
}
//========================================
//���f���̏���������
//========================================
HRESULT CXModel::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^
	CTexture*pTexture = CManager::GetCTexture();
	D3DXVECTOR3 pos;

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATERIAL *pMat;			//�}�e���A���ւ̃|�C���^

	//m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_dwNumMat];
	m_nIdxTexture = new int[(int)m_dwNumMat];

	//�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂���

		 //�e�N�X�`���̓ǂݍ���
			//D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_pTexture[nCntMat]);
			m_nIdxTexture[nCntMat] = pTexture->Regist(pMat[nCntMat].pTextureFilename);
		}
		else
		{
			m_nIdxTexture[nCntMat] = NULL;
		}
	}

	//�e��ݒ�

	return S_OK;
}
//========================================
//���f���̏I������
//========================================
void CXModel::Uninit(void)
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
void CXModel::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	if (pInputKeyboard->GetKeyboardTrigger(DIK_Q) == true)
	{
		m_rot.z += ROT_TRANS;
	}
	if (pInputKeyboard->GetKeyboardTrigger(DIK_E) == true)
	{
		m_rot.z -= ROT_TRANS;
	}
}
//======================================
//���f���̕`�揈��
//======================================
void CXModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^
	CTexture*pTexture = CManager::GetCTexture();
	D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f };

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//���f���̃T�C�Y��ύX
	D3DXMatrixScaling(&m_mtxWorld, m_Size.x, m_Size.y, m_Size.z);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//D3DXMatrixRotationAxis(&mtxRot, &pos, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

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

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
//======================================
// �ݒ菈��
//======================================
CXModel *CXModel::Create(const char* pFilename)
{
	CXModel *pModel;

	// �I�u�W�F�N�g3D�̐���
	pModel = new CXModel();

	// ���f���̐ݒ�
	pModel->BindModel(pFilename);

	// ����������
	pModel->Init();

	return pModel;
}

//======================================
// ���f���̐ݒ菈��
//======================================
void CXModel::BindModel(const char* pFilename)
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

	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVertex);

	int nNumVertices = m_pMesh->GetNumVertices();

	m_SizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	m_pPos = new D3DXVECTOR3[nNumVertices];

	for (int nCntVer = 0; nCntVer < nNumVertices; nCntVer++)
	{
		m_pPos[nCntVer] = *(D3DXVECTOR3*)m_pVertex;
		m_pVertex += m_SizeFVF;
		// ���_���̈ʒu���󂯎��

	}

}