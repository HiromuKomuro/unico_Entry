//=============================================================================
//
// サウンド処理 [sound.h]
// Author : KOMURO HIROMU
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_
#include"xaudio2.h"				//サウンド処理に必要



class CSound
{
public:

	// サウンド一覧
	typedef enum
	{
		SOUND_LABEL_SE_ATTCAK,		// 攻撃音
		SOUND_LABEL_SE_SCORE001,	// スコア001
		SOUND_LABEL_SE_SCORE002,	// スコア002
		SOUND_LABEL_SE_SCORE003,	// スコア003
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//*****************************************************************************
	// サウンド情報の構造体定義
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDINFO;

	SOUNDINFO g_aSoundInfo[SOUND_LABEL_MAX] =
	{
		{ "data/SE/shot200.wav", 0 },		// 攻撃の効果音
		{ "data/SE/powerup01.wav", 0 },		// スコア001の効果音
		{ "data/SE/powerup02.wav", 0 },		// スコア002の効果音
		{ "data/SE/powerup03.wav", 0 },		// スコア003の効果音
	};

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private:
	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ	
};

#endif
