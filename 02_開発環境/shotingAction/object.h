// =======================================================
//
// �I�u�W�F�N�g����(object.h)
// author KOMURO HIROMU
//
// =======================================================
// ��d�C���N���[�h�h�~
#ifndef _OBJECT_H_
#define _OBJECT_H_

// �}�N����`
#define PRIORITY_MAX	(8)		// �`��̗D�揇�ʂ̍ő吔
#define ROT_TRANS	(0.03f)	// ��]����l
#include"main.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CObject
{
public:	//�A�N�Z�X�w��q
	// �I�u�W�F�N�g�̎��
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

	virtual HRESULT Init(void) =0;		// ����������
	virtual void Uninit(void) = 0;		// �I������
	virtual void Update(void) = 0;		// �X�V����
	virtual void Draw(void) = 0;			// �`�揈��

	static void ReleseAll(void);	// �S�I�u�W�F�N�g�̏I������
	static void UpdateAll(void);	// �S�I�u�W�F�N�g�̍X�V����
	static void DrawAll(void);		// �S�I�u�W�F�N�g�̕`�揈��

	void Delete(int nPriority);				// �폜����

	TYPE GetType(void) { return m_type; }	// ��ނ����
	void SetType(TYPE type) { m_type = type; }	// ��ނ�ݒ�

	static CObject *GetTop(int nPriority) { return m_pTop[nPriority]; }		// �擪�̃I�u�W�F�N�g�������
	CObject *GetNext(void) { return m_pNext; }								// ���̃I�u�W�F�N�g�̏������

protected:
	void Relese(void);
private:
	static CObject*m_pTop[PRIORITY_MAX];	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CObject*m_pCur[PRIORITY_MAX];	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	CObject* m_pPrev;						// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject* m_pNext;						// ���̃I�u�W�F�N�g�ւ̃|�C���^
	TYPE m_type;			// ���
	int m_nPriority;		// �`��̗D�揇��
	bool m_bDeath;			// ���S�t���O
};
#endif