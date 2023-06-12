#include "SceneMain.h"
#include "SceneTitle.h"
#include "../Util/GameSetting.h"
#include "../Char/Player/Player.h"
#include "../Stage/Field.h"

namespace
{
	
}

SceneMain::SceneMain()
{
	m_pSet = new GameSetting;
	m_pPlayer = new Player;
	m_pField = new Field;

	
}

SceneMain::~SceneMain()
{
	delete m_pSet;
	delete m_pPlayer;
	delete m_pField;
}

void SceneMain::Init()
{
	m_pSet->Init3D();
	m_pSet->InitCamera();
	m_pPlayer->Init();
	m_pField->Init();
}

void SceneMain::End()
{
	m_pPlayer->End();
}

SceneBase* SceneMain::Update()
{
	m_pPlayer->Update();
	

	return this;
}

void SceneMain::Draw()
{
	// -500~500の範囲にグリッドを表示
	for (float x = -500.0f; x <= 500.0f; x += 100.0f)
	{
		VECTOR start = VGet(x, 0.0f, -500.0f);
		VECTOR end = VGet(x, 0.0f, 500.0f);
		DrawLine3D(start, end, GetColor(0, 255, 255));
	}
	for (float z = -500.0f; z <= 500.0f; z += 100.0f)
	{
		VECTOR start = VGet(-500.0f, 0.0f, z);
		VECTOR end = VGet(500.0f, 0.0f, z);
		DrawLine3D(start, end, GetColor(255, 0, 0));
	}

	m_pPlayer->Draw();

	m_pField->Draw();
}
