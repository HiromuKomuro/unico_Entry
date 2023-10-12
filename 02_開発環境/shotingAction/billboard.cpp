//====================================================================
//
//�r���{�[�h����[Billboard.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"Billboard.h"
#include"input.h"
#include"Manager.h"
#include"renderer.h"
#include"Texture.h"

//�}�N����`
#define Billboard_MOVE			(1.5)
#define Billboard_WIDTH			(200)
#define Billboard_DEPTH			(200)
#define Billboard_HEIGHT		(200)

//========================================
// �R���X�g���N�^
//========================================
CObjectBillboard::CObjectBillboard()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
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
CObjectBillboard::~CObjectBillboard()
{
}
//========================================
//�r���{�[�h�̏���������
//========================================
HRESULT CObjectBillboard::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^
	CTexture*pTexture = CManager::GetCTexture();

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̓ǂݍ���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);
	VERTEX_3D*pVtx;				//���_���ւ̃|�C���^�\


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̍��W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, m_fDepth, m_fHeight);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, m_fDepth, m_fHeight);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, -m_fDepth, -m_fHeight);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, -m_fDepth, -m_fHeight);
												 
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

	return S_OK;
}
//========================================
//�r���{�[�h�̏I������
//========================================
void CObjectBillboard::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	// �e�N�X�`���̔j��}
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	CObject::Relese();
}
//=======================================
//�r���{�[�h�̍X�V����
//=======================================
void CObjectBillboard::Update(void)
{
}
//======================================
//�r���{�[�h�̕`�揈��
//======================================
void CObjectBillboard::Draw(void)
{
	CTexture*pTexture = CManager::GetCTexture();

	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;		//�r���[�}�g���b�N�X�擾�p


	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����Ɍ�����
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);		//�t�s������߂�
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Z�e�X�g�𖳌��ɂ���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

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
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//�����_�\�X�e�[�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	//�����_�\�X�e�[�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}
//======================================
// �ݒ菈��
//======================================
CObjectBillboard *CObjectBillboard::Create(void)
{
	CObjectBillboard *pObjectBillboard;

	// �I�u�W�F�N�g3D�̐���
	pObjectBillboard = new CObjectBillboard();

	// ����������
	pObjectBillboard->Init();

	return pObjectBillboard;
}
//======================================
// �F�̐ݒ�
//======================================
void CObjectBillboard::SetCol(const D3DCOLOR col)
{
	m_col = col;
	VERTEX_3D*pVtx;				//���_����

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
// �e�N�X�`���̐ݒ�
//======================================
void CObjectBillboard::SetAnimeTex(float Max_Conter, int m_nAnimeCounter)
{
	VERTEX_3D*pVtx;				//���_����

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + (m_nAnimeCounter * (1.0f / Max_Conter)), 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1.0f / Max_Conter) + (m_nAnimeCounter * (1.0f / Max_Conter)), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (m_nAnimeCounter * (1.0f / Max_Conter)), 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1.0f / Max_Conter) + (m_nAnimeCounter * (1.0f / Max_Conter)), 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//======================================
// �e�N�X�`���̉��Z����
//======================================
void CObjectBillboard::SetAddTex(float fTex)
{
	VERTEX_3D*pVtx;				//���_����

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̍X�V
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + fTex);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + fTex);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f + fTex);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f + fTex);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//======================================
// �e�N�X�`���̊��蓖��
//======================================
void CObjectBillboard::BindTexture(int pTexture)
{
	m_nIdxTexture = pTexture;
}
//======================================
// �傫���̐ݒ�
//======================================
void CObjectBillboard::SetScale(float fWidth, float fHeight)
{
	// ���
	m_fHeight = fHeight;
	m_fWidth = fWidth;
	m_fDepth = fHeight;
}