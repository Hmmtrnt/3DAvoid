#pragma once
class SceneBase
{
public:
	SceneBase(){}
	virtual ~SceneBase() {}

	virtual void Init() = 0;// ‰Šú‰»
	virtual void End() = 0;// I—¹ˆ—
	virtual SceneBase* Update() { return this; }// XVˆ—
	virtual void Draw() = 0;// •`‰æ
};

