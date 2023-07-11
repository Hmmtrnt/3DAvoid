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
	// �|�C���^
	std::shared_ptr<GameSetting> m_pSet;// ���ݒ�
	std::shared_ptr<Player> m_pPlayer;// �v���C���[
	std::shared_ptr<Enemy> m_pEnemy;// �G�l�~�[

	// int
	int m_titleHandle;// �^�C�g���̉摜�n���h��
	int m_backGroundHandle;// �w�i�n���h��
};

