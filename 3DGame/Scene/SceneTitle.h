#pragma once
#include "SceneBase.h"
#include "../Util/common.h"
#include <vector>
#include <memory>

class GameSetting;
class Player;
class Enemy;
class EnemyBig;
class Field;

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	void Init();
	void End();
	SceneBase* Update();
	void Draw();

private:
	// ポインタ
	std::shared_ptr<GameSetting> m_pSet;// 環境設定
	std::shared_ptr<Player> m_pPlayer;// プレイヤー
	std::vector<std::shared_ptr<Enemy>> m_pEnemy;// エネミー
	std::shared_ptr<EnemyBig> m_pEnemyBig;// 大きいエネミー
	std::shared_ptr<Field> m_pField;// ステージ

	// int
	int m_titleHandle;// タイトルの画像ハンドル
	int m_backGroundHandle;// 背景ハンドル
	int m_enemyHandle;// エネミーハンドル
	int m_roundShadowHandle[4];// 丸影ハンドル
};

