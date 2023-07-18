#include "EnemyBig.h"
#include "../Player/Player.h"
#include "../Model.h"
#include <iostream>

namespace
{
	// 大きさ
	constexpr VECTOR kScale{ 3.0f,3.0f,3.0f };

	// キャラクターハンドル
	const char* const kEnemyHandle = "Data/3D/Char/Enemy/Enemy3(toonType2).mv1";

	// エネミーの初期スピード
	constexpr int kSpeed = 3;

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
	m_pModel->SetAnimation(m_animMove, true, true);
	// 敵の向きの初期化
	m_angle = kAngleLeft;
	m_speed = kSpeed;

	/*m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));
	m_pModel->SetScale(VGet(3.0f, 3.0f, 3.0f));*/

	m_scale = kScale;

	InitState(m_pos, VGet(0.5f, m_angle, 0.0f), m_scale);

}

EnemyBig::EnemyBig(int orgModel, std::shared_ptr<Player> pPlayer) :
	m_pPlayer(pPlayer),
	m_initPos(true)
{
	// モデルのロード
	m_pModel = std::make_shared<Model>(orgModel);

	// ポインタのメモリ確保
	m_pModel = std::make_shared<Model>(m_modelHandle);
	// 敵のアニメーション設定
	m_pModel->SetAnimation(m_animMove, true, true);
	// 敵の向きの初期化
	//m_angle = GetRand(360) * DX_PI_F / 180;
	m_speed = kSpeed;

	/*m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));
	m_pModel->SetScale(VGet(3.0f, 3.0f, 3.0f));*/

	m_scale = kScale;

	InitState(m_pos, VGet(0.5f, m_angle, 0.0f), m_scale);

}

EnemyBig::EnemyBig() :
	m_randAngleType(0),
	m_initPos(false)
{
	// モデルのロード
	m_modelHandle = MV1LoadModel(kEnemyHandle);

	// ポインタのメモリ確保
	m_pModel = std::make_shared<Model>(m_modelHandle);
	// 敵のアニメーション設定
	m_pModel->SetAnimation(m_animMove, true, true);
	// 敵の向きの初期化
	m_angle = kAngleLeft;
	m_speed = kSpeed;

	/*m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));
	m_pModel->SetScale(VGet(3.0f, 3.0f, 3.0f));*/

	m_scale = kScale;

	InitState(m_pos, VGet(0.5f, m_angle, 0.0f), m_scale);
}

EnemyBig::~EnemyBig()
{
}

void EnemyBig::Update(int score)
{
	UpdateMove(score);
}

void EnemyBig::Draw()
{
	RoundShadow(500.0f);
	m_pModel->Draw();
}

void EnemyBig::UpdateMove(int score)
{
	m_pModel->Update(1.0f);

	// スコアが上がるたびにエネミーの速度は上がる
	if (score % 1000 == 0)
	{
		m_speed++;
	}

	// 現在敵が向いている方向のベクトルを生成する
	EnemyBase::EnemyMove();

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
	

	/*m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.5f, m_angle, 0.0f));
	m_pModel->SetScale(VGet(3.0f, 3.0f, 3.0f));*/
	InitState(m_pos, VGet(0.5f, m_angle, 0.0f), m_scale);
}

void EnemyBig::UpdateTitle()
{
	m_pModel->Update(1.0f);

	//m_pModel->SetPos(VGet(150.0f,-130.0f,100.0f));	// 座標
	//m_pModel->SetRot(VGet(0.0f, 1.0f, 0.0f));		// 回転
	//m_pModel->SetScale(VGet(0.5f, 0.5f, 0.5f));		// 大きさ

	m_scale = VGet(2.0f, 2.0f, 2.0f);

	InitState(VGet(300.0f, -130.0f, 500.0f), VGet(0.0f, 0.5f, 0.0f), m_scale);
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

void EnemyBig::InitState(VECTOR pos, VECTOR rot, VECTOR scale)
{
	m_pModel->SetPos(pos);
	m_pModel->SetRot(rot);
	m_pModel->SetScale(scale);
}
