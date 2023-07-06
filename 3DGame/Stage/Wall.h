#pragma once
#include <vector>
#include <memory>

class Model;

class Wall
{
public:
	Wall();
	virtual ~Wall();

	void Init();
	void End();
	void Update();
	void Draw();

private:
	std::vector<std::shared_ptr<Model>> m_pModel;
};
