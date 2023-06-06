#pragma once
class SceneBase
{
public:
	SceneBase() {}
	virtual ~SceneBase() {}

	virtual void Init() = 0;// 初期化
	virtual void End() = 0;// 終了処理
	virtual SceneBase* Update() { return this; }// 更新処理
	virtual void Draw() = 0;// 描画
};

