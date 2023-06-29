#pragma once
#include "SceneBase.h"
#include "../Util/common.h"
#include <memory>

class StringInit;

class SceneResult : public SceneBase
{
public:
	SceneResult(int score);// コンストラクタ
	virtual ~SceneResult();// デストラクタ

	void Init();
	void End();
	SceneBase* Update();
	void Draw();

private:
	// ポインタ
	std::shared_ptr<StringInit> m_pFont;

	// int
	int m_score;// ゲームで得たスコア
};

