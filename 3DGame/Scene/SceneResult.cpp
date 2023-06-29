#include "SceneResult.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "../Util/common.h"
#include "../Util/FontFunction.h"

SceneResult::SceneResult(int score) :
	m_score(score)
{
	m_pFont = std::make_shared<StringInit>();
}

SceneResult::~SceneResult()
{
}

void SceneResult::Init()
{
	m_pFont->Init(80, 0, -1);
}

void SceneResult::End()
{
	m_pFont->End();
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
			return (new SceneMain);
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

	// スコア描画
	m_pFont->DrawFormat(10, 120, Color::kWhite, "score:%d", m_score);

	// フェードインアウトのフィルター
	SceneBase::DrawFade();
}
