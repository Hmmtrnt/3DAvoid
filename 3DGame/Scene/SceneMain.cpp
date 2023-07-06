#include "SceneMain.h"
#include "SceneTitle.h"// �f�o�b�O�p
#include "SceneResult.h"
#include "../Util/GameSetting.h"
#include "../Char/Player/Player.h"
#include "../Char/Enemy/Enemy.h"
#include "../Stage/Field.h"
#include "../Stage/Wall.h"
#include <cassert>
#include "../Util/FontFunction.h"
#include "../System/Pause.h"

namespace
{
	// �w�i�̉摜�t�@�C���̏ꏊ
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
	m_fontHandle(-1),
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
	m_pWall = std::make_shared<Wall>();
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
	m_pFont->Init(m_fontHandle, 30, 0, -1);

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
	m_pFont->End(m_fontHandle);
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
		// �|�[�Y��ʂ��J����Ă���Ƃ�
		if (!IsFading() && m_isFadeOut && !m_isBackScene && m_isNoteOpen)
		{
			// ���g���C
			return (new SceneMain());
			// �|�[�Y��ʂ̍��ڂ�������\��
		}
		// �|�[�Y��ʂ����Ă���Ƃ�
		else if (!IsFading() && m_isFadeOut && !m_isBackScene && !m_isNoteOpen)
		{
			// �Q�[�����I�������Ƃ�
			return (new SceneResult(m_score));
		}

	}

	if (!IsFading())
	{
		// �L��������������܂��͒��ӏ����ł͂�����������V�[���J��
		if (m_pPlayer->GetIsFall() || (Pad::IsTrigger(PAD_INPUT_1) && m_isNoteOpen))
		{
			//return new SceneMain;// �f�o�b�O�p�V�[���J��

			StartFadeOut();// �V�[���J��
		}
	}


	(this->*m_updateFunc)();

	if (m_score != 0)
	{
		// �X�R�A����𒴂��邽�тɓG��������@(�p�b�h�͓G�𑝂₷�f�o�b�O�p)
		if (m_score % 1000 == 0 && m_score <= 4000 /*Pad::IsTrigger(PAD_INPUT_7)*/)
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
	DrawBillboard3D(VGet(-1900.0f, 0.0f, 975.0f), 0.5f, 0.5f, 8000.0f, 0.0f, m_BackGroundHandle, true);

	// �v���C���[�̕`��
	if (m_invincibleTime % 3 == 0 || m_pushPause)
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
	//m_pWall->Draw();

	// �󂯂��_���[�W�ɂ���ĐF�ύX
	UpdateColor();

	// ���������₷������
	SetDrawBlendMode(DX_BLENDMODE_MULA, 155);
	DrawBox(0, 85, 300, 250, Color::kBlack, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// �v���C���[�̐�����ї��`��
	DrawFormatStringToHandle(10, 90, m_hpColor, m_fontHandle,"%d%%", m_pPlayer->GetBlowRate());

	// �X�R�A�`��
	DrawFormatStringToHandle(10, 120, Color::kWhite, m_fontHandle, "score:%d", m_score);

	// �Q�[���I�[�o�[�ɂȂ������̏���(�f�o�b�O�p)
	/*if (m_pPlayer->GetPos().y < -100.0f)
	{
		DrawStringToHandle(0, 150, "�Q�[���I�[�o�[", Color::kWhite, m_fontHandle);
		DrawStringToHandle(0, 180, "���U���g:PAD_INPUT_1", Color::kWhite, m_fontHandle);

	}*/

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
	// �{�c�̉\������
	// -------------------------
	// �_���[�W�ɂ���ĐF��ύX
	//m_hpColor = GetColor(m_red, m_decreaseColor, m_decreaseColor);

	//// �̗͕\�L�̐F�o�O��h��
	//if (m_decreaseColor < 0)
	//{
	//	m_decreaseColor = 0;
	//}
	//else if(m_decreaseColor != 0)
	//{
	//	m_decreaseColor = 255 - (m_pPlayer->GetBlowRate() * 2);
	//}

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
		m_score+=100;
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

	// �I�������ǂ���I��ł��邩�m�F
	//printfDx("%d", m_selectNum);
}
