#include "Enemy.h"
#include "../Player/Player.h"
#include "../Model.h"

namespace
{
	// �L�����N�^�[�n���h��
	const char* const kEnemyHandle = "Data/Char/Enemy/enemy.mv1";

	// �G�l�~�[�̃��[�V�����ԍ�
	constexpr int kAnimMove = 2;// �ړ����

	constexpr float kSpeed = 5.0f;
	

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
	m_angle(0.0f),
	m_modelHandle(-1)
{
	//m_pos.x = GetRand(2000) - 1000;
	m_pos.x = 1000.0f;
	m_pos.y = 0.0f;
	m_pos.z = GetRand(2000) - 1000;

	m_modelHandle = MV1LoadModel(kEnemyHandle);// ���f���̃��[�h

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

	m_pModel = std::make_shared<Model>(m_modelHandle);
	m_pModel->SetAnimation(kAnimMove, true, true);

	m_angle = GetRand(360) * DX_PI_F / 180;
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
	// �ړ����x�𔽉f������
	VECTOR vec = VScale(dir, kSpeed);
	// �ړ�������
	m_pos = VAdd(m_pos, vec);

	/*m_frameCount++;
	if (m_frameCount >= 2 * 60)
	{
		m_rotSpeed = static_cast<float>(GetRand(250)) * 0.0001f;
		m_rotSpeed = 0.025;
		if (GetRand(1)) m_rotSpeed *= -1.0f;

		m_upddateFunc = &Enemy::UpdateToTurn;
		m_frameCount = 0;
	}*/

	// ���W�̏�����
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

int Enemy::GetModelHandle() const
{
	return m_modelHandle;
}

float Enemy::GetColRadius()
{
	return kColRadius;
}
