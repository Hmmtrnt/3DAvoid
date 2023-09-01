#include "Player.h"
#include "../Model.h"
#include "../Enemy/Enemy.h"
#include "../../System/SoundManager.h"

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
	constexpr int kAnimJump = 7;// ジャンプアイドル状態
	constexpr int kAnimDamage = 2;// 敵に当たった時の状態
	constexpr int kAnimWaveHands = 16;// リザルト画面の状態

	// プレイヤーの移動
	// 加速度
	constexpr float kAcceleration = 0.1f;
	// 減速
	constexpr float kDeceleration = 0.5f;
	// 最高速度
	constexpr float kTopSpeed = 15.0f;
	// 回転速度
	constexpr float kRotationSpeed = 0.1f;

	// プレイヤーの移動
	constexpr VECTOR kPlayerVec{ 0.0f,0.0f,-10.0f };
	// 大きさ
	constexpr VECTOR kScale{ 0.5f,0.5f,0.5f };

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
	m_scale(kScale),
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
	m_pSound = std::make_shared<SoundManager>();
	m_roundShadowHandle = LoadGraph(kRoundShadowHandle);// 丸影画像ロード
	m_pModel->SetAnimation(m_animNum, true, true);// アニメーション設定
}

Player::~Player()
{
	// データの削除
	DeleteGraph(m_roundShadowHandle);// 丸影ハンドル
	MV1DeleteModel(m_playerHandle);// モデル
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

#ifdef _DEBUG
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
#else
#endif
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
	DrawBillboard3D(
		VGet(m_pos.x, 10.0f, m_pos.z),
		0.5f, 0.5f,
		120.0f, 2.0f,
		m_roundShadowHandle,
		true
	);

}

// タイトル更新処理
void Player::UpdateTitle()
{
	// プレイヤーのタイトルでのアニメーション
	m_pModel->ChangeAnimation(kAnimJump, true, true, 10);
	m_pModel->Update(1.0f);


	InitState(VGet(-200.0f, -170.0f, 0.0f), VGet(0.0f, 0.2f, 0.0f), m_scale);
}

void Player::UpdateResult()
{
	// プレイヤーのタイトルでのアニメーション
	m_pModel->ChangeAnimation(kAnimWaveHands, true, true, 10);
	m_pModel->Update(0.6f);

	InitState(VGet(-150.0f, -50.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f), m_scale);
}

void Player::DrawUI(int color, int fontHandle)
{
	// モデルのハンドル取得
	int handle = m_pModel->GetModelHandle();

	// モデル内にあるHPバーを表示する座標のデータを取得する
	int frameNo = MV1SearchFrame(handle, "CharacterArmature");
	// HPバーを表示する座標データのワールド座標を取得する
	VECTOR hpPos = MV1GetFramePosition(handle, frameNo);
	// HPバー表示位置のワールド座標をスクリーン座標に変換する
	VECTOR screenPos = ConvWorldPosToScreenPos(hpPos);
	if ((screenPos.z <= 0.0f) || (screenPos.z >= 1.0f))
	{
		// 表示範囲外の場合何も表示しない
		return;
	}

	// HP表示
	DrawFormatStringToHandle(static_cast<int>(screenPos.x) - 13, static_cast<int>(screenPos.y) - 100, color, fontHandle,"%d%%", m_blowRate);
	DrawStringToHandle(static_cast<int>(screenPos.x) - 13, static_cast<int>(screenPos.y) - 70, "▼", Color::kRed, fontHandle);
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
	m_pModel->Update(1.0f);

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
			m_pSound->Start(Sound::Jump, DX_PLAYTYPE_BACK, 255);
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

	InitState(m_pos, VGet(0.5f, m_playerAngleY, 0.0f), m_scale);
}

void Player::PadInputState()
{
	// 入力状態取得
	GetJoypadXInputState(DX_INPUT_PAD1, &m_input);
}

void Player::InitState(VECTOR pos, VECTOR rot, VECTOR scale)
{
	m_pModel->SetPos(pos);// 座標
	m_pModel->SetRot(rot);// 回転
	m_pModel->SetScale(scale);// 大きさ
}


