//====================================================================
//
//�u���b�N�Ǘ�����[BlockManager.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _BLOCKMANAGER_H_		//���̃}�N����`������ĂȂ�������

#define _BLOCKMANAGER_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

#define  MAX_WAVE	(64)
#include"main.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CBlockManager
{
public:
	// �u���b�N�̍\����
	typedef struct
	{
		D3DXVECTOR3 pos;	// �ʒu
		int nType;			// ���
	}Block;

	// �E�F�[�u�̍\����
	typedef struct
	{
		Block block[MAX_WAVE];	// �u���b�N�̍\����
		int nNumBlock;		// �u���b�N�̑���
	}Wave;

	CBlockManager();
	~CBlockManager();

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);


private:
	Wave m_aWave[MAX_WAVE];		// �E�F�[�u�̍\����
	int m_nCounterSummon;	// �����J�E���^�[
	int m_nNumSummon;		// ������������
	float m_posZ;			// �ʒu

};
#endif