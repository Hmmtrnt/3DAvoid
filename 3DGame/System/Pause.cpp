#include "Pause.h"
#include "../Util/common.h"

Pause::Pause()
{
}

Pause::~Pause()
{
}

void Pause::Update()
{
	if (Pad::IsTrigger(PAD_INPUT_UP))
	{
		
		if (m_posy == 400)
		{
			m_posy -= 200;
		}
	}
	else if (Pad::IsTrigger(PAD_INPUT_DOWN))
	{
		if (m_posy == 200)
		{
			m_posy += 200;
		}
	}
	
}

void Pause::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_MULA, 200);
	// デバッグ用
	DrawBox(200, 200, 200, 300, Color::kBlack, true);

	DrawBox(200, 400, 200, 500, Color::kBlack, true);
	DrawBox(m_posx, m_posy, m_posx, m_posy + 100, Color::kWhite, true);

	SetDrawBlendMode(DX_BLENDMODE_MULA, 255);
}
