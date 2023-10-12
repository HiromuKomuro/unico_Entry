// =======================================================
//
// �X�R�A����(score.h)
// author KOMURO HIROMU
//
// =======================================================
// ��d�C���N���[�h�h�~
#ifndef _SCORE_H_
#define _SCORE_H_

#include"main.h"
#include"Object.h"
// �}�N����`
#define NUM_SCOREPLACE		(8)			//�X�R�A�̌���
//---------------------------------------------------------------------------
//					*****			�O���錾			*****
//---------------------------------------------------------------------------
class CNumber;
//---------------------------------------------------------------------------
//					*****			�X�R�A�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CScore
{
public:
	CScore();
	~CScore(); 

	HRESULT Init(D3DXVECTOR3 pos);		// ����������
	void Uninit(void);					// �I������
	void Update(void);					// �X�V����
	void Draw(void);					// �`�揈��

	static void SetScore(int nScore);	// �X�R�A�̐ݒ�
	static void AddScore(int nValue);	// �X�R�A�̉��Z����

	static int GetScore(void) { return m_nScore; }		// �X�R�A�̓��菈��

	void Setpos(D3DXVECTOR3 pos) { m_pos = pos; }		// �ʒu�̐ݒ�
	static CScore *Create(const D3DXVECTOR3 pos);		// �I�u�W�F�N�g�̐�������

private:
	static CNumber *m_apNumber[NUM_SCOREPLACE];			// �����̃|�C���^�[
	static int m_nScore;								// �X�R�A�̒l
	D3DXVECTOR3 m_pos;									// �ʒu
};
//---------------------------------------------------------------------------
//					*****			�X�R�A�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CAddScore : public CObject
{
public:
	CAddScore();
	~CAddScore();

	HRESULT Init(void);					// ����������
	void Uninit(void);					// �I������
	void Update(void);					// �X�V����
	void Draw(void);					// �`�揈��

	void SetScore(int nScore);	// �X�R�A�̐ݒ�

	void Setpos(D3DXVECTOR3 pos) { m_pos = pos; }		// �ʒu�̐ݒ�

	static CAddScore *Create(const D3DXVECTOR3 pos,const int score);		// �I�u�W�F�N�g�̐�������

private:
	CNumber *m_apNumber[NUM_SCOREPLACE];			// �����̃|�C���^�[
	int m_nScore;								// �X�R�A�̒l
	D3DXVECTOR3 m_pos;									// �ʒu
	D3DXVECTOR3 m_move;									// �ړ�
	int m_nAnimeCounter;								// �A�j���[�V�����J�E���^�[
	int m_nScoreCnt;									// �X�R�A�J�E���^�[
};
//---------------------------------------------------------------------------
//					*****		�����L���O�X�R�A�N���X�̒�`		*****
//---------------------------------------------------------------------------
class CRankScore :public CObject
{
public:
	CRankScore();
	~CRankScore();

	HRESULT Init(void);					// ����������
	void Uninit(void);					// �I������
	void Update(void);					// �X�V����
	void Draw(void);					// �`�揈��

	void SetScore(int score);	// �X�R�A�̐ݒ�

	void Setpos(D3DXVECTOR3 pos) { m_pos = pos; }		// �ʒu�̐ݒ�
	static CRankScore *Create(const D3DXVECTOR3 pos, const int score);		// �I�u�W�F�N�g�̐�������


private:
	CNumber *m_apNumber[NUM_SCOREPLACE];			// �����̃|�C���^�[
	int m_nScore;									// �X�R�A�̒l
	D3DXVECTOR3 m_pos;								// �ʒu
};
#endif