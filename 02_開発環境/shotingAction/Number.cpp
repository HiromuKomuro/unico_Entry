// =======================================================
//
// �i���o�[����(Number.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include "Number.h"
#include"main.h"
#include"renderer.h"
#include"Manager.h"
#include"input.h"
#include"Texture.h"

//====================================
// �R���X�g���N�^
//====================================
CNumber::CNumber()
{
	// �p�����[�^�[������
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;
	m_nIdxTexture = 0;
}
//====================================
// �f�X�g���N�^
//====================================
CNumber::~CNumber()
{
}
//====================================
// ����������
//====================================
HRESULT CNumber::Init(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	CTexture*pTexture = CManager::GetCTexture();

	// �e�N�X�`���̓ǂݍ���
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\number002.png");

	//���_�o�b�t�@�̓ǂݍ���
	if (FAILED(pRenderer->GetDevice()
		->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&m_pVtxBuff,
			NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D*pVtx;				//���_����

	// �Ίp���̒������Z�o����
	float fLength = sqrtf(m_fWidth * m_fWidth + m_fHeight * m_fHeight);

	// �Ίp���̊p�x���Z�o����
	float fAngle = atan2f(m_fWidth, m_fHeight);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̍��W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (D3DX_PI + fAngle)) * fLength, m_pos.y + cosf(m_rot.z + (D3DX_PI + fAngle)) * fLength, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (D3DX_PI - fAngle)) * fLength, m_pos.y + cosf(m_rot.z + (D3DX_PI - fAngle)) * fLength, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z - fAngle) * fLength, m_pos.y + cosf(m_rot.z - fAngle) * fLength, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + fAngle) * fLength, m_pos.y + cosf(m_rot.z + fAngle) * fLength, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�e�N�X�`���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}
//======================================
// �I������
//=====================================
void CNumber::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CObject::Relese();
}
//======================================
// �X�V����
//======================================
void CNumber::Update(void)
{
	VERTEX_2D*pVtx;				//���_����

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �Ίp���̒������Z�o����
	float fLength = sqrtf(m_fWidth * m_fWidth + m_fHeight * m_fHeight);

	// �Ίp���̊p�x���Z�o����
	float fAngle = atan2f(m_fWidth, m_fHeight);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̍��W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (D3DX_PI + fAngle)) * fLength, m_pos.y + cosf(m_rot.z + (D3DX_PI + fAngle)) * fLength, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (D3DX_PI - fAngle)) * fLength, m_pos.y + cosf(m_rot.z + (D3DX_PI - fAngle)) * fLength, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z - fAngle) * fLength, m_pos.y + cosf(m_rot.z - fAngle) * fLength, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + fAngle) * fLength, m_pos.y + cosf(m_rot.z + fAngle) * fLength, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//======================================
// �`�揈��
//======================================
void CNumber::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	CTexture*pTexture = CManager::GetCTexture();

	//���_�t�H�[�}�b�g
	pRenderer->GetDevice()->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@�̃f�[�^�X�g���[���ɐݒ�
	pRenderer->GetDevice()->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//�e�N�X�`���̐ݒ�
	pRenderer->GetDevice()->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//�|���S���̕`��
	pRenderer->GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

}
//======================================
// �F�̐ݒ�
//======================================
void CNumber::SetCol(const D3DCOLOR col)
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
// �e�N�X�`���̐ݒ�
//======================================
void CNumber::SetAnimeTex(float Max_Conter, int m_nAnimeCounter)
{
	VERTEX_2D*pVtx;				//���_����

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
void CNumber::SetAddTex(float fTex)
{
	VERTEX_2D*pVtx;				//���_����

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
// �傫���̐ݒ�
//======================================
void CNumber::SetScale(float fHeight, float fWidth)
{ 
	// ���
	m_fHeight = fHeight;
	m_fWidth = fWidth;

	// �X�V����
	CNumber::Update();
}