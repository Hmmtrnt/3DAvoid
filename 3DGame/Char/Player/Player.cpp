#include "Player.h"
#include "../Model.h"
#include "../Enemy/Enemy.h"

namespace
{
	// ハンドル
	const char* const kPlayerHandle = "Data/3D/Char/Player/Player3(toonType2).mv1";// プレイヤー
	const char* const kRoundShadowHandle = "Data/2D/RoundShadow5.png";// 丸影

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
	// メモリ確保
	m_pModel = std::make_shared<Model>(kPlayerHandle);// モデル
	m_pEnemy = std::make_shared<Enemy>(m_pPlayer);// エネミー
	m_roundShadowHandle = LoadGraph(kRoundShadowHandle);// 丸影画像ロード
	m_pModel->SetAnimation(m_animNum, true, true);// アニメーション設定
}

Player::~Player()
{
	DeleteGraph(m_roundShadowHandle);
	MV1DeleteModel(m_playerHandle);// モデルデータの削除
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

	// デバッグ確認用ダメージ
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

// プレイヤー描画
void Player::Draw()
{
	//RoundShadow();
	m_pModel->Draw();
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

	// 各ベクトルの吹っ飛び代入
	m_hitVec.x = m_hitVec.x * blowRate;
	m_hitVec.y = m_hitVec.y * blowRate;
	m_hitVec.z = m_hitVec.z * blowRate;
}

// 当たった時のプレイヤーの移動
void Player::UpdateHitVec()
{
	// 吹っ飛び率
	m_pos = VSub(m_pos, VGet(m_hitVec.x, m_hitVec.y, m_hitVec.z));

	// 敵に当たった時のコントローラーの振動
	StartJoypadVibration(DX_INPUT_PAD1, m_blowRate + 200, 100, -1);
}

// プレイヤーの丸影
void Player::RoundShadow()
{
	// 丸影の大きさ
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
	// プレイヤーに何も起こっていない状態
	if (!m_isFall && !Hitting)
	{
		if (m_input.ThumbLX >= 5000 || m_input.ThumbLX <= -5000 ||
			m_input.ThumbLY >= 5000 || m_input.ThumbLY <= -5000)
		{
			// スティックを傾けただけで移動
			m_pos = VAdd(m_pos, m_move);
			m_isMove = true;

			// メモ360 = 91, 180 = 182;

			// 180度回転
			if (m_input.ThumbLY > 0)
			{
				m_playerAngleY = (m_input.ThumbLX / 182 / 2) * kAnglePI;
				m_playerAngleY = m_playerAngleY + (-180 * kAnglePI);
			}
			// 180度以降回転を反転
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
		// ダメージ状態
		m_animNum = kAnimDamage;
		m_pModel->ChangeAnimation(m_animNum, false, true, 10);
	}
	else
	{
		if (m_isMove && !m_isJump && !m_isFall)
		{
			if (m_animNum != kAnimRun)
			{
				// 移動アニメーション
				m_animNum = kAnimRun;
				m_pModel->ChangeAnimation(m_animNum, true, true, 5);
			}
		}
		else if (m_isJump)
		{
			if (m_animNum != kAnimJump)
			{
				// ジャンプアニメーション
				m_animNum = kAnimJump;
				m_pModel->ChangeAnimation(m_animNum, true, true, 10);
			}
		}
		else if (!m_isMove && !m_isJump)
		{
			if (m_animNum != kAnimIdle)
			{
				// 移動からアイドル状態
				m_animNum = kAnimIdle;
				m_pModel->ChangeAnimation(m_animNum, true, true, 10);
			}
		}
	}
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
		m_animNum = kAnimFall;
		m_pModel->ChangeAnimation(m_animNum, false, true, 5);

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
	m_pModel->SetRot(VGet(0.5f, m_playerAngleY, 0.0f));
	// プレイヤーの拡大率
	m_pModel->SetScale(VGet(0.5f, 0.5f, 0.5f));
}

void Player::PadInputState()
{
	// 入力状態取得
	GetJoypadXInputState(DX_INPUT_PAD1, &m_input);
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


