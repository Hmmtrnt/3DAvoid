#pragma once
#include "SceneBase.h"
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

private:
	// �Q�[���̐ݒ�|�C���^
	GameSetting* m_pSet;
	Player* m_pPlayer;
	Enemy* m_pEnemy;
	Field* m_pField;


};
