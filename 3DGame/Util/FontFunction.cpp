#include "FontFunction.h"
#include "DxLib.h"
#include <cassert>

namespace
{
	const char* const kFontName = "HG�n�p�p�߯�ߑ�";
}

StringInit::StringInit()
{
}

StringInit::~StringInit()
{
	
}

// �t�H���g�f�[�^�쐬
void StringInit::Init(int& fontHandle, int fontSize, int fontThick, int fontType)
{
	fontHandle = CreateFontToHandle(kFontName, fontSize, fontThick, fontType);
	assert(fontHandle != -1);
}

// �t�H���g�f�[�^�폜
void StringInit::End(int& fontHandle)
{
	DeleteFontToHandle(fontHandle);
}