#pragma once
#include "SceneBase.h"
#include "../Util/common.h"

class SceneResult : public SceneBase
{
public:
	SceneResult();
	virtual ~SceneResult();

	void Init();
	void End();
	SceneBase* Update();
	void Draw();

private:

};

