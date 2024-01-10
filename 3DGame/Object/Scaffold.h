// リザルト画面の台座
#pragma once
#include <memory>

class Model;

class Scaffold
{
public:
	Scaffold();
	virtual ~Scaffold();

	void Update();
	void Draw();

private:
	std::shared_ptr<Model> m_pModel;

	// int
	int m_modelHandle;// モデルハンドル
};

