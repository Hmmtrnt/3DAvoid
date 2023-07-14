#include "SceneTitle.h"
#include "SceneMain.h"
#include "../Util/GameSetting.h"
#include "../Char/Player/Player.h"
#include "../Char/Enemy/Enemy.h"
#include "../Char/Enemy/EnemyBig.h"
#include "../Char/Enemy/EnemyBase.h"
#include "../Stage/Field.h"
#include "../Stage/BackDrop.h"

namespace
{
	const char* const kTitleHandle = "Data/2D/Title2.png";// タイトルロゴ
	const char* const kStringHandle = "Data/2D/Press_any_botton.png";// 文字列の画像ハンドル
	const char* const kRoundShadowHandle = "Data/2D/RoundShadow5.png";// 丸影

	// 丸影描画座標
	// プレイヤー
	const int kPlayerPosX = 240;
	const int kPlayerPosY = 600;
	// 黄色のエネミー
	const int kYellowEnemyRightPosX = 880;
	const int kYellowEnemyRightPosY = 550;
	const int kYellowEnemyLeftPosX = 670;
	const int kYellowEnemyLeftPosY = 550;

	// 赤色のエネミー
	const int kRedEnemyPosX = 700;
	const int kRedEnemyPosY = 500;

	// タイトルの座標、大きさの初期値
	// 座標
	const int kTitleInitPosX = 200 - 200;// X
	const int kTitleInitPosY = 100 - 200;// Y
	// 大きさ
	const int kTitleInitScaleX = 800 + 400;// 幅
	const int kTitleInitScaleY = 200 + 400;// 高さ

	// タイトルの座標、大きさの最終的な値
	// 座標
	const int kTitlePosX = 200;// X
	const int kTitlePosY = 100;// Y
	// 大きさ
	const int kTitleScaleX = 800;// 幅
	const int kTitleScaleY = 200;// 高さ

	// タイトルの縮小速度
	const int kTitleShrinkSpeed = 4;

	// タイトルのαブレンドのパラメータ上昇速度
	const int kTitleAlphaSpeed = 5;
}

SceneTitle::SceneTitle() :
	m_titleHandle(-1),
	m_titlePosX(kTitleInitPosX),
	m_titlePosY(kTitleInitPosY),
	m_titleScaleX(kTitleInitScaleX),
	m_titleScaleY(kTitleInitScaleY),
	m_drawFlashingInterval(0),
	m_topNumInterval(100),
	m_alphaParameter(0),
	m_isDraw(false),
	m_isPush(false)
{
	m_titleHandle = LoadGraph(kTitleHandle);

	// ゲームの状態
	m_pSet = std::make_shared<GameSetting>();

	// プレイヤー
	m_pPlayer = std::make_shared<Player>();

	// 一体目のエネミー
	m_pEnemy.push_back(std::make_shared<Enemy>());
	m_pEnemy.back()->Init();

	// 二体目複製
	m_enemyHandle = m_pEnemy.back()->GetModelHandle();
	m_pEnemy.push_back(std::make_shared<Enemy>(m_enemyHandle));
	m_pEnemy.back()->Init();

	// 大きいエネミー
	m_pEnemyBig = std::make_shared<EnemyBig>();
	m_pField = std::make_shared<Field>();

	// 背景
	m_pBackDrop = std::make_shared<BackDrop>();

	// 丸影ハンドルロード
	m_roundShadowHandle = LoadGraph(kRoundShadowHandle);

	// 文字列の画像ハンドルロード
	m_stringHandle = LoadGraph(kStringHandle);
	
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleHandle);
	DeleteGraph(m_roundShadowHandle);
	DeleteGraph(m_stringHandle);
}

void SceneTitle::Init()
{
	m_pSet->Init3D();
	m_pSet->InitSceneTitleCamera();
}

void SceneTitle::End()
{
}

SceneBase* SceneTitle::Update()
{
	// フェードインアウトしている
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// フェードアウト終了時
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			return (new SceneMain);
		}
	}

	if (!IsFading())
	{
		// フェードアウト開始
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			StartFadeOut();
			m_topNumInterval = 10;
			m_isPush = true;
		}
	}
	// 背景スクロール
	m_pBackDrop->Update();

	// キャラクターたちのタイトルでのモーション
	m_pPlayer->UpdateTitle();
	for (auto& enemies : m_pEnemy) {
		enemies->UpdateTitle();
	}
	m_pEnemyBig->UpdateTitle();
	
	UpdateTitleLogo();

	if (m_isPush)
	{
		m_isDraw = DrawPushInterval();
	}
	else
	{
		m_isDraw = DrawInterval();
		//m_isDraw = DrawPushInterval();
	}
	

	return this;
}

void SceneTitle::Draw()
{
	// 背景描画
	m_pBackDrop->Draw();

	// 地面描画
	m_pField->DrawTitle();

	int posX = 0;
	int posY = 0;
	int ScaleX = 0;
	int ScaleY = 0;

	// 丸影描画
	for (int i = 0; i < 4; i++)
	{

		if (i == 0)
		{
			posX = kPlayerPosX;
			posY = kPlayerPosY;
			ScaleX = posX + 200;
			ScaleY = posY + 20;
		}
		if (i == 1)
		{
			posX = kYellowEnemyRightPosX;
			posY = kYellowEnemyRightPosY;
			ScaleX = posX + 150;
			ScaleY = posY + 20;
		}
		if (i == 2)
		{
			posX = kYellowEnemyLeftPosX;
			posY = kYellowEnemyLeftPosY;
			ScaleX = posX + 150;
			ScaleY = posY + 20;
		}
		if (i == 3)
		{
			posX = kRedEnemyPosX;
			posY = kRedEnemyPosY;
			ScaleX = posX + 300;
			ScaleY = posY + 20;
		}
		DrawExtendGraph(posX, posY, ScaleX, ScaleY, m_roundShadowHandle, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, BlendParameter::kMaxBlendParameter);

	
	m_pPlayer->Draw();
	for (auto& enemies : m_pEnemy) {
		enemies->DrawTitle();
	}
	m_pEnemyBig->Draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alphaParameter);
	DrawExtendGraph(m_titlePosX, m_titlePosY, 
		m_titlePosX + m_titleScaleX, 
		m_titlePosY + m_titleScaleY, 
		m_titleHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// インターバルによって描画切り替えする
	IntervalAdvance(m_topNumInterval);
	if (m_isDraw)
	{
		// press any botton描画
		DrawExtendGraph(420, 480, 850, 750, m_stringHandle, true);
	}
	

	// デバッグ用文字列描画
	/*DrawFormatString(0, 0, Color::kRed, "m_titlePosX = %d", m_titlePosX);
	DrawFormatString(0, 20, Color::kRed, "m_titlePosY = %d", m_titlePosY);
	DrawFormatString(0, 40, Color::kRed, "m_titleScaleX = %d", m_titleScaleX);
	DrawFormatString(0, 60, Color::kRed, "m_titleScaleY = %d", m_titleScaleY);*/

	// フェードインアウトのフィルター
	SceneBase::DrawFade();
}

// タイトルロゴの更新処理
void SceneTitle::UpdateTitleLogo()
{
	// タイトルロゴの縮小
	if (m_titlePosX < kTitlePosX || m_titlePosY < kTitlePosY ||
		m_titleScaleX > kTitleScaleX || m_titleScaleY > kTitleScaleY)
	{
		m_titlePosX += kTitleShrinkSpeed;
		m_titlePosY += kTitleShrinkSpeed;
		m_titleScaleX -= kTitleShrinkSpeed * 2;
		m_titleScaleY -= kTitleShrinkSpeed * 2;
	}
	if (m_alphaParameter <= BlendParameter::kMaxBlendParameter)
	{
		m_alphaParameter += kTitleAlphaSpeed;
	}
	else
	{
		m_alphaParameter = BlendParameter::kMaxBlendParameter;
	}
}

void SceneTitle::IntervalAdvance(int topNum)
{
	// インターバル進行
	m_drawFlashingInterval++;

	// topNumを超えそうになったら戻す
	if (m_drawFlashingInterval >= topNum)
	{
		m_drawFlashingInterval = 0;
	}
}

bool SceneTitle::DrawInterval()
{
	// インターバルが30未満だと描画できない
	if (m_drawFlashingInterval < 30)
	{
		return false;
	}

	return true;
}

bool SceneTitle::DrawPushInterval()
{
	// インターバルが5で割り切れる数になったら描画できない
	if (m_drawFlashingInterval < 5)
	{
		return false;
	}

	return true;
}
