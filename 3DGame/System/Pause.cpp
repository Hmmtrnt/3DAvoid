#include "Pause.h"
#include "../Util/common.h"

Pause::Pause()
{
}

Pause::~Pause()
{
}

void Pause::Update(int& selectNum)
{
	if (Pad::IsTrigger(PAD_INPUT_UP))
	{
		
		if (m_posy == 400)
		{
			m_posy -= 200;
			selectNum -= 1;
		}
	}
	else if (Pad::IsTrigger(PAD_INPUT_DOWN))
	{
		if (m_posy == 200)
		{
			m_posy += 200;
			selectNum += 1;
		}
	}
	
}

void Pause::Draw()
{
	// �f�o�b�O�p
	SetDrawBlendMode(DX_BLENDMODE_MULA, 155);
	DrawBox(200, 200, 400, 300, Color::kBlack, true);// �I������
	DrawBox(200, 400, 400, 500, Color::kBlack, true);// �I������
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawBox(m_posx, m_posy, m_posx + 200, m_posy + 100, Color::kWhite, true);// �J�[�\��

	DrawString(0, 0, "�|�[�Y", Color::kBlack);
	// �e�L�X�g
	DrawString(200, 200, "������", Color::kRed);
	DrawString(200, 400, "��蒼��", Color::kRed);
}
