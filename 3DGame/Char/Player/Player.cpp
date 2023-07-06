#include "Player.h"
#include "../Model.h"
#include "../Enemy/Enemy.h"

namespace
{
	// プレイヤーハンドル
	const char* const kPlayerHandle = "Data/Char/Player/Player2(toonType2).mv1";

	// カメラの初期位置
	constexpr VECTOR kZero{ 0.0f,0.0f,0.0f };
	constexpr VECTOR kCameraPos{ 0.0f, 400.0f, 1000.0f };
	constexpr VECTOR kCameraTarget{ 0.0f, 100.0f, 0.0f };

	// プレイヤーのモーション番号
	constexpr int kAnimFall = 0;// ステージ外に出た時の状態
	constexpr int kAnimIdle = 3;// アイドル状態
	constexpr int kAnimWalk = 14;// 歩く状態
	constexpr int kAnimRun = 11;// 走る状態
	constexpr int kAnimJump = 7;// ジャンプ状態
	constexpr int kAnimDamage = 2;// 敵に当たった時の状態

	// プレイヤーの移動
	// 加速度
	constexpr float kAcceleration = 0.1f;
	// 減速
	constexpr float kDeceleration = 0.5f;
	// 最高速度
	constexpr float kTopSpeed = 15.0f;
	// 回転速度
	constexpr float kRotationSpeed = 0.1f;

	// テスト：プレイヤーの移動
	constexpr VECTOR kPlayerVec{ 0.0f,0.0f,-10.0f };

	constexpr float kAnglePI = DX_PI_F / 180.0f;

	// プレイヤーのアングル
	constexpr float kAngleUp = 180.0f * kAnglePI;// 上
	constexpr float kAngleDown = 0.0f * kAnglePI;// 下
	constexpr float kAngleLeft = 90.0f * kAnglePI;// 左
	constexpr float kAngleRight = 270.0f * kAnglePI;// 右
	constexpr float kAngleUpLeft = 135.0f * kAnglePI;// 上左
	constexpr float kAngleUpRight = 225.0f * kAnglePI;// 上右
	constexpr float kAngleDownLeft = 45.0f * kAnglePI;// 下左
	constexpr float kAngleDownRight = 315.0f * kAnglePI;// 下右

	// プレイヤーのジャンプ
	// ジャンプ力
	constexpr float kJumpPower = 25.0f;
	// 重力
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
	m_blowRate(0)
{
	m_pModel = std::make_shared<Model>(kPlayerHandle);
	m_pEnemy = std::make_shared<Enemy>(m_pPlayer);
	m_pModel->SetAnimation(m_AnimNum, true, true);
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::End()
{
	MV1DeleteModel(m_playerHandle);// モデルの削除
}

void Player::Update(bool Hitting)
{
	UpdateMove(Hitting);

	//UpdateTestVec(Hitting);

	// デバッグ用ダメージ
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

void Player::Draw()
{
	m_pModel->Draw();
	//PadInputState();

	//DrawFormatString(0, 200, Color::kWhite, "PlayerAngle:%d", m_playerAngleY);
}

void Player::UpdateNoHitVec(bool Hitting)
{
	m_isMove = false;
	if (!m_isFall && !Hitting)
	{
		// 旧移動処理↓

		// 上下キー
		//if (Pad::IsPress(PAD_INPUT_UP))
		//{
		//	if (m_pos.z <= 950)
		//	{
		//		m_vec = VAdd(m_vec, VGet(0.0f, 0.0f, kTopSpeed));
		//		m_isMove = true;
		//		m_playerAngleY = kAngleUp;
		//	}
		//}
		//if (Pad::IsPress(PAD_INPUT_DOWN))
		//{
		//	if (m_pos.z >= -950)
		//	{
		//		m_vec = VAdd(m_vec, VGet(0.0f, 0.0f, -kTopSpeed));
		//		m_isMove = true;
		//		m_playerAngleY = kAngleDown;
		//	}
		//}
		//// 左右キー
		//if (Pad::IsPress(PAD_INPUT_LEFT))
		//{
		//	if (m_pos.x >= -950)
		//	{
		//		m_vec = VAdd(m_vec, VGet(-kTopSpeed, 0.0f, 0.0f));
		//		m_isMove = true;
		//		m_playerAngleY = kAngleLeft;
		//	}
		//}
		//if (Pad::IsPress(PAD_INPUT_RIGHT))
		//{
		//	if (m_pos.x <= 950)
		//	{
		//		m_vec = VAdd(m_vec, VGet(kTopSpeed, 0.0f, 0.0f));
		//		m_isMove = true;
		//		m_playerAngleY = kAngleRight;
		//	}
		//}

		if (input.ThumbLX >= 5000 || input.ThumbLX <= -5000 ||
			input.ThumbLY >= 5000 || input.ThumbLY <= -5000)
		{
			m_pos = VAdd(m_pos, m_move);
			m_isMove = true;

			// メモ360 = 91, 180 = 182;

			if (input.ThumbLY > 0)
			{
				m_playerAngleY = (input.ThumbLX / 182 / 2) * kAnglePI;
				m_playerAngleY = m_playerAngleY + (-180 * kAnglePI);
			}
			else if (input.ThumbLY < 0)
			{
				m_playerAngleY = -(input.ThumbLX / 182 / 2) * kAnglePI;
			}
		}
	}

	// 正規化移動処理
	//if (VSize(m_vec) > 0)
	//{
	//	m_vec = VNorm(m_vec);
	//}
	//m_vec = VScale(m_vec, kTopSpeed);
	//m_pos = VAdd(m_pos, m_vec);
	//if (!m_isFall && !Hitting)
	//{
	//	// 斜め入力時の角度
	//	if (Pad::IsPress(PAD_INPUT_UP) && Pad::IsPress(PAD_INPUT_LEFT))
	//	{
	//		m_playerAngleY = kAngleUpLeft;
	//	}
	//	if (Pad::IsPress(PAD_INPUT_UP) && Pad::IsPress(PAD_INPUT_RIGHT))
	//	{
	//		m_playerAngleY = kAngleUpRight;
	//	}
	//	if (Pad::IsPress(PAD_INPUT_DOWN) && Pad::IsPress(PAD_INPUT_LEFT))
	//	{
	//		m_playerAngleY = kAngleDownLeft;
	//	}
	//	if (Pad::IsPress(PAD_INPUT_DOWN) && Pad::IsPress(PAD_INPUT_RIGHT))
	//	{
	//		m_playerAngleY = kAngleDownRight;
	//	}
	//}
}

void Player::UpdateTestVec(bool Hitting)
{
	PadInputState();
	m_pModel->Update();

	// ジャンプ処理
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

	// ジャンプしていないとき
	if (!m_isJump)
	{
		if (Pad::IsTrigger(PAD_INPUT_1) || Pad::IsTrigger(PAD_INPUT_2))
		{
			m_jumpAcc = kJumpPower;
		}
	}

	if (!Hitting)
	{
		// 移動処理
		m_isMove = false;
		if (!m_isFall)
		{
			// スティックをニュートラル状態にしたときに入力されないように
			if (input.ThumbLX >= 5000 || input.ThumbLX <= -5000 ||
				input.ThumbLY >= 5000 || input.ThumbLY <= -5000)
			{
				// 動いている
				m_isMove = true;
				// 向いている方向に移動
				m_pos = VAdd(m_pos, m_move);

				// z軸+方向
				if (input.ThumbLY > 0)
				{
					m_playerAngleY = (input.ThumbLX / 182 / 2) * kAnglePI;
					m_playerAngleY = m_playerAngleY + (-180 * kAnglePI);
				}
				// z軸-方向
				else if(input.ThumbLY < 0)
				{
					m_playerAngleY = -(input.ThumbLX / 182 / 2) * kAnglePI;
				}

			}
		}

		if (m_isMove)
		{
			if (m_AnimNum == kAnimIdle)
			{
				// 移動アニメーション
				m_AnimNum = kAnimRun;
				m_pModel->ChangeAnimation(m_AnimNum, true, true, 10);
			}
		}
		else
		{
			if (m_AnimNum == kAnimRun)
			{
				// 移動からアイドル状態
				m_AnimNum = kAnimIdle;
				m_pModel->ChangeAnimation(m_AnimNum, true, true, 10);
			}
		}
	}
	
	

	m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f, m_playerAngleY, 0.0f));
}

void Player::UpdateMotion(bool hit)
{
	if (hit)
	{
		// ダメージ状態
		m_AnimNum = kAnimDamage;
		m_pModel->ChangeAnimation(m_AnimNum, false, true, 10);

	}
	else
	{
		if (m_isMove && !m_isJump && !m_isFall)
		{
			if (m_AnimNum != kAnimRun)
			{
				// 移動アニメーション
				m_AnimNum = kAnimRun;
				m_pModel->ChangeAnimation(m_AnimNum, true, true, 5);
			}
		}
		else if (m_isJump)
		{
			if (m_AnimNum != kAnimJump)
			{
				// ジャンプアニメーション
				m_AnimNum = kAnimJump;
				m_pModel->ChangeAnimation(m_AnimNum, true, true, 10);
			}
		}
		else if (!m_isMove && !m_isJump)
		{
			if (m_AnimNum != kAnimIdle)
			{
				// 移動からアイドル状態
				m_AnimNum = kAnimIdle;
				m_pModel->ChangeAnimation(m_AnimNum, true, true, 10);
			}
		}
	}
}

// 当たった時のダメージ
void Player::UpdateHitDamage(VECTOR enemyPos, bool hit)
{
	m_blowRate += 10;
	// 当たった時のプレイヤーとエネミーの座標で正規化
	if (!hit)
	{
		m_hitVec = VSub(enemyPos, m_pos);
		if (VSquareSize(m_hitVec) > 0)
		{
			// 正規化
			m_hitVec = VNorm(m_hitVec);
		}
		m_hitVec = VScale(m_hitVec, 1);
	}

	float blowRate = m_blowRate * 0.8f;

	m_hitVec.x = m_hitVec.x * blowRate;
	m_hitVec.y = m_hitVec.y * blowRate;
	m_hitVec.z = m_hitVec.z * blowRate;
}

// 当たった時のプレイヤーの移動
void Player::UpdateHitVec()
{
	// 吹っ飛び率
	

	m_pos = VSub(m_pos, VGet(m_hitVec.x, m_hitVec.y, m_hitVec.z));

	// -------------------------
	// テスト処理
	// -------------------------
	/*m_pos = VSub(m_pos, m_testVec);
	m_testVec.x-=10;
	m_testVec.z-=10;*/


	/*if (m_hitVec.x > 0)
	{
		m_hitVec.x -= (m_blowRate * 0.8f) / 2;
	}
	else if (m_hitVec.x < 0)
	{
		m_hitVec.x += (m_blowRate * 0.8f) / 2;
	}
	if (m_hitVec.z > 0)
	{
		m_hitVec.z -= (m_blowRate * 0.8f) / 2;
	}
	else if (m_hitVec.z < 0)
	{
		m_hitVec.z += (m_blowRate * 0.8f) / 2;
	}*/
	
	// 敵に当たった時のコントローラーの振動
	StartJoypadVibration(DX_INPUT_PAD1, m_blowRate + 200, 100, -1);
}

// 使ってない
void Player::UpdatePlayerPos()
{
	m_pos.z += m_vec.z;
	m_pos.x += m_vec.x;
}

// 使ってない
void Player::UpdateCamera()
{
	//m_cameraAngle = m_angle;
	m_cameraAngle = (m_cameraAngle * 0.8f) + (m_playerAngleY * 0.2f);
	m_cameraRotMtx = MGetRotY(m_cameraAngle);

	// ジャンプ時は単純にプレイヤーに服従するのではなく
	//プレイヤーの立っていた位置を見るようにする
	VECTOR cameraTrans = m_pos;
	//cameraTrans.y = m_pos.y * 0.0f;
	cameraTrans.y = m_pos.y * 0.2f;
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

// 使ってない
void Player::UpdateVec()
{
	m_pressUp = Pad::IsPress(PAD_INPUT_UP);
	m_pressDown = Pad::IsPress(PAD_INPUT_DOWN);
	m_pressRight = Pad::IsPress(PAD_INPUT_RIGHT);
	m_pressLeft = Pad::IsPress(PAD_INPUT_LEFT);

	if (m_pressUp)
	{
		m_vec.z -= kAcceleration;
		printfDx("ボタン押したな\n");
	}
	if (m_pressDown)
	{
		m_vec.z += kAcceleration;
		printfDx("ボタン押したな\n");
	}
	if (m_pressRight)
	{
		m_vec.x -= kAcceleration;
		printfDx("ボタン押したな\n");
	}
	if (m_pressLeft)
	{
		m_vec.x += kAcceleration;
		printfDx("ボタン押したな\n");
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

// 使ってない
void Player::UpdateIdle()
{
	m_pModel->Update();

	// ジャンプ処理
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
		m_playerAngleY -= 0.05f;
		//m_playerPos.x -= 0.1f;
	}
	if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		m_playerAngleY += 0.05f;
		//m_playerPos.x += 0.1f;
	}

	// 移動処理
	m_isMove = false;
	// 上下キーで移動
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

	m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f,m_playerAngleY,0.0f));

	//UpdateCamera();
}

// プレイヤーの更新処理
void Player::UpdateMove(bool Hitting)
{
	// パッドの入力状態取得
	PadInputState();
	m_pModel->Update();

	// ジャンプ処理
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

	// ジャンプしていないとき
	if (!m_isJump)
	{
		if (Pad::IsTrigger(PAD_INPUT_1) || Pad::IsTrigger(PAD_INPUT_2))
		{
			m_jumpAcc = kJumpPower;
		}
	}

	// 移動処理
	UpdateNoHitVec(Hitting);
	
	// ゲームオーバー処理
	if ((m_pos.x > 1000.0f || m_pos.x < -1000.0f ||
		m_pos.z > 1000.0f || m_pos.z < -1000.0f) &&
		m_pos.y <= 0.0f)
	{
		// 落下アニメーション
		m_AnimNum = kAnimFall;
		m_pModel->ChangeAnimation(m_AnimNum, false, true, 5);

		// 落下
		m_pos.y-=1.0f;

		// 見えなくなったら落下を終了
		if (m_pos.y <= -2000.0f)
		{
			m_pos.y = -2000.0f;
		}
		// 落ちる時のプレイヤーの向き固定
		m_playerAngleY = 0;

		m_isFall = true;
	}
	else
	{
		// プレイヤーのモーション処理
		UpdateMotion(Hitting);
	}

	// プレイヤーの座標
	m_pModel->SetPos(m_pos);
	// プレイヤーの回転率
	m_pModel->SetRot(VGet(0.0f, m_playerAngleY, 0.0f));
	// プレイヤーの拡大率
	m_pModel->SetScale(VGet(0.5f, 0.5f, 0.5f));
}

void Player::PadInputState()
{
	// 入力状態取得
	GetJoypadXInputState(DX_INPUT_PAD1, &input);
	// 画面に XINPUT_STATE の中身を描画
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

// 角度の計算：使ってない
int Player::TestCalculate()
{
	m_testRusult = m_angleTest - m_playerAngleY;

	return static_cast<int>(m_testRusult);
}

