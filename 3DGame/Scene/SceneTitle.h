#pragma once
#include "SceneBase.h"
#include "../Util/common.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	void Init();
	void End();
	SceneBase* Update();
	void Draw();

private:
	// int
	int m_titleHandle;// �^�C�g���̉摜�n���h��
};

