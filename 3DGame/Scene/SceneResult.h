#pragma once
#include "SceneBase.h"
#include "../Util/common.h"

class SceneResult : public SceneBase
{
public:
	SceneResult();
	virtual ~SceneResult();

	SceneBase* Update();
	void Draw();

private:

};

