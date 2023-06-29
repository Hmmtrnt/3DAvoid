#pragma once


class FontFunction
{
public:
	FontFunction();
	virtual ~FontFunction();

	/// <summary>
	/// フォントデータ作成
	/// </summary>
	/// <param name="fontData">フォントデータ</param>
	/// <param name="fontSize">サイズ</param>
	/// <param name="fontThick">太さ</param>
	/// <param name="fontType">タイプ</param>
	void Init(int& fontData, int fontSize, int fontThick, int fontType);
	void End();
	void Update();
	void Draw();


private:

};

