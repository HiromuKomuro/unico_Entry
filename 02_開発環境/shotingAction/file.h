//====================================================================
//
//ファイル処理[filel.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _FILE_H_		//このマクロ定義がされてなかったら

#define _FILE_H_		//二重インクルード防止のマクロを定義する

#include"object.h"
#include"BlockManager.h"
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CFile
{
public:
	// 種類
	typedef enum
	{
		TYPE_BLOCK = 0,
		TYPE_SCORE,
		TYPE_MAX
	}TYPE;

	CFile();
	~CFile();

	//メンバ関数
	static HRESULT MapLoad(const char *pFilename,TYPE type, CBlockManager::Wave*pWave,int *pNumSummon);	// マップロード処理
	static HRESULT Write(const char *pFilename, TYPE type,int nScore);		// 書き込み処理
	static HRESULT ScoreLoad(const char *pFilename,int *pScore,bool bMyScore);			// スコア読み込み処理


private:
	int m_nNum;	// 最大数
	D3DXVECTOR3 m_pos;	// 位置
};
#endif

