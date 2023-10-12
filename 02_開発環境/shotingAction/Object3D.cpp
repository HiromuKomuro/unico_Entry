//====================================================================
//
//3D�I�u�W�F�N�g����[Object3D.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"Object3D.h"
#include"renderer.h"
#include"Manager.h"

// �}�N����`
#define OBJECT_WIDTH	(200)	// ����
#define OBJECT_HEIGHT	(200)	// �c��
#define MAX_IDX			(19)	// �C���f�b�N�X�̑���
//========================================
// �R���X�g���N�^
//========================================
CObject3D::CObject3D()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_fDepth = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
}
//========================================
// �f�X�g���N�^
//========================================
CObject3D::~CObject3D()
{
}
//========================================
// ����������
//========================================
HRESULT CObject3D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data//block000.jpg", &m_pTexture);
	

	//���_�o�b�t�@�̓ǂݍ���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_IDX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);
	VERTEX_3D*pVtx;				//���_���ւ̃|�C���^�\


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̍��W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, m_fHeight, m_fDepth);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, m_fHeight, m_fDepth);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, m_fHeight, -m_fDepth);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, m_fHeight, -m_fDepth);

	pVtx[4].pos = D3DXVECTOR3(-m_fWidth, -m_fHeight, -m_fDepth);
	pVtx[5].pos = D3DXVECTOR3(m_fWidth, -m_fHeight, -m_fDepth);

	pVtx[6].pos = D3DXVECTOR3(m_fWidth, -m_fHeight, m_fDepth);

	pVtx[7].pos = D3DXVECTOR3(-m_fWidth, -m_fHeight, m_fDepth);

	pVtx[8].pos = D3DXVECTOR3(-m_fWidth, -m_fHeight, m_fDepth);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;
	pVtx[4].col = m_col;
	pVtx[5].col = m_col;
	pVtx[6].col = m_col;
	pVtx[7].col = m_col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);
	WORD*pIdx;				//�C���f�b�N�X���̃|�C���^

	//�C���f�b�N�X�����b�N���A���_���f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//���_�ԍ��f�[�^�̐ݒ�
	pIdx[0] = 0;
	pIdx[1] = 1;
	pIdx[2] = 2;
	pIdx[3] = 3;
	pIdx[4] = 4;
	pIdx[5] = 5;
	pIdx[6] = 3;
	pIdx[7] = 6;
	pIdx[8] = 1;
	pIdx[9] = 7;
	pIdx[10] = 8;
	pIdx[11] = 2;
	pIdx[12] = 8;
	pIdx[13] = 5;

	//���_�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();

	return S_OK;

}
//========================================
// �I������
//========================================
void CObject3D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}
//=======================================
// �X�V����
//=======================================
void CObject3D::Update(void)
{
	VERTEX_3D*pVtx;				//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̍��W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, m_fHeight, m_fDepth);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, m_fHeight, m_fDepth);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, -m_fHeight, -m_fDepth);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, -m_fHeight, -m_fDepth);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//======================================
// �`�揈��
//======================================
void CObject3D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_LINESTRIP,	// ����Ő��̕`��
				0,
				4);							// ���̐�
}
//======================================
// �ݒ菈��
//======================================
CObject3D *CObject3D::Create(void)
{
	CObject3D *pObject3D;

	// �I�u�W�F�N�g3D�̐���
	pObject3D = new CObject3D();

	// ����������
	pObject3D->Init();

	return pObject3D;
}
//======================================
// �F�̐ݒ�
//======================================
void CObject3D::SetCol(const D3DCOLOR col)
{
	m_col = col;
	VERTEX_2D*pVtx;				//���_����

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}
//======================================
// �傫���̐ݒ�
//======================================
void CObject3D::SetScale(float fWidth, float fHeight,float fDepth)
{
	// ���
	m_fHeight = fHeight;
	m_fWidth = fWidth;
	m_fDepth = fDepth;

	// �X�V����
	CObject3D::Update();
}
//======================================
// �e�N�X�`���̊��蓖��
//======================================
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}