// 共通変数
#pragma once
#include "DxLib.h"
#include "Pad.h"
#include "game.h"

// 色
namespace Color
{
	const int kWhite = 0xffffff;	// 白
	const int kBlack = 0x000000;	// 黒
	const int kRed = 0xff0000;		// 赤
	const int kTomato = 0xff6347;	// 若干薄い赤
	const int kCoral = 0xff7f50;	// 赤よりのオレンジ
	const int kOrangered = 0xff4500;// オレンジ
}

namespace BlendParameter
{
	const int kMaxBlendParameter = 255;// ブレンドパラメータの最大値
}