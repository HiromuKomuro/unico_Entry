// =======================================================
//
// �e�̏���(bullet.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include"bullet.h"
#include"input.h"
#include"Manager.h"
#include"renderer.h"
#include"Explosion.h"
#include"Effect.h"
#include"Texture.h"
#include"ObjectModel.h"
#include"BlockXbase.h"

// �}�N����`
#define BULLET_SPEED	(20.0f)	// �e�̑��x
#define BULLET_SIZE	(D3DXVECTOR3(2.0f, 2.0f, 5.0f))
//====================================
// �R���X�g���N�^
//====================================
CBullet::CBullet()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = BULLET_SIZE;
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_fmove = 0.0f;
	m_posMaxX = 0.0f;
	m_posMinX = 0.0f;
	m_posMaxY = 0.0f;
	m_posMinY = 0.0f;
	m_posMaxZ = 0.0f;
	m_posMinZ = 0.0f;
	m_nLife = 200;
	CObject::SetType(TYPE_BULLET);	// ��ނ�ݒ�
}
//====================================
// �f�X�g���N�^
//====================================
CBullet::~CBullet()
{
}
//====================================
// ����������
//====================================
HRESULT CBullet::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CXModel::Init();

	CXModel::SetPos(pos);	// �ʒu���̐ݒ�
	CXModel::SetRot(rot);	// �������̐ݒ�
	CXModel::SetSize(m_Size);	// �傫����ݒ�

	m_move.x = BULLET_SPEED * sinf(rot.y);
	m_move.z = BULLET_SPEED * cosf(rot.y);

	D3DXVECTOR3 *posVertex = GetVertexPos();
	m_posMaxX = posVertex[0].x;
	m_posMinX = posVertex[0].x;
	m_posMaxY = posVertex[0].y;
	m_posMinY = posVertex[0].y;
	m_posMaxZ = posVertex[0].z;
	m_posMinZ = posVertex[0].z;

	// �e�̃��f���̑傫�����擾
	for (int nCntVer = 0; nCntVer < GetnNumVertex(); nCntVer++)
	{
		if (m_posMaxX < posVertex[nCntVer].x)
		{
			m_posMaxX = posVertex[nCntVer].x;
		}
	
		else if (m_posMinX > posVertex[nCntVer].x)
		{
			m_posMinX = posVertex[nCntVer].x;
		}

		if (m_posMaxY < posVertex[nCntVer].y)
		{
			m_posMaxY = posVertex[nCntVer].y;
		}

		else if (m_posMinY > posVertex[nCntVer].y)
		{
			m_posMinY = posVertex[nCntVer].y;
		}
	
		if (m_posMaxZ < posVertex[nCntVer].z)
		{
			m_posMaxZ = posVertex[nCntVer].z;
		}

		else if (m_posMinZ > posVertex[nCntVer].z)
		{
			m_posMinZ = posVertex[nCntVer].z;
		}
	}
	m_posMaxX *= m_Size.x;
	m_posMaxY *= m_Size.y;
	m_posMaxZ *= m_Size.z;
	return S_OK;
}
//======================================
// �I������
//=====================================
void CBullet::Uninit(void)
{
	CXModel::Uninit();

	CObject::Relese();
}
//======================================
// �X�V����
//======================================
void CBullet::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	CEffect2D::Create(pos, GetRot(), D3DCOLOR_RGBA(255, 255, 255, 100),50);

	// �ʒu��ۑ�
	m_posOld = pos;

	// �I�u�W�F�N�g�̍X�V����
	CXModel::Update();

	// �ʒu�𑝉�
	pos += m_move;

	// �ʒu��ݒ�
	SetPos(pos);

	// �u���b�N�Ƃ̓����蔻��
	if (CBaseBlockX::Collision(&pos, &m_posOld, &m_move, rot, m_posMaxX, m_posMaxY, m_posMinZ,true,false) == TRUE)
	{// ���Ă��Ă���Ƃ�
		Uninit();			// �e���폜
		CExplosion::Create(pos);	// �����𐶐�

		return;
	}
	m_nLife--;	// �̗͂����炷
	if (m_nLife <= 0)
	{// ���C�t��0�̎�
		Uninit();	// �e���폜
		CExplosion::Create(pos);	// �����𐶐�

	}
}
//======================================
// �`�揈��
//======================================
void CBullet::Draw(void)
{
	// �I�u�W�F�N�g�̕`�揈��
	CXModel::Draw();
}
//======================================
// ��������
//======================================
CBullet *CBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const char* pFilename)
{
	CBullet *pCBullet = NULL;
	
	// �I�u�W�F�N�g2D�̐���
 	pCBullet = new CBullet();
	
	// ���f���̐ݒ�
	pCBullet->BindModel(pFilename);

	// ����������
	pCBullet->Init(pos,rot);

 	return pCBullet;
}

//====================================
// �R���X�g���N�^
//====================================
CChargeBullet::CChargeBullet()
{
}
//====================================
// �f�X�g���N�^
//====================================
CChargeBullet::~CChargeBullet()
{
}
//====================================
// ����������
//====================================
HRESULT CChargeBullet::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CBullet::Init(pos, rot);

	return S_OK;
}
//======================================
// �I������
//=====================================
void CChargeBullet::Uninit(void)
{
	CObject::Relese();
}
//======================================
// �X�V����
//======================================
void CChargeBullet::Update(void)
{
	CBullet::Update();
}
//======================================
// �`�揈��
//======================================
void CChargeBullet::Draw(void)
{
	// �I�u�W�F�N�g�̕`�揈��
	CBullet::Draw();
}
//======================================
// ��������
//======================================
CChargeBullet *CChargeBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, D3DXVECTOR3 size, const char* pFilename)
{
	CChargeBullet *pChargeBullet = NULL;

	// �I�u�W�F�N�g2D�̐���
	pChargeBullet = new CChargeBullet();

	// ���f���̐ݒ�
	pChargeBullet->BindModel(pFilename);

	// �T�C�Y�̐ݒ�
	pChargeBullet->SetSize(size);

	// ����������
	pChargeBullet->Init(pos, rot);

	return pChargeBullet;
}