#include "FontFunction.h"
#include "DxLib.h"
#include <cassert>

namespace
{
	const char* const kFontName = "HG�n�p�p�߯�ߑ�";
}

StringInit::StringInit() :
	m_fontHandle(-1)
{
}

StringInit::~StringInit()
{
	
}

// �t�H���g�f�[�^�쐬
void StringInit::Init(int& fontHandle, int fontSize, int fontThick, int fontType)
{
	fontHandle = CreateFontToHandle(kFontName, fontSize, fontThick, fontType);
	m_fontHandle = fontHandle;
	assert(fontHandle != -1);
}

// �t�H���g�f�[�^�폜
void StringInit::End()
{
	DeleteFontToHandle(m_fontHandle);
}

// �������牺�̊֐��̓{�c

//�t�H���g�����t��������`��
void StringInit::DrawFormat(int x, int y, unsigned int color, const char* string, int num)
{
	DrawFormatStringToHandle(x, y, color, m_fontHandle, string, num);
}

// �t�H���g�����Ȃ�������`��
void StringInit::DrawNoFormat(int x, int y, const char* string, unsigned int color)
{
	DrawStringToHandle(x, y, string, color, m_fontHandle);
}
