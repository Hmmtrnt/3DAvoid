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
	/*m_pSet = new GameSetting;
	m_pPlayer = new Player;
	m_pEnemy = new Enemy;
	m_pField = new Field;*/

	m_pSet = std::make_shared<GameSetting>();
	m_pPlayer = std::make_shared<Player>();
	//m_pEnemy = std::make_shared<Enemy>();
	m_pField = std::make_shared<Field>();
	
}

SceneMain::~SceneMain()
{
	/*delete m_pSet;
	delete m_pPlayer;
	delete m_pEnemy;
	delete m_pField;*/
}

void SceneMain::Init()
{
	m_pSet->Init3D();
	m_pSet->InitCamera();
	m_pPlayer->Init();
	m_pField->Init();

	// 一体目のエネミー生成
	m_pEnemy.push_back(std::make_shared<Enemy>(m_pPlayer));
	m_pEnemy.back()->Init();

	// 二体目以降は一体目をコピー
	int enemyModelHandle = m_pEnemy.back()->GetModelHandle();
	for (int i = 0; i < 10; i++)
	{
		m_pEnemy.push_back(std::make_shared<Enemy>(enemyModelHandle, m_pPlayer));
		m_pEnemy.back()->Init();
	}
}

void SceneMain::End()
{
	m_pPlayer->End();
}

SceneBase* SceneMain::Update()
{
	m_pPlayer->Update();
	//m_pEnemy->Update();

	return this;
}

void SceneMain::Draw()
{
	m_pPlayer->Draw();
	//m_pEnemy->Draw();
	m_pField->Draw();
}
