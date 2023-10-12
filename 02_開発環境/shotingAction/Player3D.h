//====================================================================
//
//�v���C���[3D����[Player3D.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _PLAYER3D_H_		//���̃}�N����`������ĂȂ�������

#define _PLAYER3D_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

// �}�N����`
#define MAX_PLAYER_PARTS	(3)
#include"object.h"
class CObjectModel;
class CMotion;
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CPlayer3D: public CObject
{
public:
	CPlayer3D();
	~CPlayer3D();

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

	static CPlayer3D*Create(D3DXVECTOR3 pos);	// ���f���I�u�W�F�N�g�̐���
private:
		D3DXMATRIX m_mtxWorld;			//���[���h�}�g���b�N�X
		D3DXVECTOR3 m_pos;				//�ʒu
		D3DXVECTOR3 m_posOld;			// �O�̈ʒu
		D3DXVECTOR3 m_move;				// �ړ���
		D3DXVECTOR3 m_boostmove;		// �u�[�X�g�����ړ���
		D3DXVECTOR3 m_rot;				//����		
		CObjectModel *m_apModel[MAX_PLAYER_PARTS];		// ���f���ւ̃|�C���^
		CMotion*m_pMotion;				// ���[�V�����̃|�C���^�\
		int m_nNumModel;				// ���f���̑���
		int m_nLife;					// ��
		int m_nSpeedCnt;				// ���x�̃J�E���g
		int m_nBoostCnt;				// �u�[�X�g�̃J�E���g
		bool m_bBoost;					// �u�[�X�g���Ă��邩�ǂ���
};
#endif
