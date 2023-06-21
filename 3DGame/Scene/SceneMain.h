#pragma once
#include "SceneBase.h"
#include "../Util/common.h"
#include <memory>
#include <vector>
#include "../Util/common.h"

class GameSetting;
class Player;
class Enemy;
class Field;

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();

	void Init();
	void End();
	SceneBase* Update();
	void Draw();

	void UpdateEnemy();
	//void UpdateHit();

private:
	// ゲームの設定ポインタ
	std::shared_ptr<GameSetting> m_pSet;// 環境設定
	std::shared_ptr<Player> m_pPlayer;// プレイヤー
	std::shared_ptr<Field> m_pField;// ステージ

	std::vector<std::shared_ptr<Enemy>> m_pEnemy;// エネミー

	// int
	int m_shadowMap; // シャドウマップ

	int m_invincibleTime;// プレイヤーの無敵時間

	int m_hpRedColor;// Hpのカラー赤

	unsigned int m_hpColor;// Hpのカラー
};
