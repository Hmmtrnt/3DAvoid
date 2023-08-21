#include <cassert>
#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneExplanation.h"
#include "SceneMain.h"
#include "SceneResult.h"
#include "../Util/Pad.h"

SceneManager::SceneManager()
{
	m_pScene = nullptr;
}
// ������
void SceneManager::Init()
{
#ifdef _DEBUG
	//m_pScene = new SceneTitle;
	m_pScene = new SceneExplanation;
	//m_pScene = new SceneMain;
	//m_pScene = new SceneResult;
#else
	m_pScene = new SceneTitle;
#endif
	m_pScene->Init();
}
// �I��
void SceneManager::End()
{
	// �m�F����
	assert(m_pScene);
	if (!m_pScene)	return;

	m_pScene->End();
	delete m_pScene;
}
// ���t���[���̏���
void SceneManager::Update()
{
	Pad::Update();
	// �m�F����
	assert(m_pScene);
	if (!m_pScene)	return;
	// SceneBase��update�����Ăяo��
	SceneBase* pScene = m_pScene->Update();
	if (pScene != m_pScene)
	{
		m_pScene->End();
		delete m_pScene;
		// ������
		m_pScene = pScene;
		m_pScene->Init();
	}
}
// �`��
void SceneManager::Draw()
{
	assert(m_pScene);
	if (!m_pScene)	return;
	m_pScene->Draw();
}