#include "SceneTitle.h"
#include "SceneMain.h"
#include "../Util/GameSetting.h"
#include "../Char/Player/Player.h"
#include "../Char/Enemy/Enemy.h"
#include "../Char/Enemy/EnemyBig.h"
#include "../Char/Enemy/EnemyBase.h"
#include "../Stage/Field.h"

namespace
{
	const char* const kTitleHandle = "Data/2D/Title.png";// タイトルロゴ
	const char* const kImgName = "Data/3D/BackGround/FieldBackGround.jpg";// 背景
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

}

SceneTitle::SceneTitle() :
	m_titleHandle(-1)
{
	m_titleHandle = LoadGraph(kTitleHandle);
	m_backGroundHandle = LoadGraph(kImgName);

	m_pSet = std::make_shared<GameSetting>();
	m_pPlayer = std::make_shared<Player>();
	// 一体目のエネミー生成
	m_pEnemy.push_back(std::make_shared<Enemy>());
	m_pEnemy.back()->Init();
	m_enemyHandle = m_pEnemy.back()->GetModelHandle();
	m_pEnemy.push_back(std::make_shared<Enemy>(m_enemyHandle));
	m_pEnemy.back()->Init();
	m_pEnemyBig = std::make_shared<EnemyBig>();
	m_pField = std::make_shared<Field>();


	// 丸影ハンドルロード
	for (int i = 0; i < 4; i++)
	{
		m_roundShadowHandle[i] = LoadGraph(kRoundShadowHandle);
	}
	
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleHandle);
	DeleteGraph(m_backGroundHandle);

	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(m_roundShadowHandle[i]);
	}
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
		/*if (Pad::IsTrigger(PAD_INPUT_1))
		{
			StartFadeOut();
		}*/
	}
	
	// キャラクターたちのタイトルでのモーション
	m_pPlayer->UpdateTitle();
	for (auto& enemies : m_pEnemy) {
		enemies->UpdateTitle();
	}
	m_pEnemyBig->UpdateTitle();
	

	return this;
}

void SceneTitle::Draw()
{
	//DrawBillboard3D(VGet(-1900.0f, 0.0f, 975.0f), 0.5f, 0.5f, 8000.0f, 0.0f, m_backGroundHandle, true);
	
	DrawGraph(0, 0, m_backGroundHandle, true);


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
		DrawExtendGraph(posX, posY, ScaleX, ScaleY, m_roundShadowHandle[i], true);
	}

	
	m_pPlayer->Draw();
	for (auto& enemies : m_pEnemy) {
		enemies->DrawTitle();
	}
	m_pEnemyBig->Draw();

	

	DrawGraph(250, 100, m_titleHandle, true);

	// フェードインアウトのフィルター
	SceneBase::DrawFade();
}
