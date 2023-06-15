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

	void UpdateMove();// エネミーの動き

private:
	// ポインタ
	std::shared_ptr<Model> m_pModel;

	// VECTOR
	VECTOR m_EnemyPos;		// エネミー座標
	VECTOR m_EnemyVec;		// エネミー移動



	// vector
	//std::vector<int> m_enemies;// エネミーの数
};

