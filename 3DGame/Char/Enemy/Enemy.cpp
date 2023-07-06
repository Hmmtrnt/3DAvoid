#include "Enemy.h"
#include "../Player/Player.h"
#include "../Model.h"
#include <iostream>

namespace
{
	// キャラクターハンドル
	const char* const kEnemyHandle = "Data/Char/Enemy/Enemy2(toonType2).mv1";

	// エネミーのモーション番号
	constexpr int kAnimMove = 2;// 移動状態
	//constexpr int kAnimAttack = 3;// 攻撃状態

	// エネミーの最大スピード
	constexpr int kSpeed = 5;
	

	// VECTORの初期化
	constexpr VECTOR kZero{ 0.0f,0.0f,0.0f };
	constexpr VECTOR kInitPos{ 0.0f,0.0f,1000.0f };

	// エネミーの向いている方向
	constexpr VECTOR kEnemyDir{ 0.0f,0.0f,-1.0f };

	// 当たり判定のサイズ
	constexpr float kColRadius = 50.0f;
}

Enemy::Enemy(std::shared_ptr<Player> pPlayer) :
	m_pPlayer(pPlayer)
{
	// モデルのロード
	m_modelHandle = MV1LoadModel(kEnemyHandle);

	// ポインタのメモリ確保
	m_pModel = std::make_shared<Model>(m_modelHandle);
	// 敵のアニメーション設定
	m_pModel->SetAnimation(kAnimMove, true, true);
	// 敵の向きの初期化
	m_angle = GetRand(360) * DX_PI_F / 180;
	m_speed = static_cast<float>(GetRand(kSpeed) + 2);
}

Enemy::Enemy(int orgModel, std::shared_ptr<Player> pPlayer) :
	m_pPlayer(pPlayer)
{
	// モデルのロード
	m_modelHandle = MV1LoadModel(kEnemyHandle);

	// ポインタのメモリ確保
	m_pModel = std::make_shared<Model>(m_modelHandle);
	// 敵のアニメーション設定
	m_pModel->SetAnimation(kAnimMove, true, true);
	// 敵の向きの初期化
	m_angle = GetRand(360) * DX_PI_F / 180;
	m_speed = static_cast<float>(GetRand(kSpeed) + 2);

	m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));
	m_pModel->SetScale(VGet(0.5f, 0.5f, 0.5f));
	
}

Enemy::~Enemy()
{
	// モデルのメモリ削除
	MV1DeleteModel(m_modelHandle);
}

void Enemy::Update()
{
	UpdateMove();
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
	m_dir = VTransform(kEnemyDir, enemyRotMtx);
	// 移動速度を反映させる
	m_vec = VScale(m_dir, m_speed);
	// 移動させる
	m_pos = VAdd(m_pos, m_vec);


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
	m_pModel->SetRot(VGet(0.0f,m_angle,0.0f));
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