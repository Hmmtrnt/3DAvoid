#include "SceneMain.h"
#include "SceneTitle.h"
#include "../Util/GameSetting.h"
#include "../Char/Player/Player.h"
#include "../Char/Enemy/Enemy.h"
#include "../Stage/Field.h"

namespace
{
	
}

SceneMain::SceneMain() :
	m_shadowMap(0),
	m_invincibleTime(0),
	m_hpRedColor(0),
	m_hpColor(0),
	m_score(0),
	m_hit(false),
	m_hitting(false)
{
	m_pSet = std::make_shared<GameSetting>();
	m_pPlayer = std::make_shared<Player>();
	m_pField = std::make_shared<Field>();
	
	
}

SceneMain::~SceneMain()
{
	
}

void SceneMain::Init()
{
	m_pSet->Init3D();
	m_pSet->InitCamera();
	m_pPlayer->Init();
	m_pField->Init();

	m_hpRedColor = m_pPlayer->GetBlowRate();

	m_hpColor = GetColor(m_hpRedColor, 0, 0);

	// 一体目のエネミー生成
	m_pEnemy.push_back(std::make_shared<Enemy>(m_pPlayer));
	m_pEnemy.back()->Init();

	// 二体目以降は一体目をコピー
	int enemyModelHandle = m_pEnemy.back()->GetModelHandle();
	for (int i = 0; i < 19; i++)
	{
		m_debugEnemyNum++;
		m_pEnemy.push_back(std::make_shared<Enemy>(enemyModelHandle, m_pPlayer, m_debugEnemyNum));
		m_pEnemy.back()->Init();
	}

	// シャドウマップの生成
	m_shadowMap = MakeShadowMap(1024, 1024);
	SetShadowMapLightDirection(m_shadowMap, GetLightDirection());
}

void SceneMain::End()
{
	m_pPlayer->End();
	// シャドウマップの削除
	DeleteShadowMap(m_shadowMap);
}

// 更新処理
SceneBase* SceneMain::Update()
{
	m_pPlayer->Update(m_hitting);
	UpdateEnemy();
	
	// ゲームが進んでいる間スコアを増やす
	if (!m_pPlayer->GetIsFall())
	{
		m_score++;
	}
	
	// ゲームオーバーになった時の処理
	if (m_pPlayer->GetPos().y < -100.0f)
	{
		DrawString(0, 130, "ゲームオーバー", 0xffffff);
		DrawString(0, 150, "リトライ:PAD_INPUT_4", 0xffffff);
	}
	if (m_pPlayer->GetIsFall())
	{
		if (Pad::IsTrigger(PAD_INPUT_4))
		{
			return new SceneMain;
		}
	}

	return this;
}

// 描画処理
void SceneMain::Draw()
{
	if (m_invincibleTime % 3 == 0)
	{
		m_pPlayer->Draw();
	}

	for (auto& enemies : m_pEnemy)
	{
		enemies->Draw();
	}
	m_pField->Draw();

	DrawFormatString(10, 30, Color::kCoral, "%d", m_pPlayer->GetBlowRate());
	DrawFormatString(10, 50, Color::kTomato, "%d", m_pPlayer->GetBlowRate());
	DrawFormatString(10, 70, Color::kOrangered, "%d", m_pPlayer->GetBlowRate());
	DrawFormatString(10, 90, Color::kRed, "%d", m_pPlayer->GetBlowRate());
	DrawFormatString(10, 110, Color::kRed, "%d", m_score);


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
				m_pPlayer->UpdateHitDamage();
				m_invincibleTime = 120;
			}
		}
		// 当たった時のプレイヤーの座標処理
		if(m_invincibleTime >= 110)
		{
			m_hitting = true;
			m_pPlayer->UpdateHitVec(enemies->GetPos(), m_hit);
			m_hit = true;
		}
		// 当たっていない状態に戻す
		if (m_invincibleTime < 110)
		{
			m_hit = false;
			m_hitting = false;
		}

	}

	if (m_invincibleTime > 0)
	{
		m_invincibleTime--;
	}
}
