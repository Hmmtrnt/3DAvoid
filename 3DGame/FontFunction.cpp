#include "FontFunction.h"
#include "DxLib.h"

namespace
{
	const char* const kFontName = "";
}

FontFunction::FontFunction()
{
}

FontFunction::~FontFunction()
{
}

void FontFunction::Init(int& fontData, int fontSize, int fontThick, int fontType)
{
	fontData = CreateFontToHandle(kFontName, fontSize, fontThick, fontType);
}

void FontFunction::End()
{
}

void FontFunction::Update()
{
}

void FontFunction::Draw()
{
}
