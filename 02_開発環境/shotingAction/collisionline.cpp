//====================================================================
//
//�����蔻��̃��C������[collisionline.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"collisionline.h"
#include"renderer.h"
#include"Manager.h"
#include"BlockXbase.h"
#include"input.h"
#include"game.h"

// �ÓI�����o�ϐ�
int CCollisionLine::m_nNumLine = 0;
//========================================
// �R���X�g���N�^
//========================================
CCollisionLine::CCollisionLine()
{
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DCOLOR_RGBA(255, 0, 0, 255);
	m_size.z = 0.0f;
	m_size.x = 0.0f;
	m_size.y = 0.0f;
	m_nId = 0;
}
//========================================
// �f�X�g���N�^
//========================================
CCollisionLine::~CCollisionLine()
{
}
//========================================
// ����������
//========================================
HRESULT CCollisionLine::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̓ǂݍ���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 5,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);
	VERTEX_3D*pVtx;				//���_���ւ̃|�C���^�\


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̍��W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_size.x,m_size.y,m_size.z);
	pVtx[1].pos = D3DXVECTOR3(m_size.x,m_size.y,m_size.z);
	pVtx[2].pos = D3DXVECTOR3(m_size.x,-m_size.y,m_size.z);
	pVtx[3].pos = D3DXVECTOR3(-m_size.x,-m_size.y,m_size.z);
	pVtx[4].pos = D3DXVECTOR3(-m_size.x,+m_size.y,m_size.z);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;
	pVtx[4].col = m_col;


	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;

}
//========================================
// �I������
//========================================
void CCollisionLine::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CObject::Relese();
}
//=======================================
// �X�V����
//=======================================
void CCollisionLine::Update(void)
{
	VERTEX_3D*pVtx;				//���_���̃|�C���^
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		CObject *pObj = CObject::GetTop(nCntPri);	// �擪�̃I�u�W�F�N�g����

		while (pObj != NULL)
		{
			CObject *pObjectNext = pObj->GetNext();	// ���̃I�u�W�F�N�g��ۑ�

			//��ނ��擾
			TYPE type = pObj->GetType();

			if (type == TYPE_BLOCKBASE || type == TYPE_BREAKBLOCKBASE)
			{
				CBaseBlockX *pBlockbase = dynamic_cast<CBaseBlockX*>(pObj);
				if (type == TYPE_BREAKBLOCKBASE)
				{// ��ނ�����u���b�N�̎�
					CBreakBaseBlockX *pBlockbase = dynamic_cast<CBreakBaseBlockX*>(pObj);
				}
				
				if (m_nId == pBlockbase->GetId())
				{// ���ʔԍ����ꏏ�̎�
					// �ʒu�ƌ����̓���
					m_rot = pBlockbase->GetRot();
					m_pos.x = pBlockbase->GetBlock()->GetMtx()._41;
					m_pos.y = pBlockbase->GetBlock()->GetMtx()._42;
					m_pos.z = pBlockbase->GetBlock()->GetMtx()._43;
				}
			}
			pObj = pObjectNext;		// ���̃I�u�W�F�N�g����
		}
	}

	//���_���W�̍��W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, -m_size.z);
	pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, -m_size.z);
	pVtx[2].pos = D3DXVECTOR3(m_size.x, -m_size.y, -m_size.z);
	pVtx[3].pos = D3DXVECTOR3(-m_size.x, -m_size.y, -m_size.z);
	pVtx[4].pos = D3DXVECTOR3(-m_size.x, m_size.y, -m_size.z);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;
	pVtx[4].col = m_col;
	

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//======================================
// �`�揈��
//======================================
void CCollisionLine::Draw(void)
{
	if (CGame::GetPause() == false)
	{
		return;
	}
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


	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_LINESTRIP,	// ����Ő��̕`��
		0,
		4);							// ���̐�
}
//======================================
// �ݒ菈��
//======================================
CCollisionLine *CCollisionLine::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,int *nId)
{
	CCollisionLine *pCollisionLine;

	// �C���X�^���X�̐���
	pCollisionLine = new CCollisionLine();

	// �ʒu�̐ݒ�
 	pCollisionLine->SetPos(pos);

	// �T�C�Y�̐ݒ�
	pCollisionLine->SetSize(size);

	// ����������
	pCollisionLine->Init();

	// ���ʔԍ��̐ݒ�
	pCollisionLine->m_nId = *nId = m_nNumLine;

	// �����̍��v
	m_nNumLine++;

	return pCollisionLine;
}
//======================================
// �F�̐ݒ�
//======================================
void CCollisionLine::SetCol(const D3DCOLOR col)
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
