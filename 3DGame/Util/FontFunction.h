#pragma once


class FontFunction
{
public:
	FontFunction();
	virtual ~FontFunction();

	/// <summary>
	/// �t�H���g�f�[�^�쐬
	/// </summary>
	/// <param name="fontData">�t�H���g�f�[�^</param>
	/// <param name="fontSize">�T�C�Y</param>
	/// <param name="fontThick">����</param>
	/// <param name="fontType">�^�C�v</param>
	void Init(int& fontData, int fontSize, int fontThick, int fontType);
	void End();
	void Update();
	void Draw();


private:

};

