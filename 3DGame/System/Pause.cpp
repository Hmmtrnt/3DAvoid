#include "Pause.h"
#include "../Util/common.h"
#include <cassert>

namespace
{
	const char* const kPauseId[4] = {
		"Data/2D/Pause/Note.png",
		"Data/2D/Pause/Pause.png",
		"Data/2D/Pause/PauseMenu.png",
		"Data/2D/Pause/PauseCursor.png"
	};

	const int kUpPos = 150;// ��ԏ�̍��W

	const int kDownPos = 350;// ��ԉ��̍��W
}

Pause::Pause() :
	m_posx(200),
	m_posy(kUpPos),
	m_selectNum(0),
	m_selectPosX(Game::kScreenWidth),
	m_selectPosY(0)
{
	// �摜�f�[�^�ǂݍ���
	for (int i = 0; i < 4; i++)
	{
		m_pauseHandle[i] = -1;
		m_pauseHandle[i] = LoadGraph(kPauseId[i]);
		assert(m_pauseHandle[i] != -1);
	}
	
}

Pause::~Pause()
{
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(m_pauseHandle[i]);
	}
}

void Pause::Update(int& selectNum)
{
	if (Pad::IsTrigger(PAD_INPUT_UP))
	{
		
		if (selectNum > 0)
		{
			m_posy -= 100;
			selectNum -= 1;
		}
		else
		{
			/*m_posy = kDownPos;
			selectNum = 3;*/
		}
	}
	else if (Pad::IsTrigger(PAD_INPUT_DOWN))
	{
		if (selectNum < 2)
		{
			m_posy += 100;
			selectNum += 1;
		}
		else
		{
			/*m_posy = kUpPos;
			selectNum = 0;*/
		}
	}
	
}

void Pause::DrawPause()
{
	// �f�o�b�O�p
	//SetDrawBlendMode(DX_BLENDMODE_MULA, 155);

	//m_selectPosY = 100;
	////for (int i = 0; i < 3; i++)
	////{
	////	DrawBox(m_selectPosX, m_selectPosY, m_selectPosX + 200, m_selectPosY + 100, Color::kBlack, true);// �I����
	////	m_selectPosY += 200;
	////}

	//DrawBox(m_selectPosX, 100, m_selectPosX + 300, 500, Color::kBlack, true);// �I������

	//
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawExtendGraph(0, 0, 200, 100, m_pauseHandle[1], true);// �|�[�Y���`��

	DrawExtendGraph(m_selectPosX, 100, m_selectPosX + 300, 500, m_pauseHandle[2], true);// �|�[�Y���j���[

	//DrawBox(m_selectPosX, m_posy, m_selectPosX + 300, m_posy + 100, Color::kWhite, true);// �J�[�\��
	DrawExtendGraph(m_selectPosX + 50, m_posy, m_selectPosX + 1000, m_posy + 100, m_pauseHandle[3], true);// �J�[�\��
	//DrawGraph(m_selectPosX, m_posy, m_pauseHandle[4], true);

	// �I�����̉��e�L�X�g
	/*DrawString(Game::kScreenWidth - 250, 150, "�ĊJ", Color::kRed);
	DrawString(Game::kScreenWidth - 250, 250, "�ݒ�", Color::kRed);
	DrawString(Game::kScreenWidth - 250, 350, "��蒼��", Color::kRed);
	DrawString(Game::kScreenWidth - 250, 450, "������߂�", Color::kRed);*/

	//DrawFormatString(0, 0, Color::kBlack, "%d", m_selectPosX);
}

void Pause::DrawNote()
{
	//SetDrawBlendMode(DX_BLENDMODE_MULA, 155);
	//// ���ӏ������u��
	//DrawBox(Game::kScreenWidth / 2 - 100, Game::kScreenHeight / 2 - 100, 
	//	Game::kScreenHeight / 2 + 500, Game::kScreenHeight / 2 + 100, Color::kBlack, true);// �I������
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//// ���ӏ����̉��e�L�X�g
	//DrawString(Game::kScreenWidth / 2 - 100, Game::kScreenHeight / 2 - 100, "���ӏ���(��蒼�����������Ƃ��̂ݕ`��)", Color::kRed);
	//DrawString(Game::kScreenWidth / 2 - 100, Game::kScreenHeight / 2 - 70, "�L�^�͕ۑ�����܂���", Color::kRed);

	//DrawGraph(0, 0, m_pauseHandle[0], true);
	DrawExtendGraph(Game::kScreenWidth / 2 - 170, Game::kScreenHeight / 2 - 160,
		Game::kScreenHeight / 2 + 490, Game::kScreenHeight / 2 + 100, m_pauseHandle[0], true);
}

/// <summary>
/// �|�[�Y��ʂ��J�������̏���
/// </summary>
/// <param name="isOpen">�|�[�Y��ʂ��J�������ǂ���</param>
void Pause::UpdateOpen(bool isOpen)
{
	// ��ʒu�܂ňړ�����
	if (m_selectPosX > Game::kScreenWidth - 300)
	{
		m_selectPosX -= 50;
	}
	// ��ʒu�ɗ�������W���Œ�
	else if (m_selectPosX <= Game::kScreenWidth - 300)
	{
		m_selectPosX = Game::kScreenWidth - 300;
	}

	if (!isOpen)
	{
		m_selectPosX = Game::kScreenWidth;
	}
}
