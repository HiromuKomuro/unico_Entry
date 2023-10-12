//====================================================================
//
//プレイヤー3D処理[Player3D.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"main.h"
#include"Player3D.h"
#include"input.h"
#include"Bullet.h"
#include"Camera.h"
#include"Manager.h"
#include"renderer.h"
#include"sound.h"
#include"Texture.h"
#include"ObjectModel.h"
#include"motion.h"
#include"BlockXbase.h"
#include"MeshCylinder.h"
#include"Fade.h"
#include"Score.h"
#include"renderer.h"
#include"Camera.h"

//マクロ定義
#define MODEL_LEFTRIHGTMOVE			(5.0f)
#define MODEL_UPDOWNMOVE			(3.0f)
#define BULLET_MAXCNT		(180)			// 弾のチャージの最大
#define BULLET_SIZE			(D3DXVECTOR3(10.0,10.0f,10.0f))		// 弾のサイズ
#define SPEED_SCORE			(1)
#define BOOST_SPEED_MAX		(30)
//========================================
// コンストラクタ
//========================================
CPlayer3D::CPlayer3D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_boostmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CObject::SetType(TYPE_PLAYER);	// 種類を設定
	m_nNumModel = 0;
	m_nLife = 100;
	m_nSpeedCnt = 0;
	m_nBoostCnt = 0;
	m_pMotion = NULL;
	m_bBoost = false;
}
//========================================
// デストラクタ
//========================================
CPlayer3D::~CPlayer3D()
{
}
//========================================
//モデルの初期化処理
//========================================
HRESULT CPlayer3D::Init(void)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// モデルの生成
	m_apModel[0] = CObjectModel::Create("data\\MODEL\\car000.x",m_pos);
	m_apModel[1] = CObjectModel::Create("data\\MODEL\\propeller.x", D3DXVECTOR3(20.0f, 20.0f, 10.0f));
	m_apModel[2] = CObjectModel::Create("data\\MODEL\\propeller.x" ,D3DXVECTOR3(-20.0f, 20.0f, 10.0f));
	
	// 親モデルの設定
	m_apModel[0]->SetParent(NULL);
	m_apModel[1]->SetParent(m_apModel[0]);
	m_apModel[2]->SetParent(m_apModel[0]);

	if (m_pMotion != NULL)
	{
		delete m_pMotion;
		m_pMotion = NULL;
	}

	m_pMotion = new CMotion;	// インスタンスを生成

	m_pMotion->SetModel(&m_apModel[0], MAX_PLAYER_PARTS);	// モデルの設定

	return S_OK;
}
//========================================
//モデルの終了処理
//========================================
void CPlayer3D::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_PLAYER_PARTS; nCnt++)
	{
		// プレイヤー3D破棄
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->Uninit();
			delete m_apModel[nCnt];
			m_apModel[nCnt] = NULL;
		}
	}

	// モーションの破棄
	if (m_pMotion != NULL)
	{
		delete m_pMotion;
		m_pMotion = NULL;
	}

	CObject::Relese();
}
//=======================================
//モデルの更新処理
//=======================================
void CPlayer3D::Update(void)
{
	CFade*pFade = CManager::GetCFade();
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CSound*pSound = CManager::GetSound();
	CScene*pScene = CManager::GetCScene();

	int Fade;	

	switch (pScene->GetMode())
	{
	case CScene::MODE_TITLE:

		break;
	case CScene::MODE_GAME:
		m_posOld = m_pos;	// 位置保存

		// 自動スクロール処理
		m_move.z += 2.0f + m_nSpeedCnt * 0.001f;

		// 移動処理
		if (pInputKeyboard->GetKeyboardPress(DIK_D) == true)
		{
			m_move.x += cosf(m_rot.y) * MODEL_LEFTRIHGTMOVE;
			m_move.z -= sinf(m_rot.y) * MODEL_LEFTRIHGTMOVE;
		}
		if (pInputKeyboard->GetKeyboardPress(DIK_A) == true)
		{
			m_move.x -= cosf(m_rot.y) * MODEL_LEFTRIHGTMOVE;
			m_move.z += sinf(m_rot.y) * MODEL_LEFTRIHGTMOVE;
		}
		if (pInputKeyboard->GetKeyboardPress(DIK_W) == true)
		{
			m_move.y += cosf(m_rot.y) * MODEL_UPDOWNMOVE;
		}
		if (pInputKeyboard->GetKeyboardPress(DIK_S) == true)
		{
			m_move.y -= cosf(m_rot.y) * MODEL_UPDOWNMOVE;
		}
		if (pInputKeyboard->GetKeyboardPress(DIK_LSHIFT) == true)
		{
			m_move.x += sinf(m_rot.y) * MODEL_UPDOWNMOVE;
			m_move.z -= cosf(D3DX_PI - m_rot.y) * MODEL_UPDOWNMOVE;
			CScore::AddScore(SPEED_SCORE);	// スコアの増加c

		}
		//if (m_bBoost == true)
		//{// ブーストをするとき
		//	m_nBoostCnt ++;
		//	m_boostmove.z = m_nBoostCnt % BOOST_SPEED_MAX;

		//	if (m_nBoostCnt >= BOOST_SPEED_MAX)
		//	{
		//		m_bBoost = false;
		//		m_nBoostCnt = 0;
		//	}
		//}
	
		// 弾の発射
		if (pInputKeyboard->GetKeyboardRelease(DIK_SPACE) == true)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ATTCAK);	// 攻撃SEの再生

			CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z - 10.0f), m_rot, "data\\MODEL\\missile.x");	// 弾を生成	
		}
		// 位置を増加
		m_pos += m_move;
		m_pos += m_boostmove;

		//移動量を更新(減衰させる)
		m_move.x += (0.0f - m_move.x) * 0.7f;
		m_move.y += (0.0f - m_move.y) *	0.7f;
		m_move.z += (0.0f - m_move.z) * 0.7f;
		m_boostmove.z += (0.0f - m_boostmove.z) * 0.1f;

		// ステージとの当たり判定
		if (CMeshClynder::Collision(m_pos) == true)
		{
			m_pos = m_posOld;
			m_move.x = 0.0f;
			m_move.y = 0.0f;

			//フェード状態を取得
			Fade = pFade->Get();

			if (Fade == CFade::FADE_NONE)
			{//フェード状態が何もないとき
			 //フェードの設定(ゲーム画面に移行)
				pFade->Set(CScene::MODE_REZULT);
			}
		}

		// ブロックとの当たり判定
		if (CBaseBlockX::Collision(&m_pos, &m_posOld, &m_move, m_rot, 20, 30, 30, false, true) == true)
		{
			CFade*pFade = CManager::GetCFade();
			int Fade;

			//フェード状態を取得
			Fade = pFade->Get();

			if (Fade == CFade::FADE_NONE)
			{//フェード状態が何もないとき
			 //フェードの設定(リザルト画面に移行)
				pFade->Set(CScene::MODE_REZULT);
			}
		}

		// スコアの増加
		if (CBaseBlockX::AddScore(m_pos, 40, 40, 30) == true)
		{
			m_bBoost = true;
			m_nSpeedCnt += 1000;
		}

		m_nSpeedCnt++;	// スピードカウンターの増加
		CScore::AddScore(SPEED_SCORE * (m_nSpeedCnt * 0.005f));	// スコアの増加c
		m_pMotion->Update();	// モーションの更新処理
		break;
	}
	
}
//======================================
//モデルの描画処理
//======================================
void CPlayer3D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// モデルの描画処理
	for (int nCnt = 0; nCnt < MAX_PLAYER_PARTS; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}
}
//======================================
// 設定処理
//======================================
CPlayer3D *CPlayer3D::Create(D3DXVECTOR3 pos)
{
	CPlayer3D *pModel;

	// オブジェクト3Dの生成
	pModel = new CPlayer3D();

	// 初期化処理
	pModel->Init();

	pModel->SetPos(pos);	// 位置を設定

	return pModel;
}