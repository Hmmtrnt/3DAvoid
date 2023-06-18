#pragma once
#include "SceneBase.h"
#include "../Util/common.h"
#include <memory>
#include <vector>

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

private:
	// ゲームの設定ポインタ
	/*GameSetting* m_pSet;
	Player* m_pPlayer;
	Enemy* m_pEnemy;
	Field* m_pField;*/

	std::shared_ptr<GameSetting> m_pSet;
	std::shared_ptr<Player> m_pPlayer;
	//std::shared_ptr<Enemy> m_pEnemy;
	std::shared_ptr<Field> m_pField;

	std::vector<std::shared_ptr<Enemy>> m_pEnemy;

};
