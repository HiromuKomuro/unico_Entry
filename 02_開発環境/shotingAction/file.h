//====================================================================
//
//�t�@�C������[filel.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _FILE_H_		//���̃}�N����`������ĂȂ�������

#define _FILE_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

#include"object.h"
#include"BlockManager.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CFile
{
public:
	// ���
	typedef enum
	{
		TYPE_BLOCK = 0,
		TYPE_SCORE,
		TYPE_MAX
	}TYPE;

	CFile();
	~CFile();

	//�����o�֐�
	static HRESULT MapLoad(const char *pFilename,TYPE type, CBlockManager::Wave*pWave,int *pNumSummon);	// �}�b�v���[�h����
	static HRESULT Write(const char *pFilename, TYPE type,int nScore);		// �������ݏ���
	static HRESULT ScoreLoad(const char *pFilename,int *pScore,bool bMyScore);			// �X�R�A�ǂݍ��ݏ���


private:
	int m_nNum;	// �ő吔
	D3DXVECTOR3 m_pos;	// �ʒu
};
#endif

