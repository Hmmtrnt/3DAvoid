#include "Enemy.h"
#include "../Player/Player.h"
#include "../Model.h"
#include <iostream>

namespace
{
	// �傫��
	constexpr VECTOR kScale{ 0.5f,0.5f,0.5f };

	// �L�����N�^�[�n���h��
	const char* const kEnemyHandle = "Data/3D/Char/Enemy/Enemy2(toonType2).mv1";
	// �ۉe�n���h��
	const char* const kRoundShadowHandle = "Data/2D/RoundShadow5.png";


	// �G�l�~�[�̍ő�X�s�[�h
	constexpr int kSpeed = 5;
}

Enemy::Enemy(std::shared_ptr<Player> pPlayer) :
	m_pPlayer(pPlayer)
{
	// ���f���̃��[�h
	m_modelHandle = MV1LoadModel(kEnemyHandle);
	// �ۉe�摜�̃��[�h
	m_roundShadowHandle = LoadGraph(kRoundShadowHandle);

	// �|�C���^�̃������m��
	m_pModel = std::make_shared<Model>(m_modelHandle);
	// �G�̃A�j���[�V�����ݒ�
	m_pModel->SetAnimation(m_animMove, true, true);
	// �G�̌����̏�����
	m_angle = GetRand(360) * DX_PI_F / 180;
	m_speed = static_cast<float>(GetRand(kSpeed) + 2);

	/*m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));
	m_pModel->SetScale(VGet(0.5f, 0.5f, 0.5f));*/

	m_scale = kScale;

	InitState(m_pos, VGet(0.5f, m_angle, 0.0f), m_scale);
}

Enemy::Enemy(int orgModel, int roundShadow, std::shared_ptr<Player> pPlayer) :
	m_pPlayer(pPlayer)
{
	// �|�C���^�̃������m��:�G�̕���
	m_pModel = std::make_shared<Model>(orgModel);
	// �ۉe�̕���
	m_roundShadowHandle = roundShadow;

	// �G�̃A�j���[�V�����ݒ�
	m_pModel->SetAnimation(m_animMove, true, true);
	// �G�̌����̏�����
	m_angle = GetRand(360) * DX_PI_F / 180;
	m_speed = static_cast<float>(GetRand(kSpeed) + 2);

	//m_pModel->SetPos(m_pos);						// ���W
	//m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));	// ��]
	//m_pModel->SetScale(VGet(0.5f, 0.5f, 0.5f));		// �傫��

	m_scale = kScale;

	InitState(m_pos, VGet(0.5f, m_angle, 0.0f), m_scale);
	
}

Enemy::Enemy()
{
	// ���f���̃��[�h
	m_modelHandle = MV1LoadModel(kEnemyHandle);

	// �|�C���^�̃������m��
	m_pModel = std::make_shared<Model>(m_modelHandle);
	// �G�̃A�j���[�V�����ݒ�
	m_pModel->SetAnimation(m_animMove, true, true);
	// �G�̌����̏�����
	m_angle = GetRand(360) * DX_PI_F / 180;
	m_speed = static_cast<float>(GetRand(kSpeed) + 2);

	/*m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));
	m_pModel->SetScale(VGet(0.5f, 0.5f, 0.5f));*/

	m_scale = kScale;
	InitState(VGet(250.0f, -130.0f, 100.0f), VGet(0.0f, 0.8f, 0.0f), m_scale);
	
}

Enemy::Enemy(int orgModel)
{
	// �|�C���^�̃������m��
	m_pModel = std::make_shared<Model>(orgModel);
	// �G�̃A�j���[�V�����ݒ�
	m_pModel->SetAnimation(m_animMove, true, true);
	// �G�̌����̏�����
	m_angle = GetRand(360) * DX_PI_F / 180;
	m_speed = static_cast<float>(GetRand(kSpeed) + 2);

	/*m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));
	m_pModel->SetScale(VGet(0.5f, 0.5f, 0.5f));*/

	m_scale = kScale;
	InitState(VGet(80.0f, -130.0f, 100.0f), VGet(0.0f, 0.4f, 0.0f), m_scale);
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	UpdateMove();
}

void Enemy::Draw()
{
	RoundShadow(120.0f);
	m_pModel->Draw();
}

void Enemy::UpdateMove()
{
	m_pModel->Update();

	// ���ݓG�������Ă�������̃x�N�g���𐶐�����
	EnemyBase::EnemyMove();

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

	/*m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.5f,m_angle,0.0f));
	m_pModel->SetScale(VGet(0.5f, 0.5f, 0.5f));*/

	InitState(m_pos, VGet(0.5f, m_angle, 0.0f), m_scale);

}

void Enemy::UpdateTitle()
{

	m_pModel->Update();

	//m_pModel->SetPos(VGet(150.0f,-130.0f,100.0f));	// ���W
	//m_pModel->SetRot(VGet(0.0f, 1.0f, 0.0f));		// ��]
	//m_pModel->SetScale(VGet(0.5f, 0.5f, 0.5f));		// �傫��

	//InitState(VGet(200.0f, -130.0f, 100.0f), VGet(0.0f, 0.8f, 0.0f), m_scale);
	//InitState(VGet(0.0f, -130.0f, 100.0f), VGet(0.0f, 0.4f, 0.0f), m_scale);
	
}

// �^�C�g����ʂɕ`��
void Enemy::DrawTitle()
{
	m_pModel->Draw();
}

// ���ǂ��������蔻��
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

// ���W�A��]�A�傫���ݒ�
void Enemy::InitState(VECTOR pos, VECTOR rot, VECTOR scale)
{
	m_pModel->SetPos(pos);
	m_pModel->SetRot(rot);
	m_pModel->SetScale(scale);
}
