#pragma once
// ポーズ処理
// TODO:デバッグ状態なので見た目をしっかりする

class Pause
{
public:
	Pause();// コンストラクタ
	virtual ~Pause();// デストラクタ

	void Update();// 更新処理
	void Draw();// 描画処理　


private:
	// テスト変数
	int m_posx = 200;
	int m_posy = 200;



};