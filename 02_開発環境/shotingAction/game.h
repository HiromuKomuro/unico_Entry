// =======================================================
//
// �Q�[������(game.h)
// author KOMURO HIROMU
//
// =======================================================
// ��d�C���N���[�h�h�~
#ifndef _GAME_H_
#define _GAME_H_

#include"Manager.h"
class CScore;
//---------------------------------------------------------------------------
//					*****			�}�l�[�W���[�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CGame:public CScene
{
public:
	CGame();
	~CGame();

	HRESULT Init(void);		// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

	static CBlockManager *GetCBlockManager(void) { return s_pBlockManager; }	// �u���b�N�Ǘ��̎擾����
	static CScore *GetScore(void) { return s_pScore; }		// �X�R�A�̎擾����
	static bool GetPause(void) { return m_bPause; }			// �|�[�Y��Ԃ̓���

private:
	static CBlockManager* s_pBlockManager;
	static CScore* s_pScore;
	static bool m_bPause;				// �|�[�Y

};
#endif
