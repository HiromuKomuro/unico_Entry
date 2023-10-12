//====================================================================
//
//�J��������[Camera.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _CAMERA_H_		//���̃}�N����`������ĂȂ�������

#define _CAMERA_H_		//��d�C���N���[�h�h�~�̃}�N�����`����
#include"main.h"

//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CCamera
{
public:
	CCamera();
	~CCamera();

	//�v���g�^�C�v�錾
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);

	D3DXVECTOR3 GetCameraV(void) { return m_posV; }	// �J�����̎n�_
	D3DXVECTOR3 GetCameraR(void) { return m_posR; }	// �J�����̒����_
private:

		D3DXVECTOR3 m_posV;				//�n�_
		D3DXVECTOR3 m_posR;				//�����_
		D3DXVECTOR3 m_vecU;				//������x�N�g��
		D3DXMATRIX  m_mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
		D3DXMATRIX  m_mtxView;			//�r���[�}�g���b�N�X
		D3DXVECTOR3 m_rot;				//����
};
#endif
