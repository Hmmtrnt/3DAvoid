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

Enemy::Enemy()
{
	m_EnemyPos = kInitPos;
	m_EnemyVec = kZero;
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
	m_pModel->Update();

	m_pModel->ChangeAnimation(kAnimMove, true, true, 5);

	UpdateMove();

	m_pModel->SetPos(m_EnemyPos);
	m_pModel->SetRot(kZero);
}

void Enemy::Draw()
{
	m_pModel->Draw();
}

void Enemy::UpdateMove()
{
	m_EnemyVec = VAdd(m_EnemyVec, VGet(0.0f,0.0f,-1.0f));

	if (VSize(m_EnemyVec) < 0)
	{
		m_EnemyVec = VNorm(m_EnemyVec);
	}

	m_EnemyVec = VScale(m_EnemyVec, -1.0f);

	m_EnemyPos = VAdd(m_EnemyPos, m_EnemyVec);
}
