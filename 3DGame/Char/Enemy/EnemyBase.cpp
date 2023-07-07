#include "EnemyBase.h"

namespace
{
	// VECTOR
	// xyz�Ƃ���0.0f
	VECTOR kZero = VGet(0.0f, 0.0f, 0.0f);

	// �G�l�~�[�̃��[�V�����ԍ�
	constexpr int kAnimMove = 2;// �ړ����
}

EnemyBase::EnemyBase() :
	m_pos(kZero),
	m_dir(kZero),
	m_vec(kZero),
	m_scale(kZero),
	m_angle(0.0f),
	m_speed(0.0f),
	m_modelHandle(-1),
	m_animMove(kAnimMove)
{
	// �G�̏����ʒu
	m_pos.x = 1000;
	//m_pos.x = 500.0f;
	m_pos.y = 0.0f;
	m_pos.z = static_cast<float>(GetRand(2000) - 1000);
	//m_pos.z = 0;

}

EnemyBase::~EnemyBase()
{
}

int EnemyBase::GetModelHandle() const
{
	return m_modelHandle;
}