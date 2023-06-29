#include "FontFunction.h"
#include "DxLib.h"
#include <cassert>

namespace
{
	const char* const kFontName = "創英角ポップ体";
}

StringInit::StringInit() :
	m_fontHandle(-1)
{
}

StringInit::~StringInit()
{
	
}

// フォントデータ作成
void StringInit::Init(int fontSize, int fontThick, int fontType)
{
	m_fontHandle = CreateFontToHandle(kFontName, fontSize, fontThick, fontType);
	assert(m_fontHandle != -1);
}

// フォントデータ削除
void StringInit::End()
{
	DeleteFontToHandle(m_fontHandle);
}

//フォント書式付き文字列描画
void StringInit::DrawFormat(int x, int y, unsigned int color, const char* string, int num)
{
	DrawFormatStringToHandle(x, y, color, m_fontHandle, string, num);
}

// フォント書式なし文字列描画
void StringInit::DrawNoFormat(int x, int y, const char* string, unsigned int color)
{
	DrawStringToHandle(x, y, string, color, m_fontHandle);
}
