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
	void Draw();

private:
	// ポインタ
	std::vector<std::shared_ptr<Model>> m_pModel;// モデル
};

