//====================================================================
//
//���f������[Model.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _MODEL_H_		//���̃}�N����`������ĂȂ�������

#define _MODEL_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

#include"object.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CXModel: public CObject
{
public:
	CXModel();
	~CXModel();

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BindModel(const char* pFilename);			// ���f���̊��蓖��

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }			// �ʒu�̐ݒ�
	void SetPosAdd(D3DXVECTOR3 pos) { m_pos += pos; }		// �ʒu�̉��Z�ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; }				// �ʒu���̓���

	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }			// �����̐ݒ�
	void SetRotAdd(D3DXVECTOR3 rot) { m_rot += rot; }		// �����̌��Z�ݒ�
	D3DXVECTOR3 GetRot(void) { return m_rot; }				// �����������

	void SetCol(D3DXCOLOR col) { m_col = col; }				// �F�̐ݒ�
	D3DXCOLOR GetCol(void) { return m_col; }				// �F�̓���

	void SetSize(D3DXVECTOR3 size) { m_Size = size; }				// �T�C�Y�̐ݒ�
	D3DXVECTOR3 GetSize(void) { return m_Size; }					// �T�C�Y�̓���

	D3DXVECTOR3 *GetVertexPos(void) { return m_pPos; }		// ���_���̈ʒu�����
	WORD GetSizeFVF(void) { return m_SizeFVF; }					// �T�C�Y�̏������	
	int GetnNumVertex(void) { return m_pMesh->GetNumVertices(); }	// ���_�̐������

	static CXModel*Create(const char* pFilename);	// ���f���I�u�W�F�N�g�̐���
private:
		LPD3DXMESH m_pMesh;				// ���b�V��(���_���)�ւ̃|�C���^
		LPD3DXBUFFER m_pBuffMat;		// �}�e���A���ւ̃|�C���^
		DWORD m_dwNumMat;				// �}�e���A���̐�
		LPDIRECT3DTEXTURE9 *m_pTexture;	// �e�N�X�`���̃|�C���^
		WORD m_SizeFVF;					// �o�b�t�@�̃T�C�Y
		D3DXVECTOR3 *m_pPos;			// ���_���̈ʒu
		BYTE *m_pVertex;				// ���_���
		D3DXVECTOR3 m_pos;				// �ʒu
		D3DXVECTOR3 m_rot;				// ����		
		D3DXMATRIX m_mtxWorld;			// ���[���h�}�g���b�N�X
		D3DXVECTOR3 m_Size;				// ���f���̃T�C�Y
		D3DXCOLOR  m_col;				// �F
		int m_nIdxMode;					// �Ώۂ̉e�̃C���f�b�N�X(�ԍ�)
		int m_nIdxModelParent;			// �e���f���̃C���f�b�N�X
		int *m_nIdxTexture;				// �e�N�X�`���̔ԍ�
};
#endif
