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

private:
	// �|�C���^
	std::shared_ptr<Model> m_pModel;

	// VECTOR
	VECTOR m_EnemyPos;		// �G�l�~�[���W
	VECTOR m_EnemyVec;		// �G�l�~�[�ړ�



	// vector
	//std::vector<int> m_enemies;// �G�l�~�[�̐�
};

