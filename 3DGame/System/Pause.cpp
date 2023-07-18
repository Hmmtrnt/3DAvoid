#include "Pause.h"
#include "../Util/common.h"

namespace
{
	const int kUpPos = 100;// ��ԏ�̍��W

	const int kDownPos = 400;// ��ԉ��̍��W
}

Pause::Pause() :
	m_posx(200),
	m_posy(kUpPos),
	m_selectNum(0),
	m_selectPosX(Game::kScreenWidth),
	m_selectPosY(0)
{
}

Pause::~Pause()
{
}

void Pause::Update(int& selectNum)
{
	if (Pad::IsTrigger(PAD_INPUT_UP))
	{
		
		if (m_posy != kUpPos)
		{
			m_posy -= 100;
			selectNum -= 1;
		}
		else
		{
			m_posy = kDownPos;
			selectNum = 2;
		}
	}
	else if (Pad::IsTrigger(PAD_INPUT_DOWN))
	{
		if (m_posy != kDownPos)
		{
			m_posy += 100;
			selectNum += 1;
		}
		else
		{
			m_posy = kUpPos;
			selectNum = 0;
		}
	}
	
}

void Pause::DrawPause()
{
	// �f�o�b�O�p
	SetDrawBlendMode(DX_BLENDMODE_MULA, 155);

	m_selectPosY = 100;
	//for (int i = 0; i < 3; i++)
	//{
	//	DrawBox(m_selectPosX, m_selectPosY, m_selectPosX + 200, m_selectPosY + 100, Color::kBlack, true);// �I����
	//	m_selectPosY += 200;
	//}

	DrawBox(m_selectPosX, 100, m_selectPosX + 300, 500, Color::kBlack, true);// �I������

	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawBox(m_selectPosX, m_posy, m_selectPosX + 300, m_posy + 100, Color::kWhite, true);// �J�[�\��

	// �I�����̉��e�L�X�g
	DrawString(Game::kScreenWidth - 250, 150, "�ĊJ", Color::kRed);
	DrawString(Game::kScreenWidth - 250, 250, "�ݒ�", Color::kRed);
	DrawString(Game::kScreenWidth - 250, 350, "��蒼��", Color::kRed);
	DrawString(Game::kScreenWidth - 250, 450, "������߂�", Color::kRed);

	DrawFormatString(0, 0, Color::kBlack, "%d", m_selectPosX);
}

void Pause::DrawNote()
{
	SetDrawBlendMode(DX_BLENDMODE_MULA, 155);
	// ���ӏ������u��
	DrawBox(Game::kScreenWidth / 2 - 100, Game::kScreenHeight / 2 - 100, 
		Game::kScreenHeight / 2 + 500, Game::kScreenHeight / 2 + 100, Color::kBlack, true);// �I������
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	// ���ӏ����̉��e�L�X�g
	DrawString(Game::kScreenWidth / 2 - 100, Game::kScreenHeight / 2 - 100, "���ӏ���(��蒼�����������Ƃ��̂ݕ`��)", Color::kRed);
	DrawString(Game::kScreenWidth / 2 - 100, Game::kScreenHeight / 2 - 70, "�L�^�͕ۑ�����܂���", Color::kRed);
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
