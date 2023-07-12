#include "SceneTitle.h"
#include "SceneMain.h"
#include "../Util/GameSetting.h"
#include "../Char/Player/Player.h"
#include "../Char/Enemy/Enemy.h"

namespace
{
	const char* const kTitleHandle = "Data/2D/Title.png";
	const char* const kImgName = "Data/3D/BackGround/FieldBackGround.jpg";
}

SceneTitle::SceneTitle() :
	m_titleHandle(-1)
{
	m_titleHandle = LoadGraph(kTitleHandle);
	m_backGroundHandle = LoadGraph(kImgName);

	m_pSet = std::make_shared<GameSetting>();
	m_pPlayer = std::make_shared<Player>();
	// 一体目のエネミー生成
	m_pEnemy.push_back(std::make_shared<Enemy>(m_pPlayer));
	m_pEnemy.back()->Init();

	m_enemyHandle = m_pEnemy.back()->GetModelHandle();

	m_pEnemy.push_back(std::make_shared<Enemy>(m_enemyHandle));
	m_pEnemy.back()->Init();

}

SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleHandle);
	DeleteGraph(m_backGroundHandle);
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
		}
	}
	
	m_pPlayer->UpdateTitle();

	for (auto& enemies : m_pEnemy) {
		enemies->UpdateTitle();
	}
	

	return this;
}

void SceneTitle::Draw()
{
	DrawBillboard3D(VGet(-1900.0f, 0.0f, 975.0f), 0.5f, 0.5f, 8000.0f, 0.0f, m_backGroundHandle, true);

	m_pPlayer->Draw();
	for (auto& enemies : m_pEnemy) {
		enemies->DrawTitle();
	}
	

	DrawString(0, 0, "Title", 0xffffff);

	//DrawGraph(Game::kScreenWidth, Game::kScreenHeight, m_titleHandle, true);

	//DrawRectRotaGraph(0,0,100,100,100,100,1.0,0.0,m_titleHandle, )

	DrawExtendGraph(350, 200, 900, 400, m_titleHandle, true);

	// フェードインアウトのフィルター
	SceneBase::DrawFade();
}
