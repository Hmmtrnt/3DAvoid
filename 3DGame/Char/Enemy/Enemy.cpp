#include "Enemy.h"
#include "../Model.h"

namespace
{
	// �L�����N�^�[�n���h��
	const char* const kEnemyHandle = "Data/Char/Enemy/enemy.mv1";

	// �G�l�~�[�̃��[�V�����ԍ�
	constexpr int kAnimMove = 2;// �ړ����
	

	// VECTOR�̏�����
	constexpr VECTOR kZero{ 0.0f,0.0f,0.0f };
	constexpr VECTOR kInitPos{ 0.0f,0.0f,1000.0f };

	// �G�l�~�[�̌����Ă������
	constexpr VECTOR kEnemyDir{ 0.0f,0.0f,-1.0f };

	// �����蔻��̃T�C�Y
	constexpr float kColRadius = 50.0f;
}

Enemy::Enemy(/*const char* fileName, */std::shared_ptr<Player> pPlayer) :
	m_updateFunc(&Enemy::UpdateMove),
	m_pPlayer(pPlayer),
	m_angle(0.0f)
{
	m_pos.x = GetRand(2000) - 1000;;
	m_pos.y = 0.0f;
	m_pos.z = GetRand(2000) - 1000;

	m_pModel = std::make_shared<Model>(kEnemyHandle);
	m_pModel->SetAnimation(kAnimMove, true, true);
}

Enemy::Enemy(int orgModel, std::shared_ptr<Player> pPlayer) :
	m_updateFunc(&Enemy::UpdateMove),
	m_pPlayer(pPlayer),
	m_angle(0.0f)
{
	m_pos.x = GetRand(2000) - 1000;;
	m_pos.y = 0.0f;
	m_pos.z = GetRand(2000) - 1000;
	m_pModel = std::make_shared<Model>(kEnemyHandle);
	m_pModel->SetAnimation(kAnimMove, true, true);
}

Enemy::~Enemy()
{
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

	

	/*if (m_pos.z <= -1000.0f)
	{
		m_pos.z = 1000.0f;
	}*/
}

void Enemy::Draw()
{
	m_pModel->Draw();
}

void Enemy::UpdateMove()
{
	m_pModel->Update();

	// ���ݓG�������Ă�������̃x�N�g���𐶐�����
	MATRIX enemyRotMtx = MGetRotY(m_angle);
	VECTOR dir = VTransform(kEnemyDir, enemyRotMtx);
	// �G����v���C���[�ւ̃x�N�g���i���K���j
	VECTOR toPlayer = VSub(m_pPlayer->GetPos(), m_pos);
	toPlayer = VNorm(toPlayer);
	// ���ς���p�x�����߂�
	float dot = VDot(dir, toPlayer);
	float angle = acosf(dot);

	m_pModel->SetPos(m_pos);
	m_pModel->SetRot(kZero);

}

int Enemy::GetModelHandle() const
{
	return 0;
}

float Enemy::GetColRadius()
{
	return kColRadius;
}
