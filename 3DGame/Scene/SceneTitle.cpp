#include "SceneTitle.h"
#include "SceneMain.h"
#include "../Util/GameSetting.h"
#include "../Char/Player/Player.h"
#include "../Char/Enemy/Enemy.h"
#include "../Char/Enemy/EnemyBig.h"
#include "../Char/Enemy/EnemyBase.h"
#include "../Stage/Field.h"
#include "../Stage/BackDrop.h"

namespace
{
	const char* const kTitleHandle = "Data/2D/Title.png";// �^�C�g�����S
	const char* const kImgName = "Data/3D/BackGround/FieldBackGround.jpg";// �w�i
	const char* const kRoundShadowHandle = "Data/2D/RoundShadow5.png";// �ۉe


	// �ۉe�`����W
	// �v���C���[
	const int kPlayerPosX = 240;
	const int kPlayerPosY = 600;
	// ���F�̃G�l�~�[
	const int kYellowEnemyRightPosX = 880;
	const int kYellowEnemyRightPosY = 550;
	const int kYellowEnemyLeftPosX = 670;
	const int kYellowEnemyLeftPosY = 550;

	// �ԐF�̃G�l�~�[
	const int kRedEnemyPosX = 700;
	const int kRedEnemyPosY = 500;

}

SceneTitle::SceneTitle() :
	m_titleHandle(-1)
{
	m_titleHandle = LoadGraph(kTitleHandle);
	m_backGroundHandle = LoadGraph(kImgName);

	// �Q�[���̏��
	m_pSet = std::make_shared<GameSetting>();

	// �v���C���[
	m_pPlayer = std::make_shared<Player>();

	// ��̖ڂ̃G�l�~�[
	m_pEnemy.push_back(std::make_shared<Enemy>());
	m_pEnemy.back()->Init();

	// ��̖ڕ���
	m_enemyHandle = m_pEnemy.back()->GetModelHandle();
	m_pEnemy.push_back(std::make_shared<Enemy>(m_enemyHandle));
	m_pEnemy.back()->Init();

	// �傫���G�l�~�[
	m_pEnemyBig = std::make_shared<EnemyBig>();
	m_pField = std::make_shared<Field>();

	// �w�i
	m_pBackDrop = std::make_shared<BackDrop>();

	// �ۉe�n���h�����[�h
	for (int i = 0; i < 4; i++)
	{
		m_roundShadowHandle[i] = LoadGraph(kRoundShadowHandle);
	}
	
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleHandle);
	DeleteGraph(m_backGroundHandle);

	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(m_roundShadowHandle[i]);
	}
}

void SceneTitle::Init()
{
	m_pSet->Init3D();
	m_pSet->InitSceneTitleCamera();
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
		/*if (Pad::IsTrigger(PAD_INPUT_1))
		{
			StartFadeOut();
		}*/
	}
	// �w�i�X�N���[��
	m_pBackDrop->Update();

	// �L�����N�^�[�����̃^�C�g���ł̃��[�V����
	m_pPlayer->UpdateTitle();
	for (auto& enemies : m_pEnemy) {
		enemies->UpdateTitle();
	}
	m_pEnemyBig->UpdateTitle();
	

	return this;
}

void SceneTitle::Draw()
{
	// �w�i�`��
	m_pBackDrop->Draw();

	// �n�ʕ`��
	m_pField->DrawTitle();

	int posX = 0;
	int posY = 0;
	int ScaleX = 0;
	int ScaleY = 0;

	// �ۉe�`��
	for (int i = 0; i < 4; i++)
	{

		if (i == 0)
		{
			posX = kPlayerPosX;
			posY = kPlayerPosY;
			ScaleX = posX + 200;
			ScaleY = posY + 20;
		}
		if (i == 1)
		{
			posX = kYellowEnemyRightPosX;
			posY = kYellowEnemyRightPosY;
			ScaleX = posX + 150;
			ScaleY = posY + 20;
		}
		if (i == 2)
		{
			posX = kYellowEnemyLeftPosX;
			posY = kYellowEnemyLeftPosY;
			ScaleX = posX + 150;
			ScaleY = posY + 20;
		}
		if (i == 3)
		{
			posX = kRedEnemyPosX;
			posY = kRedEnemyPosY;
			ScaleX = posX + 300;
			ScaleY = posY + 20;
		}
		DrawExtendGraph(posX, posY, ScaleX, ScaleY, m_roundShadowHandle[i], true);
	}

	
	m_pPlayer->Draw();
	for (auto& enemies : m_pEnemy) {
		enemies->DrawTitle();
	}
	m_pEnemyBig->Draw();

	

	DrawGraph(250, 100, m_titleHandle, true);

	// �t�F�[�h�C���A�E�g�̃t�B���^�[
	SceneBase::DrawFade();
}
