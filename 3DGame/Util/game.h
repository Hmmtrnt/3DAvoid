#pragma once

namespace Game
{
	// ウインドウモード設定
#ifdef _DEBUG
	constexpr bool kWindowModo = true;
#else
	constexpr bool kWindowModo = false;
#endif
	// ウインドウ名
	const char* const kTitleText = "Don't Fall";
	// ウインドウサイズ
	constexpr int kScreenWidth = 1280;
	constexpr int kScreenHeight = 720;
	// カラーモード
	constexpr int kColorDepth = 32;
};