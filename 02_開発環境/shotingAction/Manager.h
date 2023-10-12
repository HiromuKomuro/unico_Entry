// =======================================================
//
// �}�l�[�W���[����(Manager.h)
// author KOMURO HIROMU
//
// =======================================================
// ��d�C���N���[�h�h�~
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include"main.h"
#include"Object.h"
class CRenderer;
class CInputKeyboard;
class CPlayer;
class CBullet;
class CSound;
class CLight;
class CCamera;
class CTexture;
class CBlockManager;
class CFade;
//---------------------------------------------------------------------------
//					*****			���[�h�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CScene
{
public:
	CScene();
	~CScene();

	enum MODE
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_REZULT,
		MODE_MAX
	};
	static CScene * Create(MODE mode);

	virtual HRESULT Init(void) = 0;			// ����������
	virtual void Uninit(void) = 0;			// �I������
	virtual void Update(void) = 0;			// �X�V����
	virtual void Draw(void) = 0;			// �`�揈��

	MODE GetMode(void) { return m_mode; }	// ���[�h�̎擾
	void SetMode(MODE mode) { m_mode = mode; }	// ���[�h�̐ݒ�
private:
	MODE m_mode;			// ���[�h�̎��
};

//---------------------------------------------------------------------------
//					*****			�}�l�[�W���[�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CManager
{
public:
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);		// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

	static CRenderer *GetRenderer(void) { return m_pRenderer; }					// �����_���[�̎擾����
	static CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }	// �L�[�{�[�h�̎擾����
	static CSound *GetSound(void) { return m_pSound; }							// �T�E���h�̎擾����
	static CLight *GetCLight(void) { return m_pLight; }							// ���C�g�̎擾����
	static CCamera *GetCCamera(void) { return m_pCamera; }						// �J�����̎擾����
	static CTexture *GetCTexture(void) { return m_pTexture; }					// �e�N�X�`���̎擾����
	static CBlockManager *GetCBlockManager(void) { return m_pBlockManager; }	// �u���b�N�Ǘ��̎擾����
	static CFade *GetCFade(void) { return s_pFade; }							// �t�F�C�h�̎擾����
	static CScene *GetCScene(void) { return s_pScene; }							// �V�[���̎擾����

	static void SetMode(CScene::MODE mode);					// ���[�h�̐ݒ�
private:
	static CRenderer*m_pRenderer;
	static CInputKeyboard*m_pInputKeyboard;
	static CSound* m_pSound;
	static CLight* m_pLight;
	static CCamera* m_pCamera;
	static CTexture* m_pTexture;
	static CBlockManager* m_pBlockManager;
	static CScene *s_pScene;
	static CFade *s_pFade;

};
#endif
