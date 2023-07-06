#include "EnemyBig.h"
#include "../Player/Player.h"
#include "../Model.h"
#include <iostream>

namespace
{
	// �L�����N�^�[�n���h��
	const char* const kEnemyHandle = "Data/Char/Enemy/Enemy3(toonType2).mv1";

	// �G�l�~�[�̃��[�V�����ԍ�
	constexpr int kAnimMove = 2;// �ړ����
	//constexpr int kAnimAttack = 3;// �U�����

	// �G�l�~�[�̏����X�s�[�h
	constexpr int kSpeed = 3;


	// VECTOR�̏�����
	constexpr VECTOR kZero{ 0.0f,0.0f,0.0f };
	constexpr VECTOR kInitPos{ 0.0f,0.0f,1000.0f };

	// �G�l�~�[�̌����Ă������
	constexpr VECTOR kEnemyDir{ 0.0f,0.0f,-1.0f };

	// �����蔻��̃T�C�Y
	constexpr float kColRadius = 50.0f;

	// �ǂ��܂ł����邩�̃X�e�[�W�̃T�C�Y
	constexpr float kColStage = 1200.0f;

	// �G�l�~�[�̃A���O��
	constexpr float kAnglePI = DX_PI_F / 180.0f;
	constexpr float kAngleUp = 180.0f * kAnglePI;// ��
	constexpr float kAngleDown = 0.0f * kAnglePI;// ��
	constexpr float kAngleLeft = 90.0f * kAnglePI;// ��
	constexpr float kAngleRight = 270.0f * kAnglePI;// �E
}

EnemyBig::EnemyBig(std::shared_ptr<Player> pPlayer) :
	m_pPlayer(pPlayer),
	m_randAngleType(0),
	m_initPos(true)
{
	// ���f���̃��[�h
	m_modelHandle = MV1LoadModel(kEnemyHandle);

	// �|�C���^�̃������m��
	m_pModel = std::make_shared<Model>(m_modelHandle);
	// �G�̃A�j���[�V�����ݒ�
	m_pModel->SetAnimation(kAnimMove, true, true);
	// �G�̌����̏�����
	m_angle = kAngleLeft;
	m_speed = kSpeed;

	m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));
	m_pModel->SetScale(VGet(0.5f, 0.5f, 0.5f));
}

EnemyBig::EnemyBig(int orgModel, std::shared_ptr<Player> pPlayer) :
	m_pPlayer(pPlayer),
	m_initPos(true)
{
	// ���f���̃��[�h
	m_modelHandle = MV1LoadModel(kEnemyHandle);

	// �|�C���^�̃������m��
	m_pModel = std::make_shared<Model>(m_modelHandle);
	// �G�̃A�j���[�V�����ݒ�
	m_pModel->SetAnimation(kAnimMove, true, true);
	// �G�̌����̏�����
	//m_angle = GetRand(360) * DX_PI_F / 180;
	m_speed = kSpeed;

	m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));
	m_pModel->SetScale(VGet(3.0f, 3.0f, 3.0f));

}

EnemyBig::~EnemyBig()
{
	// ���f���̃������폜
	MV1DeleteModel(m_modelHandle);
}

void EnemyBig::Update(int score)
{
	UpdateMove(score);
}

void EnemyBig::Draw()
{
	m_pModel->Draw();
}

void EnemyBig::UpdateMove(int score)
{
	m_pModel->Update();

	// �X�R�A���オ�邽�тɃG�l�~�[�̑��x�͏オ��
	if (score % 1000 == 0)
	{
		m_speed++;
	}

	// ���ݓG�������Ă�������̃x�N�g���𐶐�����
	MATRIX enemyRotMtx = MGetRotY(m_angle);
	m_dir = VTransform(kEnemyDir, enemyRotMtx);
	// �ړ����x�𔽉f������
	m_vec = VScale(m_dir, m_speed);
	// �ړ�������
	m_pos = VAdd(m_pos, m_vec);

	// �X�e�[�W�O�ɏo�����̃G�l�~�[�̊p�x
	if (m_pos.z < -kColStage || m_pos.z > kColStage || m_pos.x > kColStage || m_pos.x < -kColStage)
	{
		m_randAngleType = GetRand(3);
		m_initPos = false;
	}

	// ���W�̏�����
	if (!m_initPos)
	{
		// �X�e�[�W�̉�
		if (m_randAngleType == 0)
		{
			m_pos.x = static_cast<float>(GetRand(2000) - 1000);
			m_pos.z = -1200.0f;
			m_angle = kAngleUp;
			//m_speed = GetRand(kSpeed) + 2;
			m_initPos = true;
		}
		// �X�e�[�W�̏�
		if (m_randAngleType == 1)
		{
			m_pos.x = static_cast<float>(GetRand(2000) - 1000);
			m_pos.z = 1200.0f;
			m_angle = kAngleDown;
			//m_speed = GetRand(kSpeed) + 2;
			m_initPos = true;
		}
		// �X�e�[�W�̍�
		if (m_randAngleType == 2)
		{
			m_pos.x = 1200.0f;
			m_pos.z = static_cast<float>(GetRand(2000) - 1000);
			m_angle = kAngleLeft;
			//m_speed = GetRand(kSpeed) + 2;
			m_initPos = true;
		}
		// �X�e�[�W�̉E
		if (m_randAngleType == 3)
		{
			m_pos.x = -1200.0f;
			m_pos.z = static_cast<float>(GetRand(2000) - 1000);
			m_angle = kAngleRight;
			//m_speed = GetRand(kSpeed) + 2;
			m_initPos = true;
		}
	}
	

	m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));
	m_pModel->SetScale(VGet(3.0f, 3.0f, 3.0f));
}

bool EnemyBig::ColFlag()
{
	float colx = m_pPlayer->GetPos().x - m_pos.x;
	float coly = m_pPlayer->GetPos().y - m_pos.y;
	float colz = m_pPlayer->GetPos().z - m_pos.z;

	if (std::pow(colx, 2.0f) +
		std::pow(colz, 2.0f) <= std::pow(260.0f, 2.0f)) {
		return true;
	}
	return false;
}