//====================================================================
//
// �^�C�g���Ǘ�����[TitleManager.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _TITLEMANAGER_H_		//���̃}�N����`������ĂȂ�������

#define _TITLEMANAGER_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

#define  MAX_WAVE	(64)
#include"main.h"

class CStartBg;
class CTutorialBg;
class CEndBg;
class CTutorial;
class CObject2D;
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CTitleManager
{
public:
	// �^�C�g����
	typedef enum
	{
		TITLE_NONE = 0,
		TITLE_END,
		TITLE_START,
		TITLE_TUTORIAL,
		TITLE_MAX
	}TITLE_SELECT;

	CTitleManager();
	~CTitleManager();

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	static CStartBg *GetStartBg(void) { return s_pStartBg; }			// �X�^�[�g�w�i�̓���
	static CTutorialBg *GetTutorialBg(void) { return s_pTutorialBg; }	// �X�^�[�g�w�i�̓���
	static CEndBg *GetEndBg(void) { return s_pEndBg; }					// �I���w�i�̓���
	static CTutorial *GetTutorial(void) { return s_pTutorial; }			// �`���[�g���A���̓���

private:
	static CStartBg *s_pStartBg;			// �X�^�[�g�w�i�̃|�C���^
	static CTutorialBg  *s_pTutorialBg;	// �`���[�g���A���w�i�̃|�C���^
	static CEndBg  *s_pEndBg;				// �I���w�i�̃|�C���^
	static CTutorial *s_pTutorial;		// �`���[�g���A���̃|�C���^
	TITLE_SELECT m_TitleSelect;			// �^�C�g���̏��
	int m_nCounterSelect;				// �I���J�E���^�[

};
#endif