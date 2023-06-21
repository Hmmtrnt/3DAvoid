#include "Enemy.h"
#include "../Player/Player.h"
#include "../Model.h"
#include <iostream>

namespace
{
	// キャラクターハンドル
	const char* const kEnemyHandle = "Data/Char/Enemy/enemy.mv1";
	// プレイヤーハンドル
	const char* const kPlayerHandle = "Data/Char/Player/Player5.mv1";

	// エネミーのモーション番号
	constexpr int kAnimMove = 2;// 移動状態

	constexpr float kSpeed = 5.0f;
	

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
	m_angle(0.0f),
	m_modelHandle(-1)
{
	//m_pos.x = GetRand(2000) - 1000;
	m_pos.x = 1000.0f;
	m_pos.y = 0.0f;
	m_pos.z = GetRand(2000) - 1000;

	m_modelHandle = MV1LoadModel(kEnemyHandle);// モデルのロード

	m_pModel = std::make_shared<Model>(m_modelHandle);
	m_pModel->SetAnimation(kAnimMove, true, true);
	m_angle = GetRand(360) * DX_PI_F / 180;
}

Enemy::Enemy(int orgModel, std::shared_ptr<Player> pPlayer) :
	m_updateFunc(&Enemy::UpdateMove),
	m_pPlayer(pPlayer),
	m_angle(0.0f),
	m_modelHandle(-1)
{
	//m_pos.x = GetRand(2000) - 1000;
	m_pos.x = 1000.0f;
	m_pos.y = 0.0f;
	m_pos.z = GetRand(2000) - 1000;

	m_modelHandle = MV1LoadModel(kEnemyHandle);
	m_playerHandle = MV1LoadModel(kPlayerHandle);

	m_pModel = std::make_shared<Model>(m_modelHandle);
	m_pModel->SetAnimation(kAnimMove, true, true);

	m_angle = GetRand(360) * DX_PI_F / 180;

	
}

Enemy::~Enemy()
{
	MV1DeleteModel(m_modelHandle);
	MV1DeleteModel(m_playerHandle);
	//MV1CollResultPolyDimTerminate(test);
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

	//test = MV1CollCheck_Sphere(m_playerHandle, -1, GetPos(), 100.0f);

	//// 当たったかどうかで処理を分岐
	//if (test.HitNum >= 1)
	//{
	//	// 当たった場合は衝突の情報を描画する

	//	// 当たったポリゴンの数を描画
	//	DrawFormatString(0, 0, GetColor(255, 255, 255), "Hit Poly Num   %d", test.HitNum);

	//	printfDx("当たった\n");

	//	// 当たったポリゴンの数だけ繰り返し
	//	for (int i = 0; i < test.HitNum; i++)
	//	{
	//		// 当たったポリゴンを描画
	//		DrawTriangle3D(
	//			test.Dim[i].Position[0],
	//			test.Dim[i].Position[1],
	//			test.Dim[i].Position[2], GetColor(0, 255, 255), TRUE);
	//	}
	//}
	/*if (m_pos.z <= -1000.0f)
	{
		m_pos.z = 1000.0f;
	}*/

	//MV1SetPosition(m_playerHandle, m_pPlayer->GetPos());
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
	// 移動速度を反映させる
	VECTOR vec = VScale(dir, kSpeed);
	// 移動させる
	m_pos = VAdd(m_pos, vec);


	// 座標の初期化
	if (m_pos.z < -1000.0f)
	{
		m_pos.z = 1000.0f;
	}
	if (m_pos.z > 1000.0f)
	{
		m_pos.z = -1000.0f;
	}
	if (m_pos.x > 1000.0f)
	{
		m_pos.x = -1000.0f;
	}
	if (m_pos.x < -1000.0f)
	{
		m_pos.x = 1000.0f;
	}

	m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f,m_angle,0.0f));
	m_pModel->SetScale(VGet(0.5f, 0.5f, 0.5f));
}

bool Enemy::ColFlag()
{
	int colx = m_pPlayer->GetPos().x - m_pos.x;
	int coly = m_pPlayer->GetPos().y - m_pos.y;
	int colz = m_pPlayer->GetPos().z - m_pos.z;

	if (std::pow(colx,2.0f) +
		std::pow(coly,2.0f) +
		std::pow(colz,2.0f) <= 
		std::pow(100.0f,2.0f)) {
		return true;
	}
	return false;
}

int Enemy::GetModelHandle() const
{
	return m_modelHandle;
}

float Enemy::GetColRadius()
{
	return kColRadius;
}
