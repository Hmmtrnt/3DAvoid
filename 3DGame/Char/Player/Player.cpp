#include "Player.h"
#include "../Model.h"
#include "../Enemy/Enemy.h"

namespace
{
	// �n���h��
	const char* const kPlayerHandle = "Data/3D/Char/Player/Player3(toonType2).mv1";// �v���C���[
	const char* const kRoundShadowHandle = "Data/2D/RoundShadow5.png";// �ۉe

	// �J�����̏����ʒu
	constexpr VECTOR kZero{ 0.0f,0.0f,0.0f };
	constexpr VECTOR kCameraPos{ 0.0f, 400.0f, 1000.0f };
	constexpr VECTOR kCameraTarget{ 0.0f, 100.0f, 0.0f };

	// �v���C���[�̃��[�V�����ԍ�
	constexpr int kAnimFall = 0;// �X�e�[�W�O�ɏo�����̏��
	constexpr int kAnimIdle = 3;// �A�C�h�����
	constexpr int kAnimWalk = 14;// �������
	constexpr int kAnimRun = 11;// ������
	constexpr int kAnimJump = 7;// �W�����v���
	constexpr int kAnimDamage = 2;// �G�ɓ����������̏��

	// �v���C���[�̈ړ�
	// �����x
	constexpr float kAcceleration = 0.1f;
	// ����
	constexpr float kDeceleration = 0.5f;
	// �ō����x
	constexpr float kTopSpeed = 15.0f;
	// ��]���x
	constexpr float kRotationSpeed = 0.1f;

	// �e�X�g�F�v���C���[�̈ړ�
	constexpr VECTOR kPlayerVec{ 0.0f,0.0f,-10.0f };

	constexpr float kAnglePI = DX_PI_F / 180.0f;

	// �v���C���[�̃A���O��
	constexpr float kAngleUp = 180.0f * kAnglePI;// ��
	constexpr float kAngleDown = 0.0f * kAnglePI;// ��
	constexpr float kAngleLeft = 90.0f * kAnglePI;// ��
	constexpr float kAngleRight = 270.0f * kAnglePI;// �E
	constexpr float kAngleUpLeft = 135.0f * kAnglePI;// �㍶
	constexpr float kAngleUpRight = 225.0f * kAnglePI;// ��E
	constexpr float kAngleDownLeft = 45.0f * kAnglePI;// ����
	constexpr float kAngleDownRight = 315.0f * kAnglePI;// ���E

	// �v���C���[�̃W�����v
	// �W�����v��
	constexpr float kJumpPower = 25.0f;
	// �d��
	constexpr float kGravity = -1.0f;

}

Player::Player() :
	m_pos(kZero),
	m_angle(kZero),
	m_vec(kZero),
	m_hitVec(kZero),
	m_move(kZero),
	m_cameraRotMtx(),
	m_playerRotMtx(),
	m_playerHandle(-1),
	m_animNum(kAnimIdle),
	m_playerAngle2(0.0f),
	m_playerAngleY(0.0f),
	m_cameraAngle(m_playerAngle2),
	m_animTotalTime(0.0f),
	m_animPlay(0.0f),
	m_jumpAcc(0.0f),
	m_pressUp(false),
	m_pressDown(false),
	m_pressRight(false),
	m_pressLeft(false),
	m_isJump(false),
	m_isMove(false),
	m_isFall(false),
	m_blowRate(0)
{
	// �������m��
	m_pModel = std::make_shared<Model>(kPlayerHandle);// ���f��
	m_pEnemy = std::make_shared<Enemy>(m_pPlayer);// �G�l�~�[
	m_roundShadowHandle = LoadGraph(kRoundShadowHandle);// �ۉe�摜���[�h
	m_pModel->SetAnimation(m_animNum, true, true);// �A�j���[�V�����ݒ�
}

Player::~Player()
{
	DeleteGraph(m_roundShadowHandle);
	MV1DeleteModel(m_playerHandle);// ���f���f�[�^�̍폜
}

void Player::Init()
{
}

void Player::End()
{
}

void Player::Update(bool Hitting)
{
	UpdateMove(Hitting);

	// �f�o�b�O�m�F�p�_���[�W
	if (Pad::IsTrigger(PAD_INPUT_3))
	{
		m_blowRate += 10;
	}
	if (Pad::IsTrigger(PAD_INPUT_4))
	{
		if (m_blowRate > 0)
		{
			m_blowRate -= 10;
		}
	}
}

// �v���C���[�`��
void Player::Draw()
{
	//RoundShadow();
	m_pModel->Draw();
}

// �����������̃_���[�W
void Player::UpdateHitDamage(VECTOR enemyPos, bool hit)
{
	m_blowRate += 10;
	// �����������̃v���C���[�ƃG�l�~�[�̍��W�Ő��K��
	if (!hit)
	{
		m_hitVec = VSub(enemyPos, m_pos);
		if (VSquareSize(m_hitVec) > 0)
		{
			// ���K��
			m_hitVec = VNorm(m_hitVec);
		}
		m_hitVec = VScale(m_hitVec, 1);
	}

	float blowRate = m_blowRate * 0.8f;

	// �e�x�N�g���̐�����ё��
	m_hitVec.x = m_hitVec.x * blowRate;
	m_hitVec.y = m_hitVec.y * blowRate;
	m_hitVec.z = m_hitVec.z * blowRate;
}

// �����������̃v���C���[�̈ړ�
void Player::UpdateHitVec()
{
	// ������ї�
	m_pos = VSub(m_pos, VGet(m_hitVec.x, m_hitVec.y, m_hitVec.z));

	// �G�ɓ����������̃R���g���[���[�̐U��
	StartJoypadVibration(DX_INPUT_PAD1, m_blowRate + 200, 100, -1);
}

// �v���C���[�̊ۉe
void Player::RoundShadow()
{
	// �ۉe�̑傫��
	float m_scale;

	DrawBillboard3D(
		VGet(m_pos.x, 10.0f, m_pos.z),
		0.5f, 0.5f,
		120.0f, 2.0f,
		m_roundShadowHandle,
		true
	);

}

void Player::UpdateNoHitVec(bool Hitting)
{
	m_isMove = false;
	// �v���C���[�ɉ����N�����Ă��Ȃ����
	if (!m_isFall && !Hitting)
	{
		if (m_input.ThumbLX >= 5000 || m_input.ThumbLX <= -5000 ||
			m_input.ThumbLY >= 5000 || m_input.ThumbLY <= -5000)
		{
			// �X�e�B�b�N���X���������ňړ�
			m_pos = VAdd(m_pos, m_move);
			m_isMove = true;

			// ����360 = 91, 180 = 182;

			// 180�x��]
			if (m_input.ThumbLY > 0)
			{
				m_playerAngleY = (m_input.ThumbLX / 182 / 2) * kAnglePI;
				m_playerAngleY = m_playerAngleY + (-180 * kAnglePI);
			}
			// 180�x�ȍ~��]�𔽓]
			else if (m_input.ThumbLY < 0)
			{
				m_playerAngleY = -(m_input.ThumbLX / 182 / 2) * kAnglePI;
			}
		}
	}
}

void Player::UpdateMotion(bool hit)
{
	if (hit)
	{
		// �_���[�W���
		m_animNum = kAnimDamage;
		m_pModel->ChangeAnimation(m_animNum, false, true, 10);
	}
	else
	{
		if (m_isMove && !m_isJump && !m_isFall)
		{
			if (m_animNum != kAnimRun)
			{
				// �ړ��A�j���[�V����
				m_animNum = kAnimRun;
				m_pModel->ChangeAnimation(m_animNum, true, true, 5);
			}
		}
		else if (m_isJump)
		{
			if (m_animNum != kAnimJump)
			{
				// �W�����v�A�j���[�V����
				m_animNum = kAnimJump;
				m_pModel->ChangeAnimation(m_animNum, true, true, 10);
			}
		}
		else if (!m_isMove && !m_isJump)
		{
			if (m_animNum != kAnimIdle)
			{
				// �ړ�����A�C�h�����
				m_animNum = kAnimIdle;
				m_pModel->ChangeAnimation(m_animNum, true, true, 10);
			}
		}
	}
}

// �v���C���[�̍X�V����
void Player::UpdateMove(bool Hitting)
{
	// �p�b�h�̓��͏�Ԏ擾
	PadInputState();
	m_pModel->Update();

	// �W�����v����
	m_isJump = true;

	m_jumpAcc += kGravity;
	m_pos.y += m_jumpAcc;
	if (m_pos.y <= 0.0f && !m_isFall)
	{
		m_pos.y = 0.0f;
		m_jumpAcc = 0.0f;
		m_isJump = false;
	}

	m_playerRotMtx = MGetRotY(m_playerAngleY);
	m_move = VTransform(kPlayerVec, m_playerRotMtx);

	// �W�����v���Ă��Ȃ��Ƃ�
	if (!m_isJump)
	{
		if (Pad::IsTrigger(PAD_INPUT_1) || Pad::IsTrigger(PAD_INPUT_2))
		{
			m_jumpAcc = kJumpPower;
		}
	}

	// �ړ�����
	UpdateNoHitVec(Hitting);
	
	// �Q�[���I�[�o�[����
	if ((m_pos.x > 1000.0f || m_pos.x < -1000.0f ||
		m_pos.z > 1000.0f || m_pos.z < -1000.0f) &&
		m_pos.y <= 0.0f)
	{
		// �����A�j���[�V����
		m_animNum = kAnimFall;
		m_pModel->ChangeAnimation(m_animNum, false, true, 5);

		// ����
		m_pos.y-=1.0f;

		// �����Ȃ��Ȃ����痎�����I��
		if (m_pos.y <= -2000.0f)
		{
			m_pos.y = -2000.0f;
		}
		// �����鎞�̃v���C���[�̌����Œ�
		m_playerAngleY = 0;

		m_isFall = true;
	}
	else
	{
		// �v���C���[�̃��[�V��������
		UpdateMotion(Hitting);
	}

	// �v���C���[�̍��W
	m_pModel->SetPos(m_pos);
	// �v���C���[�̉�]��
	m_pModel->SetRot(VGet(0.5f, m_playerAngleY, 0.0f));
	// �v���C���[�̊g�嗦
	m_pModel->SetScale(VGet(0.5f, 0.5f, 0.5f));
}

void Player::PadInputState()
{
	// ���͏�Ԏ擾
	GetJoypadXInputState(DX_INPUT_PAD1, &m_input);
	// ��ʂ� XINPUT_STATE �̒��g��`��
	/*DrawFormatString(0, 0, Color::kWhite, "LeftTrigger:%d RightTrigger:%d",
		input.LeftTrigger, input.RightTrigger);
	DrawFormatString(0, 16, Color::kWhite, "ThumbLX:%d ThumbLY:%d",
		input.ThumbLX, input.ThumbLY);
	DrawFormatString(0, 32, Color::kWhite, "ThumbRX:%d ThumbRY:%d",
		input.ThumbRX, input.ThumbRY);
	DrawString(0, 64, "Button", Color::kWhite);
	for (int i = 0; i < 16; i++)
	{
		DrawFormatString(64 + i % 8 * 64, 64 + i / 8 * 16, Color::kWhite,
			"%2d:%d", i, input.Buttons[i]);
	}*/
}


