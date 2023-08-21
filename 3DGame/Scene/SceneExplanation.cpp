#include "SceneExplanation.h"
#include "../Stage/BackDrop.h"
#include "SceneMain.h"

namespace
{
	const char* const kHandleId = "Data/2D/Explanation.png";
	const char* const kHandleMoveId = "Data/2D/ExplanationMove2.mp4";
}

SceneExplanation::SceneExplanation():
	m_handle(-1),
	m_handleMove(-1),
	m_posX(50),
	m_posY(130)
{
	m_pBackDrop = std::make_shared<BackDrop>();
}

SceneExplanation::~SceneExplanation()
{
}

void SceneExplanation::Init()
{
	m_handle = LoadGraph(kHandleId);
	m_handleMove = LoadGraph(kHandleMoveId);
}

void SceneExplanation::End()
{
	DeleteGraph(m_handle);
	DeleteGraph(m_handleMove);
}

SceneBase* SceneExplanation::Update()
{
	// 背景をスクロール
	m_pBackDrop->Update();
	
	// 動画をループ再生
	PlayMovieToGraph(m_handleMove, DX_PLAYTYPE_LOOP);

	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// フェードアウト終了時
		if (!IsFading() && m_isFadeOut)
		{
			return (new SceneMain());
		}

	}


	if (!IsFading())
	{
		if (Pad::IsTrigger(PAD_INPUT_1) || Pad::IsTrigger(PAD_INPUT_2) ||
			Pad::IsTrigger(PAD_INPUT_3) || Pad::IsTrigger(PAD_INPUT_4))
		{
			StartFadeOut();
		}
	}

	return this;
}

void SceneExplanation::Draw()
{
	// 背景の描画
	m_pBackDrop->Draw();

	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_handle, true);
	DrawExtendGraph(m_posX, m_posY, m_posX + 622, m_posY + 350, m_handleMove, true);

	SceneBase::DrawFade();
}
