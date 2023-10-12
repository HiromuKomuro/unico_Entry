//====================================================================
//
//�t�F�[�h����[Fade.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"Fade.h"
#include"renderer.h"

// �ÓI�����o�ϐ�
LPDIRECT3DVERTEXBUFFER9 CFade::s_pVtxBuff = NULL;
//========================================
// �R���X�g���N�^
//========================================
CFade::CFade()
{
	m_fade = FADE_NONE;										// �t�F�[�h��Ԃ�
	m_modeNext = CScene::MODE_TITLE;						// ���̉��(���[�h)�ɐݒ�
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		// �����|���S��(�s����)�ɂ��Ă���
}
//========================================
// �f�X�g���N�^
//========================================
CFade::~CFade()
{

}
//========================================
// ����������
//========================================
HRESULT CFade::Init(CScene::MODE modeNext)
{
	m_modeNext = modeNext;	//���̉��(���[�h)�ɐݒ�

	CRenderer *pRenderer = CManager::GetRenderer();

	//���_�o�b�t�@�̓ǂݍ���
	if (FAILED(pRenderer->GetDevice()
		->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&s_pVtxBuff,
			NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D*pVtx;				//���_����

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̍��W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 00.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 00.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);


	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;


	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);


	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuff->Unlock();

	//���[�h�̐ݒ�
	Set(m_modeNext);

	return S_OK;
}
//========================================
//�t�F�[�h�̏I������
//========================================
void CFade::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (s_pVtxBuff != NULL)
	{
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;

	}
}
//=======================================
//�t�F�[�h�̍X�V����
//=======================================
void CFade::Update(void)
{
	VERTEX_2D*pVtx;				//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{//�t�F�[�h�C����Ԃ̎�
			m_colorFade.a -= 0.05f;			//�|���S���𓧖��ɂ��Ă���

			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;
				m_fade = FADE_NONE;			//�������Ă��Ȃ���Ԃ�

			}
		}
		else if (m_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g���
			m_colorFade.a += 0.05f;			//�|���S����s�����ɂ��Ă���

			if (m_colorFade.a >= 1.0f)
			{
				m_colorFade.a = 1.0f;
				m_fade = FADE_IN;			//�t�F�[�h�C����Ԃ�

				//���[�h�ݒ�(���̉�ʂɈڍs)
				CManager::SetMode(m_modeNext);
			}
		}
	
	}
	
	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colorFade.a);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colorFade.a);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colorFade.a);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colorFade.a);

	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuff->Unlock();
}

//======================================
//�t�F�[�h�̕`�揈��
//======================================
void CFade::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

	//���_�o�b�t�@�̃f�[�^�X�g���[���ɐݒ�
	pRenderer->GetDevice()->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g
	pRenderer->GetDevice()->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pRenderer->GetDevice()->SetTexture(0, NULL);		//�e�N�X�`�����g��Ȃ�(NULL)�ɂ���

	//�|���S���̕`��
	pRenderer->GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}
//=======================================
//�t�F�[�h�̐ݒ菈��
//=======================================
void CFade::Set(CScene::MODE modeNext)
{
	m_fade = FADE_OUT;				//�t�F�[�h�A�E�g��Ԃ�

	m_modeNext = modeNext;			//���̉��(���[�h)��ݒ�

	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�����|���S��(����)�ɂ��Ă���

}
