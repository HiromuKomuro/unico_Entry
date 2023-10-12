//====================================================================
//
//���b�V���V�����_�[����[MeshCylinder.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _MESHCYLINDER_H_		//���̃}�N����`������ĂȂ�������

#define _MESHCYLINDER_H_		//��d�C���N���[�h�h�~�̃}�N�����`����
#include"object.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CMeshClynder : public CObject
{
public:
	CMeshClynder();
	~CMeshClynder();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }			// �ʒu�̐ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; }				// �ʒu���̓���

	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }			// �����̐ݒ�
	void SetRotAdd(D3DXVECTOR3 rot) { m_rot += rot; }		// �����̌��Z�ݒ�
	D3DXVECTOR3 GetRot(void) { return m_rot; }				// �����������

	D3DXMATRIX Getmtx(void) { return m_mtxWorld; }			// �}�g���b�N�X�̏��̓���

	static CMeshClynder * Create(void);

	static bool Collision(D3DXVECTOR3 pos);	// �����蔻��

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//�C���f�b�N�X�o�b�t�@�̃|�C���^
	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;					//�ʒu	
	D3DXVECTOR3 m_rot;					//����	
	D3DCOLOR m_col;		// �F
	float m_fWidth;		// ����
	float m_fDepth;		// ����
	float m_fHeight;	// �c��
	int m_nIdxTexture;	// �e�N�X�`���̃C���f�b�N�X
};
#endif
