#include "SceneTitle.h"
#include "SceneMain.h"

SceneTitle::SceneTitle()
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
}

void SceneTitle::End()
{
}

SceneBase* SceneTitle::Update()
{
	// �t�F�[�h�C���A�E�g���Ă���
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// �t�F�[�h�A�E�g�I����
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			return (new SceneMain);
		}
	}

	if (!IsFading())
	{
		// �t�F�[�h�A�E�g�J�n
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			StartFadeOut();
		}
	}
	

	return this;
}

void SceneTitle::Draw()
{
	DrawString(0, 0, "Title", 0xffffff);

	// �t�F�[�h�C���A�E�g�̃t�B���^�[
	SceneBase::DrawFade();
}
