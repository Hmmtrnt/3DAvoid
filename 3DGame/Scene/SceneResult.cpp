#include "SceneResult.h"
#include "SceneTitle.h"

SceneResult::SceneResult()
{
}

SceneResult::~SceneResult()
{
}

SceneBase* SceneResult::Update()
{
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		return new SceneTitle;
	}

	return this;
}

void SceneResult::Draw()
{
	DrawString(0, 0, "Result", 0xffffff);
}
