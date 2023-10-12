//====================================================================
//
//�����蔻��̃��C������[collisionline.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _COLLISIONLINE_H_		//���̃}�N����`������ĂȂ�������

#define _COLLISIONLINE_H_		//��d�C���N���[�h�h�~�̃}�N�����`����
#include"object.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CCollisionLine : public CObject
{
public:
	CCollisionLine();
	~CCollisionLine();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }			// �ʒu�̐ݒ�
	void SetPosAdd(D3DXVECTOR3 pos) { m_pos += pos; }		// �ʒu�̉��Z�ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; }				// �ʒu���̓���

	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }			// �����̐ݒ�
	void SetRotAdd(D3DXVECTOR3 rot) { m_rot += rot; }		// �����̌��Z�ݒ�
	D3DXVECTOR3 GetRot(void) { return m_rot; }				// �����������

	void SetSize(D3DXVECTOR3 size) { m_size = size; }		// �T�C�Y�̐ݒ�
	D3DXVECTOR3 GetSize(void) { return m_size; }			// �T�C�Y�̎擾

	void SetCol(const D3DCOLOR col);						//�@�F�̐ݒ�

	static int GetId(void) { return m_nNumLine; }				// ���ʔԍ��̓���

	static CCollisionLine * Create(D3DXVECTOR3 pos,D3DXVECTOR3 size,int *nId);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@�̃|�C���^
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;					// �ʒu	
	D3DXVECTOR3 m_rot;					// ����	
	D3DCOLOR m_col;						// �F
	D3DXVECTOR3 m_size;					// �傫��
	static int m_nNumLine;				// ���C���̑���
	int m_nId;							// ���ʔԍ�
};
#endif
