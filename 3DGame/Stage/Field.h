// ステージ
#pragma once
#include <vector>
#include <memory>

class Model;

class Field
{
public:
	Field();
	virtual ~Field();

	void DrawMain();	// メインシーンの描画
	void DrawTitle();	// タイトルシーンの描画

private:
	// ポインタ
	std::vector<std::shared_ptr<Model>> m_pModel;// モデル
};

