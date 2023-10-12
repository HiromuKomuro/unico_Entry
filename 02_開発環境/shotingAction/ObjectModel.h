//====================================================================
//
//���f������[ObjectModel.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _OBJECTMODEL_H_		//���̃}�N����`������ĂȂ�������

#define _OBJECTMODEL_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CObjectModel
{
public:
	// ��Ԃ̗񋓌^
	typedef enum
	{
		STATE_NONE = 0,
		STATE_DAMAGE,
		STATE_MAX
	}STATE;

	CObjectModel();
	~CObjectModel();

	//�����o�֐�
	HRESULT Init(const char* pFilename);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXMATRIX GetMtx(void) { return m_mtxWorld; }		// �}�g���b�N�X�̎擾
	void SetParent(CObjectModel*pObjectModel);	// �e���f���̐ݒ�

	static CObjectModel*Create(const char* pFilename, D3DXVECTOR3 pos);	// ���f���I�u�W�F�N�g�̐���

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }			// �ʒu�̐ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; }				// �ʒu���̓���

	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }			// �����̐ݒ�
	D3DXVECTOR3 GetRot(void) { return m_rot; }				// �����������

	void SetCol(D3DCOLOR col) { m_col = col; }			// �F�̐ݒ�
	D3DXCOLOR GetCol(void) { return m_col; }				// �F�������

	void SetSize(D3DXVECTOR3 size) { m_Size = size; }			// �T�C�Y�̐ݒ�
	D3DXVECTOR3 GetSize(void) { return m_Size; }				// �T�C�Y�̓���

	void SetState(STATE state) { m_state = state; }		// ��Ԃ̐ݒ�
	STATE GetState(void) { return m_state; }			// ��Ԃ̓���

	D3DXVECTOR3 *GetVertexPos(void) { return m_pPos; }		// ���_���̈ʒu�����
	WORD GetSizeFVF(void) { return m_SizeFVF; }					// �T�C�Y�̏������	
	int GetnNumVertex(void) { return m_pMesh->GetNumVertices(); }	// ���_�̐������

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
		STATE		m_state;			// ���
		D3DXVECTOR3 m_Size;				// ���f���̃T�C�Y
		D3DXMATRIX m_mtxWorld;			// ���[���h�}�g���b�N�X
		CObjectModel* m_aParent;		// �e���f���̃|�C���^
		int*m_nIdxTexture;				// �e�N�X�`���̑���
		int m_nDamgeCounter;			// �_���[�W�J�E���^�[
};
#endif
