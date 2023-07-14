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
	const char* const kTitleHandle = "Data/2D/Title2.png";// �^�C�g�����S
	const char* const kStringHandle = "Data/2D/Press_any_botton.png";// ������̉摜�n���h��
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

	// �^�C�g���̍��W�A�傫���̏����l
	// ���W
	const int kTitleInitPosX = 200 - 200;// X
	const int kTitleInitPosY = 100 - 200;// Y
	// �傫��
	const int kTitleInitScaleX = 800 + 400;// ��
	const int kTitleInitScaleY = 200 + 400;// ����

	// �^�C�g���̍��W�A�傫���̍ŏI�I�Ȓl
	// ���W
	const int kTitlePosX = 200;// X
	const int kTitlePosY = 100;// Y
	// �傫��
	const int kTitleScaleX = 800;// ��
	const int kTitleScaleY = 200;// ����

	// �^�C�g���̏k�����x
	const int kTitleShrinkSpeed = 4;

	// �^�C�g���̃��u�����h�̃p�����[�^�㏸���x
	const int kTitleAlphaSpeed = 5;
}

SceneTitle::SceneTitle() :
	m_titleHandle(-1),
	m_titlePosX(kTitleInitPosX),
	m_titlePosY(kTitleInitPosY),
	m_titleScaleX(kTitleInitScaleX),
	m_titleScaleY(kTitleInitScaleY),
	m_drawFlashingInterval(0),
	m_topNumInterval(100),
	m_alphaParameter(0),
	m_isDraw(false),
	m_isPush(false)
{
	m_titleHandle = LoadGraph(kTitleHandle);

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
	m_roundShadowHandle = LoadGraph(kRoundShadowHandle);

	// ������̉摜�n���h�����[�h
	m_stringHandle = LoadGraph(kStringHandle);
	
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleHandle);
	DeleteGraph(m_roundShadowHandle);
	DeleteGraph(m_stringHandle);
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
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			StartFadeOut();
			m_topNumInterval = 10;
			m_isPush = true;
		}
	}
	// �w�i�X�N���[��
	m_pBackDrop->Update();

	// �L�����N�^�[�����̃^�C�g���ł̃��[�V����
	m_pPlayer->UpdateTitle();
	for (auto& enemies : m_pEnemy) {
		enemies->UpdateTitle();
	}
	m_pEnemyBig->UpdateTitle();
	
	UpdateTitleLogo();

	if (m_isPush)
	{
		m_isDraw = DrawPushInterval();
	}
	else
	{
		m_isDraw = DrawInterval();
		//m_isDraw = DrawPushInterval();
	}
	

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
		DrawExtendGraph(posX, posY, ScaleX, ScaleY, m_roundShadowHandle, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, BlendParameter::kMaxBlendParameter);

	
	m_pPlayer->Draw();
	for (auto& enemies : m_pEnemy) {
		enemies->DrawTitle();
	}
	m_pEnemyBig->Draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alphaParameter);
	DrawExtendGraph(m_titlePosX, m_titlePosY, 
		m_titlePosX + m_titleScaleX, 
		m_titlePosY + m_titleScaleY, 
		m_titleHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// �C���^�[�o���ɂ���ĕ`��؂�ւ�����
	IntervalAdvance(m_topNumInterval);
	if (m_isDraw)
	{
		// press any botton�`��
		DrawExtendGraph(420, 480, 850, 750, m_stringHandle, true);
	}
	

	// �f�o�b�O�p������`��
	/*DrawFormatString(0, 0, Color::kRed, "m_titlePosX = %d", m_titlePosX);
	DrawFormatString(0, 20, Color::kRed, "m_titlePosY = %d", m_titlePosY);
	DrawFormatString(0, 40, Color::kRed, "m_titleScaleX = %d", m_titleScaleX);
	DrawFormatString(0, 60, Color::kRed, "m_titleScaleY = %d", m_titleScaleY);*/

	// �t�F�[�h�C���A�E�g�̃t�B���^�[
	SceneBase::DrawFade();
}

// �^�C�g�����S�̍X�V����
void SceneTitle::UpdateTitleLogo()
{
	// �^�C�g�����S�̏k��
	if (m_titlePosX < kTitlePosX || m_titlePosY < kTitlePosY ||
		m_titleScaleX > kTitleScaleX || m_titleScaleY > kTitleScaleY)
	{
		m_titlePosX += kTitleShrinkSpeed;
		m_titlePosY += kTitleShrinkSpeed;
		m_titleScaleX -= kTitleShrinkSpeed * 2;
		m_titleScaleY -= kTitleShrinkSpeed * 2;
	}
	if (m_alphaParameter <= BlendParameter::kMaxBlendParameter)
	{
		m_alphaParameter += kTitleAlphaSpeed;
	}
	else
	{
		m_alphaParameter = BlendParameter::kMaxBlendParameter;
	}
}

void SceneTitle::IntervalAdvance(int topNum)
{
	// �C���^�[�o���i�s
	m_drawFlashingInterval++;

	// topNum�𒴂������ɂȂ�����߂�
	if (m_drawFlashingInterval >= topNum)
	{
		m_drawFlashingInterval = 0;
	}
}

bool SceneTitle::DrawInterval()
{
	// �C���^�[�o����30�������ƕ`��ł��Ȃ�
	if (m_drawFlashingInterval < 30)
	{
		return false;
	}

	return true;
}

bool SceneTitle::DrawPushInterval()
{
	// �C���^�[�o����5�Ŋ���؂�鐔�ɂȂ�����`��ł��Ȃ�
	if (m_drawFlashingInterval < 5)
	{
		return false;
	}

	return true;
}
