//====================================================================
//
//���[�V��������[motion.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _MOTION_H_		//���̃}�N����`������ĂȂ�������

#define _MOTION_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

class CObjectModel;
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CMotion
{
public:

	// �L�[�̍\����
	typedef struct
	{
		float fPosx;	// �ʒuX
		float fPosy;	// �ʒuY
		float fPosz;	// �ʒuZ
		float fRotx;	// ����X
		float fRoty;	// ����Y
		float fRotz;	// ����Z
	}KEY;

	// �L�[�C���t�H�̍\����
	typedef struct 
	{
		int nFrame;
		KEY Key[64];
	}KEY_INFO; 

	// �C���t�H�̍\����
	typedef struct
	{
		KEY_INFO aKeyInfo[64];

	}INFO;

	CMotion();
	~CMotion();
	void Set(int nType);
	void Update(void);
	int GetType(void) { return m_nType; }
	bool bFinish(void) { return m_bFinish; }
	void SetInfo(INFO info);
	void SetModel(CObjectModel**ppObjectModel, int nNumModel);

private:
	INFO m_aInfo[64];
	int m_nNumAll;
	int m_nType;
	bool m_bLoop;
	int m_nNumKey;
	int m_nKey;
	int m_nCounter;
	bool m_bFinish;	// �I���������ǂ���

	CObjectModel** m_ppObjectModel;		// ���f���̃|�C���^
	int m_nNumModel;
};
#endif