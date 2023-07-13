#include "EnemyBase.h"

namespace
{
	// �ۉe�n���h��
	const char* const kRoundShadowHandle = "Data/2D/RoundShadow5.png";// �ۉe

	// �G�l�~�[�̃��[�V�����ԍ�
	constexpr int kAnimMove = 2;// �ړ����

	// VECTOR�̏�����
	constexpr VECTOR kZero{ 0.0f,0.0f,0.0f };
	constexpr VECTOR kInitPos{ 0.0f,0.0f,1000.0f };

	// �G�l�~�[�̌����Ă������
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
	m_animMove(kAnimMove),
	m_roundShadowHandle(-1)
{
	// �G�̏����ʒu
	m_pos.x = 1000;
	//m_pos.x = 500.0f;
	m_pos.y = 0.0f;
	m_pos.z = static_cast<float>(GetRand(2000) - 1000);
	//m_pos.z = 0;

	//m_roundShadowHandle = LoadGraph(kRoundShadowHandle);// �ۉe�摜���[�h
}

EnemyBase::~EnemyBase()
{
	// ���f���̃������폜
	MV1DeleteModel(m_modelHandle);
	// �n���h���f�[�^�̃������폜
	DeleteGraph(m_roundShadowHandle);
}

void EnemyBase::EnemyMove()
{
	// ���ݓG�������Ă�������̃x�N�g���𐶐�����
	MATRIX enemyRotMtx = MGetRotY(m_angle);
	m_dir = VTransform(m_EnemyDir, enemyRotMtx);
	// �ړ����x�𔽉f������
	m_vec = VScale(m_dir, m_speed);
	// �ړ�������
	m_pos = VAdd(m_pos, m_vec);
}

void EnemyBase::RoundShadow(float scale)
{
	DrawBillboard3D(
		VGet(m_pos.x, 20.0f, m_pos.z),
		0.5f, 0.5f,
		scale, 0.0f,
		m_roundShadowHandle,
		true
	);
}

int EnemyBase::GetModelHandle() const
{
	return m_modelHandle;
}

int EnemyBase::GetShadowHandle() const
{
	return m_roundShadowHandle;
}
