#include "BackDrop.h"
#include "../Util/common.h"
#include <cassert>

namespace
{
	const char* const kImgName = "Data/2D/BackGround/BackDrop1.png";// �w�i�摜�̃p�X
}

BackDrop::BackDrop() :
	m_scrollSpeed(1)
{
	// ������
	// 1���ڂ̉摜
	m_first.m_width = 0;
	m_first.m_height = 0;
	// 2���ڂ̉摜
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
	// �`�惂�[�h���o�C���j�A�@(�g�債�����Ɍ��₷���Ȃ�)���Z�b�g
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	// �w�i�摜�`��
	DrawExtendGraph(m_first.m_width, m_first.m_height,
		m_first.m_width + Game::kScreenWidth,
		Game::kScreenHeight,
		m_handle, true);
	DrawExtendGraph(m_second.m_width, m_second.m_height,
		m_second.m_width + Game::kScreenWidth,
		Game::kScreenHeight,
		m_handle, true);
	// �`�惂�[�h��W���ɖ߂�
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

// �摜�̈ړ�
void BackDrop::MoveImage()
{
	m_first.m_width += m_scrollSpeed;
	m_second.m_width += m_scrollSpeed;

	// �摜���[�܂ōs���ƍ��W��������
	if (m_first.m_width >= Game::kScreenWidth)
	{
		m_first.m_width = -Game::kScreenWidth;
	}
	if (m_second.m_width >= Game::kScreenWidth)
	{
		m_second.m_width = -Game::kScreenWidth;
	}
}
