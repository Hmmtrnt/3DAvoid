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

	// エネミーの向いている方向
	constexpr VECTOR kEnemyDir{ 0.0f,0.0f,-1.0f };

	// 当たり判定のサイズ
	constexpr float kColRadius = 50.0f;
}

Enemy::Enemy(/*const char* fileName, */std::shared_ptr<Player> pPlayer) :
	m_updateFunc(&Enemy::UpdateMove),
	m_pPlayer(pPlayer),
	m_angle(0.0f)
{
	m_pos.x = GetRand(2000) - 1000;;
	m_pos.y = 0.0f;
	m_pos.z = GetRand(2000) - 1000;

	m_pModel = std::make_shared<Model>(kEnemyHandle);
	m_pModel->SetAnimation(kAnimMove, true, true);
}

Enemy::Enemy(int orgModel, std::shared_ptr<Player> pPlayer) :
	m_updateFunc(&Enemy::UpdateMove),
	m_pPlayer(pPlayer),
	m_angle(0.0f)
{
	m_pos.x = GetRand(2000) - 1000;;
	m_pos.y = 0.0f;
	m_pos.z = GetRand(2000) - 1000;
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

	

	/*if (m_pos.z <= -1000.0f)
	{
		m_pos.z = 1000.0f;
	}*/
}

void Enemy::Draw()
{
	m_pModel->Draw();
}

void Enemy::UpdateMove()
{
	m_pModel->Update();

	// 現在敵が向いている方向のベクトルを生成する
	MATRIX enemyRotMtx = MGetRotY(m_angle);
	VECTOR dir = VTransform(kEnemyDir, enemyRotMtx);
	// 敵からプレイヤーへのベクトル（正規化）
	VECTOR toPlayer = VSub(m_pPlayer->GetPos(), m_pos);
	toPlayer = VNorm(toPlayer);
	// 内積から角度を求める
	float dot = VDot(dir, toPlayer);
	float angle = acosf(dot);

	m_pModel->SetPos(m_pos);
	m_pModel->SetRot(kZero);

}

int Enemy::GetModelHandle() const
{
	return 0;
}

float Enemy::GetColRadius()
{
	return kColRadius;
}
