#include "Enemy.h"
#include "../Player/Player.h"
#include "../Model.h"
#include <iostream>

namespace
{
	// �L�����N�^�[�n���h��
	const char* const kEnemyHandle = "Data/Char/Enemy/Enemy2(toonType2).mv1";

	// �G�l�~�[�̃��[�V�����ԍ�
	constexpr int kAnimMove = 2;// �ړ����
	//constexpr int kAnimAttack = 3;// �U�����

	// �G�l�~�[�̍ő�X�s�[�h
	constexpr int kSpeed = 5;
	

	// VECTOR�̏�����
	constexpr VECTOR kZero{ 0.0f,0.0f,0.0f };
	constexpr VECTOR kInitPos{ 0.0f,0.0f,1000.0f };

	// �G�l�~�[�̌����Ă������
	constexpr VECTOR kEnemyDir{ 0.0f,0.0f,-1.0f };

	// �����蔻��̃T�C�Y
	constexpr float kColRadius = 50.0f;
}

Enemy::Enemy(std::shared_ptr<Player> pPlayer) :
	m_pPlayer(pPlayer)
{
	// ���f���̃��[�h
	m_modelHandle = MV1LoadModel(kEnemyHandle);

	// �|�C���^�̃������m��
	m_pModel = std::make_shared<Model>(m_modelHandle);
	// �G�̃A�j���[�V�����ݒ�
	m_pModel->SetAnimation(kAnimMove, true, true);
	// �G�̌����̏�����
	m_angle = GetRand(360) * DX_PI_F / 180;
	m_speed = static_cast<float>(GetRand(kSpeed) + 2);
}

Enemy::Enemy(int orgModel, std::shared_ptr<Player> pPlayer) :
	m_pPlayer(pPlayer)
{
	// ���f���̃��[�h
	m_modelHandle = MV1LoadModel(kEnemyHandle);

	// �|�C���^�̃������m��
	m_pModel = std::make_shared<Model>(m_modelHandle);
	// �G�̃A�j���[�V�����ݒ�
	m_pModel->SetAnimation(kAnimMove, true, true);
	// �G�̌����̏�����
	m_angle = GetRand(360) * DX_PI_F / 180;
	m_speed = static_cast<float>(GetRand(kSpeed) + 2);

	m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));
	m_pModel->SetScale(VGet(0.5f, 0.5f, 0.5f));
	
}

Enemy::~Enemy()
{
	// ���f���̃������폜
	MV1DeleteModel(m_modelHandle);
}

void Enemy::Update()
{
	UpdateMove();
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
	m_dir = VTransform(kEnemyDir, enemyRotMtx);
	// �ړ����x�𔽉f������
	m_vec = VScale(m_dir, m_speed);
	// �ړ�������
	m_pos = VAdd(m_pos, m_vec);


	// ���W�̏�����
	// �X�e�[�W�̉�
	if (m_pos.z < -1000.0f)
	{
		m_pos.z = 1000.0f;
		m_angle = GetRand(180) * DX_PI_F / 180;
		m_speed = static_cast<float>(GetRand(kSpeed) + 2);
	}
	// �X�e�[�W�̏�
	if (m_pos.z > 1000.0f)
	{
		m_pos.z = -1000.0f;
		m_angle = GetRand(360) * DX_PI_F / 180;
		m_speed = static_cast<float>(GetRand(kSpeed) + 2);
	}
	// �X�e�[�W�̉E
	if (m_pos.x > 1000.0f)
	{
		m_pos.x = -1000.0f;
		m_angle = GetRand(360) * DX_PI_F / 180;
		m_speed = static_cast<float>(GetRand(kSpeed) + 2);
	}
	// �X�e�[�W�̍�
	if (m_pos.x < -1000.0f)
	{
		m_pos.x = 1000.0f;
		m_angle = GetRand(360) * DX_PI_F / 180;
		m_speed = static_cast<float>(GetRand(kSpeed) + 2);
	}

	m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f,m_angle,0.0f));
	m_pModel->SetScale(VGet(0.5f, 0.5f, 0.5f));
}

bool Enemy::ColFlag()
{
	float colx = m_pPlayer->GetPos().x - m_pos.x;
	float coly = m_pPlayer->GetPos().y - m_pos.y;
	float colz = m_pPlayer->GetPos().z - m_pos.z;

	if (std::pow(colx,2.0f) + 
		std::pow(coly,2.0f) + 
		std::pow(colz,2.0f) <= std::pow(70.0f,2.0f)) {
		return true;
	}
	return false;
}