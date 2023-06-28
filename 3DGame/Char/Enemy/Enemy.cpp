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
	m_modelHandle(-1),
	m_playerPos(kZero),
	m_Number(0)
{
	// 敵の初期位置
	m_pos.x = 1000;
	//m_pos.x = 500.0f;
	m_pos.y = 0.0f;
	m_pos.z = static_cast<float>(GetRand(2000) - 1000);
	//m_pos.z = 0;

	// モデルのロード
	m_modelHandle = MV1LoadModel(kEnemyHandle);

	// ポインタのメモリ確保
	m_pModel = std::make_shared<Model>(m_modelHandle);
	// 敵のアニメーション設定
	m_pModel->SetAnimation(kAnimMove, true, true);
	// 敵の向きの初期化
	m_angle = GetRand(360) * DX_PI_F / 180;
}

Enemy::Enemy(int orgModel, std::shared_ptr<Player> pPlayer, int num) :
	m_updateFunc(&Enemy::UpdateMove),
	m_pPlayer(pPlayer),
	m_angle(0.0f),
	m_modelHandle(-1),
	m_playerPos(kZero),
	m_Number(num)
{
	// 敵の初期位置
	m_pos.x = 1000;
	//m_pos.x = -500.0f;
	//m_pos.x = static_cast<float>(GetRand(1000) -1000);
	m_pos.y = 0.0f;
	m_pos.z = static_cast<float>(GetRand(2000) - 1000);
	//m_pos.z = 0;

	// モデルのロード
	m_modelHandle = MV1LoadModel(kEnemyHandle);

	// ポインタのメモリ確保
	m_pModel = std::make_shared<Model>(m_modelHandle);
	// 敵のアニメーション設定
	m_pModel->SetAnimation(kAnimMove, true, true);
	// 敵の向きの初期化
	m_angle = GetRand(360) * DX_PI_F / 180;

	
}

Enemy::~Enemy()
{
	// モデルのメモリ削除
	MV1DeleteModel(m_modelHandle);
	MV1DeleteModel(m_playerHandle);
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
}

void Enemy::Draw()
{
	m_pModel->Draw();
	DebugDraw();
}

void Enemy::UpdateMove()
{
	m_pModel->Update();

	// 現在敵が向いている方向のベクトルを生成する
	MATRIX enemyRotMtx = MGetRotY(m_angle);
	m_dir = VTransform(kEnemyDir, enemyRotMtx);
	// 移動速度を反映させる
	m_vec = VScale(m_dir, kSpeed);
	// 移動させる
	m_pos = VAdd(m_pos, m_vec);


	// 座標の初期化
	// ステージの下
	if (m_pos.z < -1000.0f)
	{
		m_pos.z = 1000.0f;
		m_angle = GetRand(360) * DX_PI_F / 180;
	}
	// ステージの上
	if (m_pos.z > 1000.0f)
	{
		m_pos.z = -1000.0f;
		m_angle = GetRand(360) * DX_PI_F / 180;
	}
	// ステージの右
	if (m_pos.x > 1000.0f)
	{
		m_pos.x = -1000.0f;
		m_angle = GetRand(360) * DX_PI_F / 180;
	}
	// ステージの左
	if (m_pos.x < -1000.0f)
	{
		m_pos.x = 1000.0f;
		m_angle = GetRand(360) * DX_PI_F / 180;
	}

	m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f,m_angle,0.0f));
	m_pModel->SetScale(VGet(0.5f, 0.5f, 0.5f));
}

void Enemy::DebugDraw()
{
	// モデルのハンドル取得
	int handle = m_pModel->getModelHandle();

	// モデル内にあるHPバーを表示する座標のデータを取得する
	int frameNo = MV1SearchFrame(handle, "Head3_end");
	// HPバーを表示する座標データのワールド座標を取得する
	VECTOR hpPos = MV1GetFramePosition(handle, frameNo);
	// HPバー表示位置のワールド座標をスクリーン座標に変換する
	VECTOR screenPos = ConvWorldPosToScreenPos(hpPos);
	if ((screenPos.z <= 0.0f) || (screenPos.z >= 1.0f))
	{
		// 表示範囲外の場合何も表示しない
		return;
	}

	DrawFormatString(static_cast<int>(screenPos.x) - 64 / 2, static_cast<int>(screenPos.y),0xffffff, "%d", m_Number);
}

bool Enemy::ColFlag()
{
	float colx = m_pPlayer->GetPos().x - m_pos.x;
	float coly = m_pPlayer->GetPos().y - m_pos.y;
	float colz = m_pPlayer->GetPos().z - m_pos.z;

	if (std::pow(colx,2.0f) + 
		std::pow(coly,2.0f) + 
		std::pow(colz,2.0f) <= std::pow(100.0f,2.0f)) {
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

void Enemy::SetPlayerPos(VECTOR playerPos)
{
	m_playerPos = playerPos;
}
