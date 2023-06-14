#include "Player.h"
#include "../Model.h"

namespace
{
	// �L�����N�^�[�n���h��
	const char* const kPlayerHandle = "Data/Char/Player/Player5.mv1";

	// �J�����̏����ʒu
	constexpr VECTOR kZero{ 0.0f,0.0f,0.0f };
	constexpr VECTOR kCameraPos{ 0.0f, 400.0f, 1000.0f };
	constexpr VECTOR kCameraTarget{ 0.0f, 100.0f, 0.0f };

	// �v���C���[�̃��[�V�����ԍ�
	constexpr int kAnimIdle = 3;
	constexpr int kAnimWalk = 14;
	constexpr int kAnimRun = 11;

	// �v���C���[�̈ړ�
	// �����x
	constexpr float kAcceleration = 0.1f;
	// ����
	constexpr float kDeceleration = 0.5f;
	// �ō����x
	constexpr float kTopSpeed = 15.0f;

	// �e�X�g�F�v���C���[�̈ړ�
	constexpr VECTOR kPlayerVec{ 0.0f,0.0f,-10.0f };

	// �v���C���[�̃A���O��
	constexpr float kAngleUp = DX_PI_F;// ��
	constexpr float kAngleDown = 0.0f;// ��
	constexpr float kAngleLeft = DX_PI_F / 2;// ��
	constexpr float kAngleRight = DX_PI_F / -2;// �E
	constexpr float kAngleUpLeft = DX_PI_F / 1.3f;// �㍶
	constexpr float kAngleUpRight = DX_PI_F / -1.3f;// ��E
	constexpr float kAngleDownLeft = DX_PI_F / 3.5f;// ����
	constexpr float kAngleDownRight = DX_PI_F / -3.5f;// ���E

	// �v���C���[�̃W�����v
	// �W�����v��
	constexpr float kJumpPower = 25.0f;
	// �d��
	constexpr float kGravity = -1.0f;

}

Player::Player() :
	m_updateFunc(&Player::TestMove),
	m_playerPos(kZero),
	m_playerAngle(kZero),
	m_playerVec(kZero),
	m_playerMove(kZero),
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
	m_frameCount(0),
	m_animPrev(0),
	m_animNext(0)
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
}

void Player::Update()
{
	(this->*m_updateFunc)();
	
	//UpdateVec();// �v���C���[�̉����x
	//UpdatePlayerPos();// �v���C���[�̍��W�X�V
	//UpdateCamera();
}

void Player::Draw()
{
	//MV1DrawModel(m_playerHandle);

	m_pModel->Draw();
	
}

void Player::UpdatePlayerPos()
{
	m_playerPos.z += m_playerVec.z;
	m_playerPos.x += m_playerVec.x;
}

void Player::UpdateCamera()
{
	//m_cameraAngle = m_angle;
	m_cameraAngle = (m_cameraAngle * 0.8f) + (m_playerAngleY * 0.2f);
	m_cameraRotMtx = MGetRotY(m_cameraAngle);

	// �W�����v���͒P���Ƀv���C���[�ɕ��]����̂ł͂Ȃ�
	//�v���C���[�̗����Ă����ʒu������悤�ɂ���
	VECTOR cameraTrans = m_playerPos;
	//cameraTrans.y = m_pos.y * 0.0f;
	cameraTrans.y = m_playerPos.y * 0.2f;
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
		m_playerVec.z -= kAcceleration;
		printfDx("�{�^����������\n");
	}
	if (m_pressDown)
	{
		m_playerVec.z += kAcceleration;
		printfDx("�{�^����������\n");
	}
	if (m_pressRight)
	{
		m_playerVec.x -= kAcceleration;
		printfDx("�{�^����������\n");
	}
	if (m_pressLeft)
	{
		m_playerVec.x += kAcceleration;
		printfDx("�{�^����������\n");
	}

	if (!m_pressUp&&!m_pressDown)
	{
		m_playerVec.z = min(max(m_playerVec.z - kDeceleration, 0),
			m_playerVec.z + kDeceleration);
	}
	if (!m_pressRight && !m_pressLeft)
	{
		m_playerVec.x = min(max(m_playerVec.x - kDeceleration, 0),
			m_playerVec.x + kDeceleration);
	}


	if (m_playerVec.z >= kTopSpeed)
	{
		m_playerVec.z = kTopSpeed;
	}
	if (m_playerVec.z <= -kTopSpeed)
	{
		m_playerVec.z = -kTopSpeed;
	}

	if (m_playerVec.x >= kTopSpeed)
	{
		m_playerVec.x = kTopSpeed;
	}
	if (m_playerVec.x <= -kTopSpeed)
	{
		m_playerVec.x = -kTopSpeed;
	}
}

void Player::UpdateIdle()
{
	m_pModel->Update();

	// �W�����v����
	m_isJump = true;

	m_jumpAcc += kGravity;
	m_playerPos.y += m_jumpAcc;
	if (m_playerPos.y <= 0.0f)
	{
		m_playerPos.y = 0.0f;
		m_jumpAcc = 0.0f;
		m_isJump = false;
	}

	m_playerRotMtx = MGetRotY(m_playerAngleY);
	m_playerMove = VTransform(kPlayerVec, m_playerRotMtx);

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
		//m_playerAngleY -= 0.05f;
		m_playerPos.x -= 0.1f;
	}
	if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		//m_playerAngleY += 0.05f;
		m_playerPos.x += 0.1f;
	}

	// �ړ�����
	m_isMove = false;
	// �㉺�L�[�ňړ�
	if (Pad::IsPress(PAD_INPUT_UP))
	{
#if false
		m_playerPos = VAdd(m_playerPos, m_playerMove);
		m_isMove = true;
#else
		m_playerPos.z += 0.1f;
#endif
	}
	if (Pad::IsPress(PAD_INPUT_DOWN))
	{
#if false
		m_playerPos = VSub(m_playerPos, m_playerMove);
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

	m_pModel->SetPos(m_playerPos);
	m_pModel->SetRot(VGet(0.0f,m_playerAngleY,0.0f));

	//UpdateCamera();
}

void Player::TestMove()
{
	m_pModel->Update();

	// �W�����v����
	m_isJump = true;

	m_jumpAcc += kGravity;
	m_playerPos.y += m_jumpAcc;
	if (m_playerPos.y <= 0.0f)
	{
		m_playerPos.y = 0.0f;
		m_jumpAcc = 0.0f;
		m_isJump = false;
	}

	m_playerRotMtx = MGetRotY(m_playerAngleY);
	m_playerMove = VTransform(kPlayerVec, m_playerRotMtx);

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
	// �㉺�L�[
	if (Pad::IsPress(PAD_INPUT_UP))
	{
		if (m_playerPos.z <= 950)
		{
			m_playerPos.z += kTopSpeed;
			m_isMove = true;
			m_playerAngleY = kAngleUp;
		}
		
	}
	if (Pad::IsPress(PAD_INPUT_DOWN))
	{
		if (m_playerPos.z >= -950)
		{
			m_playerPos.z -= kTopSpeed;
			m_isMove = true;
			m_playerAngleY = kAngleDown;
		}
	}
	// ���E�L�[
	if (Pad::IsPress(PAD_INPUT_LEFT))
	{
		if (m_playerPos.x >= -950)
		{
			m_playerPos.x -= kTopSpeed;
			m_isMove = true;
			m_playerAngleY = kAngleLeft;
		}
	}
	if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		if (m_playerPos.x <= 950)
		{
			m_playerPos.x += kTopSpeed;
			m_isMove = true;
			m_playerAngleY = kAngleRight;
		}
		
	}
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

	printfDx("m_playerPos.z;%f\n", m_playerPos.z);
	printfDx("m_playerPos.x:%f\n", m_playerPos.x);
	
	

	if (m_isMove)
	{
		if (m_AnimNum == kAnimIdle)
		{
			// �ړ��A�j���[�V����
			m_AnimNum = kAnimRun;
			m_pModel->ChangeAnimation(m_AnimNum, true, true, 5);
		}
	}
	else
	{
		if (m_AnimNum == kAnimRun)
		{
			// �ړ�����A�C�h�����
			m_AnimNum = kAnimIdle;
			m_pModel->ChangeAnimation(m_AnimNum, true, true, 20);
		}
	}

	m_pModel->SetPos(m_playerPos);
	m_pModel->SetRot(VGet(0.0f, m_playerAngleY, 0.0f));
}

