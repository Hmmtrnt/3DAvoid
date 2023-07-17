#include "Pause.h"
#include "../Util/common.h"

namespace
{
	const int kUpPos = 100;// ��ԏ�̍��W

	const int kDownPos = 500;// ��ԉ��̍��W
}

Pause::Pause() :
	m_posx(200),
	m_posy(kUpPos),
	m_selectNum(0),
	m_selectPosX(-200),
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
			m_posy -= 200;
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
			m_posy += 200;
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
	for (int i = 0; i < 3; i++)
	{
		DrawBox(m_selectPosX, m_selectPosY, m_selectPosX + 200, m_selectPosY + 100, Color::kBlack, true);// �I����
		m_selectPosY += 200;
	}

	//DrawBox(200, 100, 400, 200, Color::kBlack, true);// �I������
	//DrawBox(200, 300, 400, 400, Color::kBlack, true);// �I������
	//DrawBox(200, 500, 400, 600, Color::kBlack, true);// �I�����O
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawBox(m_selectPosX, m_posy, m_selectPosX + 200, m_posy + 100, Color::kWhite, true);// �J�[�\��

	// �I�����̉��e�L�X�g
	DrawString(200, 200, "������", Color::kRed);
	DrawString(200, 400, "��蒼��", Color::kRed);
	DrawString(200, 600, "������߂�", Color::kRed);
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
	if (m_selectPosX < 200)
	{
		m_selectPosX += 20;
	}
	// ��ʒu�ɗ�������W���Œ�
	else if (m_selectPosX >= 200)
	{
		m_selectPosX = 200;
	}

	if (!isOpen)
	{
		m_selectPosX = -200;
	}
}
