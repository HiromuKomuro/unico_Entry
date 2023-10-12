//====================================================================
//
//���蔲����E�Ǐ���[ThroughWall.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"throughWall.h"
#include"Manager.h"
#include"renderer.h"
#include"Texture.h"
#include"input.h"

//�}�N����`�@
#define Wall_WIDTH		(200.0)
#define Wall_HEIGHT		(250.0)
//====================================
// �R���X�g���N�^
//====================================
CThroughWall3D::CThroughWall3D()
{
	CObject::SetType(TYPE_THROUGHWALL);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//====================================
// �f�X�g���N�^
//====================================
CThroughWall3D::~CThroughWall3D()
{
}
//========================================
//�@����������
//========================================
HRESULT CThroughWall3D::Init(const D3DXVECTOR3 pos)
{
	CObject3D::Init();

	// �ʒu���̐ݒ�
	CObject3D::SetPos(pos);
	CObject3D::SetScale(Wall_WIDTH , Wall_HEIGHT,0.0f);

	return S_OK;
}
//========================================
// �I������
//========================================
void CThroughWall3D::Uninit(void)
{
	CObject3D::Uninit();
}
//=======================================
// �X�V����
//=======================================
void CThroughWall3D::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	CObject3D::Update();

	if (pInputKeyboard->GetKeyboardPress(DIK_E) == true)
	{
		m_rot.z += ROT_TRANS;
	}
	if (pInputKeyboard->GetKeyboardPress(DIK_Q) == true)
	{
		m_rot.z -= ROT_TRANS;
	}

	SetRot(m_rot);
}

//======================================
//�|���S���̕`�揈��
//======================================
void CThroughWall3D::Draw(void)
{
	CTexture*pTexture = CManager::GetCTexture();
	CRenderer *pRenderer = CManager::GetRenderer();

	//�e�N�X�`���̐ݒ�
	pRenderer->GetDevice()->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	CObject3D::Draw();
}
//======================================
// ��������
//======================================
CThroughWall3D *CThroughWall3D::Create(const D3DXVECTOR3 pos)
{
	CThroughWall3D *pThroughWall3D = NULL;

	// �I�u�W�F�N�g3D�̐���
	pThroughWall3D = new CThroughWall3D();

	// ����������
	pThroughWall3D->Init(pos);

	return pThroughWall3D;
}
//======================================
// �ǂƂ̓����蔻��
//======================================
bool CThroughWall3D::CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 pRot, float fWidth, float fHeight)
{
	bool bLand = false;			//���n�������ǂ���

	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		CObject *pObj = CObject::GetTop(nCntPri);	// �擪�̃I�u�W�F�N�g����

		while (pObj != NULL)
		{
			CObject *pObjectNext = pObj->GetNext();	// ���̃I�u�W�F�N�g��ۑ�

			// ��ނ��擾
			TYPE type = pObj->GetType();

			if (type == TYPE_THROUGHWALL)
			{
				CThroughWall3D *pWall3D = dynamic_cast<CThroughWall3D*>(pObj);

				// �Ίp���̒������Z�o����
				float fLength = sqrtf(Wall_WIDTH * Wall_WIDTH + Wall_HEIGHT * Wall_HEIGHT);

				// �Ίp���̊p�x���Z�o����
				float fAngle = atan2f(Wall_WIDTH, Wall_HEIGHT);

				if (pPos->x - fWidth / 2 <= pWall3D->GetPos().x + Wall_WIDTH &&
					pPos->x + fWidth / 2 >= pWall3D->GetPos().x - Wall_WIDTH &&
					pPos->y - fHeight / 2 <= pWall3D->GetPos().y + Wall_HEIGHT &&
					pPos->y + fHeight / 2 >= pWall3D->GetPos().y - Wall_HEIGHT &&
					pPos->z - fHeight / 2 <= pWall3D->GetPos().z  &&
					pPos->z + fHeight / 2 >= pWall3D->GetPos().z)
				{


				}
			}
			pObj = pObjectNext;		// ���̃I�u�W�F�N�g����
		}
	}
	return bLand;
}
