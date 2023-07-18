#include "EnemyBig.h"
#include "../Player/Player.h"
#include "../Model.h"
#include <iostream>

namespace
{
	// �傫��
	constexpr VECTOR kScale{ 3.0f,3.0f,3.0f };

	// �L�����N�^�[�n���h��
	const char* const kEnemyHandle = "Data/3D/Char/Enemy/Enemy3(toonType2).mv1";

	// �G�l�~�[�̏����X�s�[�h
	constexpr int kSpeed = 3;

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
	m_pModel->SetAnimation(m_animMove, true, true);
	// �G�̌����̏�����
	m_angle = kAngleLeft;
	m_speed = kSpeed;

	/*m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));
	m_pModel->SetScale(VGet(3.0f, 3.0f, 3.0f));*/

	m_scale = kScale;

	InitState(m_pos, VGet(0.5f, m_angle, 0.0f), m_scale);

}

EnemyBig::EnemyBig(int orgModel, std::shared_ptr<Player> pPlayer) :
	m_pPlayer(pPlayer),
	m_initPos(true)
{
	// ���f���̃��[�h
	m_pModel = std::make_shared<Model>(orgModel);

	// �|�C���^�̃������m��
	m_pModel = std::make_shared<Model>(m_modelHandle);
	// �G�̃A�j���[�V�����ݒ�
	m_pModel->SetAnimation(m_animMove, true, true);
	// �G�̌����̏�����
	//m_angle = GetRand(360) * DX_PI_F / 180;
	m_speed = kSpeed;

	/*m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));
	m_pModel->SetScale(VGet(3.0f, 3.0f, 3.0f));*/

	m_scale = kScale;

	InitState(m_pos, VGet(0.5f, m_angle, 0.0f), m_scale);

}

EnemyBig::EnemyBig() :
	m_randAngleType(0),
	m_initPos(false)
{
	// ���f���̃��[�h
	m_modelHandle = MV1LoadModel(kEnemyHandle);

	// �|�C���^�̃������m��
	m_pModel = std::make_shared<Model>(m_modelHandle);
	// �G�̃A�j���[�V�����ݒ�
	m_pModel->SetAnimation(m_animMove, true, true);
	// �G�̌����̏�����
	m_angle = kAngleLeft;
	m_speed = kSpeed;

	/*m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f, m_angle, 0.0f));
	m_pModel->SetScale(VGet(3.0f, 3.0f, 3.0f));*/

	m_scale = kScale;

	InitState(m_pos, VGet(0.5f, m_angle, 0.0f), m_scale);
}

EnemyBig::~EnemyBig()
{
}

void EnemyBig::Update(int score)
{
	UpdateMove(score);
}

void EnemyBig::Draw()
{
	RoundShadow(500.0f);
	m_pModel->Draw();
}

void EnemyBig::UpdateMove(int score)
{
	m_pModel->Update(1.0f);

	// �X�R�A���オ�邽�тɃG�l�~�[�̑��x�͏オ��
	if (score % 1000 == 0)
	{
		m_speed++;
	}

	// ���ݓG�������Ă�������̃x�N�g���𐶐�����
	EnemyBase::EnemyMove();

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
	

	/*m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.5f, m_angle, 0.0f));
	m_pModel->SetScale(VGet(3.0f, 3.0f, 3.0f));*/
	InitState(m_pos, VGet(0.5f, m_angle, 0.0f), m_scale);
}

void EnemyBig::UpdateTitle()
{
	m_pModel->Update(1.0f);

	//m_pModel->SetPos(VGet(150.0f,-130.0f,100.0f));	// ���W
	//m_pModel->SetRot(VGet(0.0f, 1.0f, 0.0f));		// ��]
	//m_pModel->SetScale(VGet(0.5f, 0.5f, 0.5f));		// �傫��

	m_scale = VGet(2.0f, 2.0f, 2.0f);

	InitState(VGet(300.0f, -130.0f, 500.0f), VGet(0.0f, 0.5f, 0.0f), m_scale);
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

void EnemyBig::InitState(VECTOR pos, VECTOR rot, VECTOR scale)
{
	m_pModel->SetPos(pos);
	m_pModel->SetRot(rot);
	m_pModel->SetScale(scale);
}
