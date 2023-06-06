#pragma once
#include "SceneBase.h"
#include "../Util/common.h"

class SceneMain : public SceneBase
{
public:
    SceneMain();
    virtual ~SceneMain();

    void Init();
    void End();
    SceneBase* Update();
    void Draw();
};

