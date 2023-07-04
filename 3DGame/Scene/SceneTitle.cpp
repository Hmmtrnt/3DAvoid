#include "SceneTitle.h"
#include "SceneMain.h"

namespace
{
	const char* const kTitleHandle = "Data/2DImg/Title.png";
}

SceneTitle::SceneTitle() :
	m_titleHandle(-1)
{
	m_titleHandle = LoadGraph(kTitleHandle);
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleHandle);
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

	//DrawGraph(Game::kScreenWidth, Game::kScreenHeight, m_titleHandle, true);

	//DrawRectRotaGraph(0,0,100,100,100,100,1.0,0.0,m_titleHandle, )

	DrawExtendGraph(300, 300, 700, 500, m_titleHandle, true);

	// �t�F�[�h�C���A�E�g�̃t�B���^�[
	SceneBase::DrawFade();
}
