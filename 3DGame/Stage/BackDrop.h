#pragma once
#include <array>
// 背景処理

class BackDrop
{
public:
	BackDrop();
	virtual ~BackDrop();

	void Update();
	void Draw();

private:
	// 背景位置情報
	struct sBackImg
	{
		int m_width;			// 幅
		int m_height;			// 高さ
	};

	// 画像の位置情報
	sBackImg m_first;	// 一枚目
	sBackImg m_second;	// 二枚目

	// int
	// 座標
	int m_handlePosX;// X
	int m_handlePosY;// Y
	int m_handlePosX2;// X
	int m_handlePosY2;// Y
	int m_scrollPower;// スクロールする速度

	int m_handle;// 背景のハンドルデータ
	//std::array<sBackImg, 2> m_backImg;

};

