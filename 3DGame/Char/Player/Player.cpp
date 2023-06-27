#include "Player.h"
#include "../Model.h"

namespace
{
	// �v���C���[�n���h��
	const char* const kPlayerHandle = "Data/Char/Player/Player5.mv1";

	// �J�����̏����ʒu
	constexpr VECTOR kZero{ 0.0f,0.0f,0.0f };
	constexpr VECTOR kCameraPos{ 0.0f, 400.0f, 1000.0f };
	constexpr VECTOR kCameraTarget{ 0.0f, 100.0f, 0.0f };

	// �v���C���[�̃��[�V�����ԍ�
	constexpr int kAnimFall = 0;
	constexpr int kAnimIdle = 3;// �A�C�h�����
	constexpr int kAnimWalk = 14;// �������
	constexpr int kAnimRun = 11;// ������
	constexpr int kAnimJump = 7;// �W�����v���

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
	m_updateFunc(&Player::TestMove),
	m_pos(kZero),
	m_angle(kZero),
	m_vec(kZero),
	m_move(kZero),
	m_cameraRotMtx(),
	m_playerRotMtx(),
	m_playerHandle(-1),
	m_AnimNum(kAnimIdle),
	m_playerAngle2(0.0f),
	m_playerAngleY(0.0f),
	m_cameraAngle(m_playerAngle2),
	m_AnimTotalTime(0.0f),
	m_AnimPlay(0.0f),
	m_jumpAcc(0.0f),
	m_pressUp(false),
	m_pressDown(false),
	m_pressRight(false),
	m_pressLeft(false),
	m_isJump(false),
	m_isMove(false),
	m_isFall(false),
	m_frameCount(0),
	m_animPrev(0),
	m_animNext(0),
	m_blowRate(0)
{
	m_pModel = std::make_shared<Model>(kPlayerHandle);
	m_pModel->SetAnimation(m_AnimNum, true, true);
}

Player::~Player()
{
}

void Player::Init()
{
	m_animPrev = -1;
	m_animNext = MV1AttachAnim(m_playerHandle, 3, -1, false);
}

void Player::End()
{
	MV1DeleteModel(m_playerHandle);// ���f���̍폜
	//MV1CollResultPolyDimTerminate(test);
}

void Player::Update()
{
	(this->*m_updateFunc)();
	
	
}

void Player::Draw()
{
	//MV1DrawModel(m_playerHandle);

	m_pModel->Draw();
	
}

void Player::UpdateHit()
{
	m_blowRate += 10;
}

void Player::UpdatePlayerPos()
{
	m_pos.z += m_vec.z;
	m_pos.x += m_vec.x;
}

void Player::UpdateCamera()
{
	//m_cameraAngle = m_angle;
	m_cameraAngle = (m_cameraAngle * 0.8f) + (m_playerAngleY * 0.2f);
	m_cameraRotMtx = MGetRotY(m_cameraAngle);

	// �W�����v���͒P���Ƀv���C���[�ɕ��]����̂ł͂Ȃ�
	//�v���C���[�̗����Ă����ʒu������悤�ɂ���
	VECTOR cameraTrans = m_pos;
	//cameraTrans.y = m_pos.y * 0.0f;
	cameraTrans.y = m_pos.y * 0.2f;
	MATRIX playerTransMtx = MGetTranslate(cameraTrans);

	// �v���C���[�̉�]�ɍ��킹�ăJ�����ʒu�A�����_����]������
	// �v���C���[�̉�]���ƕ��s�ړ���������
	MATRIX cameraMtx = MMult(m_cameraRotMtx, playerTransMtx);

	VECTOR cameraPos = VTransform(kCameraPos, cameraMtx);
	VECTOR cameraTarget = VTransform(kCameraTarget, cameraMtx);

	// �J�����̐ݒ�
	// near,far
	SetCameraNearFar(5.0f, 2800.0f);
	// �J�����̎���p��ݒ�i���W�A���j
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	// �J�����̈ʒu�A�ǂ������Ă��邩��ݒ肷��
	SetCameraPositionAndTarget_UpVecY(cameraPos, cameraTarget);
}

void Player::UpdateVec()
{
	m_pressUp = Pad::IsPress(PAD_INPUT_UP);
	m_pressDown = Pad::IsPress(PAD_INPUT_DOWN);
	m_pressRight = Pad::IsPress(PAD_INPUT_RIGHT);
	m_pressLeft = Pad::IsPress(PAD_INPUT_LEFT);

	if (m_pressUp)
	{
		m_vec.z -= kAcceleration;
		printfDx("�{�^����������\n");
	}
	if (m_pressDown)
	{
		m_vec.z += kAcceleration;
		printfDx("�{�^����������\n");
	}
	if (m_pressRight)
	{
		m_vec.x -= kAcceleration;
		printfDx("�{�^����������\n");
	}
	if (m_pressLeft)
	{
		m_vec.x += kAcceleration;
		printfDx("�{�^����������\n");
	}

	if (!m_pressUp&&!m_pressDown)
	{
		m_vec.z = min(max(m_vec.z - kDeceleration, 0),
			m_vec.z + kDeceleration);
	}
	if (!m_pressRight && !m_pressLeft)
	{
		m_vec.x = min(max(m_vec.x - kDeceleration, 0),
			m_vec.x + kDeceleration);
	}


	if (m_vec.z >= kTopSpeed)
	{
		m_vec.z = kTopSpeed;
	}
	if (m_vec.z <= -kTopSpeed)
	{
		m_vec.z = -kTopSpeed;
	}

	if (m_vec.x >= kTopSpeed)
	{
		m_vec.x = kTopSpeed;
	}
	if (m_vec.x <= -kTopSpeed)
	{
		m_vec.x = -kTopSpeed;
	}
}

void Player::UpdateIdle()
{
	m_pModel->Update();

	// �W�����v����
	m_isJump = true;

	m_jumpAcc += kGravity;
	m_pos.y += m_jumpAcc;
	if (m_pos.y <= 0.0f)
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

	
	// ���E�L�[�Ő���
	if (Pad::IsPress(PAD_INPUT_LEFT))
	{
		m_playerAngleY -= 0.05f;
		//m_playerPos.x -= 0.1f;
	}
	if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		m_playerAngleY += 0.05f;
		//m_playerPos.x += 0.1f;
	}

	// �ړ�����
	m_isMove = false;
	// �㉺�L�[�ňړ�
	if (Pad::IsPress(PAD_INPUT_UP))
	{
#if true
		m_pos = VAdd(m_pos, m_move);
		m_isMove = true;
#else
		m_playerPos.z += 0.1f;
#endif
	}
	if (Pad::IsPress(PAD_INPUT_DOWN))
	{
#if true
		m_pos = VSub(m_pos, m_move);
		m_isMove = true;
#else
		m_playerPos.z -= 0.1f;
#endif
	}
	if (m_isMove)
	{
		if (m_AnimNum == kAnimIdle)
		{
			// �ړ��A�j���[�V����
#if true
			m_AnimNum = kAnimRun;
#else
			m_AnimNum = kAnimWalk;
#endif
			m_pModel->ChangeAnimation(m_AnimNum, true, true, 40);
		}
	}
	else
	{
#if true
		if (m_AnimNum == kAnimRun)
#else
		if (m_AnimNum == kAnimWalk)
#endif
		{
			// �ړ�����A�C�h�����
			m_AnimNum = kAnimIdle;
			m_pModel->ChangeAnimation(m_AnimNum, true, true, 20);
		}
	}

	m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f,m_playerAngleY,0.0f));

	//UpdateCamera();
}

void Player::TestMove()
{
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
	m_isMove = false;
	// �ړ��͂̏�����
	m_vec = VGet(0.0f, 0.0f, 0.0f);
	if (!m_isFall)
	{
		// �㉺�L�[
		if (Pad::IsPress(PAD_INPUT_UP))
		{
			if (m_pos.z <= 950)
			{
				m_vec = VAdd(m_vec, VGet(0.0f, 0.0f, kTopSpeed));

				m_isMove = true;
				m_playerAngleY = kAngleUp;
			}

		}
		if (Pad::IsPress(PAD_INPUT_DOWN))
		{
			if (m_pos.z >= -950)
			{
				m_vec = VAdd(m_vec, VGet(0.0f, 0.0f, -kTopSpeed));

				m_isMove = true;
				m_playerAngleY = kAngleDown;
			}
		}
		// ���E�L�[
		if (Pad::IsPress(PAD_INPUT_LEFT))
		{
			if (m_pos.x >= -950)
			{
				m_vec = VAdd(m_vec, VGet(-kTopSpeed, 0.0f, 0.0f));

				m_isMove = true;
				m_playerAngleY = kAngleLeft;
			}
		}
		if (Pad::IsPress(PAD_INPUT_RIGHT))
		{
			if (m_pos.x <= 950)
			{
				m_vec = VAdd(m_vec, VGet(kTopSpeed, 0.0f, 0.0f));

				m_isMove = true;
				m_playerAngleY = kAngleRight;
			}

		}
	}
	
	// ���K���ړ�����
	if (VSize(m_vec) > 0)
	{
		m_vec = VNorm(m_vec);
	}

	m_vec = VScale(m_vec, kTopSpeed);

	m_pos = VAdd(m_pos, m_vec);
	if (!m_isFall)
	{
		// �΂ߓ��͎��̊p�x
		if (Pad::IsPress(PAD_INPUT_UP) && Pad::IsPress(PAD_INPUT_LEFT))
		{
			m_playerAngleY = kAngleUpLeft;
		}
		if (Pad::IsPress(PAD_INPUT_UP) && Pad::IsPress(PAD_INPUT_RIGHT))
		{
			m_playerAngleY = kAngleUpRight;
		}
		if (Pad::IsPress(PAD_INPUT_DOWN) && Pad::IsPress(PAD_INPUT_LEFT))
		{
			m_playerAngleY = kAngleDownLeft;
		}
		if (Pad::IsPress(PAD_INPUT_DOWN) && Pad::IsPress(PAD_INPUT_RIGHT))
		{
			m_playerAngleY = kAngleDownRight;
		}
	}
	
	// �Q�[���I�[�o�[����
	if ((m_pos.x > 1000.0f || m_pos.x < -1000.0f ||
		m_pos.z > 1000.0f || m_pos.z < -1000.0f) &&
		m_pos.y <= 0.0f)
	{
		// �����A�j���[�V����
		m_AnimNum = kAnimFall;
		m_pModel->ChangeAnimation(m_AnimNum, false, true, 5);

		// ����
		m_pos.y-=1.0f;

		if (m_pos.y <= -2000.0f)
		{
			m_pos.y = -2000.0f;
		}

		m_isFall = true;
	}
	else
	{
		if (m_isMove && !m_isJump&& !m_isFall)
		{
			if (m_AnimNum != kAnimRun)
			{
				// �ړ��A�j���[�V����
				m_AnimNum = kAnimRun;
				m_pModel->ChangeAnimation(m_AnimNum, true, true, 5);
			}
		}
		else if (m_isJump)
		{
			if (m_AnimNum != kAnimJump)
			{
				// �ړ�����A�C�h�����
				m_AnimNum = kAnimJump;
				m_pModel->ChangeAnimation(m_AnimNum, true, true, 10);
			}
		}
		else if (!m_isMove && !m_isJump)
		{
			if (m_AnimNum != kAnimIdle)
			{
				// �ړ�����A�C�h�����
				m_AnimNum = kAnimIdle;
				m_pModel->ChangeAnimation(m_AnimNum, true, true, 10);
			}
		}
	}
	
	
	// �v���C���[�̉�]

	/*if (TestCalculate() < 0)
	{
		m_playerAngleY -= kRotationSpeed;
	}
	else
	{
		m_playerAngleY += kRotationSpeed;
	}*/

	//if (m_playerAngleY > m_angleTest)
	//{
	//	m_playerAngleY -= kRotationSpeed;
	//	/*if (0.01f > m_playerAngleY - m_angleTest)
	//	{
	//		m_playerAngleY = m_angleTest;
	//	}*/

	//	//m_isFlag = true;
	//}
	//if (m_playerAngleY < m_angleTest)
	//{
	//	m_playerAngleY += kRotationSpeed;
	//	/*if (0.01f < m_playerAngleY - m_angleTest)
	//	{
	//		m_playerAngleY = m_angleTest;
	//	}*/
	//	//m_isFlag = true;
	//}
	//else
	//{
	//	//m_playerAngleY = m_angleTest;
	//	m_isFlag = false;
	//}

	/*m_isFlag = false;

	if (!m_isFlag)
	{
		m_playerAngleY = m_angleTest;
	}*/
	
	

	// �v���C���[�̍��W
	m_pModel->SetPos(m_pos);
	// �v���C���[�̉�]��
	m_pModel->SetRot(VGet(0.0f, m_playerAngleY, 0.0f));
}

// �p�x�̌v�Z
int Player::TestCalculate()
{
	m_testRusult = m_angleTest - m_playerAngleY;

	return static_cast<int>(m_testRusult);
}

