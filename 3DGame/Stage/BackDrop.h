#pragma once
// 背景処理

class BackDrop
{
public:
	BackDrop();
	virtual ~BackDrop();

	void Update();
	void Draw();

private:
	// int
	int m_Handle;// 背景のハンドルデータ
};

