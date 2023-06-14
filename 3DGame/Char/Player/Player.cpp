#include "Player.h"
#include "../Model.h"

namespace
{
	// キャラクターハンドル
	const char* const kPlayerHandle = "Data/Char/Player/Player5.mv1";

	// カメラの初期位置
	constexpr VECTOR kZero{ 0.0f,0.0f,0.0f };
	constexpr VECTOR kCameraPos{ 0.0f, 400.0f, 1000.0f };
	constexpr VECTOR kCameraTarget{ 0.0f, 100.0f, 0.0f };

	// プレイヤーのモーション番号
	constexpr int kAnimIdle = 3;
	constexpr int kAnimWalk = 14;
	constexpr int kAnimRun = 11;

	// プレイヤーの移動
	// 加速度
	constexpr float kAcceleration = 0.1f;
	// 減速
	constexpr float kDeceleration = 0.5f;
	// 最高速度
	constexpr float kTopSpeed = 15.0f;

	// テスト：プレイヤーの移動
	constexpr VECTOR kPlayerVec{ 0.0f,0.0f,-10.0f };

	// プレイヤーのアングル
	constexpr float kAngleUp = DX_PI_F;// 上
	constexpr float kAngleDown = 0.0f;// 下
	constexpr float kAngleLeft = DX_PI_F / 2;// 左
	constexpr float kAngleRight = DX_PI_F / -2;// 右
	constexpr float kAngleUpLeft = DX_PI_F / 1.3f;// 上左
	constexpr float kAngleUpRight = DX_PI_F / -1.3f;// 上右
	constexpr float kAngleDownLeft = DX_PI_F / 3.5f;// 下左
	constexpr float kAngleDownRight = DX_PI_F / -3.5f;// 下右

	// プレイヤーのジャンプ
	// ジャンプ力
	constexpr float kJumpPower = 25.0f;
	// 重力
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
	MV1DeleteModel(m_playerHandle);// モデルの削除
}

void Player::Update()
{
	(this->*m_updateFunc)();
	
	//UpdateVec();// プレイヤーの加速度
	//UpdatePlayerPos();// プレイヤーの座標更新
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

	// ジャンプ時は単純にプレイヤーに服従するのではなく
	//プレイヤーの立っていた位置を見るようにする
	VECTOR cameraTrans = m_playerPos;
	//cameraTrans.y = m_pos.y * 0.0f;
	cameraTrans.y = m_playerPos.y * 0.2f;
	MATRIX playerTransMtx = MGetTranslate(cameraTrans);

	// プレイヤーの回転に合わせてカメラ位置、注視点を回転させる
	// プレイヤーの回転情報と平行移動情報を合成
	MATRIX cameraMtx = MMult(m_cameraRotMtx, playerTransMtx);

	VECTOR cameraPos = VTransform(kCameraPos, cameraMtx);
	VECTOR cameraTarget = VTransform(kCameraTarget, cameraMtx);

	// カメラの設定
	// near,far
	SetCameraNearFar(5.0f, 2800.0f);
	// カメラの視野角を設定（ラジアン）
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	// カメラの位置、どこを見ているかを設定する
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
		printfDx("ボタン押したな\n");
	}
	if (m_pressDown)
	{
		m_playerVec.z += kAcceleration;
		printfDx("ボタン押したな\n");
	}
	if (m_pressRight)
	{
		m_playerVec.x -= kAcceleration;
		printfDx("ボタン押したな\n");
	}
	if (m_pressLeft)
	{
		m_playerVec.x += kAcceleration;
		printfDx("ボタン押したな\n");
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

	// ジャンプ処理
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

	// ジャンプしていないとき
	if (!m_isJump)
	{
		if (Pad::IsTrigger(PAD_INPUT_1) || Pad::IsTrigger(PAD_INPUT_2))
		{
			m_jumpAcc = kJumpPower;
		}
	}

	
	// 左右キーで旋回
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

	// 移動処理
	m_isMove = false;
	// 上下キーで移動
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
			// 移動アニメーション
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
			// 移動からアイドル状態
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

	// ジャンプ処理
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

	// ジャンプしていないとき
	if (!m_isJump)
	{
		if (Pad::IsTrigger(PAD_INPUT_1) || Pad::IsTrigger(PAD_INPUT_2))
		{
			m_jumpAcc = kJumpPower;
		}
	}

	// 移動処理
	m_isMove = false;
	// 上下キー
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
	// 左右キー
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
			// 移動アニメーション
			m_AnimNum = kAnimRun;
			m_pModel->ChangeAnimation(m_AnimNum, true, true, 5);
		}
	}
	else
	{
		if (m_AnimNum == kAnimRun)
		{
			// 移動からアイドル状態
			m_AnimNum = kAnimIdle;
			m_pModel->ChangeAnimation(m_AnimNum, true, true, 20);
		}
	}

	m_pModel->SetPos(m_playerPos);
	m_pModel->SetRot(VGet(0.0f, m_playerAngleY, 0.0f));
}

