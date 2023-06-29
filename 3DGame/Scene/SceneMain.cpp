#include "SceneMain.h"
#include "SceneTitle.h"// デバッグ用
#include "SceneResult.h"
#include "../Util/GameSetting.h"
#include "../Char/Player/Player.h"
#include "../Char/Enemy/Enemy.h"
#include "../Stage/Field.h"
#include <cassert>
#include "../Util/FontFunction.h"
#include "../System/Pause.h"

namespace
{
	// 画像のファイルの場所
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
	m_hit(false),
	m_hitting(false),
	m_pushPause(false)
{
	// ポインタのメモリ確保後で自動的に解放される
	m_pSet = std::make_shared<GameSetting>();
	m_pPlayer = std::make_shared<Player>();
	m_pField = std::make_shared<Field>();
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
	m_pFont->Init(30, 0, -1);

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
	m_pFont->End();
	// シャドウマップの削除
	DeleteShadowMap(m_shadowMap);
}

// 更新処理
SceneBase* SceneMain::Update()
{
	(this->*m_updateFunc)();

	if (m_score != 0)
	{
		if (m_score % 1000 == 0 /*Pad::IsTrigger(PAD_INPUT_7)*/)
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
		if (!m_pushPause)
		{
			m_pushPause = true;
		}
		else
		{
			m_pushPause = false;
		}
	}

	// フェードインアウトしている
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// フェードアウト終了時
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			return (new SceneResult);
		}
	}

	if (m_pPlayer->GetIsFall())
	{
		if (!IsFading())
		{
			//TODO:PAD_INPUT_1に戻す(デバッグが終わったら)
			if (Pad::IsTrigger(PAD_INPUT_4))
			{
				return new SceneMain;// デバッグ用シーン遷移

				//StartFadeOut();// 本番用シーン遷移
			}
		}
	}

	return this;
}

// 描画処理
void SceneMain::Draw()
{
	// 背景の描画
	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_BackGroundHandle, true);

	// プレイヤーの描画
	if (m_invincibleTime % 3 == 0)
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

	// 受けたダメージによって色変更
	UpdateColor();

	// 文字を見やすくする
	SetDrawBlendMode(DX_BLENDMODE_MULA, 155);
	DrawBox(0, 85, 300, 250, Color::kBlack, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// プレイヤーの吹っ飛び率描画
	m_pFont->DrawFormat(10, 90, m_hpColor, "%d%%", m_pPlayer->GetBlowRate());

	// スコア描画
	m_pFont->DrawFormat(10, 120, Color::kWhite, "score:%d", m_score);

	// ゲームオーバーになった時の処理
	if (m_pPlayer->GetPos().y < -100.0f)
	{
		m_pFont->DrawNoFormat(0, 150, "ゲームオーバー", Color::kWhite);
		m_pFont->DrawNoFormat(0, 180, "リトライ:PAD_INPUT_4", Color::kWhite);

	}

	if (m_pushPause)
	{
		m_pPause->Draw();
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
			
		// 敵に当たった時のコントローラーの振動
		StartJoypadVibration(DX_INPUT_PAD1, 300, 100, -1);

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
	

	m_hpColor = GetColor(m_red, m_decreaseColor, m_decreaseColor);

	if (m_decreaseColor < 0)
	{
		m_decreaseColor = 0;
	}
	else if(m_decreaseColor != 0)
	{
		m_decreaseColor = 255 - (m_pPlayer->GetBlowRate() * 2);
	}

}

void SceneMain::UpdatePauseNo()
{
	m_pPlayer->Update(m_hitting);
	UpdateEnemy();

	// ゲームが進んでいる間スコアを増やす
	if (!m_pPlayer->GetIsFall())
	{
		m_score++;
	}
	if (m_pushPause)
	{
		m_updateFunc = &SceneMain::UpdatePause;
	}
}

void SceneMain::UpdatePause()
{
	m_pPause->Update();
	if (!m_pushPause)
	{
		m_updateFunc = &SceneMain::UpdatePauseNo;
	}
}
