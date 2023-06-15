#include "SceneMain.h"
#include "SceneTitle.h"
#include "../Util/GameSetting.h"
#include "../Char/Player/Player.h"
#include "../Char/Enemy/Enemy.h"
#include "../Stage/Field.h"

namespace
{
	
}

SceneMain::SceneMain()
{
	m_pSet = new GameSetting;
	m_pPlayer = new Player;
	m_pEnemy = new Enemy;
	m_pField = new Field;

	
}

SceneMain::~SceneMain()
{
	delete m_pSet;
	delete m_pPlayer;
	delete m_pEnemy;
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
	m_pEnemy->Update();

	return this;
}

void SceneMain::Draw()
{
	m_pPlayer->Draw();
	m_pEnemy->Draw();
	m_pField->Draw();
}
