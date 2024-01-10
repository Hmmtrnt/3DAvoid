// 背景処理
#pragma once
#include <array>

class BackDrop
{
public:
	BackDrop();
	virtual ~BackDrop();

	void Update();
	void Draw();

	void MoveImage();	// 画像の移動

private:
	// 背景位置情報
	struct sBackImg
	{
		int m_width;	// 幅
		int m_height;	// 高さ
	};

	// 背景画像の位置情報
	sBackImg m_first;	// 一枚目
	sBackImg m_second;	// 二枚目

	int m_scrollSpeed;	// スクロールする速度
	int m_handle;// 背景のハンドルデータ
};

