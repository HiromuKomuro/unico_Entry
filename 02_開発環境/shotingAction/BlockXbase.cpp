//====================================================================
//
//ブロックの基礎位置の処理[BlockXbase.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include <math.h>

#include"main.h"
#include"BlockXbase.h"
#include"input.h"
#include"Bullet.h"
#include"Camera.h"
#include"Manager.h"
#include"renderer.h"
#include"sound.h"
#include"Texture.h"
#include"ObjectModel.h"
#include"motion.h"
#include"BlockX.h"
#include"collisionline.h"
#include"Score.h"
#include"Particle.h"

//マクロ定義
#define MODEL_MOVE			(3)
#define HIT_COL				(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))
#define NOTHIT_COL			(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
#define MAX_SCORE			(10000.0f)
#define MAX_DISTANCE		(1000.0f)
#define SCORE_MAG			(20.0f)		
#define Correction			(0.0f)
//========================================
// コンストラクタ
//========================================
CBaseBlockX::CBaseBlockX()
{
	CObject::SetType(TYPE_BLOCKBASE);

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumModel = 0;
	m_nId = 0;
	m_bDeath = false;
	m_pFilename = NULL;
}
//========================================
// デストラクタ
//========================================
CBaseBlockX::~CBaseBlockX()
{
}
//========================================
// 初期化処理
//========================================
HRESULT CBaseBlockX::Init(void)
{
	// モデルの生成
	m_apModel = CBlockX::Create(D3DXVECTOR3(m_pos.x,m_pos.y,0.0f),m_pFilename,m_Size);

	// 親モデルの設定
	m_apModel->SetParent(NULL);

	m_pos = D3DXVECTOR3(0.0f, (250.0f * 7.0f + 100.0f) / 2, m_pos.z);

	return S_OK;
}
//========================================
// 終了処理
//========================================
void CBaseBlockX::Uninit(void)
{
	if (m_apModel != NULL)
	{
		m_apModel->Uninit();
		delete m_apModel;
		m_apModel = NULL;
	}

	CObject::Relese();
}
//=======================================
// 更新処理
//=======================================
void CBaseBlockX::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// 回転処理
	if (pInputKeyboard->GetKeyboardPress(DIK_RIGHT) == true)
	{
		m_rotmove.z += ROT_TRANS;
	}
	if (pInputKeyboard->GetKeyboardPress(DIK_LEFT) == true)
	{
		m_rotmove.z -= ROT_TRANS;
	}

	// 位置を増加
	m_rot += m_rotmove;

	//移動量を更新(減衰させる)
	m_rotmove.x += (0.0f - m_rotmove.x) * 0.8f;
	m_rotmove.y += (0.0f - m_rotmove.y) * 0.8f;
	m_rotmove.z += (0.0f - m_rotmove.z) * 0.8f;

	m_apModel->Update();
	
}
//======================================
//モデルの描画処理
//======================================
void CBaseBlockX::Draw(void)
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
	m_apModel->Draw(m_mtxWorld);
	
}
//======================================
// 設定処理
//======================================
CBaseBlockX *CBaseBlockX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 Size)
{
	CBaseBlockX *pModel;

	// オブジェクト3Dの生成
	pModel = new CBaseBlockX();

	pModel->SetSize(Size);	// サイズの設定

	pModel->SetPos(pos);	// 位置を設定

	pModel->SetFile("data//MODEL//Block.x");	// ファイル名の設定

	// 初期化処理
	pModel->Init();

	// 当たり判定のラインの生成
	CCollisionLine::Create(D3DXVECTOR3(pModel->GetBlock()->GetPos().x, pModel->GetBlock()->GetPos().y, pModel->GetPos().z),
		D3DXVECTOR3(pModel->GetBlock()->GetMaxpos().x, pModel->GetBlock()->GetMaxpos().y, pModel->GetBlock()->GetMaxpos().z),
		&pModel->m_nId);

	return pModel;
}
//======================================
// 壁との当たり判定
//======================================
bool CBaseBlockX::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 pRot, float fWidth, float fHeight, float fDepth, bool bBullet, bool bPlayer)
{
	bool bChangeCol;
	bool bHit = false;

	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		CObject *pObj = CObject::GetTop(nCntPri);	// 先頭のオブジェクトを代入

		while (pObj != NULL)
		{
			bChangeCol = false;			//色を変えるか

			if (bPlayer == true && bHit == true)
			{// プレイヤーの場合でヒットしているとき
				return bHit;
			}

			CObject *pObjectNext = pObj->GetNext();	// 次のオブジェクトを保存

			//種類を取得
			TYPE type = pObj->GetType();

			if (type == TYPE_BLOCKBASE || type == TYPE_BREAKBLOCKBASE)
			{
				CBaseBlockX *pBlockbase = dynamic_cast<CBaseBlockX*>(pObj);

				if (type == TYPE_BREAKBLOCKBASE)
				{
					CBreakBaseBlockX *pBlockbase = dynamic_cast<CBreakBaseBlockX*>(pObj);
				}

				CBlockX* pBlock = pBlockbase->GetBlock();

				D3DXVECTOR3 pos0, pos1, pos2, pos3;

				// 計算に必要な要素を入手
				D3DXVECTOR3 Maxpos = pBlock->GetMaxpos();
				D3DXVECTOR3 Minpos = pBlock->GetMinpos();
				float fLength = pBlock->GetLength();
				float fAngle = pBlock->GetAngle();

				D3DXVECTOR3 rot = pBlockbase->GetRot();

				D3DXVECTOR3 pos;
				
				pos.x = pBlock->GetMtx()._41;
				pos.y = pBlock->GetMtx()._42;
				pos.z = pBlock->GetMtx()._43;

				// 当たり判定用の頂点を設定
		/*		pos0.x = pos.x + sinf(rot.z + (D3DX_PI + fAngle)) * fLength ;
				pos0.y = pos.y + +cosf(rot.z + (D3DX_PI + fAngle)) * fLength;
				pos0.z = Maxpos.z + pos.z;

				pos1.x = pos.x + sinf(rot.z + (D3DX_PI - fAngle)) * fLength;
				pos1.y = pos.y + cosf(rot.z + (D3DX_PI - fAngle)) * fLength;
				pos1.z = Minpos.z + pos.z;

				pos2.x = pos.x + sinf(rot.z + (-fAngle)) * fLength;
				pos2.y = pos.y + cosf(rot.z + (-fAngle)) * fLength;
				pos2.z = Maxpos.z + pos.z;

				pos3.x = pos.x + sin(rot.z + (fAngle)) * fLength;
				pos3.y = pos.y + cos(rot.z + (fAngle)) * fLength;*/
				//pos3.z = Minpos.z + pos.z;

				pos0.x = pos.x - Maxpos.x;
				pos0.y = pos.y + Maxpos.y;
				pos0.z = Maxpos.z + pos.z;

				pos1.x = pos.x + Maxpos.x;
				pos1.y = pos.y + Maxpos.y;
				pos1.z = Minpos.z + pos.z;

				pos2.x = pos.x - Maxpos.x;
				pos2.y = pos.y - Maxpos.y;
				pos2.z = Maxpos.z + pos.z;

				pos3.x = pos.x + Maxpos.x;
				pos3.y = pos.y - Maxpos.y;
				pos3.z = Minpos.z + pos.z;


				if (Minpos.z + pos.z >= pPosOld->z + fDepth&&
					Minpos.z + pos.z <= pPos->z + fDepth
					)
				{// zの範囲内にいるとき
					bool b01 = ((pos1.y - pos0.y) * (pPos->x - pos0.x)) - ((pos1.x - pos0.x) * (pPos->y - pos0.y)) >= 0.0f;
					bool b13 = ((pos3.y - pos1.y) * (pPos->x - pos1.x)) - ((pos3.x - pos1.x) * (pPos->y - pos1.y)) >= 0.0f;
					bool b32 = ((pos2.y - pos3.y) * (pPos->x - pos3.x)) - ((pos2.x - pos3.x) * (pPos->y - pos3.y)) >= 0.0f;
					bool b20 = ((pos0.y - pos2.y) * (pPos->x - pos2.x)) - ((pos0.x - pos2.x) * (pPos->y - pos2.y)) >= 0.0f;

					if (b01 && b13 && b32 && b20)
					{// xとyの範囲内の時
						bHit = true;
						bChangeCol = true;
						pMove->z = 0.0f;
						pPos->z = Minpos.z + pos.z - fDepth;
					}

				}
				if (Minpos.x + pos.x >= pPosOld->x + fWidth&&
					Minpos.x + pos.x <= pPos->x + fWidth)
				{// 右側の当たり判定
					bool b02 = ((pos1.y - pos0.y) * (pPos->z - pos0.z)) - ((pos1.z - pos0.z) * (pPos->y - pos0.y)) <= 0.0f;
					bool b14 = ((pos3.y - pos1.y) * (pPos->z - pos1.z)) - ((pos3.z - pos1.z) * (pPos->y - pos1.y)) <= 0.0f;
					bool b33 = ((pos2.y - pos3.y) * (pPos->z - pos3.z)) - ((pos2.z - pos3.z) * (pPos->y - pos3.y)) <= 0.0f;
					bool b20 = ((pos0.y - pos2.y) * (pPos->z - pos2.z)) - ((pos0.z - pos2.z) * (pPos->y - pos2.y)) <= 0.0f;

					if (b02 && b14 && b33 && b20)
					{// xとの範囲内の時
						bHit = true;
						bChangeCol = true;
						pMove->x = 0.0f;
						pPos->x = Minpos.x + pos.x - fWidth;
					}
				}
				else if (Maxpos.x + pos.x <= pPosOld->x - fWidth&&
					Maxpos.x + pos.x >= pPos->x - fWidth)
				{// 左側の当たり判定
					bool b02 = ((pos1.y - pos0.y) * (pPos->z - pos0.z)) - ((pos1.z - pos0.z) * (pPos->y - pos0.y)) <= 0.0f;
					bool b14 = ((pos3.y - pos1.y) * (pPos->z - pos1.z)) - ((pos3.z - pos1.z) * (pPos->y - pos1.y)) <= 0.0f;
					bool b33 = ((pos2.y - pos3.y) * (pPos->z - pos3.z)) - ((pos2.z - pos3.z) * (pPos->y - pos3.y)) <= 0.0f;
					bool b20 = ((pos0.y - pos2.y) * (pPos->z - pos2.z)) - ((pos0.z - pos2.z) * (pPos->y - pos2.y)) <= 0.0f;

					if (b02 && b14 && b33 && b20)
					{// xとの範囲内の時
						bHit = true;
						bChangeCol = true;
						pMove->x = 0.0f;
						pPos->x = Maxpos.x + pos.x + fWidth;
					}
				}
				if (Maxpos.y + pos.y <= pPosOld->y - fHeight&&
					Maxpos.y + pos.y >= pPos->y - fHeight)
				{// 上側の当たり判定
					float fProxypos0, fProxypos1, fProxypos2, fProxypos3;	// 代理の変数を用意
					// 各位置の設定
					fProxypos0 = pos0.z;
					fProxypos1 = pos2.z;
					fProxypos2 = pos1.z;
					fProxypos3 = pos3.z;

					bool b02 = ((pos1.x - pos0.x) * (pPos->z - fProxypos0)) - ((fProxypos1 - fProxypos0) * (pPos->x - pos0.x)) <= 0.0f;
					bool b14 = ((pos3.x - pos1.x) * (pPos->z - fProxypos1)) - ((fProxypos3 - fProxypos1) * (pPos->x - pos1.x)) <= 0.0f;
					bool b33 = ((pos2.x - pos3.x) * (pPos->z - fProxypos3)) - ((fProxypos2 - fProxypos3) * (pPos->x - pos3.x)) <= 0.0f;
					bool b20 = ((pos0.x - pos2.x) * (pPos->z - fProxypos2)) - ((fProxypos0 - fProxypos2) * (pPos->x - pos2.x)) <= 0.0f;

					if (b02 && b14 && b33 && b20)
					{// xとの範囲内の時
						bHit = true;
						bChangeCol = true;
						pMove->y = 0.0f;
						pPos->y = Maxpos.y + pos.y + fHeight;
					}
				}
				else if (Minpos.y + pos.y >= pPosOld->y + fHeight&&
					Minpos.y + pos.y <= pPos->y + fHeight)
				{// 下側の当たり判定
					float fProxypos0, fProxypos1, fProxypos2, fProxypos3;	// 代理の変数を用意
					// 各位置の設定
					fProxypos0 = pos0.z;
					fProxypos1 = pos2.z;
					fProxypos2 = pos1.z;
					fProxypos3 = pos3.z;

					bool b02 = ((pos1.x - pos0.x) * (pPos->z - fProxypos0)) - ((fProxypos1 - fProxypos0) * (pPos->x - pos0.x)) <= 0.0f;
					bool b14 = ((pos3.x - pos1.x) * (pPos->z - fProxypos1)) - ((fProxypos3 - fProxypos1) * (pPos->x - pos1.x)) <= 0.0f;
					bool b33 = ((pos2.x - pos3.x) * (pPos->z - fProxypos3)) - ((fProxypos2 - fProxypos3) * (pPos->x - pos3.x)) <= 0.0f;
					bool b20 = ((pos0.x - pos2.x) * (pPos->z - fProxypos2)) - ((fProxypos0 - fProxypos2) * (pPos->x - pos2.x)) <= 0.0f;

					if (b02 && b14 && b33 && b20)
					{// xとの範囲内の時
						bHit = true;
						bChangeCol = true;
						pMove->y = 0.0f;
						pPos->y = Minpos.y + pos.y - fHeight;
					}
				}

				if (bChangeCol == true)
				{// あたっているとき
					pBlock->SetCol(HIT_COL);	// 色の変更

					if (bBullet == true && type == TYPE_BREAKBLOCKBASE)
					{// 弾の時で種類が壊れるブロックの時
						pBlockbase->Uninit();	// ブロックを壊す
						CScore::AddScore(1000);
						break;
					}
				}
				else
				{
					pBlock->SetCol(NOTHIT_COL);	// 色の変更
				}

			}
			pObj = pObjectNext;		// 次のオブジェクトを代入

		}
	}
	return bHit;
}
//======================================
// スコアの増加処理
//======================================
bool CBaseBlockX::AddScore(D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepth)
{
	CSound*pSound = CManager::GetSound();

	bool bScoreAdd = false;
	int nScore = 0;
	int LScore = 0, RScore = 0, UScore = 0, DScore = 0;

	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		CObject *pObj = CObject::GetTop(nCntPri);	// 先頭のオブジェクトを代入

		while (pObj != NULL)
		{
			CObject *pObjectNext = pObj->GetNext();	// 次のオブジェクトを保存

			//種類を取得
			TYPE type = pObj->GetType();

			if (type == TYPE_BLOCKBASE || type == TYPE_BREAKBLOCKBASE)
			{
				CBaseBlockX *pBlockbase = dynamic_cast<CBaseBlockX*>(pObj);

				if (type == TYPE_BREAKBLOCKBASE)
				{
					CBreakBaseBlockX *pBlockbase = dynamic_cast<CBreakBaseBlockX*>(pObj);
				}

				CBlockX* pBlock = pBlockbase->GetBlock();

				D3DXVECTOR3 pos0, pos1, pos2, pos3;

				// 計算に必要な要素を入手
				D3DXVECTOR3 Maxpos = pBlock->GetMaxpos();
				D3DXVECTOR3 Minpos = pBlock->GetMinpos();
				float fLength = pBlock->GetLength();
				float fAngle = pBlock->GetAngle();

				D3DXVECTOR3 rot = pBlockbase->GetRot();

				D3DXVECTOR3 Blockpos;

				Blockpos.x = pBlock->GetMtx()._41;
				Blockpos.y = pBlock->GetMtx()._42;
				Blockpos.z = pBlock->GetMtx()._43;

				// 当たり判定用の頂点を設定
				pos0.x = Blockpos.x - Maxpos.x;
				pos0.y = Blockpos.y + Maxpos.y;
				pos0.z = Maxpos.z + Blockpos.z;

				pos1.x = Blockpos.x + Maxpos.x;
				pos1.y = Blockpos.y + Maxpos.y;
				pos1.z = Minpos.z + Blockpos.z;

				pos2.x = Blockpos.x - Maxpos.x;
				pos2.y = Blockpos.y - Maxpos.y;
				pos2.z = Maxpos.z + Blockpos.z;

				pos3.x = Blockpos.x + Maxpos.x;
				pos3.y = Blockpos.y - Maxpos.y;
				pos3.z = Minpos.z + Blockpos.z;

				if (pos.z >= Blockpos.z && pBlockbase->GetDeath() == false)
				{
					if (pos.y + fHeight >= pos2.y &&
						pos.y - fHeight <= pos0.y &&
						pos.x + fWidth  <= Blockpos.x - Maxpos.x)
					{ // プレイヤー右側の当たり判定
						float fPlayerpos = pos.x;
						float ra = fPlayerpos - Blockpos.x;
						float fDistance = sqrt(ra * ra);
						if (RScore <= MAX_SCORE - fDistance * SCORE_MAG)
						{
							RScore = MAX_SCORE - fDistance * SCORE_MAG;
						}
					}
					else if (pos.y + fHeight >= pos2.y &&
						pos.y - fHeight <= pos0.y &&
						pos.x - fWidth >= Blockpos.x + Maxpos.x)
					{ // プレイヤーの左側の当たり判定
						float fPlayerpos = pos.x;
						float ra = Blockpos.x - fPlayerpos;
						float fDistance = sqrt(ra * ra);

						if (LScore <= MAX_SCORE - fDistance * SCORE_MAG)
						{
							LScore = MAX_SCORE - fDistance * SCORE_MAG;
						}
					}
					if (pos.x + fWidth + Correction >= pos0.x &&
						pos.x - fWidth - Correction <= pos1.x &&
						pos.y - fHeight >= Blockpos.y)
					{ // プレイヤーの下側の当たり判定
						float fPlayerpos = pos.y;
						float ra = Blockpos.y - fPlayerpos;
						float fDistance = sqrt(ra * ra);

						if (DScore <= MAX_SCORE - fDistance * SCORE_MAG)
						{
 							DScore = MAX_SCORE - fDistance  * SCORE_MAG;
						}
					}
					if (pos.x + fWidth + Correction >= pos0.x &&
						pos.x - fWidth + Correction <= pos1.x &&
						pos.y + fHeight <= Blockpos.y)
					{ // プレイヤー上側の当たり判定
						float fPlayerpos = pos.y;
						float ra = fPlayerpos - Blockpos.y;
						float fDistance = sqrt(ra * ra);

						if (UScore <= MAX_SCORE - fDistance * SCORE_MAG)
						{
							UScore = MAX_SCORE - fDistance * SCORE_MAG;
						}
					}
					pBlockbase->SetDeath();

				}
			}
			pObj = pObjectNext;		// 次のオブジェクトを代入
		}
	}
	nScore += UScore + DScore + RScore + LScore;
	// パーティクルの生成
	if (nScore > MAX_SCORE)
	{
		CParticle::Create(pos, D3DCOLOR_RGBA(255, 0, 0, 255));	// パーティクルのの生成
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SCORE003);	// サウンドの再生
		bScoreAdd = true;		// スコアが増えたようにする
	}
	else if (nScore > MAX_SCORE / 2)
	{
		CParticle::Create(pos, D3DCOLOR_RGBA(255, 255, 0, 255));
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SCORE002);
		bScoreAdd = true;

	}
	else if (nScore > 0)
	{
		CParticle::Create(pos, D3DCOLOR_RGBA(255, 0, 255, 255));
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SCORE001);
		bScoreAdd = true;
	}
	CScore::AddScore(nScore);	// スコアの増加
	if (nScore > 0)
	{
		CAddScore::Create(D3DXVECTOR3(800.0f, 140.0f, 0.0f), nScore);	// スコア増加の生成
	}
	return bScoreAdd;
}
//========================================
// コンストラクタ
//========================================
CBreakBaseBlockX::CBreakBaseBlockX()
{
	CObject::SetType(TYPE_BREAKBLOCKBASE);

	m_nLife = 0;
}
//========================================
// デストラクタ
//========================================
CBreakBaseBlockX::~CBreakBaseBlockX()
{
}
//========================================
// 初期化処理
//========================================
HRESULT CBreakBaseBlockX::Init(void)
{
	CBaseBlockX::Init();

	return S_OK;
}
//========================================
// 終了処理
//========================================
void CBreakBaseBlockX::Uninit(void)
{
	CBaseBlockX::Uninit();
	CObject::Relese();
}
//=======================================
// 更新処理
//=======================================
void CBreakBaseBlockX::Update(void)
{
	CBaseBlockX::Update();
}
//======================================
// 描画処理
//======================================
void CBreakBaseBlockX::Draw(void)
{
	CBaseBlockX::Draw();
}
//======================================
// 設定処理
//======================================
CBreakBaseBlockX *CBreakBaseBlockX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 Size)
{
	CBreakBaseBlockX *pModel;

	// オブジェクト3Dの生成
	pModel = new CBreakBaseBlockX();

	pModel->SetSize(Size);	// サイズの設定

	pModel->SetPos(pos);	// 位置を設定

	pModel->SetFile("data//MODEL//BreakBlock.x");	// ファイル名の設定

	// 初期化処理
	pModel->Init();

	int nId;

	// 当たり判定のラインの生成
	CCollisionLine::Create(D3DXVECTOR3(pModel->GetBlock()->GetPos().x, pModel->GetBlock()->GetPos().y, pModel->GetPos().z),
		D3DXVECTOR3(pModel->GetBlock()->GetMaxpos().x, pModel->GetBlock()->GetMaxpos().y, pModel->GetBlock()->GetMaxpos().z),
		&nId);
		
	// 識別番号の設定
	pModel->SetId(nId);
	return pModel;
}