//====================================================================
//
//モーション処理[motion.cpp]
//author KOMURO HIROMU
//
//====================================================================
#include"motion.h"
#include"ObjectModel.h"

#include<stdio.h>
//========================================
// コンストラクタ
//========================================
CMotion::CMotion()
{
	// 各情報の初期化
	m_aInfo[0] = {};
	m_nCounter = 0;
	m_nKey = 0;
	m_nNumAll = 0;
	m_nNumKey = 0;
	m_nNumModel = 0;
	m_nType = 0;
	m_bFinish = true;
	m_bLoop = false;
}
//========================================
// デスストラクタ
//========================================
CMotion::~CMotion()
{

}
//========================================
// 設定処理
//========================================
void CMotion::Set(int nType)
{
	nType = m_nType;

	m_bLoop = false;	// ループをさせない
	m_bFinish = false;	// 終了していない


	m_aInfo[m_nType].aKeyInfo[0].Key[0].fPosx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[0].fPosy = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[0].fPosz = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[0].fRotx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[0].fRoty = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[0].fRotz = 0.0f;

	m_aInfo[m_nType].aKeyInfo[1].Key[0].fPosx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[0].fPosy = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[0].fPosz = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[0].fRotx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[0].fRoty = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[0].fRotz = 0.0f;

	m_aInfo[m_nType].aKeyInfo[0].Key[1].fPosx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[1].fPosy = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[1].fPosz = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[1].fRotx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[1].fRoty = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[1].fRotz = 0.0f;
					   
	m_aInfo[m_nType].aKeyInfo[1].Key[1].fPosx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[1].fPosy = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[1].fPosz = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[1].fRotx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[1].fRoty = 6.28f;
	m_aInfo[m_nType].aKeyInfo[1].Key[1].fRotz = 0.0f;

	m_aInfo[m_nType].aKeyInfo[0].Key[2].fPosx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[2].fPosy = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[2].fPosz = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[2].fRotx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[2].fRoty = 0.0f;
	m_aInfo[m_nType].aKeyInfo[0].Key[2].fRotz = 0.0f;
							  
	m_aInfo[m_nType].aKeyInfo[1].Key[2].fPosx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[2].fPosy = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[2].fPosz = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[2].fRotx = 0.0f;
	m_aInfo[m_nType].aKeyInfo[1].Key[2].fRoty = 6.28f;
	m_aInfo[m_nType].aKeyInfo[1].Key[2].fRotz = 0.0f;

	m_aInfo[m_nType].aKeyInfo[0].nFrame = 40;
	m_aInfo[m_nType].aKeyInfo[1].nFrame = 30;
	m_aInfo[m_nType].aKeyInfo[2].nFrame = 20;


	// 全モデルの更新
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		D3DXVECTOR3 pos = m_ppObjectModel[nCntModel]->GetPos() + D3DXVECTOR3(m_aInfo[m_nType].aKeyInfo[nCntModel].Key[0].fPosx, m_aInfo[m_nType].aKeyInfo[nCntModel].Key[0].fPosy, m_aInfo[m_nType].aKeyInfo[nCntModel].Key[0].fPosz);
		D3DXVECTOR3 rot = m_ppObjectModel[nCntModel]->GetRot() + D3DXVECTOR3(m_aInfo[m_nType].aKeyInfo[nCntModel].Key[0].fRotx, m_aInfo[m_nType].aKeyInfo[nCntModel].Key[0].fRoty, m_aInfo[m_nType].aKeyInfo[nCntModel].Key[0].fRotz);
																										
		// パーツの位置.向きを設定
		m_ppObjectModel[nCntModel]->SetPos(pos);
		m_ppObjectModel[nCntModel]->SetRot(rot);
	}
}
//========================================
// 更新処理
//========================================
void CMotion::Update(void)
{
	KEY Key;

	if (m_bFinish == false)
	{
		// 全モデルの更新
		for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
		{
			Key.fPosx = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].Key[nCntModel].fPosx - m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fPosx;
			Key.fPosy = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].Key[nCntModel].fPosy - m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fPosy;
			Key.fPosz = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].Key[nCntModel].fPosz - m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fPosz;

			Key.fRotx = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].Key[nCntModel].fRotx - m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fRotx;
			Key.fRoty = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].Key[nCntModel].fRoty - m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fRoty;
			Key.fRotz = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].Key[nCntModel].fRotz - m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fRotz;

			D3DXVECTOR3 pos = m_ppObjectModel[nCntModel]->GetPos() + D3DXVECTOR3(m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fPosx + Key.fPosx * (m_nCounter % m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame),
				m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fPosy + Key.fPosy * (m_nCounter % m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame),
				m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fPosz + Key.fPosz * (m_nCounter % m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame));

			D3DXVECTOR3 rot = m_ppObjectModel[nCntModel]->GetRot() + D3DXVECTOR3(m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fRotx + Key.fRotx * (m_nCounter % m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame),
				m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fRoty + Key.fRoty * (m_nCounter % m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame),
				m_aInfo[m_nType].aKeyInfo[m_nKey].Key[nCntModel].fRotz + Key.fRotz * (m_nCounter % m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame));

			// パーツの位置.向きを設定
			m_ppObjectModel[nCntModel]->SetPos(pos);

			m_ppObjectModel[nCntModel]->SetRot(rot);

		}
		m_nCounter++;	// カウンターを増加

		if (m_nCounter > m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame)
		{// 再生フレーム数に達したとき
			m_nKey++;		// キーを進める
			m_nCounter = 0;	// カウンターを初期化

			if (m_nKey > m_nNumKey)
			{// キーの総数に達したとき
				if (m_bLoop == false)
				{// ループをしないとき
					m_bFinish = true;	// 終了させる	
				}
				m_nKey = 0;	// 最初から

			}
		}
	}
}
//========================================
// インフォの設定処理
//========================================
void CMotion::SetInfo(INFO info)
{
	m_aInfo[m_nNumAll] = info;

	m_nNumAll++;
}
//========================================
// モデルの設定処理
//========================================
void CMotion::SetModel(CObjectModel**ppObjectModel,int nNumModel)
{
	m_ppObjectModel = ppObjectModel;	// オブジェクトモデル
	m_nNumModel = nNumModel;			// モデルの総数
}