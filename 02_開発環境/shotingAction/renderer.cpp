// =======================================================
//
// �����_�����O����(renderer.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"renderer.h"
#include"main.h"
#include"object.h"
#include"Manager.h"
#include"Camera.h"
#include"Test.h"
//====================================
// �R���X�g���N�^
//====================================
CRenderer::CRenderer()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
}
//====================================
// �f�X�g���N�^
//====================================
CRenderer::~CRenderer()
{
}
//====================================
// ����������
//====================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	//�v���[���e�[�V�����p�����[�^

	//Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h������
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));		//�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;	//�Q�[����ʃT�C�Y�i���j

	d3dpp.BackBufferHeight = SCREEN_HEIGHT;	//�Q�[����ʃT�C�Y�i�����j

	d3dpp.BackBufferFormat = d3ddm.Format;	//�o�b�N�o�b�t�@�̌`��

	d3dpp.BackBufferCount = 1;				//�o�b�N�o�b�t�@�̐�

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//�_�u���o�b�t�@�̐؂�ւ��i�f���M���ɓ���)

	d3dpp.EnableAutoDepthStencil = TRUE;		//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬

	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//�f�v�X�o�b�t�@�Ƃ���16bit���g��

	d3dpp.Windowed = bWindow;					//�E�C���h�E���[�h

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//���t���b�V�����[�g

	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;				//�C���^�[�o��

																			//Direct3D�f�o�C�X�̐���
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))

	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))

		{
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))

			{
				return E_FAIL;
			}
		}
	}
	//�����_�\�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	LPDIRECT3DSURFACE9 pRenderDef, pZBuffDef;
	for (int nCntmt = 0; nCntmt < 2; nCntmt++)
	{
		// �����_�����O�^�[�Q�b�g�p�e�N�X�`���̐���
		m_pD3DDevice->CreateTexture(SCREEN_WIDTH,
			SCREEN_HEIGHT,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&m_pTextureMT[nCntmt],
			NULL);

		// �e�N�X�`�������_�����O�p�C���^�[�t�F�[�X�̐���
		m_pTextureMT[nCntmt]->GetSurfaceLevel(0, &m_pRenderMT[nCntmt]);
	}

	// �e�N�X�`�������_�����O�pZ�o�b�t�@�̐���
	m_pD3DDevice->CreateDepthStencilSurface(SCREEN_WIDTH,
		SCREEN_HEIGHT,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&m_pZBuffMT,
		NULL);

	// ���݂̃����_�����O�^�[�Q�b�g���擾(�ۑ�)
	m_pD3DDevice->GetRenderTarget(0, &pRenderDef);

	// ���݂�Z�o�b�t�@���擾(�ۑ�)
	m_pD3DDevice->GetDepthStencilSurface(&pZBuffDef);
	for (int nCntmt = 0; nCntmt < 2; nCntmt++)
	{
		// �����_�����O�^�[�Q�b�g�𐶐������e�N�X�`���ɐݒ�
		m_pD3DDevice->SetRenderTarget(0, m_pRenderMT[nCntmt]);
	}
	// Z�o�b�t�@�𐶐�����Z�o�b�t�@�ɐݒ�
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

	// �����_�����O�^�[�Q�b�g�p�̃e�N�X�`���̃N���A
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(255, 255, 255, 255), 1.0f, 0);

	// �����_�����O�^�[�Q�b�g�����ɖ߂�
	m_pD3DDevice->SetRenderTarget(0, pRenderDef);

	// Z�o�b�t�@�����ɖ߂�
	m_pD3DDevice->SetDepthStencilSurface(pZBuffDef);

	// �e�N�X�`�������_�����O�p�r���[�|�[�g�̐ݒ�
	m_viewportMT.X = 0;
	m_viewportMT.Y = 0;
	m_viewportMT.Width = SCREEN_WIDTH;
	m_viewportMT.Height = SCREEN_HEIGHT;
	m_viewportMT.MinZ = 0.0f;
	m_viewportMT.MaxZ = 1.0f;


	return S_OK;
}
//======================================
// �I������
//=====================================
void CRenderer::Uninit(void)
{
	//Direct3D�f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}

	// �e�N�X�`���p�̔j��









	// ���ׂẴI�u�W�F�N�g�̏I������
	CObject::ReleseAll();
}
//======================================
// �X�V����
//======================================
void CRenderer::Update(void)
{
	// �S�I�u�W�F�N�g�̍X�V����
	CObject::UpdateAll();		
}
//======================================
// �`�揈��
//======================================
void CRenderer::Draw(void)
{
	LPDIRECT3DSURFACE9 pRenderWk;
	LPDIRECT3DTEXTURE9  pTextureWk;

	//��ʃN���A(�o�b�N�o�b�t�@&Z�Ԃ��ӂ��̃N���A)
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(255, 255, 255, 255), 1.0f, 0);


	//�`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ8

		// �S�I�u�W�F�N�g�̕`�揈��
		CObject::DrawAll();
		//�`��I��
		m_pD3DDevice->EndScene();

	}
	//�΂����΂��ӂ��ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//======================================
// �����_�����O�^�[�Q�b�g�̕ύX
//======================================
void CRenderer::ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 posU)
{
	D3DXMATRIX mtxview, mtxProjection;
	float fAspect;

	// �����_�����O�^�[�Q�b�g�𐶐������e�N�X�`���ɐݒ�
	m_pD3DDevice->SetRenderTarget(0, m_pRenderMT[0]);

	// Z�o�b�t�@�𐶐�����Z�o�b�t�@�ɐݒ�
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

	// �e�N�X�`�������_�����O�p�̃r���[�|�[�g
	m_pD3DDevice->SetViewport(&m_viewportMT);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxview);

	// �r���[�}�g���b�N�X�̐���
	D3DXMatrixLookAtLH(&mtxview,
		&posV,	// ���_
		&posR,	// �����_
		&posU);	// ������x�N�g��


	// �r���[�}�g���b�N�X�̐ݒ�
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &mtxview);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̐���
	fAspect = (float)m_viewportMT.Width / (float)m_viewportMT.Height;

	//�v���W�F�N�V�����}�g���b�N�X���쐬(�������e)
	D3DXMatrixPerspectiveFovLH(&mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,			//����p�̍ŏ��l
		10000.0f);		//����p�̍ő�l

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);

}
//======================================
// �f�o�C�X�̎擾����
//======================================
LPDIRECT3DDEVICE9  CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}