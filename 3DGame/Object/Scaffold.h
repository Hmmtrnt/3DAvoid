// ���U���g��ʂ̑��
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
	int m_modelHandle;// ���f���n���h��
};

