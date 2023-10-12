//====================================================================
//
//���蔲����Ǐ���[throughWall.h]
//author KOMURO HIROMU
//
//====================================================================
#ifndef _THROUGHWALL_H_		//���̃}�N����`������ĂȂ�������

#define _THROUGHWALL_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

#include"Object3D.h"
//---------------------------------------------------------------------------
//					*****			�I�u�W�F�N�g�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CThroughWall3D : public CObject3D
{
public:
	CThroughWall3D();
	~CThroughWall3D();
	// �����o�֐�
	HRESULT Init(const D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CThroughWall3D*Create(const D3DXVECTOR3 pos);
	static bool CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 pRot, float fWidth, float fHeight);

private:
	// �����o�ϐ�
	D3DXVECTOR3 m_rot;		// ����
	int m_nIdxTexture;		// �e�N�X�`���̔ԍ�

};
#endif
