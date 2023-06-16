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

	// メンバ関数ポインタ
	void(Enemy::* m_updateFunc)();

private:
	// ポインタ
	std::shared_ptr<Model> m_pModel;

	// VECTOR
	VECTOR m_enemyPos;		// エネミー座標
	VECTOR m_enemyVec;		// エネミー移動

	// float
	float m_enemyAngle;		// エネミーのアングル

	// vector
	//std::vector<int> m_enemies;// エネミーの数
};

