#include "SceneTitle.h"
#include "SceneMain.h"

SceneMain::SceneMain()
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
}

void SceneMain::End()
{
}

SceneBase* SceneMain::Update()
{
	return this;
}

void SceneMain::Draw()
{
	DrawString(0, 0, "Main", Color::kWhite);
}
