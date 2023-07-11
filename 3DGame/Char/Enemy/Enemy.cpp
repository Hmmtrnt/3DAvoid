#include "Enemy.h"
#include "../Player/Player.h"
#include "../Model.h"
#include <iostream>

namespace
{
	// キャラクターハンドル
	const char* const kEnemyHandle = "Data/3D/Char/Enemy/Enemy2(toonType2).mv1";

	// エネミーの最大スピード
	constexpr int kSpeed = 5;
}

Enemy::Enemy(std::shared_ptr<Player> pPlayer) :
	m_pPlayer(pPlayer)
{
	// モデルのロード
	m_modelHandle = MV1LoadModel(kEnemyHandle);

	// ポインタのメモリ確保
	m_pModel = std::make_shared<Model>(m_modelHandle);
	// 敵のアニメーション設定
	m_pModel->SetAnimation(m_animMove, true, true);
	// 敵の向きの初期化
	m_angle = GetRand(360) * DX_PI_F / 180;
	m_speed = static_cast<float>(GetRand(kSpeed) + 2);

	m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));
	m_pModel->SetScale(VGet(0.5f, 0.5f, 0.5f));
}

Enemy::Enemy(int orgModel, std::shared_ptr<Player> pPlayer) :
	m_pPlayer(pPlayer)
{
	// モデルのロード
	m_modelHandle = MV1LoadModel(kEnemyHandle);

	// ポインタのメモリ確保
	m_pModel = std::make_shared<Model>(m_modelHandle);
	// 敵のアニメーション設定
	m_pModel->SetAnimation(m_animMove, true, true);
	// 敵の向きの初期化
	m_angle = GetRand(360) * DX_PI_F / 180;
	m_speed = static_cast<float>(GetRand(kSpeed) + 2);

	m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));
	m_pModel->SetScale(VGet(0.5f, 0.5f, 0.5f));
	
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	UpdateMove();
}

void Enemy::Draw()
{
	RoundShadow(120.0f);
	m_pModel->Draw();
}

void Enemy::UpdateMove()
{
	m_pModel->Update();

	// 現在敵が向いている方向のベクトルを生成する
	EnemyBase::EnemyMove();

	// 座標の初期化
	// ステージの下
	if (m_pos.z < -1000.0f)
	{
		m_pos.z = 1000.0f;
		m_angle = GetRand(180) * DX_PI_F / 180;
		m_speed = static_cast<float>(GetRand(kSpeed) + 2);
	}
	// ステージの上
	if (m_pos.z > 1000.0f)
	{
		m_pos.z = -1000.0f;
		m_angle = GetRand(360) * DX_PI_F / 180;
		m_speed = static_cast<float>(GetRand(kSpeed) + 2);
	}
	// ステージの右
	if (m_pos.x > 1000.0f)
	{
		m_pos.x = -1000.0f;
		m_angle = GetRand(360) * DX_PI_F / 180;
		m_speed = static_cast<float>(GetRand(kSpeed) + 2);
	}
	// ステージの左
	if (m_pos.x < -1000.0f)
	{
		m_pos.x = 1000.0f;
		m_angle = GetRand(360) * DX_PI_F / 180;
		m_speed = static_cast<float>(GetRand(kSpeed) + 2);
	}

	m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.5f,m_angle,0.0f));
	m_pModel->SetScale(VGet(0.5f, 0.5f, 0.5f));
}

void Enemy::UpdateTitle()
{

	m_pModel->Update();

	m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.5f, m_angle, 0.0f));
	m_pModel->SetScale(VGet(0.5f, 0.5f, 0.5f));
}

bool Enemy::ColFlag()
{
	float colx = m_pPlayer->GetPos().x - m_pos.x;
	float coly = m_pPlayer->GetPos().y - m_pos.y;
	float colz = m_pPlayer->GetPos().z - m_pos.z;

	if (std::pow(colx,2.0f) + 
		std::pow(coly,2.0f) + 
		std::pow(colz,2.0f) <= std::pow(70.0f,2.0f)) {
		return true;
	}
	return false;
}