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
	// �|�C���^
	std::shared_ptr<GameSetting> m_pSet;// ���ݒ�
	std::shared_ptr<Player> m_pPlayer;// �v���C���[
	std::vector<std::shared_ptr<Enemy>> m_pEnemy;// �G�l�~�[
	std::shared_ptr<EnemyBig> m_pEnemyBig;// �傫���G�l�~�[
	std::shared_ptr<Field> m_pField;// �X�e�[�W

	// int
	int m_titleHandle;// �^�C�g���̉摜�n���h��
	int m_backGroundHandle;// �w�i�n���h��
	int m_enemyHandle;// �G�l�~�[�n���h��
	int m_roundShadowHandle[4];// �ۉe�n���h��
};

