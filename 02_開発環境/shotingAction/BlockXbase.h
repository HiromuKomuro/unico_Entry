//====================================================================
//
//�u���b�N�̊�b�ʒu�̏���[BlockXbase.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _BLOCKXBASE_H_		//���̃}�N����`������ĂȂ�������

#define _BLOCKXBASE_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

// �}�N����`
#define MAX_BLOCK	(1)
#include"object.h"
#include"BlockX.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CBaseBlockX: public CObject
{
public:
	CBaseBlockX();
	~CBaseBlockX();

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }			// �ʒu�̐ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; }				// �ʒu���̓���

	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }			// �����̐ݒ�
	void SetRotAdd(D3DXVECTOR3 rot) { m_rot += rot; }		// �����̌��Z�ݒ�
	D3DXVECTOR3 GetRot(void) { return m_rot; }				// �����������

	void SetSize(D3DXVECTOR3 size) { m_Size = size; }		// �T�C�Y�̐ݒ�
	D3DXVECTOR3 GetSize(void) { return m_Size; }			// �T�C�Y���̓���

	int GetId(void) { return m_nId; }						// ���ʔԍ��̓���
	void SetId(int id) { m_nId = id; }						// ���ʔԍ��̐ݒ�

	void SetFile(char *pFilename) { m_pFilename = pFilename; }	// �t�@�C���̐ݒ�
	char *GetFile(void) { return m_pFilename; }					// �t�@�C�����̓���

	CBlockX *GetBlock(void) { return m_apModel; }			// �u���b�N�̏������

	D3DXMATRIX Getmtx(void) { return m_mtxWorld; }	// �}�g���b�N�X�̎擾

	void SetDeath(void) { m_bDeath = true; }		// ���S�t���O���m��
	bool GetDeath(void) { return m_bDeath; }		// ���S�t���O�����
	static CBaseBlockX*Create(D3DXVECTOR3 pos, D3DXVECTOR3 Size);	// ���f���I�u�W�F�N�g�̐���

	static bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 pRot, float fWidth, float fHeight, float fDepth,bool bBullet,bool bPlayer);	// �ǂƂ̓����蔻��
	static bool  AddScore(D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepth);				// �X�R�A�̑���

private:
		D3DXMATRIX m_mtxWorld;			// ���[���h�}�g���b�N�X
		D3DXVECTOR3 m_pos;				// �ʒu
		D3DXVECTOR3 m_posOld;			// �O�̈ʒu
		D3DXVECTOR3 m_move;				// �ړ���
		D3DXVECTOR3 m_rot;				// ����		
		D3DXVECTOR3 m_rotmove;			// �����ړ���		
		D3DXVECTOR3 m_Size;				// ���f���̃T�C�Y
		CBlockX *m_apModel;				// ���f���ւ̃|�C���^
		int m_nNumModel;				// ���f���̑���	

		int m_nId;			// ���ʔԍ�	
		char* m_pFilename;	// �t�@�C����
		bool m_bDeath;		// ���S�t���O
};
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CBreakBaseBlockX : public CBaseBlockX
{
public:
	CBreakBaseBlockX();
	~CBreakBaseBlockX();

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetLife(void) { return m_nLife; }			// ���C�t�̓���
	void SetLife(int nLife) { m_nLife = nLife; }	// ���C�t�̐ݒ�

	static CBreakBaseBlockX*Create(D3DXVECTOR3 pos, D3DXVECTOR3 Size);	// ���f���I�u�W�F�N�g�̐���

private:
	int m_nLife;		// ���C�t
};

#endif
