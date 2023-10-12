//====================================================================
//
//�u���b�N�̊�b�ʒu�̏���[BlockXbase.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include <math.h>

#include"main.h"
#include"BlockXbase.h"
#include"input.h"
#include"Bullet.h"
#include"Camera.h"
#include"Manager.h"
#include"renderer.h"
#include"sound.h"
#include"Texture.h"
#include"ObjectModel.h"
#include"motion.h"
#include"BlockX.h"
#include"collisionline.h"
#include"Score.h"
#include"Particle.h"

//�}�N����`
#define MODEL_MOVE			(3)
#define HIT_COL				(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))
#define NOTHIT_COL			(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
#define MAX_SCORE			(10000.0f)
#define MAX_DISTANCE		(1000.0f)
#define SCORE_MAG			(20.0f)		
#define Correction			(0.0f)
//========================================
// �R���X�g���N�^
//========================================
CBaseBlockX::CBaseBlockX()
{
	CObject::SetType(TYPE_BLOCKBASE);

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumModel = 0;
	m_nId = 0;
	m_bDeath = false;
	m_pFilename = NULL;
}
//========================================
// �f�X�g���N�^
//========================================
CBaseBlockX::~CBaseBlockX()
{
}
//========================================
// ����������
//========================================
HRESULT CBaseBlockX::Init(void)
{
	// ���f���̐���
	m_apModel = CBlockX::Create(D3DXVECTOR3(m_pos.x,m_pos.y,0.0f),m_pFilename,m_Size);

	// �e���f���̐ݒ�
	m_apModel->SetParent(NULL);

	m_pos = D3DXVECTOR3(0.0f, (250.0f * 7.0f + 100.0f) / 2, m_pos.z);

	return S_OK;
}
//========================================
// �I������
//========================================
void CBaseBlockX::Uninit(void)
{
	if (m_apModel != NULL)
	{
		m_apModel->Uninit();
		delete m_apModel;
		m_apModel = NULL;
	}

	CObject::Relese();
}
//=======================================
// �X�V����
//=======================================
void CBaseBlockX::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// ��]����
	if (pInputKeyboard->GetKeyboardPress(DIK_RIGHT) == true)
	{
		m_rotmove.z += ROT_TRANS;
	}
	if (pInputKeyboard->GetKeyboardPress(DIK_LEFT) == true)
	{
		m_rotmove.z -= ROT_TRANS;
	}

	// �ʒu�𑝉�
	m_rot += m_rotmove;

	//�ړ��ʂ��X�V(����������)
	m_rotmove.x += (0.0f - m_rotmove.x) * 0.8f;
	m_rotmove.y += (0.0f - m_rotmove.y) * 0.8f;
	m_rotmove.z += (0.0f - m_rotmove.z) * 0.8f;

	m_apModel->Update();
	
}
//======================================
//���f���̕`�揈��
//======================================
void CBaseBlockX::Draw(void)
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
	m_apModel->Draw(m_mtxWorld);
	
}
//======================================
// �ݒ菈��
//======================================
CBaseBlockX *CBaseBlockX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 Size)
{
	CBaseBlockX *pModel;

	// �I�u�W�F�N�g3D�̐���
	pModel = new CBaseBlockX();

	pModel->SetSize(Size);	// �T�C�Y�̐ݒ�

	pModel->SetPos(pos);	// �ʒu��ݒ�

	pModel->SetFile("data//MODEL//Block.x");	// �t�@�C�����̐ݒ�

	// ����������
	pModel->Init();

	// �����蔻��̃��C���̐���
	CCollisionLine::Create(D3DXVECTOR3(pModel->GetBlock()->GetPos().x, pModel->GetBlock()->GetPos().y, pModel->GetPos().z),
		D3DXVECTOR3(pModel->GetBlock()->GetMaxpos().x, pModel->GetBlock()->GetMaxpos().y, pModel->GetBlock()->GetMaxpos().z),
		&pModel->m_nId);

	return pModel;
}
//======================================
// �ǂƂ̓����蔻��
//======================================
bool CBaseBlockX::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 pRot, float fWidth, float fHeight, float fDepth, bool bBullet, bool bPlayer)
{
	bool bChangeCol;
	bool bHit = false;

	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		CObject *pObj = CObject::GetTop(nCntPri);	// �擪�̃I�u�W�F�N�g����

		while (pObj != NULL)
		{
			bChangeCol = false;			//�F��ς��邩

			if (bPlayer == true && bHit == true)
			{// �v���C���[�̏ꍇ�Ńq�b�g���Ă���Ƃ�
				return bHit;
			}

			CObject *pObjectNext = pObj->GetNext();	// ���̃I�u�W�F�N�g��ۑ�

			//��ނ��擾
			TYPE type = pObj->GetType();

			if (type == TYPE_BLOCKBASE || type == TYPE_BREAKBLOCKBASE)
			{
				CBaseBlockX *pBlockbase = dynamic_cast<CBaseBlockX*>(pObj);

				if (type == TYPE_BREAKBLOCKBASE)
				{
					CBreakBaseBlockX *pBlockbase = dynamic_cast<CBreakBaseBlockX*>(pObj);
				}

				CBlockX* pBlock = pBlockbase->GetBlock();

				D3DXVECTOR3 pos0, pos1, pos2, pos3;

				// �v�Z�ɕK�v�ȗv�f�����
				D3DXVECTOR3 Maxpos = pBlock->GetMaxpos();
				D3DXVECTOR3 Minpos = pBlock->GetMinpos();
				float fLength = pBlock->GetLength();
				float fAngle = pBlock->GetAngle();

				D3DXVECTOR3 rot = pBlockbase->GetRot();

				D3DXVECTOR3 pos;
				
				pos.x = pBlock->GetMtx()._41;
				pos.y = pBlock->GetMtx()._42;
				pos.z = pBlock->GetMtx()._43;

				// �����蔻��p�̒��_��ݒ�
		/*		pos0.x = pos.x + sinf(rot.z + (D3DX_PI + fAngle)) * fLength ;
				pos0.y = pos.y + +cosf(rot.z + (D3DX_PI + fAngle)) * fLength;
				pos0.z = Maxpos.z + pos.z;

				pos1.x = pos.x + sinf(rot.z + (D3DX_PI - fAngle)) * fLength;
				pos1.y = pos.y + cosf(rot.z + (D3DX_PI - fAngle)) * fLength;
				pos1.z = Minpos.z + pos.z;

				pos2.x = pos.x + sinf(rot.z + (-fAngle)) * fLength;
				pos2.y = pos.y + cosf(rot.z + (-fAngle)) * fLength;
				pos2.z = Maxpos.z + pos.z;

				pos3.x = pos.x + sin(rot.z + (fAngle)) * fLength;
				pos3.y = pos.y + cos(rot.z + (fAngle)) * fLength;*/
				//pos3.z = Minpos.z + pos.z;

				pos0.x = pos.x - Maxpos.x;
				pos0.y = pos.y + Maxpos.y;
				pos0.z = Maxpos.z + pos.z;

				pos1.x = pos.x + Maxpos.x;
				pos1.y = pos.y + Maxpos.y;
				pos1.z = Minpos.z + pos.z;

				pos2.x = pos.x - Maxpos.x;
				pos2.y = pos.y - Maxpos.y;
				pos2.z = Maxpos.z + pos.z;

				pos3.x = pos.x + Maxpos.x;
				pos3.y = pos.y - Maxpos.y;
				pos3.z = Minpos.z + pos.z;


				if (Minpos.z + pos.z >= pPosOld->z + fDepth&&
					Minpos.z + pos.z <= pPos->z + fDepth
					)
				{// z�͈͓̔��ɂ���Ƃ�
					bool b01 = ((pos1.y - pos0.y) * (pPos->x - pos0.x)) - ((pos1.x - pos0.x) * (pPos->y - pos0.y)) >= 0.0f;
					bool b13 = ((pos3.y - pos1.y) * (pPos->x - pos1.x)) - ((pos3.x - pos1.x) * (pPos->y - pos1.y)) >= 0.0f;
					bool b32 = ((pos2.y - pos3.y) * (pPos->x - pos3.x)) - ((pos2.x - pos3.x) * (pPos->y - pos3.y)) >= 0.0f;
					bool b20 = ((pos0.y - pos2.y) * (pPos->x - pos2.x)) - ((pos0.x - pos2.x) * (pPos->y - pos2.y)) >= 0.0f;

					if (b01 && b13 && b32 && b20)
					{// x��y�͈͓̔��̎�
						bHit = true;
						bChangeCol = true;
						pMove->z = 0.0f;
						pPos->z = Minpos.z + pos.z - fDepth;
					}

				}
				if (Minpos.x + pos.x >= pPosOld->x + fWidth&&
					Minpos.x + pos.x <= pPos->x + fWidth)
				{// �E���̓����蔻��
					bool b02 = ((pos1.y - pos0.y) * (pPos->z - pos0.z)) - ((pos1.z - pos0.z) * (pPos->y - pos0.y)) <= 0.0f;
					bool b14 = ((pos3.y - pos1.y) * (pPos->z - pos1.z)) - ((pos3.z - pos1.z) * (pPos->y - pos1.y)) <= 0.0f;
					bool b33 = ((pos2.y - pos3.y) * (pPos->z - pos3.z)) - ((pos2.z - pos3.z) * (pPos->y - pos3.y)) <= 0.0f;
					bool b20 = ((pos0.y - pos2.y) * (pPos->z - pos2.z)) - ((pos0.z - pos2.z) * (pPos->y - pos2.y)) <= 0.0f;

					if (b02 && b14 && b33 && b20)
					{// x�Ƃ͈͓̔��̎�
						bHit = true;
						bChangeCol = true;
						pMove->x = 0.0f;
						pPos->x = Minpos.x + pos.x - fWidth;
					}
				}
				else if (Maxpos.x + pos.x <= pPosOld->x - fWidth&&
					Maxpos.x + pos.x >= pPos->x - fWidth)
				{// �����̓����蔻��
					bool b02 = ((pos1.y - pos0.y) * (pPos->z - pos0.z)) - ((pos1.z - pos0.z) * (pPos->y - pos0.y)) <= 0.0f;
					bool b14 = ((pos3.y - pos1.y) * (pPos->z - pos1.z)) - ((pos3.z - pos1.z) * (pPos->y - pos1.y)) <= 0.0f;
					bool b33 = ((pos2.y - pos3.y) * (pPos->z - pos3.z)) - ((pos2.z - pos3.z) * (pPos->y - pos3.y)) <= 0.0f;
					bool b20 = ((pos0.y - pos2.y) * (pPos->z - pos2.z)) - ((pos0.z - pos2.z) * (pPos->y - pos2.y)) <= 0.0f;

					if (b02 && b14 && b33 && b20)
					{// x�Ƃ͈͓̔��̎�
						bHit = true;
						bChangeCol = true;
						pMove->x = 0.0f;
						pPos->x = Maxpos.x + pos.x + fWidth;
					}
				}
				if (Maxpos.y + pos.y <= pPosOld->y - fHeight&&
					Maxpos.y + pos.y >= pPos->y - fHeight)
				{// �㑤�̓����蔻��
					float fProxypos0, fProxypos1, fProxypos2, fProxypos3;	// �㗝�̕ϐ���p��
					// �e�ʒu�̐ݒ�
					fProxypos0 = pos0.z;
					fProxypos1 = pos2.z;
					fProxypos2 = pos1.z;
					fProxypos3 = pos3.z;

					bool b02 = ((pos1.x - pos0.x) * (pPos->z - fProxypos0)) - ((fProxypos1 - fProxypos0) * (pPos->x - pos0.x)) <= 0.0f;
					bool b14 = ((pos3.x - pos1.x) * (pPos->z - fProxypos1)) - ((fProxypos3 - fProxypos1) * (pPos->x - pos1.x)) <= 0.0f;
					bool b33 = ((pos2.x - pos3.x) * (pPos->z - fProxypos3)) - ((fProxypos2 - fProxypos3) * (pPos->x - pos3.x)) <= 0.0f;
					bool b20 = ((pos0.x - pos2.x) * (pPos->z - fProxypos2)) - ((fProxypos0 - fProxypos2) * (pPos->x - pos2.x)) <= 0.0f;

					if (b02 && b14 && b33 && b20)
					{// x�Ƃ͈͓̔��̎�
						bHit = true;
						bChangeCol = true;
						pMove->y = 0.0f;
						pPos->y = Maxpos.y + pos.y + fHeight;
					}
				}
				else if (Minpos.y + pos.y >= pPosOld->y + fHeight&&
					Minpos.y + pos.y <= pPos->y + fHeight)
				{// �����̓����蔻��
					float fProxypos0, fProxypos1, fProxypos2, fProxypos3;	// �㗝�̕ϐ���p��
					// �e�ʒu�̐ݒ�
					fProxypos0 = pos0.z;
					fProxypos1 = pos2.z;
					fProxypos2 = pos1.z;
					fProxypos3 = pos3.z;

					bool b02 = ((pos1.x - pos0.x) * (pPos->z - fProxypos0)) - ((fProxypos1 - fProxypos0) * (pPos->x - pos0.x)) <= 0.0f;
					bool b14 = ((pos3.x - pos1.x) * (pPos->z - fProxypos1)) - ((fProxypos3 - fProxypos1) * (pPos->x - pos1.x)) <= 0.0f;
					bool b33 = ((pos2.x - pos3.x) * (pPos->z - fProxypos3)) - ((fProxypos2 - fProxypos3) * (pPos->x - pos3.x)) <= 0.0f;
					bool b20 = ((pos0.x - pos2.x) * (pPos->z - fProxypos2)) - ((fProxypos0 - fProxypos2) * (pPos->x - pos2.x)) <= 0.0f;

					if (b02 && b14 && b33 && b20)
					{// x�Ƃ͈͓̔��̎�
						bHit = true;
						bChangeCol = true;
						pMove->y = 0.0f;
						pPos->y = Minpos.y + pos.y - fHeight;
					}
				}

				if (bChangeCol == true)
				{// �������Ă���Ƃ�
					pBlock->SetCol(HIT_COL);	// �F�̕ύX

					if (bBullet == true && type == TYPE_BREAKBLOCKBASE)
					{// �e�̎��Ŏ�ނ�����u���b�N�̎�
						pBlockbase->Uninit();	// �u���b�N����
						CScore::AddScore(1000);
						break;
					}
				}
				else
				{
					pBlock->SetCol(NOTHIT_COL);	// �F�̕ύX
				}

			}
			pObj = pObjectNext;		// ���̃I�u�W�F�N�g����

		}
	}
	return bHit;
}
//======================================
// �X�R�A�̑�������
//======================================
bool CBaseBlockX::AddScore(D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepth)
{
	CSound*pSound = CManager::GetSound();

	bool bScoreAdd = false;
	int nScore = 0;
	int LScore = 0, RScore = 0, UScore = 0, DScore = 0;

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
				{
					CBreakBaseBlockX *pBlockbase = dynamic_cast<CBreakBaseBlockX*>(pObj);
				}

				CBlockX* pBlock = pBlockbase->GetBlock();

				D3DXVECTOR3 pos0, pos1, pos2, pos3;

				// �v�Z�ɕK�v�ȗv�f�����
				D3DXVECTOR3 Maxpos = pBlock->GetMaxpos();
				D3DXVECTOR3 Minpos = pBlock->GetMinpos();
				float fLength = pBlock->GetLength();
				float fAngle = pBlock->GetAngle();

				D3DXVECTOR3 rot = pBlockbase->GetRot();

				D3DXVECTOR3 Blockpos;

				Blockpos.x = pBlock->GetMtx()._41;
				Blockpos.y = pBlock->GetMtx()._42;
				Blockpos.z = pBlock->GetMtx()._43;

				// �����蔻��p�̒��_��ݒ�
				pos0.x = Blockpos.x - Maxpos.x;
				pos0.y = Blockpos.y + Maxpos.y;
				pos0.z = Maxpos.z + Blockpos.z;

				pos1.x = Blockpos.x + Maxpos.x;
				pos1.y = Blockpos.y + Maxpos.y;
				pos1.z = Minpos.z + Blockpos.z;

				pos2.x = Blockpos.x - Maxpos.x;
				pos2.y = Blockpos.y - Maxpos.y;
				pos2.z = Maxpos.z + Blockpos.z;

				pos3.x = Blockpos.x + Maxpos.x;
				pos3.y = Blockpos.y - Maxpos.y;
				pos3.z = Minpos.z + Blockpos.z;

				if (pos.z >= Blockpos.z && pBlockbase->GetDeath() == false)
				{
					if (pos.y + fHeight >= pos2.y &&
						pos.y - fHeight <= pos0.y &&
						pos.x + fWidth  <= Blockpos.x - Maxpos.x)
					{ // �v���C���[�E���̓����蔻��
						float fPlayerpos = pos.x;
						float ra = fPlayerpos - Blockpos.x;
						float fDistance = sqrt(ra * ra);
						if (RScore <= MAX_SCORE - fDistance * SCORE_MAG)
						{
							RScore = MAX_SCORE - fDistance * SCORE_MAG;
						}
					}
					else if (pos.y + fHeight >= pos2.y &&
						pos.y - fHeight <= pos0.y &&
						pos.x - fWidth >= Blockpos.x + Maxpos.x)
					{ // �v���C���[�̍����̓����蔻��
						float fPlayerpos = pos.x;
						float ra = Blockpos.x - fPlayerpos;
						float fDistance = sqrt(ra * ra);

						if (LScore <= MAX_SCORE - fDistance * SCORE_MAG)
						{
							LScore = MAX_SCORE - fDistance * SCORE_MAG;
						}
					}
					if (pos.x + fWidth + Correction >= pos0.x &&
						pos.x - fWidth - Correction <= pos1.x &&
						pos.y - fHeight >= Blockpos.y)
					{ // �v���C���[�̉����̓����蔻��
						float fPlayerpos = pos.y;
						float ra = Blockpos.y - fPlayerpos;
						float fDistance = sqrt(ra * ra);

						if (DScore <= MAX_SCORE - fDistance * SCORE_MAG)
						{
 							DScore = MAX_SCORE - fDistance  * SCORE_MAG;
						}
					}
					if (pos.x + fWidth + Correction >= pos0.x &&
						pos.x - fWidth + Correction <= pos1.x &&
						pos.y + fHeight <= Blockpos.y)
					{ // �v���C���[�㑤�̓����蔻��
						float fPlayerpos = pos.y;
						float ra = fPlayerpos - Blockpos.y;
						float fDistance = sqrt(ra * ra);

						if (UScore <= MAX_SCORE - fDistance * SCORE_MAG)
						{
							UScore = MAX_SCORE - fDistance * SCORE_MAG;
						}
					}
					pBlockbase->SetDeath();

				}
			}
			pObj = pObjectNext;		// ���̃I�u�W�F�N�g����
		}
	}
	nScore += UScore + DScore + RScore + LScore;
	// �p�[�e�B�N���̐���
	if (nScore > MAX_SCORE)
	{
		CParticle::Create(pos, D3DCOLOR_RGBA(255, 0, 0, 255));	// �p�[�e�B�N���̂̐���
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SCORE003);	// �T�E���h�̍Đ�
		bScoreAdd = true;		// �X�R�A���������悤�ɂ���
	}
	else if (nScore > MAX_SCORE / 2)
	{
		CParticle::Create(pos, D3DCOLOR_RGBA(255, 255, 0, 255));
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SCORE002);
		bScoreAdd = true;

	}
	else if (nScore > 0)
	{
		CParticle::Create(pos, D3DCOLOR_RGBA(255, 0, 255, 255));
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SCORE001);
		bScoreAdd = true;
	}
	CScore::AddScore(nScore);	// �X�R�A�̑���
	if (nScore > 0)
	{
		CAddScore::Create(D3DXVECTOR3(800.0f, 140.0f, 0.0f), nScore);	// �X�R�A�����̐���
	}
	return bScoreAdd;
}
//========================================
// �R���X�g���N�^
//========================================
CBreakBaseBlockX::CBreakBaseBlockX()
{
	CObject::SetType(TYPE_BREAKBLOCKBASE);

	m_nLife = 0;
}
//========================================
// �f�X�g���N�^
//========================================
CBreakBaseBlockX::~CBreakBaseBlockX()
{
}
//========================================
// ����������
//========================================
HRESULT CBreakBaseBlockX::Init(void)
{
	CBaseBlockX::Init();

	return S_OK;
}
//========================================
// �I������
//========================================
void CBreakBaseBlockX::Uninit(void)
{
	CBaseBlockX::Uninit();
	CObject::Relese();
}
//=======================================
// �X�V����
//=======================================
void CBreakBaseBlockX::Update(void)
{
	CBaseBlockX::Update();
}
//======================================
// �`�揈��
//======================================
void CBreakBaseBlockX::Draw(void)
{
	CBaseBlockX::Draw();
}
//======================================
// �ݒ菈��
//======================================
CBreakBaseBlockX *CBreakBaseBlockX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 Size)
{
	CBreakBaseBlockX *pModel;

	// �I�u�W�F�N�g3D�̐���
	pModel = new CBreakBaseBlockX();

	pModel->SetSize(Size);	// �T�C�Y�̐ݒ�

	pModel->SetPos(pos);	// �ʒu��ݒ�

	pModel->SetFile("data//MODEL//BreakBlock.x");	// �t�@�C�����̐ݒ�

	// ����������
	pModel->Init();

	int nId;

	// �����蔻��̃��C���̐���
	CCollisionLine::Create(D3DXVECTOR3(pModel->GetBlock()->GetPos().x, pModel->GetBlock()->GetPos().y, pModel->GetPos().z),
		D3DXVECTOR3(pModel->GetBlock()->GetMaxpos().x, pModel->GetBlock()->GetMaxpos().y, pModel->GetBlock()->GetMaxpos().z),
		&nId);
		
	// ���ʔԍ��̐ݒ�
	pModel->SetId(nId);
	return pModel;
}