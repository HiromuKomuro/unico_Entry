//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : KOMURO HIROMU
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_
#include"xaudio2.h"				//�T�E���h�����ɕK�v



class CSound
{
public:

	// �T�E���h�ꗗ
	typedef enum
	{
		SOUND_LABEL_SE_ATTCAK,		// �U����
		SOUND_LABEL_SE_SCORE001,	// �X�R�A001
		SOUND_LABEL_SE_SCORE002,	// �X�R�A002
		SOUND_LABEL_SE_SCORE003,	// �X�R�A003
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//*****************************************************************************
	// �T�E���h���̍\���̒�`
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDINFO;

	SOUNDINFO g_aSoundInfo[SOUND_LABEL_MAX] =
	{
		{ "data/SE/shot200.wav", 0 },		// �U���̌��ʉ�
		{ "data/SE/powerup01.wav", 0 },		// �X�R�A001�̌��ʉ�
		{ "data/SE/powerup02.wav", 0 },		// �X�R�A002�̌��ʉ�
		{ "data/SE/powerup03.wav", 0 },		// �X�R�A003�̌��ʉ�
	};

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private:
	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y	
};

#endif
