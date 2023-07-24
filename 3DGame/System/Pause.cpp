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

	const int kUpPos = 150;// 一番上の座標

	const int kDownPos = 350;// 一番下の座標
}

Pause::Pause() :
	m_posx(200),
	m_posy(kUpPos),
	m_selectNum(0),
	m_selectPosX(Game::kScreenWidth),
	m_selectPosY(0)
{
	// 画像データ読み込み
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
	// デバッグ用
	//SetDrawBlendMode(DX_BLENDMODE_MULA, 155);

	//m_selectPosY = 100;
	////for (int i = 0; i < 3; i++)
	////{
	////	DrawBox(m_selectPosX, m_selectPosY, m_selectPosX + 200, m_selectPosY + 100, Color::kBlack, true);// 選択肢
	////	m_selectPosY += 200;
	////}

	//DrawBox(m_selectPosX, 100, m_selectPosX + 300, 500, Color::kBlack, true);// 選択肢一

	//
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawExtendGraph(0, 0, 200, 100, m_pauseHandle[1], true);// ポーズ中描画

	DrawExtendGraph(m_selectPosX, 100, m_selectPosX + 300, 500, m_pauseHandle[2], true);// ポーズメニュー

	//DrawBox(m_selectPosX, m_posy, m_selectPosX + 300, m_posy + 100, Color::kWhite, true);// カーソル
	DrawExtendGraph(m_selectPosX + 50, m_posy, m_selectPosX + 1000, m_posy + 100, m_pauseHandle[3], true);// カーソル
	//DrawGraph(m_selectPosX, m_posy, m_pauseHandle[4], true);

	// 選択肢の仮テキスト
	/*DrawString(Game::kScreenWidth - 250, 150, "再開", Color::kRed);
	DrawString(Game::kScreenWidth - 250, 250, "設定", Color::kRed);
	DrawString(Game::kScreenWidth - 250, 350, "やり直し", Color::kRed);
	DrawString(Game::kScreenWidth - 250, 450, "あきらめる", Color::kRed);*/

	//DrawFormatString(0, 0, Color::kBlack, "%d", m_selectPosX);
}

void Pause::DrawNote()
{
	//SetDrawBlendMode(DX_BLENDMODE_MULA, 155);
	//// 注意書き仮置き
	//DrawBox(Game::kScreenWidth / 2 - 100, Game::kScreenHeight / 2 - 100, 
	//	Game::kScreenHeight / 2 + 500, Game::kScreenHeight / 2 + 100, Color::kBlack, true);// 選択肢一
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//// 注意書きの仮テキスト
	//DrawString(Game::kScreenWidth / 2 - 100, Game::kScreenHeight / 2 - 100, "注意書き(やり直しを押したときのみ描画)", Color::kRed);
	//DrawString(Game::kScreenWidth / 2 - 100, Game::kScreenHeight / 2 - 70, "記録は保存されません", Color::kRed);

	//DrawGraph(0, 0, m_pauseHandle[0], true);
	DrawExtendGraph(Game::kScreenWidth / 2 - 170, Game::kScreenHeight / 2 - 160,
		Game::kScreenHeight / 2 + 490, Game::kScreenHeight / 2 + 100, m_pauseHandle[0], true);
}

/// <summary>
/// ポーズ画面を開いた時の処理
/// </summary>
/// <param name="isOpen">ポーズ画面を開いたかどうか</param>
void Pause::UpdateOpen(bool isOpen)
{
	// 定位置まで移動する
	if (m_selectPosX > Game::kScreenWidth - 300)
	{
		m_selectPosX -= 50;
	}
	// 定位置に来たら座標を固定
	else if (m_selectPosX <= Game::kScreenWidth - 300)
	{
		m_selectPosX = Game::kScreenWidth - 300;
	}

	if (!isOpen)
	{
		m_selectPosX = Game::kScreenWidth;
	}
}
