//====================================================================
//
//�t�F�[�h����[Fade.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _FADE_H_		//���̃}�N����`������ĂȂ�������
#define _FADE_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

#include "Manager.h"
//---------------------------------------------------------------------------
//					*****			�t�F�[�h�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CFade
{
public:
	//�t�F�[�h�̏��
	typedef enum
	{
		FADE_NONE = 0,		//�������Ă��Ȃ����
		FADE_IN,			//�t�F�[�h�C�����
		FADE_OUT,			//�t�F�[�h�A�E�g���
		FADE_MAX
	}FADE;

	CFade();
	~CFade();

	HRESULT Init(CScene::MODE modeNext);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(CScene::MODE modeNext);
	FADE Get(void) { return m_fade; };
private:
	static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuff;	//���_�o�b�t�@�̃|�C���^
	FADE m_fade;									//�t�F�[�h�̏��
	CScene::MODE m_modeNext;						//���̉��(���[�h)
	D3DXCOLOR m_colorFade;							//�|���S��(�t�F�[�h)�̐F
};
#endif
