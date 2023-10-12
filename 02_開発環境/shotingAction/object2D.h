// =======================================================
//
// �I�u�W�F�N�g2D����(object2D.h)
// author KOMURO HIROMU
//
// =======================================================
// ��d�C���N���[�h�h�~
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include"object.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CObject2D : public CObject
{
public:
	CObject2D();
	 ~CObject2D();

	 HRESULT Init(void);		// ����������
	 void Uninit(void);			// �I������
	 void Update(void);			// �X�V����
	 void Draw(void);			// �`�揈��

	
	 void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }			// �ʒu�̐ݒ�
	 void SetPosAdd(D3DXVECTOR3 pos) { m_pos += pos; }		// �ʒu�̉��Z�ݒ�
	 D3DXVECTOR3 GetPos(void) { return m_pos; }				// �ʒu���̓���

	 void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }			// �����̐ݒ�
	 void SetRotAdd(D3DXVECTOR3 rot) { m_rot += rot; }		// �����̌��Z�ݒ�
	 D3DXVECTOR3 GetRot(void) { return m_rot; }				// �����������

	 void SetCol(const D3DCOLOR col);						//�@�F�̐ݒ�

	 void SetTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }	// �e�N�X�`���̐ݒ�
	 void BindTexture(int nIdxTexture) { m_nIdxTeture = nIdxTexture; }			// �e�N�X�`���̊��蓖��

	 void SetAnimeTex(float Max_Conter, int m_nAnimeCounter);	// �e�N�X�`���̐ݒ�
	 void SetAddTex(float fTex);							// �e�N�X�`���̉��Z

	 void SetScale(float fWidth,float fHeight); 	// �傫���̐ݒ�

	 static CObject2D *Create(D3DXVECTOR3 pos, D3DCOLOR Col,D3DXVECTOR2 sclae);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���̐ݒ�
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
	D3DCOLOR m_col;		// �F
	float m_fWidth;		// ����
	float m_fHeight;	// ����
	int m_nIdxTeture;	// �e�N�X�`���̃C���f�b�N�X
};
#endif