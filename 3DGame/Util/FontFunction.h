#pragma once
// フォントデータ書式付き文字列の描画関数(フォントは創英角ポップ体に固定)

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
	void End();

	// ここから下の関数はボツ

	/// <summary>
	/// フォント書式付き文字列描画
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	/// <param name="color">カラー</param>
	/// <param name="string">文字列</param>
	/// <param name="num">変数を入れる</param>
	void DrawFormat(int x, int y, unsigned int color, const char* string, int num);
	/// <summary>
	/// フォント書式無し文字列描画
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	/// <param name="string">文字列</param>
	/// <param name="color">カラー</param>
	void DrawNoFormat(int x, int y, const char* string, unsigned int color);

private:
	int m_fontHandle;// フォントハンドル
};

