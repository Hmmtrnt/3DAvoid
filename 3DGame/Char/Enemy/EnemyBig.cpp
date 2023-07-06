#include "EnemyBig.h"
#include "../Player/Player.h"
#include "../Model.h"
#include <iostream>

namespace
{
	// キャラクターハンドル
	const char* const kEnemyHandle = "Data/Char/Enemy/Enemy3(toonType2).mv1";

	// エネミーのモーション番号
	constexpr int kAnimMove = 2;// 移動状態
	//constexpr int kAnimAttack = 3;// 攻撃状態

	// エネミーの初期スピード
	constexpr int kSpeed = 3;


	// VECTORの初期化
	constexpr VECTOR kZero{ 0.0f,0.0f,0.0f };
	constexpr VECTOR kInitPos{ 0.0f,0.0f,1000.0f };

	// エネミーの向いている方向
	constexpr VECTOR kEnemyDir{ 0.0f,0.0f,-1.0f };

	// 当たり判定のサイズ
	constexpr float kColRadius = 50.0f;

	// どこまでいけるかのステージのサイズ
	constexpr float kColStage = 1200.0f;

	// エネミーのアングル
	constexpr float kAnglePI = DX_PI_F / 180.0f;
	constexpr float kAngleUp = 180.0f * kAnglePI;// 上
	constexpr float kAngleDown = 0.0f * kAnglePI;// 下
	constexpr float kAngleLeft = 90.0f * kAnglePI;// 左
	constexpr float kAngleRight = 270.0f * kAnglePI;// 右
}

EnemyBig::EnemyBig(std::shared_ptr<Player> pPlayer) :
	m_pPlayer(pPlayer),
	m_randAngleType(0),
	m_initPos(true)
{
	// モデルのロード
	m_modelHandle = MV1LoadModel(kEnemyHandle);

	// ポインタのメモリ確保
	m_pModel = std::make_shared<Model>(m_modelHandle);
	// 敵のアニメーション設定
	m_pModel->SetAnimation(kAnimMove, true, true);
	// 敵の向きの初期化
	m_angle = kAngleLeft;
	m_speed = kSpeed;

	m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));
	m_pModel->SetScale(VGet(0.5f, 0.5f, 0.5f));
}

EnemyBig::EnemyBig(int orgModel, std::shared_ptr<Player> pPlayer) :
	m_pPlayer(pPlayer),
	m_initPos(true)
{
	// モデルのロード
	m_modelHandle = MV1LoadModel(kEnemyHandle);

	// ポインタのメモリ確保
	m_pModel = std::make_shared<Model>(m_modelHandle);
	// 敵のアニメーション設定
	m_pModel->SetAnimation(kAnimMove, true, true);
	// 敵の向きの初期化
	//m_angle = GetRand(360) * DX_PI_F / 180;
	m_speed = kSpeed;

	m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));
	m_pModel->SetScale(VGet(3.0f, 3.0f, 3.0f));

}

EnemyBig::~EnemyBig()
{
	// モデルのメモリ削除
	MV1DeleteModel(m_modelHandle);
}

void EnemyBig::Update(int score)
{
	UpdateMove(score);
}

void EnemyBig::Draw()
{
	m_pModel->Draw();
}

void EnemyBig::UpdateMove(int score)
{
	m_pModel->Update();

	// スコアが上がるたびにエネミーの速度は上がる
	if (score % 1000 == 0)
	{
		m_speed++;
	}

	// 現在敵が向いている方向のベクトルを生成する
	MATRIX enemyRotMtx = MGetRotY(m_angle);
	m_dir = VTransform(kEnemyDir, enemyRotMtx);
	// 移動速度を反映させる
	m_vec = VScale(m_dir, m_speed);
	// 移動させる
	m_pos = VAdd(m_pos, m_vec);

	// ステージ外に出た時のエネミーの角度
	if (m_pos.z < -kColStage || m_pos.z > kColStage || m_pos.x > kColStage || m_pos.x < -kColStage)
	{
		m_randAngleType = GetRand(3);
		m_initPos = false;
	}

	// 座標の初期化
	if (!m_initPos)
	{
		// ステージの下
		if (m_randAngleType == 0)
		{
			m_pos.x = static_cast<float>(GetRand(2000) - 1000);
			m_pos.z = -1200.0f;
			m_angle = kAngleUp;
			//m_speed = GetRand(kSpeed) + 2;
			m_initPos = true;
		}
		// ステージの上
		if (m_randAngleType == 1)
		{
			m_pos.x = static_cast<float>(GetRand(2000) - 1000);
			m_pos.z = 1200.0f;
			m_angle = kAngleDown;
			//m_speed = GetRand(kSpeed) + 2;
			m_initPos = true;
		}
		// ステージの左
		if (m_randAngleType == 2)
		{
			m_pos.x = 1200.0f;
			m_pos.z = static_cast<float>(GetRand(2000) - 1000);
			m_angle = kAngleLeft;
			//m_speed = GetRand(kSpeed) + 2;
			m_initPos = true;
		}
		// ステージの右
		if (m_randAngleType == 3)
		{
			m_pos.x = -1200.0f;
			m_pos.z = static_cast<float>(GetRand(2000) - 1000);
			m_angle = kAngleRight;
			//m_speed = GetRand(kSpeed) + 2;
			m_initPos = true;
		}
	}
	

	m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));
	m_pModel->SetScale(VGet(3.0f, 3.0f, 3.0f));
}

bool EnemyBig::ColFlag()
{
	float colx = m_pPlayer->GetPos().x - m_pos.x;
	float coly = m_pPlayer->GetPos().y - m_pos.y;
	float colz = m_pPlayer->GetPos().z - m_pos.z;

	if (std::pow(colx, 2.0f) +
		std::pow(colz, 2.0f) <= std::pow(260.0f, 2.0f)) {
		return true;
	}
	return false;
}