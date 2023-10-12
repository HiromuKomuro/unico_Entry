//====================================================================
//
//�v���C���[3D����[Player3D.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"Player3D.h"
#include"input.h"
#include"Bullet.h"
#include"Camera.h"
#include"Manager.h"
#include"renderer.h"
#include"sound.h"
#include"Texture.h"
#include"ObjectModel.h"
#include"motion.h"
#include"BlockXbase.h"
#include"MeshCylinder.h"
#include"Fade.h"
#include"Score.h"
#include"renderer.h"
#include"Camera.h"

//�}�N����`
#define MODEL_LEFTRIHGTMOVE			(5.0f)
#define MODEL_UPDOWNMOVE			(3.0f)
#define BULLET_MAXCNT		(180)			// �e�̃`���[�W�̍ő�
#define BULLET_SIZE			(D3DXVECTOR3(10.0,10.0f,10.0f))		// �e�̃T�C�Y
#define SPEED_SCORE			(1)
#define BOOST_SPEED_MAX		(30)
//========================================
// �R���X�g���N�^
//========================================
CPlayer3D::CPlayer3D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_boostmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CObject::SetType(TYPE_PLAYER);	// ��ނ�ݒ�
	m_nNumModel = 0;
	m_nLife = 100;
	m_nSpeedCnt = 0;
	m_nBoostCnt = 0;
	m_pMotion = NULL;
	m_bBoost = false;
}
//========================================
// �f�X�g���N�^
//========================================
CPlayer3D::~CPlayer3D()
{
}
//========================================
//���f���̏���������
//========================================
HRESULT CPlayer3D::Init(void)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���f���̐���
	m_apModel[0] = CObjectModel::Create("data\\MODEL\\car000.x",m_pos);
	m_apModel[1] = CObjectModel::Create("data\\MODEL\\propeller.x", D3DXVECTOR3(20.0f, 20.0f, 10.0f));
	m_apModel[2] = CObjectModel::Create("data\\MODEL\\propeller.x" ,D3DXVECTOR3(-20.0f, 20.0f, 10.0f));
	
	// �e���f���̐ݒ�
	m_apModel[0]->SetParent(NULL);
	m_apModel[1]->SetParent(m_apModel[0]);
	m_apModel[2]->SetParent(m_apModel[0]);

	if (m_pMotion != NULL)
	{
		delete m_pMotion;
		m_pMotion = NULL;
	}

	m_pMotion = new CMotion;	// �C���X�^���X�𐶐�

	m_pMotion->SetModel(&m_apModel[0], MAX_PLAYER_PARTS);	// ���f���̐ݒ�

	return S_OK;
}
//========================================
//���f���̏I������
//========================================
void CPlayer3D::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_PLAYER_PARTS; nCnt++)
	{
		// �v���C���[3D�j��
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->Uninit();
			delete m_apModel[nCnt];
			m_apModel[nCnt] = NULL;
		}
	}

	// ���[�V�����̔j��
	if (m_pMotion != NULL)
	{
		delete m_pMotion;
		m_pMotion = NULL;
	}

	CObject::Relese();
}
//=======================================
//���f���̍X�V����
//=======================================
void CPlayer3D::Update(void)
{
	CFade*pFade = CManager::GetCFade();
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CSound*pSound = CManager::GetSound();
	CScene*pScene = CManager::GetCScene();

	int Fade;	

	switch (pScene->GetMode())
	{
	case CScene::MODE_TITLE:

		break;
	case CScene::MODE_GAME:
		m_posOld = m_pos;	// �ʒu�ۑ�

		// �����X�N���[������
		m_move.z += 2.0f + m_nSpeedCnt * 0.001f;

		// �ړ�����
		if (pInputKeyboard->GetKeyboardPress(DIK_D) == true)
		{
			m_move.x += cosf(m_rot.y) * MODEL_LEFTRIHGTMOVE;
			m_move.z -= sinf(m_rot.y) * MODEL_LEFTRIHGTMOVE;
		}
		if (pInputKeyboard->GetKeyboardPress(DIK_A) == true)
		{
			m_move.x -= cosf(m_rot.y) * MODEL_LEFTRIHGTMOVE;
			m_move.z += sinf(m_rot.y) * MODEL_LEFTRIHGTMOVE;
		}
		if (pInputKeyboard->GetKeyboardPress(DIK_W) == true)
		{
			m_move.y += cosf(m_rot.y) * MODEL_UPDOWNMOVE;
		}
		if (pInputKeyboard->GetKeyboardPress(DIK_S) == true)
		{
			m_move.y -= cosf(m_rot.y) * MODEL_UPDOWNMOVE;
		}
		if (pInputKeyboard->GetKeyboardPress(DIK_LSHIFT) == true)
		{
			m_move.x += sinf(m_rot.y) * MODEL_UPDOWNMOVE;
			m_move.z -= cosf(D3DX_PI - m_rot.y) * MODEL_UPDOWNMOVE;
			CScore::AddScore(SPEED_SCORE);	// �X�R�A�̑���c

		}
		//if (m_bBoost == true)
		//{// �u�[�X�g������Ƃ�
		//	m_nBoostCnt ++;
		//	m_boostmove.z = m_nBoostCnt % BOOST_SPEED_MAX;

		//	if (m_nBoostCnt >= BOOST_SPEED_MAX)
		//	{
		//		m_bBoost = false;
		//		m_nBoostCnt = 0;
		//	}
		//}
	
		// �e�̔���
		if (pInputKeyboard->GetKeyboardRelease(DIK_SPACE) == true)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ATTCAK);	// �U��SE�̍Đ�

			CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z - 10.0f), m_rot, "data\\MODEL\\missile.x");	// �e�𐶐�	
		}
		// �ʒu�𑝉�
		m_pos += m_move;
		m_pos += m_boostmove;

		//�ړ��ʂ��X�V(����������)
		m_move.x += (0.0f - m_move.x) * 0.7f;
		m_move.y += (0.0f - m_move.y) *	0.7f;
		m_move.z += (0.0f - m_move.z) * 0.7f;
		m_boostmove.z += (0.0f - m_boostmove.z) * 0.1f;

		// �X�e�[�W�Ƃ̓����蔻��
		if (CMeshClynder::Collision(m_pos) == true)
		{
			m_pos = m_posOld;
			m_move.x = 0.0f;
			m_move.y = 0.0f;

			//�t�F�[�h��Ԃ��擾
			Fade = pFade->Get();

			if (Fade == CFade::FADE_NONE)
			{//�t�F�[�h��Ԃ������Ȃ��Ƃ�
			 //�t�F�[�h�̐ݒ�(�Q�[����ʂɈڍs)
				pFade->Set(CScene::MODE_REZULT);
			}
		}

		// �u���b�N�Ƃ̓����蔻��
		if (CBaseBlockX::Collision(&m_pos, &m_posOld, &m_move, m_rot, 20, 30, 30, false, true) == true)
		{
			CFade*pFade = CManager::GetCFade();
			int Fade;

			//�t�F�[�h��Ԃ��擾
			Fade = pFade->Get();

			if (Fade == CFade::FADE_NONE)
			{//�t�F�[�h��Ԃ������Ȃ��Ƃ�
			 //�t�F�[�h�̐ݒ�(���U���g��ʂɈڍs)
				pFade->Set(CScene::MODE_REZULT);
			}
		}

		// �X�R�A�̑���
		if (CBaseBlockX::AddScore(m_pos, 40, 40, 30) == true)
		{
			m_bBoost = true;
			m_nSpeedCnt += 1000;
		}

		m_nSpeedCnt++;	// �X�s�[�h�J�E���^�[�̑���
		CScore::AddScore(SPEED_SCORE * (m_nSpeedCnt * 0.005f));	// �X�R�A�̑���c
		m_pMotion->Update();	// ���[�V�����̍X�V����
		break;
	}
	
}
//======================================
//���f���̕`�揈��
//======================================
void CPlayer3D::Draw(void)
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

	// ���f���̕`�揈��
	for (int nCnt = 0; nCnt < MAX_PLAYER_PARTS; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}
}
//======================================
// �ݒ菈��
//======================================
CPlayer3D *CPlayer3D::Create(D3DXVECTOR3 pos)
{
	CPlayer3D *pModel;

	// �I�u�W�F�N�g3D�̐���
	pModel = new CPlayer3D();

	// ����������
	pModel->Init();

	pModel->SetPos(pos);	// �ʒu��ݒ�

	return pModel;
}