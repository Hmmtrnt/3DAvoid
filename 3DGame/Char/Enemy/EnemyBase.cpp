#include "EnemyBase.h"

namespace
{
	// エネミーのモーション番号
	constexpr int kAnimMove = 2;// 移動状態

	// VECTORの初期化
	constexpr VECTOR kZero{ 0.0f,0.0f,0.0f };
	constexpr VECTOR kInitPos{ 0.0f,0.0f,1000.0f };

	// エネミーの向いている方向
	constexpr VECTOR kEnemyDir{ 0.0f,0.0f,-1.0f };
}

EnemyBase::EnemyBase() :
	m_pos(kZero),
	m_dir(kZero),
	m_vec(kZero),
	m_scale(kZero),
	m_EnemyDir(kEnemyDir),
	m_angle(0.0f),
	m_speed(0.0f),
	m_modelHandle(-1),
	m_animMove(kAnimMove)
{
	// 敵の初期位置
	m_pos.x = 1000;
	//m_pos.x = 500.0f;
	m_pos.y = 0.0f;
	m_pos.z = static_cast<float>(GetRand(2000) - 1000);
	//m_pos.z = 0;

}

EnemyBase::~EnemyBase()
{
	// モデルのメモリ削除
	MV1DeleteModel(m_modelHandle);
}

void EnemyBase::EnemyMove()
{
	// 現在敵が向いている方向のベクトルを生成する
	MATRIX enemyRotMtx = MGetRotY(m_angle);
	m_dir = VTransform(m_EnemyDir, enemyRotMtx);
	// 移動速度を反映させる
	m_vec = VScale(m_dir, m_speed);
	// 移動させる
	m_pos = VAdd(m_pos, m_vec);
}

int EnemyBase::GetModelHandle() const
{
	return m_modelHandle;
}