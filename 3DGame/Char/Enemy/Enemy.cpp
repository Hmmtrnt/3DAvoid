#include "Enemy.h"
#include "../Model.h"

namespace
{
	// キャラクターハンドル
	const char* const kEnemyHandle = "Data/Char/Enemy/enemy.mv1";

	// エネミーのモーション番号
	constexpr int kAnimMove = 2;// 移動状態
	

	// VECTORの初期化
	constexpr VECTOR kZero{ 0.0f,0.0f,0.0f };
	constexpr VECTOR kInitPos{ 0.0f,0.0f,1000.0f };
}

Enemy::Enemy() :
	m_updateFunc(&Enemy::UpdateMove),
	m_enemyAngle(0.0f)
{
	m_enemyPos = kInitPos;
	m_enemyVec = kZero;
	m_pModel = std::make_shared<Model>(kEnemyHandle);
	m_pModel->SetAnimation(kAnimMove, true, true);
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
}

void Enemy::End()
{
}

void Enemy::Update()
{
	(this->*m_updateFunc)();

	

	if (m_enemyPos.z <= -1000.0f)
	{
		m_enemyPos.z = 1000.0f;
	}
}

void Enemy::Draw()
{
	m_pModel->Draw();
}

void Enemy::UpdateMove()
{
	m_pModel->Update();
	m_enemyVec = VAdd(m_enemyVec, VGet(0.0f,0.0f,10.0f));

	if (VSize(m_enemyVec) < 0)
	{
		m_enemyVec = VNorm(m_enemyVec);
	}

	m_enemyVec = VScale(m_enemyVec, -1.0f);

	m_enemyPos = VAdd(m_enemyPos, m_enemyVec);

	m_pModel->SetPos(m_enemyPos);
	m_pModel->SetRot(kZero);

}
