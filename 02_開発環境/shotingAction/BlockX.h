 //====================================================================
//
//�u���b�NX����[BlockX.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _BLOCKX_H_		//���̃}�N����`������ĂȂ�������

#define _BLOCKX_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

#include"Model.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CBlockX
{
public:
	CBlockX();
	~CBlockX();

	//�����o�֐�
	HRESULT Init(const char* pFilename);
	void Uninit(void);
	void Update(void);
	void Draw(D3DXMATRIX mtxPar);

	void SetVector(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }			// �ʒu�̐ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; }				// �ʒu���̓���

	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }			// �����̐ݒ�
	D3DXVECTOR3 GetRot(void) { return m_rot; }				// �����������

	void SetCol(D3DXCOLOR col) { m_col = col; }				//�@�F�̐ݒ�
	D3DXCOLOR GetCol(void) { return m_col; }				//  �F�̓���

	void SetType(int nType) { m_nType = nType; }			// ��ނ̐ݒ�
	int GetType(void) { return m_nType; }					// ��ނ̓���

	void SetSize(D3DXVECTOR3 size) { m_Size = size; }		// �T�C�Y�̐ݒ�
	D3DXVECTOR3 GetSize(void) { return m_Size; }			// �T�C�Y���̓���

	D3DXMATRIX GetMtx(void) { return m_mtxWorld; }		// �}�g���b�N�X�̎擾
	void SetParent(CBlockX*pBlockX) { m_aParent = pBlockX; }	// �e���f���̐ݒ�

	D3DXVECTOR3 GetMaxpos(void) { return m_Maxpos; }	// ���f���̍ő�ʒu�����
	D3DXVECTOR3 GetMinpos(void) { return m_Minpos; }	// ���f���̍ŏ��ʒu�����

	float GetLength(void) { return m_fLength; }	// �Ίp���̒��������
	float GetAngle(void) { return m_fAngle; }	// �Ίp���̊p�x�����

	static CBlockX*Create(D3DXVECTOR3 pos,const char* pFilename,D3DXVECTOR3 Size);	// ���f���I�u�W�F�N�g�̐���


private:
	LPD3DXMESH m_pMesh;				//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;		//�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;				//�}�e���A���̐�
	WORD m_SizeFVF;					// �o�b�t�@�̃T�C�Y
	BYTE *m_pVertex;				// ���_���
	D3DXVECTOR3 *m_pPos;			// ���_���̈ʒu
	D3DXVECTOR3 m_pos;				// �ʒu	
	D3DXVECTOR3 m_rot;				// ����
	D3DXCOLOR	m_col;				// �F
	D3DXVECTOR3 m_Size;				// ���f���̃T�C�Y
	D3DXMATRIX m_mtxWorld;			// ���[���h�}�g���b�N�X
	CBlockX* m_aParent;				// �e���f���̃|�C���^
	int*m_nIdxTexture;				// �e�N�X�`���̑���

	D3DXVECTOR3 m_Maxpos;	// �ő�̈ʒu
	D3DXVECTOR3 m_Minpos;	// �ŏ��̈ʒu

	float m_fLength;	// �Ίp���̒���
	float m_fAngle;		// �Ίp���̊p�x

	int m_nType;		// ���

};
#endif
