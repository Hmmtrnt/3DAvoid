#pragma once
// フォントデータ読み込み(フォントは創英角ポップ体に固定)

class StringInit
{
public:
	StringInit();// コンストラクタ
	virtual ~StringInit();// デストラクタ

	/// <summary>
	/// フォントデータ作成
	/// </summary>
	/// <param name="fontSize">サイズ</param>
	/// <param name="fontThick">太さ</param>
	/// <param name="fontType">タイプ</param>
	void Init(int& fontHandle, int fontSize, int fontThick, int fontType);
	// フォントデータ削除
	void End(int& fontHandle);
};