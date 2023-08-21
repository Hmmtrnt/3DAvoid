#pragma once
#include "SceneBase.h"
#include <memory>
#include <DxLib.h>
#include "../Util/game.h"

class BackDrop;

class SceneExplanation : public SceneBase
{
public:
	SceneExplanation();
	virtual ~SceneExplanation();

	void Init();
	void End();
	SceneBase* Update();
	void Draw();

private:
	std::shared_ptr<BackDrop> m_pBackDrop;// 背景
	int m_handle;// 説明画面のハンドル
	int m_handleMove;// 説明動画のハンドル

	// 座標
	int m_posX;
	int m_posY;

};

