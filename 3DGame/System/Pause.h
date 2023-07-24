#pragma once
// ポーズ処理

class Pause
{
public:
	Pause();// コンストラクタ
	virtual ~Pause();// デストラクタ

	void Update(int& selectNum);// 更新処理
	void DrawPause();// ポーズ描画処理
	void DrawNote();// 注意書き描画

	/// <summary>
	/// ポーズ画面を開いた時の処理
	/// </summary>
	/// <param name="isOpen">ポーズ画面を開いたかどうか</param>
	void UpdateOpen(bool isOpen);

private:
	// テスト変数
	int m_posx;// カーソル座標X
	int m_posy;// カーソル座標Y
	int m_selectNum;// カーソルが選択している場所

	// 選択肢の座標
	int m_selectPosX;
	int m_selectPosY;

	// ポーズ画面のハンドル
	int m_pauseHandle[4];

};