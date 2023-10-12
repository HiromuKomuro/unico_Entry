// =======================================================
//
// �I�u�W�F�N�g����(object.cpp)
// author KOMURO HIROMU
//
// =======================================================
#include "object.h"
#include"main.h"
#include"renderer.h"
#include"Camera.h"
#include"Manager.h"

// �ÓI�����o�ϐ��錾
CObject *CObject::m_pTop[PRIORITY_MAX] = {};
CObject *CObject::m_pCur[PRIORITY_MAX] = {};

//====================================
// �R���X�g���N�^
//====================================
CObject::CObject(int nPriority)
{
	if (m_pTop[nPriority] == NULL)
	{// �擪�̃A�h���X���g���Ă��Ȃ��Ƃ�

		m_pTop[nPriority] = this;				// �擪�̃A�h���X�Ɏ��g����

		// ���ƑO�̃I�u�W�F�N�g��NULL�ɂ���
		this->m_pNext = NULL;
		this->m_pPrev = NULL;
	}
	else
	{// �擪�̃A�h���X�����݂���Ƃ�

		this->m_pPrev = m_pCur[nPriority];			// �擪�̃A�h���X��O�̃A�h���X�ɑ��

		m_pCur[nPriority]->m_pNext = this;			// �O�̃A�h���X�̎��̃A�h���X�����g�ɑ��

		// ���̃I�u�W�F�N�g�̃A�h���X��NULL�ɂ���
		this->m_pNext = NULL;

	}

	m_pCur[nPriority] = this;		// �Ō���̃A�h���X�Ɏ��g����

	m_nPriority = nPriority;		// �`��̗D��x��ݒ�
	m_bDeath = false;	// ���S�t���O�̏�����

}
//====================================
// �f�X�g���N�^
//====================================
CObject::~CObject()
{
}
//====================================
// �S�I�u�W�F�N�g�̏I������
//====================================
void CObject::ReleseAll(void)
{
	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		CObject*pObject = m_pTop[nCntPri];	// �擪�̃I�u�W�F�N�g����

		while (pObject != NULL)
		{
			CObject*pObjectNext = pObject->m_pNext;		// ���̃I�u�W�F�N�g��ۑ�

			pObject->Uninit();

			// �폜����
			pObject->Delete(nCntPri);

			pObject = pObjectNext;	// ���̃I�u�W�F�N�g����
		}
	}
}
//====================================
// �S�I�u�W�F�N�g�̍X�V����
//====================================
void CObject::UpdateAll(void)
{
	CCamera*pCamera = CManager::GetCCamera();
	
	pCamera->Update();	// �J�����̍X�V����

	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		CObject*pObject = m_pTop[nCntPri];	// �擪�̃I�u�W�F�N�g����

		while (pObject != NULL)
		{
			CObject*pObjectNext = pObject->m_pNext;		// ���̃I�u�W�F�N�g��ۑ�

			// �X�V����
			if (!pObject->m_bDeath)
				pObject->Update();

			pObject = pObjectNext;	// ���̃I�u�W�F�N�g����
		}
	}

	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		CObject*pObject = m_pTop[nCntPri];	// �擪�̃I�u�W�F�N�g����

		while (pObject != NULL)
		{
			CObject*pObjectNext = pObject->m_pNext;		// ���̃I�u�W�F�N�g��ۑ�

			// �폜����
			pObject->Delete(nCntPri);

			pObject = pObjectNext;	// ���̃I�u�W�F�N�g����
		}
	}
}
//====================================
// �S�I�u�W�F�N�g�̕`�揈��
//====================================
void CObject::DrawAll(void)
{
	CCamera*pCamera = CManager::GetCCamera();

	pCamera->SetCamera();	// �J�����̐ݒ�

	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		CObject*pObject = m_pTop[nCntPri];	// �擪�̃I�u�W�F�N�g����

		while (pObject != NULL)
		{
			CObject*pObjectNext = pObject->m_pNext;		// ���̃I�u�W�F�N�g��ۑ�

			// �`�揈��
			pObject->Draw();

			pObject = pObjectNext;	// ���̃I�u�W�F�N�g����
		
		}
	}

}
//====================================
// �I�u�W�F�N�g�̔j������
//====================================
void CObject::Relese(void)
{
	m_bDeath = true;	// ���S�t���O��L���ɂ���
}
//====================================
// �I�u�W�F�N�g�̍폜����
//====================================
void CObject::Delete(int nPriority)
{
	if (m_bDeath == true)
	{// ���S�t���O���F�D�̎�

		if (m_pPrev != NULL && m_pNext != NULL)
		{
			m_pNext->m_pPrev = m_pPrev;		// ���g�̎��̃A�h���X�̑O�̃A�h���X�����g�̑O�̃A�h���X�ɑ��
			m_pPrev->m_pNext = m_pNext;
		}
		else if (m_pPrev == NULL && m_pNext != NULL)
		{
			m_pTop[nPriority]  = m_pNext;	// �擪�̃A�h���X�ɂ���
			m_pNext->m_pPrev = NULL;
		}
		else if (m_pNext == NULL && m_pPrev != NULL)
		{
			m_pCur[nPriority] = m_pPrev;
			m_pPrev->m_pNext = NULL;
		}
		else
		{
			m_pTop[nPriority] = NULL;
			m_pCur[nPriority] = NULL;
		}
	
		// �C���X�^���X�̊J��
		delete this;

	}
}