#include "SceneMain.h"
#include "SceneTitle.h"// �f�o�b�O�p
#include "SceneResult.h"
#include "../Util/GameSetting.h"
#include "../Char/Player/Player.h"
#include "../Char/Enemy/Enemy.h"
#include "../Char/Enemy/EnemyBig.h"
#include "../Stage/Field.h"
#include "../Stage/BackDrop.h"
#include <cassert>
#include "../Util/FontFunction.h"
#include "../System/Pause.h"

namespace
{
}

SceneMain::SceneMain() :
	m_updateFunc(&SceneMain::UpdatePauseNo),
	m_shadowMap(0),
	m_invincibleTime(0),
	m_hpRedColor(0),
	m_hpColor(0),
	m_score(0),
	m_enemyModelHandle(-1),
	m_shadowHandle(-1),
	m_fontHpHandle(-1),
	m_fontScoreHnadle(-1),
	m_scoreHandle(-1),
	m_selectNum(0),
	m_hit(false),
	m_hitting(false),
	m_pushPause(false),
	m_isNoteOpen(false)
{
	// �|�C���^�̃������m�ی�Ŏ����I�ɉ�������
	m_pSet = std::make_shared<GameSetting>();
	m_pPlayer = std::make_shared<Player>();
	m_pField = std::make_shared<Field>();
	m_pBackDrop = std::make_shared<BackDrop>();
	m_pFont = std::make_shared<StringInit>();
	m_pPause = std::make_shared<Pause>();

	m_red = 255;

	m_decreaseColor = 255 - (m_pPlayer->GetBlowRate() * 2);

	m_scoreHandle = LoadGraph("Data/2D/Score.png");
}

SceneMain::~SceneMain()
{
	DeleteGraph(m_scoreHandle);
}

void SceneMain::Init()
{
	m_pSet->InitScenePlayPosCamera();
	m_pPlayer->Init();
	m_pField->Init();
	m_pFont->Init(m_fontHpHandle, 30, 0, -1);
	m_pFont->Init(m_fontScoreHnadle, 50, 0, -1);

	m_hpColor = Color::kWhite;

	// ��̖ڂ̃G�l�~�[����
	m_pEnemy.push_back(std::make_shared<Enemy>(m_pPlayer));
	m_pEnemy.back()->Init();

	// ��̖ڈȍ~�͈�̖ڂ��R�s�[
	m_enemyModelHandle = m_pEnemy.back()->GetModelHandle();
	m_shadowHandle = m_pEnemy.back()->GetShadowHandle();
	for (int i = 0; i < 19; i++)
	{
		m_pEnemy.push_back(std::make_shared<Enemy>(m_enemyModelHandle, m_shadowHandle,m_pPlayer));
		m_pEnemy.back()->Init();
	}

	// �V���h�E�}�b�v�̐���
	m_shadowMap = MakeShadowMap(1024, 1024);
	SetShadowMapLightDirection(m_shadowMap, GetLightDirection());

}

void SceneMain::End()
{
	m_pPlayer->End();
	m_pFont->End(m_fontHpHandle);
	// �V���h�E�}�b�v�̍폜
	DeleteShadowMap(m_shadowMap);
}

// �X�V����
SceneBase* SceneMain::Update()
{
	// �t�F�[�h�C���A�E�g���Ă���
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// �t�F�[�h�A�E�g�I����
		// �Q�[������蒼���Ƃ�
		if (!IsFading() && m_isFadeOut && !m_isBackScene && m_isNoteOpen)
		{
			// ���g���C
			return (new SceneMain());
			// �|�[�Y��ʂ̍��ڂ�������\��
		}
		// �Q�[����������߂鎞
		else if (!IsFading() && m_isFadeOut && !m_isBackScene && (m_selectNum == 2 || m_pPlayer->GetIsFall()))
		{
			// �Q�[�����I�������Ƃ�
			return (new SceneResult(m_score));
		}

	}

	if (!IsFading())
	{
		// �L��������������܂��͒��ӏ����ł͂�����������V�[���J��
		if (m_pPlayer->GetIsFall() || (Pad::IsTrigger(PAD_INPUT_1) && m_isNoteOpen) || (Pad::IsTrigger(PAD_INPUT_1) && m_selectNum == 2))
		{
			//return new SceneMain;// �f�o�b�O�p�V�[���J��

			StartFadeOut();// �V�[���J��
		}
	}

	// �w�i���X�N���[��
	m_pBackDrop->Update();
	(this->*m_updateFunc)();

	if (m_score != 0)
	{
		// �X�R�A����𒴂��邽�тɓG��������@(�p�b�h�͓G�𑝂₷�f�o�b�O�p)
		if (m_score % 1000 == 0 && m_score <= 6000)
		{
			for (int i = 0; i < 10; i++)
			{
				m_pEnemy.push_back(std::make_shared<Enemy>(m_enemyModelHandle, m_shadowHandle, m_pPlayer));
				m_pEnemy.back()->Init();
			}
		}
		else if (m_score % 1000 == 0 && m_score <= 8000 /*Pad::IsTrigger(PAD_INPUT_7)*/)
		{
			// �ł����G�l�~�[����
			m_pEnemyBig.push_back(std::make_shared<EnemyBig>(m_pPlayer));
			m_pEnemyBig.back()->Init();
		}
	}
	

	// �|�[�Y�{�^�����������Ƃ��̏���
	if (Pad::IsTrigger(PAD_INPUT_8))
	{
		m_pushPause = true;
	}
	// ��蒼�����������Ƃ��̏���
	if (m_selectNum == 1 && Pad::IsTrigger(PAD_INPUT_1))
	{
		m_isNoteOpen = true;
		
	}

	if (m_isNoteOpen)
	{
		if (Pad::IsTrigger(PAD_INPUT_2))
		{
			m_isNoteOpen = false;
		}
	}
	

	

	return this;
}

// �`�揈��
void SceneMain::Draw()
{
	// �w�i�̕`��
	m_pBackDrop->Draw();

	// �X�e�[�W�`��
	m_pField->DrawMain();

	// �v���C���[�̕`��
	if (m_invincibleTime % 3 == 0 || m_pushPause)
	{
		m_pPlayer->Draw();
	}
	if (m_pPlayer->GetPos().x < 1000.0f && m_pPlayer->GetPos().x > -1000.0f &&
		m_pPlayer->GetPos().z < 1000.0f && m_pPlayer->GetPos().z > -1000.0f)
	{
		m_pPlayer->RoundShadow();
	}

	// �G�̕`��
	for (auto& enemiesBig : m_pEnemyBig)
	{
		enemiesBig->Draw();
	}
	for (auto& enemies : m_pEnemy)
	{
		enemies->Draw();
	}
	
	
	// �󂯂��_���[�W�ɂ���ĐF�ύX
	UpdateColor();

	// ���������₷������
	DrawExtendGraph(0, 100, 300, 200, m_scoreHandle, true);

	// �v���C���[�̐�����ї��`��
	m_pPlayer->DrawUI(m_hpColor, m_fontHpHandle);

	// �X�R�A�`��
	DrawFormatStringToHandle(10, 120, Color::kWhite, m_fontScoreHnadle, "score:%d", m_score);

	// �|�[�Y��ʕ`��
	if (m_pushPause)
	{
		m_pPause->DrawPause();

		if (m_isNoteOpen)
		{
			m_pPause->DrawNote();
		}

		
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

	for (auto& enemies : m_pEnemyBig)
	{
		enemies->Update(m_score);
		if (m_invincibleTime <= 0)
		{
			// �����������̃_���[�W�ǉ�
			if (!m_pPlayer->GetIsFall())
			{
				if (enemies->ColFlag())
				{
					DrawString(10, 10, "�������Ă���\n", 0xff0000);
					m_pPlayer->UpdateHitDamage(enemies->GetPos(), m_hit);
					m_hit = true;
					m_invincibleTime = 120;
				}
			}
		}
	}

	// �����������̃v���C���[�̍��W����
	if(m_invincibleTime >= 110)
	{
		m_hitting = true;
		m_pPlayer->UpdateHitVec();
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
	// -------------------------
	// �V�����F�\�L
	// -------------------------
	// �_���[�W�ɂ���ĐF��ύX
	if (m_pPlayer->GetBlowRate() < 11)
	{
		m_hpColor = Color::kWhite;
	}
	else if (m_pPlayer->GetBlowRate() < 31)
	{
		m_hpColor = Color::kCoral;
	}
	else if (m_pPlayer->GetBlowRate() < 61)
	{
		m_hpColor = Color::kTomato;
	}
	else if (m_pPlayer->GetBlowRate() < 81)
	{
		m_hpColor = Color::kOrangered;
	}
	else if (m_pPlayer->GetBlowRate() < 101)
	{
		m_hpColor = Color::kRed;
	}
	

}

void SceneMain::UpdatePauseNo()
{
	m_pPlayer->Update(m_hitting);
	UpdateEnemy();

	// �Q�[�����i��ł���ԃX�R�A�𑝂₷
	if (!m_pPlayer->GetIsFall())
	{
#ifdef _DEBUG
		m_score++;
		//m_score+=10;
#else
		m_score++;
#endif
	}
	if (m_pushPause)
	{
		m_updateFunc = &SceneMain::UpdatePause;
	}
}

void SceneMain::UpdatePause()
{
	// �t�F�[�h�C���A�E�g���Ă��Ȃ���΃|�[�Y��ʂ��������
	if (!IsFading())
	{
		if (!m_isNoteOpen)
		{
			m_pPause->UpdateOpen(m_pushPause);
			m_pPause->Update(m_selectNum);
		}
	}
	
	if (!m_pushPause)
	{
		m_updateFunc = &SceneMain::UpdatePauseNo;
	}

	if (m_selectNum == 0 && Pad::IsTrigger(PAD_INPUT_1))
	{
		m_pushPause = false;
	}

}
