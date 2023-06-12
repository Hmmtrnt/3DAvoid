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
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		return new SceneMain;
	}

	return this;
}

void SceneTitle::Draw()
{
	DrawString(0, 0, "Title", 0xffffff);
}
