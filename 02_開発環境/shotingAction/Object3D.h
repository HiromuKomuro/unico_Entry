//====================================================================
//
//�|���S������[Polygon.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _POLYGON_H_		//���̃}�N����`������ĂȂ�������

#define _POLYGON_H_		//��d�C���N���[�h�h�~�̃}�N�����`����
#include"object.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CObject3D : public CObject
{
public:
	CObject3D();
	~CObject3D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);			// �e�N�X�`���̊��蓖��

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }			// �ʒu�̐ݒ�
	void SetPosAdd(D3DXVECTOR3 pos) { m_pos += pos; }		// �ʒu�̉��Z�ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; }				// �ʒu���̓���

	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }			// �����̐ݒ�
	void SetRotAdd(D3DXVECTOR3 rot) { m_rot += rot; }		// �����̌��Z�ݒ�
	D3DXVECTOR3 GetRot(void) { return m_rot; }				// �����������

	void SetCol(const D3DCOLOR col);						//�@�F�̐ݒ�

	void SetScale(float fWidth, float fHeight,float fDepth); 	// �傫���̐ݒ�

	static CObject3D * Create(void);
private:
	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//�C���f�b�N�X�o�b�t�@�̃|�C���^
	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;					//�ʒu	
	D3DXVECTOR3 m_rot;					//����	
	D3DCOLOR m_col;		// �F
	float m_fWidth;		// ����
	float m_fDepth;		// ����
	float m_fHeight;	// �c��

};
#endif
