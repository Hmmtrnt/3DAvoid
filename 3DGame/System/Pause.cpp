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

void Pause::DrawPause()
{
	// デバッグ用
	SetDrawBlendMode(DX_BLENDMODE_MULA, 155);
	DrawBox(200, 200, 400, 300, Color::kBlack, true);// 選択肢一
	DrawBox(200, 400, 400, 500, Color::kBlack, true);// 選択肢二
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawBox(m_posx, m_posy, m_posx + 200, m_posy + 100, Color::kWhite, true);// カーソル

	DrawString(0, 0, "ポーズ", Color::kBlack);
	// 選択肢の仮テキスト
	DrawString(200, 200, "続ける", Color::kRed);
	DrawString(200, 400, "やり直し", Color::kRed);
}

void Pause::DrawNote()
{
	SetDrawBlendMode(DX_BLENDMODE_MULA, 155);
	// 注意書き仮置き
	DrawBox(Game::kScreenWidth / 2 - 100, Game::kScreenHeight / 2 - 100, 
		Game::kScreenHeight / 2 + 500, Game::kScreenHeight / 2 + 100, Color::kBlack, true);// 選択肢一
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	// 注意書きの仮テキスト
	DrawString(Game::kScreenWidth / 2 - 100, Game::kScreenHeight / 2 - 100, "注意書き(やり直しを押したときのみ描画)", Color::kRed);
	DrawString(Game::kScreenWidth / 2 - 100, Game::kScreenHeight / 2 - 70, "記録は保存されません", Color::kRed);
}
