//====================================================================
//
//�����L���O�Ǘ�����[RankingManager.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _RANKINGMANAGER_H_		//���̃}�N����`������ĂȂ�������

#define _RANKINGMANAGER_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

#define MAX_SCORE	(3)
#include"Score.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CRankingManager
{
public:
	CRankingManager();
	~CRankingManager();

	//�����o�֐�
	HRESULT Init(int *pScore);
	void Uninit(void);
	void Update(void);


private:
	CRankScore m_aScore[MAX_SCORE];		// �X�R�A�̍\����

};
#endif