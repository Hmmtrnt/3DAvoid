#pragma once
#include "../../Util/common.h"
#include <memory>
#include <vector>

class Model;

class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	void Init();
	void End();
	void Update();
	void Draw();

	void UpdateMove();// �G�l�~�[�̓���

	// �����o�֐��|�C���^
	void(Enemy::* m_updateFunc)();

private:
	// �|�C���^
	std::shared_ptr<Model> m_pModel;

	// VECTOR
	VECTOR m_enemyPos;		// �G�l�~�[���W
	VECTOR m_enemyVec;		// �G�l�~�[�ړ�

	// float
	float m_enemyAngle;		// �G�l�~�[�̃A���O��

	// vector
	//std::vector<int> m_enemies;// �G�l�~�[�̐�
};

