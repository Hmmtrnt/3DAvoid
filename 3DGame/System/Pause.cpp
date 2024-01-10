#include "Pause.h"
#include "../Util/common.h"
#include "../System/SoundManager.h"
#include <cassert>

namespace
{
	// ポーズ画像のパス
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
	m_pSound = std::make_shared<SoundManager>();
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
	// ポーズ画面の選択
	if (Pad::IsTrigger(PAD_INPUT_UP))
	{
		if (selectNum > 0)
		{
			m_pSound->Start(Sound::Cursor, DX_PLAYTYPE_BACK, 255);
			m_posy -= 100;
			selectNum -= 1;
		}
	}
	else if (Pad::IsTrigger(PAD_INPUT_DOWN))
	{
		if (selectNum < 2)
		{
			m_pSound->Start(Sound::Cursor, DX_PLAYTYPE_BACK, 255);
			m_posy += 100;
			selectNum += 1;
		}
	}
	
}

void Pause::DrawPause()
{
	DrawExtendGraph(0, 0, 200, 100, m_pauseHandle[1], true);// ポーズ中描画

	DrawExtendGraph(m_selectPosX, 100, m_selectPosX + 300, 500, m_pauseHandle[2], true);// ポーズメニュー

	DrawExtendGraph(m_selectPosX + 50, m_posy, m_selectPosX + 1000, m_posy + 100, m_pauseHandle[3], true);// カーソル
}

void Pause::DrawNote()
{
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
