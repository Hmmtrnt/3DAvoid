#pragma once

namespace Game
{
	// �E�C���h�E���[�h�ݒ�
#ifdef _DEBUG
	constexpr bool kWindowModo = true;
#else
	constexpr bool kWindowModo = false;
#endif
	// �E�C���h�E��
	const char* const kTitleText = "Don't Fall";
	// �E�C���h�E�T�C�Y
	constexpr int kScreenWidth = 1280;
	constexpr int kScreenHeight = 720;
	// �J���[���[�h
	constexpr int kColorDepth = 32;
};