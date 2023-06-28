#include "Enemy.h"
#include "../Player/Player.h"
#include "../Model.h"
#include <iostream>

namespace
{
	// �L�����N�^�[�n���h��
	const char* const kEnemyHandle = "Data/Char/Enemy/enemy.mv1";
	// �v���C���[�n���h��
	const char* const kPlayerHandle = "Data/Char/Player/Player5.mv1";

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
	m_modelHandle(-1),
	m_playerPos(kZero),
	m_Number(0)
{
	// �G�̏����ʒu
	m_pos.x = 1000;
	//m_pos.x = 500.0f;
	m_pos.y = 0.0f;
	m_pos.z = static_cast<float>(GetRand(2000) - 1000);
	//m_pos.z = 0;

	// ���f���̃��[�h
	m_modelHandle = MV1LoadModel(kEnemyHandle);

	// �|�C���^�̃������m��
	m_pModel = std::make_shared<Model>(m_modelHandle);
	// �G�̃A�j���[�V�����ݒ�
	m_pModel->SetAnimation(kAnimMove, true, true);
	// �G�̌����̏�����
	m_angle = GetRand(360) * DX_PI_F / 180;
}

Enemy::Enemy(int orgModel, std::shared_ptr<Player> pPlayer, int num) :
	m_updateFunc(&Enemy::UpdateMove),
	m_pPlayer(pPlayer),
	m_angle(0.0f),
	m_modelHandle(-1),
	m_playerPos(kZero),
	m_Number(num)
{
	// �G�̏����ʒu
	m_pos.x = 1000;
	//m_pos.x = -500.0f;
	//m_pos.x = static_cast<float>(GetRand(1000) -1000);
	m_pos.y = 0.0f;
	m_pos.z = static_cast<float>(GetRand(2000) - 1000);
	//m_pos.z = 0;

	// ���f���̃��[�h
	m_modelHandle = MV1LoadModel(kEnemyHandle);

	// �|�C���^�̃������m��
	m_pModel = std::make_shared<Model>(m_modelHandle);
	// �G�̃A�j���[�V�����ݒ�
	m_pModel->SetAnimation(kAnimMove, true, true);
	// �G�̌����̏�����
	m_angle = GetRand(360) * DX_PI_F / 180;

	
}

Enemy::~Enemy()
{
	// ���f���̃������폜
	MV1DeleteModel(m_modelHandle);
	MV1DeleteModel(m_playerHandle);
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
}

void Enemy::Draw()
{
	m_pModel->Draw();
	DebugDraw();
}

void Enemy::UpdateMove()
{
	m_pModel->Update();

	// ���ݓG�������Ă�������̃x�N�g���𐶐�����
	MATRIX enemyRotMtx = MGetRotY(m_angle);
	m_dir = VTransform(kEnemyDir, enemyRotMtx);
	// �ړ����x�𔽉f������
	m_vec = VScale(m_dir, kSpeed);
	// �ړ�������
	m_pos = VAdd(m_pos, m_vec);


	// ���W�̏�����
	// �X�e�[�W�̉�
	if (m_pos.z < -1000.0f)
	{
		m_pos.z = 1000.0f;
		m_angle = GetRand(360) * DX_PI_F / 180;
	}
	// �X�e�[�W�̏�
	if (m_pos.z > 1000.0f)
	{
		m_pos.z = -1000.0f;
		m_angle = GetRand(360) * DX_PI_F / 180;
	}
	// �X�e�[�W�̉E
	if (m_pos.x > 1000.0f)
	{
		m_pos.x = -1000.0f;
		m_angle = GetRand(360) * DX_PI_F / 180;
	}
	// �X�e�[�W�̍�
	if (m_pos.x < -1000.0f)
	{
		m_pos.x = 1000.0f;
		m_angle = GetRand(360) * DX_PI_F / 180;
	}

	m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f,m_angle,0.0f));
	m_pModel->SetScale(VGet(0.5f, 0.5f, 0.5f));
}

void Enemy::DebugDraw()
{
	// ���f���̃n���h���擾
	int handle = m_pModel->getModelHandle();

	// ���f�����ɂ���HP�o�[��\��������W�̃f�[�^���擾����
	int frameNo = MV1SearchFrame(handle, "Head3_end");
	// HP�o�[��\��������W�f�[�^�̃��[���h���W���擾����
	VECTOR hpPos = MV1GetFramePosition(handle, frameNo);
	// HP�o�[�\���ʒu�̃��[���h���W���X�N���[�����W�ɕϊ�����
	VECTOR screenPos = ConvWorldPosToScreenPos(hpPos);
	if ((screenPos.z <= 0.0f) || (screenPos.z >= 1.0f))
	{
		// �\���͈͊O�̏ꍇ�����\�����Ȃ�
		return;
	}

	DrawFormatString(static_cast<int>(screenPos.x) - 64 / 2, static_cast<int>(screenPos.y),0xffffff, "%d", m_Number);
}

bool Enemy::ColFlag()
{
	float colx = m_pPlayer->GetPos().x - m_pos.x;
	float coly = m_pPlayer->GetPos().y - m_pos.y;
	float colz = m_pPlayer->GetPos().z - m_pos.z;

	if (std::pow(colx,2.0f) + 
		std::pow(coly,2.0f) + 
		std::pow(colz,2.0f) <= std::pow(100.0f,2.0f)) {
		return true;
	}
	return false;
}

int Enemy::GetModelHandle() const
{
	return m_modelHandle;
}

float Enemy::GetColRadius()
{
	return kColRadius;
}

void Enemy::SetPlayerPos(VECTOR playerPos)
{
	m_playerPos = playerPos;
}
