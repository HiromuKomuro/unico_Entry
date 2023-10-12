// =======================================================
//
// �����_�����O����(renderer.h)
// author KOMURO HIROMU
//
// =======================================================
// ��d�C���N���[�h�h�~
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include"main.h"

//---------------------------------------------------------------------------
//					*****			�����_���[�N���X�̒�`			*****
//---------------------------------------------------------------------------
class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, BOOL bWindow);	// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	LPDIRECT3DDEVICE9 GetDevice(void);

	void ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 posU);
	LPDIRECT3DTEXTURE9 GetTextureMT(void) { return m_pTextureMT[0]; }
private:

	LPDIRECT3D9				m_pD3D;			// DirectX3D�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Direct3D�f�o�C�X�ւ̃|�C���^

	LPDIRECT3DTEXTURE9		m_pTextureMT[2];// �����_�����O�^�[�Q�b�g�p�e�N�X�`��
	LPDIRECT3DSURFACE9		m_pRenderMT[2];	// �e�N�X�`�������_�����O�p�C���^�[�t�F�[�X
	LPDIRECT3DSURFACE9		m_pZBuffMT;		// �e�N�X�`�������_�����O�pZ�o�b�t�@
	D3DVIEWPORT9			m_viewportMT;	// �e�N�X�`�������_�����O�p�r���[�|�[�g

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMT;	// �t�B�[�h�o�b�N�p�|���S���̒��_�o�b�t�@
	
};

#endif