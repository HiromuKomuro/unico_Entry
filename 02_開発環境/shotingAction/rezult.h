// =======================================================
//
// ���U���g����(Rezult.h)
// author KOMURO HIROMU
//
// =======================================================
// ��d�C���N���[�h�h�~
#ifndef _REZULT_H_
#define _REZULT_H_

#include"main.h"
#include"Manager.h"

class CRankingManager;
class CScore;

//---------------------------------------------------------------------------
//					*****			�}�l�[�W���[�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CRezult:public CScene
{
public:
	CRezult();
	~CRezult();

	HRESULT Init(void);		// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

	static CRankingManager *GetRankingManager(void) { return s_pRankingmanager; }	// �����L���O�Ǘ��̎擾
	static CScore *GetScore(void) { return s_pScore; }		// �X�R�A�̎擾����

private:
	static CRankingManager * s_pRankingmanager;		// �����L���O�Ǘ��̃|�C���^
	static CScore* s_pScore;
};
#endif
