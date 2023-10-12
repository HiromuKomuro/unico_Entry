// =======================================================
//
// �X�R�A����(score.h)
// author KOMURO HIROMU
//
// =======================================================
// ��d�C���N���[�h�h�~
#ifndef _RESULTSCORE_H_
#define _RESULTSCORE_H_

#include"main.h"
// �}�N����`
#define NUM_SCOREPLACE		(8)			//�X�R�A�̌���
//---------------------------------------------------------------------------
//					*****			�O���錾			*****
//---------------------------------------------------------------------------
class CNumber;
//---------------------------------------------------------------------------
//					*****			�G�l�~�[�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CResultScore
{
public:
	CResultScore();
	~CResultScore();

	HRESULT Init(D3DXVECTOR3 pos);		// ����������
	void Uninit(void);					// �I������
	void Update(void);					// �X�V����
	void Draw(void);					// �`�揈��

	static void SetScore(int nScore);	// �X�R�A�̐ݒ�
	static void AddScore(int nValue);	// �X�R�A�̉��Z����

	static int GetScore(void) { return m_nScore; }		// �X�R�A�̓��菈��

	static CResultScore *Create(const D3DXVECTOR3 pos);		// �I�u�W�F�N�g�̐�������

private:
	static CNumber *m_apNumber[NUM_SCOREPLACE];			// �����̃|�C���^�[
	static int m_nScore;								// �X�R�A�̒l
};
#endif