#include "Enemy.h"
#include "../Player/Player.h"
#include "../Model.h"

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
	m_playerHandle = MV1LoadModel(kPlayerHandle);

	m_pModel = std::make_shared<Model>(m_modelHandle);
	m_pModel->SetAnimation(kAnimMove, true, true);

	m_angle = GetRand(360) * DX_PI_F / 180;

	
}

Enemy::~Enemy()
{
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

	test = MV1CollCheck_Sphere(m_playerHandle, -1, m_pos, 100.0f);

	// �����������ǂ����ŏ����𕪊�
	if (test.HitNum >= 1)
	{
		// ���������ꍇ�͏Փ˂̏���`�悷��

		// ���������|���S���̐���`��
		DrawFormatString(0, 0, GetColor(255, 255, 255), "Hit Poly Num   %d", test.HitNum);

		printfDx("��������");

		// ���������|���S���̐������J��Ԃ�
		for (int i = 0; i < test.HitNum; i++)
		{
			// ���������|���S����`��
			DrawTriangle3D(
				test.Dim[i].Position[0],
				test.Dim[i].Position[1],
				test.Dim[i].Position[2], GetColor(0, 255, 255), TRUE);
		}
	}
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

bool Enemy::ColTest()
{
	/*if (<500.0f + 250.0f)
	{

	}*/
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
