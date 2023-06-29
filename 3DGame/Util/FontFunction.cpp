#include "FontFunction.h"
#include "DxLib.h"

namespace
{
	const char* const kFontName = "�n�p�p�|�b�v��";
}

FontFunction::FontFunction() :
	m_fontHandle(-1)
{
}

FontFunction::~FontFunction()
{
}

// �t�H���g�f�[�^�쐬
void FontFunction::Init(int fontSize, int fontThick, int fontType)
{
	m_fontHandle = CreateFontToHandle(kFontName, fontSize, fontThick, fontType);
}

// �t�H���g�f�[�^�폜
void FontFunction::End()
{
	DeleteFontToHandle(m_fontHandle);
}

//�t�H���g�����t��������`��
void FontFunction::DrawFormat(int x, int y, unsigned int color, const char* string, int num)
{
	DrawFormatStringToHandle(x, y, color, m_fontHandle, string, num);
}

// �t�H���g�����Ȃ�������`��
void FontFunction::DrawNoFormat(int x, int y, const char* string, unsigned int color)
{
	DrawStringToHandle(x, y, string, color, m_fontHandle);
}
