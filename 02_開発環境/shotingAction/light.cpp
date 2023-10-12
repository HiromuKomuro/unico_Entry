//====================================================================
//
//���C�g����[Light.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"Light.h"
#include"Manager.h"
#include"renderer.h"

//========================================
// �R���X�g���N�^
//========================================
CLight::CLight()
{
}
//========================================
// �f�X�g���N�^
//========================================
CLight::~CLight()
{
}
//========================================
//���C�g�̏���������
//========================================
HRESULT CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^
	D3DXVECTOR3 VecDir;				//�ݒ�p�����x�N�g��

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//���C�g�̏����N���A����
		ZeroMemory(&m_alight[nCntLight], sizeof(D3DLIGHT9));

		//���C�g�̎�ނ�ݒ�
		m_alight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		////���C�g�̊g�U����ݒ�
		//m_alight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		
		if (nCntLight == 0)
		{
			/*m_alight[nCntLight].Position = D3DXVECTOR3(0.0f, -10.8f, -12.4f);*/
			//���C�g�̊g�U����ݒ�
			m_alight[nCntLight].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
			//���C�g�̕�����ݒ�
			VecDir = D3DXVECTOR3(-1.6f, 3.0f, 1.4f);
		
		}
		else if (nCntLight == 1)
		{
			/*m_alight[nCntLight].Position = D3DXVECTOR3(1.6f, -1.6f, -0.3f);*/
			//���C�g�̊g�U����ݒ�
			m_alight[nCntLight].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
			//���C�g�̕�����ݒ�
			VecDir = D3DXVECTOR3(1.6f, 0.0f, 0.6f);
		}
		else
		{
			/*m_alight[nCntLight].Position = D3DXVECTOR3(-1.6f, 10.8f, -10.0f);*/
			//���C�g�̊g�U����ݒ�
			m_alight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//���C�g�̕�����ݒ�
			VecDir = D3DXVECTOR3(0.0f, -3.0f, -0.0f);
		}
		D3DXVec3Normalize(&VecDir, &VecDir);		//�x�N�g���𐳋K������
		m_alight[nCntLight].Direction = VecDir;

		//���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &m_alight[nCntLight]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
	return S_OK;

}
//========================================
//���C�g�̏I������
//========================================
void CLight::Uninit(void)
{
}
//=======================================
//���C�g�̍X�V����
//=======================================
void CLight::Update(void)
{
}