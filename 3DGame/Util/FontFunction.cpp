#include "FontFunction.h"
#include "DxLib.h"

namespace
{
	const char* const kFontName = "創英角ポップ体";
}

FontFunction::FontFunction() :
	m_fontHandle(-1)
{
}

FontFunction::~FontFunction()
{
}

// フォントデータ作成
void FontFunction::Init(int fontSize, int fontThick, int fontType)
{
	m_fontHandle = CreateFontToHandle(kFontName, fontSize, fontThick, fontType);
}

// フォントデータ削除
void FontFunction::End()
{
	DeleteFontToHandle(m_fontHandle);
}

//フォント書式付き文字列描画
void FontFunction::DrawFormat(int x, int y, unsigned int color, const char* string, int num)
{
	DrawFormatStringToHandle(x, y, color, m_fontHandle, string, num);
}

// フォント書式なし文字列描画
void FontFunction::DrawNoFormat(int x, int y, const char* string, unsigned int color)
{
	DrawStringToHandle(x, y, string, color, m_fontHandle);
}
