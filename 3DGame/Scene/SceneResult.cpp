#include "SceneResult.h"
#include "SceneTitle.h"
#include "../Util/common.h"

SceneResult::SceneResult()
{
}

SceneResult::~SceneResult()
{
}

void SceneResult::Init()
{
}

void SceneResult::End()
{
}

SceneBase* SceneResult::Update()
{
	// フェードインアウトしている
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// フェードアウト終了時
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			return (new SceneTitle);
		}
	}

	if (!IsFading())
	{
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			StartFadeOut();
		}
	}

	return this;
}

void SceneResult::Draw()
{
	DrawString(0, 0, "Result", Color::kWhite);

	// フェードインアウトのフィルター
	SceneBase::DrawFade();
}
