// =======================================================
//
// オブジェクト処理(object.h)
// author KOMURO HIROMU
//
// =======================================================
// 二重インクルード防止
#ifndef _OBJECT_H_
#define _OBJECT_H_

// マクロ定義
#define PRIORITY_MAX	(8)		// 描画の優先順位の最大数
#define ROT_TRANS	(0.03f)	// 回転する値
#include"main.h"
//---------------------------------------------------------------------------
//					*****			オブジェクトクラスの定義			*****
//---------------------------------------------------------------------------
class CObject
{
public:	//アクセス指定子
	// オブジェクトの種類
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,
		TYPE_ENEMY,
		TYPE_BULLET,
		TYPE_BLOCK,
		TYPE_BLOCKBASE,
		TYPE_BREAKBLOCKBASE,
		TYPE_BLOCKX,
		TYPE_FILED,
		TYPE_MESHFILED,
		TYPE_WALL,
		TYPE_THROUGHWALL,
		TYPE_XMODEL,
		TYPE_ITEM,
		TYPE_MAX
	}TYPE;
	CObject(int nPriority = 3);
	virtual ~CObject();

	virtual HRESULT Init(void) =0;		// 初期化処理
	virtual void Uninit(void) = 0;		// 終了処理
	virtual void Update(void) = 0;		// 更新処理
	virtual void Draw(void) = 0;			// 描画処理

	static void ReleseAll(void);	// 全オブジェクトの終了処理
	static void UpdateAll(void);	// 全オブジェクトの更新処理
	static void DrawAll(void);		// 全オブジェクトの描画処理

	void Delete(int nPriority);				// 削除処理

	TYPE GetType(void) { return m_type; }	// 種類を入手
	void SetType(TYPE type) { m_type = type; }	// 種類を設定

	static CObject *GetTop(int nPriority) { return m_pTop[nPriority]; }		// 先頭のオブジェクト情報を入手
	CObject *GetNext(void) { return m_pNext; }								// 次のオブジェクトの情報を入手

protected:
	void Relese(void);
private:
	static CObject*m_pTop[PRIORITY_MAX];	// 先頭のオブジェクトへのポインタ
	static CObject*m_pCur[PRIORITY_MAX];	// 最後尾のオブジェクトへのポインタ
	CObject* m_pPrev;						// 前のオブジェクトへのポインタ
	CObject* m_pNext;						// 次のオブジェクトへのポインタ
	TYPE m_type;			// 種類
	int m_nPriority;		// 描画の優先順位
	bool m_bDeath;			// 死亡フラグ
};
#endif