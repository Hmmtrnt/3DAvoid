#include "EnemyBase.h"

namespace
{
	// エネミーのモーション番号
	constexpr int kAnimMove = 2;// 移動状態
}

EnemyBase::EnemyBase() :
	m_pos(VGet(0.0f,0.0f,0.0f)),
	m_dir(VGet(0.0f, 0.0f, 0.0f)),
	m_vec(VGet(0.0f, 0.0f, 0.0f)),
	m_angle(0.0f),
	m_speed(0.0f),
	m_modelHandle(-1)
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
}
