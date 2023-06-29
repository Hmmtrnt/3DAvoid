#include "SceneBase.h"
#include "../Util/common.h"

namespace
{
	// フェード速度
	constexpr int kFadeSpeed = 5;
	constexpr int kVolumeSpeed = 5;
}

SceneBase::SceneBase() :
	m_fadeColor(Color::kBlack),
	m_fadeBright(255),
	m_fadeSpeed(-kFadeSpeed),
	m_isFadeOut(false),
	m_isBackScene(false)
{
}

void SceneBase::UpdateFade()
{
	m_fadeBright += m_fadeSpeed;
	if (m_fadeBright >= 255)
	{
		m_fadeBright = 255;
		if (m_fadeSpeed > 0)
		{
			m_fadeSpeed = 0;
		}
	}
	if (m_fadeBright <= 0)
	{
		m_fadeBright = 0;
		if (m_fadeSpeed < 0)
		{
			m_fadeSpeed = 0;
		}
	}
}

void SceneBase::DrawFade() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeBright);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_fadeColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool SceneBase::IsFadingIn() const
{
	if (m_fadeSpeed < 0)	return true;
	return false;
}

bool SceneBase::IsFadingOut() const
{
	if (m_fadeSpeed > 0)	return true;
	return false;
}

void SceneBase::StartFadeOut()
{
	m_fadeSpeed = kFadeSpeed;
}

