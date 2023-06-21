#include "SceneMain.h"
#include "SceneTitle.h"
#include "../Util/GameSetting.h"
#include "../Char/Player/Player.h"
#include "../Char/Enemy/Enemy.h"
#include "../Stage/Field.h"

namespace
{
	
}

SceneMain::SceneMain() :
	m_shadowMap(0)
{
	m_pSet = std::make_shared<GameSetting>();
	m_pPlayer = std::make_shared<Player>();
	m_pField = std::make_shared<Field>();
}

SceneMain::~SceneMain()
{
	
}

void SceneMain::Init()
{
	m_pSet->Init3D();
	m_pSet->InitCamera();
	m_pPlayer->Init();
	m_pField->Init();

	// ��̖ڂ̃G�l�~�[����
	m_pEnemy.push_back(std::make_shared<Enemy>(m_pPlayer));
	m_pEnemy.back()->Init();

	// ��̖ڈȍ~�͈�̖ڂ��R�s�[
	int enemyModelHandle = m_pEnemy.back()->GetModelHandle();
	for (int i = 0; i < 20; i++)
	{
		m_pEnemy.push_back(std::make_shared<Enemy>(enemyModelHandle, m_pPlayer));
		m_pEnemy.back()->Init();
	}

	// �V���h�E�}�b�v�̐���
	m_shadowMap = MakeShadowMap(1024, 1024);
	SetShadowMapLightDirection(m_shadowMap, GetLightDirection());
}

void SceneMain::End()
{
	m_pPlayer->End();
	// �V���h�E�}�b�v�̍폜
	DeleteShadowMap(m_shadowMap);
}

// �X�V����
SceneBase* SceneMain::Update()
{
	m_pPlayer->Update();

	for (auto& enemies : m_pEnemy)
	{
		enemies->Update();
		if (enemies->ColFlag())
		{
			DrawString(10, 10, "�������Ă���\n", 0xff0000);
			m_pPlayer->m_hp += 1;
		}
	}



	return this;
}

// �`�揈��
void SceneMain::Draw()
{
	m_pPlayer->Draw();

	for (auto& enemies : m_pEnemy)
	{
		enemies->Draw();
	}

	m_pField->Draw();

	DrawFormatString(10, 30, 0xffffff, "�v���C���[��HP�F%d", m_pPlayer->m_hp);
}
