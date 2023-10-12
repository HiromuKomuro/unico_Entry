//====================================================================
//
//�J��������[Camera.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"Camera.h"
#include"input.h"
#include"Bullet.h"
#include"Manager.h"
#include"renderer.h"
#include"object.h"
#include"Player3D.h"

//�}�N����`
#define CAMERAV_INIT_POS		(D3DXVECTOR3(800.0f, 100.0f, 0.0f))	// �J�����̏����ʒu
#define CAMERA_MOVE			(2)			//�J�����̈ړ���
#define CAMERA_DIS			(550)		//�J�����̉���
#define CAMERA_HEIGHT		(100.0f)		//�J�����̍���
#define CAMERA_CDIS			(600)		//�J�����̒����̉���
#define CAMERA_CHEIGHT		(1300)		//�J�����̒����̍���
#define CAMERA_TITLE_CDIS	(200)		//�J�����̒����̉���
#define CAMERA_TITLE_CHEIGHT		(800)		//�J�����̒����̍���

//========================================
// �R���X�g���N�^
//========================================
CCamera::CCamera()
{
	//�J�����̏��̏�����
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//========================================
// �R���X�g���N�^
//========================================
CCamera::~CCamera()
{
}
//========================================
// ����������
//========================================
HRESULT CCamera::Init(void)
{
	//�J�����̏��̏�����
	m_posV = D3DXVECTOR3(800.0f, 100.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}
//========================================
//�J�����̏I������
//========================================
void CCamera::Uninit(void)
{
}
//=======================================
//�J�����̍X�V����
//=======================================
void CCamera::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	//���������߂�
	float ra = m_posV.x - m_posR.x;
	float rb = m_posV.z - m_posR.z;

	float rc = sqrtf(ra * ra + rb * rb);

	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		CObject *pObj = CObject::GetTop(nCntPri);	// �擪�̃I�u�W�F�N�g����

		while (pObj != NULL)
		{
			CObject *pObjectNext = pObj->GetNext();	// ���̃I�u�W�F�N�g��ۑ�

				//��ނ��擾
			CObject::TYPE type = pObj->GetType();

			if (type == CObject::TYPE_PLAYER)
			{
				CPlayer3D *pModel = dynamic_cast<CPlayer3D*>(pObj);

				// �J�����̈ʒu��ݒ�
				m_posR = pModel->GetPos();
				m_rot = pModel->GetRot();
				//m_posR.x = m_posV.x + sin(m_rot.y) * rc;
				//m_posR.z = m_posV.z + cos(m_rot.y) * rc;
				m_posV.x = m_posR.x + sinf((D3DX_PI)+m_rot.y) * rc;
				m_posV.y = m_posR.y + CAMERA_HEIGHT;
				m_posV.z = m_posR.z + cosf((D3DX_PI)+m_rot.y) * rc;

			}
			pObj = pObjectNext;		// ���̃I�u�W�F�N�g����
		}
	}
	



	//�J�����̈ړ�����

	//if (pInputKeyboard->GetKeyboardPress(DIK_D) == true)
	//{//D�L�[�������ꂽ��
	//	/*m_posV.x += CAMERA_MOVE;
	//	m_posR.x += CAMERA_MOVE;*/
	//	m_posV.z -= sin(m_rot.y) *CAMERA_MOVE;
	//	m_posR.z -= sin(m_rot.y) *CAMERA_MOVE;
	//	m_posV.x += cos(m_rot.y) * CAMERA_MOVE;
	//	m_posR.x += cos(m_rot.y) * CAMERA_MOVE;
	//	
	//}
	//else if (pInputKeyboard->GetKeyboardPress(DIK_A) == true)
	//{//A�L�[�������ꂽ��
	//	/*m_posV.x -= CAMERA_MOVE;
	//	m_posR.x -= CAMERA_MOVE;*/
	//	
	//	m_posV.z += sin(m_rot.y) *CAMERA_MOVE;
	//	m_posR.z += sin(m_rot.y) *CAMERA_MOVE;
	//	m_posV.x -= cos(m_rot.y) * CAMERA_MOVE;
	//	m_posR.x -= cos(m_rot.y) * CAMERA_MOVE;
	//
	//}
	//if (pInputKeyboard->GetKeyboardPress(DIK_W) == true)
	//{//W�L�[�������ꂽ��
	//	/*m_posV.z += CAMERA_MOVE;
	//	m_posR.z += CAMERA_MOVE;*/
	//	m_posV.x += sin(m_rot.y)  *CAMERA_MOVE;
	//	m_posR.x += sin(m_rot.y) * CAMERA_MOVE;
	//	m_posV.z -= cos(D3DX_PI - m_rot.y)  * CAMERA_MOVE;
	//	m_posR.z -= cos(D3DX_PI - m_rot.y) * CAMERA_MOVE;
	//}
	//else if (pInputKeyboard->GetKeyboardPress(DIK_S) == true)
	//{//S�L�[�������ꂽ��
	//	/*m_posV.z -= CAMERA_MOVE;
	//	m_posR.z -= CAMERA_MOVE;*/
	//	m_posV.x -= sin(m_rot.y) * CAMERA_MOVE;
	//	m_posR.x -= sin(m_rot.y) * CAMERA_MOVE;
	//	m_posV.z += cos(D3DX_PI - m_rot.y) * CAMERA_MOVE;
	//	m_posR.z += cos(D3DX_PI - m_rot.y) * CAMERA_MOVE;
	//}


	//if (pInputKeyboard->GetKeyboardPress(DIK_Q) == true)
	//{//Q�L�[�������ꂽ��
	//	m_rot.y -= 0.01f ;

	//	m_posR.x = m_posV.x + sin( m_rot.y) * rc;
	//	m_posR.z = m_posV.z + cos( m_rot.y) * rc;
	//}
	//else if (pInputKeyboard->GetKeyboardPress(DIK_E) == true)
	//{//E�L�[�������ꂽ��
	//	m_rot.y += 0.01f;
	//	
	//	m_posR.x = m_posV.x + sin(m_rot.y) * rc;
	//	m_posR.z = m_posV.z + cos(m_rot.y) * rc;
	//}
	//if (pInputKeyboard->GetKeyboardPress(DIK_T) == true)
	//{//T�L�[�������ꂽ��
	//	/*m_rot.y += 0.01f;

	//	m_posR.y = m_posV.y + tan(m_rot.y) * rc;*/
	//	//m_moveR.y += 1.5f;
	//}
	//else if (pInputKeyboard->GetKeyboardPress(DIK_B) == true)
	//{//B�L�[�������ꂽ��
	//	/*m_rot.y -= 0.01f;

	//	m_posR.y = m_posV.y + tan(m_rot.y) * rc;*/
	//	//m_moveR.y -= 1.5f;
	//}


	//if (pInputKeyboard->GetKeyboardPress(DIK_Z) == true)
	//{//Z�L�[�������ꂽ��
	//	m_rot.y -= 0.01f;
	//}
	//else if (pInputKeyboard->GetKeyboardPress(DIK_C) == true)
	//{//C�L�[�������ꂽ��
	//	m_rot.y += 0.01f;
	//}
	//else if (pInputKeyboard->GetKeyboardPress(DIK_Y) == true)
	//{//Y�L�[�������ꂽ��
	//	/*m_rot.y -= 0.01f;

	//	m_posV.y = m_posR.y + tan(-(D3DX_PI - m_rot.y)) * rc;*/
	//	//m_moveV.y += 1.5f;
	//}
	//else if (pInputKeyboard->GetKeyboardPress(DIK_N) == true)
	//{//N�L�[�������ꂽ��
	///*	m_rot.y += 0.01f;

	//	m_posV.y = m_posR.y + tan(-(D3DX_PI - m_rot.y)) * rc;*/
	//	//m_moveV.y -= 1.5f;
	//}
}
//======================================
//�J�����̐ݒ菈��
//======================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();


	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬(�������e)
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
								D3DXToRadian(45.0f),
								(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
								10.0f,			//����p�̍ŏ��l
								10000.0f);		//����p�̍ő�l
												
	////�v���W�F�N�V�����}�g���b�N�X���쐬(���s���e)
	//D3DXMatrixOrthoLH(&m_mtxProjection,
	//	(float)SCREEN_WIDTH,	// ��ʂ̕�
	//	(float)SCREEN_HEIGHT,	// ��ʂ̍���
	//	10.0f,			// ����p�̍ŏ��l
	//	10000.0f);		// ����p�̍ő�l
	
	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
						&m_posV,		//���_
						&m_posR,		//�����_
						&m_vecU);	//������x�N�g��

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}