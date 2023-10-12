//====================================================================
//
//モーション処理[motion.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _MOTION_H_		//このマクロ定義がされてなかったら

#define _MOTION_H_		//二重インクルード防止のマクロを定義する

class CObjectModel;
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CMotion
{
public:

	// キーの構造体
	typedef struct
	{
		float fPosx;	// 位置X
		float fPosy;	// 位置Y
		float fPosz;	// 位置Z
		float fRotx;	// 向きX
		float fRoty;	// 向きY
		float fRotz;	// 向きZ
	}KEY;

	// キーインフォの構造体
	typedef struct 
	{
		int nFrame;
		KEY Key[64];
	}KEY_INFO; 

	// インフォの構造体
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
	bool m_bFinish;	// 終了したかどうか

	CObjectModel** m_ppObjectModel;		// モデルのポインタ
	int m_nNumModel;
};
#endif