#pragma once
#include <vector>
#include <memory>

class Model;

class Field
{
public:
	Field();
	virtual ~Field();

	void Init();
	void End();
	void Update();
	void DrawMain();
	void DrawTitle();

private:
	// ポインタ
	std::vector<std::shared_ptr<Model>> m_pModel;// モデル
};

