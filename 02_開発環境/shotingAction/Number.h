// =======================================================
//
// �i���o�[����(Number.h)
// author KOMURO HIROMU
//
// =======================================================
// ��d�C���N���[�h�h�~
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include"object2D.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CNumber :public CObject
{
public:
	CNumber();
	 ~CNumber();

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

	 void SetAnimeTex(float Max_Conter, int m_nAnimeCounter);	// �e�N�X�`���̐ݒ�
	 void SetAddTex(float fTex);							// �e�N�X�`���̉��Z

	 void SetScale(float fHeight, float fWidth); 	// �傫���̐ݒ�

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�̃|�C���^
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
	D3DCOLOR m_col;		// �F
	float m_fWidth;		// ����
	float m_fHeight;	// ����
	int m_nIdxTexture;		// �e�N�X�`���̃C���f�b�N�X

};
#endif