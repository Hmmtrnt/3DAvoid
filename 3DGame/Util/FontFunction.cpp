#include "FontFunction.h"
#include "DxLib.h"
#include <cassert>

namespace
{
	const char* const kFontName = "HG創英角ﾎﾟｯﾌﾟ体";
}

StringInit::StringInit()
{
}

StringInit::~StringInit()
{
	
}

// フォントデータ作成
void StringInit::Init(int& fontHandle, int fontSize, int fontThick, int fontType)
{
	fontHandle = CreateFontToHandle(kFontName, fontSize, fontThick, fontType);
	assert(fontHandle != -1);
}

// フォントデータ削除
void StringInit::End(int& fontHandle)
{
	DeleteFontToHandle(fontHandle);
}