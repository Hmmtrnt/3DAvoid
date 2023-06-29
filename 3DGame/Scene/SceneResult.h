#pragma once
#include "SceneBase.h"
#include "../Util/common.h"
#include <memory>

class StringInit;

class SceneResult : public SceneBase
{
public:
	SceneResult(int score);// �R���X�g���N�^
	virtual ~SceneResult();// �f�X�g���N�^

	void Init();
	void End();
	SceneBase* Update();
	void Draw();

private:
	// �|�C���^
	std::shared_ptr<StringInit> m_pFont;

	// int
	int m_score;// �Q�[���œ����X�R�A
};

