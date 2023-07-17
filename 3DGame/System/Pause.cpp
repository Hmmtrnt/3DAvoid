#include "Pause.h"
#include "../Util/common.h"

namespace
{
	const int kUpPos = 100;// 一番上の座標

	const int kDownPos = 500;// 一番下の座標
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
	// デバッグ用
	SetDrawBlendMode(DX_BLENDMODE_MULA, 155);

	m_selectPosY = 100;
	for (int i = 0; i < 3; i++)
	{
		DrawBox(m_selectPosX, m_selectPosY, m_selectPosX + 200, m_selectPosY + 100, Color::kBlack, true);// 選択肢
		m_selectPosY += 200;
	}

	//DrawBox(200, 100, 400, 200, Color::kBlack, true);// 選択肢一
	//DrawBox(200, 300, 400, 400, Color::kBlack, true);// 選択肢二
	//DrawBox(200, 500, 400, 600, Color::kBlack, true);// 選択肢三
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawBox(m_selectPosX, m_posy, m_selectPosX + 200, m_posy + 100, Color::kWhite, true);// カーソル

	// 選択肢の仮テキスト
	DrawString(200, 200, "続ける", Color::kRed);
	DrawString(200, 400, "やり直し", Color::kRed);
	DrawString(200, 600, "あきらめる", Color::kRed);
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

/// <summary>
/// ポーズ画面を開いた時の処理
/// </summary>
/// <param name="isOpen">ポーズ画面を開いたかどうか</param>
void Pause::UpdateOpen(bool isOpen)
{
	// 定位置まで移動する
	if (m_selectPosX < 200)
	{
		m_selectPosX += 20;
	}
	// 定位置に来たら座標を固定
	else if (m_selectPosX >= 200)
	{
		m_selectPosX = 200;
	}

	if (!isOpen)
	{
		m_selectPosX = -200;
	}
}
