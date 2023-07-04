#include "FontFunction.h"
#include "DxLib.h"
#include <cassert>

namespace
{
	const char* const kFontName = "HG創英角ﾎﾟｯﾌﾟ体";
}

StringInit::StringInit() :
	m_fontHandle(-1)
{
}

StringInit::~StringInit()
{
	
}

// フォントデータ作成
void StringInit::Init(int& fontHandle, int fontSize, int fontThick, int fontType)
{
	fontHandle = CreateFontToHandle(kFontName, fontSize, fontThick, fontType);
	m_fontHandle = fontHandle;
	assert(fontHandle != -1);
}

// フォントデータ削除
void StringInit::End()
{
	DeleteFontToHandle(m_fontHandle);
}

// ここから下の関数はボツ

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
