#include "SceneMain.h"
#include "SceneTitle.h"// �f�o�b�O�p
#include "SceneResult.h"
#include "../Util/GameSetting.h"
#include "../Char/Player/Player.h"
#include "../Char/Enemy/Enemy.h"
#include "../Stage/Field.h"
#include <cassert>

namespace
{
	// �摜�̃t�@�C���̏ꏊ
	const char* const kImgName = "Data/BackGround/FieldBackGround.jpg";
}

SceneMain::SceneMain() :
	m_shadowMap(0),
	m_invincibleTime(0),
	m_hpRedColor(0),
	m_hpColor(0),
	m_score(0),
	m_BackGroundHandle(-1),
	m_hit(false),
	m_hitting(false)
{
	m_pSet = std::make_shared<GameSetting>();
	m_pPlayer = std::make_shared<Player>();
	m_pField = std::make_shared<Field>();
	
	m_BackGroundHandle = LoadGraph(kImgName);
	assert(m_BackGroundHandle != -1);
}

SceneMain::~SceneMain()
{
	DeleteGraph(m_BackGroundHandle);
}

void SceneMain::Init()
{
	m_pSet->Init3D();
	m_pSet->InitCamera();
	m_pPlayer->Init();
	m_pField->Init();


	m_hpColor = Color::kWhite;

	// ��̖ڂ̃G�l�~�[����
	m_pEnemy.push_back(std::make_shared<Enemy>(m_pPlayer));
	m_pEnemy.back()->Init();

	// ��̖ڈȍ~�͈�̖ڂ��R�s�[
	int enemyModelHandle = m_pEnemy.back()->GetModelHandle();
	for (int i = 0; i < 19; i++)
	{
		m_debugEnemyNum++;
		m_pEnemy.push_back(std::make_shared<Enemy>(enemyModelHandle, m_pPlayer, m_debugEnemyNum));
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
	m_pPlayer->Update(m_hitting);
	UpdateEnemy();
	
	// �Q�[�����i��ł���ԃX�R�A�𑝂₷
	if (!m_pPlayer->GetIsFall())
	{
		m_score++;
	}
	
	

	// �t�F�[�h�C���A�E�g���Ă���
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// �t�F�[�h�A�E�g�I����
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			return (new SceneResult);
		}
	}

	if (m_pPlayer->GetIsFall())
	{
		if (!IsFading())
		{
			if (Pad::IsTrigger(PAD_INPUT_1))
			{
				return new SceneMain;// �f�o�b�O�p�V�[���J��

				//StartFadeOut();// �{�ԗp�V�[���J��
			}
		}
	}

	return this;
}

// �`�揈��
void SceneMain::Draw()
{
	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_BackGroundHandle, true);

	if (m_invincibleTime % 3 == 0)
	{
		m_pPlayer->Draw();
	}

	for (auto& enemies : m_pEnemy)
	{
		enemies->Draw();
	}
	m_pField->Draw();

	/*DrawFormatString(10, 30, Color::kCoral, "%d", m_pPlayer->GetBlowRate());
	DrawFormatString(10, 50, Color::kTomato, "%d", m_pPlayer->GetBlowRate());
	DrawFormatString(10, 70, Color::kOrangered, "%d", m_pPlayer->GetBlowRate());
	DrawFormatString(10, 90, Color::kRed, "%d", m_pPlayer->GetBlowRate());*/

	// �󂯂��_���[�W�ɂ���ĐF�ύX
	UpdateColor();

	// �v���C���[�̐�����ї��`��
	DrawFormatString(10, 90, m_hpColor, "%d%%", m_pPlayer->GetBlowRate());
	// �X�R�A�`��
	DrawFormatString(10, 110, Color::kWhite, "score:%d", m_score);

	// �Q�[���I�[�o�[�ɂȂ������̏���
	if (m_pPlayer->GetPos().y < -100.0f)
	{
		DrawString(0, 130, "�Q�[���I�[�o�[", 0xffffff);
		DrawString(0, 150, "���g���C:PAD_INPUT_1", 0xffffff);
	}

	// �t�F�[�h�C���A�E�g�̃t�B���^�[
	SceneBase::DrawFade();

}

void SceneMain::UpdateEnemy()
{
	// �����������̏���
	for (auto& enemies : m_pEnemy)
	{
		enemies->Update();
		if (m_invincibleTime <= 0)
		{
			// �����������̃_���[�W�ǉ�
			if (enemies->ColFlag())
			{
				DrawString(10, 10, "�������Ă���\n", 0xff0000);
				m_pPlayer->UpdateHitDamage();
				m_invincibleTime = 120;
			}
		}
		// �����������̃v���C���[�̍��W����
		if(m_invincibleTime >= 110)
		{
			m_hitting = true;
			m_pPlayer->UpdateHitVec(enemies->GetPos(), m_hit);
			m_hit = true;
		}
		// �������Ă��Ȃ���Ԃɖ߂�
		if (m_invincibleTime < 110)
		{
			m_hit = false;
			m_hitting = false;
		}

	}

	if (m_invincibleTime > 0)
	{
		m_invincibleTime--;
	}
}

void SceneMain::UpdateColor()
{
	m_hpColor = GetColor(255, 255 - (m_pPlayer->GetBlowRate() * 2), 255 - (m_pPlayer->GetBlowRate() * 2));
}
