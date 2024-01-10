#include "BackDrop.h"
#include "../Util/common.h"
#include <cassert>

namespace
{
	const char* const kImgName = "Data/2D/BackGround/BackDrop1.png";// 背景画像のパス
}

BackDrop::BackDrop() :
	m_scrollSpeed(1)
{
	// 初期化
	// 1枚目の画像
	m_first.m_width = 0;
	m_first.m_height = 0;
	// 2枚目の画像
	m_second.m_width = -Game::kScreenWidth;
	m_second.m_height = 0;

	m_handle = LoadGraph(kImgName);
}

BackDrop::~BackDrop()
{
	DeleteGraph(m_handle);
}

void BackDrop::Update()
{
	MoveImage();
}

void BackDrop::Draw()
{
	// 描画モードをバイリニア法(拡大した時に見やすくなる)をセット
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	// 背景画像描画
	DrawExtendGraph(m_first.m_width, m_first.m_height,
		m_first.m_width + Game::kScreenWidth,
		Game::kScreenHeight,
		m_handle, true);
	DrawExtendGraph(m_second.m_width, m_second.m_height,
		m_second.m_width + Game::kScreenWidth,
		Game::kScreenHeight,
		m_handle, true);
	// 描画モードを標準に戻す
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

// 画像の移動
void BackDrop::MoveImage()
{
	m_first.m_width += m_scrollSpeed;
	m_second.m_width += m_scrollSpeed;

	// 画像が端まで行くと座標を初期化
	if (m_first.m_width >= Game::kScreenWidth)
	{
		m_first.m_width = -Game::kScreenWidth;
	}
	if (m_second.m_width >= Game::kScreenWidth)
	{
		m_second.m_width = -Game::kScreenWidth;
	}
}
