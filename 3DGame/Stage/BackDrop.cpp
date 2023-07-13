#include "BackDrop.h"
#include "../Util/common.h"
#include <cassert>

namespace
{
	const char* const kImgName = "Data/2D/BackGround/BackDrop1.png";// ”wŒi
}

BackDrop::BackDrop() :
	m_handlePosX(0),
	m_handlePosY(0),
	m_handlePosX2(-Game::kScreenWidth),
	m_handlePosY2(0),
	m_scrollPower(1)

{
	m_first.m_width = 0;
	m_first.m_height = 0;

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
	m_first.m_width += m_scrollPower;
	m_second.m_width += m_scrollPower;

	if (m_first.m_width >= Game::kScreenWidth)
	{
		m_first.m_width = -Game::kScreenWidth;
	}
	if (m_second.m_width >= Game::kScreenWidth)
	{
		m_second.m_width = -Game::kScreenWidth;
	}
}

void BackDrop::Draw()
{
	DrawExtendGraph(m_first.m_width, m_first.m_height,
		m_first.m_width + Game::kScreenWidth,
		Game::kScreenHeight,
		m_handle, true);
	DrawExtendGraph(m_second.m_width, m_second.m_height,
		m_second.m_width + Game::kScreenWidth,
		Game::kScreenHeight,
		m_handle, true);
}
