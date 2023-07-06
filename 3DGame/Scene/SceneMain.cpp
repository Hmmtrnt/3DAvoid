#include "SceneMain.h"
#include "SceneTitle.h"// デバッグ用
#include "SceneResult.h"
#include "../Util/GameSetting.h"
#include "../Char/Player/Player.h"
#include "../Char/Enemy/Enemy.h"
#include "../Stage/Field.h"
#include "../Stage/Wall.h"
#include <cassert>
#include "../Util/FontFunction.h"
#include "../System/Pause.h"

namespace
{
	// 背景の画像ファイルの場所
	const char* const kImgName = "Data/BackGround/FieldBackGround.jpg";
}

SceneMain::SceneMain() :
	m_updateFunc(&SceneMain::UpdatePauseNo),
	m_shadowMap(0),
	m_invincibleTime(0),
	m_hpRedColor(0),
	m_hpColor(0),
	m_score(0),
	m_BackGroundHandle(-1),
	m_enemyModelHandle(0),
	m_fontHandle(-1),
	m_selectNum(0),
	m_hit(false),
	m_hitting(false),
	m_pushPause(false),
	m_isNoteOpen(false)
{
	// ポインタのメモリ確保後で自動的に解放される
	m_pSet = std::make_shared<GameSetting>();
	m_pPlayer = std::make_shared<Player>();
	m_pField = std::make_shared<Field>();
	m_pWall = std::make_shared<Wall>();
	m_pFont = std::make_shared<StringInit>();
	m_pPause = std::make_shared<Pause>();
	
	m_BackGroundHandle = LoadGraph(kImgName);
	assert(m_BackGroundHandle != -1);

	m_red = 255;

	m_decreaseColor = 255 - (m_pPlayer->GetBlowRate() * 2);
}

SceneMain::~SceneMain()
{
	DeleteGraph(m_BackGroundHandle);
}

void SceneMain::Init()
{
	m_pSet->Init3D();
	m_pSet->InitCamera();
	m_pPlayer->Init();
	m_pField->Init();
	m_pFont->Init(m_fontHandle, 30, 0, -1);

	m_hpColor = Color::kWhite;

	// 一体目のエネミー生成
	m_pEnemy.push_back(std::make_shared<Enemy>(m_pPlayer));
	m_pEnemy.back()->Init();

	// 二体目以降は一体目をコピー
	m_enemyModelHandle = m_pEnemy.back()->GetModelHandle();
	for (int i = 0; i < 19; i++)
	{
		m_debugEnemyNum++;
		m_pEnemy.push_back(std::make_shared<Enemy>(m_enemyModelHandle, m_pPlayer, m_debugEnemyNum));
		m_pEnemy.back()->Init();
	}

	// シャドウマップの生成
	m_shadowMap = MakeShadowMap(1024, 1024);
	SetShadowMapLightDirection(m_shadowMap, GetLightDirection());
}

void SceneMain::End()
{
	m_pPlayer->End();
	m_pFont->End(m_fontHandle);
	// シャドウマップの削除
	DeleteShadowMap(m_shadowMap);
}

// 更新処理
SceneBase* SceneMain::Update()
{
	// フェードインアウトしている
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// フェードアウト終了時
		// ポーズ画面が開かれているとき
		if (!IsFading() && m_isFadeOut && !m_isBackScene && m_isNoteOpen)
		{
			// リトライ
			return (new SceneMain());
			// ポーズ画面の項目が増える予定
		}
		// ポーズ画面が閉じているとき
		else if (!IsFading() && m_isFadeOut && !m_isBackScene && !m_isNoteOpen)
		{
			// ゲームが終了したとき
			return (new SceneResult(m_score));
		}

	}

	if (!IsFading())
	{
		// キャラが落ちたらまたは注意書きではいを押したらシーン遷移
		if (m_pPlayer->GetIsFall() || (Pad::IsTrigger(PAD_INPUT_1) && m_isNoteOpen))
		{
			//return new SceneMain;// デバッグ用シーン遷移

			StartFadeOut();// シーン遷移
		}
	}


	(this->*m_updateFunc)();

	if (m_score != 0)
	{
		// スコアが千を超えるたびに敵が増える　(パッドは敵を増やすデバッグ用)
		if (m_score % 1000 == 0 && m_score <= 4000 /*Pad::IsTrigger(PAD_INPUT_7)*/)
		{
			for (int i = 0; i < 10; i++)
			{
				m_debugEnemyNum++;
				m_pEnemy.push_back(std::make_shared<Enemy>(m_enemyModelHandle, m_pPlayer, m_debugEnemyNum));
				m_pEnemy.back()->Init();
			}
		}
	}
	

	// ポーズボタンを押したときの処理
	if (Pad::IsTrigger(PAD_INPUT_8))
	{
		m_pushPause = true;
	}
	// やり直すを押したときの処理
	if (m_selectNum == 1 && Pad::IsTrigger(PAD_INPUT_1))
	{
		m_isNoteOpen = true;
		
	}

	if (m_isNoteOpen)
	{
		if (Pad::IsTrigger(PAD_INPUT_2))
		{
			m_isNoteOpen = false;
		}
	}
	

	

	return this;
}

// 描画処理
void SceneMain::Draw()
{
	// 背景の描画
	DrawBillboard3D(VGet(-1900.0f, 0.0f, 975.0f), 0.5f, 0.5f, 8000.0f, 0.0f, m_BackGroundHandle, true);

	// プレイヤーの描画
	if (m_invincibleTime % 3 == 0 || m_pushPause)
	{
		m_pPlayer->Draw();
	}

	// 敵の描画
	for (auto& enemies : m_pEnemy)
	{
		enemies->Draw();
	}
	// ステージ描画
	m_pField->Draw();
	//m_pWall->Draw();

	// 受けたダメージによって色変更
	UpdateColor();

	// 文字を見やすくする
	SetDrawBlendMode(DX_BLENDMODE_MULA, 155);
	DrawBox(0, 85, 300, 250, Color::kBlack, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// プレイヤーの吹っ飛び率描画
	DrawFormatStringToHandle(10, 90, m_hpColor, m_fontHandle,"%d%%", m_pPlayer->GetBlowRate());

	// スコア描画
	DrawFormatStringToHandle(10, 120, Color::kWhite, m_fontHandle, "score:%d", m_score);

	// ゲームオーバーになった時の処理(デバッグ用)
	/*if (m_pPlayer->GetPos().y < -100.0f)
	{
		DrawStringToHandle(0, 150, "ゲームオーバー", Color::kWhite, m_fontHandle);
		DrawStringToHandle(0, 180, "リザルト:PAD_INPUT_1", Color::kWhite, m_fontHandle);

	}*/

	// ポーズ画面描画
	if (m_pushPause)
	{
		m_pPause->DrawPause();

		if (m_isNoteOpen)
		{
			m_pPause->DrawNote();
		}

		
	}

	// フェードインアウトのフィルター
	SceneBase::DrawFade();

}

void SceneMain::UpdateEnemy()
{
	// 当たった時の処理
	for (auto& enemies : m_pEnemy)
	{
		enemies->Update();
		if (m_invincibleTime <= 0)
		{
			// 当たった時のダメージ追加
			if (enemies->ColFlag())
			{
				DrawString(10, 10, "当たっている\n", 0xff0000);
				m_pPlayer->UpdateHitDamage(enemies->GetPos(), m_hit);
				m_hit = true;
				m_invincibleTime = 120;
			}
		}
	}
	// 当たった時のプレイヤーの座標処理
	if(m_invincibleTime >= 110)
	{
		m_hitting = true;
		m_pPlayer->UpdateHitVec();
	}
	// 当たっていない状態に戻す
	if (m_invincibleTime < 110)
	{
		m_hit = false;
		m_hitting = false;
	}

	// 数字が限界突破しないようにする
	if (m_invincibleTime > 0)
	{
		m_invincibleTime--;
	}

	if (m_pPlayer->GetIsFall())
	{
		m_invincibleTime = 0;
	}
}

void SceneMain::UpdateColor()
{
	// -------------------------
	// ボツの可能性あり
	// -------------------------
	// ダメージによって色を変更
	//m_hpColor = GetColor(m_red, m_decreaseColor, m_decreaseColor);

	//// 体力表記の色バグを防ぐ
	//if (m_decreaseColor < 0)
	//{
	//	m_decreaseColor = 0;
	//}
	//else if(m_decreaseColor != 0)
	//{
	//	m_decreaseColor = 255 - (m_pPlayer->GetBlowRate() * 2);
	//}

	// -------------------------
	// 新しい色表記
	// -------------------------
	// ダメージによって色を変更
	if (m_pPlayer->GetBlowRate() < 11)
	{
		m_hpColor = Color::kWhite;
	}
	else if (m_pPlayer->GetBlowRate() < 31)
	{
		m_hpColor = Color::kCoral;
	}
	else if (m_pPlayer->GetBlowRate() < 61)
	{
		m_hpColor = Color::kTomato;
	}
	else if (m_pPlayer->GetBlowRate() < 81)
	{
		m_hpColor = Color::kOrangered;
	}
	else if (m_pPlayer->GetBlowRate() < 101)
	{
		m_hpColor = Color::kRed;
	}
	

}

void SceneMain::UpdatePauseNo()
{
	m_pPlayer->Update(m_hitting);
	UpdateEnemy();

	// ゲームが進んでいる間スコアを増やす
	if (!m_pPlayer->GetIsFall())
	{
		m_score+=100;
	}
	if (m_pushPause)
	{
		m_updateFunc = &SceneMain::UpdatePause;
	}
}

void SceneMain::UpdatePause()
{
	// フェードインアウトしていなければポーズ画面をいじれる
	if (!IsFading())
	{
		if (!m_isNoteOpen)
		{
			m_pPause->Update(m_selectNum);
		}
	}
	
	if (!m_pushPause)
	{
		m_updateFunc = &SceneMain::UpdatePauseNo;
	}

	if (m_selectNum == 0 && Pad::IsTrigger(PAD_INPUT_1))
	{
		m_pushPause = false;
	}

	// 選択肢がどこを選んでいるか確認
	//printfDx("%d", m_selectNum);
}
