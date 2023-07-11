#pragma once
// ポーズ処理
// TODO:デバッグ状態なので見た目をしっかりする

class Pause
{
public:
	Pause();// コンストラクタ
	virtual ~Pause();// デストラクタ

	void Update(int& selectNum);// 更新処理
	void DrawPause();// ポーズ描画処理

	void DrawNote();// 注意書き描画

private:
	// テスト変数
	int m_posx;// カーソル座標X
	int m_posy;// カーソル座標Y
	int m_selectNum;// カーソルが選択している場所


};