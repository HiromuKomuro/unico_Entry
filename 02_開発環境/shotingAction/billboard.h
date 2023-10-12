//====================================================================
//
//�r���{�[�h����[Billboard.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _BILLBOARD_H_		//���̃}�N����`������ĂȂ�������

#define _BILLBOARD_H_		//��d�C���N���[�h�h�~�̃}�N�����`����
#include"object.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CObjectBillboard : public CObject
{
public:
	CObjectBillboard();
	~CObjectBillboard();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BindTexture(int nTexture);			// �e�N�X�`���̊��蓖��

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }			// �ʒu�̐ݒ�
	void SetPosAdd(D3DXVECTOR3 pos) { m_pos += pos; }		// �ʒu�̉��Z�ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; }				// �ʒu���̓���

	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }			// �����̐ݒ�
	void SetRotAdd(D3DXVECTOR3 rot) { m_rot += rot; }		// �����̌��Z�ݒ�
	D3DXVECTOR3 GetRot(void) { return m_rot; }				// �����������

	void SetCol(const D3DCOLOR col);						//�@�F�̐ݒ�

	void SetAnimeTex(float Max_Conter, int m_nAnimeCounter);	// �e�N�X�`���̐ݒ�
	void SetAddTex(float fTex);							// �e�N�X�`���̉��Z
	void SetScale(float fWidth, float fHeight); 	// �傫���̐ݒ�

	static CObjectBillboard * Create(void);
private:
	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;					// �ʒu	
	D3DXVECTOR3 m_rot;					// ����	
	D3DCOLOR m_col;		// �F
	float m_fWidth;		// ����
	float m_fDepth;		// ����
	float m_fHeight;	// �c��
	int m_nIdxTexture;
};
#endif
