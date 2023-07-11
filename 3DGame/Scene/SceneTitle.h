#pragma once
#include "SceneBase.h"
#include "../Util/common.h"
#include <memory>

class GameSetting;
class Player;
class Enemy;

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
	std::shared_ptr<Enemy> m_pEnemy;// エネミー

	// int
	int m_titleHandle;// タイトルの画像ハンドル
	int m_backGroundHandle;// 背景ハンドル
};

