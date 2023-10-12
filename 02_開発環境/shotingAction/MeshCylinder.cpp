//====================================================================
//
//���b�V���V�����_�[����[MeshCylinder.h]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"MeshCylinder.h"
#include"renderer.h"
#include"Manager.h"
#include"Object.h"
#include"input.h"
#include"Texture.h"

// �}�N����`
#define MAX_BUFF		(14)		// �ő�̒��_�o�b�t�@
#define OBJECT_WIDTH	(100)		// ����
#define OBJECT_HEIGHT	(200)		// �c��
#define OBJECT_DEPTH	(2000)		// ����
#define MAGNI			(1.5f)		// �p�x
#define MAGNIFICATION	(7.0f)		// �g�嗦
#define MAX_IDX			(16)		// �C���f�b�N�X�̑���
//========================================
// �R���X�g���N�^
//========================================
CMeshClynder::CMeshClynder()
{
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DCOLOR_RGBA(255, 255, 0, 255);
	m_fDepth = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_nIdxTexture = 0;
	CObject::SetType(TYPE_MESHFILED);	// ��ނ̐ݒ�
}
//========================================
// �f�X�g���N�^
//========================================
CMeshClynder::~CMeshClynder()
{
}
//========================================
// ����������
//========================================
HRESULT CMeshClynder::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^
	CTexture*pTexture = CManager::GetCTexture();

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\wood_001.png");

	//���_�o�b�t�@�̓ǂݍ���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_BUFF,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);
	VERTEX_3D*pVtx;				//���_���ւ̃|�C���^�\


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̍��W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(OBJECT_WIDTH * MAGNIFICATION, -100.0f, OBJECT_DEPTH * MAGNIFICATION);
	pVtx[1].pos = D3DXVECTOR3(-OBJECT_WIDTH * MAGNIFICATION, -100.0f, OBJECT_DEPTH * MAGNIFICATION);
	pVtx[2].pos = D3DXVECTOR3(-OBJECT_WIDTH * MAGNI * MAGNIFICATION, 100.0f * MAGNIFICATION, OBJECT_DEPTH * MAGNIFICATION);
	pVtx[3].pos = D3DXVECTOR3(-OBJECT_WIDTH * MAGNIFICATION, 200.0f * MAGNIFICATION, OBJECT_DEPTH * MAGNIFICATION);
	pVtx[4].pos = D3DXVECTOR3(0.0f, 250.0f * MAGNIFICATION, OBJECT_DEPTH * MAGNIFICATION);
	pVtx[5].pos = D3DXVECTOR3(OBJECT_WIDTH * MAGNIFICATION, 200.0f * MAGNIFICATION, OBJECT_DEPTH * MAGNIFICATION);
	pVtx[6].pos = D3DXVECTOR3(OBJECT_WIDTH * MAGNI * MAGNIFICATION, 100.0f * MAGNIFICATION, OBJECT_DEPTH * MAGNIFICATION);

	pVtx[7].pos  = D3DXVECTOR3(OBJECT_WIDTH * MAGNIFICATION, -100.0f, -OBJECT_DEPTH * MAGNIFICATION);
	pVtx[8].pos  = D3DXVECTOR3(-OBJECT_WIDTH * MAGNIFICATION, -100.0f, -OBJECT_DEPTH * MAGNIFICATION);
	pVtx[9].pos  = D3DXVECTOR3(-OBJECT_WIDTH * MAGNI * MAGNIFICATION, 100.0f * MAGNIFICATION, -OBJECT_DEPTH * MAGNIFICATION);
	pVtx[10].pos = D3DXVECTOR3(-OBJECT_WIDTH * MAGNIFICATION, 200.0f * MAGNIFICATION, -OBJECT_DEPTH * MAGNIFICATION);
	pVtx[11].pos = D3DXVECTOR3(0.0f, 250.0f * MAGNIFICATION, -OBJECT_DEPTH * MAGNIFICATION);
	pVtx[12].pos = D3DXVECTOR3(OBJECT_WIDTH * MAGNIFICATION, 200.0f * MAGNIFICATION, -OBJECT_DEPTH * MAGNIFICATION);
	pVtx[13].pos = D3DXVECTOR3(OBJECT_WIDTH * MAGNI * MAGNIFICATION, 100.0f * MAGNIFICATION, -OBJECT_DEPTH * MAGNIFICATION);


	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[9].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[10].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[11].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[12].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[13].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;
	pVtx[4].col = m_col;
	pVtx[5].col = m_col;
	pVtx[6].col = m_col;
	pVtx[7].col = m_col;
	pVtx[8].col = m_col;
	pVtx[9].col = m_col;
	pVtx[10].col = m_col;
	pVtx[11].col = m_col;
	pVtx[12].col = m_col;
	pVtx[13].col = m_col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.142f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.142f * 2.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.142f * 3.0f, 0.0f);
	pVtx[4].tex = D3DXVECTOR2(0.142f * 4.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(0.142f * 5.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(1.0f, 0.0f);
	
	pVtx[7].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(0.142f, 1.0f);
	pVtx[9].tex = D3DXVECTOR2(0.142f * 2.0f, 1.0f);
	pVtx[10].tex = D3DXVECTOR2(0.142f * 3.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(0.142f * 4.0f, 1.0f);
	pVtx[12].tex = D3DXVECTOR2(0.142f * 5.0f, 1.0f);
	pVtx[13].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_IDX,
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
	pIdx[1] = 7;
	pIdx[2] = 1;
	pIdx[3] = 8;
	pIdx[4] = 2;
	pIdx[5] = 9;
	pIdx[6] = 3;
	pIdx[7] = 10;
	pIdx[8] = 4;
	pIdx[9] = 11;
	pIdx[10] = 5;
	pIdx[11] = 12;
	pIdx[12] = 6;
	pIdx[13] = 13;
	pIdx[14] = 0;
	pIdx[15] = 7;

	
	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();

	return S_OK;

}
//========================================
// �I������
//========================================
void CMeshClynder::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	// �C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}


	CObject::Relese();
}
//=======================================
// �X�V����
//=======================================
void CMeshClynder::Update(void)
{
}

//======================================
// �`�揈��
//======================================
void CMeshClynder::Draw(void)
{
	CTexture*pTexture = CManager::GetCTexture();

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

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
				0,
				0,
				MAX_BUFF,
				0,
		MAX_IDX * 2);
}
//======================================
// �ݒ菈��
//======================================
CMeshClynder *CMeshClynder::Create(void)
{
	CMeshClynder *pObject3D;

	// �I�u�W�F�N�g3D�̐���
	pObject3D = new CMeshClynder();

	// ����������
	pObject3D->Init();

	return pObject3D;
}
//======================================
// �����蔻�菈��
//======================================
bool CMeshClynder::Collision(D3DXVECTOR3 pos)
{
	bool bColli = false;

	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		CObject *pObj = CObject::GetTop(nCntPri);	// �擪�̃I�u�W�F�N�g����

		while (pObj != NULL)
		{
			CObject *pObjectNext = pObj->GetNext();	// ���̃I�u�W�F�N�g��ۑ�

			//��ނ��擾
			TYPE type = pObj->GetType();

			if (type == TYPE_MESHFILED)
			{
				CMeshClynder *pMeshClynder = dynamic_cast<CMeshClynder*>(pObj);

				// �ϊ�������̈ʒu
				D3DXVECTOR3 Meshpos;
				Meshpos.x = pMeshClynder->Getmtx()._41;
				Meshpos.y = pMeshClynder->Getmtx()._42;
				Meshpos.z = pMeshClynder->Getmtx()._43;

				//���݁E�O��̈ʒu�ƃt�B�[���h�̒��S�ʒu�̍����i�[
				D3DXVECTOR2 PosDiff;

				PosDiff.x = powf(pos.x - Meshpos.x, 2.0f);    //���݂̂w���W�̍��̂Q��
				PosDiff.y = powf(pos.y - Meshpos.y, 2.0f);    //���݂̂y���W�̍��̂Q��    �ϐ���  "�x" �����ǁA�y���W�̍������܂� 

				float fLength = sqrtf(PosDiff.x + PosDiff.y);    //���݂̂w�E�y�̒������擾

				if (fLength >= 750.0f / 2.0f)
				{//���S�ʒu����̋������t�B�[���h�̔��a�ȏゾ����

					//bColli = true;
				}

				if (Meshpos.z + OBJECT_DEPTH * MAGNIFICATION <= pos.z)
				{
					bColli = true;
				}
			}
			pObj = pObjectNext;		// ���̃I�u�W�F�N�g����
		}
	}
	return bColli;
}