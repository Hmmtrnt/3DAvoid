#include "SceneMain.h"
#include "SceneTitle.h"// �f�o�b�O�p
#include "SceneResult.h"
#include "../Util/GameSetting.h"
#include "../Char/Player/Player.h"
#include "../Char/Enemy/Enemy.h"
#include "../Stage/Field.h"
#include <cassert>
#include "../Util/FontFunction.h"
#include "../System/Pause.h"

namespace
{
	// �摜�̃t�@�C���̏ꏊ
	const char* const kImgName = "Data/BackGround/FieldBackGround.jpg";
}

SceneMain::SceneMain() :
	m_updateFunc(&SceneMain::UpdatePauseNo),
	m_shadowMap(0),
	m_invincibleTime(0),
	m_hpRedColor(0),
	m_hpColor(0),
	m_score(0),
	m_BackGroundHandle(-1),
	m_enemyModelHandle(0),
	m_hit(false),
	m_hitting(false),
	m_pushPause(false)
{
	// �|�C���^�̃������m�ی�Ŏ����I�ɉ�������
	m_pSet = std::make_shared<GameSetting>();
	m_pPlayer = std::make_shared<Player>();
	m_pField = std::make_shared<Field>();
	m_pFont = std::make_shared<StringInit>();
	m_pPause = std::make_shared<Pause>();
	
	m_BackGroundHandle = LoadGraph(kImgName);
	assert(m_BackGroundHandle != -1);

	m_red = 255;

	m_decreaseColor = 255 - (m_pPlayer->GetBlowRate() * 2);
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
	m_pFont->Init(30, 0, -1);

	m_hpColor = Color::kWhite;

	// ��̖ڂ̃G�l�~�[����
	m_pEnemy.push_back(std::make_shared<Enemy>(m_pPlayer));
	m_pEnemy.back()->Init();

	// ��̖ڈȍ~�͈�̖ڂ��R�s�[
	m_enemyModelHandle = m_pEnemy.back()->GetModelHandle();
	for (int i = 0; i < 19; i++)
	{
		m_debugEnemyNum++;
		m_pEnemy.push_back(std::make_shared<Enemy>(m_enemyModelHandle, m_pPlayer, m_debugEnemyNum));
		m_pEnemy.back()->Init();
	}

	// �V���h�E�}�b�v�̐���
	m_shadowMap = MakeShadowMap(1024, 1024);
	SetShadowMapLightDirection(m_shadowMap, GetLightDirection());
}

void SceneMain::End()
{
	m_pPlayer->End();
	m_pFont->End();
	// �V���h�E�}�b�v�̍폜
	DeleteShadowMap(m_shadowMap);
}

// �X�V����
SceneBase* SceneMain::Update()
{
	(this->*m_updateFunc)();

	if (m_score != 0)
	{
		if (m_score % 1000 == 0 /*Pad::IsTrigger(PAD_INPUT_7)*/)
		{
			for (int i = 0; i < 10; i++)
			{
				m_debugEnemyNum++;
				m_pEnemy.push_back(std::make_shared<Enemy>(m_enemyModelHandle, m_pPlayer, m_debugEnemyNum));
				m_pEnemy.back()->Init();
			}
		}
	}
	

	// �|�[�Y�{�^�����������Ƃ��̏���
	if (Pad::IsTrigger(PAD_INPUT_8))
	{
		if (!m_pushPause)
		{
			m_pushPause = true;
		}
		else
		{
			m_pushPause = false;
		}
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
			//TODO:PAD_INPUT_1�ɖ߂�(�f�o�b�O���I�������)
			if (Pad::IsTrigger(PAD_INPUT_4))
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
	// �w�i�̕`��
	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_BackGroundHandle, true);

	// �v���C���[�̕`��
	if (m_invincibleTime % 3 == 0)
	{
		m_pPlayer->Draw();
	}

	// �G�̕`��
	for (auto& enemies : m_pEnemy)
	{
		enemies->Draw();
	}
	// �X�e�[�W�`��
	m_pField->Draw();

	// �󂯂��_���[�W�ɂ���ĐF�ύX
	UpdateColor();

	// ���������₷������
	SetDrawBlendMode(DX_BLENDMODE_MULA, 155);
	DrawBox(0, 85, 300, 250, Color::kBlack, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// �v���C���[�̐�����ї��`��
	m_pFont->DrawFormat(10, 90, m_hpColor, "%d%%", m_pPlayer->GetBlowRate());

	// �X�R�A�`��
	m_pFont->DrawFormat(10, 120, Color::kWhite, "score:%d", m_score);

	// �Q�[���I�[�o�[�ɂȂ������̏���
	if (m_pPlayer->GetPos().y < -100.0f)
	{
		m_pFont->DrawNoFormat(0, 150, "�Q�[���I�[�o�[", Color::kWhite);
		m_pFont->DrawNoFormat(0, 180, "���g���C:PAD_INPUT_4", Color::kWhite);

	}

	if (m_pushPause)
	{
		m_pPause->Draw();
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
				m_pPlayer->UpdateHitDamage(enemies->GetPos(), m_hit);
				m_hit = true;
				m_invincibleTime = 120;
			}
		}
	}
	// �����������̃v���C���[�̍��W����
	if(m_invincibleTime >= 110)
	{
		m_hitting = true;
		m_pPlayer->UpdateHitVec();
			
		// �G�ɓ����������̃R���g���[���[�̐U��
		StartJoypadVibration(DX_INPUT_PAD1, 300, 100, -1);

	}
	// �������Ă��Ȃ���Ԃɖ߂�
	if (m_invincibleTime < 110)
	{
		m_hit = false;
		m_hitting = false;
	}

	// ���������E�˔j���Ȃ��悤�ɂ���
	if (m_invincibleTime > 0)
	{
		m_invincibleTime--;
	}

	if (m_pPlayer->GetIsFall())
	{
		m_invincibleTime = 0;
	}
}

void SceneMain::UpdateColor()
{
	

	m_hpColor = GetColor(m_red, m_decreaseColor, m_decreaseColor);

	if (m_decreaseColor < 0)
	{
		m_decreaseColor = 0;
	}
	else if(m_decreaseColor != 0)
	{
		m_decreaseColor = 255 - (m_pPlayer->GetBlowRate() * 2);
	}

}

void SceneMain::UpdatePauseNo()
{
	m_pPlayer->Update(m_hitting);
	UpdateEnemy();

	// �Q�[�����i��ł���ԃX�R�A�𑝂₷
	if (!m_pPlayer->GetIsFall())
	{
		m_score++;
	}
	if (m_pushPause)
	{
		m_updateFunc = &SceneMain::UpdatePause;
	}
}

void SceneMain::UpdatePause()
{
	m_pPause->Update();
	if (!m_pushPause)
	{
		m_updateFunc = &SceneMain::UpdatePauseNo;
	}
}
